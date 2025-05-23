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
#ifndef GUARD_LIBC_USER_KOS_RPC_C
#define GUARD_LIBC_USER_KOS_RPC_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "kos.rpc.h"

DECL_BEGIN

/* These 2 functions are arch-specific */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void const *NOTHROW(LIBCCALL libc_get_rpc_exec_program)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void const *NOTHROW(LIBCCALL libc_get_rpc_interrupt_program)(void);


/*[[[head:libc_rpc_schedule,hash:CRC-32=0xb00d9a41]]]*/
/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread may terminate  before the conditions  for the RPC  to be served  are
 * ever met. Note that these conditions depend on the given `mode'. Note  that
 * on multi-arch platforms (such as x86), the register numbers, as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 *
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program contains illegal instructions.
 * @throws: E_PROCESS_EXITED:  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") ATTR_IN(3) ATTR_INS(4, 5) int
NOTHROW_RPC(LIBCCALL libc_rpc_schedule)(pid_t target_tid,
                                        unsigned int mode,
                                        void const *program,
                                        void const *const *params,
                                        size_t max_param_count)
/*[[[body:libc_rpc_schedule]]]*/
{
	errno_t error;
	error = sys_rpc_schedule(target_tid, mode, program,
	                         params, max_param_count);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_rpc_schedule]]]*/

/*[[[head:libc_rpc_serve,hash:CRC-32=0x8951917e]]]*/
/* >> rpc_serve(2)
 * Check for  pending RPCs.  This function  is basically  a cancellation  point in  disguise,
 * in  that it literally _is_ a regular, old cancellation point, with the only addition being
 * it doesn't contain any blocking call. You may also know this one as `pthread_testcancel()'
 * Essentially, this function  just calls  the kernel function  `task_serve()', and  forwards
 * that function's return value.
 * @return: 0:  Nothing was handled.
 * @return: -1: [errno=EINTR] RPCs (or posix signals) were handled. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") int
NOTHROW_RPC(LIBCCALL libc_rpc_serve)(void)
/*[[[body:libc_rpc_serve]]]*/
{
	errno_t error = sys_rpc_serve();
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_rpc_serve]]]*/

/*[[[head:libc_rpc_exec,hash:CRC-32=0x75a4d5d5]]]*/
/* >> rpc_exec(3)
 * Send an RPC to `target_tid' (which must be a thread within the  current
 * process). The RPC will modify  the target thread's register state  such
 * that `func' will be executed before (upon its return) execution resumes
 * within that thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") NONNULL((3)) int
NOTHROW_RPC(LIBCCALL libc_rpc_exec)(pid_t target_tid,
                                    unsigned int mode,
                                    prpc_exec_callback_t func,
                                    void *cookie)
/*[[[body:libc_rpc_exec]]]*/
{
	void *args[2];
	args[0] = (void *)func;
	args[1] = (void *)cookie;
	return libc_rpc_schedule(target_tid, mode, libc_get_rpc_exec_program(), args, 2);
}
/*[[[end:libc_rpc_exec]]]*/

/*[[[head:libc_rpc_interrupt,hash:CRC-32=0x351268f9]]]*/
/* >> rpc_interrupt(3)
 * Send an RPC to `target_tid' (which must be a thread within the current
 * process).  The RPC won't do anything except causing an in-progress (or
 * upcoming) system  call to  fail with  `errno=EINTR' (so-long  as  that
 * system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") int
NOTHROW_RPC(LIBCCALL libc_rpc_interrupt)(pid_t target_tid,
                                         unsigned int mode)
/*[[[body:libc_rpc_interrupt]]]*/
{
	return libc_rpc_schedule(target_tid, mode, libc_get_rpc_interrupt_program(), NULL, 0);
}
/*[[[end:libc_rpc_interrupt]]]*/

/*[[[skip:libc_RpcSchedule]]]*/

/*[[[head:libc_RpcExec,hash:CRC-32=0xf5f9ca0b]]]*/
/* >> rpc_exec(3)
 * Send an RPC to `target_tid' (which must be a thread within the  current
 * process). The RPC will modify  the target thread's register state  such
 * that `func' will be executed before (upon its return) execution resumes
 * within that thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") NONNULL((3)) void
(LIBCCALL libc_RpcExec)(pid_t target_tid,
                        unsigned int mode,
                        prpc_exec_callback_t func,
                        void *cookie) THROWS(...)
/*[[[body:libc_RpcExec]]]*/
{
	void *args[2];
	args[0] = (void *)func;
	args[1] = (void *)cookie;
	libc_RpcSchedule(target_tid, mode, libc_get_rpc_exec_program(), args, 2);
}
/*[[[end:libc_RpcExec]]]*/

/*[[[head:libc_RpcInterrupt,hash:CRC-32=0xee710942]]]*/
/* >> rpc_interrupt(3)
 * Send an RPC to `target_tid' (which must be a thread within the current
 * process).  The RPC won't do anything except causing an in-progress (or
 * upcoming) system  call to  fail with  `errno=EINTR' (so-long  as  that
 * system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") void
(LIBCCALL libc_RpcInterrupt)(pid_t target_tid,
                             unsigned int mode) THROWS(...)
/*[[[body:libc_RpcInterrupt]]]*/
{
	libc_RpcSchedule(target_tid, mode, libc_get_rpc_interrupt_program(), NULL, 0);
}
/*[[[end:libc_RpcInterrupt]]]*/

/*[[[start:exports,hash:CRC-32=0xcbaf0195]]]*/
DEFINE_PUBLIC_ALIAS_P(rpc_schedule,libc_rpc_schedule,ATTR_IN(3) ATTR_INS(4, 5),int,NOTHROW_RPC,LIBCCALL,(pid_t target_tid, unsigned int mode, void const *program, void const *const *params, size_t max_param_count),(target_tid,mode,program,params,max_param_count));
DEFINE_PUBLIC_ALIAS_P(rpc_serve,libc_rpc_serve,,int,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(rpc_exec,libc_rpc_exec,NONNULL((3)),int,NOTHROW_RPC,LIBCCALL,(pid_t target_tid, unsigned int mode, prpc_exec_callback_t func, void *cookie),(target_tid,mode,func,cookie));
DEFINE_PUBLIC_ALIAS_P(rpc_interrupt,libc_rpc_interrupt,,int,NOTHROW_RPC,LIBCCALL,(pid_t target_tid, unsigned int mode),(target_tid,mode));
DEFINE_PUBLIC_ALIAS_P_VOID(RpcExec,libc_RpcExec,NONNULL((3)),THROWING(...),LIBCCALL,(pid_t target_tid, unsigned int mode, prpc_exec_callback_t func, void *cookie),(target_tid,mode,func,cookie));
DEFINE_PUBLIC_ALIAS_P_VOID(RpcInterrupt,libc_RpcInterrupt,,THROWING(...),LIBCCALL,(pid_t target_tid, unsigned int mode),(target_tid,mode));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_RPC_C */
