/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os"); // Optimize this file for size
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C 1
#define __WANT_DRIVER__d_internals
#define __WANT_MPART__mp_dead
#define __WANT_MFILE__mf_deadnod
#define __WANT_PATH__p_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/pty.h>
#include <dev/tty.h>
#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/fifonode.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mpart.h>
#include <sched/enum.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

/**/
#include "module-userelf.h" /* CONFIG_HAVE_USERELF_MODULES */

DECL_BEGIN

typedef NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
/*NOTHROW*/ (KCALL *PSYSTEMCC)(struct ccinfo *__restrict info);

#define DOCC(expr)               \
	do {                         \
		expr;                    \
		if (ccinfo_isdone(info)) \
			return;              \
	}	__WHILE0



/* Cache-clear functions from around the kernel core... */
INTDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_async_aio_handles)(struct ccinfo *__restrict info);
INTDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_module_section_cache)(struct ccinfo *__restrict info);
#ifdef CONFIG_HAVE_USERELF_MODULES
INTDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_rtld_fsfile)(struct ccinfo *__restrict info);
INTDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_mman_module_cache)(struct mman *__restrict self,
                                           struct ccinfo *__restrict info);
#endif /* CONFIG_HAVE_USERELF_MODULES */
INTDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_slab_prealloc)(struct ccinfo *__restrict info);
/*...*/




/************************************************************************/
/* DRIVER                                                               */
/************************************************************************/
INTDEF ATTR_USED NOBLOCK NONNULL((1)) size_t /* from "driver.c" */
NOTHROW(FCALL dfc_freetree)(struct driver_fde_cache *__restrict tree);
PRIVATE ATTR_USED NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_driver_fdecache)(struct driver *__restrict self,
                                         struct ccinfo *__restrict info) {
	struct driver_fde_cache *tree;
	if (!driver_eh_frame_cache_trywrite(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!driver_eh_frame_cache_write_nx(self))
			return;
	}
	tree = self->d_eh_frame_cache;
	self->d_eh_frame_cache = NULL;
	driver_eh_frame_cache_endwrite(self);
	if (tree != NULL)
		ccinfo_account(info, dfc_freetree(tree));
}

/* Clear caches associated with a given driver. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perdriver)(struct driver *__restrict self,
                                   struct ccinfo *__restrict info) {
	PSYSTEMCC func;
	DOCC(system_cc_driver_fdecache(self, info));

	/* Drivers are allowed to define custom clear-cache functions. */
	*(void **)&func = driver_dlsym_local(self, "drv_cc");
	if (func != NULL)
		DOCC((*func)(info));
}

/* Clear caches defined by drivers. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_drivers)(struct ccinfo *__restrict info) {
	size_t i;
	REF struct driver_loadlist *ll;
	/* Invoke the `drv_cc()' function of every loaded driver. */
	ll = get_driver_loadlist();
	for (i = 0; i < ll->dll_count; ++i) {
		REF struct driver *drv;
		drv = ll->dll_drivers[i];
		if (!tryincref(drv))
			continue; /* Dead driver... */
		system_cc_perdriver(drv, info);
		if (ccinfo_isdone(info))
			break;
	}
	if (ATOMIC_DECFETCH(ll->dll_refcnt) == 0) {
		ccinfo_account(info, offsetof(struct driver_loadlist, dll_drivers));
		ccinfo_account(info, ll->dll_count * sizeof(REF struct driver *));
		driver_loadlist_destroy(ll);
	}
}




/************************************************************************/
/* MMAN                                                                 */
/************************************************************************/

/* Clear per-mman caches. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_permman)(struct mman *__restrict self,
                                 struct ccinfo *__restrict info) {
#ifdef CONFIG_HAVE_USERELF_MODULES
	system_cc_mman_module_cache(self, info);
#endif /* CONFIG_HAVE_USERELF_MODULES */

	(void)self;
	(void)info;
	COMPILER_IMPURE();
}




/************************************************************************/
/* FS                                                                   */
/************************************************************************/

#ifndef __path_slist_defined
#define __path_slist_defined
SLIST_HEAD(path_slist, path);
#endif /* !__path_slist_defined */

/* Clear VFS recently-used-paths cache. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_vfs_recent_paths)(struct vfs *__restrict self,
                                          struct ccinfo *__restrict info) {
	struct path_slist deadpaths;
	struct path *iter;
	if (vfs_recentlock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!vfs_recentlock_acquire_nx(self))
			return;
	}
	SLIST_INIT(&deadpaths);

	/* We only remove paths  that are not externally  referenced.
	 * We could just remove  everything, but doing that  wouldn't
	 * do us any good since we can only report memory having been
	 * freed if we actually managed to destroy a path. */
	TAILQ_FOREACH_SAFE (iter, &self->vf_recent, p_recent) {
		if (!ATOMIC_CMPXCH(iter->p_refcnt, 1, 0))
			continue; /* Remove from the recent cache wouldn't kill this one... */

		/* Remove from the recent cache. */
		assert(self->vf_recentcnt != 0);
		TAILQ_REMOVE(&self->vf_recent, iter, p_recent);
		--self->vf_recentcnt;
		SLIST_INSERT(&deadpaths, iter, _p_dead);
		ccinfo_account(info, sizeof(struct path));
		if (ccinfo_isdone(info))
			break;
	}
	vfs_recentlock_release(self);

	/* Destroy dead path objects. */
	while (!SLIST_EMPTY(&deadpaths)) {
		iter = SLIST_FIRST(&deadpaths);
		SLIST_REMOVE_HEAD(&deadpaths, _p_dead);
		path_destroy(iter);
	}
}

/* Clear per-vfs caches. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_pervfs)(struct vfs *__restrict self,
                                struct ccinfo *__restrict info) {
	DOCC(system_cc_vfs_recent_paths(self, info));
}

/* Clear per-fs caches. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_perfs)(struct fs *__restrict self,
                               struct ccinfo *__restrict info) {
	DOCC(system_cc_pervfs(self->fs_vfs, info));
}




/************************************************************************/
/* THREAD                                                               */
/************************************************************************/

/* Clear per-thread caches. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(FCALL system_cc_pertask)(struct task *__restrict self,
                                 struct ccinfo *__restrict info) {
	/* Clear per-mman caches. */
	{
		REF struct mman *threadmm;
		threadmm = task_getmman(self);
		system_cc_permman(threadmm, info);
		if (ATOMIC_DECFETCH(threadmm->mm_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct mman));
			mman_destroy(threadmm);
		}
	}
	if (ccinfo_isdone(info))
		return;

	/* Clear per-fs caches. */
	if (ATOMIC_READ(FORTASK(self, this_fs)) != NULL) { /* May be NULL for kernel threads... */
		REF struct fs *threadfs;
		threadfs = task_getfs(self);
		system_cc_perfs(threadfs, info);
		if (ATOMIC_DECFETCH(threadfs->fs_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fs));
			fs_destroy(threadfs);
		}
	}
	if (ccinfo_isdone(info))
		return;

	/* TODO: There are probably more per-task things we could try to do. */
}

PRIVATE NOBLOCK ssize_t
NOTHROW(KCALL system_cc_pertask_cb)(void *arg,
                                    struct task *thread,
                                    struct taskpid *UNUSED(pid)) {
	if (thread) {
		struct ccinfo *info = (struct ccinfo *)arg;
		system_cc_pertask(thread, info);
		if (ccinfo_isdone(info))
			return -1; /* Stop enumeration */
	}
	return 0;
}


/* Enumerate threads and call `system_cc_pertask()'. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_threads)(struct ccinfo *__restrict info) {
	if (ccinfo_noblock(info)) {
		/* Not allowed to block -> can enumerate threads using the non-blocking method. */
		task_enum_all_nb(&system_cc_pertask_cb, NULL);
	} else {
		gfp_t saved_gfp;
		/* TODO: do  this  better (to  be precise:  in a  way that  doesn't require
		 *       `GFP_ATOMIC' to be set when doing per-task cache-clear operations)
		 * Solution: It doesn't matter if we enumerate some thread more than once,
		 *           or even if we accidentally skip one of the threads. The  only
		 *           thing that _does_ matter is  that we terminate in  guarantied
		 *           finite time, and do our best to hit every thread out there. */
		saved_gfp = info->ci_gfp;
		info->ci_gfp |= GFP_ATOMIC;
		task_enum_all_nb(&system_cc_pertask_cb, info);
		info->ci_gfp = saved_gfp;
	}
}




/************************************************************************/
/* HEAP                                                                 */
/************************************************************************/

/* Trim the given heap. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_heap)(struct heap *__restrict self,
                              struct ccinfo *__restrict info) {
	ccinfo_account(info, heap_trim(self, 0, info->ci_gfp));
}

#ifdef CONFIG_TRACE_MALLOC
INTDEF ATTR_WEAK struct heap trace_heap;
#endif /* CONFIG_TRACE_MALLOC */


/* Trim system heaps. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_heaps)(struct ccinfo *__restrict info) {
	size_t i;
	for (i = 0; i < __GFP_HEAPCOUNT; ++i)
		DOCC(system_cc_heap(&kernel_heaps[i], info));
#ifdef CONFIG_TRACE_MALLOC
	if (&trace_heap != NULL)
		DOCC(system_cc_heap(&trace_heap, info));
#endif /* CONFIG_TRACE_MALLOC */
}




/************************************************************************/
/* FILE/FILESYSTEM CACHES (including preloaded file data!)              */
/************************************************************************/

/* Clear unreferenced (cached) mem-parts from the global part list. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_allparts_unload)(struct ccinfo *__restrict info) {
	struct mpart *iter;
	struct mpart_slist deadlist;
	SLIST_INIT(&deadlist);
again:
	if (!mpart_all_tryacquire()) {
		if (ccinfo_noblock(info))
			goto done;
		if (!mpart_all_acquire_nx())
			goto done;
	}

	/* Enumerate all mem-parts. */
	/* TODO: Would be better to enumerate from least-recent to most-recent
	 *       Though for this, we should probably chance the list type from
	 *       `LIST_*' to `TAILQ_*' (which has a O(1) *_LAST operation). */
	LIST_FOREACH_SAFE (iter, &mpart_all_list, mp_allparts) {
		if (!(iter->mp_flags & MPART_F_GLOBAL_REF))
			continue; /* Can't be decref'd */
		if (ATOMIC_READ(iter->mp_refcnt) != 1)
			continue; /* External references exist, or already destroyed. */

		/* Try to unload this mem-part. */
		if (!mpart_lock_tryacquire(iter)) {
			bool waitfor_ok;
			if (!tryincref(iter))
				continue;
			mpart_all_release();
			waitfor_ok = mpart_lock_waitfor_nx(iter);
			if (ATOMIC_DECFETCH(iter->mp_refcnt) == 0) {
				ccinfo_account(info, sizeof(struct mpart));
				SLIST_INSERT(&deadlist, iter, _mp_dead);
			}
			if (!waitfor_ok)
				goto done;
			if (ccinfo_isdone(info))
				goto done;
			goto again;
		}
		if (!(ATOMIC_FETCHAND(iter->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)) /* Inherit reference */
			goto part_not_unloaded;
		if (!ATOMIC_CMPXCH(iter->mp_refcnt, 1, 0)) {
			if (!(ATOMIC_FETCHOR(iter->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)) /* Inherit reference */
				goto part_not_unloaded;
			/* Someone else set the GLOBAL_REF bit in the mean time?
			 * Anyways: since they did, they're would have had to incref() the part
			 *          to do so, so we have to decref() it since we were unable to
			 *          have the part re-inherit its original global reference. */
			if (ATOMIC_FETCHDEC(iter->mp_refcnt) != 0)
				goto part_not_unloaded;
		}
		/* Part got destroyed! */
		assert(!(ATOMIC_READ(iter->mp_flags) & MPART_F_GLOBAL_REF));
		SLIST_INSERT(&deadlist, iter, _mp_dead);
		ccinfo_account(info, sizeof(struct mpart));
		if (ccinfo_isdone(info))
			break;
		continue;
part_not_unloaded:
		mpart_lock_release(iter);
	}

	mpart_all_release();

	/* Properly destroy any dead mem-parts. */
done:
	while (!SLIST_EMPTY(&deadlist)) {
		iter = SLIST_FIRST(&deadlist);
		SLIST_REMOVE_HEAD(&deadlist, _mp_dead);
		mpart_destroy(iter);
	}
}


#ifndef __fnode_slist_defined
#define __fnode_slist_defined
SLIST_HEAD(fnode_slist, fnode);
#endif /* !__fnode_slist_defined */

/* Clear unreferenced (cached) files nodes from the global file-node-list. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_allnodes_unload)(struct ccinfo *__restrict info) {
	struct fnode *iter;
	struct fnode_slist deadlist;
	SLIST_INIT(&deadlist);
again:
	if (!fallnodes_tryacquire()) {
		if (ccinfo_noblock(info))
			goto done;
		if (!fallnodes_acquire_nx())
			goto done;
	}

	/* Enumerate all file nodes. */
	/* TODO: Would be better to enumerate from least-recent to most-recent
	 *       Though for this, we should probably chance the list type from
	 *       `LIST_*' to `TAILQ_*' (which has a O(1) *_LAST operation). */
	LIST_FOREACH_SAFE (iter, &fallnodes_list, fn_allnodes) {
		if (!(iter->mf_flags & MFILE_FN_GLOBAL_REF))
			continue; /* Can't be decref'd */
		if (ATOMIC_READ(iter->mf_refcnt) != 1)
			continue; /* External references exist, or already destroyed. */

		/* Try to unload this file. */
		if (!mfile_lock_trywrite(iter)) {
			bool waitfor_ok;
			if (!tryincref(iter))
				continue;
			mpart_all_release();
			waitfor_ok = mfile_lock_waitwrite_nx(iter);
			if (ATOMIC_DECFETCH(iter->mf_refcnt) == 0) {
				ccinfo_account(info, sizeof(struct mfile));
				SLIST_INSERT(&deadlist, iter, _mf_deadnod);
			}
			if (!waitfor_ok)
				goto done;
			if (ccinfo_isdone(info))
				goto done;
			goto again;
		}
		mfile_tslock_acquire(iter);
		if (!(ATOMIC_FETCHAND(iter->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)) { /* inherit reference */
			mfile_tslock_release_br(iter);
			mfile_lock_endwrite(iter);
			continue;
		}
		if (!ATOMIC_CMPXCH(iter->mf_refcnt, 1, 0)) {
			if (!(ATOMIC_FETCHOR(iter->mf_flags, MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)) { /* inherit reference */
				mfile_tslock_release_br(iter);
				mfile_lock_endwrite(iter);
				continue;
			}
			if (ATOMIC_DECFETCH(iter->mf_refcnt) != 0) {
				mfile_tslock_release_br(iter);
				mfile_lock_endwrite(iter);
				continue;
			}
		}

		/* Yes: must destroy this file. */
		mfile_tslock_release_pronly(iter);
		SLIST_INSERT(&deadlist, iter, _mf_deadnod);
		ccinfo_account(info, sizeof(struct mfile));
		if (ccinfo_isdone(info))
			break;
	}
	fallnodes_release();

	/* Properly destroy any dead files. */
done:
	while (!SLIST_EMPTY(&deadlist)) {
		iter = SLIST_FIRST(&deadlist);
		SLIST_REMOVE_HEAD(&deadlist, _mf_deadnod);
		mfile_destroy(iter);
	}
}


/* Free unused space from `self'. */
PUBLIC NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_ringbuffer)(struct ringbuffer *__restrict self,
                                    struct ccinfo *__restrict info) {
	if (!ringbuffer_lock_trywrite(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!ringbuffer_lock_write_nx(self))
			return;
	}
	if (self->rb_avail < self->rb_size) {
		if (self->rb_avail != 0) {
			heapptr_t newbuf;
			/* If necessary, defragment the buffer. */
			if (self->rb_rptr) {
				do {
					/* Shift buffer space so that all  data is stored at the  start,
					 * which in turn will allow us to realloc the buffer as a whole. */
					byte_t temp;
					temp = self->rb_data[0];
					memmovedown(self->rb_data,
					            self->rb_data + 1,
					            self->rb_size - 1);
					self->rb_data[self->rb_size - 1] = temp;
					--self->rb_rptr;
				} while (self->rb_rptr);
			}
			self->rb_rdtot = 0;

			/* Resize the buffer. */
			newbuf = heap_realloc_nx(&kernel_default_heap,
			                          self->rb_data,
			                          self->rb_size,
			                          self->rb_avail,
			                          GFP_ATOMIC | info->ci_gfp,
			                          GFP_NORMAL);
			if likely(heapptr_getsiz(newbuf) != 0) {
				assert(heapptr_getsiz(newbuf) >= self->rb_avail);
				if (self->rb_size > heapptr_getsiz(newbuf))
					ccinfo_account(info, self->rb_size - heapptr_getsiz(newbuf));
				self->rb_data = (byte_t *)heapptr_getptr(newbuf);
				self->rb_size = heapptr_getsiz(newbuf);
			}
		} else /*if (self->rb_size != 0)*/ {
			byte_t *buf_data;
			size_t buf_size;
			/* Free an unused buffer */
			buf_data       = self->rb_data;
			buf_size       = self->rb_size;
			self->rb_data  = NULL;
			self->rb_size  = 0;
			self->rb_rptr  = 0;
			self->rb_rdtot = 0;
			ringbuffer_lock_endwrite(self);

			/* free the buffer as a whole. */
			heap_free(&kernel_default_heap, buf_data, buf_size, GFP_NORMAL);
			ccinfo_account(info, buf_size);
			return;
		}
	}
	ringbuffer_lock_endwrite(self);
}

/* Free unused space from `self'. */
PUBLIC NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_linebuffer)(struct linebuffer *__restrict self,
                                    struct ccinfo *__restrict info) {
	if (!linebuffer_lock_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!linebuffer_lock_acquire_nx(self))
			return;
	}
	if (self->lb_line.lc_size == 0) {
		struct linecapture oldline;
		oldline                = self->lb_line;
		self->lb_line.lc_base  = NULL;
		self->lb_line.lc_alloc = 0;
		linebuffer_lock_release(self);
		if (oldline.lc_alloc != 0) {
			ccinfo_account(info, oldline.lc_alloc);
			linecapture_fini(&oldline);
		}
		return;
	} else if (self->lb_line.lc_size < self->lb_line.lc_alloc) {
		heapptr_t newline;
		/* Truncate buffer. */
		newline = heap_realloc_nx(&kernel_default_heap,
		                          self->lb_line.lc_base,
		                          self->lb_line.lc_alloc,
		                          self->lb_line.lc_size,
		                          GFP_ATOMIC | info->ci_gfp,
		                          GFP_NORMAL);
		if (heapptr_getsiz(newline) != 0) {
			if (self->lb_line.lc_alloc > heapptr_getsiz(newline))
				ccinfo_account(info, self->lb_line.lc_alloc - heapptr_getsiz(newline));
			self->lb_line.lc_base  = (byte_t *)heapptr_getptr(newline);
			self->lb_line.lc_alloc = heapptr_getsiz(newline);
		}
	}
	linebuffer_lock_release(self);
}


/* Invoke cache-clear callbacks for the given file-node. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perfnode)(struct fnode *__restrict self,
                                  struct ccinfo *__restrict info) {
	struct mfile_stream_ops const *ops;
	ops = self->mf_ops->mo_stream;
	if (ops && ops->mso_cc)
		DOCC((*ops->mso_cc)(self, info));
	if (fnode_isfifo(self)) {
		/* In this case, we can clear  */
		struct ffifonode *me = fnode_asfifo(self);
		DOCC(system_cc_ringbuffer(&me->ff_buffer, info));
	}
	if (fnode_istty(self)) {
		struct ttydev *me = fnode_astty(self);
		DOCC(system_cc_ringbuffer(&me->t_term.t_ibuf, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_canon, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_opend, info));
		DOCC(system_cc_linebuffer(&me->t_term.t_ipend, info));
		if (ttydev_isptyslave(me)) {
			struct ptyslave *ps = ttydev_asptyslave(me);
			DOCC(system_cc_ringbuffer(&ps->ps_obuf, info));
		}
	}
}


/* Invoke cache-clear callbacks for all file-nodes. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_allnodes)(struct ccinfo *__restrict info) {
	REF struct fnode *node;
	REF struct fnode *prev = NULL;
	size_t index           = 0;
	if (!fallnodes_tryacquire()) {
		if (ccinfo_noblock(info))
			return;
		if (!fallnodes_acquire_nx())
			return;
	}
	node = LIST_FIRST(&fallnodes_list);
	for (;;) {
		REF struct fnode *next;
		while (node && !tryincref(node))
			node = LIST_NEXT(node, fn_allnodes);
		fallnodes_release();
		if (prev && ATOMIC_DECFETCH(prev->mf_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fnode));
			mfile_destroy(prev);
		}
		if (!node)
			break;
		system_cc_perfnode(node, info);
		if (ccinfo_isdone(info))
			break;
		prev = node;
		if (!fallnodes_tryacquire()) {
			if (ccinfo_noblock(info))
				return;
			if (!fallnodes_acquire_nx())
				return;
		}
		if (!LIST_ISBOUND(node, fn_allnodes)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			node = LIST_FIRST(&fallnodes_list);
			for (i = 0; node && i < index; ++i) {
				node = LIST_NEXT(node, fn_allnodes);
			}
			if (!node) {
				fallnodes_release();
				break;
			}
		}
		next = LIST_NEXT(node, fn_allnodes);
		node = next;
		++index;
	}
	if (node && ATOMIC_DECFETCH(node->mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct fnode));
		mfile_destroy(node);
	}
}


/* Invoke cache-clear callbacks for the given superblock. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_persuper)(struct fsuper *__restrict self,
                                  struct ccinfo *__restrict info) {
	system_cc_perfnode(&self->fs_root, info);
}


/* Invoke cache-clear callbacks for all superblocks. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_allsuper)(struct ccinfo *__restrict info) {
	REF struct fsuper *super;
	REF struct fsuper *prev = NULL;
	size_t index            = 0;
	if (!fallsuper_tryacquire()) {
		if (ccinfo_noblock(info))
			return;
		if (!fallsuper_acquire_nx())
			return;
	}
	super = LIST_FIRST(&fallsuper_list);
	for (;;) {
		REF struct fsuper *next;
		while (super && !tryincref(super))
			super = LIST_NEXT(super, fs_root.fn_allsuper);
		fallsuper_release();
		if (prev && ATOMIC_DECFETCH(prev->fs_root.mf_refcnt) == 0) {
			ccinfo_account(info, sizeof(struct fsuper));
			mfile_destroy(&prev->fs_root);
		}
		if (!super)
			break;
		system_cc_persuper(super, info);
		if (ccinfo_isdone(info))
			break;
		prev = super;
		if (!fallsuper_tryacquire()) {
			if (ccinfo_noblock(info))
				return;
			if (!fallsuper_acquire_nx())
				return;
		}
		if (!LIST_ISBOUND(super, fs_root.fn_allsuper)) {
			/* Find  the `index'th super in the global list.
			 * This is not failsafe (elements before `super'
			 * may have been removed, so `index' may not  be
			 * correct), but it's better than nothing. */
			size_t i;
			super = LIST_FIRST(&fallsuper_list);
			for (i = 0; super && i < index; ++i) {
				super = LIST_NEXT(super, fs_root.fn_allsuper);
			}
			if (!super) {
				fallsuper_release();
				break;
			}
		}
		next = LIST_NEXT(super, fs_root.fn_allsuper);
		super = next;
		++index;
	}
	if (super && ATOMIC_DECFETCH(super->fs_root.mf_refcnt) == 0) {
		ccinfo_account(info, sizeof(struct fsuper));
		mfile_destroy(&super->fs_root);
	}
}





/* Clear all system caches according to `info'. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(FCALL system_cc_impl)(struct ccinfo *__restrict info) {
	DOCC(system_cc_drivers(info));               /* Invoke clear-cache operators from drivers */
	DOCC(system_cc_threads(info));               /* Clear caches relating to per-thread fields */
	DOCC(system_cc_async_aio_handles(info));     /* ... */
	DOCC(system_cc_allparts_unload(info));       /* Unload cached, but unused mem-parts */
	DOCC(system_cc_allnodes_unload(info));       /* Unload cached, but unused files */
	DOCC(system_cc_allnodes(info));              /* Invoke the clear-cache operator for all files */
	DOCC(system_cc_allsuper(info));              /* Invoke the clear-cache operator for all superblocks */
	DOCC(system_cc_permman(&mman_kernel, info)); /* In case more can be done now... */
	DOCC(system_cc_perfs(&fs_kernel, info));     /* In case not done already... */
	DOCC(system_cc_module_section_cache(info));  /* Clear pre-loaded module sections (e.g. .debug_info, etc...) */
#ifdef CONFIG_HAVE_USERELF_MODULES
	DOCC(system_cc_rtld_fsfile(info));
#endif /* CONFIG_HAVE_USERELF_MODULES */
	DOCC(system_cc_slab_prealloc(info));
	DOCC(system_cc_heaps(info));

	/* TODO: Clear unused buffer space from every HANDLE_TYPE_PIPE(|_READER|_WRITER)
	 *       - Find these by enumerating thread->handles */

	/* TODO: There a couple more things we can do to free up physical memory:
	 *  - We're  already unloading cached files and file-parts, but we can even
	 *    unload file parts that are currently in use (so-long as they  haven't
	 *    been modified). This can be done by changing a loaded, but unmodified
	 *    mpart back to MPART_ST_VOID
	 *  - We can  also do  `pagedir_unmap_userspace()' for  every user-space  mman
	 *    out there, and let mappings re-populate themselves upon the next access.
	 */

	if (!(info->ci_gfp & GFP_NOSWAP)) {
		/* Eh? Eeehhh?? What about it?
		 * Yes: swap off-loading will go here!
		 * And no: aside from skipping this part when GFP_ATOMIC is given, there
		 *         is no way around dealing with swap in a non-blocking context,
		 *         given that you can get here from: `kmalloc_nx(GFP_ATOMIC)'. */
	}
}







/************************************************************************/
/* High-level wrappers                                                  */
/************************************************************************/

/* [lock(ATOMIC)][const_if(cc_inside == 0)]
 * Current system cache version. */
PRIVATE unsigned int cc_version = 0;

/* [lock(ATOMIC)] # of threads currently clearing caches. */
PRIVATE uintptr_t cc_inside = 0;

/* Max # of attempts before unconditional give-up. ("/proc/kos/cc-max-attempts") */
PUBLIC ATTR_READMOSTLY unsigned int system_cc_maxattempts = 64;


/* Clear global system caches.
 * @param: info: [in|out] Specification on how caches should be cleared.
 * @return: true:  At least something (may) have become available
 *                 since the last time you tried to clear caches.
 * @return: false: Nothing could be cleared :( */
PUBLIC NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) bool
NOTHROW(FCALL system_cc)(struct ccinfo *__restrict info) {
	unsigned int version;
	uintptr_t inside;
	info->ci_bytes = 0;

	/* Deal with the special case of a zero-request
	 * -> In this case, we request that at least 1 byte be freed. */
	if unlikely(info->ci_minbytes == 0)
		info->ci_minbytes = 1;

	/* Check if we're supposed to give up */
	if (info->ci_attempt == (unsigned int)-1) {
		/* Special indicator for infinite attempts. */
	} else {
		if (info->ci_attempt >= system_cc_maxattempts)
			return false; /* D:  -- Oh no! */
		++info->ci_attempt;
	}

	/* Start out by trying to clear system caches ourself. */
	ATOMIC_INC(cc_inside);
	system_cc_impl(info);

	/* Check if we already managed to release some memory */
	if (info->ci_bytes != 0) {
		/* Since something  was cleared,  indicate
		 * that by incrementing the cache version. */
		info->ci_version = ATOMIC_FETCHINC(cc_version);
		ATOMIC_DEC(cc_inside);
		return true;
	}
	version = ATOMIC_READ(cc_version);
	inside  = ATOMIC_DECFETCH(cc_inside);

	/* If other threads are clearing caches, we try to yield to them. */
	if (inside != 0) {
		unsigned int n;
		for (n = 0; n < 256; ++n) {
			unsigned int yield_error;
			yield_error = task_tryyield_or_pause();
			if (ATOMIC_READ(cc_inside) < inside)
				break;
			if (yield_error != TASK_TRYYIELD_SUCCESS)
				break; /* Cannot yield... */
		}
		return true;
	}

	/* Fix zero-version (which is used to indicate the first cc-attempt) */
	if (version == 0) {
		ATOMIC_INC(cc_inside);
		version = ATOMIC_INCFETCH(cc_version);
		ATOMIC_DEC(cc_inside);
	}

	/* If the cache version changed since the
	 * last clear-attempt, indicate  success. */
	if (info->ci_version != version) {
		info->ci_version = version;
		return true;
	}

	/* Looks like there's nothing we can really do: no other thread  is
	 * clearing caches, and nothing became free since the last time our
	 * caller tried to clear caches.
	 * -> Memory just can't be forced to become available... */
	return false;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_CC_C */
