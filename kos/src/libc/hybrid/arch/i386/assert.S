/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S
#define GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S 1
#define DONT_REDIRECT___ubsan_handle_builtin_unreachable
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <bits/va_list-struct.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#ifndef SIZEOF_POINTER
#include <hybrid/typecore.h>
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#define Pn(n) (SIZEOF_POINTER * (n))

/* Offsets for `struct __apfail_struct' */
#define struct_apfail__afs_expr Pn(0)
#define struct_apfail__afs_file Pn(1)
#define struct_apfail__afs_line Pn(2)
#define struct_apfail__afs_func Pn(3)


#ifdef __KERNEL__
#define ASSERTION_SECTION   .text.cold
#else /* __KERNEL__ */
#define ASSERTION_SECTION   .text.crt.assert
#endif /* !__KERNEL__ */

/* >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail(void);
 * >> PUBLIC ATTR_NORETURN void LIBCCALL __stack_chk_fail_local(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_stack_chk_fail)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	EXTERN(libc_stack_failure_core)
	call   libc_stack_failure_core
	.cfi_endproc
END(libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail, libc_stack_chk_fail)
DEFINE_PUBLIC_ALIAS(__stack_chk_fail_local, libc_stack_chk_fail)


/* >> PUBLIC ATTR_NORETURN void LIBCCALL abort(void); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_abort)
	.cfi_startproc
	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	EXTERN(libc_abort_failure_core)
	call   libc_abort_failure_core
	.cfi_endproc
END(libc_abort)

DEFINE_PUBLIC_ALIAS(abort, libc_abort)


#ifndef __KERNEL__
/* >> PUBLIC ATTR_NORETURN void LIBCCALL abortf(char const *format, ...); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc_abortf)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *format
	 * %R_sysvabi1P: VA(0)
	 * %R_sysvabi2P: VA(1)
	 * %R_sysvabi3P: VA(2)
	 * %R_sysvabi4P: VA(3)
	 * %R_sysvabi5P: VA(4)
	 * 8(%Psp):      VA(5)
	 * 16(%Psp):     VA(6) */
	pushP_cfi %R_sysvabi0P /* af_format */
	pushP_cfi Pn(1)(%Psp)  /* af_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pdx, Pn(2)) /* 2 = # of preceding `pushP_cfi' */
	pushP_cfi %Pdx         /* vl_reg_save_area (filled later) */
	pushP_cfi %Pdx         /* vl_overflow_arg_area (== af_state.kcs_gpregs.gp_rsp) */
	pushP_cfi $(Pn(1))     /* vl_gp_offset */
	movP   %Psp, %R_fcall0P /* libc_vabortf_failure_core:args */
	movP   (SIZEOF_X86_64_VA_LIST_STRUCT + OFFSET_KCPUSTATE64_GPREGS + OFFSET_GPREGS64_RDX)(%R_fcall0P), %Pdx

#ifndef __NO_FPU
	/* Check if FPU registers need saving */
	testb  %al, %al
	jz     1f
	.cfi_remember_state
	subP_imm_cfi (Pn(5) + X86_64_VA_LIST_XMM_COUNT * 16), %Psp
	leaP   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RSI(%Psp), %Pax
	movq   %Pax, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%R_fcall0P)
	movl   $(0), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
	movP   %R_sysvabi5P, Pn(4)(%Psp)
	movP   %R_sysvabi4P, Pn(3)(%Psp)
	movP   %R_sysvabi3P, Pn(2)(%Psp)
	movP   %R_sysvabi2P, Pn(1)(%Psp)
	movP   %R_sysvabi1P, Pn(0)(%Psp)
	X86_64_VA_LIST_SAVE_XMM(Pn(5)(%Psp))
	INTERN(libc_vabortf_failure_core)
	call   libc_vabortf_failure_core
1:	.cfi_restore_state
#endif /* !__NO_FPU */

	/* Push normal register-save area */
	pushP_cfi %R_sysvabi5P
	pushP_cfi %R_sysvabi4P
	pushP_cfi %R_sysvabi3P
	pushP_cfi %R_sysvabi2P
	pushP_cfi %R_sysvabi1P
	leaP   -OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RSI(%Psp), %Pax
	movP   %Pax, OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA(%R_fcall0P)
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%R_fcall0P)
	INTERN(libc_vabortf_failure_core)
	call   libc_vabortf_failure_core
#else /* __x86_64__ */
	/* char const *format, ... */

	/* Generate a full `struct kcpustate' */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	leaP   (SIZEOF_KCPUSTATE + Pn(1))(%Psp), %Pax
	pushP_cfi %Pax                         /* af_args */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_vabortf_failure_core)
	call   libc_vabortf_failure_core
#endif /* !__x86_64__ */
	.cfi_endproc
END(libc_abortf)

DEFINE_PUBLIC_ALIAS(abortf, libc_abortf)
#endif /* !__KERNEL__ */

/* Provide debugging facilities for __builtin_unreachable() (s.a. <__crt.h>) */
DEFINE_PUBLIC_ALIAS(__ubsan_handle_builtin_unreachable, libc_abort)
DEFINE_INTERN_ALIAS(libc___ubsan_handle_builtin_unreachable, libc_abort)
DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort) /* std::terminate(void) */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(terminate, libc_abort)           /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort) /* std::terminate(void) */
DEFINE_PUBLIC_ALIAS(__chk_fail, libc_abort)
#endif /* !__KERNEL__ */

/* TODO: Remove me (only still needed because I don't want to
 *       rebuild  libstdc++, which still uses this symbol...) */
DEFINE_PUBLIC_ALIAS(__crt_unreachable, libc_abort)


#ifndef __INTELLISENSE__
#define DEFINE___afail
#include "assert-fail.S.inl"

#ifdef __KERNEL__
/* Support for __acheck[f]() */
#define DEFINE___acheck
#include "assert-fail.S.inl"
#endif /* __KERNEL__ */
#endif /* !__INTELLISENSE__ */


#if !defined(__KERNEL__) || defined(__INTELLISENSE__)

DEFINE_INTERN_ALIAS(libc___assert_fail, libc___afail)
DEFINE_PUBLIC_ALIAS(__assert_fail, libc___assert_fail)

/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_func(char const *file,
 * >>               unsigned int line,
 * >>               char const *func,
 * >>               char const *expr); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert_func)
	.cfi_startproc

#ifdef __x86_64__
	/* %R_sysvabi0P: char const *file
	 * %R_sysvabi1P: unsigned int line
	 * %R_sysvabi2P: char const *func
	 * %R_sysvabi3P: char const *expr */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi2P /* aa_func */
	pushP_cfi %R_sysvabi1P /* aa_line */
	pushP_cfi %R_sysvabi0P /* aa_file */
	pushP_cfi %R_sysvabi3P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *file, unsigned int line, char const *func, char const *expr */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert_func)
DEFINE_PUBLIC_ALIAS(__assert_func, libc___assert_func)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assertfail(char const *expr,
 * >>              char const *file,
 * >>              unsigned int line,
 * >>              char const *func,
 * >>              size_t charsize); */
#ifdef __x86_64__
DEFINE_INTERN_ALIAS(libc___assertfail, libc___afail)
#else /* __x86_64__ */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assertfail)
	.cfi_startproc
	/* char const *expr, char const *file, unsigned int line, char const *func, size_t charsize */
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assertfail)
#endif /* !__x86_64__ */
DEFINE_PUBLIC_ALIAS(__assertfail, libc___assertfail)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert(char const *file,
 * >>          unsigned int line,
 * >>          char const *expr); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc___assert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *file
	 * %R_sysvabi1P: unsigned int line
	 * %R_sysvabi2P: char const *expr */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi1P /* aa_line */
	pushP_cfi %R_sysvabi0P /* aa_file */
	pushP_cfi %R_sysvabi2P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* char const *file, unsigned int line, char const *expr */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                -,                -, char const  *file, unsigned int line, char const *expr */
	/* char const *expr, char const *file, unsigned int line, char const  *func, char const *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc___assert)
DEFINE_PUBLIC_ALIAS(__assert, libc___assert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _assert(char const *expr,
 * >>         char const *file,
 * >>         unsigned int line); */
.section ASSERTION_SECTION
INTERN_FUNCTION(libc__assert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char const *expr
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char const *expr, char const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                -,                -, char const  *expr, char const *file, unsigned int line */
	/* char const *expr, char const *file, unsigned int line, char const *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core)
	call   libc_assertion_failure_core
	.cfi_endproc
END(libc__assert)
DEFINE_PUBLIC_ALIAS(_assert, libc__assert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> _wassert(char32_t const *expr,
 * >>          char32_t const *file,
 * >>          unsigned int line); */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libc__wassert)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: char32_t const *expr
	 * %R_sysvabi1P: char32_t const *file
	 * %R_sysvabi2P: unsigned int line */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi $(0)         /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char32_t const *expr, char32_t const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                    -,                    -, char32_t const *expr, char32_t const *file, unsigned int line */
	/* char32_t const *expr, char32_t const *file, unsigned int    line, char     const *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char32_t const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char32_t const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core_c32)
	call   libc_assertion_failure_core_c32
	.cfi_endproc
END(libc__wassert)
DEFINE_PUBLIC_ALIAS(_wassert, libc__wassert)


/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> DOS$_wassert(char16_t const *expr,
 * >>              char16_t const *file,
 * >>              unsigned int line); */
.section ".text.crt.dos.assert"
INTERN_FUNCTION(libd__wassert)
	.cfi_startproc
#ifdef __x86_64__
	/* NOTE: Because we're NORETURN, no need to do `MSABI_SAVEZONE_PUSH()'! */

	/* %R_msabi0P: char16_t const *expr
	 * %R_msabi1P: char16_t const *file
	 * %R_msabi2P: unsigned int line */
	pushP_cfi $(0)        /* aa_format */
	pushP_cfi $(0)        /* aa_func */
	pushP_cfi %R_msabi2P  /* aa_line */
	pushP_cfi %R_msabi1P  /* aa_file */
	pushP_cfi %R_msabi0P  /* aa_expr */
	pushP_cfi Pn(5)(%Psp) /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp     /* aa_args */
#else /* __x86_64__ */
	/* char16_t const *expr, char16_t const *file, unsigned int line */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(Pn(2))
	/*                    -,                    -, char16_t const *expr, char16_t const *file, unsigned int line */
	/* char16_t const *expr, char16_t const *file, unsigned int    line, char const     *func, char const  *format */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char16_t const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* char16_t const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_core_c16)
	call   libc_assertion_failure_core_c16
	.cfi_endproc
END(libd__wassert)
DEFINE_PUBLIC_ALIAS(DOS$_wassert, libd__wassert)



/* >> PUBLIC ATTR_NORETURN void VLIBCCALL
 * >> __assert_perror_fail(int errnum,
 * >>                      char const *file,
 * >>                      unsigned int line,
 * >>                      char const *func) */
.section ".text.crt.glibc.assert"
INTERN_FUNCTION(libc___assert_perror_fail)
	.cfi_startproc
#ifdef __x86_64__
	/* %R_sysvabi0P: int errnum
	 * %R_sysvabi1P: char const *file
	 * %R_sysvabi2P: unsigned int line
	 * %R_sysvabi3P: char const *func */
	pushP_cfi $(0)         /* aa_format */
	pushP_cfi %R_sysvabi3P /* aa_func */
	pushP_cfi %R_sysvabi2P /* aa_line */
	pushP_cfi %R_sysvabi1P /* aa_file */
	pushP_cfi %R_sysvabi0P /* aa_expr */
	pushP_cfi Pn(5)(%Psp)  /* aa_state.kcs_rip */
	ASM_PUSH_KCPUSTATE_AFTER_RIP_CFI_R_EX2(%Pax, Pn(6)) /* 6 = # of preceding `pushP_cfi' */
	subP_imm_cfi SIZEOF_X86_64_VA_LIST_STRUCT, %Psp /* aa_args */
#else /* __x86_64__ */
	/* int errnum, char const *file, unsigned int line, char const *func */
	pushP_cfi 0(%Psp)  /* RETURN_PC */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R_EX(SIZEOF_POINTER)
	movP   (SIZEOF_KCPUSTATE + Pn(1))(%Psp), %Pax /* char const *expr */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(0))(%Psp) /* aa_expr */
	movP   (SIZEOF_KCPUSTATE + Pn(2))(%Psp), %Pax /* char const *file */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(1))(%Psp) /* aa_file */
	movP   (SIZEOF_KCPUSTATE + Pn(3))(%Psp), %Pax /* unsigned int line */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(2))(%Psp) /* aa_line */
	movP   (SIZEOF_KCPUSTATE + Pn(4))(%Psp), %Pax /* char const *func */
	movP   %Pax, (SIZEOF_KCPUSTATE + Pn(3))(%Psp) /* aa_func */
	movP   $(0), (SIZEOF_KCPUSTATE + Pn(4))(%Psp) /* aa_format */
	pushP_cfi $(0)                                /* aa_args */
#endif /* !__x86_64__ */

	/* Call the high-level handler */
	movP   %Psp, %R_fcall0P
	INTERN(libc_assertion_failure_perror)
	call   libc_assertion_failure_perror
	.cfi_endproc
END(libc___assert_perror_fail)
DEFINE_PUBLIC_ALIAS(__assert_perror_fail, libc___assert_perror_fail)

#endif /* !__KERNEL__ || __INTELLISENSE__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S */
