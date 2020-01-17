/* HASH CRC-32:0x1184cf6b */
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
#ifndef __local_strncoll_l_defined
#define __local_strncoll_l_defined 1
/* Dependency: "strncoll" from "string" */
#ifndef ____localdep_strncoll_defined
#define ____localdep_strncoll_defined 1
#ifdef __CRT_HAVE_strncoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncoll,(__s1,__s2,__maxlen))
#else /* LIBC: strncoll */
#include <local/string/strncoll.h>
#define __localdep_strncoll (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))
#endif /* strncoll... */
#endif /* !____localdep_strncoll_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strncoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncoll_l))(char const *__s1,
                                                        char const *__s2,
                                                        __SIZE_TYPE__ __maxlen,
                                                        __locale_t __locale) {
#line 4668 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_strncoll(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strncoll_l_defined */
