/* HASH CRC-32:0x42c15dbb */
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
#ifndef __local_isatty_defined
#define __local_isatty_defined
#include <__crt.h>
#include <asm/os/tty.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TCGETA))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined
#if defined(__CRT_HAVE_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __local___localdep_ioctl_defined
#endif /* !... */
#endif /* !__local___localdep_ioctl_defined */
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined
#ifdef __CRT_HAVE_tcgetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#elif defined(__CRT_HAVE___tcgetattr)
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),__tcgetattr,(__fd,__termios_p))
#elif (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TCGETA)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcgetattr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#else /* ... */
#undef __local___localdep_tcgetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcgetattr_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isatty) __ATTR_WUNUSED __ATTR_FDARG(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isatty))(__fd_t __fd) {
	struct termios __ios;
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TCGETA)
	return (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, __TCGETA, &__ios) < 0 ? 0 : 1;
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __TCGETA */
	return (__NAMESPACE_LOCAL_SYM __localdep_tcgetattr)(__fd, &__ios) != 0 ? 0 : 1;
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__TCGETA */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#endif /* !__local___localdep_isatty_defined */
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __TCGETA) */
#undef __local_isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__TCGETA) */
#endif /* !__local_isatty_defined */
