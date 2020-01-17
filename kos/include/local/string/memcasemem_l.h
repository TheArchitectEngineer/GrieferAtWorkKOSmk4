/* HASH CRC-32:0xe8f46f88 */
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
#ifndef __local_memcasemem_l_defined
#define __local_memcasemem_l_defined 1
/* Dependency: "tolower_l" from "ctype" */
#ifndef ____localdep_tolower_l_defined
#define ____localdep_tolower_l_defined 1
#ifdef __CRT_HAVE_tolower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),_tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* LIBC: tolower_l */
#include <local/ctype/tolower_l.h>
#define __localdep_tolower_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))
#endif /* tolower_l... */
#endif /* !____localdep_tolower_l_defined */

/* Dependency: "memcasecmp_l" from "string" */
#ifndef ____localdep_memcasecmp_l_defined
#define ____localdep_memcasecmp_l_defined 1
#ifdef __CRT_HAVE_memcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),memcasecmp_l,(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),_memicmp_l,(__s1,__s2,__n_bytes,__locale))
#else /* LIBC: memcasecmp_l */
#include <local/string/memcasecmp_l.h>
#define __localdep_memcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))
#endif /* memcasecmp_l... */
#endif /* !____localdep_memcasecmp_l_defined */

__NAMESPACE_LOCAL_BEGIN
#include <features.h>
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__LOCAL_LIBC(memcasemem_l) __ATTR_PURE __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasemem_l))(void const *__haystack,
                                                          __SIZE_TYPE__ __haystacklen,
                                                          void const *__needle,
                                                          __SIZE_TYPE__ __needlelen,
                                                          __locale_t __locale) {
#line 2904 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__candidate, __marker;
	__BYTE_TYPE__ *__hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if __unlikely(!__needlelen || __needlelen > __haystacklen)
		return __NULLPTR;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if __unlikely(!__needlelen)
		return (__BYTE_TYPE__ *)__haystack + __haystacklen;
	if __unlikely(__needlelen > __haystacklen)
		return __NULLPTR;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	__haystacklen -= (__needlelen - 1);
	__marker       = __localdep_tolower_l(*(__BYTE_TYPE__ *)__needle, __locale);
	__hayend       = (__BYTE_TYPE__ *)__haystack + __haystacklen;
	for (;;) {
		for (__candidate = (__BYTE_TYPE__ *)__haystack; __candidate < __hayend; ++__candidate) {
			__BYTE_TYPE__ __b = *__candidate;
			if (__b == __marker || __localdep_tolower_l(__b, __locale) == __marker)
				goto __got_candidate;
		}
		break;
__got_candidate:
		if (__localdep_memcasecmp_l(__candidate, __needle, __needlelen, __locale) == 0)
			return (void *)__candidate;
		++__candidate;
		__haystacklen = ((__BYTE_TYPE__ *)__haystack + __haystacklen) - __candidate;
		__haystack    = (void const *)__candidate;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memcasemem_l_defined */
