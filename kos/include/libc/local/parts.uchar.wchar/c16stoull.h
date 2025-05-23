/* HASH CRC-32:0xd1523809 */
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
#ifndef __local_c16stoull_defined
#define __local_c16stoull_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16stou32_defined
#define __local___localdep_c16stou32_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c16stou32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16stou32 __NAMESPACE_LOCAL_TYPEHAX(__UINT32_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__UINT32_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstou32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c16stou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16stou32 __LIBC_LOCAL_NAME(c16stou32)
#endif /* !... */
#endif /* !__local___localdep_c16stou32_defined */
#ifndef __local___localdep_c16stou64_defined
#define __local___localdep_c16stou64_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c16stou64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16stou64 __NAMESPACE_LOCAL_TYPEHAX(__UINT64_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__UINT64_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstou64)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c16stou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16stou64 __LIBC_LOCAL_NAME(c16stou64)
#endif /* !... */
#endif /* !__local___localdep_c16stou64_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stoull) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stoull))(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_c16stou32)(__nptr, __endptr, __base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_c16stou64)(__nptr, __endptr, __base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16stoull_defined
#define __local___localdep_c16stoull_defined
#define __localdep_c16stoull __LIBC_LOCAL_NAME(c16stoull)
#endif /* !__local___localdep_c16stoull_defined */
#endif /* !__local_c16stoull_defined */
