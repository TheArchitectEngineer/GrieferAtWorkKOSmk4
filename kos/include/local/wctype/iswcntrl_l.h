/* HASH CRC-32:0x953a3502 */
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
#ifndef __local_iswcntrl_l_defined
#define __local_iswcntrl_l_defined 1
/* Dependency: "iswcntrl" from "wctype" */
#ifndef ____localdep_iswcntrl_defined
#define ____localdep_iswcntrl_defined 1
#if __has_builtin(__builtin_iswcntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswcntrl)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswcntrl)(__WINT_TYPE__ __wc) { return __builtin_iswcntrl(__wc); }
#elif defined(__CRT_HAVE_iswcntrl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswcntrl,(__WINT_TYPE__ __wc),iswcntrl,(__wc))
#else /* LIBC: iswcntrl */
#include <local/wctype/iswcntrl.h>
#define __localdep_iswcntrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl))
#endif /* iswcntrl... */
#endif /* !____localdep_iswcntrl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswcntrl_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswcntrl_l))(__WINT_TYPE__ __wc,
                                                        __locale_t __locale) {
#line 245 "kos/src/libc/magic/wctype.c"
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswcntrl(__wc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_iswcntrl_l_defined */
