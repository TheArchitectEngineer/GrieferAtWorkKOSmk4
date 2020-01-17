/* HASH CRC-32:0xc2bdb1b0 */
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
#ifndef __local_wctomb_s_defined
#define __local_wctomb_s_defined 1
#include <parts/errno.h>
/* Dependency: "wctomb" from "stdlib" */
#ifndef ____localdep_wctomb_defined
#define ____localdep_wctomb_defined 1
#ifdef __CRT_HAVE_wctomb
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_wctomb,(char *__str, __WCHAR_TYPE__ __wc),wctomb,(__str,__wc))
#else /* LIBC: wctomb */
#include <local/stdlib/wctomb.h>
#define __localdep_wctomb (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))
#endif /* wctomb... */
#endif /* !____localdep_wctomb_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wctomb_s) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctomb_s))(int *__presult,
                                                      char *__buf,
                                                      __SIZE_TYPE__ __buflen,
                                                      __WCHAR_TYPE__ __wc) {
#line 2532 "kos/src/libc/magic/stdlib.c"
	if (!__presult || !__buf)
		return __EINVAL;
	if (__buflen < MB_CUR_MAX)
		return __ERANGE;
	*__presult = __localdep_wctomb(__buf, __wc);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wctomb_s_defined */
