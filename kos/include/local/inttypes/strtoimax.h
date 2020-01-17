/* HASH CRC-32:0xc58cf451 */
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
#ifndef __local_strtoimax_defined
#define __local_strtoimax_defined 1
/* Dependency: "strto32" from "stdlib" */
#ifndef ____localdep_strto32_defined
#define ____localdep_strto32_defined 1
#ifdef __CRT_HAVE_strto32
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, int __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strto32 */
#include <local/stdlib/strto32.h>
#define __localdep_strto32 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))
#endif /* strto32... */
#endif /* !____localdep_strto32_defined */

/* Dependency: "strto64" from "stdlib" */
#ifndef ____localdep_strto64_defined
#define ____localdep_strto64_defined 1
#ifdef __CRT_HAVE_strto64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strto64 */
#include <local/stdlib/strto64.h>
#define __localdep_strto64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))
#endif /* strto64... */
#endif /* !____localdep_strto64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoimax) __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoimax))(char const *__restrict __nptr,
                                                       char **__endptr,
                                                       int __base) {
#line 496 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (__INTMAX_TYPE__)__localdep_strto32(__nptr, __endptr, __base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (__INTMAX_TYPE__)__localdep_strto64(__nptr, __endptr, __base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strtoimax_defined */
