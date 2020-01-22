/* HASH CRC-32:0xa91f12df */
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
#ifndef _PTHREAD_H
#define _PTHREAD_H 1

#include "__stdinc.h"
#include "__crt.h"
#include <kos/anno.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <endian.h>
#include <sched.h>
#include <time.h>

#include <bits/pthreadtypes.h>
#include <bits/pthreadvalues.h>
#include <bits/pthreadinit.h>
#include <bits/setjmp.h>
#include <bits/wordsize.h>

__SYSDECL_BEGIN

/* Comments and definitions are derived from GNU C /usr/include/pthread.h: */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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


/* Detach state. */
#undef PTHREAD_CREATE_JOINABLE
#undef PTHREAD_CREATE_DETACHED
#ifdef __CC__
enum {
	PTHREAD_CREATE_JOINABLE = __PTHREAD_CREATE_JOINABLE,
	PTHREAD_CREATE_DETACHED = __PTHREAD_CREATE_DETACHED
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_JOINABLE
#define PTHREAD_CREATE_DETACHED PTHREAD_CREATE_DETACHED
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_CREATE_JOINABLE __PTHREAD_CREATE_JOINABLE
#define PTHREAD_CREATE_DETACHED __PTHREAD_CREATE_DETACHED
#endif /* !__COMPILER_PREFERR_ENUMS */

/* Mutex types. */
#undef PTHREAD_MUTEX_TIMED_NP
#undef PTHREAD_MUTEX_RECURSIVE_NP
#undef PTHREAD_MUTEX_ERRORCHECK_NP
#undef PTHREAD_MUTEX_ADAPTIVE_NP
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#undef PTHREAD_MUTEX_NORMAL
#undef PTHREAD_MUTEX_RECURSIVE
#undef PTHREAD_MUTEX_ERRORCHECK
#undef PTHREAD_MUTEX_DEFAULT
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#undef PTHREAD_MUTEX_FAST_NP
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#undef PTHREAD_MUTEX_STALLED
#undef PTHREAD_MUTEX_ROBUST
#undef PTHREAD_MUTEX_STALLED_NP
#undef PTHREAD_MUTEX_ROBUST_NP
#endif /* __USE_XOPEN2K */
#ifdef __CC__
enum {
	PTHREAD_MUTEX_TIMED_NP      = __PTHREAD_MUTEX_TIMED,
	PTHREAD_MUTEX_RECURSIVE_NP  = __PTHREAD_MUTEX_RECURSIVE,
	PTHREAD_MUTEX_ERRORCHECK_NP = __PTHREAD_MUTEX_ERRORCHECK,
	PTHREAD_MUTEX_ADAPTIVE_NP   = __PTHREAD_MUTEX_ADAPTIVE,
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
	PTHREAD_MUTEX_NORMAL        = __PTHREAD_MUTEX_TIMED,
	PTHREAD_MUTEX_RECURSIVE     = __PTHREAD_MUTEX_RECURSIVE,
	PTHREAD_MUTEX_ERRORCHECK    = __PTHREAD_MUTEX_ERRORCHECK,
	PTHREAD_MUTEX_DEFAULT       = PTHREAD_MUTEX_NORMAL,
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
	PTHREAD_MUTEX_FAST_NP       = __PTHREAD_MUTEX_TIMED,      /* For compatibility. */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
	PTHREAD_MUTEX_STALLED       = __PTHREAD_MUTEX_STALLED,    /* Robust mutex or not flags. */
	PTHREAD_MUTEX_ROBUST        = __PTHREAD_MUTEX_ROBUST,     /* ... */
	PTHREAD_MUTEX_STALLED_NP    = __PTHREAD_MUTEX_STALLED,    /* ... */
	PTHREAD_MUTEX_ROBUST_NP     = __PTHREAD_MUTEX_ROBUST     /* ... */
#endif /* __USE_XOPEN2K */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_MUTEX_TIMED_NP      PTHREAD_MUTEX_TIMED_NP
#define PTHREAD_MUTEX_RECURSIVE_NP  PTHREAD_MUTEX_RECURSIVE_NP
#define PTHREAD_MUTEX_ERRORCHECK_NP PTHREAD_MUTEX_ERRORCHECK_NP
#define PTHREAD_MUTEX_ADAPTIVE_NP   PTHREAD_MUTEX_ADAPTIVE_NP
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#define PTHREAD_MUTEX_NORMAL        PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_RECURSIVE     PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK    PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_DEFAULT       PTHREAD_MUTEX_DEFAULT
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#define PTHREAD_MUTEX_FAST_NP       PTHREAD_MUTEX_FAST_NP       /* For compatibility. */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#define PTHREAD_MUTEX_STALLED       PTHREAD_MUTEX_STALLED       /* Robust mutex or not flags. */
#define PTHREAD_MUTEX_ROBUST        PTHREAD_MUTEX_ROBUST        /* ... */
#define PTHREAD_MUTEX_STALLED_NP    PTHREAD_MUTEX_STALLED_NP    /* ... */
#define PTHREAD_MUTEX_ROBUST_NP     PTHREAD_MUTEX_ROBUST_NP     /* ... */
#endif /* __USE_XOPEN2K */
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_MUTEX_TIMED_NP      __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_RECURSIVE_NP  __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK_NP __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ADAPTIVE_NP   __PTHREAD_MUTEX_ADAPTIVE
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#define PTHREAD_MUTEX_NORMAL        __PTHREAD_MUTEX_TIMED
#define PTHREAD_MUTEX_RECURSIVE     __PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK    __PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_DEFAULT       PTHREAD_MUTEX_NORMAL
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_GNU
#define PTHREAD_MUTEX_FAST_NP       __PTHREAD_MUTEX_TIMED      /* For compatibility. */
#endif /* __USE_GNU */
#ifdef __USE_XOPEN2K
#define PTHREAD_MUTEX_STALLED       __PTHREAD_MUTEX_STALLED    /* Robust mutex or not flags. */
#define PTHREAD_MUTEX_ROBUST        __PTHREAD_MUTEX_ROBUST     /* ... */
#define PTHREAD_MUTEX_STALLED_NP    __PTHREAD_MUTEX_STALLED    /* ... */
#define PTHREAD_MUTEX_ROBUST_NP     __PTHREAD_MUTEX_ROBUST     /* ... */
#endif /* __USE_XOPEN2K */
#endif /* !__COMPILER_PREFERR_ENUMS */


#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
/* Mutex protocols. */
#undef PTHREAD_PRIO_NONE
#undef PTHREAD_PRIO_INHERIT
#undef PTHREAD_PRIO_PROTECT
#ifdef __CC__
enum {
	PTHREAD_PRIO_NONE    = __PTHREAD_PRIO_NONE,
	PTHREAD_PRIO_INHERIT = __PTHREAD_PRIO_INHERIT,
	PTHREAD_PRIO_PROTECT = __PTHREAD_PRIO_PROTECT
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_PRIO_NONE    PTHREAD_PRIO_NONE
#define PTHREAD_PRIO_INHERIT PTHREAD_PRIO_INHERIT
#define PTHREAD_PRIO_PROTECT PTHREAD_PRIO_PROTECT
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_PRIO_NONE    __PTHREAD_PRIO_NONE
#define PTHREAD_PRIO_INHERIT __PTHREAD_PRIO_INHERIT
#define PTHREAD_PRIO_PROTECT __PTHREAD_PRIO_PROTECT
#endif /* !__COMPILER_PREFERR_ENUMS */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

/* Read-write lock types. */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#undef PTHREAD_RWLOCK_PREFER_READER_NP
#undef PTHREAD_RWLOCK_PREFER_WRITER_NP
#undef PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP
#undef PTHREAD_RWLOCK_DEFAULT_NP
#ifdef __CC__
enum {
	PTHREAD_RWLOCK_PREFER_READER_NP              = __PTHREAD_RWLOCK_PREFER_READER,
	PTHREAD_RWLOCK_PREFER_WRITER_NP              = __PTHREAD_RWLOCK_PREFER_WRITER,
	PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP = __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE,
	PTHREAD_RWLOCK_DEFAULT_NP                    = __PTHREAD_RWLOCK_PREFER_READER
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_RWLOCK_PREFER_READER_NP              PTHREAD_RWLOCK_PREFER_READER_NP
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              PTHREAD_RWLOCK_PREFER_WRITER_NP
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP
#define PTHREAD_RWLOCK_DEFAULT_NP                    PTHREAD_RWLOCK_DEFAULT_NP
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_RWLOCK_PREFER_READER_NP              __PTHREAD_RWLOCK_PREFER_READER
#define PTHREAD_RWLOCK_PREFER_WRITER_NP              __PTHREAD_RWLOCK_PREFER_WRITER
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE
#define PTHREAD_RWLOCK_DEFAULT_NP                    __PTHREAD_RWLOCK_PREFER_READER
#endif /* !__COMPILER_PREFERR_ENUMS */
#endif  /* __USE_UNIX98 || __USE_XOPEN2K */

/* Scheduler inheritance. */
#undef PTHREAD_INHERIT_SCHED
#undef PTHREAD_EXPLICIT_SCHED
#ifdef __CC__
enum {
	PTHREAD_INHERIT_SCHED  = __PTHREAD_INHERIT_SCHED,
	PTHREAD_EXPLICIT_SCHED = __PTHREAD_EXPLICIT_SCHED
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_INHERIT_SCHED  PTHREAD_INHERIT_SCHED
#define PTHREAD_EXPLICIT_SCHED PTHREAD_EXPLICIT_SCHED
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_INHERIT_SCHED  __PTHREAD_INHERIT_SCHED
#define PTHREAD_EXPLICIT_SCHED __PTHREAD_EXPLICIT_SCHED
#endif /* !__COMPILER_PREFERR_ENUMS */

/* Scope handling. */
#undef PTHREAD_SCOPE_SYSTEM
#undef PTHREAD_SCOPE_PROCESS
#ifdef __CC__
enum {
	PTHREAD_SCOPE_SYSTEM  = __PTHREAD_SCOPE_SYSTEM,
	PTHREAD_SCOPE_PROCESS = __PTHREAD_SCOPE_PROCESS
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_SCOPE_SYSTEM  PTHREAD_SCOPE_SYSTEM
#define PTHREAD_SCOPE_PROCESS PTHREAD_SCOPE_PROCESS
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_SCOPE_SYSTEM  __PTHREAD_SCOPE_SYSTEM
#define PTHREAD_SCOPE_PROCESS __PTHREAD_SCOPE_PROCESS
#endif /* !__COMPILER_PREFERR_ENUMS */

/* Process shared or private flag. */
#undef PTHREAD_PROCESS_PRIVATE
#undef PTHREAD_PROCESS_SHARED
#ifdef __CC__
enum {
	PTHREAD_PROCESS_PRIVATE = __PTHREAD_PROCESS_PRIVATE,
	PTHREAD_PROCESS_SHARED  = __PTHREAD_PROCESS_SHARED
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_PROCESS_PRIVATE PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_SHARED  PTHREAD_PROCESS_SHARED
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_PROCESS_PRIVATE __PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_SHARED  __PTHREAD_PROCESS_SHARED
#endif /* !__COMPILER_PREFERR_ENUMS */

/* Cancellation */
#undef PTHREAD_CANCEL_ENABLE
#undef PTHREAD_CANCEL_DISABLE
#undef PTHREAD_CANCEL_DEFERRED
#undef PTHREAD_CANCEL_ASYNCHRONOUS
#ifdef __CC__
enum {
	PTHREAD_CANCEL_ENABLE       = __PTHREAD_CANCEL_ENABLE,
	PTHREAD_CANCEL_DISABLE      = __PTHREAD_CANCEL_DISABLE,
	PTHREAD_CANCEL_DEFERRED     = __PTHREAD_CANCEL_DEFERRED,
	PTHREAD_CANCEL_ASYNCHRONOUS = __PTHREAD_CANCEL_ASYNCHRONOUS
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define PTHREAD_CANCEL_ENABLE       PTHREAD_CANCEL_ENABLE
#define PTHREAD_CANCEL_DISABLE      PTHREAD_CANCEL_DISABLE
#define PTHREAD_CANCEL_DEFERRED     PTHREAD_CANCEL_DEFERRED
#define PTHREAD_CANCEL_ASYNCHRONOUS PTHREAD_CANCEL_ASYNCHRONOUS
#else /* __COMPILER_PREFERR_ENUMS */
#define PTHREAD_CANCEL_ENABLE       __PTHREAD_CANCEL_ENABLE
#define PTHREAD_CANCEL_DISABLE      __PTHREAD_CANCEL_DISABLE
#define PTHREAD_CANCEL_DEFERRED     __PTHREAD_CANCEL_DEFERRED
#define PTHREAD_CANCEL_ASYNCHRONOUS __PTHREAD_CANCEL_ASYNCHRONOUS
#endif /* !__COMPILER_PREFERR_ENUMS */
#define PTHREAD_CANCELED __PTHREAD_CANCELED

/* Single execution handling. */
#define PTHREAD_ONCE_INIT __PTHREAD_ONCE_INIT

#ifdef __USE_XOPEN2K
/* Value returned by 'pthread_barrier_wait' for one of the threads
 * after the required number of threads have called this function.
 * -1 is distinct from 0 and all errno constants */
#define PTHREAD_BARRIER_SERIAL_THREAD __PTHREAD_BARRIER_SERIAL_THREAD
#endif /* __USE_XOPEN2K */



#ifdef __CC__

#define PTHREAD_MUTEX_INITIALIZER               __PTHREAD_MUTEX_INITIALIZER
#ifdef __USE_GNU
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP  __PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER
#define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP   __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER
#endif /* __USE_GNU */

/* Read-write lock types. */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)

/* Read-write lock initializers. */
#define PTHREAD_RWLOCK_INITIALIZER __PTHREAD_RWLOCK_INITIALIZER
#ifdef __USE_GNU
#define PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER
#endif /* __USE_GNU */
#endif  /* __USE_UNIX98 || __USE_XOPEN2K */

/* Conditional variable handling. */
#define PTHREAD_COND_INITIALIZER __PTHREAD_COND_INITIALIZER

/* Cleanup buffers */
struct _pthread_cleanup_buffer {
	void                          (*__routine)(void *); /* Function to call. */
	void                           *__arg;              /* Its argument. */
	int                             __canceltype;       /* Saved cancellation type. */
	struct _pthread_cleanup_buffer *__prev;             /* Chaining of cleanup functions. */
};

#ifndef ____pthread_start_routine_t_defined
#define ____pthread_start_routine_t_defined 1
typedef void *(*__pthread_start_routine_t)(void *);
#endif /* !____pthread_start_routine_t_defined */

typedef __pthread_t pthread_t;
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef __pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
typedef __pthread_mutex_t pthread_mutex_t;
typedef __pthread_mutexattr_t pthread_mutexattr_t;
typedef __pthread_cond_t pthread_cond_t;
typedef __pthread_condattr_t pthread_condattr_t;
typedef __pthread_key_t pthread_key_t;
typedef __pthread_once_t pthread_once_t;
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
typedef __pthread_rwlock_t pthread_rwlock_t;
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_XOPEN2K
typedef __pthread_spinlock_t pthread_spinlock_t;
typedef __pthread_barrier_t pthread_barrier_t;
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* __USE_XOPEN2K */



#ifdef __CRT_HAVE_pthread_create
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,pthread_create,(pthread_t *__restrict __newthread, pthread_attr_t const *__restrict __attr, __pthread_start_routine_t __start_routine, void *__restrict __arg),(__newthread,__attr,__start_routine,__arg))
#endif /* pthread_create... */

#ifdef __CRT_HAVE_pthread_exit
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CDECLARE_VOID(__ATTR_NORETURN,,pthread_exit,(void *__retval),(__retval))
#endif /* pthread_exit... */

#ifdef __CRT_HAVE_pthread_join
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL */
__CDECLARE(,int,__NOTHROW_RPC,pthread_join,(pthread_t __pthread, void **__thread_return),(__pthread,__thread_return))
#endif /* pthread_join... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_tryjoin_np
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL */
__CDECLARE(,int,__NOTHROW_NCX,pthread_tryjoin_np,(pthread_t __pthread, void **__thread_return),(__pthread,__thread_return))
#endif /* pthread_tryjoin_np... */

struct timespec;

#if defined(__CRT_HAVE_pthread_timedjoin64_np) && defined(__USE_TIME_BITS64)
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__CREDIRECT(,int,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime),pthread_timedjoin64_np,(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np) && !defined(__USE_TIME_BITS64)
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__CDECLARE(,int,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime),(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np) || defined(__CRT_HAVE_pthread_timedjoin64_np)
#include <local/pthread/pthread_timedjoin_np.h>
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin_np, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL pthread_timedjoin_np)(pthread_t __pthread, void **__thread_return, struct timespec const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin_np))(__pthread, __thread_return, __abstime); })
#endif /* pthread_timedjoin_np... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_timedjoin64_np
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__CDECLARE(,int,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime),(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__CREDIRECT(,int,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime),pthread_timedjoin_np,(__pthread,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np)
#include <local/pthread/pthread_timedjoin64_np.h>
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin64_np, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL pthread_timedjoin64_np)(pthread_t __pthread, void **__thread_return, struct timespec64 const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__pthread, __thread_return, __abstime); })
#endif /* pthread_timedjoin64_np... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __CRT_HAVE_pthread_detach
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it */
__CDECLARE(,int,__NOTHROW_NCX,pthread_detach,(pthread_t __pthread),(__pthread))
#endif /* pthread_detach... */

#ifdef __CRT_HAVE_pthread_self
/* Obtain the identifier of the current thread */
__CDECLARE(__ATTR_CONST,pthread_t,__NOTHROW_NCX,pthread_self,(void),())
#elif defined(__CRT_HAVE_thrd_current)
/* Obtain the identifier of the current thread */
__CREDIRECT(__ATTR_CONST,pthread_t,__NOTHROW_NCX,pthread_self,(void),thrd_current,())
#endif /* pthread_self... */
#ifdef __CRT_HAVE_pthread_equal
/* Compare two thread identifiers */
__CDECLARE(__ATTR_CONST,int,__NOTHROW_NCX,pthread_equal,(pthread_t __pthread1, pthread_t __pthread2),(__pthread1,__pthread2))
#else /* LIBC: pthread_equal */
#include <local/pthread/pthread_equal.h>
/* Compare two thread identifiers */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_equal, __FORCELOCAL __ATTR_CONST int __NOTHROW_NCX(__LIBCCALL pthread_equal)(pthread_t __pthread1, pthread_t __pthread2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_equal))(__pthread1, __pthread2); })
#endif /* pthread_equal... */

/* Thread attribute handling. */

#ifdef __CRT_HAVE_pthread_attr_init
/* Initialize thread attribute *ATTR with default attributes
 * (detachstate is PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_init,(pthread_attr_t *__attr),(__attr))
#endif /* pthread_attr_init... */

#ifdef __CRT_HAVE_pthread_attr_destroy
/* Destroy thread attribute *ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_destroy,(pthread_attr_t *__attr),(__attr))
#endif /* pthread_attr_destroy... */

#ifdef __CRT_HAVE_pthread_attr_getdetachstate
/* Get detach state attribute */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getdetachstate,(pthread_attr_t const *__attr, int *__detachstate),(__attr,__detachstate))
#endif /* pthread_attr_getdetachstate... */

#ifdef __CRT_HAVE_pthread_attr_setdetachstate
/* Set detach state attribute */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setdetachstate,(pthread_attr_t *__attr, int __detachstate),(__attr,__detachstate))
#endif /* pthread_attr_setdetachstate... */

#ifdef __CRT_HAVE_pthread_attr_getguardsize
/* Get the size of the guard area created for stack overflow protection */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getguardsize,(pthread_attr_t const *__attr, size_t *__guardsize),(__attr,__guardsize))
#endif /* pthread_attr_getguardsize... */

#ifdef __CRT_HAVE_pthread_attr_setguardsize
/* Set the size of the guard area created for stack overflow protection */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setguardsize,(pthread_attr_t *__attr, size_t __guardsize),(__attr,__guardsize))
#endif /* pthread_attr_setguardsize... */

#ifdef __CRT_HAVE_pthread_attr_getschedparam
/* Return in *PARAM the scheduling parameters of *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getschedparam,(pthread_attr_t const *__restrict __attr, struct sched_param *__restrict __param),(__attr,__param))
#endif /* pthread_attr_getschedparam... */

#ifdef __CRT_HAVE_pthread_attr_setschedparam
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_setschedparam,(pthread_attr_t *__restrict __attr, struct sched_param const *__restrict __param),(__attr,__param))
#endif /* pthread_attr_setschedparam... */

#ifdef __CRT_HAVE_pthread_attr_getschedpolicy
/* Return in *POLICY the scheduling policy of *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getschedpolicy,(pthread_attr_t const *__restrict __attr, int *__restrict __policy),(__attr,__policy))
#endif /* pthread_attr_getschedpolicy... */

#ifdef __CRT_HAVE_pthread_attr_setschedpolicy
/* Set scheduling policy in *ATTR according to POLICY */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setschedpolicy,(pthread_attr_t *__attr, int __policy),(__attr,__policy))
#endif /* pthread_attr_setschedpolicy... */

#ifdef __CRT_HAVE_pthread_attr_getinheritsched
/* Return in *INHERIT the scheduling inheritance mode of *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getinheritsched,(pthread_attr_t const *__restrict __attr, int *__restrict __inherit),(__attr,__inherit))
#endif /* pthread_attr_getinheritsched... */

#ifdef __CRT_HAVE_pthread_attr_setinheritsched
/* Set scheduling inheritance mode in *ATTR according to INHERIT */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setinheritsched,(pthread_attr_t *__attr, int __inherit),(__attr,__inherit))
#endif /* pthread_attr_setinheritsched... */

#ifdef __CRT_HAVE_pthread_attr_getscope
/* Return in *SCOPE the scheduling contention scope of *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getscope,(pthread_attr_t const *__restrict __attr, int *__restrict __scope),(__attr,__scope))
#endif /* pthread_attr_getscope... */

#ifdef __CRT_HAVE_pthread_attr_setscope
/* Set scheduling contention scope in *ATTR according to SCOPE */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setscope,(pthread_attr_t *__attr, int __scope),(__attr,__scope))
#endif /* pthread_attr_setscope... */

#ifdef __CRT_HAVE_pthread_attr_getstackaddr
/* Return the previously set address for the stack */
__CDECLARE(__ATTR_DEPRECATED_ __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getstackaddr,(pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr),(__attr,__stackaddr))
#endif /* pthread_attr_getstackaddr... */

#ifdef __CRT_HAVE_pthread_attr_setstackaddr
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN */
__CDECLARE(__ATTR_DEPRECATED_ __ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setstackaddr,(pthread_attr_t *__attr, void *__stackaddr),(__attr,__stackaddr))
#endif /* pthread_attr_setstackaddr... */

#ifdef __CRT_HAVE_pthread_attr_getstacksize
/* Return the currently used minimal stack size */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_attr_getstacksize,(pthread_attr_t const *__restrict __attr, size_t *__restrict __stacksize),(__attr,__stacksize))
#endif /* pthread_attr_getstacksize... */

#ifdef __CRT_HAVE_pthread_attr_setstacksize
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setstacksize,(pthread_attr_t *__attr, size_t __stacksize),(__attr,__stacksize))
#endif /* pthread_attr_setstacksize... */
#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_attr_getstack
/* Return the previously set address for the stack */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,pthread_attr_getstack,(pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr, size_t *__restrict __stacksize),(__attr,__stackaddr,__stacksize))
#endif /* pthread_attr_getstack... */

#ifdef __CRT_HAVE_pthread_attr_setstack
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_attr_setstack,(pthread_attr_t *__attr, void *__stackaddr, size_t __stacksize),(__attr,__stackaddr,__stacksize))
#endif /* pthread_attr_setstack... */
#endif /* __USE_XOPEN2K */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_attr_setaffinity_np
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__attr, size_t __cpusetsize, cpu_set_t const *__cpuset),(__attr,__cpusetsize,__cpuset))
#endif /* pthread_attr_setaffinity_np... */

#ifdef __CRT_HAVE_pthread_attr_getaffinity_np
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,pthread_attr_getaffinity_np,(pthread_attr_t const *__attr, size_t __cpusetsize, cpu_set_t *__cpuset),(__attr,__cpusetsize,__cpuset))
#endif /* pthread_attr_getaffinity_np... */

#ifdef __CRT_HAVE_pthread_getattr_default_np
/* Get the default attributes used by pthread_create in this process */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_getattr_default_np,(pthread_attr_t *__attr),(__attr))
#endif /* pthread_getattr_default_np... */

#ifdef __CRT_HAVE_pthread_setattr_default_np
/* Set the default attributes to be used by pthread_create in this process */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_setattr_default_np,(pthread_attr_t const *__attr),(__attr))
#endif /* pthread_setattr_default_np... */

#ifdef __CRT_HAVE_pthread_getattr_np
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,pthread_getattr_np,(pthread_t __pthread, pthread_attr_t *__attr),(__pthread,__attr))
#endif /* pthread_getattr_np... */
#endif /* __USE_GNU */

/* Functions for scheduling control. */

#ifdef __CRT_HAVE_pthread_setschedparam
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,pthread_setschedparam,(pthread_t __target_thread, int __policy, struct sched_param const *__param),(__target_thread,__policy,__param))
#endif /* pthread_setschedparam... */

#ifdef __CRT_HAVE_pthread_getschedparam
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD */
__CDECLARE(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,pthread_getschedparam,(pthread_t __target_thread, int *__restrict __policy, struct sched_param *__restrict __param),(__target_thread,__policy,__param))
#endif /* pthread_getschedparam... */

#ifdef __CRT_HAVE_pthread_setschedprio
/* Set the scheduling priority for TARGET_THREAD */
__CDECLARE(,int,__NOTHROW_NCX,pthread_setschedprio,(pthread_t __target_thread, int __prio),(__target_thread,__prio))
#endif /* pthread_setschedprio... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_getname_np
/* Get thread name visible in the kernel and its interfaces */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,pthread_getname_np,(pthread_t __target_thread, char *__buf, size_t __buflen),(__target_thread,__buf,__buflen))
#endif /* pthread_getname_np... */

#ifdef __CRT_HAVE_pthread_setname_np
/* Set thread name visible in the kernel and its interfaces */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,pthread_setname_np,(pthread_t __target_thread, const char *__name),(__target_thread,__name))
#endif /* pthread_setname_np... */
#endif /* __USE_GNU */
#ifdef __USE_KOS
#ifndef __pthread_gettid_np_defined
#define __pthread_gettid_np_defined 1
#ifdef __CRT_HAVE_pthread_gettid_np
/* Return the TID of the given `target_thread'
 * If the given `target_thread' has already terminated, 0 is returned */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,pthread_gettid_np,(pthread_t __target_thread),(__target_thread))
#else /* LIBC: pthread_gettid_np */
#undef __pthread_gettid_np_defined
#endif /* pthread_gettid_np... */
#endif /* !__pthread_gettid_np_defined */
#endif /* __USE_KOS */
#ifdef __USE_UNIX98
#ifdef __CRT_HAVE_pthread_getconcurrency
/* Determine level of concurrency */
__CDECLARE(__ATTR_PURE,int,__NOTHROW_NCX,pthread_getconcurrency,(void),())
#endif /* pthread_getconcurrency... */

#ifdef __CRT_HAVE_pthread_setconcurrency
/* Set new concurrency level to LEVEL */
__CDECLARE(,int,__NOTHROW_NCX,pthread_setconcurrency,(int __level),(__level))
#endif /* pthread_setconcurrency... */
#endif /* __USE_UNIX98 */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_yield
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation */
__CDECLARE(,int,__NOTHROW_NCX,pthread_yield,(void),())
#elif defined(__CRT_HAVE_sched_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation */
__CREDIRECT(,int,__NOTHROW_NCX,pthread_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation */
__CREDIRECT(,int,__NOTHROW_NCX,pthread_yield,(void),thrd_yield,())
#endif /* pthread_yield... */

#ifdef __CRT_HAVE_pthread_setaffinity_np
/* Limit specified thread THREAD to run only on the processors represented in CPUSET */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,pthread_setaffinity_np,(pthread_t __pthread, size_t __cpusetsize, cpu_set_t const *__cpuset),(__pthread,__cpusetsize,__cpuset))
#endif /* pthread_setaffinity_np... */

#ifdef __CRT_HAVE_pthread_getaffinity_np
/* Get bit set in CPUSET representing the processors THREAD can run on */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,pthread_getaffinity_np,(pthread_t __pthread, size_t __cpusetsize, cpu_set_t *__cpuset),(__pthread,__cpusetsize,__cpuset))
#endif /* pthread_getaffinity_np... */
#endif /* __USE_GNU */

typedef void (__LIBCCALL *__pthread_once_routine_t)(void);

/* Functions for handling initialization. */

#ifdef __CRT_HAVE_pthread_once
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,,pthread_once,(pthread_once_t *__once_control, __pthread_once_routine_t __init_routine),(__once_control,__init_routine)) __THROWS(...)
#elif defined(__CRT_HAVE_call_once)
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,,pthread_once,(pthread_once_t *__once_control, __pthread_once_routine_t __init_routine),call_once,(__once_control,__init_routine)) __THROWS(...)
#endif /* pthread_once... */

/* Functions for handling cancellation.
 * Note that these functions are explicitly not marked to not throw an
 * exception in C++ code. If cancellation is implemented by unwinding
 * this is necessary to have the compiler generate the unwind information. */

#ifdef __CRT_HAVE_pthread_setcancelstate
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL */
__CDECLARE(,int,__NOTHROW_NCX,pthread_setcancelstate,(int __state, int *__oldstate),(__state,__oldstate))
#endif /* pthread_setcancelstate... */

#ifndef __pthread_setcanceltype_defined
#define __pthread_setcanceltype_defined 1
#ifdef __CRT_HAVE_pthread_setcanceltype
/* Set cancellation state of current thread to TYPE, returning the old
 * type in *OLDTYPE if OLDTYPE is not NULL */
__CDECLARE(,int,__NOTHROW_NCX,pthread_setcanceltype,(int __type, int *__oldtype),(__type,__oldtype))
#else /* LIBC: pthread_setcanceltype */
#undef __pthread_setcanceltype_defined
#endif /* pthread_setcanceltype... */
#endif /* !__pthread_setcanceltype_defined */

#ifdef __CRT_HAVE_pthread_cancel
/* Cancel THREAD immediately or at the next possibility */
__CDECLARE(,int,__NOTHROW_NCX,pthread_cancel,(pthread_t __pthread),(__pthread))
#endif /* pthread_cancel... */

#ifdef __CRT_HAVE_pthread_testcancel
/* Test for pending cancellation for the current thread and terminate
 * the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled */
__CDECLARE_VOID(,__NOTHROW_RPC,pthread_testcancel,(void),())
#endif /* pthread_testcancel... */

/* Cancellation handling with integration into exception handling. */
typedef struct {
	struct {
		struct __jmp_buf __cancel_jmp_buf;
		int              __mask_was_saved;
	}                    __cancel_jmp_buf[1];
	void                *__pad[4];
} __pthread_unwind_buf_t __attribute__((__aligned__)); /* XXX: Portable attribute? */

/* No special attributes by default. */
#ifndef __cleanup_fct_attribute
#define __cleanup_fct_attribute /* nothing */
#endif /* !__cleanup_fct_attribute */

/* Structure to hold the cleanup handler information. */
struct __pthread_cleanup_frame {
	void (__LIBCCALL *__cancel_routine) (void *);
	void             *__cancel_arg;
	int               __do_it;
	int               __cancel_type;
};
#if defined(__GNUC__) && defined(__EXCEPTIONS)
#ifdef __cplusplus
/* Class to handle cancellation handler invocation. */
class __pthread_cleanup_class {
	void (__LIBCCALL *__cancel_routine) (void *);
	void             *__cancel_arg;
	int               __do_it;
	int               __cancel_type;
public:
	__CXX_CLASSMEMBER __pthread_cleanup_class (void (__LIBCCALL *__fct)(void *), void *__arg)
		: __cancel_routine(__fct), __cancel_arg(__arg), __do_it(1)
	{ }
	__CXX_CLASSMEMBER ~__pthread_cleanup_class() {
		if (__do_it)
			(*__cancel_routine)(__cancel_arg);
	}
	__CXX_CLASSMEMBER void __setdoit(int __newval) {
		__do_it = __newval;
	}
#ifdef __pthread_setcanceltype_defined
	__CXX_CLASSMEMBER void __defer() { pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__cancel_type); }
	__CXX_CLASSMEMBER void __restore() const { pthread_setcanceltype(__cancel_type, 0); }
#endif /* __pthread_setcanceltype_defined */
};

/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg) \
	do {                                   \
		__pthread_cleanup_class __clframe(routine, arg)

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)  \
		__clframe.__setdoit(execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)      \
	do {                                                 \
		__pthread_cleanup_class __clframe(routine, arg); \
		__clframe.__defer()

/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute) \
		__clframe.__restore();                  \
		__clframe.__setdoit(execute);           \
	} __WHILE0
#endif /* __USE_GNU */
#else /* __cplusplus */
#ifdef __CRT_HAVE___pthread_cleanup_routine
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_cleanup_routine,(struct __pthread_cleanup_frame *__frame),(__frame))
#else /* LIBC: __pthread_cleanup_routine */
#include <local/pthread/__pthread_cleanup_routine.h>
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__NAMESPACE_LOCAL_USING_OR_IMPL(__pthread_cleanup_routine, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL __pthread_cleanup_routine)(struct __pthread_cleanup_frame *__frame) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__pthread_cleanup_routine))(__frame); })
#endif /* __pthread_cleanup_routine... */
/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg)                          \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)   \
		__clframe.__do_it = (execute); \
	} __WHILE0

#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)                 \
	do {                                                            \
		struct __pthread_cleanup_frame __clframe                    \
		__attribute__((__cleanup__(__pthread_cleanup_routine))) = { \
			.__cancel_routine = (routine),                          \
			.__cancel_arg = (arg),                                  \
			.__do_it = 1                                            \
		};                                                          \
		(void)pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__clframe.__cancel_type)

/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute)                     \
		(void)pthread_setcanceltype(__clframe.__cancel_type, NULL); \
		__clframe.__do_it = (execute);                              \
	} __WHILE0

#endif /* __USE_GNU */
#endif /* !__cplusplus */
#else /* __GNUC__ && __EXCEPTIONS */
/* Install a cleanup handler: ROUTINE will be called with arguments ARG
 * when the thread is canceled or calls pthread_exit. ROUTINE will also
 * be called with arguments ARG when the matching pthread_cleanup_pop
 * is executed with non-zero EXECUTE argument.
 * pthread_cleanup_push and pthread_cleanup_pop are macros and must always
 * be used in matching pairs at the same nesting level of braces. */
#define pthread_cleanup_push(routine, arg)                                                                    \
	do {                                                                                                      \
		__pthread_unwind_buf_t __cancel_buf;                                                                  \
		void (__LIBCCALL *__cancel_routine)(void *) = (routine);                                              \
		void *__cancel_arg                          = (arg);                                                  \
		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
		if __unlikely(__not_first_call) {                                                                     \
			(*__cancel_routine)(__cancel_arg);                                                                \
			__pthread_unwind_next(&__cancel_buf);                                                             \
			__builtin_unreachable();                                                                          \
		}                                                                                                     \
		__pthread_register_cancel(&__cancel_buf);                                                             \
		do {

#ifdef __CRT_HAVE___pthread_register_cancel
__CDECLARE_VOID(__cleanup_fct_attribute,__NOTHROW_NCX,__pthread_register_cancel,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __pthread_register_cancel... */
/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
 * If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)                                           \
			do {                                                               \
			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
		} __WHILE0;                                                            \
		__pthread_unregister_cancel(&__cancel_buf);                            \
		if (execute)                                                           \
			(*__cancel_routine)(__cancel_arg);                                 \
	} __WHILE0
#ifdef __CRT_HAVE___pthread_unregister_cancel
__CDECLARE_VOID(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unregister_cancel,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __pthread_unregister_cancel... */
#ifdef __USE_GNU
/* Install a cleanup handler as pthread_cleanup_push does, but also
 * saves the current cancellation type and sets it to deferred
 * cancellation. */
#define pthread_cleanup_push_defer_np(routine, arg)                                                           \
	do {                                                                                                      \
		__pthread_unwind_buf_t __cancel_buf;                                                                  \
		void (__LIBCCALL *__cancel_routine)(void *) = (routine);                                              \
		void *__cancel_arg               = (arg);                                                             \
		int __not_first_call = __sigsetjmp((struct __jmp_buf_tag *)(void *)__cancel_buf.__cancel_jmp_buf, 0); \
		if __unlikely(__not_first_call) {                                                                     \
			__cancel_routine(__cancel_arg);                                                                   \
			__pthread_unwind_next(&__cancel_buf);                                                             \
			__builtin_unreachable();                                                                          \
		}                                                                                                     \
		__pthread_register_cancel_defer(&__cancel_buf);                                                       \
		do {
#ifdef __CRT_HAVE___pthread_register_cancel_defer
__CDECLARE_VOID(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_register_cancel_defer,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __pthread_register_cancel_defer... */
/* Remove a cleanup handler as pthread_cleanup_pop does, but also
 * restores the cancellation type that was in effect when the matching
 * pthread_cleanup_push_defer was called. */
#define pthread_cleanup_pop_restore_np(execute)                                \
			do {                                                               \
			} __WHILE0; /* Empty to allow label before pthread_cleanup_pop. */ \
		} __WHILE0;                                                            \
		__pthread_unregister_cancel_restore(&__cancel_buf);                    \
		if (execute)                                                           \
			(*__cancel_routine)(__cancel_arg);                                 \
	} __WHILE0
#ifdef __CRT_HAVE___pthread_unregister_cancel_restore
__CDECLARE_VOID(__cleanup_fct_attribute __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unregister_cancel_restore,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __pthread_unregister_cancel_restore... */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE___pthread_unwind_next
/* Internal interface to initiate cleanup */
__CDECLARE_VOID(__cleanup_fct_attribute __ATTR_NORETURN __ATTR_WEAK __ATTR_NONNULL((1)),__NOTHROW_NCX,__pthread_unwind_next,(__pthread_unwind_buf_t *__buf),(__buf))
#endif /* __pthread_unwind_next... */
#endif /* !__GNUC__ || !__EXCEPTIONS */

/* Function used in the macros. */
struct __jmp_buf_tag;
#ifdef __CRT_HAVE___sigsetjmp
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),(__env,__savemask))
#elif defined(__CRT_HAVE_sigsetjmp)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigsetjmp,(struct __jmp_buf_tag *__env, int __savemask),sigsetjmp,(__env,__savemask))
#endif /* __sigsetjmp... */

/* Mutex handling. */

#ifdef __CRT_HAVE_pthread_mutex_init
/* Initialize a mutex */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_init,(pthread_mutex_t *__mutex, pthread_mutexattr_t const *__mutexattr),(__mutex,__mutexattr))
#endif /* pthread_mutex_init... */

#ifdef __CRT_HAVE_pthread_mutex_destroy
/* Destroy a mutex */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__mutex),(__mutex))
#elif defined(__CRT_HAVE_mtx_destroy)
/* Destroy a mutex */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_destroy,(pthread_mutex_t *__mutex),mtx_destroy,(__mutex))
#endif /* pthread_mutex_destroy... */

#ifdef __CRT_HAVE_pthread_mutex_trylock
/* Try locking a mutex */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_trylock,(pthread_mutex_t *__mutex),(__mutex))
#endif /* pthread_mutex_trylock... */

#ifdef __CRT_HAVE_pthread_mutex_lock
/* Lock a mutex */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_lock,(pthread_mutex_t *__mutex),(__mutex))
#endif /* pthread_mutex_lock... */

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_mutex_timedlock64) && defined(__USE_TIME_BITS64)
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_mutex_timedlock64,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && !defined(__USE_TIME_BITS64)
/* Wait until lock becomes available, or specified time passes */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_mutex_timedlock,(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) || defined(__CRT_HAVE_pthread_mutex_timedlock64)
#include <local/pthread/pthread_mutex_timedlock.h>
/* Wait until lock becomes available, or specified time passes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock)(pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock))(__mutex, __abstime); })
#endif /* pthread_mutex_timedlock... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_mutex_timedlock64
/* Wait until lock becomes available, or specified time passes */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_mutex_timedlock64,(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),pthread_mutex_timedlock,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <local/pthread/pthread_mutex_timedlock64.h>
/* Wait until lock becomes available, or specified time passes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_mutex_timedlock64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_mutex_timedlock64)(pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock64))(__mutex, __abstime); })
#endif /* pthread_mutex_timedlock64... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */

#ifdef __CRT_HAVE_pthread_mutex_unlock
/* Unlock a mutex */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_unlock,(pthread_mutex_t *__mutex),(__mutex))
#endif /* pthread_mutex_unlock... */

#ifdef __CRT_HAVE_pthread_mutex_getprioceiling
/* Get the priority ceiling of MUTEX */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutex_getprioceiling,(pthread_mutex_t const *__restrict __mutex, int *__restrict __prioceiling),(__mutex,__prioceiling))
#endif /* pthread_mutex_getprioceiling... */

#ifdef __CRT_HAVE_pthread_mutex_setprioceiling
/* Set the priority ceiling of MUTEX to PRIOCEILING, return old
 * priority ceiling value in *OLD_CEILING */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,pthread_mutex_setprioceiling,(pthread_mutex_t *__restrict __mutex, int __prioceiling, int *__restrict __old_ceiling),(__mutex,__prioceiling,__old_ceiling))
#endif /* pthread_mutex_setprioceiling... */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_pthread_mutex_consistent
/* Declare the state protected by MUTEX as consistent */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_consistent,(pthread_mutex_t *__mutex),(__mutex))
#endif /* pthread_mutex_consistent... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutex_consistent_np
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutex_consistent_np,(pthread_mutex_t *__mutex),(__mutex))
#endif /* pthread_mutex_consistent_np... */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K8 */

/* Functions for handling mutex attributes. */

#ifdef __CRT_HAVE_pthread_mutexattr_init
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_init,(pthread_mutexattr_t *__attr),(__attr))
#endif /* pthread_mutexattr_init... */

#ifdef __CRT_HAVE_pthread_mutexattr_destroy
/* Destroy mutex attribute object ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_destroy,(pthread_mutexattr_t *__attr),(__attr))
#endif /* pthread_mutexattr_destroy... */

#ifdef __CRT_HAVE_pthread_mutexattr_getpshared
/* Get the process-shared flag of the mutex attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_getpshared,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
#endif /* pthread_mutexattr_getpshared... */

#ifdef __CRT_HAVE_pthread_mutexattr_setpshared
/* Set the process-shared flag of the mutex attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_setpshared,(pthread_mutexattr_t *__attr, int __pshared),(__attr,__pshared))
#endif /* pthread_mutexattr_setpshared... */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __CRT_HAVE_pthread_mutexattr_gettype
/* Return in *KIND the mutex kind attribute in *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_gettype,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __kind),(__attr,__kind))
#endif /* pthread_mutexattr_gettype... */

#ifdef __CRT_HAVE_pthread_mutexattr_settype
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_settype,(pthread_mutexattr_t *__attr, int __kind),(__attr,__kind))
#endif /* pthread_mutexattr_settype... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_pthread_mutexattr_getprotocol
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_getprotocol,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __protocol),(__attr,__protocol))
#endif /* pthread_mutexattr_getprotocol... */

#ifdef __CRT_HAVE_pthread_mutexattr_setprotocol
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_setprotocol,(pthread_mutexattr_t *__attr, int __protocol),(__attr,__protocol))
#endif /* pthread_mutexattr_setprotocol... */

#ifdef __CRT_HAVE_pthread_mutexattr_getprioceiling
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_getprioceiling,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __prioceiling),(__attr,__prioceiling))
#endif /* pthread_mutexattr_getprioceiling... */

#ifdef __CRT_HAVE_pthread_mutexattr_setprioceiling
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_setprioceiling,(pthread_mutexattr_t *__attr, int __prioceiling),(__attr,__prioceiling))
#endif /* pthread_mutexattr_setprioceiling... */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust
/* Get the robustness flag of the mutex attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_getrobust,(pthread_mutexattr_t const *__attr, int *__robustness),(__attr,__robustness))
#endif /* pthread_mutexattr_getrobust... */

#ifdef __CRT_HAVE_pthread_mutexattr_setrobust
/* Set the robustness flag of the mutex attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_setrobust,(pthread_mutexattr_t *__attr, int __robustness),(__attr,__robustness))
#endif /* pthread_mutexattr_setrobust... */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_pthread_mutexattr_getrobust_np
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_mutexattr_getrobust_np,(pthread_mutexattr_t const *__attr, int *__robustness),(__attr,__robustness))
#endif /* pthread_mutexattr_getrobust_np... */
#ifdef __CRT_HAVE_pthread_mutexattr_setrobust_np
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_mutexattr_setrobust_np,(pthread_mutexattr_t *__attr, int __robustness),(__attr,__robustness))
#endif /* pthread_mutexattr_setrobust_np... */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
/* Functions for handling read-write locks. */

#ifdef __CRT_HAVE_pthread_rwlock_init
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlock_init,(pthread_rwlock_t *__restrict __rwlock, pthread_rwlockattr_t const *__restrict __attr),(__rwlock,__attr))
#endif /* pthread_rwlock_init... */

#ifdef __CRT_HAVE_pthread_rwlock_destroy
/* Destroy read-write lock RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlock_destroy,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_destroy... */

#ifdef __CRT_HAVE_pthread_rwlock_rdlock
/* Acquire read lock for RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,pthread_rwlock_rdlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_rdlock... */

#ifdef __CRT_HAVE_pthread_rwlock_tryrdlock
/* Try to acquire read lock for RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlock_tryrdlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_tryrdlock... */

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_rwlock_timedrdlock64) && defined(__USE_TIME_BITS64)
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),pthread_rwlock_timedrdlock64,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && !defined(__USE_TIME_BITS64)
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedrdlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock) || defined(__CRT_HAVE_pthread_rwlock_timedrdlock64)
#include <local/pthread/pthread_rwlock_timedrdlock.h>
/* Try to acquire read lock for RWLOCK or return after specfied time */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock))(__rwlock, __abstime); })
#endif /* pthread_rwlock_timedrdlock... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_rwlock_timedrdlock
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedrdlock32,(pthread_rwlock_t *__restrict __rwlock, struct timespec32 const *__restrict __abstime),pthread_rwlock_timedrdlock,(__rwlock,__abstime))
#endif /* pthread_rwlock_timedrdlock32... */
#ifdef __CRT_HAVE_pthread_rwlock_timedrdlock64
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedrdlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedrdlock,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedrdlock)
#include <local/pthread/pthread_rwlock_timedrdlock64.h>
/* Try to acquire read lock for RWLOCK or return after specfied time */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedrdlock64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock64))(__rwlock, __abstime); })
#endif /* pthread_rwlock_timedrdlock64... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */

#ifdef __CRT_HAVE_pthread_rwlock_wrlock
/* Acquire write lock for RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,pthread_rwlock_wrlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_wrlock... */

#ifdef __CRT_HAVE_pthread_rwlock_trywrlock
/* Try to acquire write lock for RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlock_trywrlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_trywrlock... */

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pthread_rwlock_timedwrlock64) && defined(__USE_TIME_BITS64)
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),pthread_rwlock_timedwrlock64,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && !defined(__USE_TIME_BITS64)
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedwrlock,(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) || defined(__CRT_HAVE_pthread_rwlock_timedwrlock64)
#include <local/pthread/pthread_rwlock_timedwrlock.h>
/* Try to acquire write lock for RWLOCK or return after specfied time */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict __rwlock, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock))(__rwlock, __abstime); })
#endif /* pthread_rwlock_timedwrlock... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedwrlock32,(pthread_rwlock_t *__restrict __rwlock, struct timespec32 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#endif /* pthread_rwlock_timedwrlock32... */
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock64
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_rwlock_timedwrlock64,(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <local/pthread/pthread_rwlock_timedwrlock64.h>
/* Try to acquire write lock for RWLOCK or return after specfied time */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_rwlock_timedwrlock64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict __rwlock, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64))(__rwlock, __abstime); })
#endif /* pthread_rwlock_timedwrlock64... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */

#ifdef __CRT_HAVE_pthread_rwlock_unlock
/* Unlock RWLOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlock_unlock,(pthread_rwlock_t *__rwlock),(__rwlock))
#endif /* pthread_rwlock_unlock... */

/* Functions for handling read-write lock attributes. */

#ifdef __CRT_HAVE_pthread_rwlockattr_init
/* Initialize attribute object ATTR with default values */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlockattr_init,(pthread_rwlockattr_t *__attr),(__attr))
#endif /* pthread_rwlockattr_init... */

#ifdef __CRT_HAVE_pthread_rwlockattr_destroy
/* Destroy attribute object ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlockattr_destroy,(pthread_rwlockattr_t *__attr),(__attr))
#endif /* pthread_rwlockattr_destroy... */

#ifdef __CRT_HAVE_pthread_rwlockattr_getpshared
/* Return current setting of process-shared attribute of ATTR in PSHARED */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_rwlockattr_getpshared,(pthread_rwlockattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
#endif /* pthread_rwlockattr_getpshared... */

#ifdef __CRT_HAVE_pthread_rwlockattr_setpshared
/* Set process-shared attribute of ATTR to PSHARED */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlockattr_setpshared,(pthread_rwlockattr_t *__attr, int __pshared),(__attr,__pshared))
#endif /* pthread_rwlockattr_setpshared... */

#ifdef __CRT_HAVE_pthread_rwlockattr_getkind_np
/* Return current setting of reader/writer preference */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_rwlockattr_getkind_np,(pthread_rwlockattr_t const *__restrict __attr, int *__restrict __pref),(__attr,__pref))
#endif /* pthread_rwlockattr_getkind_np... */

#ifdef __CRT_HAVE_pthread_rwlockattr_setkind_np
/* Set reader/write preference */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_rwlockattr_setkind_np,(pthread_rwlockattr_t *__attr, int __pref),(__attr,__pref))
#endif /* pthread_rwlockattr_setkind_np... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

/* Functions for handling conditional variables. */

#ifdef __CRT_HAVE_pthread_cond_init
/* Initialize condition variable COND using attributes ATTR, or use
 * the default values if later is NULL */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_cond_init,(pthread_cond_t *__restrict __cond, pthread_condattr_t const *__restrict __cond_attr),(__cond,__cond_attr))
#endif /* pthread_cond_init... */

#ifdef __CRT_HAVE_pthread_cond_destroy
/* Destroy condition variable COND */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__cond),(__cond))
#elif defined(__CRT_HAVE_cnd_destroy)
/* Destroy condition variable COND */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_cond_destroy,(pthread_cond_t *__cond),cnd_destroy,(__cond))
#endif /* pthread_cond_destroy... */

#ifdef __CRT_HAVE_pthread_cond_signal
/* Wake up one thread waiting for condition variable COND */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_cond_signal,(pthread_cond_t *__cond),(__cond))
#endif /* pthread_cond_signal... */

#ifdef __CRT_HAVE_pthread_cond_broadcast
/* Wake up all threads waiting for condition variables COND */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_cond_broadcast,(pthread_cond_t *__cond),(__cond))
#endif /* pthread_cond_broadcast... */

#ifdef __CRT_HAVE_pthread_cond_wait
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,pthread_cond_wait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex),(__cond,__mutex))
#endif /* pthread_cond_wait... */

#if defined(__CRT_HAVE_pthread_cond_timedwait64) && defined(__USE_TIME_BITS64)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && !defined(__USE_TIME_BITS64)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,pthread_cond_timedwait,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) || defined(__CRT_HAVE_pthread_cond_timedwait64)
#include <local/pthread/pthread_cond_timedwait.h>
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait)(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait))(__cond, __mutex, __abstime); })
#endif /* pthread_cond_timedwait... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_pthread_cond_timedwait64
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,pthread_cond_timedwait64,(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
#include <local/pthread/pthread_cond_timedwait64.h>
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_cond_timedwait64, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_RPC(__LIBCCALL pthread_cond_timedwait64)(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, struct timespec64 const *__restrict __abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait64))(__cond, __mutex, __abstime); })
#endif /* pthread_cond_timedwait64... */
#endif /* __USE_TIME64 */

/* Functions for handling condition variable attributes. */

#ifdef __CRT_HAVE_pthread_condattr_init
/* Initialize condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_condattr_init,(pthread_condattr_t *__attr),(__attr))
#endif /* pthread_condattr_init... */

#ifdef __CRT_HAVE_pthread_condattr_destroy
/* Destroy condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_condattr_destroy,(pthread_condattr_t *__attr),(__attr))
#endif /* pthread_condattr_destroy... */

#ifdef __CRT_HAVE_pthread_condattr_getpshared
/* Get the process-shared flag of the condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_condattr_getpshared,(pthread_condattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
#endif /* pthread_condattr_getpshared... */

#ifdef __CRT_HAVE_pthread_condattr_setpshared
/* Set the process-shared flag of the condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_condattr_setpshared,(pthread_condattr_t *__attr, int __pshared),(__attr,__pshared))
#endif /* pthread_condattr_setpshared... */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_condattr_getclock
/* Get the clock selected for the condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_condattr_getclock,(pthread_condattr_t const *__restrict __attr, __clockid_t *__restrict __clock_id),(__attr,__clock_id))
#endif /* pthread_condattr_getclock... */
#ifdef __CRT_HAVE_pthread_condattr_setclock
/* Set the clock selected for the condition variable attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_condattr_setclock,(pthread_condattr_t *__attr, __clockid_t __clock_id),(__attr,__clock_id))
#endif /* pthread_condattr_setclock... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_XOPEN2K
/* Functions to handle spinlocks. */

#ifdef __CRT_HAVE_pthread_spin_init
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_spin_init,(pthread_spinlock_t *__lock, int __pshared),(__lock,__pshared))
#else /* LIBC: pthread_spin_init */
#include <local/pthread/pthread_spin_init.h>
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_init, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pthread_spin_init)(pthread_spinlock_t *__lock, int __pshared) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_init))(__lock, __pshared); })
#endif /* pthread_spin_init... */

#ifdef __CRT_HAVE_pthread_spin_destroy
/* Destroy the spinlock LOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_spin_destroy,(pthread_spinlock_t *__lock),(__lock))
#else /* LIBC: pthread_spin_destroy */
#include <local/pthread/pthread_spin_destroy.h>
/* Destroy the spinlock LOCK */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_destroy, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pthread_spin_destroy)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_destroy))(__lock); })
#endif /* pthread_spin_destroy... */

#ifdef __CRT_HAVE_pthread_spin_lock
/* Wait until spinlock LOCK is retrieved */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_spin_lock,(pthread_spinlock_t *__lock),(__lock))
#else /* LIBC: pthread_spin_lock */
#include <local/pthread/pthread_spin_lock.h>
/* Wait until spinlock LOCK is retrieved */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_lock, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pthread_spin_lock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_lock))(__lock); })
#endif /* pthread_spin_lock... */

#ifdef __CRT_HAVE_pthread_spin_trylock
/* Try to lock spinlock LOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_spin_trylock,(pthread_spinlock_t *__lock),(__lock))
#else /* LIBC: pthread_spin_trylock */
#include <local/pthread/pthread_spin_trylock.h>
/* Try to lock spinlock LOCK */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_trylock, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pthread_spin_trylock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_trylock))(__lock); })
#endif /* pthread_spin_trylock... */

#ifdef __CRT_HAVE_pthread_spin_unlock
/* Release spinlock LOCK */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_spin_unlock,(pthread_spinlock_t *__lock),(__lock))
#else /* LIBC: pthread_spin_unlock */
#include <local/pthread/pthread_spin_unlock.h>
/* Release spinlock LOCK */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_spin_unlock, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pthread_spin_unlock)(pthread_spinlock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_unlock))(__lock); })
#endif /* pthread_spin_unlock... */

/* Functions to handle barriers. */

#ifdef __CRT_HAVE_pthread_barrier_init
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_barrier_init,(pthread_barrier_t *__restrict __barrier, pthread_barrierattr_t const *__restrict __attr, unsigned int __count),(__barrier,__attr,__count))
#endif /* pthread_barrier_init... */

#ifdef __CRT_HAVE_pthread_barrier_destroy
/* Destroy a previously dynamically initialized barrier BARRIER */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_barrier_destroy,(pthread_barrier_t *__barrier),(__barrier))
#endif /* pthread_barrier_destroy... */

#ifdef __CRT_HAVE_pthread_barrier_wait
/* Wait on barrier BARRIER */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,pthread_barrier_wait,(pthread_barrier_t *__barrier),(__barrier))
#endif /* pthread_barrier_wait... */

#ifdef __CRT_HAVE_pthread_barrierattr_init
/* Initialize barrier attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_barrierattr_init,(pthread_barrierattr_t *__attr),(__attr))
#endif /* pthread_barrierattr_init... */

#ifdef __CRT_HAVE_pthread_barrierattr_destroy
/* Destroy previously dynamically initialized barrier attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_barrierattr_destroy,(pthread_barrierattr_t *__attr),(__attr))
#endif /* pthread_barrierattr_destroy... */

#ifdef __CRT_HAVE_pthread_barrierattr_getpshared
/* Get the process-shared flag of the barrier attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,pthread_barrierattr_getpshared,(pthread_barrierattr_t const *__restrict __attr, int *__restrict __pshared),(__attr,__pshared))
#endif /* pthread_barrierattr_getpshared... */

#ifdef __CRT_HAVE_pthread_barrierattr_setpshared
/* Set the process-shared flag of the barrier attribute ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_barrierattr_setpshared,(pthread_barrierattr_t *__attr, int __pshared),(__attr,__pshared))
#endif /* pthread_barrierattr_setpshared... */
#endif /* __USE_XOPEN2K */

/* Functions for handling thread-specific data. */
#ifndef ____pthread_destr_function_t_defined
#define ____pthread_destr_function_t_defined 1
typedef void (__LIBCCALL *__pthread_destr_function_t)(void *);
#endif /* !____pthread_destr_function_t_defined */

#ifdef __CRT_HAVE_pthread_key_create
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pthread_key_create,(pthread_key_t *__key, __pthread_destr_function_t __destr_function),(__key,__destr_function))
#endif /* pthread_key_create... */

#ifdef __CRT_HAVE_pthread_key_delete
/* Destroy KEY */
__CDECLARE(,int,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_delete)
/* Destroy KEY */
__CREDIRECT(,int,__NOTHROW_NCX,pthread_key_delete,(pthread_key_t __key),tss_delete,(__key))
#endif /* pthread_key_delete... */

#ifdef __CRT_HAVE_pthread_getspecific
/* Return current value of the thread-specific data slot identified by KEY */
__CDECLARE(,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),(__key))
#elif defined(__CRT_HAVE_tss_get)
/* Return current value of the thread-specific data slot identified by KEY */
__CREDIRECT(,void *,__NOTHROW_NCX,pthread_getspecific,(pthread_key_t __key),tss_get,(__key))
#endif /* pthread_getspecific... */

#ifdef __CRT_HAVE_pthread_setspecific
/* Store POINTER in the thread-specific data slot identified by KEY */
__CDECLARE(,int,__NOTHROW_NCX,pthread_setspecific,(pthread_key_t __key, void const *__pointer),(__key,__pointer))
#endif /* pthread_setspecific... */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pthread_getcpuclockid
/* Get ID of CPU-time clock for thread THREAD_ID */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,pthread_getcpuclockid,(pthread_t __pthread_id, __clockid_t *__clock_id),(__pthread_id,__clock_id))
#endif /* pthread_getcpuclockid... */
#endif /* __USE_XOPEN2K */

typedef void (__LIBCCALL *__pthread_atfork_func_t)(void);

#ifdef __CRT_HAVE_pthread_atfork
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called) */
__CDECLARE(,int,__NOTHROW_NCX,pthread_atfork,(__pthread_atfork_func_t __prepare, __pthread_atfork_func_t __parent, __pthread_atfork_func_t __child),(__prepare,__parent,__child))
#endif /* pthread_atfork... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PTHREAD_H */
