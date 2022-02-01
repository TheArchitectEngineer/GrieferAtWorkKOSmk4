/* HASH CRC-32:0xef7833d3 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__sprintf_p_defined
#define __local__sprintf_p_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsprintf_p_defined
#define __local___localdep__vsprintf_p_defined
#ifdef __CRT_HAVE__vsprintf_p
__CREDIRECT(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsprintf_p,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args),_vsprintf_p,(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsprintf_p */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsprintf_p.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsprintf_p __LIBC_LOCAL_NAME(_vsprintf_p)
#endif /* !__CRT_HAVE__vsprintf_p */
#endif /* !__local___localdep__vsprintf_p_defined */
__LOCAL_LIBC(_sprintf_p) __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_sprintf_p))(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vsprintf_p)(__buf, __bufsize, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sprintf_p_defined
#define __local___localdep__sprintf_p_defined
#define __localdep__sprintf_p __LIBC_LOCAL_NAME(_sprintf_p)
#endif /* !__local___localdep__sprintf_p_defined */
#endif /* !__local__sprintf_p_defined */
