/* Copyright (c) 2019-2021 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_VM
#include <kernel/vm.h>
#else /* !CONFIG_USE_NEW_VM */
#include <kernel/memory.h>
#include <kernel/types.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>
#include <sched/signal.h>

#include <hybrid/__minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#undef CONFIG_MFILE_LEGACY_VIO_OPS
#if 1 /* TODO: Currently required for backwards compatibility to the old mman.
       * The plan is to eventually disable this option, and merge `inode_type'
       * with `mfile_ops', which should then contain a pointer for VIO operators.
       * With this option enabled, the old behavior is used, instead. */
#define CONFIG_MFILE_LEGACY_VIO_OPS
#endif

#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mfile; /* Memory storage owner/descriptor. */
struct mfile_ops;
struct mman;
struct aio_buffer;
struct aio_pbuffer;

#ifndef __mpart_slist_defined
#define __mpart_slist_defined 1
SLIST_HEAD(mpart_slist, mpart);
#endif /* !__mpart_slist_defined */

/* Block-index within some given mem-file. */
#ifndef __mfile_block_t_defined
#define __mfile_block_t_defined 1
typedef pos_t mfile_block_t;
#endif /* !__mfile_block_t_defined */



/* Special value for `struct mfile::mf_parts': Anonymous file.
 * When this value is used, then attempting to access one of the file's
 * memory parts will yield unique parts for every access, such that
 * writes made to one part will not be mirrored by writes made to another
 * part that (supposedly) describes the same position. */
#define MFILE_PARTS_ANONYMOUS ((struct mpart *)-1)


#ifdef CONFIG_USE_NEW_VM
#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined 1
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */
#endif /* CONFIG_USE_NEW_VM */

struct mfile_ops {
	/* [0..1] Finalize + free the given mem-file. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (FCALL *mo_destroy)(struct mfile *__restrict self);
	/* [0..1] Initialize the given mem-part (called whenever a new part is created)
	 * NOTE: This function isn't required to do anything, and may assume that the
	 *       given part is already fully initialized as ABSENT, with the proper
	 *       address range already assigned.
	 * This function is mainly intended to assign physical memory ranges for mem-parts
	 * that directly map physical memory into virtual memory, allowing them to use this
	 * function to assign the proper memory ranges. */
	NOBLOCK NONNULL((1, 2)) void (FCALL *mo_initpart)(struct mfile *__restrict self,
	                                                  struct mpart *__restrict part);
	/* [0..1] Load/initialize the given physical memory buffer (this is the read-from-disk callback)
	 * NOTE: As long as the size of a single file-block is `<= PAGESIZE', this function
	 *       is allowed to assume that `buffer' is aligned by the size of a file-block.
	 *       With file-blocks larger than PAGESIZE, `buffer' may only be aligned by `PAGESIZE' */
	NONNULL((1)) void (KCALL *mo_loadblocks)(struct mfile *__restrict self,
	                                         mfile_block_t first_block,
	                                         physaddr_t buffer, size_t num_blocks);
	/* [0..1] Save/write-back the given physical memory buffer (this is the write-to-disk callback)
	 * NOTE: As long as the size of a single file-block is `<= PAGESIZE', this function
	 *       is allowed to assume that `buffer' is aligned by the size of a file-block.
	 *       With file-blocks larger than PAGESIZE, `buffer' may only be aligned by `PAGESIZE' */
	NONNULL((1)) void (KCALL *mo_saveblocks)(struct mfile *__restrict self,
	                                         mfile_block_t first_block,
	                                         physaddr_t buffer, size_t num_blocks);
	/* [0..1] Called the first time the `MPART_F_CHANGED' flag is set for `part'.
	 * WARNING: This function is called while a lock to `part' is held!
	 * NOTE: Not invoked if a new change part is created as the result
	 *       of an already-known-as-changed part being split. */
	NOBLOCK NONNULL((1, 2)) void
	/*NOTHROW*/ (FCALL *mo_changed)(struct mfile *__restrict self,
	                                struct mpart *__restrict part);
#ifndef CONFIG_MFILE_LEGACY_VIO_OPS
	/* [0..1] VIO file operators. (when non-NULL, then this file is backed by VIO,
	 *        and the `mo_loadblocks' and `mo_saveblocks' operators are ignored) */
	struct vio_operators const *mo_vio;
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */

#ifdef CONFIG_USE_NEW_VM /* Hacky forward-compatibility... */
	/* [0..1] Optional operators for when read(2) or write(2) is used with
	 *        a file descriptor pointing to a vm_datablock of this type.
	 * These callbacks are used by UVIO datablocks to implement the
	 * server/client architecture for user-space driven VIO emulation. */
	WUNUSED NONNULL((1)) size_t
	(KCALL *dt_handle_read)(struct vm_datablock *__restrict self,
	                        USER CHECKED void *dst,
	                        size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1)) size_t
	(KCALL *dt_handle_write)(struct vm_datablock *__restrict self,
	                         USER CHECKED void const *src,
	                         size_t num_bytes, iomode_t mode) THROWS(...);
	/* [0..1] Same as above, but used when polling for data being available.
	 * When not implemented (i.e. when set to `NULL'), poll is implemented for
	 * the datablock through use of `rwlock_poll(read|write)(&self->db_lock)' */
	NONNULL((1)) void
	(KCALL *dt_handle_pollconnect)(struct vm_datablock *__restrict self,
	                               poll_mode_t what) THROWS(...);
	WUNUSED NONNULL((1)) poll_mode_t
	(KCALL *dt_handle_polltest)(struct vm_datablock *__restrict self,
	                            poll_mode_t what) THROWS(...);
#endif /* CONFIG_USE_NEW_VM */

	/* TODO: Operator `mo_changed': Called when the backing memory of a part is modified. */
	/* TODO: Operator `mo_attr_changed': Called when one of the file's attribute fields changed. */

	/* TODO: Additional operator callbacks for handle integration:
	 *  - read   (note: pread() is implemented via `mfile_read()')
	 *  - write  (note: pwrite() is implemented via `mfile_write()')
	 *  - pollconnect
	 *  - polltest
	 *  - seek
	 *  - stat
	 *  - ioctl
	 *  - truncate    (override for the default action, which does a split and uses
	 *                 `mfile_makeanon_subrange()' to mark all whole parts above the
	 *                 given address as anonymous)
	 */
};

struct mfile_lockop; /* from "mfile-lockop.h" */
SLIST_HEAD(mfile_lockop_slist, mfile_lockop);

struct mfile {
	WEAK refcnt_t               mf_refcnt;     /* Reference counter. */
	struct mfile_ops const     *mf_ops;        /* [1..1][const] File operators. */
#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
	struct vio_operators const *mf_vio;        /* [0..1][const] VIO operators. (deprecated field!) */
#endif /* CONFIG_MFILE_LEGACY_VIO_OPS */
	struct atomic_rwlock        mf_lock;       /* Lock for this file. */
	RBTREE_ROOT(struct mpart)   mf_parts;      /* [0..n][lock(mf_lock)] File parts. */
	struct sig                  mf_initdone;   /* Signal broadcast whenever one of the blocks of one of the
	                                            * contained parts changes state from INIT to LOAD. */
	struct mfile_lockop_slist   mf_lockops;    /* [0..n][lock(ATOMIC)] Chain of dead parts (that still have
	                                            * to be removed from `mf_parts'). */
	struct REF mpart_slist      mf_changed;    /* [0..n][lock(ATOMIC)]
	                                            * Chain of references to parts that contain unsaved changes.
	                                            * NOTE: Set to `MFILE_PARTS_ANONYMOUS' if changed parts should
	                                            *       always be ignored unconditionally. This should also be
	                                            *       done when `mf_ops->mo_saveblocks' is `NULL'! */
	size_t                      mf_part_amask; /* [const] == MAX(PAGESIZE, 1 << mf_blockshift) - 1
	                                            * This field describes the minimum alignment of file positions
	                                            * described by parts, minus one (meaning it can be used as a
	                                            * mask) */
	unsigned int                mf_blockshift; /* [const] == log2(FILE_BLOCK_SIZE) */
	/* TODO: File size field: (with [lock(mf_lock)])
	 *   - Attempting to map memory beyond file's end should either
	 *     fail, or cause anon+zero'd memory to be mapped instead.
	 *     XXX: Investigate what mmap(2) does here...
	 *   - Automatically increased when new data is written:
	 *      - Use of `mfile_write()' can increase this value
	 *      - writes done via modifications to mapped mem-parts don't
	 *   - Lowering causes all mem-parts above to be anonymized at the next greater page-boundary
	 *   - An additional [lock(WRITE_ONCE)]-flag should exist which can be set to make the field [const]
	 *
	 * NOTE: Using this field, we can also implement `mfile_write_append()',
	 *       which does all of the necessary work to atomically append data
	 *       at the end of a file.
	 *
	 * XXX: It may also make sense to directly integrate access/modified timestamps
	 *      right here. That way, they can be updated at the appropriate spots!
	 *
	 */
};


#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define __mfile_init_vio(self)  (self)->mf_vio = __NULLPTR,
#define __mfile_cinit_vio(self) __hybrid_assert((self)->mf_vio == __NULLPTR),
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define __mfile_init_vio(self)  /* nothing */
#define __mfile_cinit_vio(self) /* nothing */
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */

#define mfile_init_blockshift(self, block_shift)                                \
	((self)->mf_blockshift = (block_shift),                                     \
	 (self)->mf_part_amask = ((size_t)1 << (((self)->mf_blockshift) > PAGESHIFT \
	                                        ? ((self)->mf_blockshift)           \
	                                        : PAGESHIFT)) -                     \
	                         1)
#define mfile_init(self, ops, block_shift) \
	((self)->mf_refcnt = 1,                \
	 (self)->mf_ops    = (ops),            \
	 __mfile_init_vio(self)                \
	 atomic_rwlock_init(&(self)->mf_lock), \
	 (self)->mf_parts = __NULLPTR,         \
	 sig_init(&(self)->mf_initdone),       \
	 SLIST_INIT(&(self)->mf_lockops),      \
	 SLIST_INIT(&(self)->mf_changed),      \
	 mfile_init_blockshift(self, block_shift))
#define mfile_cinit(self, ops, block_shift)             \
	((self)->mf_refcnt = 1,                             \
	 (self)->mf_ops    = (ops),                         \
	 __mfile_cinit_vio(self)                            \
	 atomic_rwlock_cinit(&(self)->mf_lock),             \
	 __hybrid_assert((self)->mf_parts == __NULLPTR),    \
	 sig_cinit(&(self)->mf_initdone),                   \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_lockops)), \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_changed)), \
	 mfile_init_blockshift(self, block_shift))

/* Get a [0..1]-pointer to the VIO operators of `self' */
#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define mfile_getvio(self) ((self)->mf_vio)
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define mfile_getvio(self) ((self)->mf_ops->mo_vio)
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */


#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define MFILE_INIT_EX(refcnt, ops, parts, changed, blockshift)                         \
	{                                                                                  \
		/* .mf_refcnt     = */ refcnt,                                                 \
		/* .mf_ops        = */ ops,                                                    \
		/* .mf_vio        = */ __NULLPTR,                                              \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT,                                     \
		/* .mf_parts      = */ parts,                                                  \
		/* .mf_initdone   = */ SIG_INIT,                                               \
		/* .mf_lockops    = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_changed    = */ { changed },                                            \
		/* .mf_part_amask = */ __hybrid_max_c2(PAGESIZE, (size_t)1 << blockshift) - 1, \
		/* .mf_blockshift = */ blockshift,                                             \
	}
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define MFILE_INIT_EX(refcnt, ops, parts, changed, blockshift)                         \
	{                                                                                  \
		/* .mf_refcnt     = */ refcnt,                                                 \
		/* .mf_ops        = */ ops,                                                    \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT,                                     \
		/* .mf_parts      = */ parts,                                                  \
		/* .mf_initdone   = */ SIG_INIT,                                               \
		/* .mf_lockops    = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_changed    = */ { changed },                                            \
		/* .mf_part_amask = */ __hybrid_max_c2(PAGESIZE, (size_t)1 << blockshift) - 1, \
		/* .mf_blockshift = */ blockshift,                                             \
	}
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */
#define MFILE_INIT(ops, blockshift)      MFILE_INIT_EX(1, ops, __NULLPTR, __NULLPTR, blockshift)
#define MFILE_INIT_ANON(ops, blockshift) MFILE_INIT_EX(1, ops, MFILE_PARTS_ANONYMOUS, MFILE_PARTS_ANONYMOUS, blockshift)


/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in that it will also ensure that returned pages are properly aligned, as well
 * as that the given `max_pages' is also properly aligned. Note however that so-long
 * as the size of a single file-block is <= PAGESIZE, this function behaves 100%
 * identical to the above call to `page_malloc_part()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem)(struct mfile *__restrict self,
                                   physpagecnt_t max_pages,
                                   physpagecnt_t *__restrict res_pages);


/* Destroy a given mem-file */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mfile, mf_refcnt, mfile_destroy)


/* Check if the given mem-file has been marked as anonymous.
 * When this is the case, then accessed mem-parts of the file
 * as always unique and never the same during repeated calls. */
#define mfile_isanon(self) ((self)->mf_parts == MFILE_PARTS_ANONYMOUS)

/* Floor- or ceil-align a given `addr' such that it may describe the start/end of a mem-part. */
#define mfile_addr_flooralign(self, addr) (pos_t)((uint64_t)(addr) & ~(self)->mf_part_amask)
#define mfile_addr_ceilalign(self, addr)  (pos_t)(((uint64_t)(addr) + (self)->mf_part_amask) & ~(self)->mf_part_amask)
#define mfile_addr_aligned(self, addr)    (((uint64_t)(addr) & (self)->mf_part_amask) == 0)


/* Reap lock operations of `self' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_lockops_reap)(struct mfile *__restrict self);
#define mfile_lockops_mustreap(self) \
	(__hybrid_atomic_load((self)->mf_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mfile_lockops_reap(self) _mfile_lockops_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mfile_lockops_reap(self) (void)(!mfile_lockops_mustreap(self) || (_mfile_lockops_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

/* Lock accessor helpers for `struct mfile' */
#define mfile_lock_write(self)      atomic_rwlock_write(&(self)->mf_lock)
#define mfile_lock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mf_lock)
#define mfile_lock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mf_lock)
#define mfile_lock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->mf_lock), mfile_lockops_reap(self))
#define mfile_lock_endwrite_f(self) atomic_rwlock_endwrite(&(self)->mf_lock)
#define mfile_lock_read(self)       atomic_rwlock_read(&(self)->mf_lock)
#define mfile_lock_read_nx(self)    atomic_rwlock_read_nx(&(self)->mf_lock)
#define mfile_lock_tryread(self)    atomic_rwlock_tryread(&(self)->mf_lock)
#define mfile_lock_endread(self)    (void)(atomic_rwlock_endread(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_endread_f(self)  atomic_rwlock_endread(&(self)->mf_lock)
#define mfile_lock_end(self)        (void)(atomic_rwlock_end(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_end_f(self)      atomic_rwlock_end(&(self)->mf_lock)
#define mfile_lock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mf_lock)
#define mfile_lock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->mf_lock)
#define mfile_lock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mf_lock)
#define mfile_lock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mf_lock)
#define mfile_lock_reading(self)    atomic_rwlock_reading(&(self)->mf_lock)
#define mfile_lock_writing(self)    atomic_rwlock_writing(&(self)->mf_lock)
#define mfile_lock_canread(self)    atomic_rwlock_canread(&(self)->mf_lock)
#define mfile_lock_canwrite(self)   atomic_rwlock_canwrite(&(self)->mf_lock)


/* Make the given file anonymous. What this means is that:
 *  - Existing mappings of all mem-parts are altered to point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered. (s.a. `mfile_anon')
 *  - The `MPART_F_NO_GLOBAL_REF' flag is set for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted) */
FUNDEF NONNULL((1)) void FCALL
mfile_makeanon(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Split a potential part at `minaddr' and `maxaddr', and make
 * it so that all parts between that range are removed from the
 * part-tree of `self', by essentially anonymizing them.
 * This function can be used to implement `ftruncate(2)'
 *
 * NOTE: Unlike `mfile_makeanon()', this function doesn't mark
 *       the file itself as anonymous, meaning that more parts
 *       can still be created at a later point in time! */
FUNDEF NONNULL((1)) void FCALL
mfile_makeanon_subrange(struct mfile *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t minaddr,
                        pos_t maxaddr)
		THROWS(E_WOULDBLOCK);


/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
FUNDEF NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...);

/* Check if there are unwritten changes made to any of the parts of `self' */
#define mfile_haschanged(self) \
	(((uintptr_t)__hybrid_atomic_load((self)->mf_changed.slh_first, __ATOMIC_ACQUIRE) - 1) < (uintptr_t)-2)


/* Check `self' for a known mem-part that contains `addr', and (if found),
 * return that part. Otherwise, construct a new part start starts at `addr'
 * and spans at most `max_num_bytes' bytes (less may be returned if another part
 * already exists that describes the mapping above the requested location)
 * NOTE: The caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(max_num_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since. */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, ...);

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this function is mainly used to allocate
 * parts for `mfile_ndef' and `mfile_zero' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...);


struct mnode;

#ifndef __mnode_slist_defined
#define __mnode_slist_defined 1
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

struct mfile_map {
	/* Helper data structure to allocate+lock mem-nodes used
	 * for mapping files into a given memory-manager.
	 *
	 * Usage:
	 * >> void mman_mapat(struct mman *mm, void *addr, size_t num_bytes,
	 * >>                 struct mfile *file, pos_t offset) {
	 * >>     struct mfile_map map;
	 * >>     mfile_map_init_and_acquire(&map, file, offset, num_bytes);
	 * >>     TRY {
	 * >>         while (!mman_lock_tryacquire(mm)) {
	 * >>             mfile_map_release(&map);
	 * >>             while (!mman_lock_available(mm))
	 * >>                 task_yield();
	 * >>             mfile_map_acquire(&map);
	 * >>         }
	 * >>     } EXCEPT {
	 * >>         mfile_map_fini(&map);
	 * >>         RETHROW();
	 * >>     }
	 * >>     assert(!mnode_tree_rlocate(mm->mm_mappings, addr, (byte_t *)addr + num_bytes - 1));
	 * >>     while (!SLIST_EMPTY(&map.mfm_nodes)) {
	 * >>         struct mnode *node;
	 * >>         node = SLIST_FIRST(&map.mfm_nodes);
	 * >>         SLIST_REMOVE_HEAD(&map.mfm_nodes, _mn_alloc);
	 * >>         node->mn_flags = MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_SHARED;
	 * >>         node->mn_mman  = mm;
	 * >>         LIST_INSERT_HEAD(&node->mn_part->mp_share, node, mn_link);
	 * >>         LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
	 * >>         node->mn_fspath = NULL;
	 * >>         node->mn_fsname = NULL;
	 * >>         node->mn_minaddr += (uintptr_t)addr;
	 * >>         node->mn_maxaddr += (uintptr_t)addr;
	 * >>         mnode_tree_insert(&mm->mm_mappings, node);
	 * >>         mpart_lock_release(node->mn_part);
	 * >>     }
	 * >>     mman_lock_release(mm);
	 * >>     mfile_map_fini(&map);
	 * >> } */
	struct mfile              *mfm_file;  /* [1..1][const] File from which to allocate nodes. */
	PAGEDIR_PAGEALIGNED pos_t  mfm_addr;  /* [const] Starting address within the source file. */
	PAGEDIR_PAGEALIGNED size_t mfm_size;  /* [const] Total # of bytes that should be mapped. */
	unsigned int               mfm_prot;  /* Set of `0 | PROT_WRITE | PROT_SHARED' (other flags are silently ignored) */
	unsigned int               mfm_flags; /* Set of `0 | MAP_POPULATE | MAP_NONBLOCK' (other flags are silently ignored)
	                                       * MAP_POPULATE -- Ensure the following conditions when locking data parts:
	                                       *                  - mpart_setcore_or_unlock()
	                                       *                  - mpart_loadsome_or_unlock()   (within the range being mapped)
	                                       *                  - mpart_unsharecow_or_unlock() (only if `mfm_prot & PROT_WRITE')
	                                       * MAP_NONBLOCK -- The `MAP_POPULATE' flag may be ignored if page init of
	                                       *                 previously not loaded pages would block. Currently, all
	                                       *                 page initializers are assumed to block, with the exception
	                                       *                 of those that have a NULL-init callback, and the builtin
	                                       *                 file types known to be non-blocking (e.g. `mfile_zero') */
	struct mnode_slist         mfm_nodes; /* [0..n][owned] List of nodes.
	                                       *  - Linked via `_mn_alloc'
	                                       *  - Sorted ascendingly by part-offset
	                                       *  - `mn_minaddr' and `mn_maxaddr' are fill in to describe offsets
	                                       *    from the start of the mapping, such that nodes may directly be
	                                       *    inserted into an mman after adding the virtual base-address to
	                                       *    every node's `mn_minaddr' and `mn_maxaddr' field.
	                                       *  - The `mn_partoff' field is filled in correctly
	                                       *  - Each node is holding a lock to its `mn_part' field.
	                                       * The following fields are uninitialized:
	                                       *  - mn_flags, mn_mement, mn_mman, mn_link, mn_writable
	                                       *  - mn_fspath, mn_fsname */
	struct mnode_slist         mfm_flist; /* [0..n][owned] Internal list of free nodes.
	                                       * Required/superfluous mem-nodes are added/removed from
	                                       * this list for the purpose of allocation/deallocation.
	                                       * NOTE: Nodes in this list are free'd using `kfree()'!
	                                       *       No mcorepart support here! */
};

/* Lookup/create all parts to span the given address range, as
 * well as allocate 1 mem-node for each part, such that everything
 * put together forms 1 continuous range of fully mappable mem-parts.
 *
 * This function is designed for use in implementing `mman_map()', such
 * that this function is called before trying to acquire a lock to all
 * of the bound mem-part (s.a. `mfile_map_acquire') and the target mman.
 * As such, this API is designed to make it simple to:
 *  - Acquire locks to all of the parts, as well as making
 *    sure that all of the parts still form 1 uninterrupted
 *    mapping over the given address range in its entirety
 *  - Release locks to all of the parts */
#ifdef __INTELLISENSE__
NONNULL((1, 2)) void
mfile_map_init_and_acquire(struct mfile_map *__restrict self,
                           struct mfile *__restrict file,
                           PAGEDIR_PAGEALIGNED pos_t addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `mfile_map_init_and_acquire()', but don't acquire an initial lock. */
FUNDEF NONNULL((1, 2)) void FCALL
mfile_map_init(struct mfile_map *__restrict self,
               struct mfile *__restrict file,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes,
               unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
#else /* __INTELLISENSE__ */
#define mfile_map_init_and_acquire(self, file, addr, num_bytes, prot, flags) \
	((self)->mfm_file = (file), (self)->mfm_addr = (addr),                   \
	 (self)->mfm_size = (num_bytes), (self)->mfm_prot = (prot),              \
	 (self)->mfm_flags = (flags), SLIST_INIT(&(self)->mfm_flist),            \
	 _mfile_map_init_and_acquire(self))
#define mfile_map_init(self, file, addr, num_bytes, prot, flags)           \
	(mfile_map_init_and_acquire(self, file, addr, num_bytes, prot, flags), \
	 mfile_map_release(self))
#endif /* !__INTELLISENSE__ */
FUNDEF NONNULL((1)) void FCALL
_mfile_map_init_and_acquire(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
#define _mfile_map_init(self) \
	(_mfile_map_init_and_acquire(self), mfile_map_release(self))




/* Unlock or re-lock a mem-node allocator (that is: release/re-acquire locks
 * to all of the individual parts pointed to by the nodes allocated by `self')
 * For this purpose, re-locking a mem-node-allocator will (once again) make
 * sure that _all_ parts and nodes form a single, continuous range of mappings
 * as specified in the original call to `mfile_map_init()', leaving no
 * holes anywhere along the way, while the the act of holding locks to all of
 * the parts then guaranties that no new holes can possibly pop up out of the
 * blue. */
#define mfile_map_acquire(self) \
	do {                        \
	} while (!mfile_map_acquire_or_unlock(self, __NULLPTR))
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_release)(struct mfile_map *__restrict self);


/* (try to) do the same as `mfile_map_acquire()', but if doing so cannot be
 * done without blocking on an internal lock, then release all already-acquired
 * locks, invoke the `unlock' callback (if given), wait for the necessary lock
 * to become available, and return `false'.
 * Otherwise, don't invoke `unlock' and return `true'.
 * NOTE: In the case of an exception, `unlock' is guarantied to be invoked
 *       prior to the exception being thrown. */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_map_acquire_or_unlock(struct mfile_map *__restrict self,
                            struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Essentially does the same as `mfile_map_acquire_or_unlock()', however the
 * caller must already be holding locks to every mem-part mapped by `self'
 * However, use of `mfile_map_acquire_or_unlock()' is still more efficient,
 * since that function can do some tricks which this one can't (see impl)! */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_map_reflow_or_unlock(struct mfile_map *__restrict self,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Finalize a given mem-node-allocator.
 * This function will free (and only free; the caller is responsible to release
 * all of the locks to the individual mem-parts themselves, though for this purpose,
 * `mfile_map_release()' may also be used) all of the (still-)allocated
 * mem-nodes, as can be found apart of the `self->mfm_nodes' list. In addition
 * to freeing all of the container-nodes, this function will also drop 1 reference
 * from the mem-parts pointed-to by each of the nodes.
 * NOTE: This function doesn't necessarily have to be called if the caller was
 *       able to inherit _all_ of the nodes originally allocated (which should
 *       normally be the case when mapping was successful) */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL mfile_map_fini)(struct mfile_map *__restrict self);




/* Helpers for constructing unlockinfo objects that invoke `mfile_map_release()' when
 * triggering an unlock. - Mainly intended for use with `mman_getunmapped_or_unlock()'
 * once both mem-parts and the target mman have been locked in `mman_map()' */
struct mfile_map_with_unlockinfo
#ifdef __cplusplus
    : unlockinfo /* Underlying unlock info */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct unlockinfo mmwu_info; /* Underlying unlock info */
#endif /* __cplusplus */
	struct mfile_map  mmwu_map;  /* MFile mapping. */
};

/* Fallback to-be used with `mfile_map_with_unlockinfo::mmwu_info::ui_unlock'
 * When invoked, will call `mfile_map_release()' on the contained mfile-map. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_with_unlockinfo_unlock)(struct unlockinfo *__restrict self);






/* Read/write raw data to/from a given mem-file. */
FUNDEF NONNULL((1)) void KCALL mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_readv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_readv_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Helpers for directly reading to/from VIO space. */
#ifdef LIBVIO_CONFIG_ENABLED
FUNDEF NONNULL((1)) void KCALL mfile_vio_read(struct mfile *__restrict self, struct mpart *part, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_write(struct mfile *__restrict self, struct mpart *part, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_read_p(struct mfile *__restrict self, struct mpart *part, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_write_p(struct mfile *__restrict self, struct mpart *part, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_readv(struct mfile *__restrict self, struct mpart *part, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_writev(struct mfile *__restrict self, struct mpart *part, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_readv_p(struct mfile *__restrict self, struct mpart *part, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_writev_p(struct mfile *__restrict self, struct mpart *part, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#endif /* LIBVIO_CONFIG_ENABLED */

/* Builtin mem files */
DATDEF struct mfile /*     */ mfile_phys;     /* Physical memory access (file position is physical memory address) */
DATDEF struct mfile_ops const mfile_phys_ops; /* ... */
#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined 1
DATDEF struct mfile /*     */ mfile_ndef;     /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */
DATDEF struct mfile_ops const mfile_ndef_ops; /* ... */
#ifndef __mfile_zero_defined
#define __mfile_zero_defined 1
DATDEF struct mfile /*     */ mfile_zero;     /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */
DATDEF struct mfile_ops const mfile_zero_ops; /* ... */

/* Fallback files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_makeanon()' as replacement mappings
 * of the original file. */
DATDEF struct mfile /*     */ mfile_anon[BITSOF(void *)];
DATDEF struct mfile_ops const mfile_anon_ops[BITSOF(void *)];


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H */
