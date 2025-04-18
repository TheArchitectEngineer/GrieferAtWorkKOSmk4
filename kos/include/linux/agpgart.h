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
/* (#) Portability: Linux (/usr/include/linux/agpgart.h) */
#ifndef _LINUX_AGPGART_H
#define _LINUX_AGPGART_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <linux/types.h>

/* Taken from /usr/include/linux/agpgart.h */
/*
 * AGPGART module version 0.99
 * Copyright (C) 1999 Jeff Hartmann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


__DECL_BEGIN

#define AGPIOC_BASE          'A'
#define AGPIOC_INFO          _IOR('A', 0, struct agp_info *)
#define AGPIOC_ACQUIRE       _IO('A', 1)
#define AGPIOC_RELEASE       _IO('A', 2)
#define AGPIOC_SETUP         _IOW('A', 3, struct agp_setup *)
#define AGPIOC_RESERVE       _IOW('A', 4, struct agp_region *)
#define AGPIOC_PROTECT       _IOW('A', 5, struct agp_region *)
#define AGPIOC_ALLOCATE      _IOWR('A', 6, struct agp_allocate *)
#define AGPIOC_DEALLOCATE    _IOW('A', 7, int)
#define AGPIOC_BIND          _IOW('A', 8, struct agp_bind *)
#define AGPIOC_UNBIND        _IOW('A', 9, struct agp_unbind *)
#define AGPIOC_CHIPSET_FLUSH _IO('A', 10)

#define AGP_DEVICE "/dev/agpgart"

#ifndef TRUE
#define TRUE 1
#endif /* !TRUE */
#ifndef FALSE
#define FALSE 0
#endif /* !FALSE */


#ifdef __CC__
struct agp_version {
	__u16 major;
	__u16 minor;
};

typedef struct _agp_info {
	struct agp_version version;   /* version of the driver */
	__u32              bridge_id; /* bridge vendor/device */
	__u32              agp_mode;  /* mode info of bridge */
	__ULONGPTR_TYPE__  aper_base; /* base of aperture */
	size_t             aper_size; /* size of aperture */
	size_t             pg_total;  /* max pages (swap + system) */
	size_t             pg_system; /* max pages (system) */
	size_t             pg_used;   /* current pages used */
} agp_info;

typedef struct _agp_setup {
	__u32 agp_mode; /* mode info of bridge */
} agp_setup;

/* The "prot" down below needs still a "sleep" flag somehow ... */
typedef struct _agp_segment {
	__kernel_off_t  pg_start; /* starting page to populate */
	__kernel_size_t pg_count; /* number of pages */
	int             prot;     /* prot flags for mmap */
} agp_segment;

typedef struct _agp_region {
	__kernel_pid_t       pid;       /* pid of process */
	__kernel_size_t      seg_count; /* number of segments */
	struct _agp_segment *seg_list;
} agp_region;

typedef struct _agp_allocate {
	int             key;      /* tag of allocation */
	__kernel_size_t pg_count; /* number of pages */
	__u32           type;     /* 0 == normal, other devspec */
	__u32           physical; /* device specific (some devices
	                           * need  a  phys address  of the
	                           * actual page  behind the  gatt
	                           * table) */
} agp_allocate;

typedef struct _agp_bind {
	int            key;      /* tag of allocation */
	__kernel_off_t pg_start; /* starting page to populate */
} agp_bind;

typedef struct _agp_unbind {
	int   key;      /* tag of allocation */
	__u32 priority; /* priority for paging out */
} agp_unbind;
#endif /* __CC__ */

__DECL_END

#endif /* _LINUX_AGPGART_H */
