/* HASH CRC-32:0x63b01596 */
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
#ifndef __local_symlink_defined
#define __local_symlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_symlinkat_defined
#define __local___localdep_symlinkat_defined
#ifdef __CRT_HAVE_symlinkat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),symlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_fsymlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/symlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_symlinkat __LIBC_LOCAL_NAME(symlinkat)
#else /* ... */
#undef __local___localdep_symlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_symlinkat_defined */
__LOCAL_LIBC(symlink) __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(symlink))(char const *__link_text, char const *__target_path) {
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return (__NAMESPACE_LOCAL_SYM __localdep_symlinkat)(__link_text, __AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_symlink_defined
#define __local___localdep_symlink_defined
#define __localdep_symlink __LIBC_LOCAL_NAME(symlink)
#endif /* !__local___localdep_symlink_defined */
#else /* __AT_FDCWD && (__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat) */
#undef __local_symlink_defined
#endif /* !__AT_FDCWD || (!__CRT_HAVE_symlinkat && !__CRT_HAVE_fsymlinkat) */
#endif /* !__local_symlink_defined */
