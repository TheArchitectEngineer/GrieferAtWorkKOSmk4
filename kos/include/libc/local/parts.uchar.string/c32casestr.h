/* HASH CRC-32:0xf9875dd7 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32casestr_defined
#define __local_c32casestr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32len_defined
#define __local___localdep_c32len_defined
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_KOS$wcslen)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32len __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcslen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32len.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32len __LIBC_LOCAL_NAME(c32len)
#endif /* !... */
#endif /* !__local___localdep_c32len_defined */
#ifndef __local___localdep_c32memcasecmp_defined
#define __local___localdep_c32memcasecmp_defined
#if defined(__CRT_HAVE_wmemcasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_KOS$wmemcasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcasecmp __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(void const *,void const *,__SIZE_TYPE__),int(__LIBKCALL&)(void const *,void const *,__SIZE_TYPE__),wmemcasecmp)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32memcasecmp __LIBC_LOCAL_NAME(c32memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_c32memcasecmp_defined */
__LOCAL_LIBC(c32casestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32casestr))(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__needle) {
	__SIZE_TYPE__ __needle_len = (__NAMESPACE_LOCAL_SYM __localdep_c32len)(__needle);
	for (; *__haystack; ++__haystack) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_c32memcasecmp)(__haystack, __needle, __needle_len * sizeof(__CHAR32_TYPE__)) == 0)
			return (__CHAR32_TYPE__ *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32casestr_defined
#define __local___localdep_c32casestr_defined
#define __localdep_c32casestr __LIBC_LOCAL_NAME(c32casestr)
#endif /* !__local___localdep_c32casestr_defined */
#endif /* !__local_c32casestr_defined */
