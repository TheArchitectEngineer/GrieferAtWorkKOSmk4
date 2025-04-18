/* HASH CRC-32:0xb864c9e6 */
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
#ifndef __local__vcwscanf_l_defined
#define __local__vcwscanf_l_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#include <bits/types.h>
#if defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___conio_common_vcwscanf_defined
#define __local___localdep___conio_common_vcwscanf_defined
#ifdef __CRT_HAVE___conio_common_vcwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep___conio_common_vcwscanf,(__UINT64_TYPE__ __options, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),__conio_common_vcwscanf,(__options,__format,__locale,__args))
#elif ((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/__conio_common_vcwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___conio_common_vcwscanf __LIBC_LOCAL_NAME(__conio_common_vcwscanf)
#else /* ... */
#undef __local___localdep___conio_common_vcwscanf_defined
#endif /* !... */
#endif /* !__local___localdep___conio_common_vcwscanf_defined */
__NAMESPACE_LOCAL_END
#include <corecrt_stdio_config.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vcwscanf_l) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_vcwscanf_l))(__WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep___conio_common_vcwscanf)(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, __format, __locale, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vcwscanf_l_defined
#define __local___localdep__vcwscanf_l_defined
#define __localdep__vcwscanf_l __LIBC_LOCAL_NAME(_vcwscanf_l)
#endif /* !__local___localdep__vcwscanf_l_defined */
#else /* __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#undef __local__vcwscanf_l_defined
#endif /* !__CRT_HAVE___conio_common_vcwscanf && (((!__CRT_HAVE__getwche_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getwche && (!__CRT_HAVE_stdtty || (!__CRT_HAVE__getwche_nolock && (!__ECHO || !__TCSANOW || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) || (!__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked && !__CRT_HAVE__getwc_nolock && !__CRT_HAVE__fgetwc_nolock && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc) || (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64))))) || ((!__CRT_HAVE__ungetwch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetwch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__local__vcwscanf_l_defined */
