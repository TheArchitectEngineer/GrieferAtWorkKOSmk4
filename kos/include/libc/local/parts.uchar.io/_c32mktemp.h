/* HASH CRC-32:0x256c5281 */
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
#ifndef __local__c32mktemp_defined
#define __local__c32mktemp_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32end_defined
#define __local___localdep_c32end_defined
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_KOS$wcsend)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcsend)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32end.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __LIBC_LOCAL_NAME(c32end)
#endif /* !... */
#endif /* !__local___localdep_c32end_defined */
#ifndef __local___localdep_convert_c32tombs_defined
#define __local___localdep_convert_c32tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_KOS$convert_wcstombs)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombs __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBKCALL*)(__CHAR32_TYPE__ const *),char *(__LIBKCALL&)(__CHAR32_TYPE__ const *),convert_wcstombs)
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c32tombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombs __LIBC_LOCAL_NAME(convert_c32tombs)
#else /* ... */
#undef __local___localdep_convert_c32tombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c32tombs_defined */
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
#ifndef __local___localdep_mktemp_defined
#define __local___localdep_mktemp_defined
#ifdef __CRT_HAVE_mktemp
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),mktemp,(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),__mktemp,(__template_))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mktemp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mktemp __LIBC_LOCAL_NAME(mktemp)
#else /* ... */
#undef __local___localdep_mktemp_defined
#endif /* !... */
#endif /* !__local___localdep_mktemp_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(_c32mktemp) __ATTR_RETNONNULL __ATTR_INOUT(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(_c32mktemp))(__CHAR32_TYPE__ *__template_) {
	char *__utf8_template, *__rand;
	__CHAR32_TYPE__ *__rand_dst;
	__SIZE_TYPE__ __i;
	__utf8_template = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombs)(__template_);
	if __unlikely(!__utf8_template)
		goto __err;
	__utf8_template = (__NAMESPACE_LOCAL_SYM __localdep_mktemp)(__utf8_template);
	if (!*__utf8_template)
		goto __err_utf8_template;
	__rand = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__utf8_template) - 6;
	__rand_dst = (__NAMESPACE_LOCAL_SYM __localdep_c32end)(__template_) - 6;
	for (__i = 0; __i < 6; ++__i)
		__rand_dst[__i] = (__CHAR32_TYPE__)(unsigned char)__rand[__i];
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_template);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __template_;
__err_utf8_template:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_template);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
	*__template_ = '\0';
	return __template_;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__c32mktemp_defined
#define __local___localdep__c32mktemp_defined
#define __localdep__c32mktemp __LIBC_LOCAL_NAME(_c32mktemp)
#endif /* !__local___localdep__c32mktemp_defined */
#else /* (__CRT_HAVE_mktemp || __CRT_HAVE__mktemp || __CRT_HAVE___mktemp || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local__c32mktemp_defined
#endif /* (!__CRT_HAVE_mktemp && !__CRT_HAVE__mktemp && !__CRT_HAVE___mktemp && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) && (!__AT_FDCWD || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_stat && !__CRT_HAVE_stat64 && !__CRT_HAVE___stat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local__c32mktemp_defined */
