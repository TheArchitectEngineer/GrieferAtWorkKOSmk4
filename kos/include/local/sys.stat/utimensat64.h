/* HASH CRC-32:0x4b2845ef */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_utimensat64_defined
#ifdef __CRT_HAVE_utimensat
#define __local_utimensat64_defined 1
/* Dependency: "utimensat32" from "sys.stat" */
#ifndef ____localdep_utimensat32_defined
#define ____localdep_utimensat32_defined 1
#ifdef __CRT_HAVE_utimensat
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_utimensat32,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#else /* LIBC: utimensat */
#undef ____localdep_utimensat32_defined
#endif /* utimensat32... */
#endif /* !____localdep_utimensat32_defined */

__NAMESPACE_LOCAL_BEGIN
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__LOCAL_LIBC(utimensat64) __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(utimensat64))(__fd_t __dirfd,
                                                         char const *__filename,
                                                         struct __timespec64 const __times[2 /*or:3*/],
                                                         __atflag_t __flags) {
#line 607 "kos/src/libc/magic/sys.stat.c"
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct __timespec32 __tms[3];
	if (!__times)
		return __localdep_utimensat32(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	if (__flags & 0x0200) /* AT_CHANGE_CTIME */ {
		__tms[2].tv_sec  = (__time32_t)__times[2].tv_sec;
		__tms[2].tv_nsec = __times[2].tv_nsec;
	}
	return __localdep_utimensat32(__dirfd, __filename, __tms, __flags);
#else
	struct __timespec32 __tms[2];
	if (!__times)
		return __localdep_utimensat32(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_utimensat32(__dirfd, __filename, __tms, __flags);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_utimensat */
#endif /* !__local_utimensat64_defined */
