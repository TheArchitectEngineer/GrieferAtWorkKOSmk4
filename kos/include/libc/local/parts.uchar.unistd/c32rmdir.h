/* HASH CRC-32:0x49c9cf37 */
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
#ifndef __local_c32rmdir_defined
#define __local_c32rmdir_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wunlinkat))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32unlinkat_defined
#define __local___localdep_c32unlinkat_defined
#if defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32unlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_KOS$wunlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32unlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* ... */
#undef __local___localdep_c32unlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c32unlinkat_defined */
__LOCAL_LIBC(c32rmdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32rmdir))(__CHAR32_TYPE__ const *__path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c32unlinkat)(__AT_FDCWD, __path, __AT_REMOVEDIR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32rmdir_defined
#define __local___localdep_c32rmdir_defined
#define __localdep_c32rmdir __LIBC_LOCAL_NAME(c32rmdir)
#endif /* !__local___localdep_c32rmdir_defined */
#else /* __AT_FDCWD && __AT_REMOVEDIR && ((__CRT_HAVE_wunlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wunlinkat) */
#undef __local_c32rmdir_defined
#endif /* !__AT_FDCWD || !__AT_REMOVEDIR || ((!__CRT_HAVE_wunlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wunlinkat) */
#endif /* !__local_c32rmdir_defined */
