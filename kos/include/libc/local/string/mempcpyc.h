/* HASH CRC-32:0x17dbe522 */
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
#ifndef __local_mempcpyc_defined
#define __local_mempcpyc_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_mempcpyl_defined
#define __local___localdep_mempcpyl_defined
#ifdef __CRT_HAVE_mempcpyl
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempcpy) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyl __LIBC_LOCAL_NAME(mempcpyl)
#endif /* !... */
#endif /* !__local___localdep_mempcpyl_defined */
#ifndef __local___localdep_mempcpyq_defined
#define __local___localdep_mempcpyq_defined
#ifdef __CRT_HAVE_mempcpyq
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempcpyq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_mempcpyq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyq __LIBC_LOCAL_NAME(mempcpyq)
#endif /* !__CRT_HAVE_mempcpyq */
#endif /* !__local___localdep_mempcpyq_defined */
#ifndef __local___localdep_mempcpyw_defined
#define __local___localdep_mempcpyw_defined
#ifdef __CRT_HAVE_mempcpyw
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempcpy) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyw __LIBC_LOCAL_NAME(mempcpyw)
#endif /* !... */
#endif /* !__local___localdep_mempcpyw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mempcpyc) __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempcpyc))(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__dst, __src, __elem_count);

	case 2:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempcpyw)(__dst, __src, __elem_count);

	case 4:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempcpyl)(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempcpyq)(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return (__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__dst, __src, __elem_count * __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__local___localdep_mempcpyc_defined */
#endif /* !__local_mempcpyc_defined */
