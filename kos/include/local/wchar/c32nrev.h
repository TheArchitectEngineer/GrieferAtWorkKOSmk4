/* HASH CRC-32:0x4e44cae5 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32nrev_defined
#define __local_c32nrev_defined 1
/* Dependency: "memrevw" from "string" */
#ifndef ____localdep_memrevw_defined
#define ____localdep_memrevw_defined 1
#if defined(__CRT_HAVE_memrevw)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),memrevw,(__base,__n_words))
#else /* LIBC: memrevw */
#include <local/string/memrevw.h>
#define __localdep_memrevw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevw))
#endif /* memrevw... */
#endif /* !____localdep_memrevw_defined */

/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_c32nlen_defined
#define ____localdep_c32nlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c32nlen */
#include <local/wchar/c32nlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))
#endif /* c32nlen... */
#endif /* !____localdep_c32nlen_defined */

/* Dependency: "memrevl" from "string" */
#ifndef ____localdep_memrevl_defined
#define ____localdep_memrevl_defined 1
#if defined(__CRT_HAVE_memrevl)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),memrevl,(__base,__n_dwords))
#else /* LIBC: memrevl */
#include <local/string/memrevl.h>
#define __localdep_memrevl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevl))
#endif /* memrevl... */
#endif /* !____localdep_memrevl_defined */

/* Dependency: "memrev" from "string" */
#ifndef ____localdep_memrev_defined
#define ____localdep_memrev_defined 1
#if defined(__CRT_HAVE_memrev)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* LIBC: memrev */
#include <local/string/memrev.h>
#define __localdep_memrev (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))
#endif /* memrev... */
#endif /* !____localdep_memrev_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32nrev) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32nrev))(__CHAR32_TYPE__ *__restrict __str,
                                                     __SIZE_TYPE__ __maxlen) {
#line 1224 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (__CHAR32_TYPE__ *)__localdep_memrevw(__str, __localdep_c32nlen(__str, __maxlen));
#elif 4 == 4
	return (__CHAR32_TYPE__ *)__localdep_memrevl(__str, __localdep_c32nlen(__str, __maxlen));
#else
	return (__CHAR32_TYPE__ *)__localdep_memrev(__str, __localdep_c32nlen(__str, __maxlen) * sizeof(__CHAR32_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32nrev_defined */
