/* HASH CRC-32:0xeaff90b */
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
#ifndef __local_c32execve_defined
#define __local_c32execve_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_wcstombsv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsv) || (defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsvn) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
#include <features.h>
#include <hybrid/typecore.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_convert_c32tombsv_defined
#define __local___localdep_convert_c32tombsv_defined
#if defined(__CRT_HAVE_convert_wcstombsv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char **,__NOTHROW_NCX,__localdep_convert_c32tombsv,(__CHAR32_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif defined(__CRT_HAVE_KOS$convert_wcstombsv)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char **,__NOTHROW_NCX,__localdep_convert_c32tombsv,(__CHAR32_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif (defined(__CRT_HAVE_convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombsv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombsv __NAMESPACE_LOCAL_TYPEHAX(char **(__LIBKCALL*)(__CHAR32_TYPE__ const *const *__restrict),char **(__LIBKCALL&)(__CHAR32_TYPE__ const *const *__restrict),convert_wcstombsv)
#elif (defined(__CRT_HAVE_convert_wcstombsvn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsvn) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c32tombsv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombsv __LIBC_LOCAL_NAME(convert_c32tombsv)
#else /* ... */
#undef __local___localdep_convert_c32tombsv_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c32tombsv_defined */
#ifndef __local___localdep_convert_freev_defined
#define __local___localdep_convert_freev_defined
#ifdef __CRT_HAVE_convert_freev
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_convert_freev,(void *__vector),convert_freev,(__vector))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_freev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_freev __LIBC_LOCAL_NAME(convert_freev)
#else /* ... */
#undef __local___localdep_convert_freev_defined
#endif /* !... */
#endif /* !__local___localdep_convert_freev_defined */
#ifndef __local___localdep_execve_defined
#define __local___localdep_execve_defined
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___execve)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___libc_execve)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__libc_execve,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_execve_defined
#endif /* !... */
#endif /* !__local___localdep_execve_defined */
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
__LOCAL_LIBC(c32execve) __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32execve))(__CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP) {
	int __result = -1;
	char *__utf8_path, **__utf8_argv, **__utf8_envp;
	__utf8_path = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombs)(__path);
	if __unlikely(!__utf8_path)
		goto __done;
	__utf8_argv = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombsv)(___argv);
	if __unlikely(!__utf8_argv)
		goto __done_file;
	__utf8_envp = __NULLPTR;
	if __unlikely(___envp && (__utf8_envp = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombsv)(___envp)) == __NULLPTR)
		goto __done_argv;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_execve)(__utf8_path, __utf8_argv, __utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_convert_freev)(__utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_convert_freev)(__utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32execve_defined
#define __local___localdep_c32execve_defined
#define __localdep_c32execve __LIBC_LOCAL_NAME(c32execve)
#endif /* !__local___localdep_c32execve_defined */
#else /* (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_convert_wcstombsv && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombsv || (__CRT_HAVE_convert_wcstombsvn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsvn || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
#undef __local_c32execve_defined
#endif /* (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_convert_wcstombsv || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombsv && (!__CRT_HAVE_convert_wcstombsvn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsvn && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) */
#endif /* !__local_c32execve_defined */
