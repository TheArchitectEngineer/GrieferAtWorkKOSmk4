/* HASH CRC-32:0xf15c04ab */
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
#ifndef __local_memlenq_defined
#define __local_memlenq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memendq_defined
#define __local___localdep_memendq_defined
#ifdef __CRT_HAVE_memendq
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memendq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memendq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memendq __LIBC_LOCAL_NAME(memendq)
#endif /* !__CRT_HAVE_memendq */
#endif /* !__local___localdep_memendq_defined */
__LOCAL_LIBC(memlenq) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memlenq))(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_memendq)(__haystack, __needle, __n_qwords) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memlenq_defined
#define __local___localdep_memlenq_defined
#define __localdep_memlenq __LIBC_LOCAL_NAME(memlenq)
#endif /* !__local___localdep_memlenq_defined */
#endif /* !__local_memlenq_defined */
