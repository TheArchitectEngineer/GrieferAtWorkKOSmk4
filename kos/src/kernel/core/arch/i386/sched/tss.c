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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS_C 1
#define DISABLE_BRANCH_PROFILING
#define __WANT_MNODE_INIT
#define __WANT_MPART_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/hook.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/x86/gdt.h>
#include <sched/cpu.h>
#include <sched/pertask.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>

#include <stddef.h>

DECL_BEGIN

INTDEF byte_t __bootcpu_x86_df_stack[KERNEL_DF_STACKSIZE];

/* [1..1][const] Page directory identity pointer for unmapping the IOB vector of the current CPU. */
INTERN ATTR_PERCPU void *thiscpu_x86_iobnode_pagedir_identity = NULL;

#ifdef CONFIG_USE_NEW_VM
INTDEF byte_t __bootcpu_x86_iob_start[] ASMNAME("__x86_iob_empty_base");

DATDEF ATTR_PERCPU struct mnode thiscpu_x86_iobnode_ ASMNAME("thiscpu_x86_iobnode");
DATDEF ATTR_PERCPU struct mpart thiscpu_x86_dfstackpart_ ASMNAME("thiscpu_x86_dfstackpart");
DATDEF ATTR_PERCPU struct mnode thiscpu_x86_dfstacknode_ ASMNAME("thiscpu_x86_dfstacknode");

/* The VM node used to represent the IOB mapping of the current CPU */
PUBLIC ATTR_PERCPU struct mnode thiscpu_x86_iobnode_ = {
	MNODE_INIT_mn_mement({}),
	MNODE_INIT_mn_minaddr(__bootcpu_x86_iob_start),
	MNODE_INIT_mn_maxaddr(__bootcpu_x86_iob_start + PAGESIZE - 1),
	MNODE_INIT_mn_flags(MNODE_F_PWRITE | MNODE_F_PREAD |
	                    MNODE_F_SHARED | MNODE_F_NOSPLIT |
	                    MNODE_F_NOMERGE | MNODE_F_KERNPART |
	                    MNODE_F_MPREPARED | MNODE_F_MLOCK),
	MNODE_INIT_mn_part(NULL), /* Reserved node */
	MNODE_INIT_mn_fspath(NULL),
	MNODE_INIT_mn_fsname(NULL),
	MNODE_INIT_mn_mman(&mman_kernel),
	MNODE_INIT_mn_partoff(0),
	MNODE_INIT_mn_link(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT__mn_module(NULL)
};

INTDEF byte_t __bootcpu_x86_df_stackpage_p[];
INTDEF struct mnode __bootcpu_x86_dfstack_node;
INTDEF struct mpart __bootcpu_x86_dfstack_part;

PUBLIC ATTR_PERCPU struct mpart thiscpu_x86_dfstackpart_ = {
	MPART_INIT_mp_refcnt(2), /* `thiscpu_x86_dfstackpart', `thiscpu_x86_dfstacknode.mn_part' */
	MPART_INIT_mp_flags(MPART_F_NOFREE | MPART_F_NOSPLIT |
	                    MPART_F_NOMERGE | MPART_F_MLOCK_FROZEN |
	                    MPART_F_MLOCK),
	MPART_INIT_mp_state(MPART_ST_MEM),
	MPART_INIT_mp_file(&mfile_ndef),
	MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(thiscpu_x86_dfstackpart_.mp_copy)),
	MPART_INIT_mp_share({ &__bootcpu_x86_dfstack_node }),
	MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(thiscpu_x86_dfstackpart_.mp_lockops)),
	MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),
	MPART_INIT_mp_minaddr(0),
	MPART_INIT_mp_maxaddr(KERNEL_DF_STACKSIZE - 1),
	MPART_INIT_mp_changed({}),
	MPART_INIT_mp_filent({}),
	MPART_INIT_mp_blkst_ptr(NULL),
	MPART_INIT_mp_mem((physpage_t)__bootcpu_x86_df_stackpage_p, CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE)),
	MPART_INIT_mp_meta(NULL)
};

PUBLIC ATTR_PERCPU struct mnode thiscpu_x86_dfstacknode_ = {
	MNODE_INIT_mn_mement({ {} }),
	MNODE_INIT_mn_minaddr(__bootcpu_x86_df_stack),
	MNODE_INIT_mn_maxaddr(__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE - 1),
	MNODE_INIT_mn_flags(MNODE_F_PWRITE | MNODE_F_PREAD |
	                    MNODE_F_SHARED | MNODE_F_NOSPLIT |
	                    MNODE_F_NOMERGE | MNODE_F_KERNPART |
	                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_MLOCK),
	MNODE_INIT_mn_part(&__bootcpu_x86_dfstack_part),
	MNODE_INIT_mn_fspath(NULL),
	MNODE_INIT_mn_fsname(NULL),
	MNODE_INIT_mn_mman(&mman_kernel),
	MNODE_INIT_mn_partoff(0),
	MNODE_INIT_mn_link({ NULL, &__bootcpu_x86_dfstack_part.mp_share.lh_first }),
	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT__mn_module(NULL)
};

#else /* CONFIG_USE_NEW_VM */
INTDEF byte_t __bootcpu_x86_iob_startpage[] ASMNAME("__x86_iob_empty_page");

/* The VM node used to represent the IOB mapping of the current CPU */
PUBLIC ATTR_PERCPU struct vm_node thiscpu_x86_iobnode = {
	/* .vn_node   = */ { NULL, NULL,
	                     (pageid_t)__bootcpu_x86_iob_startpage,
	                     (pageid_t)__bootcpu_x86_iob_startpage + 1 },
	/* .vn_byaddr = */ LLIST_INITNODE,
	/* .vn_prot   = */ VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_KERNPRT,
	/* .vn_vm     = */ &vm_kernel,
	/* .vn_part   = */ NULL,
	/* .vn_block  = */ NULL,
	/* .vn_fspath = */ NULL,
	/* .vn_fsname = */ NULL,
	/* .vn_link   = */ { NULL, NULL },
	/* .vn_guard  = */ 0
};

INTDEF byte_t __bootcpu_x86_df_stackpage[];
INTDEF byte_t __bootcpu_x86_df_stackpage_p[];
INTDEF struct vm_node __bootcpu_x86_dfstack_node;
INTDEF struct vm_datapart __bootcpu_x86_dfstack_part;

PUBLIC ATTR_PERCPU struct vm_datapart
thiscpu_x86_dfstackpart_ ASMNAME("thiscpu_x86_dfstackpart") = {
	/* .dp_refcnt = */ 2, /* `thiscpu_x86_dfstackpart', `thiscpu_x86_dfstacknode' */
	.dp_lock   = SHARED_RWLOCK_INIT,
	{
		/* .dp_tree = */ { NULL, NULL, 0, CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) - 1 }
	},
	.dp_crefs = LLIST_INIT,
	.dp_srefs = &__bootcpu_x86_dfstack_node,
	.dp_stale = NULL,
	.dp_block = &vm_datablock_anonymous,
#if CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) > (BITS_PER_POINTER / VM_DATAPART_PPP_BITS)
	.dp_flags = VM_DATAPART_FLAG_NORMAL | VM_DATAPART_FLAG_HEAPPPP,
#else
	.dp_flags = VM_DATAPART_FLAG_NORMAL,
#endif
	.dp_state = VM_DATAPART_STATE_LOCKED,
	{
		.dp_ramdata = {
			.rd_blockv = &__bootcpu_x86_dfstack_part.dp_ramdata.rd_block0,
			{
				.rd_block0 = {
					.rb_start = (physpage_t)__bootcpu_x86_df_stackpage_p,
					.rb_size  = CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE)
				}
			}
		}
	},
	{
#if CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) > (BITS_PER_POINTER / VM_DATAPART_PPP_BITS)
		.dp_pprop = 0,
#else
		.dp_pprop = (uintptr_t)-1,
#endif
	},
};

PUBLIC ATTR_PERCPU struct vm_node thiscpu_x86_dfstacknode_ ASMNAME("thiscpu_x86_dfstacknode") = {
	.vn_node = {
		NULL,
		NULL,
		(pageid_t)__bootcpu_x86_df_stackpage,
		(pageid_t)__bootcpu_x86_df_stackpage + CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) - 1
	},
	.vn_byaddr = LLIST_INITNODE,
	.vn_prot   = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED,
	.vn_flags  = VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED,
	.vn_vm     = &vm_kernel,
	.vn_part   = &__bootcpu_x86_dfstack_part,
	.vn_block  = &vm_datablock_anonymous,
	.vn_fspath = NULL,
	.vn_fsname = NULL,
	.vn_link   = { NULL, &LLIST_HEAD(__bootcpu_x86_dfstack_part.dp_srefs) },
	.vn_guard  = 0
};
#endif /* !CONFIG_USE_NEW_VM */



#ifndef __x86_64__
INTDEF void ASMCALL x86_idt_double_fault(void);
INTDEF byte_t _bootcpu_thiscpu_x86_tss[];

PUBLIC ATTR_PERCPU struct tss thiscpu_x86_tssdf = {
	.t_link       = 0,
	.__t_zero0    = 0,
	.t_esp0       = (uintptr_t)COMPILER_ENDOF(__bootcpu_x86_df_stack),
	.t_ss0        = SEGMENT_KERNEL_DATA,
	.__t_zero1    = 0,
	.t_esp1       = (uintptr_t)COMPILER_ENDOF(__bootcpu_x86_df_stack),
	.t_ss1        = SEGMENT_KERNEL_DATA,
	.__t_zero2    = 0,
	.t_esp2       = (uintptr_t)COMPILER_ENDOF(__bootcpu_x86_df_stack),
	.t_ss2        = SEGMENT_KERNEL_DATA,
	.__t_zero3    = 0,
	.t_cr3        = (u32)&pagedir_kernel_phys,
	.t_eip        = (u32)&x86_idt_double_fault,
	.t_eflags     = 0,
	.t_eax        = 0,
	.t_ecx        = 0,
	.t_edx        = 0,
	.t_ebx        = (u32)&_bootcpu,                 /* Used by the implementation. */
	.t_esp        = (uintptr_t)COMPILER_ENDOF(__bootcpu_x86_df_stack),
	.t_ebp        = (u32)&_bootcpu_thiscpu_x86_tss, /* Used by the implementation. */
	.t_esi        = 0,
	.t_edi        = 0,
	.t_es         = SEGMENT_USER_DATA_RPL,
	.__t_zero4    = 0,
	.t_cs         = SEGMENT_KERNEL_CODE,
	.__t_zero5    = 0,
	.t_ss         = SEGMENT_KERNEL_DATA,
	.__t_zero6    = 0,
	.t_ds         = SEGMENT_USER_DATA_RPL,
	.__t_zero7    = 0,
	.t_fs         = SEGMENT_KERNEL_FSBASE,
	.__t_zero8    = 0,
	.t_gs         = SEGMENT_USER_GSBASE_RPL,
	.__t_zero9    = 0,
	.t_ldtr       = SEGMENT_NULL,
	.__t_zeroa    = 0,
	{
		.t_flags  = 0
	},
	.t_iomap      = 0
};
#endif /* !__x86_64__ */



PUBLIC NOBLOCK ATTR_PURE WUNUSED size_t
NOTHROW(KCALL get_stack_avail)(void) {
	void *start, *end, *sp = __rdsp();
#ifndef __x86_64__
	struct cpu *c = THIS_CPU;
	if unlikely(FORCPU(c, thiscpu_x86_tssdf.t_ecx)) {
		struct vm_node const *node;
		node  = &FORCPU(c, thiscpu_x86_dfstacknode);
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	} else
#endif /* !__x86_64__ */
	{
		struct vm_node const *node;
		node  = THIS_KERNEL_STACK;
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	}
	if likely(sp >= start && sp < end)
		return (size_t)((byte_t *)sp - (byte_t *)start);
	/* FIXME: This  is  an ugly  work-around  for when  the  kernel is
	 *        running from a custom stack, such as the debugger stack,
	 *        or the stack defined by the GDB server driver. */
	return 8096;
}

PUBLIC NOBLOCK ATTR_PURE WUNUSED size_t
NOTHROW(KCALL get_stack_inuse)(void) {
	void *start, *end, *sp = __rdsp();
#ifndef __x86_64__
	struct cpu *c = THIS_CPU;
	if unlikely(FORCPU(c, thiscpu_x86_tssdf.t_ecx)) {
		struct vm_node const *node;
		node  = &FORCPU(c, thiscpu_x86_dfstacknode);
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	} else
#endif /* !__x86_64__ */
	{
		struct vm_node const *node;
		node  = THIS_KERNEL_STACK;
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	}
	if likely(sp >= start && sp < end)
		return (size_t)((byte_t *)end - (byte_t *)sp);
	return 0;
}

/* Returns the bounds of the currently used kernel-space stack.
 * @param: pbase: Filled with a pointer to the lowest-address byte that is still apart of the stack.
 * @param: pend:  Filled with a pointer one past the highest-address byte that is still apart of the stack. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL get_stack_for)(void **pbase, void **pend, void *sp) {
	void *start, *end;
#ifndef __x86_64__
	struct cpu *c = THIS_CPU;
	if unlikely(FORCPU(c, thiscpu_x86_tssdf.t_ecx)) {
		struct vm_node const *node;
		node  = &FORCPU(c, thiscpu_x86_dfstacknode);
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	} else
#endif /* !__x86_64__ */
	{
		struct vm_node const *node;
		node  = THIS_KERNEL_STACK;
		start = vm_node_getaddr(node);
		end   = vm_node_getendaddr(node);
	}
	if likely(sp >= start && sp < end) {
		*pbase = start;
		*pend  = end;
		return;
	}
	/* FIXME: This  is  an ugly  work-around  for when  the  kernel is
	 *        running from a custom stack, such as the debugger stack,
	 *        or the stack defined by the GDB server driver. */
	*pbase = (void *)(FLOOR_ALIGN((uintptr_t)sp, PAGESIZE) - PAGESIZE);
	*pend  = (void *)(FLOOR_ALIGN((uintptr_t)sp, PAGESIZE) + PAGESIZE);
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL get_current_stack)(void **pbase, void **pend) {
	get_stack_for(pbase, pend, __rdsp());
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS_C */
