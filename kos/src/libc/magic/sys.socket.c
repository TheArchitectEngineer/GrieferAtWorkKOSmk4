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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t   = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(__SOCKADDR_ARG       = struct sockaddr *__restrict)]
%[define_replacement(__CONST_SOCKADDR_ARG = struct sockaddr const *__restrict)]
%[default_impl_section(.text.crt.net.socket)]

%{
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/socket.h>
#include <bits/timespec.h>
#include <bits/types.h>
#include <sys/uio.h>

#ifdef __USE_GNU
#include <bits/mmsghdr-struct.h>
#include <bits/sigset.h>
#endif /* __USE_GNU */

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/socket.h */
/* Declarations of socket constants, types, and functions.
   Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

#ifndef SHUT_RD
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SHUT_RD   = 0, /* No more receptions. */
	SHUT_WR   = 1, /* No more transmissions. */
	SHUT_RDWR = 2  /* No more receptions or transmissions. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SHUT_RD   SHUT_RD   /* No more receptions. */
#define SHUT_WR   SHUT_WR   /* No more transmissions. */
#define SHUT_RDWR SHUT_RDWR /* No more receptions or transmissions. */
#else /* __COMPILER_PREFERR_ENUMS */
#define SHUT_RD   0 /* No more receptions. */
#define SHUT_WR   1 /* No more transmissions. */
#define SHUT_RDWR 2 /* No more receptions or transmissions. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !SHUT_RD */


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifdef __USE_MISC
#ifndef __osockaddr_defined
#define __osockaddr_defined 1
struct osockaddr {
	__UINT16_TYPE__ sa_family;
	__UINT8_TYPE__  sa_data[14];
};
#endif /* !__osockaddr_defined */
#endif /* __USE_MISC */


#if (defined(__cplusplus) || !defined(__USE_GNU) || \
     defined(__NO_ATTR_TRANSPARENT_UNION))
#define __SOCKADDR_ARG       struct sockaddr *__restrict
#define __CONST_SOCKADDR_ARG struct sockaddr const *__restrict
#else /* __cplusplus || !__USE_GNU || __NO_ATTR_TRANSPARENT_UNION */
#define __SOCKADDR_ALLTYPES            \
	__SOCKADDR_ONETYPE(sockaddr)       \
	__SOCKADDR_ONETYPE(sockaddr_at)    \
	__SOCKADDR_ONETYPE(sockaddr_ax25)  \
	__SOCKADDR_ONETYPE(sockaddr_dl)    \
	__SOCKADDR_ONETYPE(sockaddr_eon)   \
	__SOCKADDR_ONETYPE(sockaddr_in)    \
	__SOCKADDR_ONETYPE(sockaddr_in6)   \
	__SOCKADDR_ONETYPE(sockaddr_inarp) \
	__SOCKADDR_ONETYPE(sockaddr_ipx)   \
	__SOCKADDR_ONETYPE(sockaddr_iso)   \
	__SOCKADDR_ONETYPE(sockaddr_ns)    \
	__SOCKADDR_ONETYPE(sockaddr_un)    \
	__SOCKADDR_ONETYPE(sockaddr_x25)
#ifdef __cplusplus
#define __SOCKADDR_ONETYPE(type) struct type;
__SOCKADDR_ALLTYPES
#undef __SOCKADDR_ONETYPE
#endif /* __cplusplus */
#define __SOCKADDR_ONETYPE(type) struct type *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#define __SOCKADDR_ONETYPE(type) struct type const *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES } __CONST_SOCKADDR_ARG __ATTR_TRANSPARENT_UNION;
#undef __SOCKADDR_ONETYPE
#endif /* !__cplusplus && __USE_GNU && !__NO_ATTR_TRANSPARENT_UNION */

}


@@Create a new socket of type TYPE in domain FAMILY, using
@@protocol PROTOCOL. If PROTOCOL is zero, one is chosen automatically.
@@Returns a file descriptor for the new socket, or -1 for errors
@@@param: family:   Socket address family (one of `AF_*' from `<asm/socket-families.h>')
@@@param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
@@                  May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
@@@param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
@@                  depend on the selected `family', and may be further specialized by the
@@                  `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
@@                  >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
@@                  Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
[ATTR_WUNUSED][export_alias(__socket)]
socket:(__STDC_INT_AS_UINT_T family, __STDC_INT_AS_UINT_T type,
        __STDC_INT_AS_UINT_T protocol) -> $fd_t;

@@Create two new sockets, of type TYPE in domain FAMILY and using
@@protocol PROTOCOL, which are connected to each other, and put file
@@descriptors for them in FDS[0] and FDS[1].  If PROTOCOL is zero,
@@one will be chosen automatically.  Returns 0 on success, -1 for errors
@@@param: family:   Socket address family (one of `AF_*' from `<asm/socket-families.h>')
@@@param: type:     Socket type (one of `SOCK_*' from `<bits/socket_type.h>')
@@                  May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
@@@param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
@@                  depend on the selected `family', and may be further specialized by the
@@                  `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
@@                  >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
@@                  Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
socketpair:(__STDC_INT_AS_UINT_T family, __STDC_INT_AS_UINT_T type,
            __STDC_INT_AS_UINT_T protocol, [[nonnull]] $fd_t fds[2]) -> int;

@@Give the socket FD the local address ADDR (which is LEN bytes long)
bind:($fd_t sockfd, [inp(addr_len)] __CONST_SOCKADDR_ARG addr,
      socklen_t addr_len) -> int;

@@Put the local address of FD into *ADDR and its length in *LEN
getsockname:($fd_t sockfd, [outp(*addr_len)] __SOCKADDR_ARG addr,
             socklen_t *__restrict addr_len) -> int;

@@Open a connection on socket FD to peer at ADDR (which LEN bytes long).
@@For connectionless socket types, just set the default address to send to
@@and the only address from which to accept transmissions.
@@Return 0 on success, -1 for errors
[[cp]][export_alias(__connect)]
connect:($fd_t sockfd, [inp(addr_len)] __CONST_SOCKADDR_ARG addr,
         socklen_t addr_len) -> int;

@@Put the address of the peer connected to socket FD into *ADDR
@@(which is *LEN bytes long), and its actual length into *LEN
getpeername:($fd_t sockfd, [outp(*addr_len)] __SOCKADDR_ARG addr,
             socklen_t *__restrict addr_len) -> int;

@@Send BUFSIZE bytes of BUF to socket FD.  Returns the number sent or -1
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
[[cp]][export_alias(__send)]
send:($fd_t sockfd, [inp(bufsize)] void const *buf,
      size_t bufsize, __STDC_INT_AS_UINT_T msg_flags) -> ssize_t;

@@Read BUFSIZE bytes into BUF from socket FD.
@@Returns the number read or -1 for errors
@@@param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
[[cp]][ATTR_WUNUSED][export_alias(__recv)]
recv:($fd_t sockfd, [[outp(bufsize)]] void *buf, size_t bufsize,
      __STDC_INT_AS_UINT_T msg_flags) -> ssize_t;

@@Send BUFSIZE bytes of BUF on socket FD to peer at address ADDR
@@(which is ADDR_LEN bytes long). Returns the number sent, or -1 for errors.
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
[[cp]]
sendto:($fd_t sockfd, [inp(bufsize)] void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
        [inp_opt(addr_len)] __CONST_SOCKADDR_ARG addr, socklen_t addr_len) -> ssize_t;

@@Read BUFSIZE bytes into BUF through socket FD.
@@If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
@@the sender, and store the actual size of the address in *ADDR_LEN.
@@Returns the number of bytes read or -1 for errors
@@@param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
[[cp]][ATTR_WUNUSED]
recvfrom:($fd_t sockfd, [[outp(bufsize)]] void *__restrict buf, size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
          [outp_opt(*addr_len)] __SOCKADDR_ARG addr, [[nullable]] socklen_t *__restrict addr_len) -> ssize_t;

@@Send a message described MESSAGE on socket FD.
@@Returns the number of bytes sent, or -1 for errors
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
[[cp]]
sendmsg:($fd_t sockfd, [[nonnull]] struct msghdr const *message,
         __STDC_INT_AS_UINT_T msg_flags) -> ssize_t;

@@Receive a message as described by MESSAGE from socket FD.
@@Returns the number of bytes read or -1 for errors.
@@@param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
@@                           MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
[[cp]][ATTR_WUNUSED]
recvmsg:($fd_t sockfd, [[nonnull]] struct msghdr *message,
         __STDC_INT_AS_UINT_T msg_flags) -> ssize_t;

@@Put the current value for socket FD's option OPTNAME at protocol level LEVEL
@@into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
@@actual length.  Returns 0 on success, -1 for errors
@@@param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
@@@param: optname: Dependent on `level'
getsockopt:($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
            [outp(*optlen)] void *__restrict optval, socklen_t *__restrict optlen) -> int;

@@Set socket FD's option OPTNAME at protocol level LEVEL to *OPTVAL
@@(which is OPTLEN bytes long). Returns 0 on success, -1 for errors
@@@param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
@@@param: optname: Dependent on `level'
setsockopt:($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
            [inp(optlen)] void const *optval, socklen_t optlen) -> int;

@@Prepare to accept connections on socket FD.
@@`MAX_BACKLOG' connection requests will be queued before further
@@requests are refused. Returns 0 on success, -1 for errors
listen:($fd_t sockfd, __STDC_INT_AS_UINT_T max_backlog) -> int;

@@Await a connection on socket FD.
@@When a connection arrives, open a new socket to communicate with it,
@@set *ADDR (which is *ADDR_LEN bytes long) to the address of the
@@connecting peer and *ADDR_LEN to the address's actual length, and
@@return the new socket's descriptor, or -1 for errors
[[cp]]
accept:($fd_t sockfd, [outp(*addr_len)] __SOCKADDR_ARG addr,
        socklen_t *__restrict addr_len) -> $fd_t;

@@Shut down all or part of the connection open on socket FD.
@@HOW determines what to shut down:
@@    - SHUT_RD   = No more receptions;
@@    - SHUT_WR   = No more transmissions;
@@    - SHUT_RDWR = No more receptions or transmissions.
@@Returns 0 on success, -1 for errors
shutdown:($fd_t sockfd, __STDC_INT_AS_UINT_T how) -> int;

%
%#ifdef __USE_GNU
@@Similar to 'accept(2)' but takes an additional parameter to specify socket flags.
@@@param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
[[cp]]
accept4:($fd_t sockfd, [outp(*addr_len)] __SOCKADDR_ARG addr,
         socklen_t *__restrict addr_len, __STDC_INT_AS_UINT_T sock_flags) -> $fd_t;

@@Send a VLEN messages as described by VMESSAGES to socket FD.
@@Returns the number of datagrams successfully written or -1 for errors
@@@param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
@@                           MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
[[cp]][export_alias(__sendmmsg)]
sendmmsg:($fd_t sockfd, [[nonnull]] struct mmsghdr *vmessages,
          __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags) -> int;

@@@param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
@@                           MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
[[cp]][ignore][doc_alias(recvmmsg)]
recvmmsg32:($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
            __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
            [[nullable]] struct $timespec32 *tmo) = recvmmsg?;

@@Receive up to VLEN messages as described by VMESSAGES from socket FD.
@@Returns the number of messages received or -1 for errors.
@@@param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
@@                           MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
@@                           MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
[cp, no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(recvmmsg64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(recvmmsg)]
[requires(defined(__CRT_HAVE_recvmmsg) || defined(__CRT_HAVE_recvmmsg64))]
recvmmsg:($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
          __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
          [[nullable]] struct timespec *tmo) -> int {
#ifdef __CRT_HAVE_recvmmsg64
	struct timespec64 tmo64;
	if (!tmo)
		return recvmmsg64(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time64_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg64(sockfd, vmessages, vlen, msg_flags, &tmo64);
#else /* __CRT_HAVE_recvmmsg64 */
	struct timespec32 tmo32;
	if (!tmo)
		return recvmmsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
#endif /* !__CRT_HAVE_recvmmsg64 */
}

%#ifdef __USE_TIME64
[[cp]][requires($has_function(recvmmsg32))][time64_variant_of(recvmmsg)]
recvmmsg64:($fd_t sockfd, [inp(vlen)] struct mmsghdr *vmessages,
            __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
            [[nullable]] struct $timespec64 *tmo) -> int {
	struct timespec32 tmo32;
	if (!tmo)
		return recvmmsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return recvmmsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K
@@Determine whether socket is at a out-of-band mark
@@@return: > 0 : The read-pointer is pointing at out-of-band data
@@@return: == 0: The read-pointer is not pointing at out-of-band data
@@@return: < 0 : Error (s.a. `errno')
[ATTR_WUNUSED] sockatmark:($fd_t sockfd) -> int;
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_MISC
@@FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
@@returns 1 if FD is open on an object of the indicated
@@type, 0 if not, or -1 for errors (setting errno)
@@@param: fdtype: One of `S_IF*' from `<sys/stat.h>'
[ATTR_WUNUSED] isfdtype:($fd_t fd, __STDC_INT_AS_UINT_T fdtype) -> int;
%#endif /* __USE_MISC */

%{
#endif /* __CC__ */

__SYSDECL_END

}