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
#ifndef GUARD_LIBSVGA_CS_VGA_H
#define GUARD_LIBSVGA_CS_VGA_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <libsvga/chipset.h>
#include <libsvga/chipsets/vga.h>

DECL_BEGIN

struct vga_modeinfo {
	struct svga_modeinfo gmi_base;   /* Underlying mode info (should be c++-inherited) */
	uint8_t              gmi_modeid; /* VGA Mode ID (index into `vga_modelist') */
};

struct vga_chipset: svga_chipset {
	uint8_t gcs_modeid; /* VGA Mode ID (index into `vga_modelist') */
};



/************************************************************************/
/* Known VGA video modes                                                */
/************************************************************************/
struct vga_known_mode {
	struct vga_modeinfo vkm_info; /* Video mode info. */
	struct vga_mode     vkm_regs; /* VGA register states. */
};

/* Indices for `vga_modelist' */
#define CS_VGAMODE_TEXT        0
#define CS_VGAMODE_320X200X16  1
#define CS_VGAMODE_640X200X16  2
#define CS_VGAMODE_640X350X16  3
#define CS_VGAMODE_640X480X16  4
#define CS_VGAMODE_640X480X2   5
#define CS_VGAMODE_320X200X256 6
#define CS_VGAMODE_320X240X256 7
#define CS_VGAMODE_320X400X256 8
#define CS_VGAMODE_360X480X256 9
#define CS_VGAMODE_720X348X2   10
#define CS_VGAMODE_COUNT       11

/* List of supported VGA modes. */
INTDEF struct vga_known_mode const vga_modelist[CS_VGAMODE_COUNT];

DECL_END

#endif /* !GUARD_LIBSVGA_CS_VGA_H */
