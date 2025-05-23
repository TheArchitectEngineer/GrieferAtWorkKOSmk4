/* HASH CRC-32:0x4b3e0124 */
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
#ifndef __local__ismbcdigit_defined
#define __local__ismbcdigit_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbcdigit_l_defined
#define __local___localdep__ismbcdigit_l_defined
#ifdef __CRT_HAVE__ismbcdigit_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbcdigit_l,(unsigned int __ch, __locale_t __locale),_ismbcdigit_l,(__ch,__locale))
#else /* __CRT_HAVE__ismbcdigit_l */
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_ismbcdigit_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbcdigit_l __LIBC_LOCAL_NAME(_ismbcdigit_l)
#endif /* !__CRT_HAVE__ismbcdigit_l */
#endif /* !__local___localdep__ismbcdigit_l_defined */
__LOCAL_LIBC(_ismbcdigit) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbcdigit))(unsigned int __ch) {
	return (__NAMESPACE_LOCAL_SYM __localdep__ismbcdigit_l)(__ch, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbcdigit_defined
#define __local___localdep__ismbcdigit_defined
#define __localdep__ismbcdigit __LIBC_LOCAL_NAME(_ismbcdigit)
#endif /* !__local___localdep__ismbcdigit_defined */
#endif /* !__local__ismbcdigit_defined */
