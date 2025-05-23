/* HASH CRC-32:0x93fb6d15 */
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
#ifndef __local_lchown_defined
#define __local_lchown_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchownat)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fchownat_defined
#define __local___localdep_fchownat_defined
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_fchownat,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),fchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* !__local___localdep_fchownat_defined */
__LOCAL_LIBC(lchown) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lchown))(char const *__file, __uid_t __owner, __gid_t __group) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fchownat)(__AT_FDCWD, __file, __owner, __group, __AT_SYMLINK_NOFOLLOW);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lchown_defined
#define __local___localdep_lchown_defined
#define __localdep_lchown __LIBC_LOCAL_NAME(lchown)
#endif /* !__local___localdep_lchown_defined */
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchownat */
#undef __local_lchown_defined
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || !__CRT_HAVE_fchownat */
#endif /* !__local_lchown_defined */
