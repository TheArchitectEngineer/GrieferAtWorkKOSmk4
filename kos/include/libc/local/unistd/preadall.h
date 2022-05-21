/* HASH CRC-32:0xb5865ed2 */
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
#ifndef __local_preadall_defined
#define __local_preadall_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <features.h>
#if (defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_preadall64) || defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_preadall64_defined
#define __local___localdep_preadall64_defined
#if defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),preadall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall64)
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),preadall64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/preadall64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_preadall64 __LIBC_LOCAL_NAME(preadall64)
#else /* ... */
#undef __local___localdep_preadall64_defined
#endif /* !... */
#endif /* !__local___localdep_preadall64_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(preadall) __ATTR_ACCESS_WRS(2, 3) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(preadall))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET __offset) {
	return (__NAMESPACE_LOCAL_SYM __localdep_preadall64)(__fd, __buf, __bufsize, (__PIO_OFFSET64)__offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_preadall_defined
#define __local___localdep_preadall_defined
#define __localdep_preadall __LIBC_LOCAL_NAME(preadall)
#endif /* !__local___localdep_preadall_defined */
#else /* (__CRT_HAVE_preadall && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_preadall64 || __CRT_HAVE_pread64 || __CRT_HAVE___pread64 || __CRT_HAVE_pread || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && __SEEK_CUR && __SEEK_SET) */
#undef __local_preadall_defined
#endif /* (!__CRT_HAVE_preadall || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_preadall64 && !__CRT_HAVE_pread64 && !__CRT_HAVE___pread64 && !__CRT_HAVE_pread && ((!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || !__SEEK_CUR || !__SEEK_SET) */
#endif /* !__local_preadall_defined */
