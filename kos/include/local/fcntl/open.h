/* HASH CRC-32:0x389451f3 */
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
#ifndef __local_open_defined
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#define __local_open_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "open64" from "fcntl" */
#ifndef ____localdep_open64_defined
#define ____localdep_open64_defined 1
#ifdef __CRT_HAVE_open64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#include <local/fcntl/open64.h>
#define __localdep_open64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))
#else /* CUSTOM: open64 */
#undef ____localdep_open64_defined
#endif /* open64... */
#endif /* !____localdep_open64_defined */

/* Dependency: "openat" from "fcntl" */
#ifndef ____localdep_openat_defined
#define ____localdep_openat_defined 1
#if defined(__CRT_HAVE_openat64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat64)
#include <local/fcntl/openat.h>
#define __localdep_openat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat))
#else /* CUSTOM: openat */
#undef ____localdep_openat_defined
#endif /* openat... */
#endif /* !____localdep_openat_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(open) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(open))(char const *__filename,
                                                   __oflag_t __oflags,
                                                   ...) {
#line 197 "kos/src/libc/magic/fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64)
	__result = __localdep_open64(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 */
	__result = __localdep_openat(__CRT_AT_FDCWD, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || (__CRT_AT_FDCWD && (__CRT_HAVE_openat || __CRT_HAVE_openat64)) */
#endif /* !__local_open_defined */
