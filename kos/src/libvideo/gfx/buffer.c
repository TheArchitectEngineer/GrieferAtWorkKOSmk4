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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_C
#define GUARD_LIBVIDEO_GFX_BUFFER_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>

#include <libvideo/gfx/buffer.h>
/**/

#include "buffer.h"
#include "empty-buffer.h"
#include "ram-buffer.h"

DECL_BEGIN

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
DEFINE_PUBLIC_ALIAS(video_buffer_create, libvideo_buffer_create);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_create(unsigned int type, size_t size_x, size_t size_y,
                       struct video_codec const *codec, struct video_palette *palette) {
	struct video_buffer *result;
	/* Check for special case: empty video buffer. */
	if unlikely(!size_x || !size_y)
		return incref(libvideo_getemptybuffer());
	if (!codec) {
		/* Lookup the default format. */
		struct video_format const *default_format;
		default_format = libvideo_preferred_format();
		codec          = default_format->vf_codec;
		palette        = default_format->vf_pal;
	}
	switch (type) {

	case VIDEO_BUFFER_AUTO:
	case VIDEO_BUFFER_RAM:
		result = libvideo_rambuffer_create(size_x, size_y,
		                                   codec, palette);
		break;

//TODO:	case VIDEO_BUFFER_GPU:
//TODO:		break;

	default:
		/* Unknown buffer type. */
		errno = EINVAL;
		result = NULL;
		break;
	}
	return result;
}


PRIVATE struct video_format preferred_video_format;

/* Return the preferred video format.
 * If  possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
DEFINE_PUBLIC_ALIAS(video_preferred_format, libvideo_preferred_format);
INTERN ATTR_RETNONNULL WUNUSED struct video_format const *CC
libvideo_preferred_format(void) {
	struct video_format *result;
	result = &preferred_video_format;
	if (!result->vf_codec) {
		struct video_codec const *codec;
		/* TODO: Ask the bound video driver for its preferred format. */
		COMPILER_IMPURE();
		codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		result->vf_pal = NULL;
		assert(codec != NULL);
		COMPILER_WRITE_BARRIER();
		result->vf_codec = codec;
	}
	return result;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_C */
