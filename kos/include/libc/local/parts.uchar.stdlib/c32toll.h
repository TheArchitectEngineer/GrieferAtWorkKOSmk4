/* HASH CRC-32:0xe6469d8c */
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
#ifndef __local_c32toll_defined
#define __local_c32toll_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32sto32_defined
#define __local___localdep_c32sto32_defined
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c32sto32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sto32 __NAMESPACE_LOCAL_TYPEHAX(__INT32_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),__INT32_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),wcsto32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c32sto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sto32 __LIBC_LOCAL_NAME(c32sto32)
#endif /* !... */
#endif /* !__local___localdep_c32sto32_defined */
#ifndef __local___localdep_c32sto64_defined
#define __local___localdep_c32sto64_defined
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c32sto64,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sto64 __NAMESPACE_LOCAL_TYPEHAX(__INT64_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),__INT64_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),wcsto64)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c32sto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32sto64 __LIBC_LOCAL_NAME(c32sto64)
#endif /* !... */
#endif /* !__local___localdep_c32sto64_defined */
__LOCAL_LIBC(c32toll) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32toll))(__CHAR32_TYPE__ const *__nptr) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_c32sto32)(__nptr, __NULLPTR, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_c32sto64)(__nptr, __NULLPTR, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32toll_defined
#define __local___localdep_c32toll_defined
#define __localdep_c32toll __LIBC_LOCAL_NAME(c32toll)
#endif /* !__local___localdep_c32toll_defined */
#endif /* !__local_c32toll_defined */
