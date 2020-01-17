/* HASH CRC-32:0x16e302d5 */
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
#ifndef __local_get_current_dir_name_defined
#if defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#define __local_get_current_dir_name_defined 1
/* Dependency: "getcwd" */
#ifndef ____localdep_getcwd_defined
#define ____localdep_getcwd_defined 1
#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),getcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),_getcwd,(__buf,__bufsize))
#else /* LIBC: getcwd */
#undef ____localdep_getcwd_defined
#endif /* getcwd... */
#endif /* !____localdep_getcwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(get_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(get_current_dir_name))(void) {
#line 1132 "kos/src/libc/magic/unistd.c"
	return __localdep_getcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_getcwd || __CRT_HAVE__getcwd */
#endif /* !__local_get_current_dir_name_defined */
