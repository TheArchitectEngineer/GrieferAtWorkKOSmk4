/* HASH CRC-32:0x3d62d7cb */
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
#ifndef __local_wexecvp_defined
#define __local_wexecvp_defined
#include <__crt.h>
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_wcstombsv) || defined(__CRT_HAVE_convert_wcstombsvn) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
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
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
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
#ifndef __local___localdep_convert_wcstombsv_defined
#define __local___localdep_convert_wcstombsv_defined
#ifdef __CRT_HAVE_convert_wcstombsv
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char **,__NOTHROW_NCX,__localdep_convert_wcstombsv,(__WCHAR_TYPE__ const *const *__restrict __vector),convert_wcstombsv,(__vector))
#elif defined(__CRT_HAVE_convert_wcstombsvn) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombsv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_wcstombsv __LIBC_LOCAL_NAME(convert_wcstombsv)
#else /* ... */
#undef __local___localdep_convert_wcstombsv_defined
#endif /* !... */
#endif /* !__local___localdep_convert_wcstombsv_defined */
#ifndef __local___localdep_execvp_defined
#define __local___localdep_execvp_defined
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),execvp,{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),execvp,(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,___argv))
#elif (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execvp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execvp __LIBC_LOCAL_NAME(execvp)
#else /* ... */
#undef __local___localdep_execvp_defined
#endif /* !... */
#endif /* !__local___localdep_execvp_defined */
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
__LOCAL_LIBC(wexecvp) __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wexecvp))(__WCHAR_TYPE__ const *__restrict __file, __TWARGV) {
	int __result = -1;
	char *__utf8_file, **__utf8_argv;
	__utf8_file = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__file);
	if __unlikely(!__utf8_file)
		goto __done;
	__utf8_argv = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombsv)(___argv);
	if __unlikely(!__utf8_argv)
		goto __done_file;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_execvp)(__utf8_file, __utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_convert_freev)(__utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexecvp_defined
#define __local___localdep_wexecvp_defined
#define __localdep_wexecvp __LIBC_LOCAL_NAME(wexecvp)
#endif /* !__local___localdep_wexecvp_defined */
#else /* (__CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_wcstombsv || __CRT_HAVE_convert_wcstombsvn || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
#undef __local_wexecvp_defined
#endif /* (!__CRT_HAVE_execvp && !__CRT_HAVE__execvp && ((!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca)) || !__LOCAL_environ)) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_convert_wcstombsv && !__CRT_HAVE_convert_wcstombsvn && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) */
#endif /* !__local_wexecvp_defined */
