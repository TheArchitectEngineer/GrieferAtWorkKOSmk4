/* HASH CRC-32:0x87da4b09 */
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
#ifndef __local_modff_defined
#if defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf)
#define __local_modff_defined 1
/* Dependency: "modf" */
#ifndef ____localdep_modf_defined
#define ____localdep_modf_defined 1
#if __has_builtin(__builtin_modf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__EXTERNINLINE __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL __localdep_modf)(double __x, double *__iptr) { return __builtin_modf(__x, __iptr); }
#elif defined(__CRT_HAVE_modf)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__localdep_modf,(double __x, double *__iptr),modf,(__x,__iptr))
#elif defined(__CRT_HAVE___modf)
/* Break VALUE into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__localdep_modf,(double __x, double *__iptr),__modf,(__x,__iptr))
#else /* LIBC: modf */
#undef ____localdep_modf_defined
#endif /* modf... */
#endif /* !____localdep_modf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Break VALUE into integral and fractional parts */
__LOCAL_LIBC(modff) __ATTR_NONNULL((2)) float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(modff))(float __x,
                                                   float *__iptr) {
#line 238 "kos/src/libc/magic/math.c"
	double __ipart;
	float __result;
	__result = (float)__localdep_modf(__x, &__ipart);
	*__iptr  = (float)__ipart;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_modf || __CRT_HAVE___modf */
#endif /* !__local_modff_defined */
