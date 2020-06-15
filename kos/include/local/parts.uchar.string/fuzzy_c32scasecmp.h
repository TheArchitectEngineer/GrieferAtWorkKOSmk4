/* HASH CRC-32:0x2e10c870 */
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
#ifndef __local_fuzzy_c32scasecmp_defined
#define __local_fuzzy_c32scasecmp_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32slen from parts.uchar.string */
#ifndef __local___localdep_c32slen_defined
#define __local___localdep_c32slen_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32slen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen __LIBC_LOCAL_NAME(c32slen)
#endif /* !... */
#endif /* !__local___localdep_c32slen_defined */
/* Dependency: fuzzy_c32memcasecmp from parts.uchar.string */
#ifndef __local___localdep_fuzzy_c32memcasecmp_defined
#define __local___localdep_fuzzy_c32memcasecmp_defined 1
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c32memcasecmp,(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c32memcasecmp,(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__NO_MALLOCA) && (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/fuzzy_wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c32memcasecmp (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *, __SIZE_TYPE__, __CHAR32_TYPE__ const *, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))
#else /* !__NO_MALLOCA && (__SIZEOF_WCHAR_T__ == 4) */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/fuzzy_c32memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_c32memcasecmp __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp)
#else /* !__NO_MALLOCA */
#undef __local___localdep_fuzzy_c32memcasecmp_defined
#endif /* __NO_MALLOCA */
#endif /* __NO_MALLOCA || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#endif /* !__local___localdep_fuzzy_c32memcasecmp_defined */
__NAMESPACE_LOCAL_END
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_c32scasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(fuzzy_c32scasecmp))(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2) {
	return __localdep_fuzzy_c32memcasecmp(__s1, __localdep_c32slen(__s1), __s2, __localdep_c32slen(__s2));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c32scasecmp_defined
#define __local___localdep_fuzzy_c32scasecmp_defined 1
#define __localdep_fuzzy_c32scasecmp __LIBC_LOCAL_NAME(fuzzy_c32scasecmp)
#endif /* !__local___localdep_fuzzy_c32scasecmp_defined */
#else /* (__CRT_HAVE_fuzzy_wmemcasecmp && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fuzzy_wmemcasecmp || !__NO_MALLOCA */
#undef __local_fuzzy_c32scasecmp_defined
#endif /* (!__CRT_HAVE_fuzzy_wmemcasecmp || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fuzzy_wmemcasecmp && __NO_MALLOCA */
#endif /* !__local_fuzzy_c32scasecmp_defined */
