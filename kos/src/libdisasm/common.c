/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_LIBDISASM_COMMON_C
#define GUARD_LIBDISASM_COMMON_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/typecore.h>

#include <kos/except.h>
#include <kos/exec/module.h>

#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/addr2line.h>

#include "common.h"

#if (defined(DISASSEMBLER_TARGET_8086) || \
     defined(DISASSEMBLER_TARGET_I386) || \
     defined(DISASSEMBLER_TARGET_X86_64))
#include "x86.h"
#endif /* X86... */

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */


DECL_BEGIN

/* Quick and simple function for disassembling text into a given printer.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_until(&da, (byte_t *)pc + num_bytes);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm(pformatprinter printer, void *arg, void *pc, size_t num_bytes,
             uintptr_half_t target, uintptr_half_t flags) {
	struct disassembler da;
	disasm_init(&da, printer, arg, pc, target, flags, 0);
	return libda_disasm_print_until(&da,
	                                (byte_t *)pc + num_bytes);
}


/* Quick and simple function for disassembling a single instruction.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_instruction(&da);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_single(pformatprinter printer, void *arg, void *pc,
                    uintptr_half_t target, uintptr_half_t flags) {
	struct disassembler da;
	disasm_init(&da, printer, arg, pc, target, flags, 0);
	return libda_disasm_print_instruction(&da);
}


/* Disassembly and print lines (s.a. `disasm_print_line()') until `endpc'
 * has been reached, or a printer error has occurred.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_print_until(struct disassembler *__restrict self,
                         void const *endpc) {
	while (self->d_result >= 0 &&
	       (byte_t *)self->d_pc < (byte_t *)endpc)
		libda_disasm_print_line(self);
	return self->d_result;
}

/* Disassemble a single  instruction line, following  formatting rules  specified
 * by `DISASSEMBLER_F*', potentially printing multiple lines of the instruction's
 * bytes don't all fit into a single line (s.a. `').
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_print_line(struct disassembler *__restrict self) {
	libda_disasm_print_line_nolf(self);
	disasm_print(self, "\n", 1);
	return self->d_result;
}

/* Same as `libda_disasm_print_line()', but don't print a trailing line-feed. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_print_line_nolf(struct disassembler *__restrict self) {
	if (!(self->d_flags & DISASSEMBLER_FNOADDR))
		disasm_printf(self, "%p: ", self->d_pc + self->d_baseoff);
	if (!(self->d_flags & DISASSEMBLER_FNOBYTES)) {
		size_t instrlen, i;
		byte_t *bytes_base;
		if (!self->d_maxbytes)
			self->d_maxbytes = libda_disasm_default_maxbytes(self->d_target);
		instrlen = libda_disasm_instrlen(self);
		/* Bytes within the first line. */
		bytes_base = self->d_pc;
		i = 0;
		for (; i < self->d_maxbytes && i < instrlen; ++i)
			disasm_printf(self, "%.2I8x ", bytes_base[i]);
		if (i < self->d_maxbytes) {
			ssize_t temp;
			temp = format_repeat(self->d_printer, self->d_arg, ' ',
			                     (size_t)(self->d_maxbytes - i) * 3);
			if unlikely(temp < 0) {
				self->d_result = temp;
				goto done;
			}
			self->d_result += temp;
		}

		/* Print the actual instruction. */
		libda_disasm_print_instruction(self);
		instrlen = (size_t)(self->d_pc - bytes_base);
		/* Print additional instruction bytes in secondary lines. */
		while (i < instrlen) {
			size_t j;
			disasm_print(self, "\n", 1);
#if __SIZEOF_POINTER__ == 4
			disasm_print(self, "          ", 10);
#elif __SIZEOF_POINTER__ == 8
			disasm_print(self, "                  ", 18);
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported __SIZEOF_POINTER__"
#endif /* __SIZEOF_POINTER__ != ... */
			for (j = 0; j < self->d_maxbytes && i < instrlen; ++j, ++i)
				disasm_printf(self, "%.2I8x ", bytes_base[i]);
		}
	} else {
		libda_disasm_print_instruction(self);
	}
done:
	return self->d_result;
}

/* Disassemble a single instruction, including its mnemonic, and all operands.
 * This  function does not include any prefix,  nor does it append a trailing.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_print_instruction(struct disassembler *__restrict self) {
	switch (self->d_target) {

#if (defined(DISASSEMBLER_TARGET_8086) || \
     defined(DISASSEMBLER_TARGET_I386) || \
     defined(DISASSEMBLER_TARGET_X86_64))
#ifdef DISASSEMBLER_TARGET_8086
	case DISASSEMBLER_TARGET_8086:
#endif /* DISASSEMBLER_TARGET_8086 */
#ifdef DISASSEMBLER_TARGET_I386
	case DISASSEMBLER_TARGET_I386:
#endif /* DISASSEMBLER_TARGET_I386 */
#ifdef DISASSEMBLER_TARGET_X86_64
	case DISASSEMBLER_TARGET_X86_64:
#endif /* DISASSEMBLER_TARGET_X86_64 */
		libda_single_x86(self);
		break;
#endif /* X86... */

	default:
		libda_single_generic(self);
		break;
	}
	return self->d_result;
}

INTERN NONNULL((1)) void CC
libda_single_generic(struct disassembler *__restrict self) {
	disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX);
	disasm_print(self, ".byte", 5);
	disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX);
	disasm_printf(self, " %#.2I8x", *self->d_pc++);
}

#undef CONFIG_LOOKUP_SYMBOL_NAME
#define CONFIG_LOOKUP_SYMBOL_NAME 1


#ifdef CONFIG_LOOKUP_SYMBOL_NAME
#ifndef __KERNEL__
PRIVATE void *pdyn_libdebuginfo = NULL;
PRIVATE ATTR_NOINLINE WUNUSED void *CC get_libdebuginfo(void) {
	void *result;
again:
	result = ATOMIC_READ(pdyn_libdebuginfo);
	if (result == (void *)-1)
		return NULL;
	if (!result) {
		result = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL);
		if (!result)
			result = (void *)-1;
		if (!ATOMIC_CMPXCH(pdyn_libdebuginfo, NULL, result)) {
			if (result != (void *)-1)
				dlclose(result);
			goto again;
		}
	}
	return result;
}

PRIVATE PDEBUG_ADDR2LINE_SECTIONS_LOCK     pdyn_debug_addr2line_sections_lock     = NULL;
PRIVATE PDEBUG_ADDR2LINE_SECTIONS_UNLOCK   pdyn_debug_addr2line_sections_unlock   = NULL;
PRIVATE PDEBUG_ADDR2LINE pdyn_debug_addr2line = NULL;

#define debug_addr2line_sections_lock     (*pdyn_debug_addr2line_sections_lock)
#define debug_addr2line_sections_unlock   (*pdyn_debug_addr2line_sections_unlock)
#define debug_addr2line (*pdyn_debug_addr2line)

PRIVATE ATTR_NOINLINE WUNUSED bool CC init_libdebuginfo(void) {
	void *lib;
	if (pdyn_debug_addr2line_sections_lock)
		return true;
	lib = get_libdebuginfo();
	if (!lib)
		return false;
	*(void **)&pdyn_debug_addr2line = dlsym(lib, "debug_addr2line");
	if unlikely(!pdyn_debug_addr2line)
		return false;
	*(void **)&pdyn_debug_addr2line_sections_unlock = dlsym(lib, "debug_addr2line_sections_unlock");
	if unlikely(!pdyn_debug_addr2line_sections_unlock)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_debug_addr2line_sections_lock = dlsym(lib, "debug_addr2line_sections_lock");
	if unlikely(!pdyn_debug_addr2line_sections_lock)
		return false;
	return true;
}


__attribute__((__destructor__))
PRIVATE void fini_libdebuginfo() {
	if (pdyn_libdebuginfo && pdyn_libdebuginfo != (void *)-1)
		dlclose(pdyn_libdebuginfo);
};

#endif /* !__KERNEL__ */
#endif /* CONFIG_LOOKUP_SYMBOL_NAME */

PRIVATE WUNUSED ATTR_CONST unsigned int CC
address_width(uintptr_half_t target) {
	switch (target) {

#ifdef DISASSEMBLER_TARGET_8086
	case DISASSEMBLER_TARGET_8086:
		return 4;
#endif /* DISASSEMBLER_TARGET_8086 */

#ifdef DISASSEMBLER_TARGET_I386
	case DISASSEMBLER_TARGET_I386:
		return 8;
#endif /* DISASSEMBLER_TARGET_I386 */

#ifdef DISASSEMBLER_TARGET_X86_64
	case DISASSEMBLER_TARGET_X86_64:
		return 16;
#endif /* DISASSEMBLER_TARGET_X86_64 */

	default:
		break;
	}
	return sizeof(void *) * 2;
}

/* Print the name+offset/address of a symbol at `symbol_addr'
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTERN NONNULL((1)) ssize_t CC
libda_disasm_print_symbol(struct disassembler *__restrict self,
                          void *symbol_addr) {
	if likely(self->d_result >= 0) {
		disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_PREFIX);
		if (self->d_symbol) {
			ssize_t error;
			error = (*self->d_symbol)(self, symbol_addr);
			if unlikely(error < 0)
				self->d_result = error;
			else {
				self->d_result += error;
			}
		} else {
#ifdef CONFIG_LOOKUP_SYMBOL_NAME
#ifndef __KERNEL__
			if (init_libdebuginfo())
#else /* !__KERNEL__ */
			__IF1
#endif /* __KERNEL__ */
			{
				/* Use pdyn_libdebuginfo as source for symbol names. */
				di_debug_addr2line_t a2l_info;
				di_addr2line_sections_t dbg_sect;
				di_addr2line_dl_sections_t dl_sect;
				REF module_t *symbol_module;
				module_type_var(symbol_module_type);
				symbol_module = module_ataddr_nx(symbol_addr, symbol_module_type);
				if (!symbol_module)
					goto generic_print_symbol_addr;
				TRY {
					if (debug_addr2line_sections_lock(symbol_module, &dbg_sect, &dl_sect
					                                  module_type__arg(symbol_module_type)) !=
					    DEBUG_INFO_ERROR_SUCCESS) {
						module_decref(symbol_module, symbol_module_type);
						goto generic_print_symbol_addr;
					}
					TRY {
						uintptr_t loadaddr;
						uintptr_t symbol_offset;
						loadaddr = module_getloadaddr(symbol_module, symbol_module_type);
						if (debug_addr2line(&dbg_sect, &a2l_info,
						                    (uintptr_t)symbol_addr - loadaddr,
						                    DEBUG_ADDR2LINE_LEVEL_SOURCE,
						                    DEBUG_ADDR2LINE_FNORMAL) != DEBUG_INFO_ERROR_SUCCESS) {
							module_decref(symbol_module, symbol_module_type);
							debug_addr2line_sections_unlock(&dl_sect module_type__arg(symbol_module_type));
							goto generic_print_symbol_addr;
						}
						if (!a2l_info.al_rawname)
							a2l_info.al_rawname = a2l_info.al_name;
						if (a2l_info.al_rawname && !*a2l_info.al_rawname)
							a2l_info.al_rawname = NULL;
						disasm_print(self, "<", 1);
						if (a2l_info.al_rawname) {
							disasm_printf(self, "%s", a2l_info.al_rawname);
						} else {
							/* If we can't determine the symbol's name, generate one using its address. */
							disasm_printf(self, "sym_%.*p",
							              address_width(self->d_target),
							              a2l_info.al_symstart + loadaddr);
						}
						/* Include the symbol offset (if non-zero) */
						symbol_offset = (uintptr_t)((byte_t *)symbol_addr -
						                            (byte_t *)(a2l_info.al_symstart + loadaddr));
						if (symbol_offset != 0)
							disasm_printf(self, "+%#" PRIxPTR, symbol_offset);
						disasm_print(self, ">", 1);
					} EXCEPT {
						debug_addr2line_sections_unlock(&dl_sect module_type__arg(symbol_module_type));
						RETHROW();
					}
					debug_addr2line_sections_unlock(&dl_sect module_type__arg(symbol_module_type));
				} EXCEPT {
					module_decref(symbol_module,
					              symbol_module_type);
					RETHROW();
				}
				module_decref(symbol_module,
				              symbol_module_type);
			} else
generic_print_symbol_addr:
#endif /* CONFIG_LOOKUP_SYMBOL_NAME */
			{
#ifdef CONFIG_LOOKUP_SYMBOL_NAME
#ifndef __KERNEL__
				Dl_info info;
				if (dladdr(symbol_addr, &info) == 0 &&
				    info.dli_sname != NULL && *info.dli_sname) {
					/* Use DL symbol information as source for symbol names. */
					disasm_printf(self, "<%s+%#Ix>", info.dli_sname,
					              (uintptr_t)((byte_t *)symbol_addr - (byte_t *)info.dli_saddr));
				} else
#endif /* !__KERNEL__ */
#endif /* CONFIG_LOOKUP_SYMBOL_NAME */
				{
					disasm_printf(self, "%#.*p",
					              address_width(self->d_target),
					              symbol_addr);
				}
			}
		}
		disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_SUFFIX);
	}
	return self->d_result;
}



PRIVATE ssize_t
NOTHROW(FORMATPRINTER_CC stub_printer)(void *UNUSED(arg),
                                       /*utf-8*/ char const *__restrict UNUSED(data),
                                       size_t UNUSED(datalen)) {
	return 0;
}

PRIVATE ssize_t
NOTHROW(LIBDISASM_CC stub_symbol_printer)(struct disassembler *__restrict UNUSED(self),
                                          void *UNUSED(symbol_addr)) {
	return 0;
}


/* Returns the length (in bytes) of the next instruction to-be disassembled. */
INTERN NONNULL((1)) size_t CC
libda_disasm_instrlen(struct disassembler *__restrict self) {
	byte_t *oldpc;
	size_t result;
	ssize_t oldresult;
	pformatprinter old_printer;
	diasm_symbol_printer_t old_symbol_printer;
	byte_t padbuf[sizeof(self->d_pad0) + sizeof(self->d_pad1)];
	__STATIC_IF (offsetafter(struct disassembler, d_pad0) == offsetof(struct disassembler, d_pad1)) {
		memcpy(padbuf, &self->d_pad0, sizeof(padbuf));
	} __STATIC_ELSE (offsetafter(struct disassembler, d_pad0) == offsetof(struct disassembler, d_pad1)) {
		memcpy(padbuf, &self->d_pad0, sizeof(self->d_pad0));
		memcpy(padbuf + sizeof(self->d_pad0), self->d_pad1, sizeof(self->d_pad1));
	}
	old_printer        = self->d_printer;
	oldpc              = self->d_pc;
	oldresult          = self->d_result;
	old_symbol_printer = self->d_symbol;
	self->d_result     = 0;
	self->d_printer    = &stub_printer;
	self->d_symbol     = &stub_symbol_printer;
	libda_disasm_print_instruction(self);
	result          = (size_t)(self->d_pc - oldpc);
	self->d_symbol  = old_symbol_printer;
	self->d_printer = old_printer;
	self->d_result  = oldresult;
	self->d_pc      = oldpc;
	__STATIC_IF (offsetafter(struct disassembler, d_pad0) == offsetof(struct disassembler, d_pad1)) {
		memcpy(&self->d_pad0, padbuf, sizeof(padbuf));
	} __STATIC_ELSE (offsetafter(struct disassembler, d_pad0) == offsetof(struct disassembler, d_pad1)) {
		memcpy(&self->d_pad0, padbuf, sizeof(self->d_pad0));
		memcpy(self->d_pad1, padbuf + sizeof(self->d_pad0), sizeof(self->d_pad1));
	}
	return result;
}

/* Return the default number of max instruction bytes to print for `target' */
INTERN ATTR_CONST uintptr_half_t CC
libda_disasm_default_maxbytes(uintptr_half_t target) {
	uintptr_half_t result;
	switch (target) {

#if (defined(DISASSEMBLER_TARGET_8086) || \
     defined(DISASSEMBLER_TARGET_I386) || \
     defined(DISASSEMBLER_TARGET_X86_64))
#ifdef DISASSEMBLER_TARGET_8086
	case DISASSEMBLER_TARGET_8086:
#endif /* DISASSEMBLER_TARGET_8086 */
#ifdef DISASSEMBLER_TARGET_I386
	case DISASSEMBLER_TARGET_I386:
#endif /* DISASSEMBLER_TARGET_I386 */
#ifdef DISASSEMBLER_TARGET_X86_64
	case DISASSEMBLER_TARGET_X86_64:
#endif /* DISASSEMBLER_TARGET_X86_64 */
		result = 5;
		break;
#endif /* X86... */

	default:
		result = 4;
		break;
	}
	return result;
}



DEFINE_PUBLIC_ALIAS(disasm, libda_disasm);
DEFINE_PUBLIC_ALIAS(disasm_single, libda_disasm_single);
DEFINE_PUBLIC_ALIAS(disasm_print_until, libda_disasm_print_until);
DEFINE_PUBLIC_ALIAS(disasm_print_line, libda_disasm_print_line);
DEFINE_PUBLIC_ALIAS(disasm_print_line_nolf, libda_disasm_print_line_nolf);
DEFINE_PUBLIC_ALIAS(disasm_print_instruction, libda_disasm_print_instruction);
DEFINE_PUBLIC_ALIAS(disasm_print_symbol, libda_disasm_print_symbol);
DEFINE_PUBLIC_ALIAS(disasm_instrlen, libda_disasm_instrlen);
DEFINE_PUBLIC_ALIAS(disasm_default_maxbytes, libda_disasm_default_maxbytes);

DECL_END

#endif /* !GUARD_LIBDISASM_COMMON_C */
