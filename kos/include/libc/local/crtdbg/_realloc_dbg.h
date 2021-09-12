/* HASH CRC-32:0x21925042 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__realloc_dbg_defined
#define __local__realloc_dbg_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__LOCAL_LIBC(_realloc_dbg) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_realloc_dbg))(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__ptr, __num_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__realloc_dbg_defined
#define __local___localdep__realloc_dbg_defined 1
#define __localdep__realloc_dbg __LIBC_LOCAL_NAME(_realloc_dbg)
#endif /* !__local___localdep__realloc_dbg_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
#undef __local__realloc_dbg_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign */
#endif /* !__local__realloc_dbg_defined */
