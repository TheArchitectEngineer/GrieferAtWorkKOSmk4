/* HASH CRC-32:0x1ed4af02 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16memcasecmp_defined
#define __local_c16memcasecmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tolower16_defined
#define __local___localdep_tolower16_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 2
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW(__LIBDCALL __localdep_tolower16)(__WINT16_TYPE__ __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,(__wc))
#elif defined(__CRT_HAVE_DOS$towlower)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower16 __NAMESPACE_LOCAL_TYPEHAX(__WINT16_TYPE__(__LIBDCALL*)(__WINT16_TYPE__),__WINT16_TYPE__(__LIBDCALL&)(__WINT16_TYPE__),towlower)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/tolower16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower16 __LIBC_LOCAL_NAME(tolower16)
#endif /* !... */
#endif /* !__local___localdep_tolower16_defined */
__LOCAL_LIBC(c16memcasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16memcasecmp))(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) {
	__CHAR16_TYPE__ const *__p1 = (__CHAR16_TYPE__ const *)__s1;
	__CHAR16_TYPE__ const *__p2 = (__CHAR16_TYPE__ const *)__s2;
	__CHAR16_TYPE__ __v1, __v2;
	__v1 = 0;
	__v2 = 0;
	while (__num_chars--) {
		__v1 = *__p1++;
		__v2 = *__p2++;
		if (__v1 != __v2) {
			__v1 = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)(__v1);
			__v2 = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)(__v2);
			if (__v1 != __v2)
				break;
		}
	}
#if __SIZEOF_INT__ > 2
	return (int)__v1 - (int)__v2;
#else /* __SIZEOF_INT__ > 2 */
	if (__v1 < __v2)
		return -1;
	if (__v1 > __v2)
		return 1;
	return 0;
#endif /* __SIZEOF_INT__ <= 2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16memcasecmp_defined
#define __local___localdep_c16memcasecmp_defined
#define __localdep_c16memcasecmp __LIBC_LOCAL_NAME(c16memcasecmp)
#endif /* !__local___localdep_c16memcasecmp_defined */
#endif /* !__local_c16memcasecmp_defined */
