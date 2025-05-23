/* HASH CRC-32:0xb4f18cd */
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
#ifndef __local_reallocarr_defined
#define __local_reallocarr_defined
#include <__crt.h>
#if defined(__CRT_HAVE_reallocarray) || defined(__CRT_HAVE___libc_reallocarray) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_reallocarray_defined
#define __local___localdep_reallocarray_defined
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE___libc_reallocarray)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),__libc_reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_reallocarray __LIBC_LOCAL_NAME(reallocarray)
#else /* ... */
#undef __local___localdep_reallocarray_defined
#endif /* !... */
#endif /* !__local___localdep_reallocarray_defined */
__LOCAL_LIBC(reallocarr) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(reallocarr))(void *__ptr_p, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
	void **__p_ptr = (void **)__ptr_p;
	void *__result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_reallocarray)(*__p_ptr, __elem_count, __elem_size);
	if __unlikely(!__result)
		return -1;
	*__p_ptr = __result;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_reallocarr_defined
#define __local___localdep_reallocarr_defined
#define __localdep_reallocarr __LIBC_LOCAL_NAME(reallocarr)
#endif /* !__local___localdep_reallocarr_defined */
#else /* __CRT_HAVE_reallocarray || __CRT_HAVE___libc_reallocarray || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_reallocarr_defined
#endif /* !__CRT_HAVE_reallocarray && !__CRT_HAVE___libc_reallocarray && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_reallocarr_defined */
