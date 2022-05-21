/* HASH CRC-32:0xc8abdbc4 */
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
#ifndef __local_fuzzy_wmemcasecmp_defined
#define __local_fuzzy_wmemcasecmp_defined
#include <__crt.h>
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
#ifndef __local___localdep_towlower_defined
#define __local___localdep_towlower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW(__LIBCCALL __localdep_towlower)(__WINT_TYPE__ __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towlower __LIBC_LOCAL_NAME(towlower)
#endif /* !... */
#endif /* !__local___localdep_towlower_defined */
__LOCAL_LIBC(fuzzy_wmemcasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes) {
	__SIZE_TYPE__ *__v0, *__v1, __i, __j, __cost, __temp;
	if __unlikely(!__s1_bytes)
		return __s2_bytes;
	if __unlikely(!__s2_bytes)
		return __s1_bytes;
	if (__s2_bytes > __s1_bytes) {
		{
			void const *__temp;
			__temp = (void const *)__s1;
			__s1   = __s2;
			*(void const **)&__s2 = __temp;
		}
		{
			__SIZE_TYPE__ __temp;
			__temp     = __s1_bytes;
			__s1_bytes = __s2_bytes;
			__s2_bytes = __temp;
		}
	}
	__malloca_tryhard(__v0, (__s2_bytes + 1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v0)
		return (__SIZE_TYPE__)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(__v1, (__s2_bytes + 1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v1) {
		__freea(__v0);
		return (__SIZE_TYPE__)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (__i = 0; __i < __s2_bytes; ++__i)
		__v0[__i] = __i;
	for (__i = 0; __i < __s1_bytes; ++__i) {
		__v1[0] = __i + 1;
		for (__j = 0; __j < __s2_bytes; __j++) {
			__BYTE_TYPE__ __c1 = ((__BYTE_TYPE__ *)__s1)[__i];
			__BYTE_TYPE__ __c2 = ((__BYTE_TYPE__ *)__s2)[__j];
			__cost  = __c1 != __c2 && ((__NAMESPACE_LOCAL_SYM __localdep_towlower)((__WCHAR_TYPE__)__c1) !=
			                     (__NAMESPACE_LOCAL_SYM __localdep_towlower)((__WCHAR_TYPE__)__c2));
			__cost += __v0[__j];
			__temp  = __v1[__j] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__temp  = __v0[__j + 1] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__v1[__j + 1] = __cost;
		}
		(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__v0, __v1, __s2_bytes, sizeof(__SIZE_TYPE__));
	}
	__temp = __v1[__s2_bytes];
	__freea(__v1);
	__freea(__v0);
	return __temp;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_wmemcasecmp_defined
#define __local___localdep_fuzzy_wmemcasecmp_defined
#define __localdep_fuzzy_wmemcasecmp __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp)
#endif /* !__local___localdep_fuzzy_wmemcasecmp_defined */
#else /* !__NO_MALLOCA */
#undef __local_fuzzy_wmemcasecmp_defined
#endif /* __NO_MALLOCA */
#endif /* !__local_fuzzy_wmemcasecmp_defined */
