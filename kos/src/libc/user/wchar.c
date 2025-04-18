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
#ifndef GUARD_LIBC_USER_WCHAR_C
#define GUARD_LIBC_USER_WCHAR_C 1

#include "../api.h"
/**/

#include <stdio.h>
#include <string.h>
#include <uchar.h>
#include <unicode.h>

#include <libc/unicode.h>

#include "../auto/parts.wchar.format-printer.h"
#include "../libc/globals.h"
#include "malloc.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"
#include "unicode.h"
#include "wchar.h"

DECL_BEGIN

#define file_print16 libd_file_wprinter_unlocked
#define file_print32 libc_file_wprinter_unlocked

/* The DOS version of wcstok() doesn't take the 3rd safe-ptr argument,
 * but rather only takes 2  arguments (under DOS, the 3-argument  form
 * carries the name `wcstok_s')
 * Define this special variant manually, since magic wouldn't  understand
 * some weird function that only exists in DOS-mode, but uses a name that
 * is bound to a different function in KOS-mode... */
PRIVATE ATTR_SECTION(".bss.crt.dos.wchar.string.memory")
char16_t *wcstok_safe_ptr = NULL;

DEFINE_PUBLIC_ALIAS(DOS$wcstok, libd_wcstok_nosafe);
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcstok_nosafe)(char16_t *string,
                                         char16_t const *__restrict delim) {
	return libd_wcstok(string, delim, &wcstok_safe_ptr);
}


/* Define the `_mb_shift' used and exported by libc4/5
 *
 * This one's used internally by `mbrtowc(3)' and `wcrtomb(3)' when the
 * caller doesn't supply their  own `mbstate_t *mbs' item, with  libc's
 * internally buffer for this having been exported by libc4/5.
 * -> As such, we do the same for binary compat. */
#undef _mb_shift
INTDEF mbstate_t libc__mb_shift;
INTERN ATTR_SECTION(".bss.crt.compat.linux") mbstate_t libc__mb_shift = MBSTATE_INIT;
DEFINE_PUBLIC_ALIAS(_mb_shift, libc__mb_shift);
#define _mb_shift GET_NOREL_GLOBAL(_mb_shift)





/*[[[head:libc_fgetwc_unlocked,hash:CRC-32=0xa9490e1d]]]*/
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc") ATTR_INOUT(1) wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_fgetwc_unlocked)(FILE *__restrict stream)
/*[[[body:libc_fgetwc_unlocked]]]*/
{
	wint32_t result;
	struct iofile_data *ex;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	ex     = stream->if_exdata;
	assert(ex);
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		char32_t ch32;
		int ch;
		ch = file_getc(stream);
		if (ch == EOF) {
			result = WEOF32;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc32(&ch32, buf, 1, &ex->io_mbs);
		result = (wint32_t)ch32;
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF32;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}
/*[[[end:libc_fgetwc_unlocked]]]*/

/*[[[head:libd_fgetwc_unlocked,hash:CRC-32=0x4364e3d1]]]*/
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc") ATTR_INOUT(1) wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_fgetwc_unlocked)(FILE *__restrict stream)
/*[[[body:libd_fgetwc_unlocked]]]*/
{
	wint16_t result;
	struct iofile_data *ex;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	ex     = stream->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		result = (char16_t)(0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff));
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
		goto done;
	}
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		char16_t ch16;
		int ch;
		ch = file_getc(stream);
		if (ch == EOF) {
			result = WEOF16;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc16(&ch16, buf, 1, &ex->io_mbs);
		result = (wint16_t)ch16;
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == 0) {
			/* Shouldn't happen (a surrogate was written) */
			if (file_ungetc(stream, (unsigned char)buf[0]) == EOF)
				result = WEOF16;
			goto done;
		}
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF16;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}
/*[[[end:libd_fgetwc_unlocked]]]*/

/*[[[head:libc_fgetwc,hash:CRC-32=0xba9e9f8e]]]*/
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc") ATTR_INOUT(1) wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_fgetwc)(FILE *__restrict stream)
/*[[[body:libc_fgetwc]]]*/
{
	wint32_t result;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libc_fgetwc_unlocked(stream);
		file_lock_endwrite(stream);
	} else {
		result = libc_fgetwc_unlocked(stream);
	}
	return result;
}
/*[[[end:libc_fgetwc]]]*/

/*[[[head:libd_fgetwc,hash:CRC-32=0x21a94341]]]*/
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc") ATTR_INOUT(1) wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_fgetwc)(FILE *__restrict stream)
/*[[[body:libd_fgetwc]]]*/
{
	wint16_t result;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libd_fgetwc_unlocked(stream);
		file_lock_endwrite(stream);
	} else {
		result = libd_fgetwc_unlocked(stream);
	}
	return result;
}
/*[[[end:libd_fgetwc]]]*/

/*[[[head:libc_ungetwc_unlocked,hash:CRC-32=0xcfff050d]]]*/
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") ATTR_INOUT(2) wint32_t
NOTHROW_NCX(LIBKCALL libc_ungetwc_unlocked)(wint32_t ch,
                                            FILE *__restrict stream)
/*[[[body:libc_ungetwc_unlocked]]]*/
{
	wint32_t result = ch;
	char buf[UNICODE_UTF8_CURLEN], *end;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	end = unicode_writeutf8(buf, (char32_t)ch);
	assert(end > buf);
	do {
		--end;
		if (file_ungetc(stream, (unsigned char)*end) == EOF) {
			result = WEOF32;
			break;
		}
	} while (end > buf);
	return result;
}
/*[[[end:libc_ungetwc_unlocked]]]*/

/*[[[head:libd_ungetwc_unlocked,hash:CRC-32=0xfd477e67]]]*/
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") ATTR_INOUT(2) wint16_t
NOTHROW_NCX(LIBDCALL libd_ungetwc_unlocked)(wint16_t ch,
                                            FILE *__restrict stream)
/*[[[body:libd_ungetwc_unlocked]]]*/
{
	char32_t unget_char;
	wint16_t result = ch;
	struct iofile_data *ex;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	ex = stream->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		char16_t lo_surrogate;
		if unlikely((char16_t)ch < UTF16_HIGH_SURROGATE_MIN ||
		            (char16_t)ch > UTF16_HIGH_SURROGATE_MAX) {
set_ilseq:
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF16;
			goto done;
		}
		lo_surrogate = (char16_t)(0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff));
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
		unget_char = (char32_t)(char16_t)ch;
		unget_char -= 0xd800;
		unget_char <<= 10;
		unget_char += 0x10000 - 0xdc00;
		unget_char += lo_surrogate;
	} else {
		if unlikely((char16_t)ch >= UTF16_HIGH_SURROGATE_MIN &&
		            (char16_t)ch <= UTF16_HIGH_SURROGATE_MAX)
			goto set_ilseq;
		unget_char = (char32_t)(char16_t)ch;
	}
	if (libc_ungetwc_unlocked(unget_char, stream) == WEOF32)
		result = WEOF16;
done:
	return result;
}
/*[[[end:libd_ungetwc_unlocked]]]*/

/*[[[head:libc_ungetwc,hash:CRC-32=0x3e4c27d6]]]*/
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") ATTR_INOUT(2) wint32_t
NOTHROW_NCX(LIBKCALL libc_ungetwc)(wint32_t wc,
                                   FILE *stream)
/*[[[body:libc_ungetwc]]]*/
{
	wint32_t result;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libc_ungetwc_unlocked(wc, stream);
		file_lock_endwrite(stream);
	} else {
		result = libc_ungetwc_unlocked(wc, stream);
	}
	return result;
}
/*[[[end:libc_ungetwc]]]*/

/*[[[head:libd_ungetwc,hash:CRC-32=0xd4d4df4a]]]*/
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") ATTR_INOUT(2) wint16_t
NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint16_t wc,
                                   FILE *stream)
/*[[[body:libd_ungetwc]]]*/
{
	wint16_t result;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libd_ungetwc_unlocked(wc, stream);
		file_lock_endwrite(stream);
	} else {
		result = libd_ungetwc_unlocked(wc, stream);
	}
	return result;
}
/*[[[end:libd_ungetwc]]]*/

/*[[[head:libc_fputwc_unlocked,hash:CRC-32=0xe2b8cfb0]]]*/
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") ATTR_INOUT(2) wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_fputwc_unlocked)(char32_t wc,
                                              FILE *__restrict stream)
/*[[[body:libc_fputwc_unlocked]]]*/
{
	wint32_t result = (wint32_t)wc;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	if (file_print32(stream, &wc, 1) <= 0)
		result = WEOF32;
	return result;
}
/*[[[end:libc_fputwc_unlocked]]]*/

/*[[[head:libd_fputwc_unlocked,hash:CRC-32=0x36b55701]]]*/
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") ATTR_INOUT(2) wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_fputwc_unlocked)(char16_t wc,
                                              FILE *__restrict stream)
/*[[[body:libd_fputwc_unlocked]]]*/
{
	wint16_t result = (wint16_t)wc;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	if (file_print16(stream, &wc, 1) <= 0)
		result = WEOF16;
	return result;
}
/*[[[end:libd_fputwc_unlocked]]]*/

/*[[[head:libc_fputwc,hash:CRC-32=0x7faf09c8]]]*/
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") ATTR_INOUT(2) wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_fputwc)(char32_t wc,
                                     FILE *stream)
/*[[[body:libc_fputwc]]]*/
{
	ssize_t error;
	wint32_t result = (wint32_t)wc;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF32(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		error = file_print32(stream, &wc, 1);
		file_lock_endwrite(stream);
	} else {
		error = file_print32(stream, &wc, 1);
	}
	if (error <= 0)
		result = WEOF32;
	return result;
}
/*[[[end:libc_fputwc]]]*/

/*[[[head:libd_fputwc,hash:CRC-32=0x4fb26230]]]*/
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") ATTR_INOUT(2) wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_fputwc)(char16_t wc,
                                     FILE *stream)
/*[[[body:libd_fputwc]]]*/
{
	ssize_t error;
	wint16_t result = (wint16_t)wc;
	if unlikely(!stream)
		return libc_seterrno_and_return_WEOF16(EINVAL);
	stream = file_fromuser(stream);
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		error = file_print16(stream, &wc, 1);
		file_lock_endwrite(stream);
	} else {
		error = file_print16(stream, &wc, 1);
	}
	if (error <= 0)
		result = WEOF16;
	return result;
}
/*[[[end:libd_fputwc]]]*/

/*[[[head:libc_open_wmemstream,hash:CRC-32=0xf53c4d2d]]]*/
/* >> open_wmemstream(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") FILE *
NOTHROW_NCX(LIBKCALL libc_open_wmemstream)(char32_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:libc_open_wmemstream]]]*/
/*AUTO*/{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTEDF("open_wmemstream(bufloc: %p, sizeloc: %p)", bufloc, sizeloc); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_open_wmemstream]]]*/

/*[[[head:libd_open_wmemstream,hash:CRC-32=0xc95e5f0e]]]*/
/* >> open_wmemstream(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") FILE *
NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:libd_open_wmemstream]]]*/
/*AUTO*/{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTEDF("DOS$open_wmemstream(bufloc: %p, sizeloc: %p)", bufloc, sizeloc); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_open_wmemstream]]]*/












/*[[[head:libd_fgetwln,hash:CRC-32=0x5f428ce3]]]*/
/* >> fgetwln(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd_fgetwln)(FILE *__restrict stream,
                                   size_t *__restrict lenp)
/*[[[body:libd_fgetwln]]]*/
{
	size_t i, bufsiz;
	char16_t *result;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return NULL;
	}
	stream = file_fromuser(stream);
	if (FEOF(stream)) /* XXX: Also do this on FERROR()? */
		return NULL;  /* Must return `NULL' after EOF */
	result = (char16_t *)stream->if_exdata->io_getln;
	if (!result) {
		result = (char16_t *)malloc(IOBUF_MIN, sizeof(char16_t));
		if unlikely(!result)
			return NULL;
		stream->if_exdata->io_getln = (char *)result;
	}
	bufsiz = malloc_usable_size(result) / sizeof(char16_t);
	assert(bufsiz != 0);
	for (i = 0;; ++i) {
		wint16_t ch;
		if (i >= bufsiz - 1) {
			/* Allocate larger buffer. */
			size_t new_bufsiz = bufsiz * 2;
			char16_t *new_result;
			new_result = (char16_t *)realloc(result, new_bufsiz, sizeof(char16_t));
			if unlikely(!new_result) {
				new_bufsiz = i + 2;
				new_result = (char16_t *)realloc(result, new_bufsiz, sizeof(char16_t));
				if unlikely(!new_result)
					return NULL;
			}
			result = new_result;
			bufsiz = malloc_usable_size(result) / sizeof(char16_t);
			assert(bufsiz >= new_bufsiz);
			stream->if_exdata->io_getln = (char *)result;
		}
		ch = libd_fgetwc_unlocked(stream);
		if (ch == WEOF32)
			break; /* End-of-file */
		if (ch == (wint16_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			result[i++] = (char16_t)'\n';
			ch = libd_fgetwc_unlocked(stream);
			if (ch == (wint16_t)WEOF32)
				break;
			if (ch == (wint16_t)'\r')
				continue;
			libd_ungetwc_unlocked(ch, stream);
			break;
		}
		result[i] = (char16_t)ch;
		if (ch == (wint16_t)'\n') {
			++i; /* Must keep the trailing '\n' at the end of lines! */
			break;
		}
	}

	/* Special case: absolutely _must_ return `NULL' on EOF */
	if (i == 0)
		return NULL;

	/* NUL-terminate line.
	 * NOTE: This is actually a KOS extension, as BSD's fgetln()
	 *       documents that it  doesn't NUL-terminate the  line! */
	result[i] = '\0';

	/* KOS extension: we make the `lenp' argument optional. */
	if (lenp != NULL)
		*lenp = i;
	return result;
}
/*[[[end:libd_fgetwln]]]*/

/*[[[head:libc_fgetwln,hash:CRC-32=0x8015928a]]]*/
/* >> fgetwln(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc_fgetwln)(FILE *__restrict stream,
                                   size_t *__restrict lenp)
/*[[[body:libc_fgetwln]]]*/
{
	size_t i, bufsiz;
	char32_t *result;
	if unlikely(!stream) {
		(void)libc_seterrno(EINVAL);
		return NULL;
	}
	stream = file_fromuser(stream);
	if (FEOF(stream)) /* XXX: Also do this on FERROR()? */
		return NULL;  /* Must return `NULL' after EOF */
	result = (char32_t *)stream->if_exdata->io_getln;
	if (!result) {
		result = (char32_t *)malloc(IOBUF_MIN, sizeof(char32_t));
		if unlikely(!result)
			return NULL;
		stream->if_exdata->io_getln = (char *)result;
	}
	bufsiz = malloc_usable_size(result) / sizeof(char32_t);
	assert(bufsiz != 0);
	for (i = 0;; ++i) {
		wint32_t ch;
		if (i >= bufsiz - 1) {
			/* Allocate larger buffer. */
			size_t new_bufsiz = bufsiz * 2;
			char32_t *new_result;
			new_result = (char32_t *)realloc(result, new_bufsiz, sizeof(char32_t));
			if unlikely(!new_result) {
				new_bufsiz = i + 2;
				new_result = (char32_t *)realloc(result, new_bufsiz, sizeof(char32_t));
				if unlikely(!new_result)
					return NULL;
			}
			result = new_result;
			bufsiz = malloc_usable_size(result) / sizeof(char32_t);
			assert(bufsiz >= new_bufsiz);
			stream->if_exdata->io_getln = (char *)result;
		}
		ch = libc_fgetwc_unlocked(stream);
		if (ch == WEOF32)
			break; /* End-of-file */
		if (ch == (wint32_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			result[i++] = (char32_t)'\n';
			ch = libc_fgetwc_unlocked(stream);
			if (ch == (wint32_t)WEOF32)
				break;
			if (ch == (wint32_t)'\r')
				continue;
			libc_ungetwc_unlocked(ch, stream);
			break;
		}
		result[i] = (char32_t)ch;
		if (ch == (wint32_t)'\n') {
			++i; /* Must keep the trailing '\n' at the end of lines! */
			break;
		}
	}

	/* Special case: absolutely _must_ return `NULL' on EOF */
	if (i == 0)
		return NULL;

	/* NUL-terminate line.
	 * NOTE: This is actually a KOS extension, as BSD's fgetln()
	 *       documents that it  doesn't NUL-terminate the  line! */
	result[i] = '\0';

	/* KOS extension: we make the `lenp' argument optional. */
	if (lenp != NULL)
		*lenp = i;
	return result;
}
/*[[[end:libc_fgetwln]]]*/





/*[[[head:libc_file_wprinter,hash:CRC-32=0x98d00812]]]*/
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_CB_NCX(LIBKCALL libc_file_wprinter)(void *arg,
                                            char32_t const *__restrict data,
                                            size_t datalen)
/*[[[body:libc_file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = file_fromuser((FILE *)arg);
	if (FMUSTLOCK(me)) {
		file_lock_write(me);
		result = file_print32(arg, data, datalen);
		file_lock_endwrite(me);
	} else {
		result = file_print32(arg, data, datalen);
	}
	return result;
}
/*[[[end:libc_file_wprinter]]]*/

/*[[[head:libc_file_wprinter_unlocked,hash:CRC-32=0x6fa76ae]]]*/
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_CB_NCX(LIBKCALL libc_file_wprinter_unlocked)(void *arg,
                                                     char32_t const *__restrict data,
                                                     size_t datalen)
/*[[[body:libc_file_wprinter_unlocked]]]*/
{
	struct format_32to8_data format;
	format.fd_printer = &libc_file_printer_unlocked;
	format.fd_arg     = arg;
	return libc_format_wto8(&format, data, datalen);
}
/*[[[end:libc_file_wprinter_unlocked]]]*/

/*[[[head:libd_file_wprinter,hash:CRC-32=0x465bf114]]]*/
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_CB_NCX(LIBDCALL libd_file_wprinter)(void *arg,
                                            char16_t const *__restrict data,
                                            size_t datalen)
/*[[[body:libd_file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = file_fromuser((FILE *)arg);
	if (FMUSTLOCK(me)) {
		file_lock_write(me);
		result = file_print16(arg, data, datalen);
		file_lock_endwrite(me);
	} else {
		result = file_print16(arg, data, datalen);
	}
	return result;
}
/*[[[end:libd_file_wprinter]]]*/

/*[[[head:libd_file_wprinter_unlocked,hash:CRC-32=0xa0674ecc]]]*/
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_CB_NCX(LIBDCALL libd_file_wprinter_unlocked)(void *arg,
                                                     char16_t const *__restrict data,
                                                     size_t datalen)
/*[[[body:libd_file_wprinter_unlocked]]]*/
{
	ssize_t result;
	struct format_16to8_data format;
	struct iofile_data *ex;
	FILE *me;
	me = file_fromuser((FILE *)arg);
	ex = me->if_exdata;
	assert(ex);
	format.fd_arg       = arg;
	format.fd_printer   = &libc_file_printer_unlocked;
	format.fd_surrogate = 0;
	/* Check for a the pending surrogate pair */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		format.fd_surrogate = 0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff);
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
	}
	result = libd_format_wto8(&format, data, datalen);
	/* Update the pending surrogate pair */
	if (format.fd_surrogate)
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_UTF16_LO | (format.fd_surrogate - 0xdc00);
	return result;
}
/*[[[end:libd_file_wprinter_unlocked]]]*/

/*[[[start:exports,hash:CRC-32=0xcc8ae557]]]*/
DEFINE_PUBLIC_ALIAS_P(DOS$getwc,libd_fgetwc,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fgetwc,libd_fgetwc,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(getwc,libc_fgetwc,ATTR_INOUT(1),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(fgetwc,libc_fgetwc,ATTR_INOUT(1),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$putwc,libd_fputwc,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fputwc,libd_fputwc,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(putwc,libc_fputwc,ATTR_INOUT(2),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(fputwc,libc_fputwc,ATTR_INOUT(2),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$ungetwc,libd_ungetwc,ATTR_INOUT(2),wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(ungetwc,libc_ungetwc,ATTR_INOUT(2),wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t wc, FILE *stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$open_wmemstream,libd_open_wmemstream,,FILE *,NOTHROW_NCX,LIBDCALL,(char16_t **bufloc, size_t *sizeloc),(bufloc,sizeloc));
DEFINE_PUBLIC_ALIAS_P(open_wmemstream,libc_open_wmemstream,,FILE *,NOTHROW_NCX,LIBKCALL,(char32_t **bufloc, size_t *sizeloc),(bufloc,sizeloc));
DEFINE_PUBLIC_ALIAS_P(DOS$getwc_unlocked,libd_fgetwc_unlocked,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_getwc_nolock,libd_fgetwc_unlocked,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_fgetwc_nolock,libd_fgetwc_unlocked,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fgetwc_unlocked,libd_fgetwc_unlocked,ATTR_INOUT(1),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(getwc_unlocked,libc_fgetwc_unlocked,ATTR_INOUT(1),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(fgetwc_unlocked,libc_fgetwc_unlocked,ATTR_INOUT(1),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream),(stream));
DEFINE_PUBLIC_ALIAS_P(DOS$putwc_unlocked,libd_fputwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_putwc_nolock,libd_fputwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_fputwc_nolock,libd_fputwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fputwc_unlocked,libd_fputwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(putwc_unlocked,libc_fputwc_unlocked,ATTR_INOUT(2),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(fputwc_unlocked,libc_fputwc_unlocked,ATTR_INOUT(2),wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc, FILE *__restrict stream),(wc,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$file_wprinter,libd_file_wprinter,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_CB_NCX,LIBDCALL,(void *arg, char16_t const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(file_wprinter,libc_file_wprinter,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_CB_NCX,LIBKCALL,(void *arg, char32_t const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(DOS$file_wprinter_unlocked,libd_file_wprinter_unlocked,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_CB_NCX,LIBDCALL,(void *arg, char16_t const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(file_wprinter_unlocked,libc_file_wprinter_unlocked,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_CB_NCX,LIBKCALL,(void *arg, char32_t const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(DOS$_ungetwc_nolock,libd_ungetwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, FILE *__restrict stream),(ch,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$ungetwc_unlocked,libd_ungetwc_unlocked,ATTR_INOUT(2),wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, FILE *__restrict stream),(ch,stream));
DEFINE_PUBLIC_ALIAS_P(ungetwc_unlocked,libc_ungetwc_unlocked,ATTR_INOUT(2),wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, FILE *__restrict stream),(ch,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fgetwln,libd_fgetwln,WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(FILE *__restrict stream, size_t *__restrict lenp),(stream,lenp));
DEFINE_PUBLIC_ALIAS_P(fgetwln,libc_fgetwln,WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(FILE *__restrict stream, size_t *__restrict lenp),(stream,lenp));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_C */
