/* HASH CRC-32:0x43132eb7 */
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
#ifndef __local_vscanf_s_defined
#define __local_vscanf_s_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__CRT_HAVE__vscanf_s_l) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__doscan) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE_vfscanf_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vscanf_s_l_defined
#define __local___localdep__vscanf_s_l_defined
#ifdef __CRT_HAVE__vscanf_s_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep__vscanf_s_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),_vscanf_s_l,(__format,__locale,__args))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__doscan) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE_vfscanf_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vscanf_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vscanf_s_l __LIBC_LOCAL_NAME(_vscanf_s_l)
#else /* ... */
#undef __local___localdep__vscanf_s_l_defined
#endif /* !... */
#endif /* !__local___localdep__vscanf_s_l_defined */
__LOCAL_LIBC(vscanf_s) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vscanf_s))(char const *__format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep__vscanf_s_l)(__format, __NULLPTR, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vscanf_s_defined
#define __local___localdep_vscanf_s_defined
#define __localdep_vscanf_s __LIBC_LOCAL_NAME(vscanf_s)
#endif /* !__local___localdep_vscanf_s_defined */
#else /* __CRT_HAVE__vscanf_s_l || (__LOCAL_stdin && (__CRT_HAVE__vfscanf_s_l || __CRT_HAVE___stdio_common_vfscanf || __CRT_HAVE_vfscanf || __CRT_HAVE__IO_vfscanf || __CRT_HAVE___vfscanf || __CRT_HAVE__doscan || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE_vfscanf_unlocked || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#undef __local_vscanf_s_defined
#endif /* !__CRT_HAVE__vscanf_s_l && (!__LOCAL_stdin || (!__CRT_HAVE__vfscanf_s_l && !__CRT_HAVE___stdio_common_vfscanf && !__CRT_HAVE_vfscanf && !__CRT_HAVE__IO_vfscanf && !__CRT_HAVE___vfscanf && !__CRT_HAVE__doscan && !__CRT_HAVE__vfscanf && !__CRT_HAVE__vfscanf_s && !__CRT_HAVE_vfscanf_unlocked && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)))) */
#endif /* !__local_vscanf_s_defined */
