/* HASH CRC-32:0x488cc78 */
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
#ifndef __local_vfprintf_defined
#define __local_vfprintf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_file_printer_unlocked_defined
#define __local___localdep_file_printer_unlocked_defined
#ifdef __CRT_HAVE_file_printer_unlocked
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__FORMATPRINTER_CC,__localdep_file_printer_unlocked,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_printer)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__FORMATPRINTER_CC,__localdep_file_printer_unlocked,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/file_printer_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_file_printer_unlocked __LIBC_LOCAL_NAME(file_printer_unlocked)
#else /* ... */
#undef __local___localdep_file_printer_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_file_printer_unlocked_defined */
#ifndef __local___localdep_flockfile_defined
#define __local___localdep_flockfile_defined
#ifdef __CRT_HAVE_flockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#else /* ... */
#undef __local___localdep_flockfile_defined
#endif /* !... */
#endif /* !__local___localdep_flockfile_defined */
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_funlockfile_defined
#define __local___localdep_funlockfile_defined
#ifdef __CRT_HAVE_funlockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#else /* ... */
#undef __local___localdep_funlockfile_defined
#endif /* !... */
#endif /* !__local___localdep_funlockfile_defined */
__LOCAL_LIBC(vfprintf) __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vfprintf))(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) {
	__STDC_INT_AS_SSIZE_T __result;
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_flockfile)(__stream);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	__result = (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_file_printer_unlocked), __stream, __format, __args);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_funlockfile)(__stream);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfprintf_defined
#define __local___localdep_vfprintf_defined
#define __localdep_vfprintf __LIBC_LOCAL_NAME(vfprintf)
#endif /* !__local___localdep_vfprintf_defined */
#else /* __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#undef __local_vfprintf_defined
#endif /* !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock */
#endif /* !__local_vfprintf_defined */
