/* HASH CRC-32:0xf4b56c42 */
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
#ifndef __local_format_c32printf_defined
#define __local_format_c32printf_defined
#include <__crt.h>
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vc32printf_defined
#define __local___localdep_format_vc32printf_defined
#if defined(__CRT_HAVE_format_vwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vc32printf,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif defined(__CRT_HAVE_KOS$format_vwprintf)
__CREDIRECT_KOS(__ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vc32printf,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32printf __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBKCALL*)(__pc32formatprinter,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__SSIZE_TYPE__(__LIBKCALL&)(__pc32formatprinter,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),format_vwprintf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_vc32printf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32printf __LIBC_LOCAL_NAME(format_vc32printf)
#endif /* !... */
#endif /* !__local___localdep_format_vc32printf_defined */
__LOCAL_LIBC(format_c32printf) __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_CB(__LIBKCALL __LIBC_LOCAL_NAME(format_c32printf))(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __format, ...) {
	__SSIZE_TYPE__ __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_format_vc32printf)(__printer, __arg, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_c32printf_defined
#define __local___localdep_format_c32printf_defined
#define __localdep_format_c32printf __LIBC_LOCAL_NAME(format_c32printf)
#endif /* !__local___localdep_format_c32printf_defined */
#endif /* !__local_format_c32printf_defined */
