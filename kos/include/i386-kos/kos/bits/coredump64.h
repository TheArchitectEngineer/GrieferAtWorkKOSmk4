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
/*!replace_with_include <kos/coredump.h>*/
#ifndef _I386_KOS_KOS_BITS_COREDUMP64_H
#define _I386_KOS_KOS_BITS_COREDUMP64_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/kos/siginfo64.h>
#include <kos/bits/exception_data64.h>

#ifdef __x86_64__
#define coredump_assert64 coredump_assert
#define coredump_info64   coredump_info
#endif /* __x86_64__ */

#ifdef __CC__
__DECL_BEGIN

struct coredump_assert64 {
	__HYBRID_PTR64(char const) ca_expr; /* [0..1] Faulting expression    (`#expr') */
	__HYBRID_PTR64(char const) ca_file; /* [0..1] Faulting file name     (`__FILE__') */
	__ULONG64_TYPE__           ca_line; /* Faulting line number (or `0') (`__LINE__') */
	__HYBRID_PTR64(char const) ca_func; /* [0..1] Faulting function name (`__func__') */
	__HYBRID_PTR64(char const) ca_mesg; /* [0..1] Assert message         (`sprintf(...)'; for `assertf(expr, ...)') */
};

/* Optional argument for additional information passed to `sys_coredump(2)'
 * via the `exception' argument. Depending on `unwind_error', this can be a
 * number of things relating to what caused  the error, and can be used  to
 * affect  the behavior of how the kernel will handle the fault, as well as
 * how/if the system call returns (because normally it doesn't). */
union coredump_info64 {
	struct __exception_data64  ci_except;     /* [unwind_error = *]                   Exception data. */
	struct __siginfox64_struct ci_signal;     /* [unwind_error = UNWIND_SUCCESS]      Signal information. */
	char                       ci_dlerror[1]; /* [unwind_error = UNWIND_USER_DLERROR] dlerror() error message. */
	char                       ci_abrtmsg[1]; /* [unwind_error = UNWIND_USER_ABORT]   abortf() error message. */
	struct coredump_assert64   ci_assert;     /* [unwind_error = UNWIND_USER_ASSERT]  Assert info.
	                                           * [unwind_error = UNWIND_USER_ACHECK]  *ditto* */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_COREDUMP64_H */
