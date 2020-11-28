/* HASH CRC-32:0xc449bf3c */
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
#ifndef _STRINGS_H
#define _STRINGS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_NETBSD
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#endif /* __USE_NETBSD */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
#ifndef __bcopy_defined
#define __bcopy_defined 1
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1, 2)),void,__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),{ return __builtin_bcopy(__src, __dst, __num_bytes); })
#elif defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CDECLARE_VOID_GCCNCX(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),(__src,__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bcopy.h>
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* !... */
#endif /* !__bcopy_defined */
#ifndef __bcmp_defined
#define __bcmp_defined 1
#if defined(__fast_memcmp_defined) && defined(__CRT_HAVE_memcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),memcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_memcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__bcmp_defined */
#ifndef __index_defined
#define __index_defined 1
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),{ return __builtin_index(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack,__needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/index.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(index, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined 1
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),{ return __builtin_rindex(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/rindex.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(rindex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__rindex_defined */

#ifndef __bzero_defined
#define __bzero_defined 1
#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIREDIRECT_GCCNCX(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT_GCCNCX(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID_GCCNCX(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,(__dst,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/bzeroc.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#endif /* !__bzero_defined */

#ifdef __USE_STRING_BWLQ
#ifndef __bzerow_defined
#define __bzerow_defined 1
#if defined(__fast_bzerow_defined) && defined(__CRT_HAVE_bzerow)
__CEIDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); })
#elif defined(__fast_bzerow_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); }
#elif defined(__CRT_HAVE_bzerow)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),(__dst,__num_words))
#else /* ... */
#include <libc/local/string/bzerow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerow))(__dst, __num_words); })
#endif /* !... */
#endif /* !__bzerow_defined */
#ifndef __bzerol_defined
#define __bzerol_defined 1
#if defined(__fast_bzerol_defined) && defined(__CRT_HAVE_bzerol)
__CEIDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); })
#elif defined(__fast_bzerol_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); }
#elif defined(__CRT_HAVE_bzerol)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),(__dst,__num_dwords))
#else /* ... */
#include <libc/local/string/bzerol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerol))(__dst, __num_dwords); })
#endif /* !... */
#endif /* !__bzerol_defined */
#ifndef __bzeroq_defined
#define __bzeroq_defined 1
#if defined(__fast_bzeroq_defined) && defined(__CRT_HAVE_bzeroq)
__CEIDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); })
#elif defined(__fast_bzeroq_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); }
#elif defined(__CRT_HAVE_bzeroq)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),(__dst,__num_qwords))
#else /* ... */
#include <libc/local/string/bzeroq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroq))(__dst, __num_qwords); })
#endif /* !... */
#endif /* !__bzeroq_defined */
#endif /* __USE_STRING_BWLQ */

#ifdef __USE_KOS
#ifndef __bzeroc_defined
#define __bzeroc_defined 1
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/bzeroc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#endif /* !... */
#endif /* !__bzeroc_defined */
#endif /* __USE_KOS */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifndef __strcasecmp_defined
#define __strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined 1
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__strncasecmp_defined */

#ifdef __USE_XOPEN2K8
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined 1
#ifdef __CRT_HAVE_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined 1
#ifdef __CRT_HAVE_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#endif /* !__strncasecmp_l_defined */
#endif /* __USE_XOPEN2K8 */


#if defined(__USE_KOS) || defined(__USE_GNU) || defined(__USE_BSD)
#ifdef __CRT_HAVE_bzero
/* >> explicit_bzero(3)
 * Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CREDIRECT_VOID(,__NOTHROW_NCX,explicit_bzero,(void *__buf, size_t __num_bytes),bzero,(__buf,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
/* >> explicit_bzero(3)
 * Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CDECLARE_VOID(,__NOTHROW_NCX,explicit_bzero,(void *__buf, size_t __num_bytes),(__buf,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
/* >> explicit_bzero(3)
 * Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__CREDIRECT_VOID(,__NOTHROW_NCX,explicit_bzero,(void *__buf, size_t __num_bytes),__bzero,(__buf,__num_bytes))
#else /* ... */
#include <libc/local/strings/explicit_bzero.h>
/* >> explicit_bzero(3)
 * Same as `bzero(buf, num_bytes)', however compilers will not optimize
 * away uses of this function when they (think) that clearing the memory
 * wouldn't have any visible side-effects (though those side-effects
 * may be a security-concious application trying to wipe sensitive data) */
__NAMESPACE_LOCAL_USING_OR_IMPL(explicit_bzero, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL explicit_bzero)(void *__buf, size_t __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(explicit_bzero))(__buf, __num_bytes); })
#endif /* !... */
#endif /* __USE_KOS || __USE_GNU || __USE_BSD */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS) && defined(__HYBRID_PP_VA_OVERLOAD)
/* In C, we can use argument-count overload macros to implement these overloads! */
#ifdef __USE_MISC
#undef __PRIVATE_bzero_3
#undef __PRIVATE_bzero_4
#ifdef __USE_KOS
#define __PRIVATE_bzero_4   bzeroc
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_bzero_4   __libc_bzeroc
#endif /* !__USE_KOS */
#define __PRIVATE_bzero_3   (bzero)
#undef bzero
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define bzero(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define bzero(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (args))(args)
#endif /* ... */
#endif /* __USE_MISC */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS && __HYBRID_PP_VA_OVERLOAD */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8) || defined(__USE_XOPEN2K8XSI)
#ifndef __ffs_defined
#define __ffs_defined 1
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),{ return __builtin_ffs(__i); })
#elif defined(__CRT_HAVE_ffs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),(__i))
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsl,(__i))
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsll,(__i))
#elif defined(__CRT_HAVE___ffs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),__ffs,(__i))
#else /* ... */
#include <libc/local/string/ffs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_UINT_T __NOTHROW(__LIBCCALL ffs)(int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffs))(__i); })
#endif /* !... */
#endif /* !__ffs_defined */
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* unsigned int FFS(INTEGER i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define ffs(i) __hybrid_ffs(i)
#endif /* !__USE_KOS */
#endif /* __USE_MISC || !__USE_XOPEN2K8 || __USE_XOPEN2K8XSI */

#if defined(__USE_NETBSD)
#if __has_builtin(__builtin_popcount) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),{ return __builtin_popcount(__i); })
#elif defined(__CRT_HAVE_popcount)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_INT__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_INT__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcountll,(__i))
#elif __SIZEOF_INT__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_INT__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcount.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount))(__i); })
#endif /* !... */
#if __has_builtin(__builtin_popcountl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountl)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),{ return __builtin_popcountl(__i); })
#elif defined(__CRT_HAVE_popcountl)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcountll,(__i))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcountl.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcountl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcountl))(__i); })
#endif /* !... */
#ifdef __ULONGLONG
#if __has_builtin(__builtin_popcountll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountll)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),{ return __builtin_popcountll(__i); })
#elif defined(__CRT_HAVE_popcountll)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcountl,(__i))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcountll.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcountll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcountll))(__i); })
#endif /* !... */
#endif /* __ULONGLONG */
#if __has_builtin(__builtin_popcount32) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount32)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),{ return __builtin_popcount32(__i); })
#elif defined(__CRT_HAVE_popcount32)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_INT__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcountll,(__i))
#else /* ... */
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount32)(__UINT32_TYPE__ __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))(__i); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#if __has_builtin(__builtin_popcount64) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount64)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),{ return __builtin_popcount64(__i); })
#elif defined(__CRT_HAVE_popcount64)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_INT__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcountll,(__i))
#else /* ... */
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount64)(__UINT64_TYPE__ __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))(__i); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* unsigned int POPCOUNT(unsigned Integer i):
 *     POPulationCOUNT
 *     Return the number of 1-bits in `i' */
#define popcount(i) __hybrid_popcount(i)
#endif /* !__USE_KOS */
#endif /* __USE_NETBSD */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STRINGS_H */
