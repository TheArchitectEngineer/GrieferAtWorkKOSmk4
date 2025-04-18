/* HASH CRC-32:0x27892371 */
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
#ifndef __local_getpass_defined
#define __local_getpass_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpass_r) || defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpass_r_defined
#define __local___localdep_getpass_r_defined
#ifdef __CRT_HAVE_getpass_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2),char *,__NOTHROW_RPC,__localdep_getpass_r,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize),getpass_r,(__prompt,__buf,__bufsize))
#elif defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getpass_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getpass_r __LIBC_LOCAL_NAME(getpass_r)
#else /* ... */
#undef __local___localdep_getpass_r_defined
#endif /* !... */
#endif /* !__local___localdep_getpass_r_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getpass) __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpass))(char const *__restrict __prompt) {
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
	static char *__getpass_buf = __NULLPTR;
	if (!__getpass_buf) {
		/* Lazily allocate buffer. */
		__getpass_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(257 * sizeof(char)); /* `getpassphrase()' requires passwords at least this long! */
//		getpass_buf = (char *)malloc(129 * sizeof(char)); /* 129 == _PASSWORD_LEN + 1 */
		if __unlikely(!__getpass_buf)
			return __NULLPTR;
	}
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
	static char __getpass_buf[257]; /* `getpassphrase()' requires passwords at least this long! */
//	static char getpass_buf[129]; /* 129 == _PASSWORD_LEN + 1 */
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
	return (__NAMESPACE_LOCAL_SYM __localdep_getpass_r)(__prompt, __getpass_buf, 257);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpass_defined
#define __local___localdep_getpass_defined
#define __localdep_getpass __LIBC_LOCAL_NAME(getpass)
#endif /* !__local___localdep_getpass_defined */
#else /* __CRT_HAVE_getpass_r || __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read || __CRT_HAVE_readpassphrase */
#undef __local_getpass_defined
#endif /* !__CRT_HAVE_getpass_r && !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read && !__CRT_HAVE_readpassphrase */
#endif /* !__local_getpass_defined */
