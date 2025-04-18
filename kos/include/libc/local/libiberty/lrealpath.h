/* HASH CRC-32:0xb60441e6 */
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
#ifndef __local_lrealpath_defined
#define __local_lrealpath_defined
#include <__crt.h>
#if defined(__CRT_HAVE_canonicalize_file_name) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_canonicalize_file_name_defined
#define __local___localdep_canonicalize_file_name_defined
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_RPC,__localdep_canonicalize_file_name,(char const *__filename),canonicalize_file_name,(__filename))
#endif /* !__local___localdep_canonicalize_file_name_defined */
#ifndef __local___localdep_strdup_defined
#define __local___localdep_strdup_defined
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE__mbsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),_mbsdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/string/strdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strdup __LIBC_LOCAL_NAME(strdup)
#else /* ... */
#undef __local___localdep_strdup_defined
#endif /* !... */
#endif /* !__local___localdep_strdup_defined */
__LOCAL_LIBC(lrealpath) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lrealpath))(char const *__path) {
	char *__result = (__NAMESPACE_LOCAL_SYM __localdep_canonicalize_file_name)(__path);
	if (__result == __NULLPTR)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strdup)(__path);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lrealpath_defined
#define __local___localdep_lrealpath_defined
#define __localdep_lrealpath __LIBC_LOCAL_NAME(lrealpath)
#endif /* !__local___localdep_lrealpath_defined */
#else /* __CRT_HAVE_canonicalize_file_name && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE__mbsdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
#undef __local_lrealpath_defined
#endif /* !__CRT_HAVE_canonicalize_file_name || (!__CRT_HAVE_strdup && !__CRT_HAVE__strdup && !__CRT_HAVE__mbsdup && !__CRT_HAVE___strdup && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) */
#endif /* !__local_lrealpath_defined */
