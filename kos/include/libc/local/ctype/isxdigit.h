/* HASH CRC-32:0xdf8497d1 */
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
#ifndef __local_isxdigit_defined
#define __local_isxdigit_defined
#include <__crt.h>
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isxdigit) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isxdigit))(int __ch) {
#ifdef __crt_isxdigit
	return __crt_isxdigit(__ch);
#else /* __crt_isxdigit */
	return __ascii_isxdigit(__ch);
#endif /* !__crt_isxdigit */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isxdigit_defined
#define __local___localdep_isxdigit_defined
#define __localdep_isxdigit __LIBC_LOCAL_NAME(isxdigit)
#endif /* !__local___localdep_isxdigit_defined */
#endif /* !__local_isxdigit_defined */
