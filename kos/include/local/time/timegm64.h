/* HASH CRC-32:0x485580b */
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
#ifndef __local_timegm64_defined
#define __local_timegm64_defined 1
#include <__crt.h>
#include <bits/types.h>
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mktime64 from time */
#ifndef __local___localdep_mktime64_defined
#define __local___localdep_mktime64_defined 1
#ifdef __CRT_HAVE_mktime64
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/time/mktime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
#define __localdep_mktime64 __LIBC_LOCAL_NAME(mktime64)
#endif /* !... */
#endif /* !__local___localdep_mktime64_defined */
/* Dependency: timegm32 from time */
#if !defined(__local___localdep_timegm32_defined) && defined(__CRT_HAVE_timegm)
#define __local___localdep_timegm32_defined 1
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_timegm32,(__STRUCT_TM *__tp),timegm,(__tp))
#endif /* !__local___localdep_timegm32_defined && __CRT_HAVE_timegm */
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__LOCAL_LIBC(timegm64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timegm64))(__STRUCT_TM *__tp) {



#ifdef __CRT_HAVE_timegm
	return (__time64_t)__localdep_timegm32(__tp);
#else /* 0 */
	/* TODO: Timezones */
	return __localdep_mktime64(__tp);
#endif /* 1 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timegm64_defined
#define __local___localdep_timegm64_defined 1
#define __localdep_timegm64 __LIBC_LOCAL_NAME(timegm64)
#endif /* !__local___localdep_timegm64_defined */
#endif /* !__local_timegm64_defined */
