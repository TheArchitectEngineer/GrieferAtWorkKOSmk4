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
%(c_prefix){
/* (#) Portability: OpenSolaris (/usr/src/head/siginfo.h) */
}

%[default:section(".text.crt{|.dos}.solaris")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/siginfo.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

}%[push_macro @undef { siginfolist, nsiginfo, vsiginfo }]%{

struct siginfolist {
	int    nsiginfo;
	char **vsiginfo;
};

/* For compatibility with OpenSolaris
 *
 * Note that on KOS, these same strings can (and should) instead be
 * accessed  through `sigcodedesc_np(3)', as declared in <signal.h>
 *
 * Portability notes:
 * >> _sys_siginfolist[signo-1].vsiginfo[code-1] == sigcodedesc_np(signo, code);
 * >> _sys_siginfolist[SIGILL-1].vsiginfo        == _sys_illlist;
 * >> _sys_siginfolist[SIGFPE-1].vsiginfo        == _sys_fpelist;
 * >> _sys_siginfolist[SIGSEGV-1].vsiginfo       == _sys_segvlist;
 * >> _sys_siginfolist[SIGBUS-1].vsiginfo        == _sys_buslist;
 * >> _sys_siginfolist[SIGTRAP-1].vsiginfo       == _sys_traplist;
 * >> _sys_siginfolist[SIGCLD-1].vsiginfo        == _sys_cldlist;
 * >> _sys_siginfolist[SIGPOLL-1].vsiginfo       == _sys_polllist;
 */

#ifndef _sys_illlist
#ifdef __CRT_HAVE__sys_illlist
extern char const *_sys_illlist[];
#define _sys_illlist _sys_illlist
#endif /* __CRT_HAVE__sys_illlist */
#endif /* !_sys_illlist */

#ifndef _sys_fpelist
#ifdef __CRT_HAVE__sys_fpelist
extern char const *_sys_fpelist[];
#define _sys_fpelist _sys_fpelist
#endif /* __CRT_HAVE__sys_fpelist */
#endif /* !_sys_fpelist */

#ifndef _sys_segvlist
#ifdef __CRT_HAVE__sys_segvlist
extern char const *_sys_segvlist[];
#define _sys_segvlist _sys_segvlist
#endif /* __CRT_HAVE__sys_segvlist */
#endif /* !_sys_segvlist */

#ifndef _sys_buslist
#ifdef __CRT_HAVE__sys_buslist
extern char const *_sys_buslist[];
#define _sys_buslist _sys_buslist
#endif /* __CRT_HAVE__sys_buslist */
#endif /* !_sys_buslist */

#ifndef _sys_traplist
#ifdef __CRT_HAVE__sys_traplist
extern char const *_sys_traplist[];
#define _sys_traplist _sys_traplist
#endif /* __CRT_HAVE__sys_traplist */
#endif /* !_sys_traplist */

#ifndef _sys_cldlist
#ifdef __CRT_HAVE__sys_cldlist
extern char const *_sys_cldlist[];
#define _sys_cldlist _sys_cldlist
#endif /* __CRT_HAVE__sys_cldlist */
#endif /* !_sys_cldlist */

#ifndef _sys_polllist
#ifdef __CRT_HAVE__sys_polllist
extern char const *_sys_polllist[];
#define _sys_polllist _sys_polllist
#endif /* __CRT_HAVE__sys_polllist */
#endif /* !_sys_polllist */

#ifndef _sys_siginfolistp
#ifdef __CRT_HAVE__sys_siginfolistp
extern struct siginfolist const *_sys_siginfolistp;
#define _sys_siginfolistp _sys_siginfolistp
#endif /* __CRT_HAVE__sys_siginfolistp */
#endif /* !_sys_siginfolistp */

#if !defined(_sys_siginfolist) && defined(_sys_siginfolistp)
#define _sys_siginfolist _sys_siginfolistp
#endif /* !_sys_siginfolist && _sys_siginfolistp */

}%[pop_macro]%{
}

%[insert:extern(psignal)]
%[insert:extern(psiginfo)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
