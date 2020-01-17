/* HASH CRC-32:0x67186403 */
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
#ifndef _IO_H
#define _IO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifndef _A_NORMAL
#define _A_NORMAL 0x00
#define _A_RDONLY 0x01
#define _A_HIDDEN 0x02
#define _A_SYSTEM 0x04
#define _A_SUBDIR 0x10
#define _A_ARCH   0x20
#endif /* !_A_NORMAL */

#ifdef __CC__

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef _FSIZE_T_DEFINED
#define _FSIZE_T_DEFINED
typedef __UINT32_TYPE__ _fsize_t;
#endif /* _FSIZE_T_DEFINED */

struct _finddata32_t;
struct __finddata64_t; /* I guess something else already using the more obvious choice... */
struct _finddata32i64_t;
struct _finddata64i32_t;

#ifndef __remove_defined
#define __remove_defined 1
#ifdef __std_remove_defined
__NAMESPACE_STD_USING(remove)
#elif defined(__CRT_HAVE_remove)
/* Remove a file or directory `FILENAME' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,remove,(char const *__filename),(__filename))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_removeat)
#include <local/stdio/remove.h>
/* Remove a file or directory `FILENAME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remove))(__filename); })
#else /* CUSTOM: remove */
#undef __remove_defined
#endif /* remove... */
#endif /* !__remove_defined */
#ifndef __rename_defined
#define __rename_defined 1
#ifdef __std_rename_defined
__NAMESPACE_STD_USING(rename)
#elif defined(__CRT_HAVE_rename)
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#elif defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_frenameat) || defined(__CRT_HAVE_renameat))
#include <local/stdio/rename.h>
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rename))(__oldname, __newname_or_path); })
#else /* CUSTOM: rename */
#undef __rename_defined
#endif /* rename... */
#endif /* !__rename_defined */
#ifndef __unlink_defined
#define __unlink_defined 1
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* CUSTOM: unlink */
#undef __unlink_defined
#endif /* unlink... */
#endif /* !__unlink_defined */
#ifndef __open_defined
#define __open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open");
#elif defined(__CRT_HAVE___open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/fcntl/open.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(open)
#else /* __cplusplus */
#define open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#endif /* !__cplusplus */
#else /* CUSTOM: open */
#undef __open_defined
#endif /* open... */
#endif /* !__open_defined */
#ifndef __creat_defined
#define __creat_defined 1
#if defined(__CRT_HAVE_creat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__creat)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#include <local/fcntl/creat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(creat, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); })
#else /* CUSTOM: creat */
#undef __creat_defined
#endif /* creat... */
#endif /* !__creat_defined */
#ifndef __access_defined
#define __access_defined 1
#ifdef __CRT_HAVE_access
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,access,(char const *__file, int __type),(__file,__type))
#elif defined(__CRT_HAVE__access)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,access,(char const *__file, int __type),_access,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/unistd/access.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL access)(char const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__file, __type); })
#else /* CUSTOM: access */
#undef __access_defined
#endif /* access... */
#endif /* !__access_defined */
#ifndef __chmod_defined
#define __chmod_defined 1
#ifdef __CRT_HAVE_chmod
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#else /* LIBC: chmod */
#undef __chmod_defined
#endif /* chmod... */
#endif /* !__chmod_defined */
#ifndef __close_defined
#define __close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a file handle */
__CDECLARE(,int,__NOTHROW_NCX,close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__close,(__fd))
#else /* LIBC: close */
#undef __close_defined
#endif /* close... */
#endif /* !__close_defined */
#ifndef __dup_defined
#define __dup_defined 1
#ifdef __CRT_HAVE_dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),(__fd))
#else /* LIBC: dup */
#undef __dup_defined
#endif /* dup... */
#endif /* !__dup_defined */
#ifndef __dup2_defined
#define __dup2_defined 1
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#else /* LIBC: dup2 */
#undef __dup2_defined
#endif /* dup2... */
#endif /* !__dup2_defined */
#ifndef __isatty_defined
#define __isatty_defined 1
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#else /* LIBC: isatty */
#undef __isatty_defined
#endif /* isatty... */
#endif /* !__isatty_defined */
#ifndef __lseek_defined
#define __lseek_defined 1
#if defined(__CRT_HAVE_lseek64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off64_t __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off64_t __offset, int __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__off32_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off32_t __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off32_t __offset, int __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek.h>
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek, __FORCELOCAL __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL lseek)(__fd_t __fd, __FS_TYPE(off) __offset, int __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(__fd, __offset, __whence); })
#else /* CUSTOM: lseek */
#undef __lseek_defined
#endif /* lseek... */
#endif /* !__lseek_defined */
#ifndef __mktemp_defined
#define __mktemp_defined 1
#ifdef __CRT_HAVE_mktemp
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mktemp,(char *__template_),__mktemp,(__template_))
#else /* LIBC: mktemp */
#undef __mktemp_defined
#endif /* mktemp... */
#endif /* !__mktemp_defined */
#ifndef __umask_defined
#define __umask_defined 1
#ifdef __CRT_HAVE_umask
__CDECLARE(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE__umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),_umask,(__mode))
#else /* LIBC: umask */
#undef __umask_defined
#endif /* umask... */
#endif /* !__umask_defined */
#ifndef __read_defined
#define __read_defined 1
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__read,(__fd,__buf,__bufsize))
#else /* LIBC: read */
#undef __read_defined
#endif /* read... */
#endif /* !__read_defined */
#ifndef __write_defined
#define __write_defined 1
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__write,(__fd,__buf,__bufsize))
#else /* LIBC: write */
#undef __write_defined
#endif /* write... */
#endif /* !__write_defined */
#ifdef __CRT_HAVE__access
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,_access,(char const *__filename, int __type),(__filename,__type))
#elif defined(__CRT_HAVE_access)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,_access,(char const *__filename, int __type),access,(__filename,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/unistd/access.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _access)(char const *__filename, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__filename, __type); }
#endif /* _access... */
#if defined(__CRT_HAVE_creat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#include <local/fcntl/creat.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL _creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); }
#endif /* _creat... */
#ifdef __CRT_HAVE__chmod
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE_chmod)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chmod,(char const *__filename, __mode_t __mode),chmod,(__filename,__mode))
#endif /* _chmod... */
#ifdef __CRT_HAVE__access_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_RPC,_access_s,(char const *__filename, int __type),(__filename,__type))
#endif /* _access_s... */
#ifdef __CRT_HAVE__chsize
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __LONG32_TYPE__ __size),(__fd,__size))
#elif defined(__CRT_HAVE_ftruncate)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __LONG32_TYPE__ __size),ftruncate,(__fd,__size))
#elif defined(__CRT_HAVE_chsize)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,_chsize,(__fd_t __fd, __LONG32_TYPE__ __size),chsize,(__fd,__size))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)
#include <local/unistd/ftruncate.h>
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _chsize)(__fd_t __fd, __LONG32_TYPE__ __size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, (__PIO_OFFSET)__size); }
#endif /* _chsize... */
#ifdef __CRT_HAVE__chsize_s
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE(,errno_t,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __INT64_TYPE__ __size),(__fd,__size))
#elif defined(__CRT_HAVE_ftruncate64)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,errno_t,__NOTHROW_NCX,_chsize_s,(__fd_t __fd, __INT64_TYPE__ __size),ftruncate64,(__fd,__size))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
#include <local/unistd/ftruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__FORCELOCAL errno_t __NOTHROW_NCX(__LIBCCALL _chsize_s)(__fd_t __fd, __INT64_TYPE__ __size) { return (errno_t)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))(__fd, (__PIO_OFFSET64)__size); }
#endif /* _chsize_s... */
#ifdef __CRT_HAVE__commit
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CDECLARE(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_fsync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),fsync,(__fd))
#elif defined(__CRT_HAVE_fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,_commit,(__fd_t __fd),fdatasync,(__fd))
#else /* LIBC: fsync */
#include <local/unistd/fsync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__FORCELOCAL int __NOTHROW_RPC(__LIBCCALL _commit)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsync))(__fd); }
#endif /* _commit... */
#ifdef __CRT_HAVE__lseek
__CDECLARE(,__LONG32_TYPE__,__NOTHROW_NCX,_lseek,(__fd_t __fd, __LONG32_TYPE__ __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek)
__CREDIRECT(,__LONG32_TYPE__,__NOTHROW_NCX,_lseek,(__fd_t __fd, __LONG32_TYPE__ __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/io/_lseek.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lseek, __FORCELOCAL __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL _lseek)(__fd_t __fd, __LONG32_TYPE__ __offset, int __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lseek))(__fd, __offset, __whence); })
#endif /* _lseek... */
#ifdef __CRT_HAVE__lseeki64
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__INT64_TYPE__,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __INT64_TYPE__ __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__INT64_TYPE__,__NOTHROW_NCX,_lseeki64,(__fd_t __fd, __INT64_TYPE__ __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__FORCELOCAL __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _lseeki64)(__fd_t __fd, __INT64_TYPE__ __offset, int __whence) { return (__INT64_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))(__fd, (__off64_t)__offset, __whence); }
#endif /* _lseeki64... */
#ifdef __CRT_HAVE__locking
__CDECLARE(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __length),(__fd,__lockmode,__length))
#elif defined(__CRT_HAVE_locking)
__CREDIRECT(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __length),locking,(__fd,__lockmode,__length))
#elif defined(__CRT_HAVE_lockf)
__CREDIRECT(,int,__NOTHROW_RPC,_locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __length),lockf,(__fd,__lockmode,__length))
#elif defined(__CRT_HAVE_lockf64)
#include <local/io/locking.h>
__FORCELOCAL int __NOTHROW_RPC(__LIBCCALL _locking)(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(locking))(__fd, __lockmode, __length); }
#endif /* _locking... */

#ifndef ___unlink_defined
#define ___unlink_defined 1
#ifdef __CRT_HAVE__unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_unlink,(char const *__filename),(__filename))
#elif defined(__CRT_HAVE_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_unlink,(char const *__filename),unlink,(__filename))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _unlink)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__filename); }
#else /* CUSTOM: unlink */
#undef ___unlink_defined
#endif /* _unlink... */
#endif /* !___unlink_defined */

#ifdef __CRT_HAVE__close
/* >> close(2)
 * Close a file handle */
__CDECLARE(,int,__NOTHROW_NCX,_close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,_close,(__fd_t __fd),close,(__fd))
#endif /* _close... */
#ifdef __CRT_HAVE__dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CDECLARE(,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,_dup,(__fd_t __fd),dup,(__fd))
#endif /* _dup... */
#ifdef __CRT_HAVE__dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE_dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#endif /* _dup2... */

#ifdef __CRT_HAVE__read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CDECLARE(,ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(,ssize_t,__NOTHROW_RPC,_read,(__fd_t __fd, void *__buf, size_t __bufsize),read,(__fd,__buf,__bufsize))
#endif /* _read... */
#ifdef __CRT_HAVE__write
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CDECLARE(,ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(,ssize_t,__NOTHROW_RPC,_write,(__fd_t __fd, void const *__buf, size_t __bufsize),write,(__fd,__buf,__bufsize))
#endif /* _write... */
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL _open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("_open");
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/fcntl/open.h>
#define _open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#endif /* _open... */
#ifdef __CRT_HAVE__setmode
__CDECLARE(,__oflag_t,__NOTHROW_NCX,_setmode,(__fd_t __fd, __oflag_t __mode),(__fd,__mode))
#elif defined(__CRT_HAVE_setmode)
__CREDIRECT(,__oflag_t,__NOTHROW_NCX,_setmode,(__fd_t __fd, __oflag_t __mode),setmode,(__fd,__mode))
#elif (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && (defined(__KOS__) || defined(__linux__))
#include <local/io/setmode.h>
__FORCELOCAL __oflag_t __NOTHROW_NCX(__LIBCCALL _setmode)(__fd_t __fd, __oflag_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setmode))(__fd, __mode); }
#endif /* _setmode... */
#ifdef __CRT_HAVE__umask
__CDECLARE(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE_umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,_umask,(__mode_t __mode),umask,(__mode))
#endif /* _umask... */
#ifdef __CRT_HAVE__isatty
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_isatty)
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_isatty,(__fd_t __fd),isatty,(__fd))
#endif /* _isatty... */


#ifdef __CRT_HAVE__findclose
__CDECLARE(,int,__NOTHROW_NCX,_findclose,(intptr_t __findfd),(__findfd))
#endif /* _findclose... */
#ifdef __CRT_HAVE__findfirst32
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst32,(char const *__restrict __filename, struct _finddata32_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst32,(char const *__restrict __filename, struct _finddata32_t *__restrict __finddata),_findfirst,(__filename,__finddata))
#endif /* _findfirst32... */
#ifdef __CRT_HAVE__findfirst32i64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst32i64,(char const *__restrict __filename, struct _finddata32i64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirsti64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst32i64,(char const *__restrict __filename, struct _finddata32i64_t *__restrict __finddata),_findfirsti64,(__filename,__finddata))
#endif /* _findfirst32i64... */
#ifdef __CRT_HAVE__findnext32
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext32,(intptr_t __findfd, struct _finddata32_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext32,(intptr_t __findfd, struct _finddata32_t *__restrict __finddata),_findnext,(__findfd,__finddata))
#endif /* _findnext32... */
#ifdef __CRT_HAVE__findnext32i64
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext32i64,(intptr_t __findfd, struct _finddata32i64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnexti64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext32i64,(intptr_t __findfd, struct _finddata32i64_t *__restrict __finddata),_findnexti64,(__findfd,__finddata))
#endif /* _findnext32i64... */
#ifdef __CRT_HAVE__findfirst64i32
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst64i32,(char const *__restrict __filename, struct _finddata64i32_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst64i32,(char const *__restrict __filename, struct _finddata64i32_t *__restrict __finddata),_findfirst64,(__filename,__finddata))
#endif /* _findfirst64i32... */
#ifdef __CRT_HAVE__findfirst64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst64,(char const *__restrict __filename, struct __finddata64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__findfirst64i32)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),intptr_t,__NOTHROW_RPC,_findfirst64,(char const *__restrict __filename, struct __finddata64_t *__restrict __finddata),_findfirst64i32,(__filename,__finddata))
#endif /* _findfirst64... */
#ifdef __CRT_HAVE__findnext64
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64,(intptr_t __findfd, struct __finddata64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext64i32)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64,(intptr_t __findfd, struct __finddata64_t *__restrict __finddata),_findnext64i32,(__findfd,__finddata))
#endif /* _findnext64... */
#ifdef __CRT_HAVE__findnext64i32
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64i32,(intptr_t __findfd, struct _finddata64i32_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__findnext64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64i32,(intptr_t __findfd, struct _finddata64i32_t *__restrict __finddata),_findnext64,(__findfd,__finddata))
#endif /* _findnext64i32... */

#ifdef __CRT_HAVE__sopen_s
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_RPC,_sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__sopen_s_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_RPC,_sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s_nolock,(__fd,__filename,__oflags,__sflags,__mode))
#endif /* _sopen_s... */
#ifdef __CRT_HAVE__sopen_s_nolock
__CDECLARE(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_RPC,_sopen_s_nolock,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__sopen_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),errno_t,__NOTHROW_RPC,_sopen_s_nolock,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s,(__fd,__filename,__oflags,__sflags,__mode))
#endif /* _sopen_s_nolock... */
#ifdef __CRT_HAVE__mktemp_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_mktemp_s,(char *__template_, size_t __size),(__template_,__size))
#endif /* _mktemp_s... */
#ifdef __CRT_HAVE__sopen
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL _sopen)(char const *__filename, __oflag_t __oflags, int __sflags, ...) __CASMNAME_SAME("_sopen");
#elif defined(__CRT_HAVE_sopen)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,_sopen,(char const *__filename, __oflag_t __oflags, int __sflags),sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64))) || (defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE__open)
#include <local/io/sopen.h>
#define _sopen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))
#endif /* _sopen... */
#ifdef __CRT_HAVE__pipe
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_pipe,(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode),(__pipedes,__pipesize,__textmode))
#elif defined(__CRT_HAVE__pipe) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE_pipe2)
#include <local/io/_pipe.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_pipe, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _pipe)(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_pipe))(__pipedes, __pipesize, __textmode); })
#endif /* _pipe... */
#ifdef __CRT_HAVE__eof
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_eof,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_eof)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_eof,(__fd_t __fd),eof,(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/io/eof.h>
__FORCELOCAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _eof)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eof))(__fd); }
#endif /* _eof... */
#ifdef __CRT_HAVE__filelength
__CDECLARE(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,_filelength,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_filelength)
__CREDIRECT(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,_filelength,(__fd_t __fd),filelength,(__fd))
#elif defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/io/filelength.h>
__FORCELOCAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL _filelength)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(filelength))(__fd); }
#endif /* _filelength... */
#ifdef __CRT_HAVE__tell
__CDECLARE(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,_tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_tell)
__CREDIRECT(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,_tell,(__fd_t __fd),tell,(__fd))
#elif defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/io/tell.h>
__FORCELOCAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL _tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); }
#endif /* _tell... */
#ifdef __CRT_HAVE__filelengthi64
__CDECLARE(__ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW_NCX,_filelengthi64,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/io/_filelengthi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_filelengthi64, __FORCELOCAL __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _filelengthi64)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_filelengthi64))(__fd); })
#endif /* _filelengthi64... */
#ifdef __CRT_HAVE__telli64
__CDECLARE(__ATTR_WUNUSED,__INT64_TYPE__,__NOTHROW_NCX,_telli64,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/io/_telli64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_telli64, __FORCELOCAL __ATTR_WUNUSED __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _telli64)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_telli64))(__fd); })
#endif /* _telli64... */
#ifdef __CRT_HAVE_umask_s
__CDECLARE(,errno_t,__NOTHROW_NCX,umask_s,(__mode_t __newmode, __mode_t *__oldmode),(__newmode,__oldmode))
#elif defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask)
#include <local/io/umask_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(umask_s, __FORCELOCAL errno_t __NOTHROW_NCX(__LIBCCALL umask_s)(__mode_t __newmode, __mode_t *__oldmode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umask_s))(__newmode, __oldmode); })
#endif /* umask_s... */
#ifdef __CRT_HAVE___lock_fhandle
__CDECLARE(,int,__NOTHROW_RPC,__lock_fhandle,(__fd_t __fd),(__fd))
#endif /* __lock_fhandle... */
#ifdef __CRT_HAVE__unlock_fhandle
__CDECLARE_VOID(,__NOTHROW_NCX,_unlock_fhandle,(__fd_t __fd),(__fd))
#endif /* _unlock_fhandle... */
#ifdef __CRT_HAVE__get_osfhandle
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,intptr_t,__NOTHROW_NCX,_get_osfhandle,(__fd_t __fd),(__fd))
#elif !defined(__CRT_DOS)
#include <local/io/_get_osfhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_osfhandle, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED intptr_t __NOTHROW_NCX(__LIBCCALL _get_osfhandle)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_osfhandle))(__fd); })
#endif /* _get_osfhandle... */
#ifdef __CRT_HAVE__open_osfhandle
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,_open_osfhandle,(intptr_t __osfd, __oflag_t __flags),(__osfd,__flags))
#elif !defined(__CRT_DOS)
#include <local/io/_open_osfhandle.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_open_osfhandle, __FORCELOCAL __ATTR_WUNUSED __fd_t __NOTHROW_NCX(__LIBCCALL _open_osfhandle)(intptr_t __osfd, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_open_osfhandle))(__osfd, __flags); })
#endif /* _open_osfhandle... */


/* Weird, new functions not apart of any standard. */

#ifdef __CRT_HAVE_setmode
__CDECLARE(,__oflag_t,__NOTHROW_NCX,setmode,(__fd_t __fd, __oflag_t __mode),(__fd,__mode))
#elif defined(__CRT_HAVE__setmode)
__CREDIRECT(,__oflag_t,__NOTHROW_NCX,setmode,(__fd_t __fd, __oflag_t __mode),_setmode,(__fd,__mode))
#elif (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && (defined(__KOS__) || defined(__linux__))
#include <local/io/setmode.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setmode, __FORCELOCAL __oflag_t __NOTHROW_NCX(__LIBCCALL setmode)(__fd_t __fd, __oflag_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setmode))(__fd, __mode); })
#endif /* setmode... */
#ifdef __CRT_HAVE_chsize
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __LONG32_TYPE__ __$size),(__fd,__$size))
#elif defined(__CRT_HAVE_ftruncate)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __LONG32_TYPE__ __$size),ftruncate,(__fd,__$size))
#elif defined(__CRT_HAVE__chsize)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,chsize,(__fd_t __fd, __LONG32_TYPE__ __$size),_chsize,(__fd,__$size))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)
#include <local/unistd/ftruncate.h>
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL chsize)(__fd_t __fd, __LONG32_TYPE__ __$size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, (__PIO_OFFSET)__$size); }
#endif /* chsize... */
#ifdef __CRT_HAVE_locking
__CDECLARE(,int,__NOTHROW_RPC,locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __numofbytes),(__fd,__lockmode,__numofbytes))
#elif defined(__CRT_HAVE__locking)
__CREDIRECT(,int,__NOTHROW_RPC,locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __numofbytes),_locking,(__fd,__lockmode,__numofbytes))
#elif defined(__CRT_HAVE_lockf)
__CREDIRECT(,int,__NOTHROW_RPC,locking,(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __numofbytes),lockf,(__fd,__lockmode,__numofbytes))
#elif defined(__CRT_HAVE_lockf64)
#include <local/io/locking.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(locking, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL locking)(__fd_t __fd, int __lockmode, __LONG32_TYPE__ __numofbytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(locking))(__fd, __lockmode, __numofbytes); })
#endif /* locking... */
#ifdef __CRT_HAVE_sopen
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL sopen)(char const *__filename, __oflag_t __oflags, int __sflags, ...) __CASMNAME_SAME("sopen");
#elif defined(__CRT_HAVE__sopen)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,sopen,(char const *__filename, __oflag_t __oflags, int __sflags),_sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64))) || (defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE__open)
#include <local/io/sopen.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(sopen)
#else /* __cplusplus */
#define sopen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))
#endif /* !__cplusplus */
#endif /* sopen... */
#ifdef __CRT_HAVE_filelength
__CDECLARE(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,filelength,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__filelength)
__CREDIRECT(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,filelength,(__fd_t __fd),_filelength,(__fd))
#elif defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/io/filelength.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(filelength, __FORCELOCAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL filelength)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(filelength))(__fd); })
#endif /* filelength... */
#ifdef __CRT_HAVE_tell
__CDECLARE(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__tell)
__CREDIRECT(__ATTR_WUNUSED,__LONG32_TYPE__,__NOTHROW_NCX,tell,(__fd_t __fd),_tell,(__fd))
#elif defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/io/tell.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tell, __FORCELOCAL __ATTR_WUNUSED __LONG32_TYPE__ __NOTHROW_NCX(__LIBCCALL tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); })
#endif /* tell... */
#ifdef __CRT_HAVE_eof
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,eof,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__eof)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,eof,(__fd_t __fd),_eof,(__fd))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/io/eof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(eof, __FORCELOCAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL eof)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eof))(__fd); })
#endif /* eof... */

/* Safely first! */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("attrib")
#pragma push_macro("time_create")
#pragma push_macro("time_access")
#pragma push_macro("time_write")
#pragma push_macro("size")
#pragma push_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef attrib
#undef time_create
#undef time_access
#undef time_write
#undef size
#undef name

#ifndef _FINDDATA_T_DEFINED
#define _FINDDATA_T_DEFINED 1
struct _finddata32_t {
	__UINT32_TYPE__      attrib;
	__time32_t           time_create;
	__time32_t           time_access;
	__time32_t           time_write;
	_fsize_t             size;
	char                 name[260];
};
struct _finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__time32_t           time_create;
	__time32_t           time_access;
	__time32_t           time_write;
	/* Microsoft:
	 * A: "I mean: we could use an unsigned type for this, seeing as how _fsize_t is also unsigned."
	 * B: "Nah! - Lets rather p1$$ off anyone that notices. - That'll be way more fun." */
	__INT64_TYPE__       size;
	char                 name[260];
};
struct _finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__time64_t           time_create;
	__time64_t           time_access;
	__time64_t           time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char                 name[260];
};
struct __finddata64_t {
	__UINT32_TYPE__      attrib;
	__time64_t           time_create;
	__time64_t           time_access;
	__time64_t           time_write;
	__INT64_TYPE__       size;
	char                 name[260];
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("name")
#pragma pop_macro("size")
#pragma pop_macro("time_write")
#pragma pop_macro("time_access")
#pragma pop_macro("time_create")
#pragma pop_macro("attrib")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_TIME_BITS64
#define _finddata_t                       _finddata64i32_t
#define _finddatai64_t                    __finddata64_t
#define _findfirst(filename, finddata)    _findfirst64i32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext64i32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _finddata_t                       _finddata32_t
#define _finddatai64_t                    _finddata32i64_t
#define _findfirst(filename, finddata)    _findfirst32(filename, finddata)
#define _findnext(findfd, finddata)       _findnext32(findfd, finddata)
#define _findfirsti64(filename, finddata) _findfirst32i64(filename, finddata)
#define _findnexti64(findfd, finddata)    _findnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_FINDDATA_T_DEFINED */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_IO_H */
#endif /* __USE_UTF */

#endif /* !_IO_H */
