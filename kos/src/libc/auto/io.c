/* HASH CRC-32:0x9ff362c3 */
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
#ifndef GUARD_LIBC_AUTO_IO_C
#define GUARD_LIBC_AUTO_IO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/io.h"
#include "../user/fcntl.h"
#include "../user/sys.stat.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) errno_t
NOTHROW_RPC(LIBDCALL libd__access_s)(char const *filename,
                                     __STDC_INT_AS_UINT_T type) {
	if (libd_access(filename, type) == 0)
		return 0;
	return __libd_geterrno_or(1);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) errno_t
NOTHROW_RPC(LIBCCALL libc__access_s)(char const *filename,
                                     __STDC_INT_AS_UINT_T type) {
	if (libc_access(filename, type) == 0)
		return EOK;
	return __libc_geterrno_or(1);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.property") ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc__umask_s)(mode_t nmode,
                                    mode_t *omode) {
	*omode = libc_umask(nmode);
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) oflag_t
NOTHROW_NCX(LIBCCALL libc__setmode)(fd_t fd,
                                    oflag_t mode) {

	return libc_fcntl(fd, __F_SETFL_XCH, mode);







}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBDCALL libd__sopen_s)(fd_t *fd,
                                    char const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    mode_t mode) {
	fd_t result;
	if (!fd) {

		return 22;



	}
	result = libd_sopen(filename, oflags, sflags, mode);
	if (result < 0)
		return __libd_geterrno_or(1);
	*fd = result;
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_IN(2) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc__sopen_s)(fd_t *fd,
                                    char const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    mode_t mode) {
	fd_t result;
	if (!fd) {

		return EINVAL;



	}
	result = libc_sopen(filename, oflags, sflags, mode);
	if (result < 0)
		return __libc_geterrno_or(1);
	*fd = result;
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t
NOTHROW_RPC(LIBDCALL libd__sopen_dispatch)(char const *filename,
                                           oflag_t oflags,
                                           int sflags,
                                           mode_t mode,
                                           fd_t *fd,
                                           int bsecure) {
	(void)bsecure;
	return libd__sopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t
NOTHROW_RPC(LIBCCALL libc__sopen_dispatch)(char const *filename,
                                           oflag_t oflags,
                                           int sflags,
                                           mode_t mode,
                                           fd_t *fd,
                                           int bsecure) {
	(void)bsecure;
	return libc__sopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2],
                                 uint32_t pipesize,
                                 oflag_t textmode) {
	(void)pipesize;
	return libc_pipe2(pipedes, textmode);
}
#include <asm/os/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_FDARG(1) int64_t
NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd) {
	int64_t oldpos, result;
	oldpos = libc_lseek64(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = libc_lseek64(fd, 0, __SEEK_END);
	if likely(result >= 0)
		libc_lseek64(fd, oldpos, __SEEK_SET);
	return result;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.basic_property") errno_t
NOTHROW_NCX(LIBDCALL libd_umask_s)(mode_t newmode,
                                   mode_t *oldmode) {
	if (!oldmode) {

		return 22;



	}
	*oldmode = libc_umask(newmode);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") errno_t
NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode,
                                   mode_t *oldmode) {
	if (!oldmode) {

		return EINVAL;



	}
	*oldmode = libc_umask(newmode);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_FDARG(1) int
NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-op */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_FDARG(1) void
NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* No-op */
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_PURE WUNUSED ATTR_FDARG(1) intptr_t
NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd) {
	COMPILER_IMPURE();
	return (intptr_t)fd;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd,
                                           oflag_t flags) {
	(void)flags;
	COMPILER_IMPURE();
	return (fd_t)osfd;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) fd_t
NOTHROW_RPC(VLIBDCALL libd_sopen)(char const *filename,
                                  oflag_t oflags,
                                  int sflags,
                                  ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = libd_open(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED ATTR_IN(1) fd_t
NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename,
                                  oflag_t oflags,
                                  int sflags,
                                  ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = libc_open(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_FDARG(1) __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc__filelength)(fd_t fd) {
	__LONG32_TYPE__ oldpos, result;
	oldpos = libc_lseek(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = libc_lseek(fd, 0, SEEK_END);
	if likely(result >= 0)
		libc_lseek(fd, oldpos, SEEK_SET);
	return result;
}
#include <asm/os/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc__eof)(fd_t fd) {
	int64_t oldpos, endpos;
	oldpos = libc_lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	endpos = libc_lseek64(fd, 0, SEEK_END);
	if likely(endpos >= 0) {
		if (endpos == oldpos)
			return 1;
		libc_lseek64(fd, oldpos, SEEK_SET);
	}
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$_access_s,libd__access_s,ATTR_IN(1),errno_t,NOTHROW_RPC,LIBDCALL,(char const *filename, __STDC_INT_AS_UINT_T type),(filename,type));
DEFINE_PUBLIC_ALIAS_P(_access_s,libc__access_s,ATTR_IN(1),errno_t,NOTHROW_RPC,LIBCCALL,(char const *filename, __STDC_INT_AS_UINT_T type),(filename,type));
DEFINE_PUBLIC_ALIAS_P(_umask_s,libc__umask_s,ATTR_OUT(2),errno_t,NOTHROW_NCX,LIBCCALL,(mode_t nmode, mode_t *omode),(nmode,omode));
DEFINE_PUBLIC_ALIAS_P(_setmode,libc__setmode,ATTR_FDARG(1),oflag_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, oflag_t mode),(fd,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$_sopen_s_nolock,libd__sopen_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBDCALL,(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode),(fd,filename,oflags,sflags,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$_sopen_s,libd__sopen_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBDCALL,(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode),(fd,filename,oflags,sflags,mode));
DEFINE_PUBLIC_ALIAS_P(_sopen_s_nolock,libc__sopen_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBCCALL,(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode),(fd,filename,oflags,sflags,mode));
DEFINE_PUBLIC_ALIAS_P(_sopen_s,libc__sopen_s,ATTR_IN(2) ATTR_OUT(1),errno_t,NOTHROW_RPC,LIBCCALL,(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode),(fd,filename,oflags,sflags,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$_sopen_dispatch,libd__sopen_dispatch,WUNUSED ATTR_IN(1) ATTR_OUT(5),errno_t,NOTHROW_RPC,LIBDCALL,(char const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure),(filename,oflags,sflags,mode,fd,bsecure));
DEFINE_PUBLIC_ALIAS_P(_sopen_dispatch,libc__sopen_dispatch,WUNUSED ATTR_IN(1) ATTR_OUT(5),errno_t,NOTHROW_RPC,LIBCCALL,(char const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure),(filename,oflags,sflags,mode,fd,bsecure));
DEFINE_PUBLIC_ALIAS_P(_pipe,libc__pipe,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode),(pipedes,pipesize,textmode));
DEFINE_PUBLIC_ALIAS_P(_filelengthi64,libc__filelengthi64,WUNUSED ATTR_FDARG(1),int64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(DOS$umask_s,libd_umask_s,,errno_t,NOTHROW_NCX,LIBDCALL,(mode_t newmode, mode_t *oldmode),(newmode,oldmode));
DEFINE_PUBLIC_ALIAS_P(umask_s,libc_umask_s,,errno_t,NOTHROW_NCX,LIBCCALL,(mode_t newmode, mode_t *oldmode),(newmode,oldmode));
DEFINE_PUBLIC_ALIAS_P(__lock_fhandle,libc___lock_fhandle,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P_VOID(_unlock_fhandle,libc__unlock_fhandle,ATTR_FDARG(1),NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(_get_osfhandle,libc__get_osfhandle,ATTR_PURE WUNUSED ATTR_FDARG(1),intptr_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(_open_osfhandle,libc__open_osfhandle,WUNUSED,fd_t,NOTHROW_NCX,LIBCCALL,(intptr_t osfd, oflag_t flags),(osfd,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$_sopen,libd_sopen,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, int sflags, ...),(filename,oflags,sflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$sopen,libd_sopen,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, int sflags, ...),(filename,oflags,sflags,));
DEFINE_PUBLIC_ALIAS_P(sopen,libc_sopen,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, int sflags, ...),(filename,oflags,sflags,));
DEFINE_PUBLIC_ALIAS_P(_filelength,libc__filelength,WUNUSED ATTR_FDARG(1),__LONG32_TYPE__,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(_eof,libc__eof,WUNUSED ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_IO_C */
