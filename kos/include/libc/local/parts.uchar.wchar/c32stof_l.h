/* HASH CRC-32:0xdb46e679 */
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
#ifndef __local_c32stof_l_defined
#define __local_c32stof_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32stof_defined
#define __local___localdep_c32stof_defined
#if defined(__CRT_HAVE_wcstof) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,__localdep_c32stof,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_KOS$wcstof)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,__localdep_c32stof,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstof.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stof __NAMESPACE_LOCAL_TYPEHAX(float(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **),float(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **),wcstof)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c32stof.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stof __LIBC_LOCAL_NAME(c32stof)
#endif /* !... */
#endif /* !__local___localdep_c32stof_defined */
__LOCAL_LIBC(c32stof_l) __ATTR_IN(1) __ATTR_OUT_OPT(2) float
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stof_l))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_c32stof)(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stof_l_defined
#define __local___localdep_c32stof_l_defined
#define __localdep_c32stof_l __LIBC_LOCAL_NAME(c32stof_l)
#endif /* !__local___localdep_c32stof_l_defined */
#endif /* !__local_c32stof_l_defined */
