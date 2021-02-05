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

#include <bits/os/timespec.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#undef CONFIG_MFILE_LEGACY_VIO_OPS
#ifndef CONFIG_USE_NEW_FS
#if 1 /* TODO: Currently required for backwards compatibility to the old mman.
       * The plan is to eventually disable this option, and merge `inode_type'
       * with `mfile_ops', which should then contain a pointer for VIO operators.
       * With this option enabled, the old behavior is used, instead. */
#define CONFIG_MFILE_LEGACY_VIO_OPS
#endif
#endif /* !CONFIG_USE_NEW_FS */

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

/*
 * HINTS: Disallowing certain operations for `struct mfile' users:
 *
 * - MFILE_F_FIXEDFILESIZE:
 *    - mfile_truncate()   (throws: E_INVALID_ARGUMENT_CONTEXT_FIXED_LENGTH_FILE)
 *    - mfile_tailread()   (for offsets >= mf_filesize: blocks forever)
 *    - mfile_tailwrite()  (THROW(E_FSERROR_DISK_FULL))
 *    - mfile_read()       (for offsets >= mf_filesize: returns `0')
 *    - mfile_write()      (for offsets >= mf_filesize: THROW(E_FSERROR_DISK_FULL))
 *
 * - MFILE_F_READONLY:
 *    - mfile_tailwrite()  (THROW(E_FSERROR_READONLY))
 *    - mfile_write()      (THROW(E_FSERROR_READONLY))
 *    - mmap(SHARED|WRITE) (THROW(E_FSERROR_READONLY))
 *    - Note that `mfile_truncate()' is _not_ affected!
 *
 * - MFILE_F_DELETED
 *
 */


#ifdef CONFIG_USE_NEW_FS
/* Optional operators used when  */
struct mfile_stream_ops {

};
#endif /* CONFIG_USE_NEW_FS */

struct mfile_ops {
	/* [0..1] Finalize + free the given mem-file. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *mo_destroy)(struct mfile *__restrict self);

	/* [0..1] Construct a new given mem-part. When not implemented, use the default
	 *        mechanism for the creation of new mem-parts.
	 * This function is mainly intended to be used by `mfile_pyhs' in order to create
	 * custom, already-initialized mem-parts for use with a given physical location.
	 * NOTE: This function may assume that the given address range is aligned by `mf_part_amask'.
	 * The following fields should _NOT_ already be initialized by this
	 * function, and will unconditionally be initialized by the caller:
	 *  - mp_refcnt                      (Initialized to whatever is the correct value)
	 *  - mp_flags & MPART_F_GLOBAL_REF  (Set if `self' isn't anonymous)
	 *  - mp_flags & MPART_F_LOCKBIT     (Must not be set)
	 *  - mp_flags & MPART_F_CHANGED     (Must not be set)
	 *  - mp_flags & MPART_F_PERSISTENT  (Set if `self' isn't anonymous and has the `MFILE_F_PERSISTENT' flag set)
	 *  - mp_flags & MPART_F__RBRED      (Needed of the file-tree)
	 *  - mp_file                        (Set to `self' or `mfile_anon[*]')
	 *  - mp_copy                        (Initialized as empty)
	 *  - mp_share                       (Initialized as empty)
	 *  - mp_lockops                     (Initialized as empty)
	 *  - mp_allparts                    (The part (may be) added to the all-list only _after_ all other fields were initialized)
	 *  - mp_minaddr                     (Set to `minaddr' by the caller)
	 *  - mp_maxaddr                     (Set to `minaddr + num_bytes - 1' by the caller)
	 *  - mp_changed                     (Intentionally left uninitialized)
	 *  - mp_filent                      (Needed of the file-tree; set to indicate an anon-part if `self' was anonymous)
	 * As such, this function may only initialize:
	 *  - mp_flags & ...                 (All flags except for the above)
	 *  - mp_state                       (usually `MPART_ST_VOID' or `MPART_ST_MEM')
	 *  - mp_blkst_ptr / mp_blkst_inl    (Containing the fully initialized initial block-status bitset)
	 *  - mp_mem / mp_mem_sc / ...       (Containing the initial backing storage location; s.a. `mp_state')
	 *  - mp_meta                        (usually `NULL') */
	ATTR_RETNONNULL NONNULL((1)) REF struct mpart *
	(FCALL *mo_newpart)(struct mfile *__restrict self,
	                    PAGEDIR_PAGEALIGNED pos_t minaddr,
	                    PAGEDIR_PAGEALIGNED size_t num_bytes);

	/* [0..1] Load/initialize the given physical memory buffer (this is the read-from-disk callback)
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));
	 * @assume(addr + num_bytes <= self->mf_filesize);
	 * @assume(self->mf_trunclock != 0);
	 * @assume(num_bytes != 0);
	 * @assume(WRITABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));
	 * NOTE: WRITABLE_BUFFER_SIZE means that this function is allowed to write until the aligned
	 *       end of the last file-block when `num_bytes' isn't aligned by whole blocks, where
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */
	NONNULL((1)) void (KCALL *mo_loadblocks)(struct mfile *__restrict self, pos_t addr,
	                                         physaddr_t buf, size_t num_bytes);

	/* [0..1] Save/write-back the given physical memory buffer (this is the write-to-disk callback)
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));
	 * @assume(addr + num_bytes <= self->mf_filesize);
	 * @assume(self->mf_trunclock != 0);
	 * @assume(num_bytes != 0);
	 * @assume(READABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));
	 * NOTE: READABLE_BUFFER_SIZE means that this function is allowed to read until the aligned
	 *       end of the last file-block when `num_bytes' isn't aligned by whole blocks, where
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */
	NONNULL((1)) void (KCALL *mo_saveblocks)(struct mfile *__restrict self, pos_t addr,
	                                         physaddr_t buf, size_t num_bytes);

#ifdef CONFIG_USE_NEW_FS
	/* [0..1] Called after `MFILE_F_CHANGED' and/or `MFILE_F_ATTRCHANGED' becomes set.
	 * @param: what: Set of `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED' (never zero).
	 *               This argument specifies which of the changed-bits have been
	 *               set (atomically), meaning that these bits weren't set before,
	 *               but have become set just now. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *mo_changed)(struct mfile *__restrict self,
	                                uintptr_t what);
#else /* CONFIG_USE_NEW_FS */
	/* [0..1] Called the first time the `MPART_F_CHANGED' flag is set for `part'.
	 * WARNING: This function is called while a lock to `part' is held!
	 * NOTE: Not invoked if a new change part is created as the result
	 *       of an already-known-as-changed part being split. */
	NOBLOCK NONNULL((1, 2)) void
	/*NOTHROW*/ (FCALL *mo_changed)(struct mfile *__restrict self,
	                                struct mpart *__restrict part);
#endif /* !CONFIG_USE_NEW_FS */

#ifndef CONFIG_MFILE_LEGACY_VIO_OPS
	/* [0..1] VIO file operators. (when non-NULL, then this file is backed by VIO,
	 *        and the `mo_loadblocks' and `mo_saveblocks' operators are ignored) */
	struct vio_operators const *mo_vio;
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */

#ifdef CONFIG_USE_NEW_VM /* Hacky forward-compatibility... */
	/* [0..1] Optional operators for when read(2) or write(2) is used with
	 *        a file descriptor pointing to a mfile of this type.
	 * These callbacks are used by UVIO datablocks to implement the
	 * server/client architecture for user-space driven VIO emulation.
	 * They are also used to implement flexible-context files such as
	 * those found under `/proc' */
	WUNUSED NONNULL((1)) size_t
	(KCALL *mo_stream_read)(struct mfile *__restrict self,
	                        USER CHECKED void *dst,
	                        size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1)) size_t
	(KCALL *mo_stream_write)(struct mfile *__restrict self,
	                         USER CHECKED void const *src,
	                         size_t num_bytes, iomode_t mode) THROWS(...);
	/* [0..1] Same as above, but used when polling for data being available.
	 * When not implemented (i.e. when set to `NULL'), poll is implemented for
	 * the datablock through use of `rwlock_poll(read|write)(&self->db_lock)' */
	NONNULL((1)) void
	(KCALL *dt_handle_pollconnect)(struct mfile *__restrict self,
	                               poll_mode_t what) THROWS(...);
	WUNUSED NONNULL((1)) poll_mode_t
	(KCALL *dt_handle_polltest)(struct mfile *__restrict self,
	                            poll_mode_t what) THROWS(...);
#endif /* CONFIG_USE_NEW_VM */

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

#ifdef CONFIG_USE_NEW_FS
#define MFILE_F_NORMAL          0x0000 /* Normal flags. */
#ifndef CONFIG_NO_SMP
#define _MFILE_F_SMP_TSLOCK     0x0001 /* [lock(ATOMIC)] SMP-lock for TimeStamps (`mf_atime', `mf_mtime'). */
#endif /* !CONFIG_NO_SMP */
/*efine MFILE_F_                0x0002  * ... */
/*efine MFILE_F_                0x0004  * ... */
#define MFILE_F_CHANGED         0x0008 /* [lock(SET(ATOMIC), CLEAR(WEAK))]
                                        * This flag is set before `mo_changed()' is invoked, which also won't
                                        * be invoked again until this flag has been cleared, which is done
                                        * as part of a call to `mfile_sync()' */
#define MFILE_F_ATTRCHANGED     0x0010 /* [lock(SET(ATOMIC), CLEAR(WEAK))]
                                        * Indicates that attributes of this file (its size, etc.) have changed. */
#define MFILE_F_READONLY        0x0020 /* [lock(WRITE_ONCE)] Disallow `mfile_write()', as well as `PROT_WRITE|PROT_SHARED'
                                        * mappings. Attempting to do either will result in `E_FSERROR_READONLY' being thrown. */
#define MFILE_F_DELETED         0x0040 /* [lock(WRITE_ONCE)][const_if(MFILE_F_READONLY)] The file has been marked as
                                        * deleted. When this flag is set, new parts may be created with `mfile_anon[*]'
                                        * set for their pointed-to `mp_file' field. This flag also means that
                                        * `mfile_isanon(self)' and `mf_filesize == 0' will be the same sooner or later,
                                        * though this may not be the case yet, since file anonymization & all of that
                                        * jazz happens asynchronously through use of lockops!
                                        * Note that this flag implies `MFILE_F_READONLY|MFILE_F_FIXEDFILESIZE', except
                                        * that the delete-operation itself will eventually be allowed to set the file's
                                        * size to `0'. Once async deletion is complete, the file's part-tree and changed-
                                        * list will be set to MFILE_PARTS_ANONYMOUS, the file will have a zero of `0',
                                        * and all of its used-to-be parts will be anon, too. */
#define MFILE_F_PERSISTENT      0x0080 /* [const] Parts of this file should not be unloaded to free up memory.
                                        * When this flag is set, then newly created parts (if non-anonymous)
                                        * will be created with the `MPART_F_PERSISTENT' flag set.
                                        * This flag is used to implement ramfs-based filesystems, where it is
                                        * used to prevent files on such filesystem from being deleted when the
                                        * kernel tries to reclaim memory. */
#define MFILE_F_FIXEDFILESIZE   0x0100 /* [lock(WRITE_ONCE)] The size of this file cannot be altered.
                                        * Note that when using `mfile_write()' on a VIO-file, the call will
                                        * act as though this flag was always set, since it's impossible to
                                        * atomically modify the file's size while also invoking (possibly
                                        * blocking) VIO callbacks, without locking all other write-past-end
                                        * operations on the same file. Note however that you can still use
                                        * `mfile_truncate()' to change the size of a VIO-file, so-long as
                                        * it doesn't have this flag set! */
#define MFILE_F_NOATIME         0x0200 /* [lock(WRITE_ONCE && _MFILE_F_SMP_TSLOCK)] Don't modify the value of `mf_atime' */
#define MFILE_F_NOMTIME         0x0400 /* [lock(WRITE_ONCE && _MFILE_F_SMP_TSLOCK)] Don't modify the value of `mf_mtime' */
/*efine MFILE_F_                0x0800  * ... */
/*efine MFILE_F_                0x1000  * ... */
/*efine MFILE_F_                0x2000  * ... */
/*efine MFILE_F_                0x4000  * ... */
/*efine MFILE_F_                0x8000  * ... */
#endif /* CONFIG_USE_NEW_FS */

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
	struct mfile_lockop_slist   mf_lockops;    /* [0..n][lock(ATOMIC)] Chain of lock operations. */
	struct REF mpart_slist      mf_changed;    /* [0..n][lock(APPEND: ATOMIC,
	                                            *             CLEAR:  ATOMIC && mf_lock)]
	                                            * Chain of references to parts that contain unsaved changes.
	                                            * NOTE: Set to `MFILE_PARTS_ANONYMOUS' if changed parts should
	                                            *       always be ignored unconditionally, the same way they
	                                            *       would be when `mf_ops->mo_saveblocks' is `NULL'. */
	size_t                      mf_part_amask; /* [const] == MAX(PAGESIZE, 1 << mf_blockshift) - 1
	                                            * This field describes the minimum alignment of file positions
	                                            * described by parts, minus one (meaning it can be used as a
	                                            * mask) */
	unsigned int                mf_blockshift; /* [const] == log2(FILE_BLOCK_SIZE) */

	/* TODO: Change `mfile_makeanon_subrange()' to `mfile_truncate()' (which can
	 *       be used to dynamically alter the `mf_filesize' value of a given mem-file) */

#ifdef CONFIG_USE_NEW_FS
	uintptr_t                   mf_flags;      /* File flags (set of `MFILE_F_*') */
	WEAK size_t                 mf_trunclock;  /* [lock(INC(RDLOCK(mf_lock) || mpart_lock_acquired(ANY(mf_parts))),
	                                            *       DEC(ATOMIC))]
	                                            * Non-zero if `mf_filesize' must not be lowered. Incrementing this
	                                            * counter requires one to be holding a lock to one of the mem-
	                                            * parts of this file, or a lock to the file itself. However,
	                                            * decrementing it doesn't impose such a requirement. When this
	                                            * counter hits 0, then `mf_initdone' must be broadcast. */
	atomic64_t                  mf_filesize;   /* [lock(READ:      ATOMIC,
	                                            *       INCREMENT: mf_trunclock != 0 && ATOMIC,  // NOTE: `mf_trunclock' was incremented while holding `mf_lock'!
	                                            *                                                // By acquiring a write-lock to `mf_lock' and waiting for `mf_trunclock == 0',
	                                            *                                                // one must be able to prevent `mf_filesize' from changing at all!
	                                            *       DECREMENT: WRLOCK(mf_lock) && mf_trunclock == 0 &&
	                                            *                  mpart_lock_acquired(ALL(mf_parts)))]
	                                            * [const_if(MFILE_F_FIXEDFILESIZE || MFILE_F_DELETED)] // Also cannot be lowered when `mf_trunclock != 0'
	                                            * [valid_if(!mfile_isanon(self))] File size field.
	                                            * Attempting to construct new mem-parts above this address
	                                            * will fail and/or clamp the max accessible file size to
	                                            * the given address. Note however that in the case of a file
	                                            * that doesn't have the `MFILE_F_FIXEDFILESIZE' flag set, this
	                                            * values _can_ be increased by writing beyond the end of the
	                                            * file in a call to `mfile_write()'. Also note that whenever
	                                            * this value is increased, then the `mf_initdone' signal will
	                                            * be broadcast. */
	struct timespec             mf_atime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOATIME)][valid_if(!MFILE_F_DELETED)]
	                                            * Last-accessed timestamp. NOTE!!! Becomes invalid when `MFILE_F_DELETED' is set!
	                                            * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                            *      before proceeding to use the data you've just read! */
	struct timespec             mf_mtime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOMTIME)][valid_if(!MFILE_F_DELETED)]
	                                            * Last-modified timestamp. NOTE!!! Becomes invalid when `MFILE_F_DELETED' is set!
	                                            * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                            *      before proceeding to use the data you've just read! */
	struct timespec             mf_ctime;      /* [const][valid_if(!MFILE_F_DELETED)]
	                                            * Creation timestamp. NOTE!!! Becomes invalid when `MFILE_F_DELETED' is set!
	                                            * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                            *      before proceeding to use the data you've just read! */
#endif /* CONFIG_USE_NEW_FS */
};


#ifdef CONFIG_USE_NEW_FS
/* Increment or decrement the size-lock counter. In order to use these functions,
 * the caller must currently be holding a lock to `self->mf_lock', or at least one
 * of the parts found in the tree of `self->mf_parts'.
 * Alternatively, when `mfile_isanon(self)' is true, then no such requirements are
 * imposed, and use of these functions becomes optional. */
#define mfile_trunclock_inc(self) \
	__hybrid_atomic_inc((self)->mf_trunclock, __ATOMIC_ACQUIRE)
#define mfile_trunclock_dec(self)                                        \
	(__hybrid_atomic_decfetch((self)->mf_trunclock, __ATOMIC_RELEASE) || \
	 (sig_broadcast(&(self)->mf_initdone), 0))
#define mfile_trunclock_dec_nosignal(self) \
	__hybrid_atomic_decfetch((self)->mf_trunclock, __ATOMIC_RELEASE)

/* Indicate that attributes of the given mem-file (may) have changed. */
#define mfile_handle_attrchanged(self)                                                                        \
	((__hybrid_atomic_fetchor((self)->mf_flags, MFILE_F_ATTRCHANGED, __ATOMIC_SEQ_CST) & MFILE_F_ATTRCHANGED) \
	 ? ((self)->mf_ops->mo_changed ? (*self->mf_ops->mo_changed)(self, MFILE_F_ATTRCHANGED) : (void)0)        \
	 : (void)0)

#ifdef CONFIG_NO_SMP
#define mfile_tslock_tryacquire(self)   1
#define mfile_tslock_acquire_nopr(self) (void)0
#define mfile_tslock_release_nopr(self) (void)0
#else /* CONFIG_NO_SMP */
#define mfile_tslock_tryacquire(self)               \
	(!(__hybrid_atomic_fetchor((self)->mf_flags,    \
	                           _MFILE_F_SMP_TSLOCK, \
	                           __ATOMIC_ACQUIRE) &  \
	   _MFILE_F_SMP_TSLOCK))
#define mfile_tslock_acquire_nopr(self)        \
	do {                                       \
		while (!mfile_tslock_tryacquire(self)) \
			task_pause();                      \
	}	__WHILE0
#define mfile_tslock_release_nopr(self) \
	__hybrid_atomic_and((self)->mf_flags, ~_MFILE_F_SMP_TSLOCK, __ATOMIC_RELEASE)
#endif /* !CONFIG_NO_SMP */
#define mfile_tslock_acquire(self)                \
	do {                                          \
		pflag_t _mtsl_was = PREEMPTION_PUSHOFF(); \
		mfile_tslock_acquire_nopr(self)
#define mfile_tslock_release(self)       \
		mfile_tslock_release_nopr(self); \
	} __WHILE0
#endif /* CONFIG_USE_NEW_FS */

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


#ifdef CONFIG_USE_NEW_FS
/* Make the given file anonymous+deleted. What this means is that (in order):
 *  - The `MFILE_F_DELETED' flag is set for the file.
 *  - The file-fields of all mem-parts are altered to point
 *    at anonymous memory files. (s.a. `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' fields are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_filesize' field is set to `0'.
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted)
 *
 * Note that (with the exception of `MFILE_F_DELETED' being set, which is
 * always done synchronously), this function operates entirely asynchronously,
 * meaning that it uses lockops in order to wait for any locks it may need to
 * become available. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete)(struct mfile *__restrict self);
#else /* CONFIG_USE_NEW_FS */
/* Make the given file anonymous+deleted. What this means is that:
 *  - Existing mappings of all mem-parts are altered to point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered. (s.a. `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted) */
FUNDEF NONNULL((1)) void FCALL
mfile_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK);
#endif /* !CONFIG_USE_NEW_FS */


/* Split a potential part at `minaddr' and `maxaddr', and make
 * it so that all parts between that range are removed from the
 * part-tree of `self', by essentially anonymizing them.
 * This function can be used to implement `ftruncate(2)'
 *
 * NOTE: Unlike `mfile_delete()', this function doesn't mark
 *       the file itself as deleted, meaning that more parts
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


/* Check `self' for a known mem-part that contains `addr', and (if
 * found), return that part. Otherwise, construct a new part start
 * starts at `addr' and spans around `hint_bytes' bytes (less may
 * be returned if another part already exists that describes the
 * mapping above the requested location, and more may be returned
 * if a pre-existing part was spans beyond `addr +hint_bytes -1')
 *
 * Note that the caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(hint_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since.
 * @throw: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_MMAP_BEYOND_END_OF_FILE: ... */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t hint_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT, ...);

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this function is mainly used to allocate
 * parts for `mfile_ndef' and `mfile_zero' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


struct mfile_extendpart_data {
	PAGEDIR_PAGEALIGNED pos_t  mep_minaddr;  /* Base address of an unmapped range to fill by extending another part. */
	pos_t                      mep_maxaddr;  /* Last byte of the gap that should be filled. */
	int                        _placeholder; /* ... */
};
#define mfile_extendpart_data_init(self) ((self)->_placeholder = 0)
#define mfile_extendpart_data_fini(self) ((self)->_placeholder = 0)

/* While holding a read- or write-lock to `self', try to extend an
 * existing mem-part that borders against the given address range
 * in order to fill the specified gap.
 * This function assumes that:
 *  - @assume(mfile_lock_reading(self) || mfile_lock_writing(self));
 *  - @assume(data->mep_minaddr <= data->mep_maxaddr);
 *  - @assume(mfile_addr_aligned(self, data->mep_minaddr));
 *  - @assume(mfile_addr_aligned(self, data->mep_maxaddr + 1));
 *  - @assume(WAS_CALLED(mfile_extendpart_data_init(data)));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(mfile_addr_ceilalign(self, self->mf_filesize) >= data->mep_maxaddr + 1);
 *  - @assume(!mpart_tree_rlocate(self->mf_parts, data->mep_minaddr, data->mep_maxaddr));
 * Locking logic:
 *   in:                                         mfile_lock_reading(self) || mfile_lock_writing(self)
 *   return == *:                                mfile_lock_writing(self) && undefined(out(data)) &&
 *                                               mpart_lock_acquired(return)
 *   return == MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (mfile_lock_reading(self) || mfile_lock_writing(self)) &&
 *                                               undefined(out(data))
 *   return == MFILE_EXTENDPART_OR_UNLOCK_AGAIN: mfile_lock_end(self) && unlock()
 *   EXCEPT:                                     mfile_lock_end(self) && unlock()
 * @return: * : Success: A pointer to an extended mem-part that contains the entirety
 *                       of the address range originally specified in `data'. Note
 *                       that in this case, you're inheriting a lock to that part.
 *                       Note: In this case, this function also guaranties that the
 *                       returned part doesn't exist in SWAP, though it may still
 *                       not be allowed (i.e. it's state may be MPART_ST_VOID)
 * @return: MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (kind-of) success; the function was unable
 *                       to extend a pre-existing mem-part, but this is because there was
 *                       no such part to begin with: No existing part was neighboring, or
 *                       was even remotely close to the given address range, meaning that
 *                       extending such a part (if one even exists at all) would be less
 *                       efficient than just creating a new, separate part.
 * @return: MFILE_EXTENDPART_OR_UNLOCK_AGAIN: The lock to `self' (and `unlock') was lost.
 *                       Simply re-acquire those locks and try again. Note that in this
 *                       case, the caller should always acquire a write-lock to `self'! */
FUNDEF WUNUSED NONNULL((1, 2)) struct mpart *FCALL
mfile_extendpart_or_unlock(struct mfile *__restrict self,
                           struct mfile_extendpart_data *__restrict data,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#define MFILE_EXTENDPART_OR_UNLOCK_NOSIB ((REF struct mpart *)0)
#define MFILE_EXTENDPART_OR_UNLOCK_AGAIN ((REF struct mpart *)-1)


/* High-level wrapper for `mf_ops->mo_newpart' that automatically does
 * the right things when `mf_ops->mo_newpart' hasn't been defined.
 * This function doesn't do any further initialization that what is
 * already described by `mf_ops->mo_newpart' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *FCALL
_mfile_newpart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


/* Look at the neighbors of `part' and try to merge them with `part'. If
 * no neighbors exist, or if those neighbors are so far away that merging
 * with them wouldn't be efficient, then simply insert `part' as-is into
 * the given mem-file `self', before adding `part' to the global list of
 * parts (but only if it has the `MPART_F_GLOBAL_REF' flag set), and finally
 * releasing a lock to `self', as well as re-returning a pointer to the
 * given part. - For this purpose, the caller must initialize the `part'
 * reference counter of `part' as `MPART_F_GLOBAL_REF ? 2 : 1'
 * If the `MPART_F_CHANGED' flag is set, the given part, or the combination
 * of it and the to-be returned part will be added to the changed-part list.
 * However, if this is done, the caller is responsible for updating the file,
 * such that `MFILE_F_CHANGED' is set, and `mo_changed()' is invoked.
 * If merging was done, returning a reference to the new part against within
 * the given `part' was merged (i.e. the one that was left apart of the
 * mem-part tree of `self')
 * This function assumes that:
 *  - @assume(mfile_lock_writing(self));
 *  - @assume(mfile_addr_aligned(self, part->mp_minaddr));
 *  - @assume(mfile_addr_aligned(self, part->mp_maxaddr + 1));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(LIST_EMPTY(&part->mp_copy));
 *  - @assume(LIST_EMPTY(&part->mp_share));
 *  - @assume(UNINITIALIZED(&part->mp_allparts));
 *  - @assume(part->mp_refcnt == 1 + ((part->mp_flags & MPART_F_GLOBAL_REF) != 0) + ((part->mp_flags & MPART_F_CHANGED) != 0));
 *  - @assume(part->mp_file == self);
 *  - @assume(INITIALIZED(part->mp_*)); // All other fields...
 * @return: NULL: A pre-existing part overlaps with the address range of `part':
 *                mpart_tree_rlocate(self->mf_parts, part->mp_minaddr, part->mp_maxaddr) != NULL
 * @return: * :   A reference to a part that (at one point) contained a super-set
 *                of the address range described by the given `part'. */
FUNDEF WUNUSED NONNULL((1)) REF struct mpart *FCALL
mfile_insert_and_merge_part_and_unlock(struct mfile *__restrict self,
                                       /*inherit(on_success)*/ struct mpart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);








/* Read/write raw data to/from a given mem-file. */
#ifdef CONFIG_USE_NEW_FS
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_tailread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_tailread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_tailwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_tailwrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_tailwritev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_tailwritev_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the above, but these use an intermediate (stack) buffer for transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
FUNDEF NONNULL((1)) size_t KCALL _mfile_buffered_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL _mfile_buffered_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL _mfile_buffered_tailwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL _mfile_buffered_readv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL _mfile_buffered_writev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL _mfile_buffered_tailwritev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
#endif /* CONFIG_USE_NEW_FS */

/* Helpers for directly reading to/from VIO space. */
#ifdef LIBVIO_CONFIG_ENABLED
FUNDEF NONNULL((1)) void KCALL mfile_vioread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_viowrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vioread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_viowrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_vioreadv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_viowritev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_vioreadv_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_viowritev_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
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
 * As such, these files are used by `mfile_delete()' as replacement mappings
 * of the original file. */
DATDEF struct mfile /*     */ mfile_anon[BITSOF(void *)];
DATDEF struct mfile_ops const mfile_anon_ops[BITSOF(void *)];


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H */
