/* HASH CRC-32:0xcc5b4b8f */
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
#ifndef __local___memmovedownq_chk_defined
#define __local___memmovedownq_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmovedownq_defined
#define __local___localdep_memmovedownq_defined
#ifdef __CRT_HAVE_memmovedownq
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedownq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedownq __LIBC_LOCAL_NAME(memmovedownq)
#endif /* !... */
#endif /* !__local___localdep_memmovedownq_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovedownq_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovedownq_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmovedownq", __dst, __n_qwords * 8, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_memmovedownq)(__dst, __src, __n_qwords);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmovedownq_chk_defined
#define __local___localdep___memmovedownq_chk_defined
#define __localdep___memmovedownq_chk __LIBC_LOCAL_NAME(__memmovedownq_chk)
#endif /* !__local___localdep___memmovedownq_chk_defined */
#endif /* !__local___memmovedownq_chk_defined */
