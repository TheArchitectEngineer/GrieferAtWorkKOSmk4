/* HASH CRC-32:0xe907240 */
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
#ifndef __local_wmemcpy_s_defined
#define __local_wmemcpy_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wmemcpy_s) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemcpy_s))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstlength, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __srclength) {
	if (!__srclength)
		return 0;
	if (__dst == __NULLPTR)
		return 22;
	if (!__src || __dstlength < __srclength) {
		__libc_memsetc(__dst, 0, __dstlength, __SIZEOF_WCHAR_T__);
		if (!__src)
			return 22;
		if (__dstlength < __srclength)
			return 34;
		return 22;
	}
	__libc_memcpyc(__dst, __src, __srclength, __SIZEOF_WCHAR_T__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmemcpy_s_defined
#define __local___localdep_wmemcpy_s_defined
#define __localdep_wmemcpy_s __LIBC_LOCAL_NAME(wmemcpy_s)
#endif /* !__local___localdep_wmemcpy_s_defined */
#endif /* !__local_wmemcpy_s_defined */
