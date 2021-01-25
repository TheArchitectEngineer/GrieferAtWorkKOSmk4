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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_PHYS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_PHYS_C 1
#define __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/nopf.h>
#include <kernel/mman/phys-access.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <sys/io.h>

#include <alloca.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

typedef union {
	u16 w;
	u8 b[2];
} word16;

typedef union {
	u32 l;
	u16 w[2];
	u8 b[4];
} word32;

#ifdef __UINT64_TYPE__
typedef union {
	u64 q;
	u32 l[2];
	u16 w[4];
	u8 b[8];
} word64;
#endif /* __UINT64_TYPE__ */




/************************************************************************/
/* Helper functions for accessing very small segments of physical memory.
 * WARNING: DON'T SPAM THESE FUNCTIONS! If you want to access consecutive physical memory,
 *          either make use of `copy(from|to)phys()' or `THIS_TRAMPOLINE'.
 *          These functions will try to make use arch-specific physical identity mappings,
 *          like can be found on `x86_64' for the first 1Gib of physical memory.
 *          However any memory outside that region (or any memory at all if no such
 *          region is defined by the arch (as is the case for `i386'), will need to
 *          be accessed through use of `THIS_TRAMPOLINE'!) */
PUBLIC NOBLOCK WUNUSED u8
NOTHROW(FCALL peekphysb)(PHYS physaddr_t addr) {
	PHYS_VARS;
	u8 result;
	/* A single page of virtual memory in the kernel mman, that is always
	 * prepared for being used for whatever purposes a thread has in mind.
	 * NOTE: This page is also used by PAGEFAULTS, though it will
	 *       restore a previous mapping, if such a mapping existed.
	 * NOTE: Because this page is unique for each thread, the user is not
	 *       required to acquire a lock to the kernel mman when wishing to
	 *       map something at this location! */
	DEFINE_PUBLIC_SYMBOL(this_trampoline, this_trampoline_node.mn_minaddr,
	                     sizeof(this_trampoline_node.mn_minaddr));
	IF_PHYS_IDENTITY(addr, 1, {
		return *(u8 const *)PHYS_TO_IDENTITY(addr);
	});
	result = *(u8 const *)phys_pushaddr(addr);
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED u16
NOTHROW(FCALL peekphysw)(/*aligned(2)*/ PHYS physaddr_t addr) {
	PHYS_VARS;
	u16 result;
	assert(IS_ALIGNED(addr, 2));
	IF_PHYS_IDENTITY(addr, 2, {
		return *(u16 const *)PHYS_TO_IDENTITY(addr);
	});
	result = *(u16 const *)phys_pushaddr(addr);
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED u32
NOTHROW(FCALL peekphysl)(/*aligned(4)*/ PHYS physaddr_t addr) {
	PHYS_VARS;
	u32 result;
	assert(IS_ALIGNED(addr, 4));
	IF_PHYS_IDENTITY(addr, 4, {
		return *(u32 const *)PHYS_TO_IDENTITY(addr);
	});
	result = *(u32 const *)phys_pushaddr(addr);
	phys_pop();
	return result;
}

#ifdef __UINT64_TYPE__
PUBLIC NOBLOCK WUNUSED u64
NOTHROW(FCALL peekphysq)(/*aligned(8)*/ PHYS physaddr_t addr) {
	PHYS_VARS;
	u64 result;
	assert(IS_ALIGNED(addr, 8));
	IF_PHYS_IDENTITY(addr, 8, {
		return *(u64 const *)PHYS_TO_IDENTITY(addr);
	});
	result = *(u64 const *)phys_pushaddr(addr);
	phys_pop();
	return result;
}
#endif /* __UINT64_TYPE__ */

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysb)(PHYS physaddr_t addr, u8 value) {
	PHYS_VARS;
	IF_PHYS_IDENTITY(addr, 1, {
		*(u8 *)PHYS_TO_IDENTITY(addr) = value;
		return;
	});
	*(u8 *)phys_pushaddr(addr) = value;
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysw)(/*aligned(2)*/ PHYS physaddr_t addr, u16 value) {
	PHYS_VARS;
	assert(IS_ALIGNED(addr, 2));
	IF_PHYS_IDENTITY(addr, 2, {
		*(u16 *)PHYS_TO_IDENTITY(addr) = value;
		return;
	});
	*(u16 *)phys_pushaddr(addr) = value;
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysl)(/*aligned(4)*/ PHYS physaddr_t addr, u32 value) {
	PHYS_VARS;
	assert(IS_ALIGNED(addr, 4));
	IF_PHYS_IDENTITY(addr, 4, {
		*(u32 *)PHYS_TO_IDENTITY(addr) = value;
		return;
	});
	*(u32 *)phys_pushaddr(addr) = value;
	phys_pop();
}

#ifdef __UINT64_TYPE__
PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysq)(/*aligned(8)*/ PHYS physaddr_t addr, u64 value) {
	PHYS_VARS;
	assert(IS_ALIGNED(addr, 8));
	IF_PHYS_IDENTITY(addr, 8, {
		*(u64 *)PHYS_TO_IDENTITY(addr) = value;
		return;
	});
	*(u64 *)phys_pushaddr(addr) = value;
	phys_pop();
}
#endif /* __UINT64_TYPE__ */

PUBLIC NOBLOCK WUNUSED u16
NOTHROW(FCALL peekphysw_unaligned)(PHYS physaddr_t addr) {
	PHYS_VARS;
	byte_t *map;
	word16 result;
	IF_PHYS_IDENTITY(addr, 2, {
		return UNALIGNED_GET16((u16 const *)PHYS_TO_IDENTITY(addr));
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) != PAGEMASK) {
		result.w = UNALIGNED_GET16((u16 const *)map);
	} else {
		result.b[0] = ((u8 const *)map)[0];
		result.b[0] = ((u8 const *)phys_loadpage(addr + 1))[0];
	}
	phys_pop();
	return result.w;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysw_unaligned)(PHYS physaddr_t addr, u16 value) {
	PHYS_VARS;
	byte_t *map;
	IF_PHYS_IDENTITY(addr, 2, {
		UNALIGNED_SET16((u16 *)PHYS_TO_IDENTITY(addr), value);
		return;
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) != PAGEMASK) {
		UNALIGNED_SET16((u16 *)map, value);
	} else {
		word16 word;
		word.w         = value;
		((u8 *)map)[0] = word.b[0];
		map            = phys_loadpage(addr + 1);
		((u8 *)map)[0] = word.b[1];
	}
	phys_pop();
}


PUBLIC NOBLOCK WUNUSED u32
NOTHROW(FCALL peekphysl_unaligned)(PHYS physaddr_t addr) {
	PHYS_VARS;
	byte_t *map;
	word32 result;
	IF_PHYS_IDENTITY(addr, 4, {
		return UNALIGNED_GET32((u32 const *)PHYS_TO_IDENTITY(addr));
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) <= (PAGESIZE - 4)) {
		result.l = UNALIGNED_GET32((u32 const *)map);
	} else {
		void *dest;
		size_t count;
		count = PAGESIZE - (addr & PAGEMASK);
		dest  = mempcpy(result.b, map, count);
		map   = phys_loadpage(addr + count);
		memcpy(dest, map, 4 - count);
	}
	phys_pop();
	return result.l;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysl_unaligned)(PHYS physaddr_t addr, u32 value) {
	PHYS_VARS;
	byte_t *map;
	IF_PHYS_IDENTITY(addr, 4, {
		UNALIGNED_SET32((u32 *)PHYS_TO_IDENTITY(addr), value);
		return;
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) <= (PAGESIZE - 4)) {
		UNALIGNED_SET32((u32 *)map, value);
	} else {
		word32 word;
		size_t count;
		word.l = value;
		count  = PAGESIZE - (addr & PAGEMASK);
		memcpy(map, word.b, count);
		map = phys_loadpage(addr + count);
		memcpy(map, word.b + count, 4 - count);
	}
	phys_pop();
}

#ifdef __UINT64_TYPE__
PUBLIC NOBLOCK WUNUSED u64
NOTHROW(FCALL peekphysq_unaligned)(PHYS physaddr_t addr) {
	PHYS_VARS;
	byte_t *map;
	word64 result;
	IF_PHYS_IDENTITY(addr, 8, {
		return UNALIGNED_GET64((u64 const *)PHYS_TO_IDENTITY(addr));
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) <= (PAGESIZE - 8)) {
		result.q = UNALIGNED_GET64((u64 const *)map);
	} else {
		void *dest;
		size_t count;
		count = PAGESIZE - (addr & PAGEMASK);
		dest  = mempcpy(result.b, map, count);
		map   = phys_loadpage(addr + count);
		memcpy(dest, map, 8 - count);
	}
	phys_pop();
	return result.q;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pokephysq_unaligned)(PHYS physaddr_t addr, u64 value) {
	PHYS_VARS;
	byte_t *map;
	IF_PHYS_IDENTITY(addr, 8, {
		UNALIGNED_SET64((u64 *)PHYS_TO_IDENTITY(addr), value);
		return;
	});
	map = phys_pushaddr(addr);
	if ((addr & PAGEMASK) <= (PAGESIZE - 8)) {
		UNALIGNED_SET64((u64 *)map, value);
	} else {
		word64 word;
		size_t count;
		word.q = value;
		count  = PAGESIZE - (addr & PAGEMASK);
		memcpy(map, word.b, count);
		map = phys_loadpage(addr + count);
		memcpy(map, word.b + count, 8 - count);
	}
	phys_pop();
}
#endif /* __UINT64_TYPE__ */


#define phys_foreach_Twords(sizeofT, buf, buf_Twords, addr, num_Twords, ...)         \
	IF_HAVE_PHYS_IDENTITY(                                                           \
	if (PHYS_IS_IDENTITY(addr, (num_Twords)*sizeofT)) {                              \
		(buf)      = (typeof(buf))PHYS_TO_IDENTITY(addr);                            \
		buf_Twords = num_Twords;                                                     \
		__VA_ARGS__;                                                                 \
	} else)                                                                          \
	if (num_Twords != 0) {                                                           \
		PHYS_VARS;                                                                   \
		phys_pushpage((addr) & ~PAGEMASK);                                           \
		for (;;) {                                                                   \
			size_t _page_bytes;                                                      \
			_page_bytes  = PAGESIZE - (uintptr_t)((addr)&PAGEMASK);                  \
			(buf)        = (typeof(buf))(trampoline + (uintptr_t)((addr)&PAGEMASK)); \
			(buf_Twords) = _page_bytes / sizeofT;                                    \
			__VA_ARGS__;                                                             \
			(num_Twords) -= (buf_Twords);                                            \
			if (!(num_Twords))                                                       \
				break;                                                               \
			(addr) += _page_bytes;                                                   \
			phys_loadpage(addr);                                                     \
		}                                                                            \
		phys_pop();                                                                  \
	}


#define phys_foreach_b(buf, buf_bytes, addr, num_bytes, ...) \
	phys_foreach_Twords(1, buf, buf_bytes, addr, num_bytes, __VA_ARGS__)
#define phys_foreach_w(buf, buf_words, addr, num_words, ...) \
	phys_foreach_Twords(2, buf, buf_words, addr, num_words, __VA_ARGS__)
#define phys_foreach_l(buf, buf_dwords, addr, num_dwords, ...) \
	phys_foreach_Twords(4, buf, buf_dwords, addr, num_dwords, __VA_ARGS__)
#define phys_foreach_q(buf, buf_qwords, addr, num_qwords, ...) \
	phys_foreach_Twords(8, buf, buf_qwords, addr, num_qwords, __VA_ARGS__)



/* I/O functions with physical buffers. */
PUBLIC NOBLOCK void
NOTHROW(KCALL insphysb)(port_t port, PHYS physaddr_t addr, size_t num_bytes) {
	u8 *buf;
	size_t buflen;
	phys_foreach_b(buf, buflen, addr, num_bytes, {
		insb(port, buf, buflen);
	});
}

PUBLIC NOBLOCK void
NOTHROW(KCALL insphysw)(port_t port, /*aligned(2)*/ PHYS physaddr_t addr, size_t num_words) {
	u16 *buf;
	size_t buflen;
	phys_foreach_w(buf, buflen, addr, num_words, {
		insw(port, buf, buflen);
	});
}

PUBLIC NOBLOCK void
NOTHROW(KCALL insphysl)(port_t port, /*aligned(4)*/ PHYS physaddr_t addr, size_t num_dwords) {
	u32 *buf;
	size_t buflen;
	phys_foreach_l(buf, buflen, addr, num_dwords, {
		insl(port, buf, buflen);
	});
}

PUBLIC NOBLOCK void
NOTHROW(KCALL outsphysb)(port_t port, PHYS physaddr_t addr, size_t num_bytes) {
	u8 const *buf;
	size_t buflen;
	phys_foreach_b(buf, buflen, addr, num_bytes, {
		outsb(port, buf, buflen);
	});
}

PUBLIC NOBLOCK void
NOTHROW(KCALL outsphysw)(port_t port, /*aligned(2)*/ PHYS physaddr_t addr, size_t num_words) {
	u16 const *buf;
	size_t buflen;
	phys_foreach_w(buf, buflen, addr, num_words, {
		outsw(port, buf, buflen);
	});
}

PUBLIC NOBLOCK void
NOTHROW(KCALL outsphysl)(port_t port, /*aligned(4)*/ PHYS physaddr_t addr, size_t num_dwords) {
	u32 const *buf;
	size_t buflen;
	phys_foreach_l(buf, buflen, addr, num_dwords, {
		outsl(port, buf, buflen);
	});
}


/* Copy memory to/from the physical address space. */
PUBLIC void KCALL
copyfromphys(USER CHECKED void *dst,
             PHYS physaddr_t src,
             size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t const *map;
	IF_PHYS_IDENTITY(src, num_bytes, {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushaddr(src);
	TRY {
		for (;;) {
			size_t avail;
			avail = PAGESIZE - ((uintptr_t)map & PAGEMASK);
			if (avail > num_bytes)
				avail = num_bytes;
			memcpy(dst, map, avail);
			if (avail >= num_bytes)
				break;
			dst = (byte_t *)dst + avail;
			src += avail;
			num_bytes -= avail;
			map = phys_loadpage(src);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC void KCALL
copytophys(PHYS physaddr_t dst,
           USER CHECKED void const *src,
           size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t *map;
	IF_PHYS_IDENTITY(dst, num_bytes, {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushaddr(dst);
	TRY {
		for (;;) {
			size_t avail;
			avail = PAGESIZE - ((uintptr_t)map & PAGEMASK);
			if (avail > num_bytes)
				avail = num_bytes;
			memcpy(map, src, avail);
			if (avail >= num_bytes)
				break;
			dst += avail;
			src = (byte_t *)src + avail;
			num_bytes -= avail;
			map = phys_loadpage(dst);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL copyinphys)(PHYS physaddr_t dst,
                          PHYS physaddr_t src,
                          size_t num_bytes) {
	byte_t *buf;
	size_t bufsize;
	IF_PHYS_IDENTITY(dst, num_bytes, {
		IF_PHYS_IDENTITY(src, num_bytes, {
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       num_bytes);
			return;
		});
		copyfromphys(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	});
	IF_PHYS_IDENTITY(src, num_bytes, {
		copytophys(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	bufsize = get_stack_avail() / 2;
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	if (bufsize > PAGESIZE)
		bufsize = PAGESIZE;
	buf = (byte_t *)alloca(bufsize);
	for (;;) {
		size_t loadsize;
		loadsize = num_bytes;
		if (loadsize > bufsize)
			loadsize = bufsize;
		/* Transfer data using our intermediate buffer. */
		copyfromphys(buf, src, loadsize);
		copytophys(dst, buf, loadsize);
		if (loadsize >= num_bytes)
			break;
		src += loadsize;
		dst += loadsize;
		num_bytes -= loadsize;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL memsetphys)(PHYS physaddr_t dst, int byte, size_t num_bytes) {
	u8 *buf;
	size_t buflen;
	phys_foreach_b(buf, buflen, dst, num_bytes, {
		memset(buf, byte, buflen);
	});
}

/* no-#PF variants of `copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copyfromphys_nopf)(USER CHECKED void *dst,
                                 PHYS physaddr_t src,
                                 size_t num_bytes) {
	PHYS_VARS;
	size_t result;
	byte_t const *map;
	IF_PHYS_IDENTITY(src, num_bytes, {
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
	});
	if unlikely(!num_bytes)
		return 0;
	map = phys_pushaddr(src);
	for (;;) {
		size_t avail;
		avail = PAGESIZE - ((uintptr_t)map & PAGEMASK);
		if (avail > num_bytes)
			avail = num_bytes;
		result = memcpy_nopf(dst, map, avail);
		if unlikely(result != 0) {
			result += num_bytes - avail;
			break;
		}
		if (avail >= num_bytes)
			break;
		dst = (byte_t *)dst + avail;
		src += avail;
		num_bytes -= avail;
		map = phys_loadpage(src);
	}
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copytophys_nopf)(PHYS physaddr_t dst,
                               USER CHECKED void const *src,
                               size_t num_bytes) {
	PHYS_VARS;
	size_t result;
	byte_t *map;
	IF_PHYS_IDENTITY(dst, num_bytes, {
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
	});
	if unlikely(!num_bytes)
		return 0;
	map = phys_pushaddr(dst);
	for (;;) {
		size_t avail;
		avail = PAGESIZE - ((uintptr_t)map & PAGEMASK);
		if (avail > num_bytes)
			avail = num_bytes;
		result = memcpy_nopf(map, src, avail);
		if unlikely(result != 0) {
			result += num_bytes - avail;
			break;
		}
		if (avail >= num_bytes)
			break;
		dst += avail;
		src = (byte_t *)src + avail;
		num_bytes -= avail;
		map = phys_loadpage(dst);
	}
	phys_pop();
	return result;
}

/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~PAGEMASK) == ((PHYS + num_bytes - 1) & ~PAGEMASK)' */
PUBLIC void KCALL
copyfromphys_onepage(USER CHECKED void *dst,
                     PHYS physaddr_t src,
                     size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t const *map;
	assert((src & ~PAGEMASK) == ((src + num_bytes - 1) & ~PAGEMASK));
	IF_PHYS_IDENTITY(src, num_bytes, {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	});
	map = phys_pushaddr(src);
	TRY {
		memcpy(dst, map, num_bytes);
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC void KCALL
copytophys_onepage(PHYS physaddr_t dst,
                   USER CHECKED void const *src,
                   size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t *map;
	assert((dst & ~PAGEMASK) == ((dst + num_bytes - 1) & ~PAGEMASK));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	});
	map = phys_pushaddr(dst);
	TRY {
		memcpy(map, src, num_bytes);
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL copyinphys_onepage)(PHYS physaddr_t dst,
                                  PHYS physaddr_t src,
                                  size_t num_bytes) {
	byte_t *buf;
	size_t bufsize;
	assert((dst & ~PAGEMASK) == ((dst + num_bytes - 1) & ~PAGEMASK));
	assert((src & ~PAGEMASK) == ((src + num_bytes - 1) & ~PAGEMASK));
	assert(num_bytes <= PAGESIZE);
	IF_PHYS_IDENTITY(dst, num_bytes, {
		IF_PHYS_IDENTITY(src, num_bytes, {
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       num_bytes);
			return;
		});
		copyfromphys_onepage(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	});
	IF_PHYS_IDENTITY(src, num_bytes, {
		copytophys_onepage(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	bufsize = get_stack_avail() / 2;
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	buf = (byte_t *)alloca(bufsize);
	for (;;) {
		size_t loadsize;
		loadsize = num_bytes;
		if unlikely(loadsize > bufsize)
			loadsize = bufsize;
		/* Transfer data using our intermediate buffer. */
		copyfromphys_onepage(buf, src, loadsize);
		copytophys_onepage(dst, buf, loadsize);
		if likely(loadsize >= num_bytes)
			break;
		src += loadsize;
		dst += loadsize;
		num_bytes -= loadsize;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL memsetphys_onepage)(PHYS physaddr_t dst, int byte, size_t num_bytes) {
	PHYS_VARS;
	byte_t *map;
	assert((dst & ~PAGEMASK) == ((dst + num_bytes - 1) & ~PAGEMASK));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	});
	map = phys_pushaddr(dst);
	memset(map, byte, num_bytes);
	phys_pop();
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copyfromphys_onepage_nopf)(USER CHECKED void *dst,
                                         PHYS physaddr_t src,
                                         size_t num_bytes) {
	PHYS_VARS;
	byte_t const *map;
	size_t result;
	assert((src & ~PAGEMASK) == ((src + num_bytes - 1) & ~PAGEMASK));
	IF_PHYS_IDENTITY(src, num_bytes, {
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
	});
	map    = phys_pushaddr(src);
	result = memcpy_nopf(dst, map, num_bytes);
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copytophys_onepage_nopf)(PHYS physaddr_t dst,
                                       USER CHECKED void const *src,
                                       size_t num_bytes) {
	PHYS_VARS;
	byte_t *map;
	size_t result;
	assert((dst & ~PAGEMASK) == ((dst + num_bytes - 1) & ~PAGEMASK));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
	});
	map    = phys_pushaddr(dst);
	result = memcpy_nopf(map, src, num_bytes);
	phys_pop();
	return result;
}

/* Copy a whole page to/from physical memory. (s.a. `PAGESIZE') */
PUBLIC void KCALL
copypagefromphys(USER CHECKED void *dst,
                 PAGEDIR_PAGEALIGNED PHYS physaddr_t src)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t const *map;
	assert(IS_ALIGNED(src, PAGESIZE));
	IF_PHYS_IDENTITY_PAGE(src, {
		memcpy(dst, PHYS_TO_IDENTITY(src), PAGESIZE);
		return;
	});
	map = phys_pushpage(src);
	TRY {
		memcpy(dst, map, PAGESIZE);
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC void KCALL
copypagetophys(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
               USER CHECKED void const *src)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t *map;
	assert(IS_ALIGNED(dst, PAGESIZE));
	IF_PHYS_IDENTITY_PAGE(dst, {
		memcpy(PHYS_TO_IDENTITY(dst), src, PAGESIZE);
		return;
	});
	map = phys_pushpage(dst);
	TRY {
		memcpy(map, src, PAGESIZE);
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC void KCALL
copypagesfromphys(USER CHECKED void *dst,
                  PAGEDIR_PAGEALIGNED PHYS physaddr_t src,
                  PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t const *map;
	assert(IS_ALIGNED(src, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(src, num_bytes, {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushpage(src);
	TRY {
		for (;;) {
			memcpy(dst, map, PAGESIZE);
			num_bytes -= PAGESIZE;
			if (!num_bytes)
				break;
			dst = (byte_t *)dst + PAGESIZE;
			src += PAGESIZE;
			map = phys_loadpage(src);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC void KCALL
copypagestophys(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                USER CHECKED void const *src,
                PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_SEGFAULT) {
	PHYS_VARS;
	byte_t *map;
	assert(IS_ALIGNED(dst, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushpage(dst);
	TRY {
		for (;;) {
			memcpy(map, src, PAGESIZE);
			num_bytes -= PAGESIZE;
			if (!num_bytes)
				break;
			src = (byte_t const *)src + PAGESIZE;
			dst += PAGESIZE;
			map = phys_loadpage(dst);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL copypageinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                              PAGEDIR_PAGEALIGNED PHYS physaddr_t src) {
	byte_t *buf;
	size_t bufsize;
	IF_PHYS_IDENTITY_PAGE(dst, {
		IF_PHYS_IDENTITY_PAGE(src, {
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       PAGESIZE);
			return;
		});
		copypagefromphys(PHYS_TO_IDENTITY(dst), src);
		return;
	});
	IF_PHYS_IDENTITY_PAGE(src, {
		copypagetophys(dst, PHYS_TO_IDENTITY(src));
		return;
	});
	bufsize = get_stack_avail() / 2;
	if likely(bufsize >= PAGESIZE) {
		PHYS_VARS;
		byte_t *map;
		buf = (byte_t *)alloca(PAGESIZE);
		map = phys_pushpage(src);
		memcpy(buf, map, PAGESIZE);
		map = phys_loadpage(dst);
		memcpy(map, buf, PAGESIZE);
		phys_pop();
	} else {
		size_t missing;
		buf     = (byte_t *)alloca(bufsize);
		missing = PAGESIZE;
		for (;;) {
			size_t part = bufsize;
			if (part > missing)
				part = missing;
			copyfromphys_onepage(buf, src, part);
			copytophys_onepage(dst, buf, part);
			if (part >= missing)
				break;
			dst += part;
			src += part;
			missing -= part;
		}
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL copypagesinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                               PAGEDIR_PAGEALIGNED PHYS physaddr_t src,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	byte_t *buf;
	size_t bufsize;
	IF_PHYS_IDENTITY_PAGE(dst, {
		IF_PHYS_IDENTITY_PAGE(src, {
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       PAGESIZE);
			return;
		});
		copypagefromphys(PHYS_TO_IDENTITY(dst), src);
		return;
	});
	IF_PHYS_IDENTITY_PAGE(src, {
		copypagetophys(dst, PHYS_TO_IDENTITY(src));
		return;
	});
	bufsize = get_stack_avail() / 2;
	if likely(bufsize >= PAGESIZE) {
		PHYS_VARS;
		byte_t *map;
		buf = (byte_t *)alloca(PAGESIZE);
		map = phys_pushpage(src);
		for (;;) {
			memcpy(buf, map, PAGESIZE);
			map = phys_loadpage(dst);
			memcpy(map, buf, PAGESIZE);
			if (num_bytes <= PAGESIZE)
				break;
			num_bytes -= PAGESIZE;
			src += PAGESIZE;
			dst += PAGESIZE;
			map = phys_loadpage(src);
		}
		phys_pop();
	} else {
		copyinphys(dst, src, num_bytes);
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL memsetphyspage)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, int byte) {
	PHYS_VARS;
	byte_t *map;
	assert(IS_ALIGNED(dst, PAGESIZE));
	IF_PHYS_IDENTITY_PAGE(dst, {
		memset(PHYS_TO_IDENTITY(dst), byte, PAGESIZE);
		return;
	});
	map = phys_pushpage(dst);
	memset(map, byte, PAGESIZE);
	phys_pop();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL memsetphyspages)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, int byte,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PHYS_VARS;
	byte_t *map;
	assert(IS_ALIGNED(dst, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	});
	if unlikely(!num_bytes)
		return;
	map = phys_pushpage(dst);
	for (;;) {
		memset(map, byte, PAGESIZE);
		num_bytes -= PAGESIZE;
		if (!num_bytes)
			break;
		dst += PAGESIZE;
		map = phys_loadpage(dst);
	}
	phys_pop();
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copypagefromphys_nopf)(USER CHECKED void *dst,
                                     PAGEDIR_PAGEALIGNED PHYS physaddr_t src) {
	PHYS_VARS;
	byte_t const *map;
	size_t result;
	assert(IS_ALIGNED(src, PAGESIZE));
	IF_PHYS_IDENTITY_PAGE(src, {
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), PAGESIZE);
	});
	map    = phys_pushpage(src);
	result = memcpy_nopf(dst, map, PAGESIZE);
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copypagesfromphys_nopf)(USER CHECKED void *dst,
                                      PAGEDIR_PAGEALIGNED PHYS physaddr_t src,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PHYS_VARS;
	byte_t const *map;
	size_t result;
	assert(IS_ALIGNED(src, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(src, num_bytes, {
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
	});
	if unlikely(!num_bytes)
		return 0;
	map    = phys_pushpage(src);
	result = memcpy_nopf(dst, map, PAGESIZE);
	if unlikely(result != 0) {
		result += (num_bytes - PAGESIZE);
	} else {
		for (;;) {
			num_bytes -= PAGESIZE;
			if (!num_bytes)
				break;
			dst = (byte_t *)dst + PAGESIZE;
			src += PAGESIZE;
			map = phys_loadpage(src);
			result = memcpy_nopf(dst, map, PAGESIZE);
			if unlikely(result != 0) {
				result += num_bytes;
				result -= PAGESIZE;
				break;
			}
		}
	}
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copypagetophys_nopf)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                   USER CHECKED void const *src) {
	PHYS_VARS;
	byte_t *map;
	size_t result;
	assert(IS_ALIGNED(dst, PAGESIZE));
	IF_PHYS_IDENTITY_PAGE(dst, {
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, PAGESIZE);
	});
	map    = phys_pushpage(dst);
	result = memcpy_nopf(map, src, PAGESIZE);
	phys_pop();
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL copypagestophys_nopf)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                    USER CHECKED void const *src,
                                    PAGEDIR_PAGEALIGNED size_t num_bytes) {
	PHYS_VARS;
	byte_t *map;
	size_t result;
	assert(IS_ALIGNED(dst, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	IF_PHYS_IDENTITY(dst, num_bytes, {
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
	});
	if unlikely(!num_bytes)
		return 0;
	map    = phys_pushpage(dst);
	result = memcpy_nopf(map, src, PAGESIZE);
	if unlikely(result != 0) {
		result += (num_bytes - PAGESIZE);
	} else {
		for (;;) {
			num_bytes -= PAGESIZE;
			if (!num_bytes)
				break;
			src = (byte_t *)src + PAGESIZE;
			dst += PAGESIZE;
			map = phys_loadpage(dst);
			result = memcpy_nopf(map, src, PAGESIZE);
			if unlikely(result != 0) {
				result += num_bytes;
				result -= PAGESIZE;
				break;
			}
		}
	}
	phys_pop();
	return result;
}
/************************************************************************/







/************************************************************************/
/* A mem-node used to describe a single, reserved page. */
PUBLIC ATTR_PERTASK struct mnode this_trampoline_node = {
	/* .mn_mement   = */ { {} },
	/* .mn_minaddr  = */ (byte_t *)(0),
	/* .mn_maxaddr  = */ (byte_t *)(PAGESIZE - 1),
	/* .mn_flags    = */ MNODE_F_PWRITE | MNODE_F_PREAD |
	/*                */ MNODE_F_SHARED | MNODE_F_NO_SPLIT |
	/*                */ MNODE_F_NO_MERGE | MNODE_F_MPREPARED |
	/*                */ MNODE_F_MLOCK,
	/* .mn_part     = */ NULL,
	/* .mn_fspath   = */ NULL,
	/* .mn_fsname   = */ NULL,
	/* .mn_mman     = */ { &mman_kernel },
	/* .mn_partoff  = */ 0,
	/* .mn_link     = */ LIST_ENTRY_UNBOUND_INITIALIZER,
	/* .mn_writable = */ LIST_ENTRY_UNBOUND_INITIALIZER,
};
/************************************************************************/

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_PHYS_C */
