/* HASH CRC-32:0x49d0bdbd */
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
#ifndef __local_nl_langinfo_l_defined
#define __local_nl_langinfo_l_defined
#include <__crt.h>
#include <bits/crt/langinfo.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_nl_langinfo_defined
#define __local___localdep_nl_langinfo_defined
#ifdef __CRT_HAVE_nl_langinfo
__CREDIRECT(__ATTR_RETNONNULL,char __KOS_FIXED_CONST *,__NOTHROW_NCX,__localdep_nl_langinfo,(__nl_item __item),nl_langinfo,(__item))
#else /* __CRT_HAVE_nl_langinfo */
__NAMESPACE_LOCAL_END
#include <libc/local/langinfo/nl_langinfo.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nl_langinfo __LIBC_LOCAL_NAME(nl_langinfo)
#endif /* !__CRT_HAVE_nl_langinfo */
#endif /* !__local___localdep_nl_langinfo_defined */
__LOCAL_LIBC(nl_langinfo_l) __ATTR_RETNONNULL char __KOS_FIXED_CONST *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(nl_langinfo_l))(__nl_item __item, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_nl_langinfo)(__item);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_nl_langinfo_l_defined
#define __local___localdep_nl_langinfo_l_defined
#define __localdep_nl_langinfo_l __LIBC_LOCAL_NAME(nl_langinfo_l)
#endif /* !__local___localdep_nl_langinfo_l_defined */
#endif /* !__local_nl_langinfo_l_defined */
