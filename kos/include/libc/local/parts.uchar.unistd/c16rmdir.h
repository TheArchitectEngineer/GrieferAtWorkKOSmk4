/* HASH CRC-32:0xc4e5013f */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16rmdir_defined
#define __local_c16rmdir_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wunlinkat))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16unlinkat_defined
#define __local___localdep_c16unlinkat_defined
#if defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c16unlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c16unlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* ... */
#undef __local___localdep_c16unlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c16unlinkat_defined */
__LOCAL_LIBC(c16rmdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16rmdir))(__CHAR16_TYPE__ const *__path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c16unlinkat)(__AT_FDCWD, __path, __AT_REMOVEDIR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16rmdir_defined
#define __local___localdep_c16rmdir_defined
#define __localdep_c16rmdir __LIBC_LOCAL_NAME(c16rmdir)
#endif /* !__local___localdep_c16rmdir_defined */
#else /* __AT_FDCWD && __AT_REMOVEDIR && ((__CRT_HAVE_wunlinkat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wunlinkat) */
#undef __local_c16rmdir_defined
#endif /* !__AT_FDCWD || !__AT_REMOVEDIR || ((!__CRT_HAVE_wunlinkat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wunlinkat) */
#endif /* !__local_c16rmdir_defined */
