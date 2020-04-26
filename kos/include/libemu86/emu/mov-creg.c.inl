/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS 0x11d
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS 0x1d
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#ifdef EMU86_EMULATE_RDCR0
#define EMU86_EMULATE_HAVE_RDCRn_0 0x0001
#else /* EMU86_EMULATE_RDCR0 */
#define EMU86_EMULATE_HAVE_RDCRn_0 0x0000
#endif /* !EMU86_EMULATE_RDCR0 */
#ifdef EMU86_EMULATE_RDCR1
#define EMU86_EMULATE_HAVE_RDCRn_1 0x0002
#else /* EMU86_EMULATE_RDCR1 */
#define EMU86_EMULATE_HAVE_RDCRn_1 0x0000
#endif /* !EMU86_EMULATE_RDCR1 */
#ifdef EMU86_EMULATE_RDCR2
#define EMU86_EMULATE_HAVE_RDCRn_2 0x0004
#else /* EMU86_EMULATE_RDCR2 */
#define EMU86_EMULATE_HAVE_RDCRn_2 0x0000
#endif /* !EMU86_EMULATE_RDCR2 */
#ifdef EMU86_EMULATE_RDCR3
#define EMU86_EMULATE_HAVE_RDCRn_3 0x0008
#else /* EMU86_EMULATE_RDCR3 */
#define EMU86_EMULATE_HAVE_RDCRn_3 0x0000
#endif /* !EMU86_EMULATE_RDCR3 */
#ifdef EMU86_EMULATE_RDCR4
#define EMU86_EMULATE_HAVE_RDCRn_4 0x0010
#else /* EMU86_EMULATE_RDCR4 */
#define EMU86_EMULATE_HAVE_RDCRn_4 0x0000
#endif /* !EMU86_EMULATE_RDCR4 */
#ifdef EMU86_EMULATE_RDCR5
#define EMU86_EMULATE_HAVE_RDCRn_5 0x0020
#else /* EMU86_EMULATE_RDCR5 */
#define EMU86_EMULATE_HAVE_RDCRn_5 0x0000
#endif /* !EMU86_EMULATE_RDCR5 */
#ifdef EMU86_EMULATE_RDCR6
#define EMU86_EMULATE_HAVE_RDCRn_6 0x0040
#else /* EMU86_EMULATE_RDCR6 */
#define EMU86_EMULATE_HAVE_RDCRn_6 0x0000
#endif /* !EMU86_EMULATE_RDCR6 */
#ifdef EMU86_EMULATE_RDCR7
#define EMU86_EMULATE_HAVE_RDCRn_7 0x0080
#else /* EMU86_EMULATE_RDCR7 */
#define EMU86_EMULATE_HAVE_RDCRn_7 0x0000
#endif /* !EMU86_EMULATE_RDCR7 */

#ifdef EMU86_EMULATE_WRCR0
#define EMU86_EMULATE_HAVE_WRCRn_0 0x0001
#else /* EMU86_EMULATE_WRCR0 */
#define EMU86_EMULATE_HAVE_WRCRn_0 0x0000
#endif /* !EMU86_EMULATE_WRCR0 */
#ifdef EMU86_EMULATE_WRCR1
#define EMU86_EMULATE_HAVE_WRCRn_1 0x0002
#else /* EMU86_EMULATE_WRCR1 */
#define EMU86_EMULATE_HAVE_WRCRn_1 0x0000
#endif /* !EMU86_EMULATE_WRCR1 */
#ifdef EMU86_EMULATE_WRCR2
#define EMU86_EMULATE_HAVE_WRCRn_2 0x0004
#else /* EMU86_EMULATE_WRCR2 */
#define EMU86_EMULATE_HAVE_WRCRn_2 0x0000
#endif /* !EMU86_EMULATE_WRCR2 */
#ifdef EMU86_EMULATE_WRCR3
#define EMU86_EMULATE_HAVE_WRCRn_3 0x0008
#else /* EMU86_EMULATE_WRCR3 */
#define EMU86_EMULATE_HAVE_WRCRn_3 0x0000
#endif /* !EMU86_EMULATE_WRCR3 */
#ifdef EMU86_EMULATE_WRCR4
#define EMU86_EMULATE_HAVE_WRCRn_4 0x0010
#else /* EMU86_EMULATE_WRCR4 */
#define EMU86_EMULATE_HAVE_WRCRn_4 0x0000
#endif /* !EMU86_EMULATE_WRCR4 */
#ifdef EMU86_EMULATE_WRCR5
#define EMU86_EMULATE_HAVE_WRCRn_5 0x0020
#else /* EMU86_EMULATE_WRCR5 */
#define EMU86_EMULATE_HAVE_WRCRn_5 0x0000
#endif /* !EMU86_EMULATE_WRCR5 */
#ifdef EMU86_EMULATE_WRCR6
#define EMU86_EMULATE_HAVE_WRCRn_6 0x0040
#else /* EMU86_EMULATE_WRCR6 */
#define EMU86_EMULATE_HAVE_WRCRn_6 0x0000
#endif /* !EMU86_EMULATE_WRCR6 */
#ifdef EMU86_EMULATE_WRCR7
#define EMU86_EMULATE_HAVE_WRCRn_7 0x0080
#else /* EMU86_EMULATE_WRCR7 */
#define EMU86_EMULATE_HAVE_WRCRn_7 0x0000
#endif /* !EMU86_EMULATE_WRCR7 */

#if CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_RDCR8
#define EMU86_EMULATE_HAVE_RDCRn_8 0x0100
#else /* EMU86_EMULATE_RDCR8 */
#define EMU86_EMULATE_HAVE_RDCRn_8 0x0000
#endif /* !EMU86_EMULATE_RDCR8 */
#ifdef EMU86_EMULATE_RDCR9
#define EMU86_EMULATE_HAVE_RDCRn_9 0x0200
#else /* EMU86_EMULATE_RDCR9 */
#define EMU86_EMULATE_HAVE_RDCRn_9 0x0000
#endif /* !EMU86_EMULATE_RDCR9 */
#ifdef EMU86_EMULATE_RDCR10
#define EMU86_EMULATE_HAVE_RDCRn_10 0x0400
#else /* EMU86_EMULATE_RDCR10 */
#define EMU86_EMULATE_HAVE_RDCRn_10 0x0000
#endif /* !EMU86_EMULATE_RDCR10 */
#ifdef EMU86_EMULATE_RDCR11
#define EMU86_EMULATE_HAVE_RDCRn_11 0x0800
#else /* EMU86_EMULATE_RDCR11 */
#define EMU86_EMULATE_HAVE_RDCRn_11 0x0000
#endif /* !EMU86_EMULATE_RDCR11 */
#ifdef EMU86_EMULATE_RDCR12
#define EMU86_EMULATE_HAVE_RDCRn_12 0x1000
#else /* EMU86_EMULATE_RDCR12 */
#define EMU86_EMULATE_HAVE_RDCRn_12 0x0000
#endif /* !EMU86_EMULATE_RDCR12 */
#ifdef EMU86_EMULATE_RDCR13
#define EMU86_EMULATE_HAVE_RDCRn_13 0x2000
#else /* EMU86_EMULATE_RDCR13 */
#define EMU86_EMULATE_HAVE_RDCRn_13 0x0000
#endif /* !EMU86_EMULATE_RDCR13 */
#ifdef EMU86_EMULATE_RDCR14
#define EMU86_EMULATE_HAVE_RDCRn_14 0x4000
#else /* EMU86_EMULATE_RDCR14 */
#define EMU86_EMULATE_HAVE_RDCRn_14 0x0000
#endif /* !EMU86_EMULATE_RDCR14 */
#ifdef EMU86_EMULATE_RDCR15
#define EMU86_EMULATE_HAVE_RDCRn_15 0x8000
#else /* EMU86_EMULATE_RDCR15 */
#define EMU86_EMULATE_HAVE_RDCRn_15 0x0000
#endif /* !EMU86_EMULATE_RDCR15 */

#ifdef EMU86_EMULATE_WRCR8
#define EMU86_EMULATE_HAVE_WRCRn_8 0x0100
#else /* EMU86_EMULATE_WRCR8 */
#define EMU86_EMULATE_HAVE_WRCRn_8 0x0000
#endif /* !EMU86_EMULATE_WRCR8 */
#ifdef EMU86_EMULATE_WRCR9
#define EMU86_EMULATE_HAVE_WRCRn_9 0x0200
#else /* EMU86_EMULATE_WRCR9 */
#define EMU86_EMULATE_HAVE_WRCRn_9 0x0000
#endif /* !EMU86_EMULATE_WRCR9 */
#ifdef EMU86_EMULATE_WRCR10
#define EMU86_EMULATE_HAVE_WRCRn_10 0x0400
#else /* EMU86_EMULATE_WRCR10 */
#define EMU86_EMULATE_HAVE_WRCRn_10 0x0000
#endif /* !EMU86_EMULATE_WRCR10 */
#ifdef EMU86_EMULATE_WRCR11
#define EMU86_EMULATE_HAVE_WRCRn_11 0x0800
#else /* EMU86_EMULATE_WRCR11 */
#define EMU86_EMULATE_HAVE_WRCRn_11 0x0000
#endif /* !EMU86_EMULATE_WRCR11 */
#ifdef EMU86_EMULATE_WRCR12
#define EMU86_EMULATE_HAVE_WRCRn_12 0x1000
#else /* EMU86_EMULATE_WRCR12 */
#define EMU86_EMULATE_HAVE_WRCRn_12 0x0000
#endif /* !EMU86_EMULATE_WRCR12 */
#ifdef EMU86_EMULATE_WRCR13
#define EMU86_EMULATE_HAVE_WRCRn_13 0x2000
#else /* EMU86_EMULATE_WRCR13 */
#define EMU86_EMULATE_HAVE_WRCRn_13 0x0000
#endif /* !EMU86_EMULATE_WRCR13 */
#ifdef EMU86_EMULATE_WRCR14
#define EMU86_EMULATE_HAVE_WRCRn_14 0x4000
#else /* EMU86_EMULATE_WRCR14 */
#define EMU86_EMULATE_HAVE_WRCRn_14 0x0000
#endif /* !EMU86_EMULATE_WRCR14 */
#ifdef EMU86_EMULATE_WRCR15
#define EMU86_EMULATE_HAVE_WRCRn_15 0x8000
#else /* EMU86_EMULATE_WRCR15 */
#define EMU86_EMULATE_HAVE_WRCRn_15 0x0000
#endif /* !EMU86_EMULATE_WRCR15 */

#define EMU86_EMULATE_HAVE_RDCRn                                 \
	(EMU86_EMULATE_HAVE_RDCRn_0 | EMU86_EMULATE_HAVE_RDCRn_1 |   \
	 EMU86_EMULATE_HAVE_RDCRn_2 | EMU86_EMULATE_HAVE_RDCRn_3 |   \
	 EMU86_EMULATE_HAVE_RDCRn_4 | EMU86_EMULATE_HAVE_RDCRn_5 |   \
	 EMU86_EMULATE_HAVE_RDCRn_6 | EMU86_EMULATE_HAVE_RDCRn_7 |   \
	 EMU86_EMULATE_HAVE_RDCRn_8 | EMU86_EMULATE_HAVE_RDCRn_9 |   \
	 EMU86_EMULATE_HAVE_RDCRn_10 | EMU86_EMULATE_HAVE_RDCRn_11 | \
	 EMU86_EMULATE_HAVE_RDCRn_12 | EMU86_EMULATE_HAVE_RDCRn_13 | \
	 EMU86_EMULATE_HAVE_RDCRn_14 | EMU86_EMULATE_HAVE_RDCRn_15)

#define EMU86_EMULATE_HAVE_WRCRn                                 \
	(EMU86_EMULATE_HAVE_WRCRn_0 | EMU86_EMULATE_HAVE_WRCRn_1 |   \
	 EMU86_EMULATE_HAVE_WRCRn_2 | EMU86_EMULATE_HAVE_WRCRn_3 |   \
	 EMU86_EMULATE_HAVE_WRCRn_4 | EMU86_EMULATE_HAVE_WRCRn_5 |   \
	 EMU86_EMULATE_HAVE_WRCRn_6 | EMU86_EMULATE_HAVE_WRCRn_7 |   \
	 EMU86_EMULATE_HAVE_WRCRn_8 | EMU86_EMULATE_HAVE_WRCRn_9 |   \
	 EMU86_EMULATE_HAVE_WRCRn_10 | EMU86_EMULATE_HAVE_WRCRn_11 | \
	 EMU86_EMULATE_HAVE_WRCRn_12 | EMU86_EMULATE_HAVE_WRCRn_13 | \
	 EMU86_EMULATE_HAVE_WRCRn_14 | EMU86_EMULATE_HAVE_WRCRn_15)
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_EMULATE_HAVE_RDCRn                               \
	(EMU86_EMULATE_HAVE_RDCRn_0 | EMU86_EMULATE_HAVE_RDCRn_1 | \
	 EMU86_EMULATE_HAVE_RDCRn_2 | EMU86_EMULATE_HAVE_RDCRn_3 | \
	 EMU86_EMULATE_HAVE_RDCRn_4 | EMU86_EMULATE_HAVE_RDCRn_5 | \
	 EMU86_EMULATE_HAVE_RDCRn_6 | EMU86_EMULATE_HAVE_RDCRn_7)
#define EMU86_EMULATE_HAVE_WRCRn                               \
	(EMU86_EMULATE_HAVE_WRCRn_0 | EMU86_EMULATE_HAVE_WRCRn_1 | \
	 EMU86_EMULATE_HAVE_WRCRn_2 | EMU86_EMULATE_HAVE_WRCRn_3 | \
	 EMU86_EMULATE_HAVE_WRCRn_4 | EMU86_EMULATE_HAVE_WRCRn_5 | \
	 EMU86_EMULATE_HAVE_WRCRn_6 | EMU86_EMULATE_HAVE_WRCRn_7)
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */

#if !EMU86_EMULATE_HAVE_RDCRn
#undef EMU86_EMULATE_HAVE_RDCRn
#define EMU86_EMULATE_HAVE_RDCRn 0
#endif /* !EMU86_EMULATE_HAVE_RDCRn */

#if !EMU86_EMULATE_HAVE_WRCRn
#undef EMU86_EMULATE_HAVE_WRCRn
#define EMU86_EMULATE_HAVE_WRCRn 0
#endif /* !EMU86_EMULATE_HAVE_WRCRn */

#undef EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD
#undef EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR
#if EMU86_EMULATE_HAVE_RDCRn && EMU86_EMULATE_CONFIG_WANT_MOV_CREG
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD 1
#else /* EMU86_EMULATE_HAVE_RDCRn && EMU86_EMULATE_CONFIG_WANT_MOV_CREG */
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD 0
#endif /* !EMU86_EMULATE_HAVE_RDCRn || !EMU86_EMULATE_CONFIG_WANT_MOV_CREG */
#if EMU86_EMULATE_HAVE_WRCRn && EMU86_EMULATE_CONFIG_WANT_MOV_CREG
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR 1
#else /* EMU86_EMULATE_HAVE_WRCRn && EMU86_EMULATE_CONFIG_WANT_MOV_CREG */
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR 0
#endif /* !EMU86_EMULATE_HAVE_WRCRn || !EMU86_EMULATE_CONFIG_WANT_MOV_CREG */


EMU86_INTELLISENSE_BEGIN(mov_creg) {

#if EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD || EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0f20): {
	/*         0F 20 /r MOV r32, CR0-CR7     Move control register to r32.
	 *         0F 20 /r MOV r64, CR0-CR7     Move extended control register to r64.
	 * REX.R + 0F 20 /0 MOV r64, CR8         Move extended CR8 to r64.1 */
	MODRM_DECODE();
	if (!EMU86_MODRM_ISREG(modrm.mi_type))
		goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
#if (defined(EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER) || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD)
	/* Not all control registers are defined. - Verify that the index is valid! */
	if (!((EMU86_EMULATE_HAVE_RDCRn | EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) & (1 << modrm.mi_reg))) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
		                                                 X86_REGISTER_CONTROL_CR0 + modrm.mi_reg,
		                                                 0, 0);
		__builtin_unreachable();
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
		goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#if EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD
#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (!EMU86_ISUSER())
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
	{
		EMU86_UREG_TYPE value;
		switch (modrm.mi_reg) {
#ifdef EMU86_EMULATE_RDCR0
		case 0: value = EMU86_EMULATE_RDCR0(); break;
#endif /* EMU86_EMULATE_RDCR0 */
#ifdef EMU86_EMULATE_RDCR1
		case 1: value = EMU86_EMULATE_RDCR1(); break;
#endif /* EMU86_EMULATE_RDCR1 */
#ifdef EMU86_EMULATE_RDCR2
		case 2: value = EMU86_EMULATE_RDCR2(); break;
#endif /* EMU86_EMULATE_RDCR2 */
#ifdef EMU86_EMULATE_RDCR3
		case 3: value = EMU86_EMULATE_RDCR3(); break;
#endif /* EMU86_EMULATE_RDCR3 */
#ifdef EMU86_EMULATE_RDCR4
		case 4: value = EMU86_EMULATE_RDCR4(); break;
#endif /* EMU86_EMULATE_RDCR4 */
#ifdef EMU86_EMULATE_RDCR5
		case 5: value = EMU86_EMULATE_RDCR5(); break;
#endif /* EMU86_EMULATE_RDCR5 */
#ifdef EMU86_EMULATE_RDCR6
		case 6: value = EMU86_EMULATE_RDCR6(); break;
#endif /* EMU86_EMULATE_RDCR6 */
#ifdef EMU86_EMULATE_RDCR7
		case 7: value = EMU86_EMULATE_RDCR7(); break;
#endif /* EMU86_EMULATE_RDCR7 */
#if CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_RDCR8
		case 8: value = EMU86_EMULATE_RDCR8(); break;
#endif /* EMU86_EMULATE_RDCR8 */
#ifdef EMU86_EMULATE_RDCR9
		case 9: value = EMU86_EMULATE_RDCR9(); break;
#endif /* EMU86_EMULATE_RDCR9 */
#ifdef EMU86_EMULATE_RDCR10
		case 10: value = EMU86_EMULATE_RDCR10(); break;
#endif /* EMU86_EMULATE_RDCR10 */
#ifdef EMU86_EMULATE_RDCR11
		case 11: value = EMU86_EMULATE_RDCR11(); break;
#endif /* EMU86_EMULATE_RDCR11 */
#ifdef EMU86_EMULATE_RDCR12
		case 12: value = EMU86_EMULATE_RDCR12(); break;
#endif /* EMU86_EMULATE_RDCR12 */
#ifdef EMU86_EMULATE_RDCR13
		case 13: value = EMU86_EMULATE_RDCR13(); break;
#endif /* EMU86_EMULATE_RDCR13 */
#ifdef EMU86_EMULATE_RDCR14
		case 14: value = EMU86_EMULATE_RDCR14(); break;
#endif /* EMU86_EMULATE_RDCR14 */
#ifdef EMU86_EMULATE_RDCR15
		case 15: value = EMU86_EMULATE_RDCR15(); break;
#endif /* EMU86_EMULATE_RDCR15 */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
		default:
#if (EMU86_EMULATE_HAVE_RDCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) == EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS
			__builtin_unreachable(); /* All mandatory registers are supported */
#else /* (EMU86_EMULATE_HAVE_RDCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) == EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS */
#define WANT_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* (EMU86_EMULATE_HAVE_RDCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) != EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS */
		}
#if CONFIG_LIBEMU86_WANT_64BIT && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT)
		if (EMU86_F_IS64(op_flags)) {
			MODRM_SETRMREGQ((u64)value);
		} else {
			MODRM_SETRMREGL((u32)value);
		}
#elif CONFIG_LIBEMU86_WANT_64BIT
		MODRM_SETRMREGQ((u64)value);
#else /* CONFIG_LIBEMU86_WANT_... */
		MODRM_SETRMREGL((u32)value);
#endif /* !CONFIG_LIBEMU86_WANT_... */
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
	                                                 X86_REGISTER_CONTROL_CR0 + modrm.mi_reg,
	                                                 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
	goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD */
#define NEED_return_privileged_instruction
	goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER && !EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD */
}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD || EMU86_EMULATE_CONFIG_CHECKERROR */

#if EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR || EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0f22): {
	/*         0F 22 /r MOV CR0-CR7, r32     Move r32 to control register.
	 *         0F 22 /r MOV CR0-CR7, r64     Move r64 to extended control register.
	 * REX.R + 0F 22 /0 MOV CR8, r64         Move r64 to extended CR8.1 */
#if (defined(EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER) || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR)
	EMU86_UREG_TYPE value;
#endif /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR */
	MODRM_DECODE();
	if (!EMU86_MODRM_ISREG(modrm.mi_type))
		goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
#if (defined(EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER) || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR)
#if CONFIG_LIBEMU86_WANT_64BIT && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT)
	if (EMU86_F_IS64(op_flags)) {
		value = MODRM_GETRMREGQ();
	} else {
		value = MODRM_GETRMREGL();
	}
#elif CONFIG_LIBEMU86_WANT_64BIT
	value = MODRM_GETRMREGQ();
#else /* CONFIG_LIBEMU86_WANT_... */
	value = MODRM_GETRMREGL();
#endif /* !CONFIG_LIBEMU86_WANT_... */
	/* Not all control registers are defined. - Verify that the index is valid! */
	if (!((EMU86_EMULATE_HAVE_WRCRn | EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) & (1 << modrm.mi_reg))) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
		                                                 X86_REGISTER_CONTROL_CR0 + modrm.mi_reg,
		                                                 value, 0);
		__builtin_unreachable();
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
		goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#if EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR
#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (!EMU86_ISUSER())
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
	{
		switch (modrm.mi_reg) {
#ifdef EMU86_EMULATE_WRCR0
		case 0: EMU86_EMULATE_WRCR0(value); break;
#endif /* EMU86_EMULATE_WRCR0 */
#ifdef EMU86_EMULATE_WRCR1
		case 1: EMU86_EMULATE_WRCR1(value); break;
#endif /* EMU86_EMULATE_WRCR1 */
#ifdef EMU86_EMULATE_WRCR2
		case 2: EMU86_EMULATE_WRCR2(value); break;
#endif /* EMU86_EMULATE_WRCR2 */
#ifdef EMU86_EMULATE_WRCR3
		case 3: EMU86_EMULATE_WRCR3(value); break;
#endif /* EMU86_EMULATE_WRCR3 */
#ifdef EMU86_EMULATE_WRCR4
		case 4: EMU86_EMULATE_WRCR4(value); break;
#endif /* EMU86_EMULATE_WRCR4 */
#ifdef EMU86_EMULATE_WRCR5
		case 5: EMU86_EMULATE_WRCR5(value); break;
#endif /* EMU86_EMULATE_WRCR5 */
#ifdef EMU86_EMULATE_WRCR6
		case 6: EMU86_EMULATE_WRCR6(value); break;
#endif /* EMU86_EMULATE_WRCR6 */
#ifdef EMU86_EMULATE_WRCR7
		case 7: EMU86_EMULATE_WRCR7(value); break;
#endif /* EMU86_EMULATE_WRCR7 */
#if CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_WRCR8
		case 8: EMU86_EMULATE_WRCR8(value); break;
#endif /* EMU86_EMULATE_WRCR8 */
#ifdef EMU86_EMULATE_WRCR9
		case 9: EMU86_EMULATE_WRCR9(value); break;
#endif /* EMU86_EMULATE_WRCR9 */
#ifdef EMU86_EMULATE_WRCR10
		case 10: EMU86_EMULATE_WRCR10(value); break;
#endif /* EMU86_EMULATE_WRCR10 */
#ifdef EMU86_EMULATE_WRCR11
		case 11: EMU86_EMULATE_WRCR11(value); break;
#endif /* EMU86_EMULATE_WRCR11 */
#ifdef EMU86_EMULATE_WRCR12
		case 12: EMU86_EMULATE_WRCR12(value); break;
#endif /* EMU86_EMULATE_WRCR12 */
#ifdef EMU86_EMULATE_WRCR13
		case 13: EMU86_EMULATE_WRCR13(value); break;
#endif /* EMU86_EMULATE_WRCR13 */
#ifdef EMU86_EMULATE_WRCR14
		case 14: EMU86_EMULATE_WRCR14(value); break;
#endif /* EMU86_EMULATE_WRCR14 */
#ifdef EMU86_EMULATE_WRCR15
		case 15: EMU86_EMULATE_WRCR15(value); break;
#endif /* EMU86_EMULATE_WRCR15 */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
		default:
#if (EMU86_EMULATE_HAVE_WRCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) == EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS
			__builtin_unreachable(); /* All mandatory registers are supported */
#else /* (EMU86_EMULATE_HAVE_WRCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) == EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS */
#define WANT_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* (EMU86_EMULATE_HAVE_WRCRn & EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS) != EMU86_EMULATE_MANDATORY_CONTROL_REGISTERS */
		}
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
	                                                 X86_REGISTER_CONTROL_CR0 + modrm.mi_reg,
	                                                 value, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
	goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER || EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR */
#define NEED_return_privileged_instruction
	goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER && !EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR */
}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR || EMU86_EMULATE_CONFIG_CHECKERROR */

#undef EMU86_EMULATE_CONFIG_WANT_MOV_CREG_RD
#undef EMU86_EMULATE_CONFIG_WANT_MOV_CREG_WR
#undef EMU86_EMULATE_HAVE_RDCRn_0
#undef EMU86_EMULATE_HAVE_RDCRn_1
#undef EMU86_EMULATE_HAVE_RDCRn_2
#undef EMU86_EMULATE_HAVE_RDCRn_3
#undef EMU86_EMULATE_HAVE_RDCRn_4
#undef EMU86_EMULATE_HAVE_RDCRn_5
#undef EMU86_EMULATE_HAVE_RDCRn_6
#undef EMU86_EMULATE_HAVE_RDCRn_7
#undef EMU86_EMULATE_HAVE_WRCRn_0
#undef EMU86_EMULATE_HAVE_WRCRn_1
#undef EMU86_EMULATE_HAVE_WRCRn_2
#undef EMU86_EMULATE_HAVE_WRCRn_3
#undef EMU86_EMULATE_HAVE_WRCRn_4
#undef EMU86_EMULATE_HAVE_WRCRn_5
#undef EMU86_EMULATE_HAVE_WRCRn_6
#undef EMU86_EMULATE_HAVE_WRCRn_7
#if CONFIG_LIBEMU86_WANT_64BIT
#undef EMU86_EMULATE_HAVE_RDCRn_8
#undef EMU86_EMULATE_HAVE_RDCRn_9
#undef EMU86_EMULATE_HAVE_RDCRn_10
#undef EMU86_EMULATE_HAVE_RDCRn_11
#undef EMU86_EMULATE_HAVE_RDCRn_12
#undef EMU86_EMULATE_HAVE_RDCRn_13
#undef EMU86_EMULATE_HAVE_RDCRn_14
#undef EMU86_EMULATE_HAVE_RDCRn_15
#undef EMU86_EMULATE_HAVE_WRCRn_8
#undef EMU86_EMULATE_HAVE_WRCRn_9
#undef EMU86_EMULATE_HAVE_WRCRn_10
#undef EMU86_EMULATE_HAVE_WRCRn_11
#undef EMU86_EMULATE_HAVE_WRCRn_12
#undef EMU86_EMULATE_HAVE_WRCRn_13
#undef EMU86_EMULATE_HAVE_WRCRn_14
#undef EMU86_EMULATE_HAVE_WRCRn_15
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#undef EMU86_EMULATE_HAVE_RDCRn
#undef EMU86_EMULATE_HAVE_WRCRn

}
EMU86_INTELLISENSE_END

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
