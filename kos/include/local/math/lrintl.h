/* HASH CRC-32:0x5b3c1f30 */
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
#ifndef __local_lrintl_defined
#define __local_lrintl_defined 1
#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Dependency: "rintl" from "math" */
#ifndef ____localdep_rintl_defined
#define ____localdep_rintl_defined 1
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),__rintl,(__x))
#else /* LIBC: rintl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint)
#include <local/math/rintl.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
#define __localdep_rintl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))
#else /* CUSTOM: rintl */
#undef ____localdep_rintl_defined
#endif /* rintl... */
#endif /* rintl... */
#endif /* !____localdep_rintl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__LOCAL_LIBC(lrintl) __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lrintl))(__LONGDOUBLE __x) {
#line 1816 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_lrintl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_lrintf((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee854_lrint((__IEEE754_DOUBLE_TYPE__)__x);
#else /* ... */
	return (long int)__localdep_rintl(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lrintl_defined */
