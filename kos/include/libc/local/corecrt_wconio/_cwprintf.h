/* HASH CRC-32:0xc8fd5a3f */
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
#ifndef __local__cwprintf_defined
#define __local__cwprintf_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__vcwprintf) || defined(__CRT_HAVE__vcwprintf_l) || defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vcwprintf_defined
#define __local___localdep__vcwprintf_defined
#ifdef __CRT_HAVE__vcwprintf
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep__vcwprintf,(__WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vcwprintf,(__format,__args))
#elif defined(__CRT_HAVE__vcwprintf_l) || defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/_vcwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vcwprintf __LIBC_LOCAL_NAME(_vcwprintf)
#else /* ... */
#undef __local___localdep__vcwprintf_defined
#endif /* !... */
#endif /* !__local___localdep__vcwprintf_defined */
__LOCAL_LIBC(_cwprintf) __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(_cwprintf))(__WCHAR_TYPE__ const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vcwprintf)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cwprintf_defined
#define __local___localdep__cwprintf_defined
#define __localdep__cwprintf __LIBC_LOCAL_NAME(_cwprintf)
#endif /* !__local___localdep__cwprintf_defined */
#else /* __CRT_HAVE__vcwprintf || __CRT_HAVE__vcwprintf_l || __CRT_HAVE___conio_common_vcwprintf || (__CRT_HAVE_stdtty && (__CRT_HAVE___stdio_common_vfwprintf || __CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) */
#undef __local__cwprintf_defined
#endif /* !__CRT_HAVE__vcwprintf && !__CRT_HAVE__vcwprintf_l && !__CRT_HAVE___conio_common_vcwprintf && (!__CRT_HAVE_stdtty || (!__CRT_HAVE___stdio_common_vfwprintf && !__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) */
#endif /* !__local__cwprintf_defined */
