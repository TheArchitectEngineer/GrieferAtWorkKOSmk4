/* HASH CRC-32:0x6073d3af */
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
#ifndef __local_wfreadlinkat_defined
#define __local_wfreadlinkat_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_freadlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_wcstombs,(__WCHAR_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_wcstombs __LIBC_LOCAL_NAME(convert_wcstombs)
#else /* ... */
#undef __local___localdep_convert_wcstombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_wcstombs_defined */
#ifndef __local___localdep_freadlinkat_defined
#define __local___localdep_freadlinkat_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(3, 4),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_freadlinkat,(__fd_t __dfd, char const *__path, char *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),freadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* !__local___localdep_freadlinkat_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_unicode_8to16_n_defined
#define __local___localdep_unicode_8to16_n_defined
#ifdef __CRT_HAVE_unicode_8to16_n
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_8to16_n,(__CHAR16_TYPE__ *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_8to16_n,(__utf16_dst,__utf16_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_8to16_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_8to16_n __LIBC_LOCAL_NAME(unicode_8to16_n)
#endif /* !__CRT_HAVE_unicode_8to16_n */
#endif /* !__local___localdep_unicode_8to16_n_defined */
#ifndef __local___localdep_unicode_8to32_n_defined
#define __local___localdep_unicode_8to32_n_defined
#ifdef __CRT_HAVE_unicode_8to32_n
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_8to32_n,(__CHAR32_TYPE__ *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_8to32_n,(__utf32_dst,__utf32_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to32_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_8to32_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_8to32_n __LIBC_LOCAL_NAME(unicode_8to32_n)
#endif /* !__CRT_HAVE_unicode_8to32_n */
#endif /* !__local___localdep_unicode_8to32_n_defined */
#ifndef __local___localdep_unicode_len8to16_defined
#define __local___localdep_unicode_len8to16_defined
#ifdef __CRT_HAVE_unicode_len8to16
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_len8to16,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_len8to16,(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_len8to16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_len8to16 __LIBC_LOCAL_NAME(unicode_len8to16)
#endif /* !__CRT_HAVE_unicode_len8to16 */
#endif /* !__local___localdep_unicode_len8to16_defined */
#ifndef __local___localdep_unicode_len8to32_defined
#define __local___localdep_unicode_len8to32_defined
#ifdef __CRT_HAVE_unicode_len8to32
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_len8to32,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_len8to32,(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to32 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_len8to32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_len8to32 __LIBC_LOCAL_NAME(unicode_len8to32)
#endif /* !__CRT_HAVE_unicode_len8to32 */
#endif /* !__local___localdep_unicode_len8to32_defined */
__LOCAL_LIBC(wfreadlinkat) __ATTR_IN(2) __ATTR_OUTS(3, 4) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wfreadlinkat))(__fd_t __dfd, __WCHAR_TYPE__ const *__path, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags) {
	char *__utf8_path;
	__SSIZE_TYPE__ __result;
#if __SIZEOF_WCHAR_T__ == 4
	__SIZE_TYPE__ __utf8_buflen = __buflen * 7; /* s.a. `UNICODE_32TO8_MAXBUF()' */
#else /* __SIZEOF_WCHAR_T__ == 4 */
	__SIZE_TYPE__ __utf8_buflen = __buflen * 3; /* s.a. `UNICODE_16TO8_MAXBUF()' */
#endif /* __SIZEOF_WCHAR_T__ != 4 */
	char *__utf8_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__utf8_buflen * sizeof(char));
	if __unlikely(!__utf8_buf)
		goto __err;
	__utf8_path = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__path);
	if __unlikely(!__utf8_path)
		goto __err_utf8_buf;
#ifdef __AT_READLINK_REQSIZE
__again_freadlinkat:
#endif /* __AT_READLINK_REQSIZE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_freadlinkat)(__dfd, __utf8_path, __utf8_buf, __utf8_buflen, __flags);
#if !defined(__AT_READLINK_REQSIZE) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_path);
#endif /* !__AT_READLINK_REQSIZE && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free) */
	if __likely(__result >= 0) {
		__WCHAR_TYPE__ *__dst;
#ifdef __AT_READLINK_REQSIZE
		if ((__SIZE_TYPE__)__result > __utf8_buflen) {
			/* Caller used the REQSIZE flag, and the buffer was too small.
			 * -> Allocate a larger utf-8 buffer so we can get the entire
			 *    utf-8 string from the kernel! */
			__utf8_buflen = (__SIZE_TYPE__)__result;
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			__utf8_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__utf8_buflen * sizeof(char));
			if __unlikely(!__utf8_buf) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
				(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
				goto __err;
			}
			goto __again_freadlinkat;
		}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* __AT_READLINK_REQSIZE */
#if __SIZEOF_WCHAR_T__ == 4
		__dst = (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_unicode_8to32_n)((__CHAR32_TYPE__ *)__buf, __buflen, __utf8_buf, (__SIZE_TYPE__)__result);
#else /* __SIZEOF_WCHAR_T__ == 4 */
		__dst = (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_unicode_8to16_n)((__CHAR16_TYPE__ *)__buf, __buflen, __utf8_buf, (__SIZE_TYPE__)__result);
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#ifdef __AT_READLINK_REQSIZE
		if (__flags & __AT_READLINK_REQSIZE) {
#if __SIZEOF_WCHAR_T__ == 4
			__result = (__NAMESPACE_LOCAL_SYM __localdep_unicode_len8to32)(__utf8_buf, (__SIZE_TYPE__)__result);
#else /* __SIZEOF_WCHAR_T__ == 4 */
			__result = (__NAMESPACE_LOCAL_SYM __localdep_unicode_len8to16)(__utf8_buf, (__SIZE_TYPE__)__result);
#endif /* __SIZEOF_WCHAR_T__ != 4 */
		} else
#endif /* __AT_READLINK_REQSIZE */
		{
			__result = (__SIZE_TYPE__)(__dst - __buf);
		}
	} else {
#if defined(__AT_READLINK_REQSIZE) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_path);
#endif /* __AT_READLINK_REQSIZE && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free) */
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
__err_utf8_buf:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wfreadlinkat_defined
#define __local___localdep_wfreadlinkat_defined
#define __localdep_wfreadlinkat __LIBC_LOCAL_NAME(wfreadlinkat)
#endif /* !__local___localdep_wfreadlinkat_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_freadlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_wfreadlinkat_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_freadlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_wfreadlinkat_defined */
