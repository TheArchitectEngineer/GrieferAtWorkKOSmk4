/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_GDB_INFO_C
#define GUARD_MODGDBSERVER_GDB_INFO_C 1

#include "gdb-info.h"

#include <kernel/compiler.h>
#include <kernel/driver.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/vm.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/library.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <errno.h>
#include <format-printer.h>
#include <string.h>

#include "gdb.h"
#include "thread-enum.h"


DECL_BEGIN

#define DO(expr)    do{ if ((temp = (expr)) < 0) goto err; result += temp; }__WHILE0
#define PRINT(str)  DO((*printer)(arg, str, COMPILER_STRLEN(str)))
#define PRINTF(...) DO(format_printf(printer, arg, __VA_ARGS__))


/* NOTE: All of the following functions return negative ERRNO values on failure. */
/* Print a human-readable name for `thread' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadName)(pformatprinter printer, void *arg,
                                       struct task *__restrict thread) {
	ssize_t temp, result;
	pid_t pid, tid;
	result = GDBInfo_PrintThreadExecFile(printer, arg, thread, true);
	if unlikely(result < 0)
		goto done;
	pid = task_getrootpid_of_s(thread);
	tid = task_getroottid_of_s(thread);
	PRINT(" (");
	if (pid && tid && pid != tid)
		PRINTF("%u.%u:", pid, tid);
	else if (tid) {
		PRINTF("%u:", tid);
	}
	PRINTF("%p)", thread);
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintKernelFilename)(pformatprinter printer, void *arg,
                                           bool filename_only) {
	char const *str = filename_only
	                  ? kernel_driver.d_name
	                  : kernel_driver.d_filename;
	return (*printer)(arg, str, strlen(str));
}

/* `qXfer:exec-file:read': Print the absolute filename for the original
 * binary passed to exec() when the process of `thread' was started.
 * (`/proc/${PID_OF(thread)}/exe') */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadExecFile)(pformatprinter printer, void *arg,
                                           struct task *__restrict thread,
                                           bool filename_only) {
	ssize_t result;
	REF struct vm *v;
	REF struct directory_entry *dent;
	REF struct path            *path;
	if (task_getrootpid_of_s(thread) == 0 ||
	    task_getroottid_of_s(thread) == 0)
		return GDBInfo_PrintKernelFilename(printer, arg, filename_only);
	v = task_getvm(thread);
	if (v == &vm_kernel)
		result = GDBInfo_PrintKernelFilename(printer, arg, filename_only);
	else {
		/* FIXME: What if one of the suspended threads is holding the VM lock?
		 *        We should have some kind of timeout here, and switch to all-stop
		 *        mode if the timeout expires. */
		if (GDBThread_IsAllStopModeActive) {
			dent = xincref(FORVM(v, vm_execinfo).ei_dent);
			path = xincref(FORVM(v, vm_execinfo).ei_path);
		} else {
			sync_read(v);
			dent = xincref(FORVM(v, vm_execinfo).ei_dent);
			path = xincref(FORVM(v, vm_execinfo).ei_path);
			sync_endread(v);
		}
		if (filename_only && (dent || path)) {
			result = dent ? (*printer)(arg, dent->de_name, dent->de_namelen)
			              : (*printer)(arg, "?", 1);
			xdecref_unlikely(path);
			xdecref_unlikely(dent);
		} else if (dent && path) {
			result = path_printentex(path, dent, printer, arg,
			                         PATH_PRINT_MODE_NORMAL,
			                         &vfs_kernel);
			decref_unlikely(path);
			decref_unlikely(dent);
		} else if (path) {
			result = path_printex(path, printer, arg,
			                      PATH_PRINT_MODE_INCTRAIL,
			                      &vfs_kernel);
			if likely(result >= 0) {
				ssize_t temp;
				temp = (*printer)(arg, "?", 1);
				if unlikely(temp < 0)
					result = temp;
				else {
					result += temp;
				}
			}
			decref_unlikely(path);
		} else if (dent) {
			result = (*printer)(arg,"/?/", 3);
			if likely(result >= 0) {
				ssize_t temp;
				temp = (*printer)(arg,
				                  dent->de_name,
				                  dent->de_namelen);
				if unlikely(temp < 0)
					result = temp;
				else {
					result += temp;
				}
			}
			decref_unlikely(dent);
		} else if (thread == &_boottask) {
			/* Workaround for early-boot (before the initial user-space exec()) */
			result = GDBInfo_PrintKernelFilename(printer, arg,
			                                     filename_only);
		} else {
			result = (*printer)(arg, "?", 1);
		}
	}
	decref_unlikely(v);
	return result;
}


PRIVATE NONNULL((1, 3)) ssize_t KCALL
GDB_PrintRemoteVMString(pformatprinter printer, void *arg,
                        struct vm *__restrict effective_vm,
                        USER CHECKED char const *string,
                        bool print_repr) {
	char buf[256];
	size_t temp, result = 0;
	size_t pagesize = pagedir_pagesize_p(PAGEDIR_P_SELFOFVM(effective_vm));
	for (;;) {
		size_t partlen, maxread;
		/* Stay within the same page when reading memory. */
		maxread = pagesize - ((uintptr_t)string & (pagesize - 1));
		if (maxread > sizeof(buf))
			maxread = sizeof(buf);
		vm_read(buf, effective_vm, string, maxread, true);
		partlen = strnlen(buf, maxread);
		assert(partlen <= maxread);
		DO(print_repr ? format_escape(printer, arg, buf, partlen, FORMAT_ESCAPE_FPRINTRAW)
		              : (*printer)(arg, buf, partlen));
		if (partlen < maxread)
			break;
		string += maxread;
	}
	return result;
err:
	return temp;
}

typedef struct {
	pformatprinter ll_printer; /* Printer. */
	void          *ll_arg;     /* Printer argument. */
} GDB_LibraryListPrinterData;

PRIVATE NONNULL((1, 2)) ssize_t KCALL
GDB_LibraryListPrinter(void *closure,
                       struct vm *__restrict effective_vm,
                       USER CHECKED char const *filename,
                       USER UNCHECKED void *UNUSED(loadaddr),
                       USER UNCHECKED void *loadstart,
                       bool UNUSED(filename_may_be_relative)) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	printer = ((GDB_LibraryListPrinterData *)closure)->ll_printer;
	arg     = ((GDB_LibraryListPrinterData *)closure)->ll_arg;
	PRINT("<library name=\"");
	TRY {
		DO(GDB_PrintRemoteVMString(printer, arg, effective_vm, filename, true));
	} EXCEPT {
	}
	PRINTF("\">"
	           "<segment address=\"%#Ix\"/>"
	       "</library>",
	       loadstart);
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintKernelDriverList)(pformatprinter printer, void *arg) {
	size_t i; ssize_t temp, result = 0;
	REF struct driver_state *state;
	state = driver_get_state();
	for (i = 0; i < state->ds_count; ++i) {
		struct driver *d = state->ds_drivers[i];
		Elf_Half j;
		size_t lowest_segment_offset;
		size_t alignment_offset;
		/* One would expect that GDB wants `d_loadaddr', but that is incorrect.
		 * One might also thing that GDB wants `d_loadstart', and that is ~mostly~ correct.
		 * But what GDB actually wants is the absolute address of the first segment, meaning
		 * we need to adjust the driver load address for the sub-page offset of the segment
		 * with the lowest vaddr offset. */
		alignment_offset      = 0;
		lowest_segment_offset = (size_t)-1;
		assert(d->d_phnum != 0);
		for (j = 0; j < d->d_phnum; ++j) {
			if (d->d_phdr[j].p_type != PT_LOAD)
				continue;
			if (d->d_phdr[j].p_offset >= lowest_segment_offset)
				continue;
			lowest_segment_offset = d->d_phdr[j].p_offset;
			alignment_offset      = lowest_segment_offset & (PAGESIZE - 1);
		}
		if (d->d_filename) {
			PRINTF("<library name=\"%#q\">", d->d_filename);
		} else {
			REF struct driver_library_path_string *libpath;
			libpath = driver_library_path.get();
			if (!strrchr(libpath->dlp_path, ':')) {
				/* Only a single library path was defined.
				 * In this case, we can pretty much assume where the driver originates from. */
				size_t len;
				char const *path = libpath->dlp_path;
				while (*path == '/')
					++path;
				len = strlen(path);
				while (len && path[len - 1] == '/')
					--len;
				PRINTF("<library name=\"/%#$q/%#q\">", len, path, d->d_name);
				decref_unlikely(libpath);
			} else {
				decref_unlikely(libpath);
				PRINTF("<library name=\"%#q\">", d->d_name);
			}
		}
		PRINTF("<segment address=\"%#Ix\"/>"
		       "</library>",
		       d->d_loadstart + alignment_offset);
	}
	decref_unlikely(state);
	return result;
err:
	decref_unlikely(state);
	return temp;
}


/* `qXfer:libraries:read': Print the list of library loaded into the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintLibraryList)(pformatprinter printer, void *arg,
                                        struct task *__restrict thread) {
	ssize_t result;
	REF struct vm *v = task_getvm(thread);
	result = GDBInfo_PrintVMLibraryList(printer, arg, v);
	decref_unlikely(v);
	return result;
}
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintVMLibraryList)(pformatprinter printer, void *arg,
                                          struct vm *__restrict effective_vm) {
	ssize_t temp, result = 0;
	GDB_LibraryListPrinterData data;
	data.ll_printer = printer;
	data.ll_arg     = arg;
	PRINTF("<?xml version=\"1.0\"?>"
	       "<!DOCTYPE target SYSTEM \"library-list.dtd\">"
	       "<library-list>"
	           "<library name=%q>"
	               "<segment address=\"%#Ix\"/>"
	           "</library>",
	       kernel_driver.d_filename,
	       kernel_driver.d_loadstart);
	DO(GDBInfo_PrintKernelDriverList(printer, arg));
	/* Print user-space library listings. */
	if (effective_vm != &vm_kernel) {
		TRY {
			DO(vm_library_enumerate(effective_vm, &GDB_LibraryListPrinter, &data));
		} EXCEPT {
		}
	}
	PRINT("</library-list>");
	return result;
err:
	return temp;
}


struct GDBInfo_PrintThreadList_Data {
	pformatprinter ptld_printer;
	void          *ptld_arg;
};

INTDEF char *
NOTHROW(FCALL GDBThread_EncodeThreadID)(char *buf,
                                        struct task *__restrict thread);
#define GDBTHREAD_ENCODETHREADID_MAXCHARS 21 /* p-12345678.-12345678\0 */


PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList_Callback)(void *closure,
                                                struct task *__restrict thread) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	char id_buf[GDBTHREAD_ENCODETHREADID_MAXCHARS], *id_end;
	char const *description;
	uintptr_t flags;
	printer = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_printer;
	arg     = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_arg;
	id_end = GDBThread_EncodeThreadID(id_buf, thread);
	assert((size_t)(id_end - id_buf) < GDBTHREAD_ENCODETHREADID_MAXCHARS);
	PRINTF("<thread id=\"%$s\" core=\"%u\" name=\"",
	       (size_t)(id_end - id_buf), id_buf,
	       thread->t_cpu->c_id);
	DO(GDBInfo_PrintThreadName(printer, arg, thread));
	flags = ATOMIC_READ(thread->t_flags);
	if (flags & TASK_FTERMINATED)
		description = "terminated";
	else if (flags & TASK_FTERMINATING)
		description = "terminating";
	else if (thread == &FORCPU(thread->t_cpu, _this_idle))
		description = "idle";
	else if (flags & TASK_FRUNNING)
		description = "running";
	else {
		description = "?";
	}
	PRINTF("\">%s</thread>", description);
	return result;
err:
	return temp;
}


/* `qXfer:threads:read': Print the list of threads apart of the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList)(pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	struct GDBInfo_PrintThreadList_Data data;
	PRINT("<?xml version=\"1.0\"?>"
	      "<threads>");
	data.ptld_printer = printer;
	data.ptld_arg     = arg;
	DO(GDBThread_Enumerate(&GDBInfo_PrintThreadList_Callback, &data));
	PRINT("</threads>");
	return result;
err:
	return temp;
}


/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintProcessList)(pformatprinter printer, void *arg) {
	return -ENOSYS;
}




#ifdef __x86_64__
#elif defined(__i386__)
#define HAVE_GDBFeatures_target_xml 1
STATIC_ASSERT(GDB_REGISTER_I386_FSBASE == 48);
STATIC_ASSERT(GDB_REGISTER_I386_GSBASE == 49);
PRIVATE char const GDBFeatures_target_xml[] =
"<?xml version=\"1.0\"?>"
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
	"<architecture>i386</architecture>"
//	"<osabi>KOS</osabi>"
	"<xi:include href=\"32bit-core.xml\"/>"
	"<xi:include href=\"32bit-sse.xml\"/>"
	"<feature name=\"de.gdb.i386.kos\">"
		"<reg name=\"fs_base\" bitsize=\"32\" type=\"int\" regnum=\"48\"/>" /* GDB_REGISTER_I386_FSBASE */
		"<reg name=\"gs_base\" bitsize=\"32\" type=\"int\" regnum=\"49\"/>" /* GDB_REGISTER_I386_GSBASE */
	"</feature>"
"</target>"
;
#endif /* !__x86_64__ */


/* `qXfer:features:read': Print the named features file `filename' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintFeaturesFile)(pformatprinter printer, void *arg,
                                         char const *__restrict filename) {
#ifdef HAVE_GDBFeatures_target_xml
	if (strcmp(filename, "target.xml") == 0)
		return (*printer)(arg, GDBFeatures_target_xml, COMPILER_STRLEN(GDBFeatures_target_xml));
#endif /* HAVE_GDBFeatures_target_xml */
	return -ENOENT;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_GDB_INFO_C */
