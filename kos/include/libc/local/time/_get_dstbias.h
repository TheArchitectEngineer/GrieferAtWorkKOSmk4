/* HASH CRC-32:0xef220e89 */
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
#ifndef __local__get_dstbias_defined
#define __local__get_dstbias_defined
#include <__crt.h>
#include <libc/template/dstbias.h>
#ifdef __LOCAL_dstbias
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_get_dstbias) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_get_dstbias))(__LONG32_TYPE__ *__p_result) {
	*__p_result = __LOCAL_dstbias;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_dstbias_defined
#define __local___localdep__get_dstbias_defined
#define __localdep__get_dstbias __LIBC_LOCAL_NAME(_get_dstbias)
#endif /* !__local___localdep__get_dstbias_defined */
#else /* __LOCAL_dstbias */
#undef __local__get_dstbias_defined
#endif /* !__LOCAL_dstbias */
#endif /* !__local__get_dstbias_defined */
