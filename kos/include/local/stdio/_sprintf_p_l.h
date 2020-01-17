/* HASH CRC-32:0x3c9395cd */
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
#ifndef __local__sprintf_p_l_defined
#if 1
#define __local__sprintf_p_l_defined 1
/* Dependency: "_vsprintf_p_l" from "stdio" */
#ifndef ____localdep__vsprintf_p_l_defined
#define ____localdep__vsprintf_p_l_defined 1
#ifdef __CRT_HAVE__vsprintf_p_l
__CREDIRECT(__ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF_P(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsprintf_p_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsprintf_p_l,(__buf,__bufsize,__format,__locale,__args))
#else /* LIBC: _vsprintf_p_l */
#include <local/stdio/_vsprintf_p_l.h>
#define __localdep__vsprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p_l))
#endif /* _vsprintf_p_l... */
#endif /* !____localdep__vsprintf_p_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_sprintf_p_l) __ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF_P(3, 5) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_sprintf_p_l))(char *__restrict __buf,
                                                           __SIZE_TYPE__ __bufsize,
                                                           char const *__restrict __format,
                                                           __locale_t __locale,
                                                           ...) {
#line 2419 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vsprintf_p_l(__buf, __bufsize, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__sprintf_p_l_defined */
