/* HASH CRC-32:0x65fd396c */
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
#ifndef __local_strnunvis_netbsd_defined
#define __local_strnunvis_netbsd_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnunvisx_defined
#define __local___localdep_strnunvisx_defined
#ifdef __CRT_HAVE_strnunvisx
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnunvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags),strnunvisx,(__dst,__dstsize,__src,__flags))
#else /* __CRT_HAVE_strnunvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnunvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnunvisx __LIBC_LOCAL_NAME(strnunvisx)
#endif /* !__CRT_HAVE_strnunvisx */
#endif /* !__local___localdep_strnunvisx_defined */
__LOCAL_LIBC(strnunvis_netbsd) __ATTR_IN(3) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnunvis_netbsd))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strnunvisx)(__dst, __dstsize, __src, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnunvis_netbsd_defined
#define __local___localdep_strnunvis_netbsd_defined
#define __localdep_strnunvis_netbsd __LIBC_LOCAL_NAME(strnunvis_netbsd)
#endif /* !__local___localdep_strnunvis_netbsd_defined */
#endif /* !__local_strnunvis_netbsd_defined */
