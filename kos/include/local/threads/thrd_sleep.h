/* HASH CRC-32:0x1b599bac */
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
#ifndef __local_thrd_sleep_defined
#if defined(__CRT_HAVE_thrd_sleep) || defined(__CRT_HAVE_thrd_sleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE_nanosleep64)
#define __local_thrd_sleep_defined 1
#include <bits/timespec.h>
#include <bits/timespec.h>
#include <parts/errno.h>
/* Dependency: "thrd_sleep32" from "threads" */
#ifndef ____localdep_thrd_sleep32_defined
#define ____localdep_thrd_sleep32_defined 1
#ifdef __CRT_HAVE_thrd_sleep
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_thrd_sleep32,(struct __timespec32 const *__time_point, struct __timespec32 *__remaining),thrd_sleep,(__time_point,__remaining))
#else /* LIBC: thrd_sleep */
#undef ____localdep_thrd_sleep32_defined
#endif /* thrd_sleep32... */
#endif /* !____localdep_thrd_sleep32_defined */

/* Dependency: "crt_thrd_sleep64" from "threads" */
#ifndef ____localdep_crt_thrd_sleep64_defined
#define ____localdep_crt_thrd_sleep64_defined 1
#ifdef __CRT_HAVE_thrd_sleep64
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_thrd_sleep64,(struct __timespec64 const *__time_point, struct __timespec64 *__remaining),thrd_sleep64,(__time_point,__remaining))
#else /* LIBC: thrd_sleep64 */
#undef ____localdep_crt_thrd_sleep64_defined
#endif /* crt_thrd_sleep64... */
#endif /* !____localdep_crt_thrd_sleep64_defined */

/* Dependency: "nanosleep" from "time" */
#ifndef ____localdep_nanosleep_defined
#define ____localdep_nanosleep_defined 1
#if defined(__CRT_HAVE_nanosleep64) && defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) && !defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE_nanosleep64)
#include <local/time/nanosleep.h>
/* Pause execution for a number of nanoseconds */
#define __localdep_nanosleep (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep))
#else /* CUSTOM: nanosleep */
#undef ____localdep_nanosleep_defined
#endif /* nanosleep... */
#endif /* !____localdep_nanosleep_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__LOCAL_LIBC(thrd_sleep) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thrd_sleep))(struct timespec const *__time_point,
                                                        struct timespec *__remaining) {
#line 138 "kos/src/libc/magic/threads.c"
#ifdef __CRT_HAVE_thrd_sleep
	int __result;
	struct __timespec32 __tp32, __rem32;
	__tp32.tv_sec  = (__time32_t)__time_point->tv_sec;
	__tp32.tv_nsec = __time_point->tv_nsec;
	__result = __localdep_thrd_sleep32(&__tp32, __remaining ? &__rem32 : __NULLPTR);
	if (__result == -1 && __remaining) {
		__remaining->tv_sec = (__time64_t)__rem32.tv_sec;
		__remaining->tv_nsec = __rem32.tv_nsec;
	}
	return __result;
#elif defined(__CRT_HAVE_thrd_sleep64)
	int __result;
	struct __timespec64 __tp64, __rem64;
	__tp64.tv_sec  = (__time64_t)__time_point->tv_sec;
	__tp64.tv_nsec = __time_point->tv_nsec;
	__result = __localdep_crt_thrd_sleep64(&__tp64, __remaining ? &__rem64 : __NULLPTR);
	if (__result == -1 && __remaining) {
		__remaining->tv_sec = (__time32_t)__rem64.tv_sec;
		__remaining->tv_nsec = __rem64.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_thrd_sleep64 */
	int __error;
	__error = __localdep_nanosleep(__time_point, __remaining);
	if __likely(__error == 0)
		return 0;
#if defined(__errno) && defined(__EINTR)
	if (__errno == __EINTR)
		return -1; /* thrd_nomem */
#endif /* __errno && __EINTR */
	return -2;
#endif /* !__CRT_HAVE_thrd_sleep64 */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_thrd_sleep || __CRT_HAVE_thrd_sleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE_nanosleep64 */
#endif /* !__local_thrd_sleep_defined */
