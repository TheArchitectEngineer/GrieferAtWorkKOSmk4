/* HASH CRC-32:0x82256b9d */
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
#ifndef __local_wcscmp_defined
#define __local_wcscmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcscmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscmp))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2) {
	__WCHAR_TYPE__ __c1, __c2;
	do {
		if __unlikely((__c1 = *__s1++) != (__c2 = *__s2++))
			return (int)((__WCHAR_TYPE__)__c1 - (__WCHAR_TYPE__)__c2);
	} while (__c1);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscmp_defined
#define __local___localdep_wcscmp_defined
#define __localdep_wcscmp __LIBC_LOCAL_NAME(wcscmp)
#endif /* !__local___localdep_wcscmp_defined */
#endif /* !__local_wcscmp_defined */
