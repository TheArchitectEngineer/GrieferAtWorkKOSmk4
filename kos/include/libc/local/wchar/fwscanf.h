/* HASH CRC-32:0xc500c9ca */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fwscanf_defined
#define __local_fwscanf_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfwscanf_defined
#define __local___localdep_vfwscanf_defined
#if defined(__CRT_HAVE_vfwscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfwscanf,(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/vfwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfwscanf __LIBC_LOCAL_NAME(vfwscanf)
#else /* ... */
#undef __local___localdep_vfwscanf_defined
#endif /* !... */
#endif /* !__local___localdep_vfwscanf_defined */
__LOCAL_LIBC(fwscanf) __ATTR_ACCESS_RW(1) __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(fwscanf))(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vfwscanf)(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fwscanf_defined
#define __local___localdep_fwscanf_defined
#define __localdep_fwscanf __LIBC_LOCAL_NAME(fwscanf)
#endif /* !__local___localdep_fwscanf_defined */
#else /* __CRT_HAVE_vfwscanf || __CRT_HAVE_vfwscanf_unlocked || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)) */
#undef __local_fwscanf_defined
#endif /* !__CRT_HAVE_vfwscanf && !__CRT_HAVE_vfwscanf_unlocked && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)) */
#endif /* !__local_fwscanf_defined */
