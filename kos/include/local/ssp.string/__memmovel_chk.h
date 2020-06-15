/* HASH CRC-32:0x7ae02aa4 */
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
#ifndef __local___memmovel_chk_defined
#define __local___memmovel_chk_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memmovel from string */
#ifndef __local___localdep_memmovel_defined
#define __local___localdep_memmovel_defined 1
#ifdef __CRT_HAVE_memmovel
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__PE__)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovel.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovel __LIBC_LOCAL_NAME(memmovel)
#endif /* !... */
#endif /* !__local___localdep_memmovel_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovel_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovel_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmovel", __dst, __n_dwords * 4, __dst_objsize);
	return __localdep_memmovel(__dst, __src, __n_dwords);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmovel_chk_defined
#define __local___localdep___memmovel_chk_defined 1
#define __localdep___memmovel_chk __LIBC_LOCAL_NAME(__memmovel_chk)
#endif /* !__local___localdep___memmovel_chk_defined */
#endif /* !__local___memmovel_chk_defined */
