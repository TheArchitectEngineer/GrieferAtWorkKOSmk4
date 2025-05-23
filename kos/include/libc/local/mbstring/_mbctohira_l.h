/* HASH CRC-32:0xaeee840a */
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
#ifndef __local__mbctohira_l_defined
#define __local__mbctohira_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbckata_l) || defined(__CRT_HAVE__getmbcp)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbckata_l_defined
#define __local___localdep__ismbckata_l_defined
#ifdef __CRT_HAVE__ismbckata_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbckata_l,(unsigned int __ch, __locale_t __locale),_ismbckata_l,(__ch,__locale))
#elif defined(__CRT_HAVE__getmbcp)
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_ismbckata_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbckata_l __LIBC_LOCAL_NAME(_ismbckata_l)
#else /* ... */
#undef __local___localdep__ismbckata_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbckata_l_defined */
__LOCAL_LIBC(_mbctohira_l) __ATTR_PURE __ATTR_WUNUSED unsigned int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbctohira_l))(unsigned int __ch, __locale_t __locale) {
	/* Extrapolated from reverse engineering. */
	if ((__NAMESPACE_LOCAL_SYM __localdep__ismbckata_l)(__ch, __locale) && __ch < 0x8394) {
		if (__ch < 0x837f) {
			__ch -= 0xa1;
		} else {
			__ch -= 0xa2;
		}
	}
	return __ch;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbctohira_l_defined
#define __local___localdep__mbctohira_l_defined
#define __localdep__mbctohira_l __LIBC_LOCAL_NAME(_mbctohira_l)
#endif /* !__local___localdep__mbctohira_l_defined */
#else /* __CRT_HAVE__ismbckata_l || __CRT_HAVE__getmbcp */
#undef __local__mbctohira_l_defined
#endif /* !__CRT_HAVE__ismbckata_l && !__CRT_HAVE__getmbcp */
#endif /* !__local__mbctohira_l_defined */
