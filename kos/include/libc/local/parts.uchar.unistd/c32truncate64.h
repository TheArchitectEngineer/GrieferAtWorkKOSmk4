/* HASH CRC-32:0x1f8ca8a0 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32truncate64_defined
#define __local_c32truncate64_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wtruncate) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32truncate32_defined
#define __local___localdep_c32truncate32_defined 1
#if defined(__CRT_HAVE_wtruncate) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_c32truncate32,(__CHAR32_TYPE__ const *__file, __pos32_t __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_KOS$wtruncate)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_c32truncate32,(__CHAR32_TYPE__ const *__file, __pos32_t __length),wtruncate,(__file,__length))
#else /* ... */
#undef __local___localdep_c32truncate32_defined
#endif /* !... */
#endif /* !__local___localdep_c32truncate32_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_ftruncate64_defined
#define __local___localdep_ftruncate64_defined 1
#ifdef __CRT_HAVE_ftruncate64
__NAMESPACE_LOCAL_END
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
__NAMESPACE_LOCAL_END
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/ftruncate64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ftruncate64 __LIBC_LOCAL_NAME(ftruncate64)
#else /* ... */
#undef __local___localdep_ftruncate64_defined
#endif /* !... */
#endif /* !__local___localdep_ftruncate64_defined */
#ifndef __local___localdep_open64_defined
#define __local___localdep_open64_defined 1
#ifdef __CRT_HAVE_open64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open64 __LIBC_LOCAL_NAME(open64)
#else /* ... */
#undef __local___localdep_open64_defined
#endif /* !... */
#endif /* !__local___localdep_open64_defined */
__NAMESPACE_LOCAL_END
#include <features.h>
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
__LOCAL_LIBC(c32truncate64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32truncate64))(__CHAR32_TYPE__ const *__file, __PIO_OFFSET64 __length) {
#if (defined(__CRT_HAVE_wtruncate) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wtruncate)
	return (__NAMESPACE_LOCAL_SYM __localdep_c32truncate32)(__file, (__PIO_OFFSET)__length);
#else /* (__CRT_HAVE_wtruncate && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wtruncate */
	int __result;
	__fd_t __fd;
	__fd = (__NAMESPACE_LOCAL_SYM __localdep_open64)(__file, 1); /* O_WRONLY */
	if __unlikely(__fd < 0)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_ftruncate64)(__fd, __length);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */
	return __result;
#endif /* (!__CRT_HAVE_wtruncate || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wtruncate */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32truncate64_defined
#define __local___localdep_c32truncate64_defined 1
#define __localdep_c32truncate64 __LIBC_LOCAL_NAME(c32truncate64)
#endif /* !__local___localdep_c32truncate64_defined */
#else /* (__CRT_HAVE_wtruncate && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wtruncate || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate)) */
#undef __local_c32truncate64_defined
#endif /* (!__CRT_HAVE_wtruncate || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wtruncate && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open) || (!__CRT_HAVE_ftruncate64 && !__CRT_HAVE__chsize_s && !__CRT_HAVE_ftruncate)) */
#endif /* !__local_c32truncate64_defined */
