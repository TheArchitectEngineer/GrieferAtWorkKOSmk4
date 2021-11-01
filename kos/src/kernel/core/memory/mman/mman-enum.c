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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically  re-
 * assemble  memory mappings that  had previously been  split into multiple nodes,
 * such that adjacent  `struct mnode's that describe  a contiguous memory  mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback  that  should  be  invoked for  every  mapped  memory  region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The  sum of return  values returned by this  callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will  cause enumeration to  halt immediately, and that  same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated  in strictly ascending order, and  that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes  place, the `mmi_min' of all  future
 *                       mappings will always be `> mmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap  with `enum_minaddr ... enum_maxaddr'  will be  enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
FUNDEF BLOCKING_IF(BLOCKING(cb)) NONNULL((1, 2)) ssize_t KCALL
mman_enum(struct mman *__restrict self, mman_enum_callback_t cb, void *arg,
          UNCHECKED void *enum_minaddr, UNCHECKED void *enum_maxaddr) {
	ssize_t temp, result = 0;
	struct mmapinfo mi;
	size_t num_nodes = 0;
	while (enum_minaddr <= enum_maxaddr) {
		struct mnode_tree_minmax mima;
		struct mnode *node;
		struct mpart *part;
again_lookup_node:
		mi.mmi_index = num_nodes++;
#ifdef CONFIG_HAVE_DEBUGGER
		if unlikely(dbg_active) {
			/* Do everything while ignoring all of the locks (or refs).
			 *
			 * The debugger uses  this function for  `lsmm', and  yes:
			 * by not acquiring  locks, there is  a chance that  we'll
			 * crash because mappings may be in an inconsistent state.
			 *
			 * But  if  we did  try to  acquire  locks, then  it also
			 * wouldn't work because task_yield() within the debugger
			 * throws an exception. */
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        enum_minaddr,
			                        enum_maxaddr,
			                        &mima);
			node = mima.mm_min;
			if (!node)
				break;
			mi.mmi_min   = mnode_getminaddr(node);
			mi.mmi_flags = node->mn_flags & MMAPINFO_FLAGS_MASK;
			part         = node->mn_part;
			if (part) {
				mi.mmi_file   = part->mp_file;
				mi.mmi_offset = mnode_getfileaddr(node);
			} else {
				mi.mmi_file   = NULL;
				mi.mmi_offset = 0;
			}
			if (mi.mmi_min < enum_minaddr) {
				if (part != NULL) {
					mi.mmi_offset += (size_t)((byte_t *)enum_minaddr -
					                          (byte_t *)mi.mmi_min);
				}
				mi.mmi_min = enum_minaddr;
			}
			mi.mmi_fspath = node->mn_fspath;
			mi.mmi_fsname = node->mn_fsname;
			for (;;) {
				mi.mmi_max = mnode_getmaxaddr(node);
				if (mi.mmi_max >= enum_maxaddr)
					break;
				if (node == mima.mm_max)
					break; /* Nothing hereafter -> We're done! */
				/* Search for adjacent nodes that may reference the same underlying file. */
				node = mnode_tree_nextnode(node);
				assertf(node != NULL,
				        "But the last node should have been `mima.mm_max', "
				        "and we didn't get to that one, yet...");
				if ((byte_t *)mi.mmi_max + 1 !=  mnode_getminaddr(node))
					break; /* Not a continuous mapping */
				if (mi.mmi_flags != (node->mn_flags & MMAPINFO_FLAGS_MASK))
					break; /* Different flags */
				if (mi.mmi_fsname != node->mn_fsname ||
				    mi.mmi_fspath != node->mn_fspath)
					break; /* Different file name */
				if (part) {
					pos_t expected_offset;
					bool part_ok;
					if (!node->mn_part)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					/* Check that the part maps the expected location. */
					part_ok = (part->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
					if (!part_ok)
						break;
				} else {
					if (node->mn_part)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
				++num_nodes;
			}

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;

			/* Invoke the given callback. */
			temp = (*cb)(arg, &mi);
		} else
#endif /* CONFIG_HAVE_DEBUGGER */
		{
			mman_lock_read(self);
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        enum_minaddr,
			                        enum_maxaddr,
			                        &mima);
			node = mima.mm_min;
			if (!node) {
				mman_lock_endread(self);
				break;
			}
			mi.mmi_min   = mnode_getminaddr(node);
			mi.mmi_flags = node->mn_flags & MMAPINFO_FLAGS_MASK;
			part         = node->mn_part;
			if (part) {
				if (!mpart_lock_tryacquire(part)) {
waitfor_part:
					/* Wait for the lock of `part' to become available. */
					incref(part);
					mman_lock_endread(self);
					FINALLY_DECREF_UNLIKELY(part);
					while (!mpart_lock_available(part))
						task_yield();
					num_nodes = mi.mmi_index;
					goto again_lookup_node;
				}
				mi.mmi_file   = incref(part->mp_file);
				mi.mmi_offset = mnode_getfileaddr(node);
				mpart_lock_release(part);
			} else {
				mi.mmi_file   = NULL;
				mi.mmi_offset = 0;
			}
			if (mi.mmi_min < enum_minaddr) {
				if (part != NULL) {
					mi.mmi_offset += (size_t)((byte_t *)enum_minaddr -
					                          (byte_t *)mi.mmi_min);
				}
				mi.mmi_min = enum_minaddr;
			}
			mi.mmi_fspath = xincref(node->mn_fspath);
			mi.mmi_fsname = xincref(node->mn_fsname);
			for (;;) {
				mi.mmi_max = mnode_getmaxaddr(node);
				if (mi.mmi_max >= enum_maxaddr)
					break;
				if (node == mima.mm_max)
					break; /* Nothing hereafter -> We're done! */
				/* Search for adjacent nodes that may reference the same underlying file. */
				node = mnode_tree_nextnode(node);
				assertf(node != NULL,
				        "But the last node should have been `mima.mm_max', "
				        "and we didn't get to that one, yet...");
				if ((byte_t *)mi.mmi_max + 1 !=  mnode_getminaddr(node))
					break; /* Not a continuous mapping */
				if (mi.mmi_flags != (node->mn_flags & MMAPINFO_FLAGS_MASK))
					break; /* Different flags */
				if (mi.mmi_fsname != node->mn_fsname ||
				    mi.mmi_fspath != node->mn_fspath)
					break; /* Different file name */
				if (part) {
					pos_t expected_offset;
					bool part_ok;
					if (!node->mn_part)
						break;
					expected_offset = mi.mmi_offset;
					expected_offset += (size_t)((byte_t *)mnode_getminaddr(node) -
					                            (byte_t *)mi.mmi_min);
					if (!mpart_lock_tryacquire(part)) {
						xdecref_unlikely(mi.mmi_file);
						xdecref_unlikely(mi.mmi_fsname);
						xdecref_unlikely(mi.mmi_fspath);
						DBG_memset(&mi.mmi_file, 0xcc, sizeof(mi.mmi_file));
						DBG_memset(&mi.mmi_fsname, 0xcc, sizeof(mi.mmi_fsname));
						DBG_memset(&mi.mmi_fspath, 0xcc, sizeof(mi.mmi_fspath));
						goto waitfor_part;
					}
					/* Check that the part maps the expected location. */
					part_ok = (part->mp_file == mi.mmi_file) &&
					          (mnode_getfileaddr(node) == expected_offset);
					mpart_lock_release(part);
					if (!part_ok)
						break;
				} else {
					if (node->mn_part)
						break;
				}
				/* The secondary node is considered to be apart of the same mapping! */
				++num_nodes;
			}
			mman_lock_endread(self);

			/* Limit the enumerated address range to the requested range */
			if (mi.mmi_max > enum_maxaddr)
				mi.mmi_max = enum_maxaddr;

			/* Invoke the given callback. */
			FINALLY_XDECREF_UNLIKELY(mi.mmi_file);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fsname);
			FINALLY_XDECREF_UNLIKELY(mi.mmi_fspath);
			temp = (*cb)(arg, &mi);
		}
		if unlikely(temp < 0)
			return temp;
		result += temp;
		if (OVERFLOW_UADD((uintptr_t)mi.mmi_max, 1,
		                  (uintptr_t *)&enum_minaddr))
			break;
	}
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_ENUM_C */
