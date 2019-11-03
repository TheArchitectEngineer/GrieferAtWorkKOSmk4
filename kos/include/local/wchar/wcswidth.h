/* HASH CRC-32:0x477631fe */
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
#ifndef __local_wcswidth_defined
#define __local_wcswidth_defined 1
/* Dependency: "wcwidth" from "wchar" */
#ifndef ____localdep_wcwidth_defined
#define ____localdep_wcwidth_defined 1
#if defined(__CRT_HAVE_wcwidth)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_wcwidth,(__WCHAR_TYPE__ __ch),wcwidth,(__ch))
#else /* LIBC: wcwidth */
#include <local/wchar/wcwidth.h>
#define __localdep_wcwidth (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))
#endif /* wcwidth... */
#endif /* !____localdep_wcwidth_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcswidth) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcswidth))(__WCHAR_TYPE__ const *__restrict __string,
                                                      __SIZE_TYPE__ __num_chars) {
#line 793 "kos/src/libc/magic/wchar.c"
	int __temp, __result = 0;
	for (; __num_chars; --__num_chars, ++__string) {
		__WCHAR_TYPE__ __ch = *__string;
		if (!__ch)
			break;
		__temp = __localdep_wcwidth(__ch);
		if (__temp < 0)
			return __temp;
		__result += __temp;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcswidth_defined */
