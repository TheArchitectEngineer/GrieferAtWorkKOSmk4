/* HASH CRC-32:0xfef46f05 */
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
#ifndef __local_c16pncpy_defined
#define __local_c16pncpy_defined 1
/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_c16nlen_defined
#define ____localdep_c16nlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c16nlen */
#include <local/wchar/c16nlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))
#endif /* c16nlen... */
#endif /* !____localdep_c16nlen_defined */

/* Dependency: "wmemcpy" from "wchar" */
#ifndef ____localdep_c16memcpy_defined
#define ____localdep_c16memcpy_defined 1
#if defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16memcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmemcpy.h>
#define __localdep_c16memcpy(dst, src, num_chars) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))((__WCHAR_TYPE__ *)(dst), (__WCHAR_TYPE__ const *)(src), num_chars)
#else /* LIBC: c16memcpy */
#include <local/wchar/c16memcpy.h>
#define __localdep_c16memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16memcpy))
#endif /* c16memcpy... */
#endif /* !____localdep_c16memcpy_defined */

/* Dependency: "wmempset" from "wchar" */
#ifndef ____localdep_c16mempset_defined
#define ____localdep_c16mempset_defined 1
#if defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempset,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmempset,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_c16mempset(dst, filler, num_chars) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))((__WCHAR_TYPE__ *)(dst), (__WCHAR_TYPE__)(filler), num_chars)
#else /* LIBC: c16mempset */
#include <local/wchar/c16mempset.h>
/* Same as wmemset, but return a pointer after the last written character */
#define __localdep_c16mempset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempset))
#endif /* c16mempset... */
#endif /* !____localdep_c16mempset_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as wcsncpy, but return a pointer after the last written character */
__LOCAL_LIBC(c16pncpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16pncpy))(__CHAR16_TYPE__ *__restrict __buf,
                                                      __CHAR16_TYPE__ const *__restrict __src,
                                                      __SIZE_TYPE__ __buflen) {
#line 1369 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __srclen = __localdep_c16nlen(__src, __buflen);
	__localdep_c16memcpy(__buf, __src, __srclen);
	return __localdep_c16mempset(__buf+__srclen, '\0', __buflen - __srclen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16pncpy_defined */
