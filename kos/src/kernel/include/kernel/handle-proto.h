/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/io.h>

DECL_BEGIN

#ifdef __DEEMON__
#define HANDLE_OPERATOR_PROTOTYPES                                                                            \
	{                                                                                                         \
		("refcnt", "NOBLOCK WUNUSED NONNULL((1))", "refcnt_t", "NOTHROW", "FCALL",                            \
		 { ("T const *__restrict", "self") },                                                                 \
		 "", "return 0;"),                                                                                    \
		("incref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                        \
		 { ("T *__restrict", "self") },                                                                       \
		 "", ""),                                                                                             \
		("decref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                        \
		 { ("REF T *__restrict", "self") },                                                                   \
		 "", ""),                                                                                             \
		("tryincref", "NOBLOCK WUNUSED NONNULL((1))", "__BOOL", "NOTHROW", "FCALL",                           \
		 { ("T *__restrict", "self") },                                                                       \
		 "", "return 1;"),                                                                                    \
		("weakgetref", "NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1))", "WEAK REF void *", "NOTHROW", "FCALL", \
		 { ("T *__restrict", "self") },                                                                       \
		 "", "return self;"),                                                                                 \
		("weaklckref", "NOBLOCK WUNUSED NONNULL((1))", "REF T *", "NOTHROW", "FCALL",                         \
		 { ("void *__restrict", "weakref_ptr") },                                                             \
		 "", "return NULL;"),                                                                                 \
		("weakdecref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                    \
		 { ("WEAK REF void *__restrict", "weakref_ptr") },                                                    \
		 "", ""),                                                                                             \
		("read", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                               \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("write", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                              \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("pread", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                              \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("pwrite", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("readv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                           \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("writev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                          \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("preadv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                          \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("pwritev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("readdir", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                            \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct dirent *", "buf"),                                                           \
		   ("size_t", "bufsize"),                                                                             \
		   ("readdir_mode_t", "readdir_mode"),                                                                \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR);"),                          \
		("seek", "NONNULL((1))", "pos_t", "", "KCALL",                                                        \
		 { ("T *__restrict", "self"),                                                                         \
		   ("off_t", "offset"),                                                                               \
		   ("unsigned int", "whence") },                                                                      \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK);"),                             \
		("ioctl", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("syscall_ulong_t", "cmd"),                                                                        \
		   ("USER UNCHECKED void *", "arg"),                                                                  \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd);"),        \
		("truncate", "NONNULL((1))", "void", "", "KCALL",                                                     \
		 { ("T *__restrict", "self"),                                                                         \
		   ("pos_t", "new_size") },                                                                           \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);"),                            \
		("mmap", "NONNULL((1, 2))", "void", "", "KCALL",                                                      \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct handle_mmap_info *__restrict", "info") },                                                 \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP);"),                             \
		("allocate", "NONNULL((1))", "pos_t", "", "KCALL",                                                    \
		 { ("T *__restrict", "self"),                                                                         \
		   ("fallocate_mode_t", "mode"),                                                                      \
		   ("pos_t", "start"),                                                                                \
		   ("pos_t", "length") },                                                                             \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE);"),                         \
		("sync", "NONNULL((1))", "void", "", "KCALL",                                                         \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC);"),                             \
		("datasync", "NONNULL((1))", "void", "", "KCALL",                                                     \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC);"),                         \
		("stat", "NONNULL((1))", "void", "", "KCALL",                                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct stat *", "result") },                                                        \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT);"),                             \
		("pollconnect", "NONNULL((1))", "void", "", "KCALL",                                                  \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);"),                             \
		("polltest", "WUNUSED NONNULL((1))", "poll_mode_t", "", "KCALL",                                      \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);"),                             \
		("hop", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                               \
		 { ("T *__restrict", "self"),                                                                         \
		   ("syscall_ulong_t", "cmd"),                                                                        \
		   ("USER UNCHECKED void *", "arg"),                                                                  \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd);"),          \
		("tryas", "NONNULL((1))", "REF void *", "", "KCALL",                                                  \
		 { ("T *__restrict", "self"),                                                                         \
		   ("uintptr_half_t", "wanted_type") },                                                               \
		 "THROWS(E_WOULDBLOCK)",                                                                              \
		 "return NULL;"),                                                                                     \
	}
#endif /* __DEEMON__ */

/* Prototypes for handle operators. */

/*[[[deemon
import util;
import * from deemon;

@@List of (name, type)
local handle_types: {(string, string)...} = [];

function injectObjectType(type_expr: string, typename: string): string {
	if (!typename) typename = "void";
	switch (type_expr) {
	case "T *":                    return typename + " *";
	case "T *__restrict":          return typename + " *__restrict";
	case "T const *":              return typename + " const *";
	case "T const *__restrict":    return typename + " const *__restrict";
	case "REF T *":                return "REF " + typename + " *";
	case "REF T *__restrict":      return "REF " + typename + " *__restrict";
	case "WEAK REF T *":           return "WEAK REF " + typename + " *";
	case "WEAK REF T *__restrict": return "WEAK REF " + typename + " *__restrict";
	default: break;
	}
	return type_expr;
}

for (local l: File.open("../../../../include/kos/kernel/handle.h")) {
	local name, id, tail;
	try name, id, tail = l.scanf(" # define HANDLE_TYPE_%[^ ] %[^ /] %[^]")...;
	catch (...) continue;
	if (name == "COUNT")
		continue;
	id = int(id);
	if (id >= #handle_types)
		handle_types.resize(id + 1, ("undefined", ""));
	tail = try tail.scanf(" /" "* `%[^']")[0] catch (...) "";
	handle_types[id] = (name.lower(), tail);
}

#define ARGS   name,attr,return_type,nothrow,cc,argv,throws,default_impl
local ops = HANDLE_OPERATOR_PROTOTYPES;

print "#ifdef CONFIG_BUILDING_KERNEL_CORE";
print "#ifdef __CC__";
{
	local knownTypes = HashSet();
	for (local name, typ: handle_types) {
		if (!typ || typ in knownTypes)
			continue;
		if (!typ.startswith("struct"))
			continue;
		print typ,;
		print ";";
		knownTypes.insert(typ);
	}
}

print;
print;
print;
for (local h_name, h_typ: handle_types) {
	if (h_name in ["undefined"])
		continue;
	print "/" "* Handle operators for `HANDLE_TYPE_",;
	print h_name.upper(),;
	print "'",;
	if (h_typ) {
		print " (`",;
		print h_typ,;
		print "')",;
	}
	print " *" "/";
	for (local ARGS: ops) {
		print "INTDEF ",;
		if (attr) {
			print attr,;
			print " ",;
		}
		return_type = injectObjectType(return_type, h_typ);
		print return_type,;
		if (!return_type.endswith("*"))
			print " ",;
		print nothrow,;
		if (nothrow)
			print "(",;
		print cc, "handle_",;
		print h_name,;
		print "_",;
		print name,;
		if (nothrow)
			print ")",;
		print "(",;
		local is_first = true;
		for (local t, n: argv) {
			t = injectObjectType(t, h_typ);
			if (!is_first)
				print ", ",;
			print t,;
			if (!t.endswith("*"))
				print " ",;
			print n,;
			is_first = false;
		}
		print ")",;
		if (throws) {
			print " ",;
			print throws,;
		}
		print ";";
	}
	print;
}
print "#endif /" "* __CC__ *" "/";
print "#endif /" "* CONFIG_BUILDING_KERNEL_CORE *" "/";

]]]*/
#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __CC__
struct vm_datablock;
struct basic_block_device;
struct directory_entry;
struct file;
struct oneshot_directory_file;
struct path;
struct fs;
struct vm;
struct taskpid;
struct epoll_controller;
struct driver;
struct pipe;
struct pipe_reader;
struct pipe_writer;
struct pidns;
struct driver_state;
struct character_device;
struct eventfd;
struct signalfd;
struct vm_datapart;
struct vm_futex;
struct vm_futexfd;
struct driver_section;
struct socket;
struct uaio_controller;
struct fifo_user;



/* Handle operators for `HANDLE_TYPE_DATABLOCK' (`struct vm_datablock') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_datablock_refcnt)(struct vm_datablock const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datablock_incref)(struct vm_datablock *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datablock_decref)(REF struct vm_datablock *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_datablock_tryincref)(struct vm_datablock *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_datablock_weakgetref)(struct vm_datablock *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct vm_datablock *NOTHROW(FCALL handle_datablock_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datablock_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_read(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_write(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_pread(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_pwrite(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_readv(struct vm_datablock *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_writev(struct vm_datablock *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_preadv(struct vm_datablock *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_pwritev(struct vm_datablock *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_readdir(struct vm_datablock *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datablock_seek(struct vm_datablock *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datablock_ioctl(struct vm_datablock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_truncate(struct vm_datablock *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_dataQblock_mmap(struct vm_datablock *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datablock_allocate(struct vm_datablock *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_sync(struct vm_datablock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_datasync(struct vm_datablock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_stat(struct vm_datablock *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_pollconnect(struct vm_datablock *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_datablock_polltest(struct vm_datablock *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datablock_hop(struct vm_datablock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_datablock_tryas(struct vm_datablock *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_BLOCKDEVICE' (`struct basic_block_device') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_blockdevice_refcnt)(struct basic_block_device const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_incref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_decref)(REF struct basic_block_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_blockdevice_tryincref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_blockdevice_weakgetref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct basic_block_device *NOTHROW(FCALL handle_blockdevice_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_read(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_write(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pread(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pwrite(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_readv(struct basic_block_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_writev(struct basic_block_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_preadv(struct basic_block_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_pwritev(struct basic_block_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_readdir(struct basic_block_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_seek(struct basic_block_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_ioctl(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_truncate(struct basic_block_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_blockdevice_mmap(struct basic_block_device *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_allocate(struct basic_block_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_sync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_datasync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_stat(struct basic_block_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_pollconnect(struct basic_block_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_blockdevice_polltest(struct basic_block_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_hop(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_blockdevice_tryas(struct basic_block_device *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DIRECTORYENTRY' (`struct directory_entry') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_directoryentry_refcnt)(struct directory_entry const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_incref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_decref)(REF struct directory_entry *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_directoryentry_tryincref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_directoryentry_weakgetref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct directory_entry *NOTHROW(FCALL handle_directoryentry_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_read(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_write(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pread(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pwrite(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_readv(struct directory_entry *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_writev(struct directory_entry *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_preadv(struct directory_entry *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_pwritev(struct directory_entry *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_readdir(struct directory_entry *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_seek(struct directory_entry *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_ioctl(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_truncate(struct directory_entry *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_directoryentry_mmap(struct directory_entry *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_allocate(struct directory_entry *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_sync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_datasync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_stat(struct directory_entry *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_pollconnect(struct directory_entry *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_directoryentry_polltest(struct directory_entry *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_hop(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_directoryentry_tryas(struct directory_entry *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FILE' (`struct file') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_file_refcnt)(struct file const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_incref)(struct file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_decref)(REF struct file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_file_tryincref)(struct file *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_file_weakgetref)(struct file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct file *NOTHROW(FCALL handle_file_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_read(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_write(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pread(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pwrite(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_readv(struct file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_writev(struct file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_preadv(struct file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_pwritev(struct file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_readdir(struct file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_seek(struct file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_ioctl(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_truncate(struct file *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_file_mmap(struct file *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_allocate(struct file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_sync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_datasync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_stat(struct file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_pollconnect(struct file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_file_polltest(struct file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_hop(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_file_tryas(struct file *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_ONESHOT_DIRECTORY_FILE' (`struct oneshot_directory_file') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_oneshot_directory_file_refcnt)(struct oneshot_directory_file const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_incref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_decref)(REF struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_oneshot_directory_file_tryincref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_oneshot_directory_file_weakgetref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct oneshot_directory_file *NOTHROW(FCALL handle_oneshot_directory_file_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_read(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_write(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pread(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pwrite(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_readv(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_writev(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_preadv(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_pwritev(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_readdir(struct oneshot_directory_file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_seek(struct oneshot_directory_file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_ioctl(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_truncate(struct oneshot_directory_file *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_oneshot_directory_file_mmap(struct oneshot_directory_file *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_allocate(struct oneshot_directory_file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_sync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_datasync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_stat(struct oneshot_directory_file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_pollconnect(struct oneshot_directory_file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_oneshot_directory_file_polltest(struct oneshot_directory_file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_hop(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_oneshot_directory_file_tryas(struct oneshot_directory_file *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PATH' (`struct path') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_path_refcnt)(struct path const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_incref)(struct path *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_decref)(REF struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_path_tryincref)(struct path *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_path_weakgetref)(struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct path *NOTHROW(FCALL handle_path_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_read(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_write(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pwrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_readv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_writev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_preadv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_pwritev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_readdir(struct path *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_seek(struct path *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_ioctl(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_truncate(struct path *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_path_mmap(struct path *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_allocate(struct path *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_sync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_datasync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_stat(struct path *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_pollconnect(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_path_polltest(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_hop(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_path_tryas(struct path *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FS' (`struct fs') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fs_refcnt)(struct fs const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_incref)(struct fs *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_decref)(REF struct fs *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_fs_tryincref)(struct fs *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_fs_weakgetref)(struct fs *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fs *NOTHROW(FCALL handle_fs_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_read(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_write(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pread(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pwrite(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_readv(struct fs *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_writev(struct fs *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_preadv(struct fs *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_pwritev(struct fs *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_readdir(struct fs *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_seek(struct fs *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_ioctl(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_truncate(struct fs *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_fs_mmap(struct fs *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_allocate(struct fs *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_sync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_datasync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_stat(struct fs *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_pollconnect(struct fs *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fs_polltest(struct fs *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_hop(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_fs_tryas(struct fs *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_VM' (`struct vm') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_vm_refcnt)(struct vm const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_vm_incref)(struct vm *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_vm_decref)(REF struct vm *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_vm_tryincref)(struct vm *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_vm_weakgetref)(struct vm *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct vm *NOTHROW(FCALL handle_vm_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_vm_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_read(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_write(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_pread(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_pwrite(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_readv(struct vm *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_writev(struct vm *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_preadv(struct vm *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_pwritev(struct vm *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_readdir(struct vm *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_vm_seek(struct vm *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_vm_ioctl(struct vm *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_truncate(struct vm *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_vm_mmap(struct vm *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_vm_allocate(struct vm *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_sync(struct vm *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_datasync(struct vm *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_stat(struct vm *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_pollconnect(struct vm *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_vm_polltest(struct vm *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_vm_hop(struct vm *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_vm_tryas(struct vm *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_TASK' (`struct taskpid') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_task_refcnt)(struct taskpid const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_incref)(struct taskpid *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_decref)(REF struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_task_tryincref)(struct taskpid *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_task_weakgetref)(struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(FCALL handle_task_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_read(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_write(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pwrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_readv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_writev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_preadv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_pwritev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_readdir(struct taskpid *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_seek(struct taskpid *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_ioctl(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_truncate(struct taskpid *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_task_mmap(struct taskpid *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_allocate(struct taskpid *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_sync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_datasync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_stat(struct taskpid *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_pollconnect(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_task_polltest(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_hop(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_task_tryas(struct taskpid *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EPOLL' (`struct epoll_controller') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_epoll_refcnt)(struct epoll_controller const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_incref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_decref)(REF struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_epoll_tryincref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_epoll_weakgetref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct epoll_controller *NOTHROW(FCALL handle_epoll_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_read(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_write(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_pread(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_pwrite(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_readv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_writev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_preadv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_pwritev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_readdir(struct epoll_controller *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_epoll_seek(struct epoll_controller *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_epoll_ioctl(struct epoll_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_truncate(struct epoll_controller *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_epoll_mmap(struct epoll_controller *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_epoll_allocate(struct epoll_controller *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_sync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_datasync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_stat(struct epoll_controller *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_pollconnect(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_epoll_polltest(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_epoll_hop(struct epoll_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_epoll_tryas(struct epoll_controller *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DRIVER' (`struct driver') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_refcnt)(struct driver const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_incref)(struct driver *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_decref)(REF struct driver *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_tryincref)(struct driver *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_driver_weakgetref)(struct driver *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver *NOTHROW(FCALL handle_driver_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_read(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_write(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_pread(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_pwrite(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_readv(struct driver *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_writev(struct driver *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_preadv(struct driver *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_pwritev(struct driver *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_readdir(struct driver *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_seek(struct driver *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_ioctl(struct driver *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_truncate(struct driver *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_driver_mmap(struct driver *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_allocate(struct driver *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_sync(struct driver *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_datasync(struct driver *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_stat(struct driver *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_pollconnect(struct driver *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_polltest(struct driver *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_hop(struct driver *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_driver_tryas(struct driver *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_refcnt)(struct pipe const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_incref)(struct pipe *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_decref)(REF struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_tryincref)(struct pipe *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_weakgetref)(struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe *NOTHROW(FCALL handle_pipe_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_read(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_write(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pwrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_readv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_preadv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_pwritev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_readdir(struct pipe *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_seek(struct pipe *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_ioctl(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_truncate(struct pipe *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_mmap(struct pipe *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_allocate(struct pipe *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_sync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_datasync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_stat(struct pipe *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_pollconnect(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_polltest(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_hop(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_tryas(struct pipe *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_reader_refcnt)(struct pipe_reader const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_incref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_decref)(REF struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_reader_tryincref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_reader_weakgetref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_reader *NOTHROW(FCALL handle_pipe_reader_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_read(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_write(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pwrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_readv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_writev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_preadv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_pwritev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_readdir(struct pipe_reader *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_seek(struct pipe_reader *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_ioctl(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_truncate(struct pipe_reader *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_reader_mmap(struct pipe_reader *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_allocate(struct pipe_reader *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_sync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_datasync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_stat(struct pipe_reader *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_pollconnect(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_reader_polltest(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_hop(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_reader_tryas(struct pipe_reader *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_writer_refcnt)(struct pipe_writer const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_incref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_decref)(REF struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_writer_tryincref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_writer_weakgetref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_writer *NOTHROW(FCALL handle_pipe_writer_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_read(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_write(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pwrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_readv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_writev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_preadv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_pwritev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_readdir(struct pipe_writer *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_seek(struct pipe_writer *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_ioctl(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_truncate(struct pipe_writer *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_writer_mmap(struct pipe_writer *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_allocate(struct pipe_writer *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_sync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_datasync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_stat(struct pipe_writer *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_pollconnect(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_writer_polltest(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_hop(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_writer_tryas(struct pipe_writer *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIDNS' (`struct pidns') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pidns_refcnt)(struct pidns const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_incref)(struct pidns *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_decref)(REF struct pidns *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pidns_tryincref)(struct pidns *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pidns_weakgetref)(struct pidns *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pidns *NOTHROW(FCALL handle_pidns_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_read(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_write(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pread(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pwrite(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_readv(struct pidns *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_writev(struct pidns *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_preadv(struct pidns *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_pwritev(struct pidns *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_readdir(struct pidns *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_seek(struct pidns *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_ioctl(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_truncate(struct pidns *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pidns_mmap(struct pidns *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_allocate(struct pidns *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_sync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_datasync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_stat(struct pidns *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_pollconnect(struct pidns *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pidns_polltest(struct pidns *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_hop(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pidns_tryas(struct pidns *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DRIVER_STATE' (`struct driver_state') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_state_refcnt)(struct driver_state const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_state_incref)(struct driver_state *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_state_decref)(REF struct driver_state *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_state_tryincref)(struct driver_state *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_driver_state_weakgetref)(struct driver_state *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver_state *NOTHROW(FCALL handle_driver_state_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_state_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_read(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_write(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_pread(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_pwrite(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_readv(struct driver_state *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_writev(struct driver_state *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_preadv(struct driver_state *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_pwritev(struct driver_state *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_readdir(struct driver_state *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_state_seek(struct driver_state *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_state_ioctl(struct driver_state *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_truncate(struct driver_state *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_driver_state_mmap(struct driver_state *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_state_allocate(struct driver_state *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_sync(struct driver_state *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_datasync(struct driver_state *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_stat(struct driver_state *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_pollconnect(struct driver_state *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_state_polltest(struct driver_state *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_state_hop(struct driver_state *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_driver_state_tryas(struct driver_state *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_CHARACTERDEVICE' (`struct character_device') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_characterdevice_refcnt)(struct character_device const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_incref)(struct character_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_decref)(REF struct character_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_characterdevice_tryincref)(struct character_device *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_characterdevice_weakgetref)(struct character_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct character_device *NOTHROW(FCALL handle_characterdevice_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_write(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pwrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_readv(struct character_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_writev(struct character_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_preadv(struct character_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_pwritev(struct character_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_readdir(struct character_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_seek(struct character_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_truncate(struct character_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_characterdevice_mmap(struct character_device *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_allocate(struct character_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_sync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_datasync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_pollconnect(struct character_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_characterdevice_polltest(struct character_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_hop(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_characterdevice_tryas(struct character_device *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_fence_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_fence_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_fence_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_fence_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_eventfd_fence_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_fence_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_eventfd_fence_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_sema_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_sema_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_sema_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_sema_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_eventfd_sema_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_sema_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_eventfd_sema_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_signalfd_refcnt)(struct signalfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_incref)(struct signalfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_decref)(REF struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_signalfd_tryincref)(struct signalfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_signalfd_weakgetref)(struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct signalfd *NOTHROW(FCALL handle_signalfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_read(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_write(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pwrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_readv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_writev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_preadv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_pwritev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_readdir(struct signalfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_seek(struct signalfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_ioctl(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_truncate(struct signalfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_signalfd_mmap(struct signalfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_allocate(struct signalfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_sync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_datasync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_stat(struct signalfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_pollconnect(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_signalfd_polltest(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_hop(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_signalfd_tryas(struct signalfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DATAPART' (`struct vm_datapart') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_datapart_refcnt)(struct vm_datapart const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datapart_incref)(struct vm_datapart *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datapart_decref)(REF struct vm_datapart *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_datapart_tryincref)(struct vm_datapart *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_datapart_weakgetref)(struct vm_datapart *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct vm_datapart *NOTHROW(FCALL handle_datapart_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datapart_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_read(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_write(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_pread(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_pwrite(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_readv(struct vm_datapart *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_writev(struct vm_datapart *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_preadv(struct vm_datapart *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_pwritev(struct vm_datapart *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_readdir(struct vm_datapart *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datapart_seek(struct vm_datapart *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datapart_ioctl(struct vm_datapart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_truncate(struct vm_datapart *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_datapart_mmap(struct vm_datapart *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datapart_allocate(struct vm_datapart *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_sync(struct vm_datapart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_datasync(struct vm_datapart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_stat(struct vm_datapart *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_pollconnect(struct vm_datapart *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_datapart_polltest(struct vm_datapart *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datapart_hop(struct vm_datapart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_datapart_tryas(struct vm_datapart *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FUTEX' (`struct vm_futex') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futex_refcnt)(struct vm_futex const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_incref)(struct vm_futex *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_decref)(REF struct vm_futex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_futex_tryincref)(struct vm_futex *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_futex_weakgetref)(struct vm_futex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct vm_futex *NOTHROW(FCALL handle_futex_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_read(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_write(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pread(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pwrite(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_readv(struct vm_futex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_writev(struct vm_futex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_preadv(struct vm_futex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_pwritev(struct vm_futex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_readdir(struct vm_futex *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_seek(struct vm_futex *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_ioctl(struct vm_futex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_truncate(struct vm_futex *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_futex_mmap(struct vm_futex *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_allocate(struct vm_futex *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_sync(struct vm_futex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_datasync(struct vm_futex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_stat(struct vm_futex *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_pollconnect(struct vm_futex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futex_polltest(struct vm_futex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_hop(struct vm_futex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_futex_tryas(struct vm_futex *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FUTEXFD' (`struct vm_futexfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futexfd_refcnt)(struct vm_futexfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_incref)(struct vm_futexfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_decref)(REF struct vm_futexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_futexfd_tryincref)(struct vm_futexfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_futexfd_weakgetref)(struct vm_futexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct vm_futexfd *NOTHROW(FCALL handle_futexfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_read(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_write(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pread(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pwrite(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_readv(struct vm_futexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_writev(struct vm_futexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_preadv(struct vm_futexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_pwritev(struct vm_futexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_readdir(struct vm_futexfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_seek(struct vm_futexfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_ioctl(struct vm_futexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_truncate(struct vm_futexfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_futexfd_mmap(struct vm_futexfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_allocate(struct vm_futexfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_sync(struct vm_futexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_datasync(struct vm_futexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_stat(struct vm_futexfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_pollconnect(struct vm_futexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futexfd_polltest(struct vm_futexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_hop(struct vm_futexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_futexfd_tryas(struct vm_futexfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DRIVER_SECTION' (`struct driver_section') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_section_refcnt)(struct driver_section const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_section_incref)(struct driver_section *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_section_decref)(REF struct driver_section *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_section_tryincref)(struct driver_section *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_driver_section_weakgetref)(struct driver_section *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver_section *NOTHROW(FCALL handle_driver_section_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_section_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_read(struct driver_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_write(struct driver_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_pread(struct driver_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_pwrite(struct driver_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_readv(struct driver_section *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_writev(struct driver_section *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_preadv(struct driver_section *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_pwritev(struct driver_section *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_readdir(struct driver_section *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_section_seek(struct driver_section *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_section_ioctl(struct driver_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_truncate(struct driver_section *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_driver_section_mmap(struct driver_section *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_section_allocate(struct driver_section *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_sync(struct driver_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_datasync(struct driver_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_stat(struct driver_section *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_pollconnect(struct driver_section *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_section_polltest(struct driver_section *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_section_hop(struct driver_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_driver_section_tryas(struct driver_section *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_socket_refcnt)(struct socket const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_incref)(struct socket *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_decref)(REF struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_socket_tryincref)(struct socket *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_socket_weakgetref)(struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct socket *NOTHROW(FCALL handle_socket_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_read(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_write(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pread(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pwrite(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_readv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_writev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_preadv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_pwritev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_readdir(struct socket *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_seek(struct socket *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_ioctl(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_truncate(struct socket *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_socket_mmap(struct socket *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_allocate(struct socket *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_sync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_datasync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_stat(struct socket *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_pollconnect(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_socket_polltest(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_hop(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_socket_tryas(struct socket *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_UAIO' (`struct uaio_controller') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_uaio_refcnt)(struct uaio_controller const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_incref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_decref)(REF struct uaio_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_uaio_tryincref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_uaio_weakgetref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct uaio_controller *NOTHROW(FCALL handle_uaio_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_read(struct uaio_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_write(struct uaio_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_pread(struct uaio_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_pwrite(struct uaio_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_readv(struct uaio_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_writev(struct uaio_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_preadv(struct uaio_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_pwritev(struct uaio_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_readdir(struct uaio_controller *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_uaio_seek(struct uaio_controller *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_uaio_ioctl(struct uaio_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_truncate(struct uaio_controller *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_uaio_mmap(struct uaio_controller *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_uaio_allocate(struct uaio_controller *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_sync(struct uaio_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_datasync(struct uaio_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_stat(struct uaio_controller *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_pollconnect(struct uaio_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_uaio_polltest(struct uaio_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_uaio_hop(struct uaio_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_uaio_tryas(struct uaio_controller *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FIFO_USER' (`struct fifo_user') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fifo_user_refcnt)(struct fifo_user const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_incref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_decref)(REF struct fifo_user *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_fifo_user_tryincref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_fifo_user_weakgetref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fifo_user *NOTHROW(FCALL handle_fifo_user_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_read(struct fifo_user *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_write(struct fifo_user *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_pread(struct fifo_user *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_pwrite(struct fifo_user *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_readv(struct fifo_user *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_writev(struct fifo_user *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_preadv(struct fifo_user *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_pwritev(struct fifo_user *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_readdir(struct fifo_user *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fifo_user_seek(struct fifo_user *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fifo_user_ioctl(struct fifo_user *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_truncate(struct fifo_user *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_fifo_user_mmap(struct fifo_user *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fifo_user_allocate(struct fifo_user *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_sync(struct fifo_user *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_datasync(struct fifo_user *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_stat(struct fifo_user *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_pollconnect(struct fifo_user *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fifo_user_polltest(struct fifo_user *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fifo_user_hop(struct fifo_user *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_fifo_user_tryas(struct fifo_user *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */
//[[[end]]]




#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __CC__

/* `name' must be the lower-case form of the `*' in one of the `HANDLE_TYPE_*' macros.
 * `T' must be the actual object type (one implementing the refcnt protocol or deriving from another that does) */
#define DEFINE_HANDLE_REFCNT_FUNCTIONS(name, T)                                  \
	INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t                                 \
	NOTHROW(FCALL handle_##name##_refcnt)(T const *__restrict self) {            \
		return getrefcnt(self);                                                  \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) WEAK REF void *                                  \
	NOTHROW(FCALL handle_##name##_weakgetref)(T *__restrict self) {              \
		return incref(self);                                                     \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) void                                             \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {              \
		decref(self);                                                            \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) __BOOL                                           \
	NOTHROW(FCALL handle_##name##_tryincref)(T *__restrict self) {               \
		return tryincref(self);                                                  \
	}                                                                            \
	DEFINE_INTERN_ALIAS(handle_##name##_incref, handle_##name##_weakgetref);     \
	DEFINE_INTERN_ALIAS(handle_##name##_weaklckref, handle_##name##_weakgetref); \
	DEFINE_INTERN_ALIAS(handle_##name##_weakdecref, handle_##name##_decref)


/* Same as `DEFINE_HANDLE_REFCNT_FUNCTIONS', but include dedicated weak referencing support
 * in terms of `weakincref()'  and friends. The regular  `DEFINE_HANDLE_REFCNT_FUNCTIONS()'
 * will implement those  functions in  terms of the  regular reference  counter, such  that
 * anyone  holding a weak reference is actually  holding a regular reference. This behavior
 * is ok in most  cases, however objects which  can exist as handles  and could be made  to
 * form reference  loops should  only ever  store  weak references  to other  handles,  and
 * should themself  have a  dedicated weakref  mechanism.  One example  of such  an  object
 * is `struct epoll_controller' * */
#define DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(name, T)            \
	INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t                                \
	NOTHROW(FCALL handle_##name##_refcnt)(T const *__restrict self) {           \
		return getrefcnt(self);                                                 \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_incref)(T *__restrict self) {                 \
		incref(self);                                                           \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {             \
		decref(self);                                                           \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) __BOOL                                          \
	NOTHROW(FCALL handle_##name##_tryincref)(T *__restrict self) {              \
		return tryincref(self);                                                 \
	}                                                                           \
	INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *         \
	NOTHROW(FCALL handle_##name##_weakgetref)(T *__restrict self) {             \
		return weakincref(self);                                                \
	}                                                                           \
	INTERN NOBLOCK WUNUSED NONNULL((1)) REF T *                                 \
	NOTHROW(FCALL handle_##name##_weaklckref)(void *__restrict weakref_ptr) {   \
		return tryincref((T *)weakref_ptr) ? (T *)weakref_ptr : __NULLPTR;      \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_weakdecref)(WEAK REF void *__restrict self) { \
		weakdecref((T *)self);                                                  \
	}

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#define HANDLE_TYPE_MFILE        HANDLE_TYPE_DATABLOCK
#define handle_mfile_refcnt      handle_datablock_refcnt
#define handle_mfile_incref      handle_datablock_incref
#define handle_mfile_decref      handle_datablock_decref
#define handle_mfile_tryincref   handle_datablock_tryincref
#define handle_mfile_weakgetref  handle_datablock_weakgetref
#define handle_mfile_weaklckref  handle_datablock_weaklckref
#define handle_mfile_weakdecref  handle_datablock_weakdecref
#define handle_mfile_read        handle_datablock_read
#define handle_mfile_write       handle_datablock_write
#define handle_mfile_pread       handle_datablock_pread
#define handle_mfile_pwrite      handle_datablock_pwrite
#define handle_mfile_readv       handle_datablock_readv
#define handle_mfile_writev      handle_datablock_writev
#define handle_mfile_preadv      handle_datablock_preadv
#define handle_mfile_pwritev     handle_datablock_pwritev
#define handle_mfile_readdir     handle_datablock_readdir
#define handle_mfile_seek        handle_datablock_seek
#define handle_mfile_ioctl       handle_datablock_ioctl
#define handle_mfile_truncate    handle_datablock_truncate
#define handle_mfile_mmap        handle_datablock_mmap
#define handle_mfile_allocate    handle_datablock_allocate
#define handle_mfile_sync        handle_datablock_sync
#define handle_mfile_datasync    handle_datablock_datasync
#define handle_mfile_stat        handle_datablock_stat
#define handle_mfile_pollconnect handle_datablock_pollconnect
#define handle_mfile_polltest    handle_datablock_polltest
#define handle_mfile_hop         handle_datablock_hop
#define handle_mfile_tryas       handle_datablock_tryas

/* Handle operators for `HANDLE_TYPE_MFILE' (`struct mfile') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_mfile_refcnt)(struct mfile const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_incref)(struct mfile *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_decref)(REF struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_mfile_tryincref)(struct mfile *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_mfile_weakgetref)(struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfile *NOTHROW(FCALL handle_mfile_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_pread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_pwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_readv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_pwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_readdir(struct mfile *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mfile_seek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mfile_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_truncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_mfile_mmap(struct mfile *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mfile_allocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_sync(struct mfile *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_datasync(struct mfile *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_stat(struct mfile *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_pollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_mfile_polltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mfile_hop(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_mfile_tryas(struct mfile *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H */
