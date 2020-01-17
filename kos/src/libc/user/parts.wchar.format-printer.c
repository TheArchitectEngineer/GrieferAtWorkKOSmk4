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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_C
#define GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_C 1

#include "../api.h"
/**/

#include <string.h>

#include "malloc.h"
#include "parts.wchar.format-printer.h"
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:format_waprintf_pack,hash:CRC-32=0xfb24fc97]]]*/
/* Pack and finalize a given aprintf format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_waprintf_pack") char32_t *
NOTHROW_NCX(LIBCCALL libc_format_waprintf_pack)(struct format_c32aprintf_data *__restrict self,
                                                size_t *pstrlen)
/*[[[body:format_waprintf_pack]]]*/
/*AUTO*/{
	/* Free unused buffer memory. */
	char32_t *result;
	if (self->ap_avail != 0) {
		char32_t *newbuf;
		newbuf = (char32_t *)libc_realloc(self->ap_base,
		                         (self->ap_used + 1) * sizeof(char32_t));
		if likely(newbuf)
			self->ap_base = newbuf;
	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);
#ifdef __CRT_HAVE_malloc
			self->ap_base = (char32_t *)libc_malloc(1 * sizeof(char32_t));
#else /* __CRT_HAVE_malloc */
			self->ap_base = (char32_t *)libc_realloc(NULL, 1 * sizeof(char32_t));
#endif /* !__CRT_HAVE_malloc */
			if unlikely(!self->ap_base)
				return NULL;
		}
	}
	result = self->ap_base;
	__hybrid_assert(result);
	result[self->ap_used] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->ap_used;
#ifndef NDEBUG
#if __SIZEOF_POINTER__ == 4
	self->ap_base  = (char32_t *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char32_t *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !NDEBUG */
	return result;
}
/*[[[end:format_waprintf_pack]]]*/

/*[[[head:DOS$format_waprintf_pack,hash:CRC-32=0x5a6cf992]]]*/
/* Pack and finalize a given aprintf format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_waprintf_pack") char16_t *
NOTHROW_NCX(LIBDCALL libd_format_waprintf_pack)(struct format_c16aprintf_data *__restrict self,
                                                size_t *pstrlen)
/*[[[body:DOS$format_waprintf_pack]]]*/
/*AUTO*/{
	/* Free unused buffer memory. */
	char16_t *result;
	if (self->ap_avail != 0) {
		char16_t *newbuf;
		newbuf = (char16_t *)libc_realloc(self->ap_base,
		                         (self->ap_used + 1) * sizeof(char16_t));
		if likely(newbuf)
			self->ap_base = newbuf;
	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);
#ifdef __CRT_HAVE_malloc
			self->ap_base = (char16_t *)libc_malloc(1 * sizeof(char16_t));
#else /* __CRT_HAVE_malloc */
			self->ap_base = (char16_t *)libc_realloc(NULL, 1 * sizeof(char16_t));
#endif /* !__CRT_HAVE_malloc */
			if unlikely(!self->ap_base)
				return NULL;
		}
	}
	result = self->ap_base;
	__hybrid_assert(result);
	result[self->ap_used] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->ap_used;
#ifndef NDEBUG
#if __SIZEOF_POINTER__ == 4
	self->ap_base  = (char16_t *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char16_t *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !NDEBUG */
	return result;
}
/*[[[end:DOS$format_waprintf_pack]]]*/

/*[[[head:format_waprintf_printer,hash:CRC-32=0x14d90401]]]*/
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_waprintf_printer") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_waprintf_printer)(/*struct format_waprintf_data **/ void *arg,
                                                   char32_t const *__restrict data,
                                                   size_t datalen)
/*[[[body:format_waprintf_printer]]]*/
/*AUTO*/{
	char32_t *buf;
	buf = libc_format_waprintf_alloc((struct format_c32aprintf_data *)arg, datalen);
	if unlikely(!buf)
		return -1;
	libc_wmemcpy(buf, data, datalen);
	return (ssize_t)datalen;
}
/*[[[end:format_waprintf_printer]]]*/

/*[[[head:DOS$format_waprintf_printer,hash:CRC-32=0x808c96c2]]]*/
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_waprintf_printer") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_waprintf_printer)(/*struct format_waprintf_data **/ void *arg,
                                                   char16_t const *__restrict data,
                                                   size_t datalen)
/*[[[body:DOS$format_waprintf_printer]]]*/
/*AUTO*/{
	char16_t *buf;
	buf = libd_format_waprintf_alloc((struct format_c16aprintf_data *)arg, datalen);
	if unlikely(!buf)
		return -1;
	libd_wmemcpy(buf, data, datalen);
	return (ssize_t)datalen;
}
/*[[[end:DOS$format_waprintf_printer]]]*/

/*[[[head:format_waprintf_alloc,hash:CRC-32=0x2a1ef99a]]]*/
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_waprintf_alloc") char32_t *
NOTHROW_NCX(LIBCCALL libc_format_waprintf_alloc)(struct format_c32aprintf_data *__restrict self,
                                                 size_t num_wchars)
/*[[[body:format_waprintf_alloc]]]*/
/*AUTO*/{
	char32_t *result;
	if (self->ap_avail < num_wchars) {
		char32_t *newbuf;
		size_t min_alloc = self->ap_used + num_wchars;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char32_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char32_t));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char32_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char32_t));
			if unlikely(!newbuf)
				return NULL;
		}
		__hybrid_assert(new_alloc >= self->ap_used + num_wchars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_wchars;
	self->ap_used  += num_wchars;
	return result;
}
/*[[[end:format_waprintf_alloc]]]*/

/*[[[head:DOS$format_waprintf_alloc,hash:CRC-32=0x8fd56030]]]*/
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_waprintf_alloc") char16_t *
NOTHROW_NCX(LIBDCALL libd_format_waprintf_alloc)(struct format_c16aprintf_data *__restrict self,
                                                 size_t num_wchars)
/*[[[body:DOS$format_waprintf_alloc]]]*/
/*AUTO*/{
	char16_t *result;
	if (self->ap_avail < num_wchars) {
		char16_t *newbuf;
		size_t min_alloc = self->ap_used + num_wchars;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char16_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char16_t));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char16_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char16_t));
			if unlikely(!newbuf)
				return NULL;
		}
		__hybrid_assert(new_alloc >= self->ap_used + num_wchars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_wchars;
	self->ap_used  += num_wchars;
	return result;
}
/*[[[end:DOS$format_waprintf_alloc]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf7c0034b]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(format_waprintf_pack, libc_format_waprintf_pack);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_waprintf_pack, libd_format_waprintf_pack);
DEFINE_PUBLIC_WEAK_ALIAS(format_waprintf_alloc, libc_format_waprintf_alloc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_waprintf_alloc, libd_format_waprintf_alloc);
DEFINE_PUBLIC_WEAK_ALIAS(format_waprintf_printer, libc_format_waprintf_printer);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_waprintf_printer, libd_format_waprintf_printer);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_C */
