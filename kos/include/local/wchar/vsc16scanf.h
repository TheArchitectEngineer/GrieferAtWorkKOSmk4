/* HASH CRC-32:0xe66ed920 */
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
#ifndef __local_vsc16scanf_defined
#define __local_vsc16scanf_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(vsc16scanf))(__CHAR16_TYPE__ const *__restrict __src,
                                                        __CHAR16_TYPE__ const *__restrict __format,
                                                        __builtin_va_list __args) {
#line 745 "kos/src/libc/magic/wchar.c"
	/* TODO: format_wscanf() */
	(void)__src;
	(void)__format;
	(void)__args;
	__COMPILER_IMPURE();
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_vsc16scanf_defined */
