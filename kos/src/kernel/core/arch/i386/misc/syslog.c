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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/arch/syslog.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <sys/io.h>

#include <inttypes.h>
#include <stdio.h> /* sprintf() */
#include <time.h>  /* localtime_r() */



#undef DBG_MONITOR_MEMORY
#if 0 /* For debugging: Monitor a physical memory location */
#define DBG_MONITOR_MEMORY 0x000c9574
#define DBG_MONITOR_TYPE   u16
#endif


#ifdef DBG_MONITOR_MEMORY
#include <fs/vfs.h>
#include <kernel/paging.h>
#endif /* DBG_MONITOR_MEMORY */

DECL_BEGIN

INTERN port_t x86_syslog_port = (port_t)0x80;


#ifndef CONFIG_NO_SMP
PRIVATE unsigned int x86_syslog_smplock = 0;
#define x86_syslog_smplock_acquire(was)                \
	do {                                               \
		(was) = PREEMPTION_PUSHOFF();                  \
		while (ATOMIC_XCH(x86_syslog_smplock, 1) != 0) \
			task_pause();                              \
	}	__WHILE0
#define x86_syslog_smplock_release(was)   \
	(ATOMIC_STORE(x86_syslog_smplock, 0), \
	 PREEMPTION_POP(was))
#else /* !CONFIG_NO_SMP */
#define x86_syslog_smplock_acquire(was) \
	((was) = PREEMPTION_PUSHOFF())
#define x86_syslog_smplock_release(was)   \
	PREEMPTION_POP(was)
#endif /* CONFIG_NO_SMP */


/* Raw, low-level write the given data to the default x86 system log.
 * The write is performed atomically in respect to other calls to
 * this function. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL x86_syslog_write)(char const *__restrict data,
                                size_t datalen) {
	pflag_t was;
	x86_syslog_smplock_acquire(was);
	outsb(x86_syslog_port, data, datalen);
	x86_syslog_smplock_release(was);
}



PRIVATE ATTR_ALIGNED(1) char const level_prefix[][10] = {
	/* [SYSLOG_LEVEL_EMERG  ] = */ ":emerg ][",
	/* [SYSLOG_LEVEL_ALERT  ] = */ ":alert ][",
	/* [SYSLOG_LEVEL_CRIT   ] = */ ":crit  ][",
	/* [SYSLOG_LEVEL_ERR    ] = */ ":error ][",
	/* [SYSLOG_LEVEL_WARNING] = */ ":warn  ][",
	/* [SYSLOG_LEVEL_NOTICE ] = */ ":notice][",
	/* [SYSLOG_LEVEL_INFO   ] = */ ":info  ][",
	/* [SYSLOG_LEVEL_TRACE  ] = */ ":trace ][",
	/* [SYSLOG_LEVEL_DEBUG  ] = */ ":debug ][",
	/* [SYSLOG_LEVEL_DEFAULT] = */ ":output]["
};


#ifdef DBG_MONITOR_MEMORY
static struct atomic_rwlock monitor_memory_lock = ATOMIC_RWLOCK_INIT;
#endif /* DBG_MONITOR_MEMORY */


PRIVATE NOBLOCK void
NOTHROW(FCALL x86_syslog_sink_impl)(struct syslog_sink *__restrict UNUSED(self),
                                    struct syslog_packet const *__restrict packet,
                                    unsigned int level) {
	pflag_t was;
	/* Write to a debug port. */
	if (level < COMPILER_LENOF(level_prefix)) {
		char buf[64];
		struct tm t;
		size_t len;
		localtime_r(&packet->sp_time, &t);
#ifdef DBG_MONITOR_MEMORY
		if (vfs_kernel.p_inode && sync_trywrite(&monitor_memory_lock)) {
			pagedir_pushval_t pv;
			byte_t *addr = (byte_t *)0xc0000000 + (DBG_MONITOR_MEMORY & ~PAGEMASK);
			DBG_MONITOR_TYPE value;
			pv = pagedir_push_mapone(addr, (physaddr_t)(DBG_MONITOR_MEMORY & ~PAGEMASK), PAGEDIR_MAP_FREAD);
			pagedir_syncone(addr);
			value = *(DBG_MONITOR_TYPE volatile *)(0xc0000000 + DBG_MONITOR_MEMORY);
			pagedir_pop_mapone((void *)addr, pv);
			sync_endwrite(&monitor_memory_lock);
			len = sprintf(buf, "[" PP_STR(DBG_MONITOR_TYPE) "@%Ix=%#I16x]",
			              (uintptr_t)DBG_MONITOR_MEMORY, value);
			x86_syslog_write(buf, len);
		}
#endif /* DBG_MONITOR_MEMORY */

		/* Use ISO-8601-derived format (without the timezone; plus nanoseconds) */
		len = sprintf(buf, "[%.4u-%.2u-%.2uT%.2u:%.2u:%.2u.%.9" PRIu32 "%s%u] ",
		              t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		              t.tm_hour, t.tm_min, t.tm_sec,
		              packet->sp_nsec, level_prefix[level],
		              packet->sp_tid);
		if (packet->sp_msg[0] == '[')
			--len;
		x86_syslog_smplock_acquire(was);
		outsb(x86_syslog_port, buf, len);
	} else {
		x86_syslog_smplock_acquire(was);
	}
	outsb(x86_syslog_port, packet->sp_msg, packet->sp_len);
	x86_syslog_smplock_release(was);
}

/* The x86 hook for the arch-specific, default system log sink */
PUBLIC struct syslog_sink x86_default_syslog_sink = {
	/* .ss_refcnt = */ 2, /* +1: x86_default_syslog_sink, +1: <DEFAULT_SYSLOG_SINKS> */
	/* .ss_levels = */ (uintptr_t)-1,
	/* .ss_sink   = */ &x86_syslog_sink_impl,
	/* .ss_fini   = */ NULL
};


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_SYSLOG_C */
