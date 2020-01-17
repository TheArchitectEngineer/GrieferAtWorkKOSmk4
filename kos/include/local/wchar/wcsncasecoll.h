/* HASH CRC-32:0xba657f58 */
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
#ifndef __local_wcsncasecoll_defined
#define __local_wcsncasecoll_defined 1
/* Dependency: "wcsncasecmp" from "wchar" */
#ifndef ____localdep_wcsncasecmp_defined
#define ____localdep_wcsncasecmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
#define __localdep_wcsncasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))
#endif /* wcsncasecmp... */
#endif /* !____localdep_wcsncasecmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsncasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncasecoll))(__WCHAR_TYPE__ const *__s1,
                                                          __WCHAR_TYPE__ const *__s2,
                                                          __SIZE_TYPE__ __maxlen) {
#line 4639 "kos/src/libc/magic/string.c"
	return __localdep_wcsncasecmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsncasecoll_defined */
