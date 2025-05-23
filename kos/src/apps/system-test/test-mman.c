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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_MMAN_C
#define GUARD_APPS_SYSTEM_TEST_TEST_MMAN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <sys/mman.h>
#include <system-test/ctest.h>

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(mlock_and_mincore) {
	void *p;
	size_t ps = getpagesize();
	uint8_t incore[2];

	NE(MAP_FAILED, (p = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_LOCKED, -1, 0)));

	/* Technically, mincore() is meant to be used for file mappings,
	 * but it should  work for PRIVATE+ANON  mappings just as  well. */
	incore[0] = 0xcc;
	EQ(0, mincore(p, 0, incore)); /* No-op with zero-size argument. */
	EQ(0xcc, incore[0]);

	/* All right: let's do this properly... */
	EQ(0, mincore(p, ps, incore));
	EQ(0, incore[0]);
	COMPILER_WRITE_BARRIER();
	*(unsigned int *)p = 0x1234;
	COMPILER_WRITE_BARRIER();
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);
	EQ(0, munmap(p, ps));

	/* When mapping with `MAP_POPULATE | MAP_LOCKED', then the mapping should be incore from the get-go! */
	NE(MAP_FAILED, (p = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_POPULATE | MAP_LOCKED, -1, 0)));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);
	EQ(0, munmap(p, ps));

	/* Use of mlock(MLOCK_ONFAULT) shouldn't cause the page to be moved into the core! */
	NE(MAP_FAILED, (p = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(0, incore[0]);
	EQ(0, mlock2(p, ps, MLOCK_ONFAULT));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(0, incore[0]);
	COMPILER_WRITE_BARRIER();
	*(unsigned int *)p = 0x1234;
	COMPILER_WRITE_BARRIER();
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);
	EQ(0, munmap(p, ps));

	/* But use of of mlock(0) _should_ cause the page to become INCORE! */
	NE(MAP_FAILED, (p = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(0, incore[0]);
	EQ(0, mlock2(p, ps, 0));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);
	/* Call `munlock()' just so we've called it at least once! */
	EQ(0, munlock(p, ps));
	EQ(0, munmap(p, ps));
}


/* Test the mremap(2) system call. */
DEFINE_TEST(mremap) {
	void *p;
	size_t ps = getpagesize();
	uint8_t incore[2];

	NE(MAP_FAILED, (p = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_LOCKED, -1, 0)));
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(0, incore[0]);
	COMPILER_WRITE_BARRIER();
	*(unsigned int *)p = 0x1234;
	COMPILER_WRITE_BARRIER();
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);

	NE(MAP_FAILED, (p = mremap(p, ps, ps * 2, MREMAP_MAYMOVE)));
	incore[0] = incore[1] = 0xcc;
	EQ(0, mincore(p, ps * 2, incore));
	EQ(1, incore[0]);
	EQ(0, incore[1]);

	/* Reducing the size should re-yield the old base-address! (even if `MREMAP_MAYMOVE' is given) */
	EQ(p, mremap(p, ps * 2, ps, MREMAP_MAYMOVE));
	EQ(-1, mincore(p, ps * 2, incore)); /* The second page should be unmapped now! */
	incore[0] = 0xcc;
	EQ(0, mincore(p, ps, incore));
	EQ(1, incore[0]);

	/* Increase the size once again, but this time, pass `MREMAP_POPULATE',
	 * thereby forcing the second page to also be pre-faulted (which we can
	 * test for by use of `mincore()') */
	NE(MAP_FAILED, (p = mremap(p, ps, ps * 2, MREMAP_MAYMOVE | MREMAP_POPULATE)));
	incore[0] = incore[1] = 0xcc;
	EQ(0, mincore(p, ps * 2, incore));
	EQ(1, incore[0]);
	EQ(1, incore[1]); /* !!! Second page must already be in-core */

	EQ(0x1234, *(unsigned int *)p);
	EQ(0, munmap(p, ps * 2));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_MMAN_C */
