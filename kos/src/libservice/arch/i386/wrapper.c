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
#ifndef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C
#define GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/minmax.h>

#include <kos/bits/userprocmask.h>
#include <kos/except.h>
#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>

#include <libgen86/gen.h>
#include <libservice/client.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>

#include "../../com.h"
#include "wrapper.h"

#ifdef __x86_64__
#include <libunwind/cfi/x86_64.h>
#else /* __x86_64__ */
#include <libunwind/cfi/i386.h>
#endif /* !__x86_64__ */

DECL_BEGIN

#ifndef __getuserprocmask_defined
#error "Generated wrapper functions assume that userprocmask is available and supported!"
#endif /* !__getuserprocmask_defined */



/* When the currently set exception is RT-level, return `false'.
 * Otherwise,   clear   the   exception   and   return   `true'. */
INTERN bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void) {
	struct exception_data *d = error_data();
	if (ERRORCLASS_ISRTLPRIORITY(d->e_class))
		return false;
	d->e_code = ERROR_CODEOF(E_OK); /* Clear exception */
	return true;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) int
compar_com_inline_buffer_param(void const *_a, void const *_b) {
#define _MASK (COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT)
	STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FIN < COM_INLINE_BUFFER_PARAM_FOUT);
	struct com_inline_buffer_param const *a, *b;
	a = (struct com_inline_buffer_param const *)_a;
	b = (struct com_inline_buffer_param const *)_b;
	if ((a->cibp_flags & _MASK) < (b->cibp_flags & _MASK))
		return -1; /* Less than */
	if ((a->cibp_flags & _MASK) > (b->cibp_flags & _MASK))
		return 1; /* Greater than */

	/* Non-pointer-aligned buffer sizes go after those that are  pointer-aligned.
	 * That way, the number of buffers following those which leave %Pdi unaligned
	 * may be reduced by 1. */
	{
		bool is_a_aligned = IS_ALIGNED(a->cibp_sizeof, sizeof(void *));
		bool is_b_aligned = IS_ALIGNED(b->cibp_sizeof, sizeof(void *));
		if (is_a_aligned && !is_b_aligned)
			return -1; /* Less than */
		if (!is_a_aligned && is_b_aligned)
			return 1; /* Greater than */
	}

	/* Lastly, sort by serial argument stream offsets. */
	if (a->cibp_serial_offset < b->cibp_serial_offset)
		return -1; /* Less than */
	if (a->cibp_serial_offset > b->cibp_serial_offset)
		return 1; /* Greater than */

	/* Shouldn't get here! */
	return 0;
#undef _MASK
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) int
compar_com_buffer_param(void const *_a, void const *_b) {
#define _MASK (COM_BUFFER_PARAM_FIN | COM_BUFFER_PARAM_FOUT)
	STATIC_ASSERT(COM_BUFFER_PARAM_FIN < COM_BUFFER_PARAM_FOUT);
	struct com_buffer_param const *a, *b;
	a = (struct com_buffer_param const *)_a;
	b = (struct com_buffer_param const *)_b;
	if ((a->cbp_flags & _MASK) < (b->cbp_flags & _MASK))
		return -1; /* Less than */
	if ((a->cbp_flags & _MASK) > (b->cbp_flags & _MASK))
		return 1; /* Greater than */

	/* When `COM_BUFFER_PARAM_FRETMIN' is set, the
	 * parameter should come after another without
	 * that flag. */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FRETMIN) < (b->cbp_flags & COM_BUFFER_PARAM_FRETMIN))
		return -1; /* Less than */
	if ((a->cbp_flags & COM_BUFFER_PARAM_FRETMIN) > (b->cbp_flags & COM_BUFFER_PARAM_FRETMIN))
		return 1; /* Greater than */

	/* Lastly, sort by serial argument stream offsets. */
	if (a->cbp_serial_offset < b->cbp_serial_offset)
		return -1; /* Less than */
	if (a->cbp_serial_offset > b->cbp_serial_offset)
		return 1; /* Greater than */

	/* Shouldn't get here! */
	return 0;
#undef _MASK
}


/* Return the max # of consecutive integer params with
 * adjacent `cip_param_offset' or `cip_serial_offset',
 * where  `u16_field_offset' must be the offset to one
 * of those fields within `com_int_param' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uint8_t
NOTHROW(FCALL comgen_count_consecutive_intpar)(struct com_generator const *__restrict self,
                                               ptrdiff_t u16_field_offset) {
	uint8_t i, result = 0;
	for (i = 0; i < self->cg_int_paramc;) {
		uint8_t count = 1;
		uint16_t next;
		next = *(u16 const *)((byte_t const *)&self->cg_intpar[i] + u16_field_offset);
		for (;;) {
			++i;
			if (i >= self->cg_int_paramc)
				break;
			next += sizeof(void *);
			if (*(u16 const *)((byte_t const *)&self->cg_intpar[i] + u16_field_offset) != next)
				break;
			++count;
		}
		if (result < count)
			result = count;
	}
	return result;
}



/* Initialize the given com generator. Prior to calling
 * this function, the  caller must already  initialize:
 *  - self->cg_info
 * NOTE: This  function will leave the following fields
 *       uninitialized (which must be set-up by a later
 *       call to `comgen_reset()'):
 *  - self->cg_txbas, self->cg_ehbas
 *  - self->cg_txend, self->cg_ehend */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _comgen_init)(struct com_generator *__restrict self) {
	uint8_t i;
	int16_t param_offset;
	uint16_t serial_offset;

	/* Load and sort buffer arguments. */
#ifdef __x86_64__
	for (i = 0; i < SERVICE_ARGC_MAX; ++i) {
		if (self->cg_info.dl_params[i] == SERVICE_TYPE_VOID)
			break;
	}
	self->cg_paramc = i;

	/* On  x86_64, register parameters  are pushed at the  start of the function
	 * and therefor have negative offsets. Note  that for the time being,  these
	 * offsets are only correct when `COM_GENERATOR_FEATURE_USES_R12' isn't set.
	 * Code  that may eventually set `COM_GENERATOR_FEATURE_USES_R12' knows this
	 * and will adjust offsets to account for 8 more bytes of offset. */
	if (i > 6) /* First 6 arguments are passed through registers (and are therefor saved) */
		i = 6;
	param_offset = -((3 + i) * sizeof(void *));
#else /* __x86_64__ */

	/* On  i386, there only exist stack arguments which being immediately after
	 * the return address. Since CFA also points after the return address, it's
	 * effectively a zero-offset! */
	param_offset = 0;
#endif /* !__x86_64__ */

	self->cg_inline_buf_paramc = 0;
	self->cg_buf_paramc        = 0;
	self->cg_inbuf_paramc      = 0;
	self->cg_inoutbuf_paramc   = 0;
	self->cg_outbuf_paramc     = 0;
	self->cg_int_paramc        = 0;
	serial_offset              = offsetof(struct service_com, sc_generic.g_data);
	for (i = 0; i < SERVICE_ARGC_MAX; ++i) {
		uint8_t flags;
		service_typeid_t typ;
		typ = self->cg_info.dl_params[i];
		switch (typ & _SERVICE_TYPE_CLASSMASK) {

		case (SERVICE_TYPE_ARGBUF_IN(0) & _SERVICE_TYPE_CLASSMASK): {
			struct com_buffer_param *par;
do_flexible_inbuf_argument:
			flags = COM_BUFFER_PARAM_FIN;
			++self->cg_inbuf_paramc;
			__IF0 {
		case (SERVICE_TYPE_ARGBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_BUFFER_PARAM_FOUT;
				++self->cg_outbuf_paramc;
			}
			__IF0 {
		case (SERVICE_TYPE_ARGBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_BUFFER_PARAM_FIN | COM_BUFFER_PARAM_FOUT;
				++self->cg_inoutbuf_paramc;
			}
			/* Buffer parameter. (NOTE: The sorting of these is done in a second step) */
			if ((typ & SERVICE_OUT_SIZEARG_RETURN_MINVAL) &&
			    (typ & _SERVICE_TYPE_CLASSMASK) != (SERVICE_TYPE_ARGBUF_IN(0) & _SERVICE_TYPE_CLASSMASK))
				flags |= COM_BUFFER_PARAM_FRETMIN;
			par = &self->cg_buf_paramv[self->cg_buf_paramc++];
			par->cbp_flags         = flags;
			par->cbp_param_index   = i;
			par->cbp_param_offset  = param_offset;
			par->cbp_serial_offset = serial_offset;
#ifndef __x86_64__
			/* `movs' is always used for copying of buffers here! */
			self->cg_features |= (COM_GENERATOR_FEATURE_USES_EDI |
			                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
		}	break;

		case (SERVICE_TYPE_FIXBUF_IN(0) & _SERVICE_TYPE_CLASSMASK): {
			uint16_t buffer_sizeof;
			flags = COM_INLINE_BUFFER_PARAM_FIN;
			__IF0 {
		case (SERVICE_TYPE_FIXBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_INLINE_BUFFER_PARAM_FOUT;
			}
			__IF0 {
		case (SERVICE_TYPE_FIXBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK):
				flags = COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT;
			}
			buffer_sizeof = typ & _SERVICE_TYPE_PARAMMASK;
			if (buffer_sizeof <= COM_FIXBUF_INLINE_THRESHOLD) {
				/* Use a fixed-length inline buffer. */
				struct com_inline_buffer_param *par;
				if (buffer_sizeof >= COM_USEMOVS_THRESHOLD) {
					/* Use movs for copying data. */
#ifdef __x86_64__
					self->cg_features |= (COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS);
#else /* __x86_64__ */
					self->cg_features |= (COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS |
					                      COM_GENERATOR_FEATURE_USES_EDI |
					                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
				}
				par = &self->cg_inline_buf_paramv[self->cg_inline_buf_paramc++];
				par->cibp_param_index   = i;             /* [const] Parameter index in `:cg_info.dl_params' */
				par->cibp_flags         = flags;         /* [const] Parameter flags (set of `COM_INLINE_BUFFER_PARAM_F*') */
				par->cibp_param_offset  = param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory */
				par->cibp_serial_offset = serial_offset; /* [const] Offset from `struct service_com' to where the address of this buffer is saved */
/*				par->cibp_buffer_offset = ...;            * Initialized later */
				par->cibp_sizeof        = buffer_sizeof;
			} else {
				/* Use a dynamically allocated buffer. */
				struct com_buffer_param *par;
				STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FIN == COM_BUFFER_PARAM_FIN);
				STATIC_ASSERT(COM_INLINE_BUFFER_PARAM_FOUT == COM_BUFFER_PARAM_FOUT);
				par = &self->cg_buf_paramv[self->cg_buf_paramc++];
				par->cbp_flags         = flags;
				par->cbp_param_index   = i;
				par->cbp_param_offset  = param_offset;
				par->cbp_serial_offset = serial_offset;
				switch (flags) {
				case COM_INLINE_BUFFER_PARAM_FIN:
					++self->cg_inbuf_paramc;
					break;
				case COM_INLINE_BUFFER_PARAM_FOUT:
					++self->cg_outbuf_paramc;
					break;
				case COM_INLINE_BUFFER_PARAM_FIN | COM_INLINE_BUFFER_PARAM_FOUT:
					++self->cg_inoutbuf_paramc;
					break;
				default: __builtin_unreachable();
				}
#ifndef __x86_64__
				/* `movs' is always used for copying of buffers here! */
				self->cg_features |= (COM_GENERATOR_FEATURE_USES_EDI |
				                      COM_GENERATOR_FEATURE_USES_ESI);
#endif /* !__x86_64__ */
			}
		}	break;

		default:
			switch (typ & _SERVICE_TYPE_PARAMMASK) {

			case SERVICE_TYPE_VOID & _SERVICE_TYPE_PARAMMASK:
				goto done_params;

			case SERVICE_TYPE_STR_IN & _SERVICE_TYPE_PARAMMASK:
				goto do_flexible_inbuf_argument;

#ifndef __x86_64__
			case SERVICE_TYPE_386_R64 & _SERVICE_TYPE_PARAMMASK:
				/* Double-wide integer argument. */
				self->cg_intpar[self->cg_int_paramc].cip_param_offset  = param_offset;
				self->cg_intpar[self->cg_int_paramc].cip_serial_offset = serial_offset;
				++self->cg_int_paramc;
				param_offset += sizeof(void *);
				serial_offset += sizeof(void *);
				ATTR_FALLTHROUGH
#endif /* !__x86_64__ */
			default:
				/* Integer argument. */
				self->cg_intpar[self->cg_int_paramc].cip_param_offset  = param_offset;
				self->cg_intpar[self->cg_int_paramc].cip_serial_offset = serial_offset;
				++self->cg_int_paramc;
				break;
			}
			break;
		}

		/* Adjust offsets for the next argument. */
		param_offset += sizeof(void *);
		serial_offset += sizeof(void *);

#ifdef __x86_64__
		/* Special case: Once we hit the `SAVED: %Pbx'-field, we've
		 * handled all register parameters  and must jump ahead  to
		 * continue on with stack-based arguments. */
		if (param_offset == -3 * (int16_t)sizeof(void *))
			param_offset = 0;
#endif /* __x86_64__ */
	}
done_params:
#ifndef __x86_64__
	self->cg_paramc = i;
#endif /* !__x86_64__ */

#ifdef __x86_64__
	/* When  at least  2 buffer parameters  exist, then `%r12'  will be used
	 * by the implementation. As such, we  need to set the appropriate  code
	 * feature flag, as well as  adjust parameter offsets since all  offsets
	 * pointing into the argument save area will be shifted down by 8 bytes. */
	if (self->cg_buf_paramc >= 2) {
#define reloc_param_offset(x) ((x) < 0 ? (void)((x) -= 8) : (void)0)
		self->cg_features |= COM_GENERATOR_FEATURE_USES_R12;
		for (i = 0; i < self->cg_int_paramc; ++i)
			reloc_param_offset(self->cg_intpar[i].cip_param_offset);
		for (i = 0; i < self->cg_inline_buf_paramc; ++i)
			reloc_param_offset(self->cg_inline_buf_paramv[i].cibp_param_offset);
		for (i = 0; i < self->cg_buf_paramc; ++i)
			reloc_param_offset(self->cg_buf_paramv[i].cbp_param_offset);
#undef reloc_param_offset
	}
#endif /* __x86_64__ */

	/* Sort `self->cg_inline_buf_paramv' */
	qsort(self->cg_inline_buf_paramv,
	      self->cg_inline_buf_paramc,
	      sizeof(self->cg_inline_buf_paramv[0]),
	      &compar_com_inline_buffer_param);

	/* Assign `self->cg_inline_buf_paramv[*].cibp_buffer_offset' */
	for (i = 0; i < self->cg_inline_buf_paramc; ++i) {
		/* Inline buffers are always pointer-aligned. */
		serial_offset = CEIL_ALIGN(serial_offset, sizeof(void *));
		self->cg_inline_buf_paramv[i].cibp_buffer_offset = serial_offset;
		serial_offset += self->cg_inline_buf_paramv[i].cibp_sizeof;
	}

	/* The  end address  of the last  inline buffer is  equal to the
	 * minimum allocation size of the service_com descriptor struct. */
	self->cg_sizeof_service_com = serial_offset;

	/* Sort `self->cg_buf_paramv' */
	qsort(self->cg_buf_paramv,
	      self->cg_buf_paramc,
	      sizeof(self->cg_buf_paramv[0]),
	      &compar_com_buffer_param);

	/* At this point, pretty much everything has been initialized, with
	 * the exception of:
	 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
	 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
	 *   - cg_locvar_offset
	 *   - cg_locvar_size
	 * Start out by figuring out if lods and/or stos should be used for
	 * loading integer arguments. */
	if (self->cg_int_paramc != 0) {
		uint8_t consecutive_param;
		uint8_t consecutive_serial;
		consecutive_param  = comgen_count_consecutive_intpar(self, offsetof(struct com_int_param, cip_param_offset));
		consecutive_serial = comgen_count_consecutive_intpar(self, offsetof(struct com_int_param, cip_serial_offset));
		if (consecutive_param >= 3) {
			self->cg_features |= COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS;
#ifndef __x86_64__
			self->cg_features |= COM_GENERATOR_FEATURE_USES_ESI;
#endif /* !__x86_64__ */
		}
		if (consecutive_serial >= 3) {
			self->cg_features |= COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS;
#ifndef __x86_64__
			self->cg_features |= COM_GENERATOR_FEATURE_USES_EDI;
#endif /* !__x86_64__ */
		}
	}

	/* Figure out the local variable area size. */
	self->cg_locvar_size = 2 * sizeof(void *); /* LOC_oldset, LOC_upm */
	if (self->cg_buf_paramc != 0) {
		self->cg_locvar_size += 2 * sizeof(void *);                   /* LOC_bufpar_ptr, LOC_bufpar_shm */
		self->cg_locvar_size += self->cg_buf_paramc * sizeof(void *); /* LOC_bufparam_handles */
		if (self->cg_inbuf_paramc != 0 && (self->cg_inoutbuf_paramc != 0 || self->cg_outbuf_paramc != 0))
			self->cg_locvar_size += sizeof(void *); /* LOC_outbuffers_start */
	}

	/* Figure out where local variables end, which in turn determines where they start. */
	{
		int16_t locend;
		locend = -3 * (int16_t)sizeof(void *); /* RETURN_PC, saved %Pbp, saved %Pbx */
#ifdef __x86_64__
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_R12)
			locend -= 8;                       /* Saved %r12 */
		locend -= MIN(self->cg_paramc, 6) * 8; /* Saved register params */
#else /* __x86_64__ */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI)
			locend -= 4; /* Saved %esi */
		if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI)
			locend -= 4; /* Saved %edi */
#endif /* !__x86_64__ */
		/* Remember where local variables start */
		self->cg_locvar_offset = locend - self->cg_locvar_size;
	}
}



/************************************************************************/
/* Assembly generation                                                  */
/************************************************************************/

#ifdef __x86_64__
/* Parameter register indices for the SysVAbi calling convention. */
static uint8_t const sysvabi_registers[6] = {
	GEN86_R_RDI,
	GEN86_R_RSI,
	GEN86_R_RDX,
	GEN86_R_RCX,
	GEN86_R_R8,
	GEN86_R_R9
};
#endif /* __x86_64__ */

/* Signal mask set by wrapper functions to disable preemption */
PRIVATE sigset_t const full_sigset = SIGSET_INIT_FULL;


/* Generate instrumentation to move the CFA PC to the current position.
 * The  .cfi_* macros in  GNU AS automatically do  this whenever any of
 * them are used, and will  also move the CFA  PC such that it  equates
 * the current PC.
 * >> if (self->cg_CFA_loc < self->cg_txptr) {
 * >>     uint32_t delta;
 * >>     delta = (uint32_t)(uintptr_t)(self->cg_txptr - self->cg_CFA_loc);
 * >>     comgen_eh_DW_CFA_advance_loc(self, delta);
 * >>     self->cg_CFA_loc = self->cg_txptr;
 * >> } */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_movehere)(struct com_generator *__restrict self) {
	if (self->cg_CFA_loc < self->cg_txptr) {
		uint32_t delta;
		delta = (uint32_t)(uintptr_t)(self->cg_txptr - self->cg_CFA_loc);
		comgen_eh_DW_CFA_advance_loc(self, delta);
		self->cg_CFA_loc = self->cg_txptr;
	}
}


/* .cfi_def_cfa_offset <regno> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_DW_CFA_def_cfa_offset)(struct com_generator *__restrict self,
                                               int16_t offset) {
	assert((offset % __SIZEOF_POINTER__) == 0);
	if (!comgen_ehok(self))
		return;
	if (offset != self->cg_cfa_offset) {
		comgen_eh_putb(self, DW_CFA_def_cfa_offset_sf);
		comgen_eh_putsleb128(self, -(offset / __SIZEOF_POINTER__));
		self->cg_cfa_offset = offset;
	}
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_putsleb128)(struct com_generator *__restrict self,
                                    intptr_t value) {
	byte_t byte;
	for (;;) {
		byte = value & 0x7f;
		value >>= 7;
		if ((value == 0 && (byte & 0x40) == 0) ||
		    (value == -1 && (byte & 0x40) != 0))
			break;
		byte |= 0x80; /* more bytes to come */
		comgen_eh_putb(self, byte);
	}
	comgen_eh_putb(self, byte);
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_putuleb128)(struct com_generator *__restrict self,
                                    uintptr_t value) {
	uint8_t byte;
	for (;;) {
		byte = value & 0x7f;
		value >>= 7;
		if (value == 0)
			break;
		byte |= 0x80; /* more bytes to come */
		comgen_eh_putb(self, byte);
	}
	comgen_eh_putb(self, byte);
}



/* With %Psi and %Pdi already populated (and permission to clobber %Pcx),
 * generate code to copy exactly `num_bytes' from 0(%Psi) to 0(%Pdi). */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_memcpy_with_rep_movs)(struct com_generator *__restrict self,
                                           size_t num_bytes) {
	size_t pwords = num_bytes / sizeof(void *);
	/* Because `num_bytes' is fixed, we can encode a super-efficient memcpy */
	if (pwords >= COM_USEREP_THRESHOLD) {
		gen86_movP_imm_r(&self->cg_txptr, pwords, GEN86_R_PCX);
		gen86_rep_movsP(&self->cg_txptr);
	} else {
		size_t i;
		for (i = 0; i < pwords; ++i)
			gen86_movsP(&self->cg_txptr);
	}
#ifdef __x86_64__
	if (num_bytes & 8)
		gen86_movsq(&self->cg_txptr);
#endif /* __x86_64__ */
	if (num_bytes & 4)
		gen86_movsl(&self->cg_txptr);
	if (num_bytes & 2)
		gen86_movsw(&self->cg_txptr);
	if (num_bytes & 1)
		gen86_movsb(&self->cg_txptr);
}


/* Generate instructions:
 * >>     pushP_cfi_r %Pbp        # %Pbp is used for `REF struct service_shm_handle *R_service_shm_handle'
 * >>     pushP_cfi_r %Pbx        # %Pbx is used for `struct service_com            *R_service_com'
 * >> #ifdef __x86_64__
 * >>     pushP_cfi_r %r12        # only if COM_GENERATOR_FEATURE_USES_R12
 * >>     pushP_cfi %r9           # only if cg_paramc >= 6
 * >>     pushP_cfi %r8           # only if cg_paramc >= 5
 * >>     pushP_cfi %rcx          # only if cg_paramc >= 4
 * >>     pushP_cfi %rdx          # only if cg_paramc >= 3
 * >>     pushP_cfi %rsi          # only if cg_paramc >= 2
 * >>     pushP_cfi %rdi          # only if cg_paramc >= 1
 * >> #else // __x86_64__
 * >>     pushP_cfi_r %Psi        # only if COM_GENERATOR_FEATURE_USES_ESI
 * >>     pushP_cfi_r %Pdi        # only if COM_GENERATOR_FEATURE_USES_EDI
 * >> #endif // !__x86_64__ */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_push_registers_on_entry)(struct com_generator *__restrict self) {
#define generate_pushP_cfi(GEN86_R_NAME)           \
	(gen86_pushP_r(&self->cg_txptr, GEN86_R_NAME), \
	 comgen_eh_movehere(self),                     \
	 comgen_eh_DW_CFA_adjust_cfa_offset(self, sizeof(void *)))
#define generate_pushP_cfi_r(GEN86_R_NAME, CFI_X86_UNWIND_REGISTER_NAME) \
	(generate_pushP_cfi(GEN86_R_NAME),     \
	 comgen_eh_DW_CFA_rel_offset(self, CFI_X86_UNWIND_REGISTER_NAME, 0))

	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */
	generate_pushP_cfi_r(GEN86_R_PBP, CFI_X86_UNWIND_REGISTER_PBP); /* pushP_cfi_r %Pbp */
	generate_pushP_cfi_r(GEN86_R_PBX, CFI_X86_UNWIND_REGISTER_PBX); /* pushP_cfi_r %Pbx */

#ifdef __x86_64__
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_R12)
		generate_pushP_cfi_r(GEN86_R_R12, CFI_X86_64_UNWIND_REGISTER_R12); /* pushP_cfi_r %r12 */
	/* Push argument registers. */
	{
		unsigned int i;
		for (i = self->cg_paramc; i--;) {
			generate_pushP_cfi(sysvabi_registers[i]);
		}
	}
#else /* __x86_64__ */
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_ESI)
		generate_pushP_cfi_r(GEN86_R_ESI, CFI_386_UNWIND_REGISTER_ESI); /* pushP_cfi_r %Psi */
	if (self->cg_features & COM_GENERATOR_FEATURE_USES_EDI)
		generate_pushP_cfi_r(GEN86_R_EDI, CFI_386_UNWIND_REGISTER_EDI); /* pushP_cfi_r %Pdi */
#endif /* !__x86_64__ */

#undef generate_pushP_cfi_r
#undef generate_pushP_cfi
}


/* Generate instructions:
 * >>     subP   $<cg_locvar_size - 2 * sizeof(void*)>, %Psp
 * >>     .cfi_adjust_cfa_offset <cg_locvar_size - 2 * sizeof(void*)> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_allocate_stack_space)(struct com_generator *__restrict self) {
	uint16_t delta;
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */
	delta = self->cg_locvar_size - 2 * sizeof(void *);
	gen86_subP_imm_r(&self->cg_txptr, delta, GEN86_R_PSP);
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, delta);
}


/* Generate instructions:
 * >> // Disable preemption
 * >>     call   getuserprocmask
 * >>     pushP_cfi %Pax                                  # LOC_upm
 * >>     pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset
 * >>     .cfi_remember_state
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset, %Pcx
 * >>     movP   %Pcx,         userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $full_sigset, userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >> .Leh_preemption_pop_begin: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_disable_preemption)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */

	/* >>     call   getuserprocmask */
	gen86_call(&self->cg_txptr, &getuserprocmask);

	/* >>     pushP_cfi %Pax                                  # LOC_upm */
	gen86_pushP_r(&self->cg_txptr, GEN86_R_PAX);
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, sizeof(void *));

	/* >>     pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset */
	gen86_pushP_mod(&self->cg_txptr, gen86_modrm_db,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PAX);
	comgen_eh_movehere(self);
	comgen_eh_DW_CFA_adjust_cfa_offset(self, sizeof(void *));

	/* >>     .cfi_remember_state */
	comgen_eh_DW_CFA_remember_state(self);

#ifdef __x86_64__
	if ((uintptr_t)&full_sigset > UINT64_C(0x00000000ffffffff)) {
		/* >>     movabs $full_sigset, %Pcx */
		gen86_movabs_imm_r(&self->cg_txptr, &full_sigset, GEN86_R_PCX);

		/* >>     movP   %Pcx,         userprocmask::pm_sigmask(%Pax) # Disable preemption */
		gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
		                offsetof(struct userprocmask, pm_sigmask),
		                GEN86_R_PAX);
	} else
#endif /* __x86_64__ */
	{
		/* >>     movP   $full_sigset, userprocmask::pm_sigmask(%Pax) # Disable preemption */
		gen86_movP_imm_db(&self->cg_txptr, (uintptr_t)&full_sigset,
		                  offsetof(struct userprocmask, pm_sigmask),
		                  GEN86_R_PAX);
	}

	/* >> .Leh_preemption_pop_begin: */
	comgen_defsym(self, COM_SYM_Leh_preemption_pop_begin);
}



/* Convenience register names. */
#define GEN86_R_service_shm_handle GEN86_R_PBP
#define GEN86_R_service_com        GEN86_R_PBX


/* Generate instructions:
 * >> // Allocate the com buffer
 * >>     movP   $<cg_service>, %R_fcall0P   # Input constant (hard-coded)
 * >>     movP   $<ALLOC_SIZE>, %R_fcall1P   # Input constant (hard-coded)
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_pop_preemption
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, %R_service_shm_handle   # %R_service_shm_handle == %Pbp
 * >>     movP   %Pdx, %R_service_com          # %R_service_com        == %Pbx
 * >> .Leh_free_service_com_begin: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_allocate_com_buffer)(struct com_generator *__restrict self) {
	size_t alloc_size;
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */

	/* >>     movP   $<cg_service>, %R_fcall0P   # Input constant (hard-coded) */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	/* >>     movP   $<ALLOC_SIZE>, %R_fcall1P   # Input constant (hard-coded) */
	alloc_size = self->cg_sizeof_service_com;
	alloc_size = CEIL_ALIGN(alloc_size, SERVICE_SHM_ALLOC_ALIGN);
	alloc_size += SERVICE_SHM_ALLOC_EXTRA;
	if (alloc_size < SERVICE_SHM_ALLOC_MINSIZE)
		alloc_size = SERVICE_SHM_ALLOC_MINSIZE;
	gen86_movP_imm_r(&self->cg_txptr, alloc_size, GEN86_R_FCALL1P);

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >>     call   libservice_shmbuf_alloc_nopr_nx */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr_nx);

		/* >>     testP  %Pax, %Pax */
		gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);

		/* >>     jz     .Lerr_pop_preemption */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4);
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_pop_preemption);
	} else {
		/* >>     call   libservice_shmbuf_alloc_nopr */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr);
	}

	/* >>     movP   %Pax, %R_service_shm_handle   # %R_service_shm_handle == %Pbp */
	gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_service_shm_handle);

	/* >>     movP   %Pdx, %R_service_com          # %R_service_com        == %Pbx */
	gen86_movP_r_r(&self->cg_txptr, GEN86_R_PDX, GEN86_R_service_com);

	/* >> .Leh_free_service_com_begin: */
	comgen_defsym(self, COM_SYM_Leh_free_service_com_begin);
}



/* Generate instructions for the "#if cg_buf_paramc == 0"
 * case of `comgen_serialize_buffer_arguments()':
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pax, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_com_buffer_alloc
 * >> .Ltest_pending_signals_after_com_buffer_alloc_return: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_0)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */

	/* >>     movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PAX);

	/* >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >>     movP   %Pax, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >>     jnz    .Ltest_pending_signals_after_com_buffer_alloc */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc);

	/* >> .Ltest_pending_signals_after_com_buffer_alloc_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_com_buffer_alloc_return);
}




/* Generate instructions for the "#if cg_buf_paramc == 1"
 * case of `comgen_serialize_buffer_arguments()':
 * >>     movP   $0, LOC_bufpar_ptr(%Psp)
 * >>     movP   $<cg_service>,                             %R_fcall0P
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[0](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jnz    .Lsingle_buffers_is_in_band
 * >>     movP   $<cg_service>,                                         %R_fcall0P
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   ...,                                                   %R_fcall1P  # Buffer size requirements of cg_buf_paramv[0]
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %R_fcall1P, %Pax   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy an out-of-band in/inout buffer into SHM memory
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %Pax, %Pdi # Unconditionally use %Pdi for copying!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     subP   service_shm_handle::ssh_shm(%Pdx), %Pax
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     movP   %Pax, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffer_alloc
 * >> .Ltest_pending_signals_after_single_buffer_alloc_return:
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE>, %Pcx
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   %Psi,                                      %Pcx # This one was preserved above!
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     jmp    .Lsingle_buffers_done
 * >>
 * >> .Lsingle_buffers_is_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffers_is_in_band
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band_return:
 * >>     # %Pax == libservice_shm_handle_ataddr_nopr(<cg_service>, <cg_buf_paramv[0].cbp_param_offset>(%Psp))
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >> .Lsingle_buffers_done: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_1)(struct com_generator *__restrict self) {
	/* NOTE: Because of `COM_GENERATOR_INITIAL_TX_BUFSIZ', we don't
	 *       have to worry about running out of buffer space (yet) */
	uint8_t param_index;
	service_typeid_t param_typ;
	size_t fixed_buffer_size;
	int8_t *pdisp_Lsingle_buffers_done;       /* Relocate PC8 */
	int8_t *pdisp_Lsingle_buffers_is_in_band; /* Relocate PC8 */

	param_index       = self->cg_buf_paramv[0].cbp_param_index;
	param_typ         = self->cg_info.dl_params[param_index];
	fixed_buffer_size = (size_t)-1;
	/* If the buffer's size if fixed, load it now. */
	switch (param_typ & _SERVICE_TYPE_CLASSMASK) {
	case SERVICE_TYPE_FIXBUF_IN(0) & _SERVICE_TYPE_CLASSMASK:
	case SERVICE_TYPE_FIXBUF_OUT(0) & _SERVICE_TYPE_CLASSMASK:
	case SERVICE_TYPE_FIXBUF_INOUT(0) & _SERVICE_TYPE_CLASSMASK:
		fixed_buffer_size = param_typ & _SERVICE_TYPE_PARAMMASK;
		break;
	default:
		break;
	}

	/* >>     movP   $0, LOC_bufpar_ptr(%Psp) */
	gen86_movP_imm_db(&self->cg_txptr, 0,
	                  comgen_spoffsetof_LOC_bufpar_ptr(self),
	                  GEN86_R_PSP);

	/* >>     movP   $<cg_service>, %R_fcall0P */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	/* >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %R_fcall1P */
	gen86_movP_db_r(&self->cg_txptr, self->cg_buf_paramv[0].cbp_param_offset,
	                GEN86_R_PSP, GEN86_R_FCALL1P);

	/* >>     call   libservice_shm_handle_ataddr_nopr */
	gen86_call(&self->cg_txptr, &libservice_shm_handle_ataddr_nopr);

	/* >>     movP   %Pax, LOC_bufparam_handles[0](%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                comgen_spoffsetof_LOC_bufpar_handles(self, 0),
	                GEN86_R_PSP);

	/* >>     testP  %Pax, %Pax */
	gen86_testP_r_r(&self->cg_txbas, GEN86_R_PAX, GEN86_R_PAX);

	/* >>     jnz    .Lsingle_buffers_is_in_band */
	gen86_jcc8_offset(&self->cg_txptr, GEN86_CC_NZ, -1);
	pdisp_Lsingle_buffers_is_in_band = (int8_t *)(self->cg_txptr - 1);

	/* >>     movP   $<cg_service>, %R_fcall0P */
	gen86_movP_imm_r(&self->cg_txptr, self->cg_service, GEN86_R_FCALL0P);

	if (fixed_buffer_size != (size_t)-1) {
		size_t adjusted;
		adjusted = fixed_buffer_size;
		adjusted = CEIL_ALIGN(adjusted, SERVICE_SHM_ALLOC_ALIGN);
		adjusted += SERVICE_SHM_ALLOC_EXTRA;
		if (adjusted < SERVICE_SHM_ALLOC_MINSIZE)
			adjusted = SERVICE_SHM_ALLOC_MINSIZE;

		/* >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P */
		gen86_movP_imm_r(&self->cg_txptr, adjusted, GEN86_R_FCALL1P);
	} else {
		/* >>     movP   ..., %R_fcall1P  # Buffer size requirements of cg_buf_paramv[0] */
		/* TODO */
		abort();

		if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
			/* >>     movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below! */
			gen86_movP_r_r(&self->cg_txptr, GEN86_R_FCALL1P, GEN86_R_PSI);
		}

		/* >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
		gen86_addP_imm_r(&self->cg_txptr, SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1, GEN86_R_FCALL1P);

		/* >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P */
		gen86_andP_imm_r(&self->cg_txptr, ~(SERVICE_SHM_ALLOC_ALIGN - 1), GEN86_R_FCALL1P);

		/* >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax */
		gen86_movP_imm_r(&self->cg_txptr, SERVICE_SHM_ALLOC_MINSIZE, GEN86_R_PAX);

		/* >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE) */
		gen86_cmpP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P);

		/* >>     cmovbP %R_fcall1P, %Pax   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE; */
		gen86_cmovbP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_FCALL1P);
	}

	if (!(self->cg_features & COM_GENERATOR_FEATURE_FEXCEPT)) {
		/* >>     call   libservice_shmbuf_alloc_nopr_nx */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr_nx);

		/* >>     testP  %Pax, %Pax */
		gen86_testP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PAX);

		/* >>     jz     .Lerr_free_service_com */
		gen86_jccl_offset(&self->cg_txptr, GEN86_CC_Z, -4);
		comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Lerr_free_service_com);
	} else {
		/* >>     call   libservice_shmbuf_alloc_nopr */
		gen86_call(&self->cg_txptr, &libservice_shmbuf_alloc_nopr);
	}

	/* >>     movP   %Pax, LOC_bufpar_ptr(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                comgen_spoffsetof_LOC_bufpar_ptr(self),
	                GEN86_R_PSP);

	/* >>     movP   %Pdx, LOC_bufpar_shm(%Psp) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                comgen_spoffsetof_LOC_bufpar_shm(self),
	                GEN86_R_PSP);

	/* >> .Leh_free_xbuf_begin: */
	comgen_defsym(self, COM_SYM_Leh_free_xbuf_begin);

	/* Copy an out-of-band in/inout buffer into SHM memory */
	if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
		/* >>     movP   %Pax, %Pdi # Unconditionally use %Pdi for copying! */
		gen86_movP_r_r(&self->cg_txptr, GEN86_R_PAX, GEN86_R_PDI);
	}

	/* >>     subP   service_shm_handle::ssh_shm(%Pdx), %Pax */
	gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PAX,
	                 offsetof(struct service_shm_handle, ssh_shm),
	                 GEN86_R_PDX);

	/* Re-enable preemption */
	/* >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PCX);

	/* >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >>     movP   %Pax, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PAX,
	                self->cg_buf_paramv[0].cbp_serial_offset,
	                GEN86_R_service_com);

	/* >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >>     jnz    .Ltest_pending_signals_after_single_buffer_alloc */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc);

	/* >> .Ltest_pending_signals_after_single_buffer_alloc_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffer_alloc_return);

	if (self->cg_buf_paramv[0].cbp_flags & COM_BUFFER_PARAM_FIN) {
		if (fixed_buffer_size != (size_t)-1) {
			/* >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying! */
			gen86_movP_db_r(&self->cg_txptr,
			                self->cg_buf_paramv[0].cbp_param_offset,
			                GEN86_R_PSP, GEN86_R_PSI);

			/* >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE>, %Pcx */
			comgen_memcpy_with_rep_movs(self, fixed_buffer_size);
		} else {
			/* >>     movP   %Psi, %Pcx # This one was preserved above! */
			gen86_movP_r_r(&self->cg_txptr, GEN86_R_PSI, GEN86_R_PCX);

			/* >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying! */
			gen86_movP_db_r(&self->cg_txptr,
			                self->cg_buf_paramv[0].cbp_param_offset,
			                GEN86_R_PSP, GEN86_R_PSI);

			/* >>     rep    movsb */
			gen86_rep_movsb(&self->cg_txptr);
		}
	}

	/* >>     jmp    .Lsingle_buffers_done */
	gen86_jmp8_offset(&self->cg_txptr, -1);
	pdisp_Lsingle_buffers_done = (int8_t *)(self->cg_txptr - 1);

	/* >> .Lsingle_buffers_is_in_band: */
	*pdisp_Lsingle_buffers_is_in_band += (int8_t)(uint8_t)(uintptr_t)
	                                     (self->cg_txptr - (byte_t *)pdisp_Lsingle_buffers_is_in_band);

	/* Re-enable preemption */
	/* >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_oldset(self),
	                GEN86_R_PSP, GEN86_R_PCX);

	/* >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm' */
	gen86_movP_db_r(&self->cg_txptr, comgen_spoffsetof_LOC_upm(self),
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PCX,
	                offsetof(struct userprocmask, pm_sigmask),
	                GEN86_R_PDX);

	/* >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx) */
	gen86_testP_imm_mod(&self->cg_txptr, gen86_modrm_db, USERPROCMASK_FLAG_HASPENDING,
	                    offsetof(struct userprocmask, pm_flags), GEN86_R_PDX);

	/* >>     jnz    .Ltest_pending_signals_after_single_buffers_is_in_band */
	gen86_jccl_offset(&self->cg_txptr, GEN86_CC_NZ, -4);
	comgen_reloc(self, self->cg_txptr - 4, COM_R_PCREL32, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band);

	/* >> .Ltest_pending_signals_after_single_buffers_is_in_band_return: */
	comgen_defsym(self, COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band_return);

	/* >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdx */
	gen86_movP_db_r(&self->cg_txptr,
	                self->cg_buf_paramv[0].cbp_param_offset,
	                GEN86_R_PSP, GEN86_R_PDX);

	/* >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx */
	gen86_subP_mod_r(&self->cg_txptr, gen86_modrm_db, GEN86_R_PDX,
	                 offsetof(struct service_shm_handle, ssh_shm),
	                 GEN86_R_PAX);

	/* >>     movP   %Pdx, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com) */
	gen86_movP_r_db(&self->cg_txptr, GEN86_R_PDX,
	                self->cg_buf_paramv[0].cbp_serial_offset,
	                GEN86_R_service_com);

	/* >> .Lsingle_buffers_done: */
	*pdisp_Lsingle_buffers_done += (int8_t)(uint8_t)(uintptr_t)
	                               (self->cg_txptr - (byte_t *)pdisp_Lsingle_buffers_done);
}




/* Generate instructions for the "#if cg_buf_paramc >= 2"
 * case of `comgen_serialize_buffer_arguments()':
 * >>     # >> %R_temp_exbuf_size is %edi on i386 and %r12 on x86_64
 * >>     # NOTE: On x86_64, compilation getting here imples `COM_GENERATOR_FEATURE_USES_R12'!
 * >>     xorP   %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     movP   %R_temp_exbuf_size, LOC_bufpar_ptr(%Psp)
 * >> {foreach[BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     movP   $<cg_service>,            %R_fcall0P
 * >>     movP   <cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[INDEX](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jz     1f
 * >>     movP   <cbp_param_offset>(%Psp),          %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cbp_serial_offset>(%Psp)
 * >>     jmp    2f
 * >> 1:  # NOTE: When only 1 buffer argument exists, %R_temp_exbuf_size isn't
 * >>     #       used and the allocated+initialization is done inline.
 * >>     addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
 * >> 2:
 * >> }}
 * >>     testP  %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     jz     .Lall_buffers_are_in_band
 * >>     movP   $<cg_service>,      %R_fcall0P
 * >>     movP   %R_temp_exbuf_size, %R_fcall1P
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %R_fcall1P, %Pax   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy out-of-band in/inout buffers into SHM memory
 * >> #if cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdi  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pcx  # `struct userprocmask *upm'
 * >>     movP   %Pdi, userprocmask::pm_sigmask(%Pcx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pcx)
 * >>     jnz    .Ltest_pending_signals_after_xbuf_alloc
 * >> .Ltest_pending_signals_after_xbuf_alloc_return:
 * >>     movP   %Pax, %Pdi                               # Unconditionally use %Pdi for copying!
 * >>     movP   service_shm_handle::ssh_shm(%Pdx), %Pdx  # %Pdx is the base address of the out-of-band buffer SHM mapping
 * >> {foreach[IN_INOUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >> #if IS_FIRST_INOUT_BUFFER(INDEX)
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >>
 * >>     # Set: %Pax = SHM_ADDR - SHM_BASE  (offset in SHM to input buffer)
 * >>     # NOTE: We don't have to about output buffers, since those appear after in/inout buffers
 * >>     movP   %Pdi, %Pax
 * >>     subP   %Pdx, %Pax
 * >>     movP   %Pax, <cbp_serial_offset>(%Psp)          # Store SHM offset in serial data
 * >>
 * >>     movP   <cbp_param_offset>(%Psp), %Psi           # Unconditionally use %Psi for copying!
 * >>     movP   ...,                      %Pcx           # required buffer size (depending on buffer type)
 * >>     rep    movsb                                    # Copy input buffers into SHM
 * >> 1:
 * >> }}
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled
 * >> #endif // cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Lall_buffers_are_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Ltest_pending_signals_after_all_buffers_are_in_band
 * >> .Lall_buffers_are_in_band_preemption_reenabled: */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments_n)(struct com_generator *__restrict self) {
	/* TODO */
	(void)self;
	abort();
}




/* Generate instructions:
 * >> #if cg_buf_paramc == 0
 * >> ...
 * >> #elif cg_buf_paramc == 1
 * >> ...
 * >> #else // #elif cg_buf_paramc >= 2
 * >> ...
 * >> #endif // #endif cg_buf_paramc >= 2
 */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_serialize_buffer_arguments)(struct com_generator *__restrict self) {
	switch (self->cg_buf_paramc) {
	case 0:
		comgen_serialize_buffer_arguments_0(self);
		break;
	case 1:
		comgen_serialize_buffer_arguments_1(self);
		break;
	default:
		comgen_serialize_buffer_arguments_n(self);
		break;
	}
}












/************************************************************************/
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_apply_relocations)(struct com_generator *__restrict self) {
	uint8_t i;
	for (i = 0; i < self->cg_nrelocs; ++i) {
		byte_t *addr;
		uintptr_t value;
		value = (uintptr_t)(addr = self->cg_txbas);
		addr += self->cg_relocs[i].cr_offset;
		value += self->cg_symbols[self->cg_relocs[i].cr_symbol];
		assertf(self->cg_symbols[self->cg_relocs[i].cr_symbol] != 0,
		        "Undefined symbol: %u", self->cg_relocs[i].cr_symbol);
		switch (self->cg_relocs[i].cr_type) {

		case COM_R_PCREL32:
			/* [*(s32 *)ADDR += (32)(u32)(VALUE - (uintptr_t)ADDR)] PC-relative, 32-bit */
			*(s32 *)addr += (s32)(u32)(value - (uintptr_t)addr);
			break;

		case COM_R_ABSPTR:
			/* [*(uintptr_t *)ADDR += VALUE] Absolute, pointer-sized */
			*(uintptr_t *)addr += value;
			break;

		default: __builtin_unreachable();
		}
	}
}
/************************************************************************/



/* Initializer pattern for com function .eh_frame data. */
PRIVATE struct com_eh_frame const eh_frame_pattern = {
	.cef_cie_size = 0, /* Should be `offsetof(struct com_eh_frame, cef_fde_size)', but only  set
	                    * as such on compilation success. Until that point, this being `0'  will
	                    * tell other pieces of code which may  already be making use of the  eh-
	                    * frame data buffer we're using, that the section ends here, rather than
	                    * containing the (not fully initialized) unwind descriptor found  below. */
	.cef_cie_id        = 0,
	.cef_cie_version   = 1,
	.cef_cie_augstr    = { 'z', 'L', 'P' },
	.cef_cie_codealign = 1,
#ifdef __x86_64__
	.cef_cie_dataalign = 0x78,
	.cef_cie_retreg    = CFI_X86_64_UNWIND_REGISTER_RIP,
	.cef_cie_auglen    = 9,
#else /* __x86_64__ */
	.cef_cie_dataalign = 0x7c,
	.cef_cie_retreg    = CFI_386_UNWIND_REGISTER_EIP,
	.cef_cie_auglen    = 5,
#endif /* !__x86_64__ */
	.cef_cie_lsdaenc   = DW_EH_PE_absptr,
	.cef_cie_persoenc  = DW_EH_PE_absptr,
	.cef_cie_persoptr  = NULL, /* Dynamically filled */
	/* CIE init text would go here... */

	/* FDE */
	.cef_fde_size      = 0, /* Dynamically filled */
	.cef_fde_cie_off   = offsetof(struct com_eh_frame, cef_fde_cie_off),
	.cef_fde_funbase   = NULL, /* Dynamically filled */
	.cef_fde_funsize   = 0,    /* Dynamically filled */
	.cef_fde_auglen    = sizeof(void *),
	.cef_fde_lsda      = NULL, /* Dynamically filled */
};


/* Do the initial setup of .eh_frame */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL comgen_eh_frame_setup)(struct com_generator *__restrict self) {
	/* Fill in the .eh_frame description header. */
	struct com_eh_frame *eh_hdr = (struct com_eh_frame *)self->cg_ehbas;
	memcpy(eh_hdr, &eh_frame_pattern, offsetof(struct com_eh_frame, cef_fde_text));
	self->cg_ehptr = eh_hdr->cef_fde_text;
}

extern void __gcc_personality_v0(void);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL comgen_eh_frame_finish)(struct com_generator *__restrict self) {
	/* Finalize the .eh_frame description header. */
	struct com_eh_frame *eh_hdr = (struct com_eh_frame *)self->cg_ehbas;
	eh_hdr->cef_cie_persoptr = (void *)&__gcc_personality_v0;
	eh_hdr->cef_fde_size     = (uint32_t)(size_t)(self->cg_ehptr - (byte_t *)&eh_hdr->cef_fde_size);
	eh_hdr->cef_fde_funbase  = self->cg_txbas;
	eh_hdr->cef_fde_funsize  = (size_t)(self->cg_txptr - self->cg_txbas);

	/* After the following write has been done, other threads may _immediatly_
	 * start to parse our newly generated unwind data, _as_ _well_ _as_ access
	 * the generated wrapper function.
	 * In a sense, making this write is a point-of-no-return */
	COMPILER_BARRIER();
	eh_hdr->cef_cie_size = offsetof(struct com_eh_frame, cef_fde_size);
	COMPILER_BARRIER();
}

/* Compile  the  com generator  wrapper function.  Upon return,
 * the caller must check the status using `comgen_compile_st_*'
 * Only with both *_moretx and *_moreeh return `false' may  the
 * compile operation be  considered successful. Otherwise,  the
 * respective need-more-memory condition should be handled.
 *
 * @return: true:  Compilation succeed (you may assume `comgen_compile_isok(self) == true')
 * @return: false: Compilation failed due to lack of .text- or  .eh_frame-memory
 *                 Check which is the case with `comgen_compile_st_moretx()' and
 *                 `comgen_compile_st_moreeh()'
 *
 * NOTE: Upon  success, the  used EH  buffer size  will indicate 4
 *       bytes more than should actually be accounted as belonging
 *       to the associated function. These bytes may not be freed,
 *       but should be overwritten  (iow: passed as `cg_ehbas'  in
 *       some  future compilation operation),  as they represent a
 *       sentinel marker in unwind debug data.
 *       The implementation of  this function takes  care to  maintain
 *       the  sentinel until the  point in time when  eh data has been
 *       finalized, at which point other threads may immediately begin
 *       parsing generated debug data.
 *       Until  that point,  the sentinel  must be  kept to prevent
 *       other threads from accessing incomplete debug information! */
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL comgen_compile)(struct com_generator *__restrict self) {
	/* Assert that the given buffer meets the minimum size requirements. */
	assert((size_t)(self->cg_txend - self->cg_txbas) >= COM_GENERATOR_INITIAL_TX_BUFSIZ);
	assert((size_t)(self->cg_ehend - self->cg_ehbas) >= COM_GENERATOR_INITIAL_EH_BUFSIZ);
	self->cg_txptr      = self->cg_txbas;
	self->cg_nrelocs    = 0;
	self->cg_CFA_loc    = self->cg_txptr;
	comgen_eh_frame_setup(self);
	comgen_eh_DW_CFA_def_cfa(self, CFI_X86_UNWIND_REGISTER_PSP, sizeof(void *));

	/* Generate the unconditional push instructions at the start of the wrapper. */
	comgen_push_registers_on_entry(self);

	/* Allocate space for local variables */
	comgen_allocate_stack_space(self);

	/* Disable preemption */
	comgen_disable_preemption(self);

	/* Allocate the com buffer */
	comgen_allocate_com_buffer(self);

	/* Serialize buffer arguments */
	comgen_serialize_buffer_arguments(self);

	/* TODO: All of the stuff that's missing */
	(void)self;
	abort();

	/* TODO: Generate LSDA (like it would appear in .gcc_except_table)
	 *       This data we simply put into .text (even though it doesn't
	 *       need to be executable, doing so is the easiest way for us
	 *       to define it) */

	/* Do one last check if everything went OK */
	if (!comgen_compile_isok(self))
		goto fail;

	/* Apply relocations. (this can't fail, so
	 * we can do it after the last isok check!) */
	comgen_apply_relocations(self);

	/* Finalize the eh_frame descriptor. This _must_ be done last, as
	 * this operation includes a point-of-no-return, as it (may) make
	 * the newly generated function (and its unwind data) visible  to
	 * other threads. */
	comgen_eh_frame_finish(self);
	return true;
fail:
	return false;
}





DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
