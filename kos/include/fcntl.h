/* HASH CRC-32:0xf9834654 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/fcntl.h) */
/* (#) Portability: DJGPP         (/include/fcntl.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fcntl.h) */
/* (#) Portability: GNU C Library (/io/fcntl.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fcntl.h) */
/* (#) Portability: MSVC          (/include/fcntl.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/fcntl.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/fcntl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/fcntl.h) */
/* (#) Portability: Windows Kits  (/ucrt/fcntl.h) */
/* (#) Portability: avr-libc      (/include/fcntl.h) */
/* (#) Portability: diet libc     (/include/fcntl.h) */
/* (#) Portability: libc4/5       (/include/fcntl.h) */
/* (#) Portability: libc6         (/include/fcntl.h) */
/* (#) Portability: mintlib       (/include/fcntl.h) */
/* (#) Portability: musl libc     (/include/fcntl.h) */
/* (#) Portability: uClibc        (/include/fcntl.h) */
#ifndef _FCNTL_H
#define _FCNTL_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/flock.h>
#include <bits/types.h>

#ifdef __USE_GNU
#include <asm/os/limits.h> /* __IOV_MAX */
#include <bits/os/f_owner_ex.h>
#include <bits/os/file_handle.h>
#include <bits/os/iovec.h>

#ifndef UIO_MAXIOV
#if !defined(__IOV_MAX) || (__IOV_MAX == -1)
#define UIO_MAXIOV 16
#else /* !__IOV_MAX || __IOV_MAX == -1 */
#define UIO_MAXIOV __IOV_MAX
#endif /* __IOV_MAX && __IOV_MAX != -1 */
#endif /* !UIO_MAXIOV */
#endif /* __USE_GNU */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <asm/os/stat.h>
#include <asm/os/stdio.h>
#include <bits/os/stat.h>
#include <bits/os/timespec.h>

#ifdef __USE_ATFILE
#if !defined(UTIME_NOW) && defined(__UTIME_NOW)
#define UTIME_NOW  __UTIME_NOW  /* for utimensat(): Set `times[0|1].tv_nsec' to this to use the current time instead. */
#endif /* !UTIME_NOW && __UTIME_NOW */
#if !defined(UTIME_OMIT) && defined(__UTIME_OMIT)
#define UTIME_OMIT __UTIME_OMIT /* for utimensat(): Set `times[0|1].tv_nsec' to this to not modify that timestamp. */
#endif /* !UTIME_OMIT && __UTIME_OMIT */
#endif /* __USE_ATFILE */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#if defined(__USE_NETBSD) && defined(__USE_XOPEN)
#include <sys/stat.h>
#endif /* __USE_NETBSD && __USE_XOPEN */

#ifdef __USE_NEWLIB
#include <features.h>
#include <sys/cdefs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <_ansi.h>
#ifdef __USE_GNU
#include <sys/time.h> /* For `futimesat()' */
#endif /* __USE_GNU */
#ifdef __USE_BSD
#include <sys/file.h> /* For `flock()' */
#endif /* __USE_BSD */
#endif /* __USE_NEWLIB */

/* susv4-2018: Inclusion  of  the  <fcntl.h>  header  may  also make
 *             visible all symbols from <sys/stat.h> and <unistd.h>. */
#ifdef __USE_POSIX_BLOAT
#include <sys/stat.h>
#include <unistd.h>
#endif /* __USE_POSIX_BLOAT */

__SYSDECL_BEGIN

/* Mask for `O_RDONLY | O_WRONLY | O_RDWR' */
#if !defined(O_ACCMODE) && defined(__O_ACCMODE)
#define O_ACCMODE __O_ACCMODE
#endif /* !O_ACCMODE && __O_ACCMODE */

/* Access mode: read-only */
#if !defined(O_RDONLY) && defined(__O_RDONLY)
#define O_RDONLY __O_RDONLY
#endif /* !O_RDONLY && __O_RDONLY */

/* Access mode: write-only */
#if !defined(O_WRONLY) && defined(__O_WRONLY)
#define O_WRONLY __O_WRONLY
#endif /* !O_WRONLY && __O_WRONLY */

/* Access mode: read/write */
#if !defined(O_RDWR) && defined(__O_RDWR)
#define O_RDWR __O_RDWR
#endif /* !O_RDWR && __O_RDWR */

/* Truncate the file's size to 0 */
#if !defined(O_TRUNC) && defined(__O_TRUNC)
#define O_TRUNC __O_TRUNC
#endif /* !O_TRUNC && __O_TRUNC */

/* If missing, create a new file */
#if !defined(O_CREAT) && defined(__O_CREAT)
#define O_CREAT __O_CREAT
#endif /* !O_CREAT && __O_CREAT */

/* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS' (-EEXISTS)
 * exception if the file already exists. */
#if !defined(O_EXCL) && defined(__O_EXCL)
#define O_EXCL __O_EXCL
#endif /* !O_EXCL && __O_EXCL */

/* If the calling process does not have a controlling terminal assigned,
 * do not attempt to assign the newly opened file as terminal, even when
 * `isatty(open(...))' would be true. */
#if !defined(O_NOCTTY) && defined(__O_NOCTTY)
#define O_NOCTTY __O_NOCTTY
#endif /* !O_NOCTTY && __O_NOCTTY */

/* Always append data to the end of the file */
#if !defined(O_APPEND) && defined(__O_APPEND)
#define O_APPEND __O_APPEND
#endif /* !O_APPEND && __O_APPEND */

/* Do not block when trying to read data that hasn't been written, yet. */
#if !defined(O_NONBLOCK) && defined(__O_NONBLOCK)
#define O_NONBLOCK __O_NONBLOCK
#endif /* !O_NONBLOCK && __O_NONBLOCK */

#if !defined(O_SYNC) && defined(__O_SYNC)
#define O_SYNC __O_SYNC /* ??? */
#endif /* !O_SYNC && __O_SYNC */

#if !defined(O_ASYNC) && defined(__O_ASYNC)
#define O_ASYNC __O_ASYNC /* ??? */
#endif /* !O_ASYNC && __O_ASYNC */

#ifdef __USE_KOS
/* Open anything directly (as best as possible). (file, directory or symlink)
 * KOS: Open a file, directory or symlink directly.
 * DOS: Open a file or directory directly.
 * GLC: Open a file or directory directly. */
#ifndef O_ANYTHING
#ifdef __O_ANYTHING
#define O_ANYTHING __O_ANYTHING
#else /* __O_ANYTHING */
#define O_ANYTHING 0
#endif /* !__O_ANYTHING */
#endif /* !O_ANYTHING */
#endif /* __USE_KOS */

#if !defined(O_FSYNC) && defined(__O_SYNC)
#define O_FSYNC __O_SYNC /* ??? */
#endif /* !O_FSYNC && __O_SYNC */

#ifdef __USE_LARGEFILE64
#if !defined(O_LARGEFILE) && defined(__O_LARGEFILE)
#define O_LARGEFILE __O_LARGEFILE /* Ignored... */
#endif /* !O_LARGEFILE && __O_LARGEFILE */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K8
/* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' (-ENOTDIR) exception when the
 * final path component of  an open() system  call turns out  to be something  other than a  directory. */
#if !defined(O_DIRECTORY) && defined(__O_DIRECTORY)
#define O_DIRECTORY __O_DIRECTORY
#endif /* !O_DIRECTORY && __O_DIRECTORY */

/* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'  exception
 * when the final path component of an open() system call turns out to be a symbolic link. */
#if !defined(O_NOFOLLOW) && defined(__O_NOFOLLOW)
#define O_NOFOLLOW __O_NOFOLLOW
#endif /* !O_NOFOLLOW && __O_NOFOLLOW */

/* Close the file during exec() */
#if !defined(O_CLOEXEC) && defined(__O_CLOEXEC)
#define O_CLOEXEC __O_CLOEXEC
#endif /* !O_CLOEXEC && __O_CLOEXEC */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
/* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#if !defined(O_CLOFORK) && defined(__O_CLOFORK)
#define O_CLOFORK __O_CLOFORK
#endif /* !O_CLOFORK && __O_CLOFORK */

/* Interpret  '\\'  as  '/',  and   ignore  casing  during  path   resolution.
 * Additionally,   recognize  DOS  mounting   points,  and  interpret  leading
 * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#if !defined(O_DOSPATH) && defined(__O_DOSPATH)
#define O_DOSPATH __O_DOSPATH
#endif /* !O_DOSPATH && __O_DOSPATH */
#endif /* __USE_KOS */

#if defined(__USE_GNU) || defined(__USE_BSD)
/* Bypass unified I/O buffers. Directly read-from / write-to hardware (s.a. `FILE_IOC_BLKSHIFT'). */
#if !defined(O_DIRECT) && defined(__O_DIRECT)
#define O_DIRECT __O_DIRECT
#endif /* !O_DIRECT && __O_DIRECT */
#endif /* __USE_GNU || __USE_BSD */

#ifdef __USE_NETBSD
#if !defined(O_ALT_IO) && defined(__O_ALT_IO)
#define O_ALT_IO __O_ALT_IO
#endif /* !O_ALT_IO && __O_ALT_IO */
#endif /* __USE_NETBSD */

#ifdef __USE_GNU
/* Don't update last-accessed time stamps. */
#if !defined(O_NOATIME) && defined(__O_NOATIME)
#define O_NOATIME __O_NOATIME
#endif /* !O_NOATIME && __O_NOATIME */

/* Open a path for *at system calls. */
#if !defined(O_PATH) && defined(__O_PATH)
#define O_PATH __O_PATH
#endif /* !O_PATH && __O_PATH */

#if !defined(O_TMPFILE) && defined(__O_TMPFILE)
#define O_TMPFILE __O_TMPFILE
#endif /* !O_TMPFILE && __O_TMPFILE */
#endif /* __USE_GNU */

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98) || defined(__USE_CYGWIN)
#if !defined(O_DSYNC) && defined(__O_DSYNC)
#define O_DSYNC __O_DSYNC /* ??? */
#endif /* !O_DSYNC && __O_DSYNC */
#if !defined(O_RSYNC) && defined(__O_SYNC)
#define O_RSYNC __O_SYNC /* ??? */
#endif /* !O_RSYNC && __O_SYNC */
#endif /* __USE_POSIX199309 || __USE_UNIX98 || __USE_CYGWIN */

#if defined(__USE_CYGWIN) || defined(__USE_DOS)
#if !defined(O_BINARY) && defined(__O_BINARY)
#define O_BINARY __O_BINARY /* ... */
#endif /* !O_BINARY && __O_BINARY */
#if !defined(O_TEXT) && defined(__O_TEXT)
#define O_TEXT __O_TEXT /* ... */
#endif /* !O_TEXT && __O_TEXT */
#endif /* __USE_CYGWIN || __USE_DOS */

#if defined(__USE_XOPEN2K8) || defined(__USE_NEWLIB) || defined(__USE_NETBSD)
#if !defined(O_SEARCH) && defined(__O_SEARCH)
#define O_SEARCH __O_SEARCH /* ... */
#endif /* !O_SEARCH && __O_SEARCH */
#if !defined(O_EXEC) && defined(__O_EXEC)
#define O_EXEC __O_EXEC /* ... */
#endif /* !O_EXEC && __O_EXEC */
#endif /* __USE_XOPEN2K8 || __USE_NEWLIB || __USE_NETBSD */

#ifdef __USE_NETBSD
#if !defined(O_NOSIGPIPE) && defined(__O_NOSIGPIPE)
#define O_NOSIGPIPE __O_NOSIGPIPE /* ... */
#endif /* !O_NOSIGPIPE && __O_NOSIGPIPE */
#if !defined(O_REGULAR) && defined(__O_REGULAR)
#define O_REGULAR __O_REGULAR /* ... */
#endif /* !O_REGULAR && __O_REGULAR */
#if !defined(O_SHLOCK) && defined(__O_SHLOCK)
#define O_SHLOCK __O_SHLOCK /* ... */
#endif /* !O_SHLOCK && __O_SHLOCK */
#if !defined(O_EXLOCK) && defined(__O_EXLOCK)
#define O_EXLOCK __O_EXLOCK /* ... */
#endif /* !O_EXLOCK && __O_EXLOCK */
#endif /* __USE_NETBSD */






/* Aliases */

/* Do not block when trying to read data that hasn't been written, yet. */
#if !defined(O_NDELAY) && defined(__O_NONBLOCK)
#define O_NDELAY __O_NONBLOCK
#endif /* !O_NDELAY && __O_NONBLOCK */

#if defined(__USE_MISC) || defined(__USE_NETBSD)
/* Always append data to the end of the file */
#if !defined(FAPPEND) && defined(__O_APPEND)
#define FAPPEND __O_APPEND
#endif /* !FAPPEND && __O_APPEND */

#if !defined(FFSYNC) && defined(__O_SYNC)
#define FFSYNC __O_SYNC /* ??? */
#endif /* !FFSYNC && __O_SYNC */

#if !defined(FASYNC) && defined(__O_ASYNC)
#define FASYNC __O_ASYNC /* ??? */
#endif /* !FASYNC && __O_ASYNC */

#if !defined(FNONBLOCK) && defined(__O_NONBLOCK)
#define FNONBLOCK __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !FNONBLOCK && __O_NONBLOCK */

#if !defined(FNDELAY) && defined(__O_NONBLOCK)
#define FNDELAY __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !FNDELAY && __O_NONBLOCK */
#endif /* __USE_MISC || __USE_NETBSD */





#ifndef __USE_FILE_OFFSET64
/* [struct flock *arg] Get record locking info. */
#if !defined(F_GETLK) && defined(__F_GETLK)
#define F_GETLK __F_GETLK
#endif /* !F_GETLK && __F_GETLK */

/* [struct flock const *arg] Set record locking info (non-blocking). */
#if !defined(F_SETLK) && defined(__F_SETLK)
#define F_SETLK __F_SETLK
#endif /* !F_SETLK && __F_SETLK */

/* [struct flock const *arg] Set record locking info (blocking). */
#if !defined(F_SETLKW) && defined(__F_SETLKW)
#define F_SETLKW __F_SETLKW
#endif /* !F_SETLKW && __F_SETLKW */
#else /* __USE_FILE_OFFSET64 */
/* [struct flock *arg] Get record locking info. */
#if !defined(F_GETLK) && defined(__F_GETLK64)
#define F_GETLK __F_GETLK64
#endif /* !F_GETLK && __F_GETLK64 */

/* [struct flock const *arg] Set record locking info (non-blocking). */
#if !defined(F_SETLK) && defined(__F_SETLK64)
#define F_SETLK __F_SETLK64
#endif /* !F_SETLK && __F_SETLK64 */

/* [struct flock const *arg] Set record locking info (blocking). */
#if !defined(F_SETLKW) && defined(__F_SETLKW64)
#define F_SETLKW __F_SETLKW64
#endif /* !F_SETLKW && __F_SETLKW64 */
#endif /* !__USE_FILE_OFFSET64 */


#ifdef __USE_LARGEFILE64
/* [struct flock64 *arg] Get record locking info. */
#if !defined(F_GETLK64) && defined(__F_GETLK64)
#define F_GETLK64   __F_GETLK64
#endif /* !F_GETLK64 && __F_GETLK64 */

/* [struct flock64 const *arg] Set record locking info (non-blocking). */
#if !defined(F_SETLK64) && defined(__F_SETLK64)
#define F_SETLK64   __F_SETLK64
#endif /* !F_SETLK64 && __F_SETLK64 */

/* [struct flock64 const *arg] Set record locking info (blocking). */
#if !defined(F_SETLKW64) && defined(__F_SETLKW64)
#define F_SETLKW64  __F_SETLKW64
#endif /* !F_SETLKW64 && __F_SETLKW64 */
#endif /* !__USE_LARGEFILE64 */

/* [fd_t minfd] Same as `dup(2)', but returned FD is guarantied `>= minfd' */
#if !defined(F_DUPFD) && defined(__F_DUPFD)
#define F_DUPFD __F_DUPFD
#endif /* !F_DUPFD && __F_DUPFD */

/* [void arg] Get file descriptor flags.
 * @return: * : Set of `FD_CLOEXEC | FD_CLOFORK' */
#if !defined(F_GETFD) && defined(__F_GETFD)
#define F_GETFD __F_GETFD
#endif /* !F_GETFD && __F_GETFD */

/* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#if !defined(F_SETFD) && defined(__F_SETFD)
#define F_SETFD __F_SETFD
#endif /* !F_SETFD && __F_SETFD */

/* [void arg] Get file status flags.
 * @return: * : Set of `O_APPEND | O_NONBLOCK | O_DSYNC | O_ASYNC | O_DIRECT' */
#if !defined(F_GETFL) && defined(__F_GETFL)
#define F_GETFL __F_GETFL
#endif /* !F_GETFL && __F_GETFL */

/* [oflag_t arg] Set file status flags. */
#if !defined(F_SETFL) && defined(__F_SETFL)
#define F_SETFL __F_SETFL
#endif /* !F_SETFL && __F_SETFL */


#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_BSD)
/* [void arg] Get owner (process receiving SIGIO).
 * @return: * : The PID of the process (warning: the PID may not
 *              fit into an int and -EOVERFLOW may be  returned) */
#if !defined(F_GETOWN) && defined(__F_GETOWN)
#define F_GETOWN __F_GETOWN
#endif /* !F_GETOWN && __F_GETOWN */

/* [pid_t arg] Set owner (process receiving SIGIO). */
#if !defined(F_SETOWN) && defined(__F_SETOWN)
#define F_SETOWN __F_SETOWN
#endif /* !F_SETOWN && __F_SETOWN */
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_BSD */


#ifdef __USE_GNU
/* [struct flock *arg] */
#if !defined(F_OFD_GETLK) && defined(__F_OFD_GETLK)
#define F_OFD_GETLK  __F_OFD_GETLK
#endif /* !F_OFD_GETLK && __F_OFD_GETLK */

/* [struct flock const *arg] */
#if !defined(F_OFD_SETLK) && defined(__F_OFD_SETLK)
#define F_OFD_SETLK  __F_OFD_SETLK
#endif /* !F_OFD_SETLK && __F_OFD_SETLK */

/* [struct flock const *arg] */
#if !defined(F_OFD_SETLKW) && defined(__F_OFD_SETLKW)
#define F_OFD_SETLKW __F_OFD_SETLKW
#endif /* !F_OFD_SETLKW && __F_OFD_SETLKW */

/* [int signo] Set number of signal to be sent. */
#if !defined(F_SETSIG) && defined(__F_SETSIG)
#define F_SETSIG __F_SETSIG
#endif /* !F_SETSIG && __F_SETSIG */

/* [void arg] Get number of signal to be sent.
 * @return: * : One of `SIG*' */
#if !defined(F_GETSIG) && defined(__F_GETSIG)
#define F_GETSIG __F_GETSIG
#endif /* !F_GETSIG && __F_GETSIG */

/* [struct f_owner_ex const *arg] Set owner (thread receiving SIGIO). */
#if !defined(F_SETOWN_EX) && defined(__F_SETOWN_EX)
#define F_SETOWN_EX __F_SETOWN_EX
#endif /* !F_SETOWN_EX && __F_SETOWN_EX */

/* [struct f_owner_ex *arg] Get owner (thread receiving SIGIO). */
#if !defined(F_GETOWN_EX) && defined(__F_GETOWN_EX)
#define F_GETOWN_EX __F_GETOWN_EX
#endif /* !F_GETOWN_EX && __F_GETOWN_EX */

/* [int arg = <One of `F_RDLCK', `F_WRLCK', `F_UNLCK'>] Set a lease. */
#if !defined(F_SETLEASE) && defined(__F_SETLEASE)
#define F_SETLEASE __F_SETLEASE
#endif /* !F_SETLEASE && __F_SETLEASE */

/* [void arg] Enquire what lease is active.
 * @return: * : One of `F_RDLCK', `F_WRLCK', `F_UNLCK' */
#if !defined(F_GETLEASE) && defined(__F_GETLEASE)
#define F_GETLEASE __F_GETLEASE
#endif /* !F_GETLEASE && __F_GETLEASE */

/* [int arg = <Set of `DN_*'>] Request notifications on a directory. */
#if !defined(F_NOTIFY) && defined(__F_NOTIFY)
#define F_NOTIFY __F_NOTIFY
#endif /* !F_NOTIFY && __F_NOTIFY */

/* [unsigned int arg] Set pipe buffer size (in bytes). */
#if !defined(F_SETPIPE_SZ) && defined(__F_SETPIPE_SZ)
#define F_SETPIPE_SZ __F_SETPIPE_SZ
#endif /* !F_SETPIPE_SZ && __F_SETPIPE_SZ */

/* [void arg] Get pipe buffer size (in bytes).
 * @return: * : The buffer size (in bytes) */
#if !defined(F_GETPIPE_SZ) && defined(__F_GETPIPE_SZ)
#define F_GETPIPE_SZ __F_GETPIPE_SZ
#endif /* !F_GETPIPE_SZ && __F_GETPIPE_SZ */

/* [unsigned int seals] Set file seals (`seals' is a set of `F_SEAL_*') */
#if !defined(F_ADD_SEALS) && defined(__F_ADD_SEALS)
#define F_ADD_SEALS __F_ADD_SEALS
#endif /* !F_ADD_SEALS && __F_ADD_SEALS */

/* [void arg] Get active file seals.
 * @return: * : Active seals (set of `F_SEAL_*') */
#if !defined(F_GET_SEALS) && defined(__F_GET_SEALS)
#define F_GET_SEALS __F_GET_SEALS
#endif /* !F_GET_SEALS && __F_GET_SEALS */

/* [uint64_t *arg] ??? */
#if !defined(F_GET_RW_HINT) && defined(__F_GET_RW_HINT)
#define F_GET_RW_HINT __F_GET_RW_HINT
#endif /* !F_GET_RW_HINT && __F_GET_RW_HINT */

/* [uint64_t const *arg] ??? */
#if !defined(F_SET_RW_HINT) && defined(__F_SET_RW_HINT)
#define F_SET_RW_HINT __F_SET_RW_HINT
#endif /* !F_SET_RW_HINT && __F_SET_RW_HINT */

/* [uint64_t *arg] ??? */
#if !defined(F_GET_FILE_RW_HINT) && defined(__F_GET_FILE_RW_HINT)
#define F_GET_FILE_RW_HINT __F_GET_FILE_RW_HINT
#endif /* !F_GET_FILE_RW_HINT && __F_GET_FILE_RW_HINT */

/* [uint64_t const *arg] ??? */
#if !defined(F_SET_FILE_RW_HINT) && defined(__F_SET_FILE_RW_HINT)
#define F_SET_FILE_RW_HINT __F_SET_FILE_RW_HINT
#endif /* !F_SET_FILE_RW_HINT && __F_SET_FILE_RW_HINT */

#endif /* __USE_GNU */

#if defined(__USE_XOPEN2K8) || defined(__USE_NETBSD)
/* [fd_t minfd] Same as `F_DUPFD', but also set `FD_CLOEXEC' bit. */
#if !defined(F_DUPFD_CLOEXEC) && defined(__F_DUPFD_CLOEXEC)
#define F_DUPFD_CLOEXEC __F_DUPFD_CLOEXEC
#endif /* !F_DUPFD_CLOEXEC && __F_DUPFD_CLOEXEC */
#endif /* __USE_XOPEN2K8 || __USE_NETBSD */

#ifdef __USE_KOS
/* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#if !defined(F_SETFD) && defined(__F_SETFD)
#define F_SETFD __F_SETFD
#endif /* !F_SETFD && __F_SETFD */

/* [int flags] Same as 'F_SETFL', but return the old set of flags instead of `-EOK' upon success. */
#if !defined(F_SETFL_XCH) && defined(__F_SETFL_XCH)
#define F_SETFL_XCH __F_SETFL_XCH
#endif /* !F_SETFL_XCH && __F_SETFL_XCH */

/* [void arg] Return the next open handle id >= the given fd, or `-EBADF' if no such FD exists.
 * s.a. https://lkml.org/lkml/2012/4/1/71 */
#if !defined(F_NEXT) && defined(__F_NEXT)
#define F_NEXT __F_NEXT
#endif /* !F_NEXT && __F_NEXT */
#endif /* __USE_KOS */

#if defined(__USE_KOS) || defined(__USE_NETBSD)
/* [void arg] close  all  handles  >=  to  the  one  given
 * s.a. https://www.unix.com/man-page/FreeBSD/2/closefrom/ */
#if !defined(F_CLOSEM) && defined(__F_CLOSEM)
#define F_CLOSEM __F_CLOSEM
#endif /* !F_CLOSEM && __F_CLOSEM */

/* [void arg] return the max open handle id (the given fd is ignored) */
#if !defined(F_MAXFD) && defined(__F_MAXFD)
#define F_MAXFD __F_MAXFD
#endif /* !F_MAXFD && __F_MAXFD */
#endif /* __USE_KOS || __USE_NETBSD */

#ifdef __USE_NETBSD
#if !defined(F_GETNOSIGPIPE) && defined(__F_GETNOSIGPIPE)
#define F_GETNOSIGPIPE __F_GETNOSIGPIPE /* ... */
#endif /* !F_GETNOSIGPIPE && __F_GETNOSIGPIPE */
#if !defined(F_SETNOSIGPIPE) && defined(__F_SETNOSIGPIPE)
#define F_SETNOSIGPIPE __F_SETNOSIGPIPE /* ... */
#endif /* !F_SETNOSIGPIPE && __F_SETNOSIGPIPE */
#if !defined(F_GETPATH) && defined(__F_GETPATH)
#define F_GETPATH      __F_GETPATH      /* ... */
#endif /* !F_GETPATH && __F_GETPATH */
#endif /* __USE_KOS || __USE_NETBSD */


#if defined(__USE_KOS) || defined(__USE_BSD)
/* [fd_t arg] Same as `dup2()' (the target FD is given as `(fd_t)arg') */
#if !defined(F_DUP2FD) && defined(__F_DUP2FD)
#define F_DUP2FD __F_DUP2FD
#endif /* !F_DUP2FD && __F_DUP2FD */

/* [fd_t arg] Same as `F_DUP2FD', but set `FD_CLOEXEC'. */
#if !defined(F_DUP2FD_CLOEXEC) && defined(__F_DUP2FD_CLOEXEC)
#define F_DUP2FD_CLOEXEC __F_DUP2FD_CLOEXEC
#endif /* !F_DUP2FD_CLOEXEC && __F_DUP2FD_CLOEXEC */
#endif /* __USE_KOS || __USE_BSD */

#if defined(__USE_NEWLIB) && defined(__USE_MISC)
#if !defined(F_RGETLK) && defined(__F_RGETLK)
#define F_RGETLK  __F_RGETLK
#endif /* !F_RGETLK && __F_RGETLK */
#if !defined(F_RSETLK) && defined(__F_RSETLK)
#define F_RSETLK  __F_RSETLK
#endif /* !F_RSETLK && __F_RSETLK */
#if !defined(F_CNVT) && defined(__F_CNVT)
#define F_CNVT    __F_CNVT
#endif /* !F_CNVT && __F_CNVT */
#if !defined(F_RSETLKW) && defined(__F_RSETLKW)
#define F_RSETLKW __F_RSETLKW
#endif /* !F_RSETLKW && __F_RSETLKW */
#endif /* __USE_NEWLIB && __USE_MISC */



/* FLAG: Close the descriptor on `exec()'. */
#if !defined(FD_CLOEXEC) && defined(__FD_CLOEXEC)
#define FD_CLOEXEC __FD_CLOEXEC
#endif /* !FD_CLOEXEC && __FD_CLOEXEC */

#ifdef __USE_KOS
/* FLAG: Close the descriptor during unsharing after `fork()'. */
#if !defined(FD_CLOFORK) && defined(__FD_CLOFORK)
#define FD_CLOFORK __FD_CLOFORK
#endif /* !FD_CLOFORK && __FD_CLOFORK */
#endif /* __USE_KOS */

/* Read lock. */
#if !defined(F_RDLCK) && defined(__F_RDLCK)
#define F_RDLCK __F_RDLCK
#endif /* !F_RDLCK && __F_RDLCK */

/* Write lock. */
#if !defined(F_WRLCK) && defined(__F_WRLCK)
#define F_WRLCK __F_WRLCK
#endif /* !F_WRLCK && __F_WRLCK */

/* Remove lock. */
#if !defined(F_UNLCK) && defined(__F_UNLCK)
#define F_UNLCK __F_UNLCK
#endif /* !F_UNLCK && __F_UNLCK */

/* TODO: DOC */
#if !defined(F_EXLCK) && defined(__F_EXLCK)
#define F_EXLCK __F_EXLCK
#endif /* !F_EXLCK && __F_EXLCK */

/* TODO: DOC */
#if !defined(F_SHLCK) && defined(__F_SHLCK)
#define F_SHLCK __F_SHLCK
#endif /* !F_SHLCK && __F_SHLCK */

#if defined(__USE_NEWLIB) && defined(__USE_MISC)
#if !defined(F_UNLKSYS) && defined(__F_UNLKSYS)
#define F_UNLKSYS __F_UNLKSYS
#endif /* !F_UNLKSYS && __F_UNLKSYS */
#endif /* __USE_NEWLIB && __USE_MISC */




#if defined(__USE_MISC) || defined(__USE_BSD)
/* Shared lock. */
#if !defined(LOCK_SH) && defined(__LOCK_SH)
#define LOCK_SH __LOCK_SH
#endif /* !LOCK_SH && __LOCK_SH */

/* Exclusive lock. */
#if !defined(LOCK_EX) && defined(__LOCK_EX)
#define LOCK_EX __LOCK_EX
#endif /* !LOCK_EX && __LOCK_EX */

/* Or'd with one of the above to prevent blocking. */
#if !defined(LOCK_NB) && defined(__LOCK_NB)
#define LOCK_NB __LOCK_NB
#endif /* !LOCK_NB && __LOCK_NB */

/* Remove lock. */
#if !defined(LOCK_UN) && defined(__LOCK_UN)
#define LOCK_UN __LOCK_UN
#endif /* !LOCK_UN && __LOCK_UN */
#endif /* __USE_MISC || __USE_BSD */



#ifdef __USE_XOPEN2K
/* No further special treatment. */
#ifdef __POSIX_FADV_NORMAL
#define POSIX_FADV_NORMAL __POSIX_FADV_NORMAL
#endif /* __POSIX_FADV_NORMAL */

/* Expect random page references. */
#ifdef __POSIX_FADV_RANDOM
#define POSIX_FADV_RANDOM __POSIX_FADV_RANDOM
#endif /* __POSIX_FADV_RANDOM */

/* Expect sequential page references. */
#ifdef __POSIX_FADV_SEQUENTIAL
#define POSIX_FADV_SEQUENTIAL __POSIX_FADV_SEQUENTIAL
#endif /* __POSIX_FADV_SEQUENTIAL */

/* Will need these pages. */
#ifdef __POSIX_FADV_WILLNEED
#define POSIX_FADV_WILLNEED __POSIX_FADV_WILLNEED
#endif /* __POSIX_FADV_WILLNEED */

/* Don't need these pages. */
#ifdef __POSIX_FADV_DONTNEED
#define POSIX_FADV_DONTNEED __POSIX_FADV_DONTNEED
#endif /* __POSIX_FADV_DONTNEED */

/* Data will be accessed once. */
#ifdef __POSIX_FADV_NOREUSE
#define POSIX_FADV_NOREUSE __POSIX_FADV_NOREUSE
#endif /* __POSIX_FADV_NOREUSE */
#endif /* !__USE_XOPEN2K */



#ifdef __USE_GNU
/* This is a mandatory flock: */
#if !defined(LOCK_MAND) && defined(__LOCK_MAND)
#define LOCK_MAND __LOCK_MAND
#endif /* !LOCK_MAND && __LOCK_MAND */

/* ... which allows concurrent read operations. */
#if !defined(LOCK_READ) && defined(__LOCK_READ)
#define LOCK_READ __LOCK_READ
#endif /* !LOCK_READ && __LOCK_READ */

/* ... which allows concurrent write operations. */
#if !defined(LOCK_WRITE) && defined(__LOCK_WRITE)
#define LOCK_WRITE __LOCK_WRITE
#endif /* !LOCK_WRITE && __LOCK_WRITE */

/* ... Which allows concurrent read & write operations. */
#if !defined(LOCK_RW) && defined(__LOCK_RW)
#define LOCK_RW __LOCK_RW
#endif /* !LOCK_RW && __LOCK_RW */

/* File accessed. */
#if !defined(DN_ACCESS) && defined(__DN_ACCESS)
#define DN_ACCESS __DN_ACCESS
#endif /* !DN_ACCESS && __DN_ACCESS */

/* File modified. */
#if !defined(DN_MODIFY) && defined(__DN_MODIFY)
#define DN_MODIFY __DN_MODIFY
#endif /* !DN_MODIFY && __DN_MODIFY */

/* File created. */
#if !defined(DN_CREATE) && defined(__DN_CREATE)
#define DN_CREATE __DN_CREATE
#endif /* !DN_CREATE && __DN_CREATE */

/* File removed. */
#if !defined(DN_DELETE) && defined(__DN_DELETE)
#define DN_DELETE __DN_DELETE
#endif /* !DN_DELETE && __DN_DELETE */

/* File renamed. */
#if !defined(DN_RENAME) && defined(__DN_RENAME)
#define DN_RENAME __DN_RENAME
#endif /* !DN_RENAME && __DN_RENAME */

/* File changed attributes. */
#if !defined(DN_ATTRIB) && defined(__DN_ATTRIB)
#define DN_ATTRIB __DN_ATTRIB
#endif /* !DN_ATTRIB && __DN_ATTRIB */

/* Don't remove notifier. */
#if !defined(DN_MULTISHOT) && defined(__DN_MULTISHOT)
#define DN_MULTISHOT __DN_MULTISHOT
#endif /* !DN_MULTISHOT && __DN_MULTISHOT */


/* PID Types. */
#if !defined(F_OWNER_TID) && defined(__F_OWNER_TID)
#define F_OWNER_TID __F_OWNER_TID /* Kernel thread. */
#endif /* !F_OWNER_TID && __F_OWNER_TID */
#if !defined(F_OWNER_PID) && defined(__F_OWNER_PID)
#define F_OWNER_PID __F_OWNER_PID /* Process. */
#endif /* !F_OWNER_PID && __F_OWNER_PID */
#if !defined(F_OWNER_PGRP) && defined(__F_OWNER_PGRP)
#define F_OWNER_PGRP __F_OWNER_PGRP /* Process group. */
#endif /* !F_OWNER_PGRP && __F_OWNER_PGRP */
#if !defined(F_OWNER_GID) && defined(__F_OWNER_PGRP)
#define F_OWNER_GID __F_OWNER_PGRP /* Alternative, obsolete name. */
#endif /* !F_OWNER_GID && __F_OWNER_PGRP */


/* Wait upon writeout of all pages in the range before performing the write. */
#if !defined(SYNC_FILE_RANGE_WAIT_BEFORE) && defined(__SYNC_FILE_RANGE_WAIT_BEFORE)
#define SYNC_FILE_RANGE_WAIT_BEFORE __SYNC_FILE_RANGE_WAIT_BEFORE
#endif /* !SYNC_FILE_RANGE_WAIT_BEFORE && __SYNC_FILE_RANGE_WAIT_BEFORE */

/* Initiate writeout of all those dirty pages in the range which are not presently under writeback. */
#if !defined(SYNC_FILE_RANGE_WRITE) && defined(__SYNC_FILE_RANGE_WRITE)
#define SYNC_FILE_RANGE_WRITE __SYNC_FILE_RANGE_WRITE
#endif /* !SYNC_FILE_RANGE_WRITE && __SYNC_FILE_RANGE_WRITE */

/* Wait upon writeout of all pages in the range after performing the write. */
#if !defined(SYNC_FILE_RANGE_WAIT_AFTER) && defined(__SYNC_FILE_RANGE_WAIT_AFTER)
#define SYNC_FILE_RANGE_WAIT_AFTER __SYNC_FILE_RANGE_WAIT_AFTER
#endif /* !SYNC_FILE_RANGE_WAIT_AFTER && __SYNC_FILE_RANGE_WAIT_AFTER */

/* Move pages instead of copying. */
#if !defined(SPLICE_F_MOVE) && defined(__SPLICE_F_MOVE)
#define SPLICE_F_MOVE __SPLICE_F_MOVE
#endif /* !SPLICE_F_MOVE && __SPLICE_F_MOVE */

/* Don't block on the pipe splicing (but we may still block on the fd we splice from/to). */
#if !defined(SPLICE_F_NONBLOCK) && defined(__SPLICE_F_NONBLOCK)
#define SPLICE_F_NONBLOCK __SPLICE_F_NONBLOCK
#endif /* !SPLICE_F_NONBLOCK && __SPLICE_F_NONBLOCK */

/* Expect more data. */
#if !defined(SPLICE_F_MORE) && defined(__SPLICE_F_MORE)
#define SPLICE_F_MORE __SPLICE_F_MORE
#endif /* !SPLICE_F_MORE && __SPLICE_F_MORE */

/* Pages passed in are a gift. */
#if !defined(SPLICE_F_GIFT) && defined(__SPLICE_F_GIFT)
#define SPLICE_F_GIFT __SPLICE_F_GIFT
#endif /* !SPLICE_F_GIFT && __SPLICE_F_GIFT */

/* Don't extend size of file even if offset + len is greater than file size. */
#if !defined(FALLOC_FL_KEEP_SIZE) && defined(__FALLOC_FL_KEEP_SIZE)
#define FALLOC_FL_KEEP_SIZE __FALLOC_FL_KEEP_SIZE
#endif /* !FALLOC_FL_KEEP_SIZE && __FALLOC_FL_KEEP_SIZE */
/* Create a hole in the file. */
#if !defined(FALLOC_FL_PUNCH_HOLE) && defined(__FALLOC_FL_PUNCH_HOLE)
#define FALLOC_FL_PUNCH_HOLE __FALLOC_FL_PUNCH_HOLE
#endif /* !FALLOC_FL_PUNCH_HOLE && __FALLOC_FL_PUNCH_HOLE */
/* Remove a range of a file without leaving a hole. */
#if !defined(FALLOC_FL_COLLAPSE_RANGE) && defined(__FALLOC_FL_COLLAPSE_RANGE)
#define FALLOC_FL_COLLAPSE_RANGE __FALLOC_FL_COLLAPSE_RANGE
#endif /* !FALLOC_FL_COLLAPSE_RANGE && __FALLOC_FL_COLLAPSE_RANGE */
/* Convert a range of a file to zeros. */
#if !defined(FALLOC_FL_ZERO_RANGE) && defined(__FALLOC_FL_ZERO_RANGE)
#define FALLOC_FL_ZERO_RANGE __FALLOC_FL_ZERO_RANGE
#endif /* !FALLOC_FL_ZERO_RANGE && __FALLOC_FL_ZERO_RANGE */

#if !defined(MAX_HANDLE_SZ) && defined(__MAX_HANDLE_SZ)
#define MAX_HANDLE_SZ __MAX_HANDLE_SZ
#endif /* !MAX_HANDLE_SZ && __MAX_HANDLE_SZ */

/* For use with `F_ADD_SEALS' and `F_GET_SEALS' */
#if !defined(F_SEAL_SEAL) && defined(__F_SEAL_SEAL)
#define F_SEAL_SEAL         __F_SEAL_SEAL         /* Prevent further modification of seals */
#endif /* !F_SEAL_SEAL && __F_SEAL_SEAL */
#if !defined(F_SEAL_SHRINK) && defined(__F_SEAL_SHRINK)
#define F_SEAL_SHRINK       __F_SEAL_SHRINK       /* Prevent the file's size from being truncated */
#endif /* !F_SEAL_SHRINK && __F_SEAL_SHRINK */
#if !defined(F_SEAL_GROW) && defined(__F_SEAL_GROW)
#define F_SEAL_GROW         __F_SEAL_GROW         /* Prevent the file's size from being increased */
#endif /* !F_SEAL_GROW && __F_SEAL_GROW */
#if !defined(F_SEAL_WRITE) && defined(__F_SEAL_WRITE)
#define F_SEAL_WRITE        __F_SEAL_WRITE        /* Prevent any modifications to the file's contents.
                                                   * If  writable memory mappings exist, trying to set
                                                   * this flag fails with TODO:EXCEPTION_FOR_EBUSY */
#endif /* !F_SEAL_WRITE && __F_SEAL_WRITE */
#if !defined(F_SEAL_FUTURE_WRITE) && defined(__F_SEAL_FUTURE_WRITE)
#define F_SEAL_FUTURE_WRITE __F_SEAL_FUTURE_WRITE /* Same as `F_SEAL_WRITE', but pre-existing, writable
                                                   * memory mappings continue to work. */
#endif /* !F_SEAL_FUTURE_WRITE && __F_SEAL_FUTURE_WRITE */

/* For use with `F_GET_RW_HINT' and `F_SET_RW_HINT' */
#if !defined(RWF_WRITE_LIFE_NOT_SET) && defined(__RWF_WRITE_LIFE_NOT_SET)
#define RWF_WRITE_LIFE_NOT_SET __RWF_WRITE_LIFE_NOT_SET /* ??? */
#endif /* !RWF_WRITE_LIFE_NOT_SET && __RWF_WRITE_LIFE_NOT_SET */
#if !defined(RWH_WRITE_LIFE_NONE) && defined(__RWH_WRITE_LIFE_NONE)
#define RWH_WRITE_LIFE_NONE    __RWH_WRITE_LIFE_NONE    /* ??? */
#endif /* !RWH_WRITE_LIFE_NONE && __RWH_WRITE_LIFE_NONE */
#if !defined(RWH_WRITE_LIFE_SHORT) && defined(__RWH_WRITE_LIFE_SHORT)
#define RWH_WRITE_LIFE_SHORT   __RWH_WRITE_LIFE_SHORT   /* ??? */
#endif /* !RWH_WRITE_LIFE_SHORT && __RWH_WRITE_LIFE_SHORT */
#if !defined(RWH_WRITE_LIFE_MEDIUM) && defined(__RWH_WRITE_LIFE_MEDIUM)
#define RWH_WRITE_LIFE_MEDIUM  __RWH_WRITE_LIFE_MEDIUM  /* ??? */
#endif /* !RWH_WRITE_LIFE_MEDIUM && __RWH_WRITE_LIFE_MEDIUM */
#if !defined(RWH_WRITE_LIFE_LONG) && defined(__RWH_WRITE_LIFE_LONG)
#define RWH_WRITE_LIFE_LONG    __RWH_WRITE_LIFE_LONG    /* ??? */
#endif /* !RWH_WRITE_LIFE_LONG && __RWH_WRITE_LIFE_LONG */
#if !defined(RWH_WRITE_LIFE_EXTREME) && defined(__RWH_WRITE_LIFE_EXTREME)
#define RWH_WRITE_LIFE_EXTREME __RWH_WRITE_LIFE_EXTREME /* ??? */
#endif /* !RWH_WRITE_LIFE_EXTREME && __RWH_WRITE_LIFE_EXTREME */

#endif /* __USE_GNU */



#if defined(__USE_ATFILE) || defined(__USE_BSD) || defined(__USE_XOPEN2K8)

/* Special value used to indicate the *at functions
 * should  use  the   current  working   directory. */
#if !defined(AT_FDCWD) && defined(__AT_FDCWD)
#define AT_FDCWD __AT_FDCWD
#endif /* !AT_FDCWD && __AT_FDCWD */

/* If the last path component is a symlink, don't follow it. */
#if !defined(AT_SYMLINK_NOFOLLOW) && defined(__AT_SYMLINK_NOFOLLOW)
#define AT_SYMLINK_NOFOLLOW __AT_SYMLINK_NOFOLLOW
#endif /* !AT_SYMLINK_NOFOLLOW && __AT_SYMLINK_NOFOLLOW */

/* Remove directory instead of unlinking file. */
#if !defined(AT_REMOVEDIR) && defined(__AT_REMOVEDIR)
#define AT_REMOVEDIR __AT_REMOVEDIR
#endif /* !AT_REMOVEDIR && __AT_REMOVEDIR */

/* Test access permitted for effective IDs, not real IDs. */
#if !defined(AT_EACCESS) && defined(__AT_EACCESS)
#define AT_EACCESS __AT_EACCESS
#endif /* !AT_EACCESS && __AT_EACCESS */

/* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#if !defined(AT_SYMLINK_FOLLOW) && defined(__AT_SYMLINK_FOLLOW)
#define AT_SYMLINK_FOLLOW __AT_SYMLINK_FOLLOW
#endif /* !AT_SYMLINK_FOLLOW && __AT_SYMLINK_FOLLOW */

#if defined(__USE_GNU) || defined(__USE_KOS_KERNEL)
/* Suppress terminal automount traversal. */
#if !defined(AT_NO_AUTOMOUNT) && defined(__AT_NO_AUTOMOUNT)
#define AT_NO_AUTOMOUNT __AT_NO_AUTOMOUNT
#endif /* !AT_NO_AUTOMOUNT && __AT_NO_AUTOMOUNT */

/* Allow empty relative pathname. */
#if !defined(AT_EMPTY_PATH) && defined(__AT_EMPTY_PATH)
#define AT_EMPTY_PATH __AT_EMPTY_PATH
#endif /* !AT_EMPTY_PATH && __AT_EMPTY_PATH */
#endif /* __USE_GNU || __USE_KOS_KERNEL */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
/* For use with `utimensat' and friends: Take `struct timespec[3]', where the 3rd entry
 * (when not  equal to  `UTIME_OMIT') is  used to  override the  file brith  timestamp.
 * NOTE: Passing this flag when the 3rd  timespec isn't set to `UTIME_OMIT'  requires
 *       that the calling thread be holding the `CAP_SYS_TIME' permission and be  the
 *       owner of the file in question, or to be holding the `CAP_FOWNER' permission.
 *       Less permissions  are required  when `UTIME_NOW'  is passed,  in which  case
 *       `CAP_SYS_TIME' is not required (similarly how having `CAP_FOWNER', or  being
 *       the owner would allow  you to copy the  file (updating the timestamp),  then
 *       replacing the original)
 * NOTE: This flag is used to implement full compatibility with NT's SetFileTime function. */
#if !defined(AT_CHANGE_BTIME) && defined(__AT_CHANGE_BTIME)
#define AT_CHANGE_BTIME __AT_CHANGE_BTIME
#endif /* !AT_CHANGE_BTIME && __AT_CHANGE_BTIME */

/* For use with `freadlinkat' and friends.
 * Rather  than following  unix semantics  and returning  the amount of
 * copied bytes with  no indication  of whether or  not everything  was
 * copied, return the ~required~  buffer size (including a  terminating
 * NUL-character that normally wouldn't be copied either) to user-space
 * (which may be more than the  specified buffer size, which should  be
 * reallocated to fit in successive calls)
 * Additionally, as already  mentioned, a  trailing NUL-character  is
 * appended  to the link  text, ensuring that  a valid C-style string
 * can be read so long as the provided buffer was of sufficient size. */
#if !defined(AT_READLINK_REQSIZE) && defined(__AT_READLINK_REQSIZE)
#define AT_READLINK_REQSIZE __AT_READLINK_REQSIZE
#endif /* !AT_READLINK_REQSIZE && __AT_READLINK_REQSIZE */

/* Explicitly allow removing anything that unlink() removes. (Default;
 * Set in addition to `AT_REMOVEDIR' to implement `remove()' semantics
 * as an atomic kernel operation, removing any race condition that the
 * alternative  of  `if (unlink(x) && errno == EISDIR) rmdir(x)' would
 * introduce). */
#if !defined(AT_REMOVEREG) && defined(__AT_REMOVEREG)
#define AT_REMOVEREG __AT_REMOVEREG
#endif /* !AT_REMOVEREG && __AT_REMOVEREG */

/* For `frealpath4' / `frealpathat': the specified path should
 * be  printed  as  the  reverse  of  the  `AT_DOSPATH'  flag:
 *  - 0                      : in:UNIX  out:UNIX
 *  - AT_DOSPATH             : in:DOS   out:DOS
 *  - AT_ALTPATH             : in:UNIX  out:DOS
 *  - AT_ALTPATH | AT_DOSPATH: in:DOS   out:UNIX */
#if !defined(AT_ALTPATH) && defined(__AT_ALTPATH)
#define AT_ALTPATH __AT_ALTPATH
#endif /* !AT_ALTPATH && __AT_ALTPATH */

/* Interpret '\\'  as  '/',  and ignore  casing  during  path  resolution.
 * Additionally,  recognize  `<LETTER>:'-style  drive  prefixes,  as  well
 * as make use of per-drive working directories, as well as drive-relative
 * path names that start with a leading slash.
 * Basically, when set: perform the system call in DOS-compatibility mode.
 * HINT:  This  flag can  be specified  with  the `fsmode()'  system call. */
#if !defined(AT_DOSPATH) && defined(__AT_DOSPATH)
#define AT_DOSPATH __AT_DOSPATH
#endif /* !AT_DOSPATH && __AT_DOSPATH */

/* Same as `AT_FDCWD' but sets the filesystem root
 * (using this, you can `chroot()' with 'dup2()'!) */
#if !defined(AT_FDROOT) && defined(__AT_FDROOT)
#define AT_FDROOT __AT_FDROOT
#endif /* !AT_FDROOT && __AT_FDROOT */

/* Special, symbolic file numbers.
 * These descriptors cannot be overwritten, and their meaning is context-sensitive. */

/* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(gettid())') */
#if !defined(AT_FDTHRD) && defined(__AT_FDTHRD)
#define AT_FDTHRD __AT_FDTHRD
#endif /* !AT_FDTHRD && __AT_FDTHRD */

/* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(getpid())') */
#if !defined(AT_FDPROC) && defined(__AT_FDPROC)
#define AT_FDPROC __AT_FDPROC
#endif /* !AT_FDPROC && __AT_FDPROC */

/* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(getppid())') */
#if !defined(AT_FDPARPROC) && defined(__AT_FDPARPROC)
#define AT_FDPARPROC __AT_FDPARPROC
#endif /* !AT_FDPARPROC && __AT_FDPARPROC */

/* HANDLE_TYPE_MFILE (read-only; equivalent of `open("/dev/tty")') */
#if !defined(AT_FDCTTY) && defined(__AT_FDCTTY)
#define AT_FDCTTY __AT_FDCTTY
#endif /* !AT_FDCTTY && __AT_FDCTTY */


#ifdef __USE_KOS_KERNEL
/* HANDLE_TYPE_MFILE (read-only; Handle for `execabi_system_rtld_file')
 * Can be used to mmap() additional instances of the system RTLD, or to
 * relocate the system RTLD to a different address. */
#if !defined(AT_FDSYSRTLD) && defined(__AT_FDSYSRTLD)
#define AT_FDSYSRTLD __AT_FDSYSRTLD
#endif /* !AT_FDSYSRTLD && __AT_FDSYSRTLD */
#endif /* __USE_KOS_KERNEL */


/* DOS Drive root / current-working paths.
 * These are special file descriptors that can be written to using `dup2()',
 * where   they  expect  to  receive  either  a  FILE  or  PATH  descriptor.
 * Once  set,  these  paths  describe   the  root-paths  of  DOS's   drives:
 * >> // Force DOS filesystem semantics for all filesystem operations.
 * >> struct fsmask mask = {0,0};
 * >> mask = fsmode(mask);
 * >> mask.fm_mask &= ~AT_DOSPATH;
 * >> mask.fm_mode |=  AT_DOSPATH;
 * >> fsmode(mask);
 * >>
 * >> // Mount some filesystem locations as DOS drives.
 * >> dup2(open("/"), AT_FDDRIVE_ROOT('C'));
 * >> dup2(open("/bin"), AT_FDDRIVE_ROOT('D'));
 * >> dup2(open("/home"), AT_FDDRIVE_ROOT('E'));
 * >>
 * >> // Open a file on a dos-path.
 * >> open("D:\\ls"); // open("/bin/ls")
 * >>
 * >> // Explicitly set the current-working directory of a specific drive.
 * >> // NOTE: Requires that the opened path be reachable from `AT_FDDRIVE_ROOT('E')'
 * >> //       If it isn't, an `E_FSERROR_CROSS_DEVICE_LINK' error is thrown.
 * >> dup2(open("/home/me/Downloads"), AT_FDDRIVE_CWD('E'));
 * >>
 * >> chdir("C:\\bin"); // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('C') = AT_FDCWD;
 * >> chdir("E:");      // AT_FDCWD = AT_FDDRIVE_CWD('E'); (`/home/me/Downloads')
 * >> chdir("E:\\");    // AT_FDCWD = "/home"; AT_FDDRIVE_CWD('E') = AT_FDCWD;
 * >> chdir("C:");      // AT_FDCWD = AT_FDDRIVE_CWD('C'); (`/bin')
 * >> chdir("D:\\");    // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD;
 * >> chdir("..");      // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD; (Don't escape the current drive)
 * >>
 * NOTES:
 *   - Setting the root-path of a drive will not update the drive working directories of processes sharing VFS.
 *     With  that  in   mind,  you   should  not   re-mount  a   DOS  drive   as  a   sub-directory  of   where
 *     it  was   located  before   then,  unless   you   first  unshared   your  VFS   (using   `CLONE_NEWNS').
 *     Allowing  a   program's   current   working   directory   to   be   located   outside   the   associated
 *     drive causes weak undefined behavior. In KOS this means:
 *       - `xfdname()' will not produce the correct path
 *       - Relative path names still operate on the old directory
 *       - Navigating into parent directories is no longer restricted (except by `chroot()')
 *       - Manually navigating into a portion of the new drives mounting point fixes the problem.
 *   - DOS drive mounting points are beneath UNIX mounting points, in that they don't
 *     actually mount a superblock to some  filesystem location, but rather mirror  a
 *     filesystem  path, meaning that DOS drives can  be thought of as the equivalent
 *     of the `dfd' argument of `*at' system calls:
 *     >> open("C:\\foo.txt"); // Same as `openat(AT_FDDRIVE_ROOT('C'), "foo.txt")'
 *     If `mount()' is used to create a  new (real) mounting point, it will  appear
 *     in  all DOS drives that are mounting  the location where the mount happened,
 *     or  any location further up the tree  immediately (it's the same data object
 *     internally; DOS drives are merely aliasing regular paths; aka. `O_PATH')
 *   - To ~unmount~ (quote-unquote) a DOS drive, simply close() the associated root file descriptor:
 *     >> // Unmount `C:' (also closes the associated FDCWD descriptor)
 *     >> close(AT_FDDRIVE_ROOT('C'));
 *   - Mounting, or unmounting dos drives requires the same privileges as the `mount()' and `umount()' system calls.
 *   - Closing an `AT_FDDRIVE_CWD()' descriptor will revert it to match the root path of the associated drive.
 *     >> close(AT_FDDRIVE_CWD('C'));
 *     >> // Same as:
 *     >> dup2(AT_FDDRIVE_ROOT('C'),AT_FDDRIVE_CWD('C'));
 *   - Symbolic links  are evaluated  the same  as any  user-provided  path.
 *     If a symbolic link starts with a '/' or '\\' character, the remainder
 *     of its  text  is relative  to  the  first DOS  drive  mounting  point
 *     encountered while walking up the chain of parent directories. */
#if !defined(AT_FDDRIVE_CWD) && defined(__AT_FDDRIVE_CWD)
#define AT_FDDRIVE_CWD(drivechar) __AT_FDDRIVE_CWD(drivechar)
#endif /* !AT_FDDRIVE_CWD && __AT_FDDRIVE_CWD */
#if !defined(AT_FDDRIVE_ROOT) && defined(__AT_FDDRIVE_ROOT)
#define AT_FDDRIVE_ROOT(drivechar) __AT_FDDRIVE_ROOT(drivechar)
#endif /* !AT_FDDRIVE_ROOT && __AT_FDDRIVE_ROOT */
#if !defined(AT_DOS_DRIVEMIN) && defined(__AT_DOS_DRIVEMIN)
#define AT_DOS_DRIVEMIN __AT_DOS_DRIVEMIN
#endif /* !AT_DOS_DRIVEMIN && __AT_DOS_DRIVEMIN */
#if !defined(AT_DOS_DRIVEMAX) && defined(__AT_DOS_DRIVEMAX)
#define AT_DOS_DRIVEMAX __AT_DOS_DRIVEMAX
#endif /* !AT_DOS_DRIVEMAX && __AT_DOS_DRIVEMAX */
#endif /* __USE_KOS */
#endif /* __USE_ATFILE || __USE_BSD || __USE_XOPEN2K8 */



#ifdef __USE_DOS
/* DOS extension flags. */
#if !defined(O_RAW) && defined(__O_BINARY)
#define O_RAW           __O_BINARY
#endif /* !O_RAW && __O_BINARY */
#if !defined(_O_RAW) && defined(__O_BINARY)
#define _O_RAW          __O_BINARY
#endif /* !_O_RAW && __O_BINARY */
#if !defined(O_SEQUENTIAL) && defined(__O_SEQUENTIAL)
#define O_SEQUENTIAL    __O_SEQUENTIAL
#endif /* !O_SEQUENTIAL && __O_SEQUENTIAL */
#if !defined(_O_SEQUENTIAL) && defined(__O_SEQUENTIAL)
#define _O_SEQUENTIAL   __O_SEQUENTIAL
#endif /* !_O_SEQUENTIAL && __O_SEQUENTIAL */
#if !defined(O_RANDOM) && defined(__O_RANDOM)
#define O_RANDOM        __O_RANDOM
#endif /* !O_RANDOM && __O_RANDOM */
#if !defined(_O_RANDOM) && defined(__O_RANDOM)
#define _O_RANDOM       __O_RANDOM
#endif /* !_O_RANDOM && __O_RANDOM */
#if !defined(_O_SHORT_LIVED) && defined(__O_SHORT_LIVED)
#define _O_SHORT_LIVED  __O_SHORT_LIVED
#endif /* !_O_SHORT_LIVED && __O_SHORT_LIVED */
#if !defined(_O_U16TEXT) && defined(__O_U16TEXT)
#define _O_U16TEXT      __O_U16TEXT
#endif /* !_O_U16TEXT && __O_U16TEXT */
#if !defined(_O_U8TEXT) && defined(__O_U8TEXT)
#define _O_U8TEXT       __O_U8TEXT
#endif /* !_O_U8TEXT && __O_U8TEXT */
#if !defined(_O_WTEXT) && defined(__O_WTEXT)
#define _O_WTEXT        __O_WTEXT
#endif /* !_O_WTEXT && __O_WTEXT */
#if !defined(_O_OBTAIN_DIR) && defined(__O_OBTAIN_DIR)
#define _O_OBTAIN_DIR   __O_OBTAIN_DIR
#endif /* !_O_OBTAIN_DIR && __O_OBTAIN_DIR */
#if !defined(O_TEMPORARY) && defined(__O_TMPFILE)
#define O_TEMPORARY     __O_TMPFILE
#endif /* !O_TEMPORARY && __O_TMPFILE */
#if !defined(_O_TEMPORARY) && defined(__O_TMPFILE)
#define _O_TEMPORARY    __O_TMPFILE
#endif /* !_O_TEMPORARY && __O_TMPFILE */
#if !defined(_O_BINARY) && defined(__O_BINARY)
#define _O_BINARY       __O_BINARY
#endif /* !_O_BINARY && __O_BINARY */
#if !defined(_O_TEXT) && defined(__O_TEXT)
#define _O_TEXT         __O_TEXT
#endif /* !_O_TEXT && __O_TEXT */

/* DOS name aliases */
#if !defined(_O_RDONLY) && defined(__O_RDONLY)
#define _O_RDONLY __O_RDONLY
#endif /* !_O_RDONLY && __O_RDONLY */
#if !defined(_O_WRONLY) && defined(__O_WRONLY)
#define _O_WRONLY __O_WRONLY
#endif /* !_O_WRONLY && __O_WRONLY */
#if !defined(_O_RDWR) && defined(__O_RDWR)
#define _O_RDWR __O_RDWR
#endif /* !_O_RDWR && __O_RDWR */
#if !defined(_O_APPEND) && defined(__O_APPEND)
#define _O_APPEND __O_APPEND
#endif /* !_O_APPEND && __O_APPEND */
#if !defined(_O_CREAT) && defined(__O_CREAT)
#define _O_CREAT __O_CREAT
#endif /* !_O_CREAT && __O_CREAT */
#if !defined(_O_EXCL) && defined(__O_EXCL)
#define _O_EXCL __O_EXCL
#endif /* !_O_EXCL && __O_EXCL */
#if !defined(_O_TRUNC) && defined(__O_TRUNC)
#define _O_TRUNC __O_TRUNC
#endif /* !_O_TRUNC && __O_TRUNC */
#if !defined(O_NOINHERIT) && defined(__O_CLOEXEC)
#define O_NOINHERIT __O_CLOEXEC
#endif /* !O_NOINHERIT && __O_CLOEXEC */
#if !defined(_O_NOINHERIT) && defined(__O_CLOEXEC)
#define _O_NOINHERIT __O_CLOEXEC
#endif /* !_O_NOINHERIT && __O_CLOEXEC */
#endif /* __USE_DOS */




#ifndef __OPEN_NEEDS_MODE
#if defined(__O_CREAT) && defined(__O_TMPFILE)
#define __OPEN_NEEDS_MODE(oflags) (((oflags) & __O_CREAT) || ((oflags) & __O_TMPFILE) == __O_TMPFILE)
#elif defined(__O_CREAT)
#define __OPEN_NEEDS_MODE(oflags) ((oflags) & __O_CREAT)
#else /* __O_TMPFILE */
#define __OPEN_NEEDS_MODE(oflags) 0
#endif /* !__O_TMPFILE */
#endif /* !__OPEN_NEEDS_MODE */


/* For XPG all symbols from <sys/stat.h> should also be available. */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#if !defined(S_IFMT) && defined(__S_IFMT)
#define S_IFMT  __S_IFMT /* These bits determine file type. */
#endif /* !S_IFMT && __S_IFMT */
#if !defined(S_IFDIR) && defined(__S_IFDIR)
#define S_IFDIR __S_IFDIR /* Directory. */
#endif /* !S_IFDIR && __S_IFDIR */
#if !defined(S_IFCHR) && defined(__S_IFCHR)
#define S_IFCHR __S_IFCHR /* Character device. */
#endif /* !S_IFCHR && __S_IFCHR */
#if !defined(S_IFBLK) && defined(__S_IFBLK)
#define S_IFBLK __S_IFBLK /* Block device. */
#endif /* !S_IFBLK && __S_IFBLK */
#if !defined(S_IFREG) && defined(__S_IFREG)
#define S_IFREG __S_IFREG /* Regular file. */
#endif /* !S_IFREG && __S_IFREG */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO __S_IFIFO /* FIFO. */
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK __S_IFLNK /* Symbolic link. */
#endif /* !S_IFLNK && __S_IFLNK */
#if ((defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)) && \
     (!defined(S_IFSOCK) && defined(__S_IFSOCK)))
#define S_IFSOCK __S_IFSOCK /* Socket. */
#endif /* (__USE_UNIX98 || __USE_XOPEN2K8) && (!S_IFSOCK && __S_IFSOCK) */
#if !defined(S_ISUID) && defined(__S_ISUID)
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#endif /* !S_ISUID && __S_ISUID */
#if !defined(S_ISGID) && defined(__S_ISGID)
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif /* !S_ISGID && __S_ISGID */
#if ((defined(__USE_MISC) || defined(__USE_XOPEN)) && \
     (!defined(S_ISVTX) && defined(__S_ISVTX)))
#define S_ISVTX __S_ISVTX /* Save swapped text after use (sticky). */
#endif /* (__USE_MISC || __USE_XOPEN) && (!S_ISVTX && __S_ISVTX) */

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#define S_IWUSR 0200 /* Write by owner. */
#define S_IXUSR 0100 /* Execute by owner. */
#define S_IRWXU 0700
#define S_IRGRP 0040 /* Read by group. */
#define S_IWGRP 0020 /* Write by group. */
#define S_IXGRP 0010 /* Execute by group. */
#define S_IRWXG 0070
#define S_IROTH 0004 /* Read by others. */
#define S_IWOTH 0002 /* Write by others. */
#define S_IXOTH 0001 /* Execute by others. */
#define S_IRWXO 0007
#endif /* !S_IRWXO */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __USE_MISC
#if !defined(R_OK) && defined(__R_OK)
#define R_OK __R_OK /* Test for read permission. */
#endif /* !R_OK && __R_OK */
#if !defined(W_OK) && defined(__W_OK)
#define W_OK __W_OK /* Test for write permission. */
#endif /* !W_OK && __W_OK */
#if !defined(X_OK) && defined(__X_OK)
#define X_OK __X_OK /* Test for execute permission. */
#endif /* !X_OK && __X_OK */
#if !defined(F_OK) && defined(__F_OK)
#define F_OK __F_OK /* Test for existence. */
#endif /* !F_OK && __F_OK */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */
#endif /* __USE_GNU || __USE_SOLARIS */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */




#if defined(__USE_NEWLIB) || defined(__USE_NETBSD)
#if !defined(FREAD) && defined(__O_FREAD)
#define FREAD   __O_FREAD
#endif /* !FREAD && __O_FREAD */
#if !defined(FWRITE) && defined(__O_FWRITE)
#define FWRITE  __O_FWRITE
#endif /* !FWRITE && __O_FWRITE */
#endif /* __USE_NEWLIB || __USE_NETBSD */


#ifdef __USE_NEWLIB
/* API_LEVEL: newlib */
#if !defined(_FOPEN) && defined(__O_FOPEN)
#define _FOPEN __O_FOPEN
#endif /* !_FOPEN && __O_FOPEN */

#if !defined(_FREAD) && defined(__O_FREAD)
#define _FREAD   __O_FREAD   /* ... */
#endif /* !_FREAD && __O_FREAD */
#if !defined(_FWRITE) && defined(__O_FWRITE)
#define _FWRITE  __O_FWRITE  /* ... */
#endif /* !_FWRITE && __O_FWRITE */
#if !defined(_FMARK) && defined(__O_FMARK)
#define _FMARK   __O_FMARK   /* ... */
#endif /* !_FMARK && __O_FMARK */
#if !defined(_FDEFER) && defined(__O_FDEFER)
#define _FDEFER  __O_FDEFER  /* ... */
#endif /* !_FDEFER && __O_FDEFER */
#if !defined(_FSHLOCK) && defined(__O_SHLOCK)
#define _FSHLOCK __O_SHLOCK /* ... */
#endif /* !_FSHLOCK && __O_SHLOCK */
#if !defined(_FEXLOCK) && defined(__O_EXLOCK)
#define _FEXLOCK __O_EXLOCK /* ... */
#endif /* !_FEXLOCK && __O_EXLOCK */

#if !defined(_FAPPEND) && defined(__O_APPEND)
#define _FAPPEND    __O_APPEND /* Always append data to the end of the file */
#endif /* !_FAPPEND && __O_APPEND */
#if !defined(_FASYNC) && defined(__O_ASYNC)
#define _FASYNC     __O_ASYNC
#endif /* !_FASYNC && __O_ASYNC */
#if !defined(_FCREAT) && defined(__O_CREAT)
#define _FCREAT     __O_CREAT
#endif /* !_FCREAT && __O_CREAT */
#if !defined(_FTRUNC) && defined(__O_TRUNC)
#define _FTRUNC     __O_TRUNC
#endif /* !_FTRUNC && __O_TRUNC */
#if !defined(_FEXCL) && defined(__O_EXCL)
#define _FEXCL      __O_EXCL
#endif /* !_FEXCL && __O_EXCL */
#if !defined(_FNBIO) && defined(__O_NBIO)
#define _FNBIO      __O_NBIO     /* Do not block when trying to read data that hasn't been written, yet. */
#elif !defined(_FNBIO) && defined(__O_NONBLOCK)
#define _FNBIO      __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !_FNBIO && __O_NONBLOCK */
#if !defined(_FSYNC) && defined(__O_SYNC)
#define _FSYNC      __O_SYNC
#endif /* !_FSYNC && __O_SYNC */
#if !defined(_FNONBLOCK) && defined(__O_NONBLOCK)
#define _FNONBLOCK  __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !_FNONBLOCK && __O_NONBLOCK */
#if !defined(_FNDELAY) && defined(__O_NONBLOCK)
#define _FNDELAY    __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !_FNDELAY && __O_NONBLOCK */
#if !defined(_FNOCTTY) && defined(__O_NOCTTY)
#define _FNOCTTY    __O_NOCTTY
#endif /* !_FNOCTTY && __O_NOCTTY */
#if !defined(_FBINARY) && defined(__O_BINARY)
#define _FBINARY    __O_BINARY
#endif /* !_FBINARY && __O_BINARY */
#if !defined(_FTEXT) && defined(__O_TEXT)
#define _FTEXT      __O_TEXT
#endif /* !_FTEXT && __O_TEXT */
#if !defined(_FNOINHERIT) && defined(__O_CLOEXEC)
#define _FNOINHERIT __O_CLOEXEC
#endif /* !_FNOINHERIT && __O_CLOEXEC */
#if !defined(_FDIRECT) && defined(__O_DIRECT)
#define _FDIRECT    __O_DIRECT
#endif /* !_FDIRECT && __O_DIRECT */
#if !defined(_FNOFOLLOW) && defined(__O_NOFOLLOW)
#define _FNOFOLLOW  __O_NOFOLLOW
#endif /* !_FNOFOLLOW && __O_NOFOLLOW */
#if !defined(_FDIRECTORY) && defined(__O_DIRECTORY)
#define _FDIRECTORY __O_DIRECTORY
#endif /* !_FDIRECTORY && __O_DIRECTORY */
#if !defined(_FEXECSRCH) && defined(__O_EXEC)
#define _FEXECSRCH  __O_EXEC
#endif /* !_FEXECSRCH && __O_EXEC */
#if !defined(_FTMPFILE) && defined(__O_TMPFILE)
#define _FTMPFILE   __O_TMPFILE
#endif /* !_FTMPFILE && __O_TMPFILE */
#if !defined(_FNOATIME) && defined(__O_NOATIME)
#define _FNOATIME   __O_NOATIME
#endif /* !_FNOATIME && __O_NOATIME */

#ifdef __USE_MISC
#if !defined(FSYNC) && defined(__O_SYNC)
#define FSYNC __O_SYNC /* ??? */
#endif /* !FSYNC && __O_SYNC */

#if !defined(FNBIO) && defined(__O_NBIO)
#define FNBIO __O_NBIO     /* Do not block when trying to read data that hasn't been written, yet. */
#elif !defined(FNBIO) && defined(__O_NONBLOCK)
#define FNBIO __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !FNBIO && __O_NONBLOCK */

#if !defined(FNONBIO) && defined(__O_NONBLOCK)
#define FNONBIO __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !FNONBIO && __O_NONBLOCK */

#if !defined(FMARK) && defined(__O_FMARK)
#define FMARK   __O_FMARK
#endif /* !FMARK && __O_FMARK */
#if !defined(FDEFER) && defined(__O_FDEFER)
#define FDEFER  __O_FDEFER
#endif /* !FDEFER && __O_FDEFER */
#if !defined(FSHLOCK) && defined(__O_SHLOCK)
#define FSHLOCK __O_SHLOCK
#endif /* !FSHLOCK && __O_SHLOCK */
#if !defined(FEXLOCK) && defined(__O_EXLOCK)
#define FEXLOCK __O_EXLOCK
#endif /* !FEXLOCK && __O_EXLOCK */

#if !defined(FOPEN) && defined(__O_FOPEN)
#define FOPEN   __O_FOPEN
#endif /* !FOPEN && __O_FOPEN */
#if !defined(FCREAT) && defined(__O_CREAT)
#define FCREAT  __O_CREAT  /* If missing, create a new file */
#endif /* !FCREAT && __O_CREAT */
#if !defined(FTRUNC) && defined(__O_TRUNC)
#define FTRUNC  __O_TRUNC  /* Truncate (clear) the named file if it already exists,
                            * and  `O_WRONLY'  or  `O_RDWR'  access  is  specified. */
#endif /* !FTRUNC && __O_TRUNC */
#if !defined(FEXCL) && defined(__O_EXCL)
#define FEXCL   __O_EXCL   /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                            * exception if the file already exists. */
#endif /* !FEXCL && __O_EXCL */
#if !defined(FNOCTTY) && defined(__O_NOCTTY)
#define FNOCTTY __O_NOCTTY /* If the calling process does not have a controlling terminal assigned,
                            * do not attempt to assign the newly opened file as terminal, even when
                            * `isatty(open(...))' would be true. */
#endif /* !FNOCTTY && __O_NOCTTY */
#endif /* __USE_MISC */

#ifdef __USE_BSD
#if !defined(FNONBLOCK) && defined(__O_NONBLOCK)
#define FNONBLOCK __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !FNONBLOCK && __O_NONBLOCK */
#endif /* __USE_BSD */

#endif /* __USE_NEWLIB */


#ifdef __CC__

#ifdef __USE_SOLARIS
typedef struct flock flock_t;
#ifdef __USE_LARGEFILE64
typedef struct flock64 flock64_t;
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_SOLARIS */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */

#ifndef __off_t_defined
#define __off_t_defined
typedef __off_t off_t;
#endif /* !__off_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifdef __USE_GNU
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#ifdef __CRT_HAVE_readahead
__CDECLARE(__ATTR_FDREAD(1),__SSIZE_TYPE__,__NOTHROW_NCX,readahead,(__fd_t __fd, __PIO_OFFSET64 __offset, __SIZE_TYPE__ __count),(__fd,__offset,__count))
#else /* __CRT_HAVE_readahead */
#include <libc/local/fcntl/readahead.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(readahead, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL readahead)(__fd_t __fd, __PIO_OFFSET64 __offset, __SIZE_TYPE__ __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readahead))(__fd, __offset, __count); })
#endif /* !__CRT_HAVE_readahead */
#ifdef __CRT_HAVE_sync_file_range
__CDECLARE(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,sync_file_range,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __count, unsigned int __flags),(__fd,__offset,__count,__flags))
#else /* __CRT_HAVE_sync_file_range */
#include <libc/local/fcntl/sync_file_range.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sync_file_range, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) int __NOTHROW_NCX(__LIBCCALL sync_file_range)(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __count, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sync_file_range))(__fd, __offset, __count, __flags); })
#endif /* !__CRT_HAVE_sync_file_range */
struct iovec;
__CDECLARE_OPT(__ATTR_FDWRITE(1),__SSIZE_TYPE__,__NOTHROW_RPC,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __SIZE_TYPE__ __count, unsigned int __flags),(__fdout,__iov,__count,__flags))
__CDECLARE_OPT(__ATTR_FDREAD(1) __ATTR_FDWRITE(3) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_RPC,splice,(__fd_t __fdin, __PIO_OFFSET64 *__offin, __fd_t __fdout, __PIO_OFFSET64 *__offout, __SIZE_TYPE__ __length, unsigned int __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
__CDECLARE_OPT(__ATTR_FDREAD(1) __ATTR_FDWRITE(2),__SSIZE_TYPE__,__NOTHROW_RPC,tee,(__fd_t __fdin, __fd_t __fdout, __SIZE_TYPE__ __length, unsigned int __flags),(__fdin,__fdout,__length,__flags))
__CDECLARE_OPT(__ATTR_OUT(3),int,__NOTHROW_RPC,name_to_handle_at,(__fd_t __dirfd, char const *__name, struct file_handle *__handle, int *__mnt_id, int __flags),(__dirfd,__name,__handle,__mnt_id,__flags))
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_IN(2),__fd_t,__NOTHROW_RPC,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle *__handle, int __flags),(__mountdirfd,__handle,__flags))
#if defined(__CRT_HAVE_fallocate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,fallocate,(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET __offset, __PIO_OFFSET __length),(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,fallocate,(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET __offset, __PIO_OFFSET __length),fallocate64,(__fd,__mode,__offset,__length))
#else /* ... */
#include <libc/local/fcntl/fallocate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fallocate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL fallocate)(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET __offset, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fallocate))(__fd, __mode, __offset, __length); })
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_fallocate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,fallocate64,(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),fallocate,(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate64)
__CDECLARE(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,fallocate64,(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),(__fd,__mode,__offset,__length))
#else /* ... */
#include <libc/local/fcntl/fallocate64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fallocate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) int __NOTHROW_NCX(__LIBCCALL fallocate64)(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fallocate64))(__fd, __mode, __offset, __length); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */
#ifndef __fcntl_defined
#define __fcntl_defined
#ifdef __CRT_HAVE_fcntl
__LIBC __ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fcntl)(__fd_t __fd, __fcntl_t __cmd, ...) __CASMNAME_SAME("fcntl");
#elif defined(__CRT_HAVE___fcntl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,fcntl,(__fd_t __fd, __fcntl_t __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___libc_fcntl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,fcntl,(__fd_t __fd, __fcntl_t __cmd),__libc_fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __fcntl_defined
#endif /* !... */
#endif /* !__fcntl_defined */
#ifndef __open_defined
#define __open_defined
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open");
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/fcntl/open.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(open, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))(__filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define open(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __open_defined
#endif /* !... */
#endif /* !__open_defined */
#ifndef __creat_defined
#define __creat_defined
#if defined(__CRT_HAVE_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE___creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),__creat,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),__libc_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat64)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))
#include <libc/local/fcntl/creat.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(creat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__LIBCCALL creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); })
#else /* ... */
#undef __creat_defined
#endif /* !... */
#endif /* !__creat_defined */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open64)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open64");
#elif defined(__CRT_HAVE___open64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)
#include <libc/local/fcntl/open64.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(open64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL open64)(char const *__filename, __oflag_t __oflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))(__filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define open64(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifndef __creat64_defined
#define __creat64_defined
#if defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE___creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),__creat,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),__libc_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat64)
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open))
#include <libc/local/fcntl/creat64.h>
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(creat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__LIBCCALL creat64)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat64))(__filename, __mode); })
#else /* ... */
#undef __creat64_defined
#endif /* !... */
#endif /* !__creat64_defined */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_ATFILE
#ifndef __openat_defined
#define __openat_defined
#if defined(__CRT_HAVE_openat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __fd_t __NOTHROW_RPC(__VLIBCCALL openat)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("openat");
#elif defined(__CRT_HAVE_openat64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
#include <libc/local/fcntl/openat.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(openat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __fd_t __NOTHROW_RPC(__VLIBCCALL openat)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat))(__dirfd, __filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define openat(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __openat_defined
#endif /* !... */
#endif /* !__openat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __openat64_defined
#define __openat64_defined
#if defined(__CRT_HAVE_openat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat64)
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __fd_t __NOTHROW_RPC(__VLIBCCALL openat64)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("openat64");
#elif defined(__CRT_HAVE_openat)
#include <libc/local/fcntl/openat64.h>
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(openat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __fd_t __NOTHROW_RPC(__VLIBCCALL openat64)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat64))(__dirfd, __filename, __oflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define openat64(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat64))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __openat64_defined
#endif /* !... */
#endif /* !__openat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */

#ifdef __USE_XOPEN2K
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_posix_fadvise) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fadvise,(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length, __STDC_INT_AS_UINT_T __advise),(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fadvise,(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length, __STDC_INT_AS_UINT_T __advise),posix_fadvise64,(__fd,__offset,__length,__advise))
#else /* ... */
#include <libc/local/fcntl/posix_fadvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fadvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL posix_fadvise)(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length, __STDC_INT_AS_UINT_T __advise) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fadvise))(__fd, __offset, __length, __advise); })
#endif /* !... */
#if defined(__CRT_HAVE_posix_fallocate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fallocate,(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length),(__fd,__offset,__length))
#elif defined(__CRT_HAVE_posix_fallocate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fallocate,(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length),posix_fallocate64,(__fd,__offset,__length))
#else /* ... */
#include <libc/local/fcntl/posix_fallocate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fallocate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL posix_fallocate)(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fallocate))(__fd, __offset, __length); })
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_posix_fadvise) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fadvise64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length, __STDC_INT_AS_UINT_T __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise64)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fadvise64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length, __STDC_INT_AS_UINT_T __advise),(__fd,__offset,__length,__advise))
#else /* ... */
#include <libc/local/fcntl/posix_fadvise64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fadvise64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL posix_fadvise64)(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length, __STDC_INT_AS_UINT_T __advise) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fadvise64))(__fd, __offset, __length, __advise); })
#endif /* !... */
#if defined(__CRT_HAVE_posix_fallocate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fallocate64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),posix_fallocate,(__fd,__offset,__length))
#elif defined(__CRT_HAVE_posix_fallocate64)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,posix_fallocate64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),(__fd,__offset,__length))
#else /* ... */
#include <libc/local/fcntl/posix_fallocate64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fallocate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL posix_fallocate64)(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fallocate64))(__fd, __offset, __length); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#if !defined(F_ULOCK) && defined(__F_ULOCK)
#define F_ULOCK __F_ULOCK /* Unlock a previously locked region. */
#endif /* !F_ULOCK && __F_ULOCK */
#if !defined(F_LOCK) && defined(__F_LOCK)
#define F_LOCK  __F_LOCK  /* Lock a region for exclusive use. */
#endif /* !F_LOCK && __F_LOCK */
#if !defined(F_TLOCK) && defined(__F_TLOCK)
#define F_TLOCK __F_TLOCK /* Test and lock a region for exclusive use. */
#endif /* !F_TLOCK && __F_TLOCK */
#if !defined(F_TEST) && defined(__F_TEST)
#define F_TEST  __F_TEST  /* Test a region for other processes locks. */
#endif /* !F_TEST && __F_TEST */
#ifndef __lockf_defined
#define __lockf_defined
#if defined(__CRT_HAVE_lockf) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_RPC(__LIBCCALL lockf)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf_defined
#endif /* !... */
#endif /* !__lockf_defined */
#ifdef __USE_LARGEFILE64
#ifndef __lockf64_defined
#define __lockf64_defined
#if defined(__CRT_HAVE_lockf) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,lockf64,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64)
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_RPC,lockf64,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_RPC(__LIBCCALL lockf64)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf64))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf64_defined
#endif /* !... */
#endif /* !__lockf64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */

#ifdef __USE_SOLARIS
#ifdef __CRT_HAVE_directio
/* >> directio(3)
 * Enable or disable optional direct-I/O for  `fd'. Optional direct I/O behaves  the
 * same as mandatory direct I/O (s.a. `O_DIRECT'), but those cases where the  buffer
 * or file position/length provided in a call to `read(2)' or `write(2)' don't match
 * the requirements imposed by the  backing hardware (s.a. `FILE_IOC_BLKSHIFT')  are
 * handled  not by throwing an `E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*' exception,
 * but by falling back to doing non-direct I/O (as if `O_DIRECT') hasn't been set.
 *
 * Note that when optional direct-I/O is enabled, the O_DIRECT bit will also be set
 * for  the  given  `fd'  (in   addition  to  the  internal  `IO_OPTDIRECT'   bit).
 *
 * PORTABILITY WARNING: On OpenSolaris, this optional direct  I/O isn't used for file  ranges
 *                      of the given `fd' that have been mmap'd. This is NOT the case on KOS,
 *                      where direct I/O is always use if possible.
 *
 * @param: fd:   The file for which direct-I/O should be enabled/disabled
 * @param: mode: One of `DIRECTIO_*' from `<sys/fcntl.h>'
 * @return:  0: Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,directio,(__fd_t __fd, int __mode),(__fd,__mode))
#else /* __CRT_HAVE_directio */
#include <asm/os/file-ioctls.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__FIODIRECTIO)
#include <libc/local/fcntl/directio.h>
/* >> directio(3)
 * Enable or disable optional direct-I/O for  `fd'. Optional direct I/O behaves  the
 * same as mandatory direct I/O (s.a. `O_DIRECT'), but those cases where the  buffer
 * or file position/length provided in a call to `read(2)' or `write(2)' don't match
 * the requirements imposed by the  backing hardware (s.a. `FILE_IOC_BLKSHIFT')  are
 * handled  not by throwing an `E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*' exception,
 * but by falling back to doing non-direct I/O (as if `O_DIRECT') hasn't been set.
 *
 * Note that when optional direct-I/O is enabled, the O_DIRECT bit will also be set
 * for  the  given  `fd'  (in   addition  to  the  internal  `IO_OPTDIRECT'   bit).
 *
 * PORTABILITY WARNING: On OpenSolaris, this optional direct  I/O isn't used for file  ranges
 *                      of the given `fd' that have been mmap'd. This is NOT the case on KOS,
 *                      where direct I/O is always use if possible.
 *
 * @param: fd:   The file for which direct-I/O should be enabled/disabled
 * @param: mode: One of `DIRECTIO_*' from `<sys/fcntl.h>'
 * @return:  0: Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(directio, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL directio)(__fd_t __fd, int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(directio))(__fd, __mode); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __FIODIRECTIO */
#endif /* !__CRT_HAVE_directio */
#endif /* __USE_SOLARIS */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_FCNTL_H */
#endif /* __USE_UTF */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_FCNTL_H)
#include <parts/wchar/fcntl.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_FCNTL_H */
#endif /* __USE_KOS */

#endif /* !_FCNTL_H */
