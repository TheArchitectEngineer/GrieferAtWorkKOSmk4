/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_C
#define GUARD_LIBVIDEO_GFX_GFX_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/blendcolors.h>
/**/

#include "gfx-empty.h"
#include "gfx.h"

DECL_BEGIN

static_assert(sizeof(struct video_blit_xops) ==
              (_VIDEO_BLIT_XOPS__N_INTERNAL * sizeof(void (*)(void))),
              "sizeof(struct video_blit_xops) doesn't match '_VIDEO_BLIT_XOPS__N_INTERNAL'");
static_assert((sizeof(struct video_gfx_xops) - offsetafter(struct video_gfx_xops, vgxo_blitfrom)) ==
              (_VIDEO_GFX_XOPS__N_INTERNAL * sizeof(void (*)(void))),
              "sizeof(struct video_gfx_xops) doesn't match '_VIDEO_GFX_XOPS__N_INTERNAL'");

#ifndef PRIdOFF
#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxCOL PRIxN(__SIZEOF_VIDEO_COLOR_T__)
#endif /* !PRIdOFF */

#define _GFX_SELF self
#define GFX_BXMIN _GFX_SELF->vx_bxmin
#define GFX_BYMIN _GFX_SELF->vx_bymin
#define GFX_BXEND _GFX_SELF->vx_bxend
#define GFX_BYEND _GFX_SELF->vx_byend
#define GFX_BXMAX (_GFX_SELF->vx_bxend - 1)
#define GFX_BYMAX (_GFX_SELF->vx_byend - 1)


#undef ASSERT_ABS_COORDS_IS_NOOP
#if !defined(NDEBUG) && 0
#define ASSERT_ABS_COORDS(self, x, y)                    \
	(assertf((x) >= (self)->vx_bxmin &&                  \
	         (x) < (self)->vx_bxend,                     \
	         "x       = %" PRIuCRD " (%#" PRIxCRD ")\n"  \
	         "vx_bxmin = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_bxend = %" PRIuCRD " (%#" PRIxCRD ")",  \
	         (x), (x),                                   \
	         (self)->vx_bxmin, (self)->vx_bxmin,         \
	         (self)->vx_bxend, (self)->vx_bxend),        \
	 assertf((y) >= (self)->vx_bymin &&                  \
	         (y) < (self)->vx_byend,                     \
	         "y       = %" PRIuCRD " (%#" PRIxCRD ")\n"  \
	         "vx_bymin = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_byend = %" PRIuCRD " (%#" PRIxCRD ")",  \
	         (y), (y),                                   \
	         (self)->vx_bymin, (self)->vx_bymin,         \
	         (self)->vx_byend, (self)->vx_byend))
#else /* !NDEBUG */
#define ASSERT_ABS_COORDS(self, x, y) (void)0
#define ASSERT_ABS_COORDS_IS_NOOP 1
#endif /* NDEBUG */


#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(ASSERT_ABS_COORDS(self, abs_x, abs_y), (*(self)->vx_xops.vgxo_getcolor)(self, abs_x, abs_y))
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(ASSERT_ABS_COORDS(self, abs_x, abs_y), (*(self)->vx_xops.vgxo_putcolor)(self, abs_x, abs_y, color))

#ifdef ASSERT_ABS_COORDS_IS_NOOP
#undef video_gfx_getabscolor
#undef video_gfx_putabscolor
#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(*(self)->vx_xops.vgxo_getcolor)(self, abs_x, abs_y)
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(*(self)->vx_xops.vgxo_putcolor)(self, abs_x, abs_y, color)
#endif /* ASSERT_ABS_COORDS_IS_NOOP */

/************************************************************************/
/* CLAMPING / WRAPPING HELPERS                                          */
/************************************************************************/

/* @assume(dim > 0); */
LOCAL ATTR_CONST WUNUSED video_coord_t CC
wrap(video_offset_t offset, video_dim_t dim) {
	if unlikely(offset < 0) {
		offset = -offset;
		offset = (video_offset_t)((video_coord_t)offset % dim);
		if likely(offset)
			offset = dim - offset;
	} else if unlikely((video_coord_t)offset > dim) {
		offset = (video_offset_t)((video_coord_t)offset % dim);
	}
	return (video_coord_t)offset;
}



/************************************************************************/
/* BLENDING HELPERS                                                     */
/************************************************************************/

/* Check if `color' must be blended (false), or blending is optional (true),
 * such that behavior would be  the same when `GFX_BLENDINFO_OVERRIDE'  were
 * to be used. */
LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool CC
libvideo_gfx_allow_noblend(struct video_gfx *__restrict self,
                           video_color_t *__restrict p_color) {
	gfx_blendmode_t mode = self->vx_blend;
	/* TODO: Do this dynamically for all blending modes */
	if (mode == GFX_BLENDINFO_ALPHA)
		return VIDEO_COLOR_ISOPAQUE(*p_color);
	return false;
}



/************************************************************************/
/* LINEAR BLITTING HELPERS                                              */
/************************************************************************/

typedef video_channel_t channel_t;
typedef video_twochannels_t twochannels_t;
#define CHANNEL_MIN VIDEO_CHANNEL_MIN
#define CHANNEL_MAX VIDEO_CHANNEL_MAX

#define BITSOF(x) (sizeof(x) * NBBY)
static_assert(BITSOF(stretch_fp_t) >= BITSOF(video_coord_t) + STRETCH_FP_NFRAC,
              "stretch_fp_t is too small to hold arbitrary video coords + a fractional part");
static_assert(BITSOF(twochannels_t) >= (BITSOF(channel_t) * 2));


/************************************************************************/
/* DISCLAIMER: The linear stretch algorithm is derived from SDL!        */
/* s.a. SDL:/src/video/SDL_stretch.c:scale_mat                          */
/************************************************************************/

/* # of  leading bits  of "STRETCH_FP_NFRAC"  actually used  during
 * linear interpolation. Allowed to be less than "STRETCH_FP_NFRAC"
 * since no as much precision is still needed at that point.
 *
 * Specifically, we need at most "BITSOF(channel_t)" bots of precision,
 * however since for the purpose of blending we also need to be able to
 * represent a fixed-point "1.0", we need  1 extra bit for the  decimal
 * part.  And since we want to be  as efficient as possible, that means
 * we just restrict ourselves to 7 bits.
 *
 * In practice, you won't ever be able to see the difference, since this
 * missing bit of precision only comes  into play in how exactly  pixels
 * are  blended into  each other  during stretching,  having a minuscule
 * effect during color interpolation.
 */
#define LINEAR_FP_BLEND_NFRAC 7
typedef uint_fast8_t linear_fp_blend_t;     /* uint_fast{LINEAR_FP_BLEND_NFRAC+1}_t */
typedef uint_fast16_t linear_fp_twoblend_t; /* uint_fast{(LINEAR_FP_BLEND_NFRAC+1)*2}_t */
#define LINEAR_FP_BLEND(whole)    ((linear_fp_blend_t)(whole) << LINEAR_FP_BLEND_NFRAC)
#define LINEAR_FP_BLEND_WHOLE(fp) ((linear_fp_twoblend_t)(fp) >> LINEAR_FP_BLEND_NFRAC)

/* Return the blend-fraction of a gfx-stretch fixed-point (stretch_fp_t) "fp" value */
#define STRETCH_FP_BLEND_FRAC(fp) \
	((linear_fp_blend_t)((uint32_t)((fp) >> (STRETCH_FP_NFRAC - LINEAR_FP_BLEND_NFRAC)) & ((1 << LINEAR_FP_BLEND_NFRAC) - 1)))
static_assert(LINEAR_FP_BLEND_NFRAC <= STRETCH_FP_NFRAC);


LOCAL NONNULL((3, 4, 5, 6)) void CC
calc_linear_stretch_dim(video_dim_t src_dim,     /* in: "src" dimension */
                        video_dim_t dst_dim,     /* in: "dst" dimension */
                        sstretch_fp_t *fp_start, /* out: FP start value for "src" (still includes `*pad_min') */
                        stretch_fp_t *fp_step,   /* out: FP-delta in "src" to add for each pixel */
                        video_dim_t *pad_min,    /* out: # of leading pixels of padding in "dst" */
                        video_dim_t *pad_max) {  /* out: # of trailing pixels of padding in "dst" */
	stretch_fp_t fp_ratio; /* # of "src" pixels for each "dst" pixel */
	sstretch_fp_t fp_iter; /* Must be signed because *pad_min can result in negative values */
	assert(src_dim >= 1);
	assert(dst_dim >= 1);

	/* Special case for when the source dimension is so small that no blending can happen.
	 * Without this, we'd get a pixel out-of-bounds assertion fail in the "middle" part of
	 * the linear blender, which would try to access out-of-bounds pixels. */
	if unlikely(src_dim <= 1) {
		*fp_start = 0; /* Could also be left uninitialized */
		*fp_step  = 0; /* Could also be left uninitialized */
		*pad_min  = dst_dim;
		*pad_max  = 0;
		return;
	}

	fp_ratio = STRETCH_FP(src_dim) / dst_dim;

	fp_iter = fp_ratio * STRETCH_FP_FRAC(STRETCH_FP(1) / 2);
	fp_iter = STRETCH_FP_WHOLE(fp_iter + (STRETCH_FP(1) / 2));
	fp_iter -= STRETCH_FP(1) / 2; /* Start in the middle of pixels (this is also the reason why "*pad_min" is needed) */

	*fp_start = fp_iter;
	*fp_step  = fp_ratio;
	*pad_min  = 0;
	*pad_max  = 0;
	do {
		if (fp_iter < 0) {
			*pad_min += 1;
		} else {
			video_coord_t index = STRETCH_FP_WHOLE(fp_iter);
			if (index > src_dim - 2) {
				*pad_max += 1;
			}
		}
		fp_iter += fp_ratio;
		--dst_dim;
	} while (dst_dim);
}

/* Interpolate "c0" with "c1".
 * NOTE: Make sure that "frac0 + frac1 == LINEAR_FP_BLEND(1)" */
LOCAL ATTR_CONST channel_t CC
interpolate_channel_1d(channel_t c0, channel_t c1,
                       linear_fp_blend_t frac0,
                       linear_fp_blend_t frac1) {
	__builtin_assume(frac0 + frac1 == LINEAR_FP_BLEND(1));
	return (channel_t)LINEAR_FP_BLEND_WHOLE(((linear_fp_twoblend_t)c0 * frac1) +
	                                        ((linear_fp_twoblend_t)c1 * frac0));
}

LOCAL ATTR_CONST channel_t
interpolate_channel_2d(channel_t c_y0_x0, channel_t c_y0_x1,
                       channel_t c_y1_x0, channel_t c_y1_x1,
                       linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1,
                       linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1) {
	/* Blend vertically */
	channel_t y0 = interpolate_channel_1d(c_y0_x0, c_y1_x0, frac_y0, frac_y1);
	channel_t y1 = interpolate_channel_1d(c_y0_x1, c_y1_x1, frac_y0, frac_y1);
	/* Blend horizontally */
	return interpolate_channel_1d(y0, y1, frac_x0, frac_x1);
}

LOCAL ATTR_CONST video_color_t CC
interpolate_1d(video_color_t c0, video_color_t c1,
               linear_fp_blend_t frac0, linear_fp_blend_t frac1) {
	channel_t r = interpolate_channel_1d(VIDEO_COLOR_GET_RED(c0), VIDEO_COLOR_GET_RED(c1), frac0, frac1);
	channel_t g = interpolate_channel_1d(VIDEO_COLOR_GET_GREEN(c0), VIDEO_COLOR_GET_GREEN(c1), frac0, frac1);
	channel_t b = interpolate_channel_1d(VIDEO_COLOR_GET_BLUE(c0), VIDEO_COLOR_GET_BLUE(c1), frac0, frac1);
	channel_t a = interpolate_channel_1d(VIDEO_COLOR_GET_ALPHA(c0), VIDEO_COLOR_GET_ALPHA(c1), frac0, frac1);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

LOCAL ATTR_CONST video_color_t
interpolate_2d(video_color_t c_y0_x0, video_color_t c_y0_x1,
               video_color_t c_y1_x0, video_color_t c_y1_x1,
               linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1,
               linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1) {
	/* Blend vertically */
	video_color_t y0 = interpolate_1d(c_y0_x0, c_y1_x0, frac_y0, frac_y1);
	video_color_t y1 = interpolate_1d(c_y0_x1, c_y1_x1, frac_y0, frac_y1);
	/* Blend horizontally */
	return interpolate_1d(y0, y1, frac_x0, frac_x1);
}

/* Macro-implementation of a general-purpose linear stretch algorithm.
 *
 * @param: video_coord_t dst_x:      Destination X coord
 * @param: video_coord_t dst_y:      Destination Y coord
 * @param: video_dim_t   dst_size_x: Destination size in X
 * @param: video_dim_t   dst_size_y: Destination size in Y
 * @param: video_coord_t src_x:      Source X coord
 * @param: video_coord_t src_y:      Source Y coord
 * @param: video_dim_t   src_size_x: Source size in X
 * @param: video_dim_t   src_size_y: Source size in Y
 *
 * Blending implementation callbacks (macros). All of these are expected
 * to fill in a specific portion of the destination GFX using data  from
 * the specified source coords. When appropriate, blending fractions to-
 * be applied to source pixels are also supplied.
 * In all cases, the supplied "src_x/src_y" points to the top-left of a
 * 1x1,  1x2,  2x1 or  2x2  pixel area  from  which data  can  be read.
 *
 * @param: [1x1] "top-left":     void blend_xmin_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [2x1] "top":          void blend_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_y, video_coord_t src_x0, video_coord_t src_y, video_coord_t src_x1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1)
 * @param: [1x1] "top-right":    void blend_xmax_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [1x2] "left":         void blend_xmin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_coord_t src_x, video_coord_t src_y0, video_coord_t src_y1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [2x2] "center":       void blend(video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x0, video_coord_t src_y0, video_coord_t src_x1, video_coord_t src_y1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [1x2] "right":        void blend_xmax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_coord_t src_x, video_coord_t src_y0, video_coord_t src_y1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [1x1] "bottom-left":  void blend_xmin_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [2x1] "bottom":       void blend_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_y, video_coord_t src_x0, video_coord_t src_y, video_coord_t src_x1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1)
 * @param: [1x1] "bottom-right": void blend_xmax_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 */
#define GFX_LINEAR_STRETCH(dst_x, dst_y, dst_size_x, dst_size_y,                                                                   \
                           src_x, src_y, src_size_x, src_size_y,                                                                   \
                           blend_xmin_ymin /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_ymin /**/ /*(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1)*/,                \
                           blend_xmax_ymin /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_xmin /**/ /*(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)*/,                \
                           blend /*     */ /*(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1)*/, \
                           blend_xmax /**/ /*(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)*/,                \
                           blend_xmin_ymax /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_ymax /**/ /*(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1)*/,                \
                           blend_xmax_ymax /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/)                               \
	do {                                                                                                                           \
		video_coord_t _rel_dst_y; /* Relative destination Y coord [0,dst_size_y) */                                                \
		video_dim_t _pad_xmin, _pad_xmax;                                                                                          \
		video_dim_t _pad_ymin, _pad_ymax;                                                                                          \
		sstretch_fp_t _fp_src_x;                                                                                                   \
		sstretch_fp_t _fp_src_y;                                                                                                   \
		stretch_fp_t _fp_step_x;                                                                                                   \
		stretch_fp_t _fp_step_y;                                                                                                   \
		video_dim_t _nopad_dst_x; /* # of horizontal pixels that can be written w/o padding */                                     \
		calc_linear_stretch_dim(src_size_x, dst_size_x, &_fp_src_x, &_fp_step_x, &_pad_xmin, &_pad_xmax);                          \
		calc_linear_stretch_dim(src_size_y, dst_size_y, &_fp_src_y, &_fp_step_y, &_pad_ymin, &_pad_ymax);                          \
		_nopad_dst_x = dst_size_x - _pad_xmin - _pad_xmax;                                                                         \
		_fp_src_x += _pad_xmin * _fp_step_x; /* Skip over leading padding */                                                       \
		                                                                                                                           \
		/* Render padding near the top */                                                                                          \
		if (_pad_ymin) {                                                                                                           \
			video_coord_t _used_dst_x = dst_x;                                                                                     \
			video_dim_t _middle;                                                                                                   \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin_ymin(_used_dst_x, dst_y, _pad_xmin, _pad_ymin, src_x, src_y);                                           \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend_ymin(_used_dst_x, dst_y, _pad_ymin, _used_src_x, src_y, (_used_src_x + 1), _frac_x0, _frac_x1);              \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmax_ymin(_used_dst_x, dst_y, _pad_xmax, _pad_ymin, _used_src_x, src_y);                                     \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
			_fp_src_y += _fp_step_y * _pad_ymin;                                                                                   \
		}                                                                                                                          \
		                                                                                                                           \
		/* Render the main image */                                                                                                \
		for (_rel_dst_y = _pad_ymin; _rel_dst_y < dst_size_y - _pad_ymax; ++_rel_dst_y, _fp_src_y += _fp_step_y) {                 \
			video_coord_t _used_dst_y = dst_y + _rel_dst_y; /* Absolute destination Y coord [dst_y,dst_y+dst_size_y) */            \
			video_coord_t _used_dst_x;                                                                                             \
			video_coord_t _rel_src_y;                                                                                              \
			linear_fp_blend_t _frac_y0, _frac_y1;                                                                                  \
			video_dim_t _middle;                                                                                                   \
			video_coord_t _used_src_y0, _used_src_y1;                                                                              \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			_rel_src_y = STRETCH_FP_WHOLE(_fp_src_y);                                                                              \
			_frac_y0   = STRETCH_FP_BLEND_FRAC(_fp_src_y);                                                                         \
			_frac_y1   = LINEAR_FP_BLEND(1) - _frac_y0;                                                                            \
			                                                                                                                       \
			_used_src_y0 = src_y + _rel_src_y; /* Y coord of first src row */                                                      \
			_used_src_y1 = _used_src_y0 + 1;   /* Y coord of second src row */                                                     \
			_used_dst_x  = dst_x;                                                                                                  \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin(_used_dst_x, _used_dst_y, _pad_xmin, src_x, _used_src_y0, _used_src_y1, _frac_y0, _frac_y1);            \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend(_used_dst_x, _used_dst_y, _used_src_x, _used_src_y0, (_used_src_x + 1), _used_src_y1,                        \
				      _frac_x0, _frac_x1, _frac_y0, _frac_y1);                                                                     \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmin(_used_dst_x, _used_dst_y, _pad_xmax, _used_src_x, _used_src_y0, _used_src_y1, _frac_y0, _frac_y1);      \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
		}                                                                                                                          \
		                                                                                                                           \
		/* Render padding near the bottom */                                                                                       \
		if (_pad_ymax) {                                                                                                           \
			video_coord_t _used_dst_y = dst_y + dst_size_y - _pad_ymax;                                                            \
			video_coord_t _used_dst_x = dst_x;                                                                                     \
			video_dim_t _middle;                                                                                                   \
			video_coord_t _used_src_y = src_y + src_size_y - 1;                                                                    \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			                                                                                                                       \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin_ymin(_used_dst_x, _used_dst_y, _pad_xmin, _pad_ymax, src_x, _used_src_y);                               \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend_ymin(_used_dst_x, _used_dst_y, _pad_ymax, _used_src_x, _used_src_y, (_used_src_x + 1), _frac_x0, _frac_x1);  \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmax_ymax(_used_dst_x, _used_dst_y, _pad_xmax, _pad_ymax, _used_src_x, _used_src_y);                         \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
		}                                                                                                                          \
	}	__WHILE0

/************************************************************************/
/************************************************************************/
/************************************************************************/



LOCAL ATTR_PURE WUNUSED channel_t
bitmask2d_getbit(byte_t const *__restrict bitmask, size_t bitscan,
                 video_coord_t x, video_coord_t y) {
	uintptr_t bitno = (uintptr_t)x + y * bitscan;
	byte_t byte;
	byte  = bitmask[bitno / NBBY];
	bitno = bitno % NBBY;
#if 1
	/* Move the bit we're interested in to the most significant position.
	 * e.g.: when "bitno == 0", then we want bit masked by 0x80
	 *       when "bitno == 3", then we want bit masked by 0x10 */
	byte <<= bitno;
	/* Used signed shift to duplicate the most significant bit into all other bits. */
	byte = (byte_t)((__SBYTE_TYPE__)byte >> (NBBY - 1));
	return byte;
#else
	return ((byte >> (NBBY - 1) - bitno) & 1) ? 0xff : 0;
#endif
}






/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                                                                      */
/* INTERNAL API                                                         */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/


/* Low-level, Generic, always-valid GFX color functions (using only `vgxo_getpixel' + `vgxo_setpixel') */
INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_generic__getcolor_noblend(struct video_gfx const *__restrict self,
                                       video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = (*self->vx_xops.vgxo_getpixel)(self, x, y);
	return self->vx_buffer->vb_format.pixel2color(pixel);
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_generic__getcolor_blur(struct video_gfx const *__restrict self,
                                    video_coord_t x, video_coord_t y) {
	video_color_t result;
	video_color_t colors[8];
	video_twochannels_t r, g, b, a;
	uint_fast8_t i, color_count;
#define MODE_XMIN 0x1
#define MODE_XMAX 0x2
#define MODE_YMIN 0x4
#define MODE_YMAX 0x8
	uint_fast8_t mode = 0x0;
	ASSERT_ABS_COORDS(self, x, y);
	/* Figure out how we're situated in relation to bounds. */
	if unlikely(x == self->vx_bxmin)
		mode |= MODE_XMIN;
	if unlikely(y == self->vx_bymin)
		mode |= MODE_YMIN;
	if unlikely(x == self->vx_bxend - 1)
		mode |= MODE_XMAX;
	if unlikely(y == self->vx_byend - 1)
		mode |= MODE_YMAX;
	/* Load colors as needed. */
	switch (__builtin_expect(mode, 0x0)) {
#define GETCOLOR(xoff, yoff) \
		libvideo_gfx_generic__getcolor_noblend(self, x + (xoff), y + (yoff))

	case 0x0:
		/* +++ */
		/* +.+ */
		/* +++ */
		color_count = 8;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);

		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);

		colors[5] = GETCOLOR(-1, 1);
		colors[6] = GETCOLOR(0, 1);
		colors[7] = GETCOLOR(1, 1);
		break;

	case MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* -++ */
		color_count = 5;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);

		colors[2] = GETCOLOR(1, 0);

		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_XMAX:
		/* ++- */
		/* +.- */
		/* ++- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);

		colors[2] = GETCOLOR(-1, 0);

		colors[3] = GETCOLOR(-1, 1);
		colors[4] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN:
		/* --- */
		/* +.+ */
		/* +++ */
		color_count = 5;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		colors[2] = GETCOLOR(-1, 1);
		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_YMAX:
		/* +++ */
		/* +.+ */
		/* --- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);
		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX:
		/* --- */
		/* +.+ */
		/* --- */
		color_count = 2;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		break;

	case MODE_XMIN | MODE_XMAX:
		/* -+- */
		/* -.- */
		/* -+- */
		color_count = 2;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* -++ */
		color_count = 3;
		colors[0] = GETCOLOR(1, 0);
		colors[1] = GETCOLOR(0, 1);
		colors[2] = GETCOLOR(1, 1);
		break;

	case MODE_YMIN | MODE_XMAX:
		/* --- */
		/* +.- */
		/* ++- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(-1, 1);
		colors[2] = GETCOLOR(0, 1);
		break;

	case MODE_YMAX | MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);
		colors[2] = GETCOLOR(1, 0);
		break;

	case MODE_YMAX | MODE_XMAX:
		/* ++- */
		/* +.- */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMIN:
		/* --- */
		/* -.- */
		/* -+- */
		color_count = 1;
		colors[0] = GETCOLOR(0, 1);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMAX:
		/* -+- */
		/* -.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(0, -1);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMAX:
		/* --- */
		/* +.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_YMIN | MODE_XMAX | MODE_YMAX:
		/* --- */
		/* -.- */
		/* --- */
		color_count = 0;
		break;

#undef GETCOLOR
	default: __builtin_unreachable();
	}
#undef MODE_XMIN
#undef MODE_XMAX
#undef MODE_YMIN
#undef MODE_YMAX
	result = libvideo_gfx_generic__getcolor_noblend(self, x, y);
	r = VIDEO_COLOR_GET_RED(result);
	g = VIDEO_COLOR_GET_GREEN(result);
	b = VIDEO_COLOR_GET_BLUE(result);
	a = VIDEO_COLOR_GET_ALPHA(result);
	for (i = 0; i < color_count; ++i) {
		r += VIDEO_COLOR_GET_RED(colors[i]);
		g += VIDEO_COLOR_GET_GREEN(colors[i]);
		b += VIDEO_COLOR_GET_BLUE(colors[i]);
		a += VIDEO_COLOR_GET_ALPHA(colors[i]);
	}
	++color_count;
	r /= color_count;
	g /= color_count;
	b /= color_count;
	a /= color_count;
	result = VIDEO_COLOR_RGBA((video_channel_t)r,
	                          (video_channel_t)g,
	                          (video_channel_t)b,
	                          (video_channel_t)a);
	return result;
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_generic__getcolor_with_key(struct video_gfx const *__restrict self,
                                        video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = (*self->vx_xops.vgxo_getpixel)(self, x, y);
	video_color_t result = self->vx_buffer->vb_format.pixel2color(pixel);
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__putcolor(struct video_gfx *__restrict self,
                               video_coord_t x, video_coord_t y,
                               video_color_t color) {
	video_pixel_t o_pixel = (*self->vx_xops.vgxo_getpixel)(self, x, y);
	video_color_t o_color = self->vx_buffer->vb_format.pixel2color(o_pixel);
	video_color_t n_color = gfx_blendcolors(o_color, color, self->vx_blend);
	video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(n_color);
	(*self->vx_xops.vgxo_setpixel)(self, x, y, n_pixel);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__putcolor_noblend(struct video_gfx *__restrict self,
                                       video_coord_t x, video_coord_t y,
                                       video_color_t color) {
	video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(color);
	(*self->vx_xops.vgxo_setpixel)(self, x, y, n_pixel);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__putcolor_alphablend(struct video_gfx *__restrict self,
                                          video_coord_t x, video_coord_t y,
                                          video_color_t color) {
	video_pixel_t o_pixel = (*self->vx_xops.vgxo_getpixel)(self, x, y);
	video_color_t o_color = self->vx_buffer->vb_format.pixel2color(o_pixel);
	video_color_t n_color = gfx_blendcolors(o_color, color, GFX_BLENDINFO_ALPHA);
	video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(n_color);
	(*self->vx_xops.vgxo_setpixel)(self, x, y, n_pixel);
}





/* Generic, always-valid GFX functions (using only `vx_pxops') */
INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_llhh(struct video_gfx *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	video_dim_t step;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	assert(size_x > 0);
	assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + step,
			                      dst_y + (video_dim_t)(((uint64_t)size_y * step) / size_x),
			                      color);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y),
			                      dst_y + step,
			                      color);
		} while (++step != size_y);
	} else {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + step,
			                      dst_y + step,
			                      color);
		} while (++step != size_x);
	}
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_lhhl(struct video_gfx *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	video_dim_t step;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	assert(size_x > 0);
	assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + step,
			                      dst_y - (video_dim_t)(((uint64_t)size_y * step) / size_x),
			                      color);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y),
			                      dst_y - step,
			                      color);
		} while (++step != size_y);
	} else {
		do {
			video_gfx_putabscolor(self,
			                      dst_x + step,
			                      dst_y - step,
			                      color);
		} while (++step != size_x);
	}
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_llhh_aa(struct video_gfx *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t color) {
	/* TODO: anti-aliased line drawing */
	libvideo_gfx_generic__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_lhhl_aa(struct video_gfx *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t color) {
	/* TODO: anti-aliased line drawing */
	libvideo_gfx_generic__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);
}



INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_h(struct video_gfx *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	video_coord_t x = 0;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_h(self, dst_x, dst_y, length, color);
		return;
	}
	do {
		video_gfx_putabscolor(self, dst_x + x, dst_y, color);
	} while (++x < length);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absline_v(struct video_gfx *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	video_coord_t y = 0;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_v(self, dst_x, dst_y, length, color);
		return;
	}
	do {
		video_gfx_putabscolor(self, dst_x, dst_y + y, color);
	} while (++y < length);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__absfill(struct video_gfx *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color) {
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	video_coord_t y = 0;
	do {
		(*self->vx_xops.vgxo_absline_h)(self, dst_x, dst_y + y, size_x, color);
	} while (++y < size_y);
}




/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_generic__bitfill(struct video_gfx *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color,
                              struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__bitfill(self, dst_x, dst_y, size_x, size_y,
		                              color, bm);
		return;
	}
	TRACE_START("generic__bitfill("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p)\n",
	            dst_x, dst_y, size_x, size_y, color, bm);
	bitskip = bm->vbm_skip;
	do {
		video_dim_t x = 0;
		uintptr_t row_bitskip = bitskip;
		byte_t const *row = (byte_t const *)bm->vbm_mask;
		do {
			video_dim_t count;
			byte_t byte;
			shift_t bits;
			if (row_bitskip >= NBBY) {
				row += row_bitskip / NBBY;
				row_bitskip %= NBBY;
			}
			byte = *row;
			bits = NBBY - row_bitskip;

			/* Skip over 0-bits */
			for (;;) {
				--bits;
				++row_bitskip;
				if (byte & ((byte_t)1 << bits))
					break;
				++x;
				if (x >= size_x)
					goto next_row;
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
			}

			/* Count consecutive 1-bits */
			count = 1;
			while ((x + count) < size_x) {
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
				--bits;
				if (!(byte & ((byte_t)1 << bits)))
					break;
				++row_bitskip;
				++count;
			}
			(*self->vx_xops.vgxo_absline_h)(self,
			                                dst_x + x,
			                                dst_y,
			                                count, color);
			x += count;
		} while (x < size_x);
next_row:
		bitskip += bm->vbm_scan;
		++dst_y;
	} while (--size_y);
	TRACE_END("generic__bitfill()\n");
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_generic__bitstretchfill_l(struct video_gfx *__restrict self,
                                       video_coord_t dst_x_, video_coord_t dst_y_,
                                       video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                       video_color_t color,
                                       video_dim_t src_size_x_, video_dim_t src_size_y_,
                                       struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip_ = bm->vbm_skip;
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	video_color_t raw_color = color & ~VIDEO_COLOR_ALPHA_MASK;
	channel_t raw_alpha = VIDEO_COLOR_GET_ALPHA(color);
#define makealpha(alpha_chan) (channel_t)(((twochannels_t)raw_alpha * (alpha_chan)) / CHANNEL_MAX)
#define makecolor(alpha_chan) (raw_color | ((video_color_t)makealpha(alpha_chan) << VIDEO_COLOR_ALPHA_SHIFT))
	if (bitskip_ > NBBY) {
		bitmask += bitskip_ / NBBY;
		bitskip_ = bitskip_ % NBBY;
	}

#define getbit(src_x, src_y) bitmask2d_getbit(bitmask, bm->vbm_scan, src_x, src_y)

#define bitmask_blend_xmax_ymin bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmax_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)           \
	{                                                                                         \
		if (getbit(src_x, src_y))                                                             \
			(*self->vx_xops.vgxo_absfill)(self, dst_x, dst_y, dst_size_x, dst_size_y, color); \
	}

#define bitmask_blend_ymax bitmask_blend_ymin
#define bitmask_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1)   \
	{                                                                                           \
		channel_t src_y0_x0 = getbit(src_x0, src_y);                                            \
		channel_t src_y0_x1 = getbit(src_x1, src_y);                                            \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);        \
		if (chan) {                                                                             \
			video_color_t out = makecolor(chan);                                                \
			(*self->vx_xops.vgxo_absline_v)(self, dst_x, dst_y, dst_size_y, out);               \
		}                                                                                       \
	}

#define bitmask_blend_xmax bitmask_blend_xmin
#define bitmask_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                         \
		channel_t src_y0_x0 = getbit(src_x, src_y0);                                          \
		channel_t src_y1_x0 = getbit(src_x, src_y1);                                          \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);      \
		if (chan) {                                                                           \
			video_color_t out = makecolor(chan);                                              \
			(*self->vx_xops.vgxo_absline_h)(self, dst_x, dst_y, dst_size_x, out);             \
		}                                                                                     \
	}

#define bitmask_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                   \
		channel_t src_y0_x0 = getbit(src_x0, src_y0);                                                   \
		channel_t src_y0_x1 = getbit(src_x1, src_y0);                                                   \
		channel_t src_y1_x0 = getbit(src_x0, src_y1);                                                   \
		channel_t src_y1_x1 = getbit(src_x1, src_y1);                                                   \
		channel_t chan      = interpolate_channel_2d(src_y0_x0, src_y0_x1,                              \
		                                             src_y1_x0, src_y1_x1,                              \
		                                             frac_x0, frac_x1,                                  \
		                                             frac_y0, frac_y1);                                 \
		if (chan) {                                                                                     \
			video_color_t out = makecolor(chan);                                                        \
			video_gfx_putabscolor(self, dst_x, dst_y, out);                                             \
		}                                                                                               \
	}

	TRACE_START("generic__bitstretchfill_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            color, src_size_x_, src_size_y_, bm);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   bitskip_, 0, src_size_x_, src_size_y_,
	                   bitmask_blend_xmin_ymin,
	                   bitmask_blend_ymin,
	                   bitmask_blend_xmax_ymin,
	                   bitmask_blend_xmin,
	                   bitmask_blend,
	                   bitmask_blend_xmax,
	                   bitmask_blend_xmin_ymax,
	                   bitmask_blend_ymax,
	                   bitmask_blend_xmax_ymax);
	TRACE_END("generic__bitstretchfill_l()\n");
#undef bitmask_blend_xmin_ymin
#undef bitmask_blend_ymin
#undef bitmask_blend_xmax_ymin
#undef bitmask_blend_xmin
#undef bitmask_blend
#undef bitmask_blend_xmax
#undef bitmask_blend_xmin_ymax
#undef bitmask_blend_ymax
#undef bitmask_blend_xmax_ymax

#undef getbit
#undef makealpha
#undef makecolor
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_generic__bitstretchfill_n(struct video_gfx *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_color_t color,
                                       video_dim_t src_size_x, video_dim_t src_size_y,
                                       struct video_bitmask const *__restrict bm) {
	video_dim_t y;
	stretch_fp_t step_x, step_y, src_pos_y;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
	}
	if ((src_size_x < (dst_size_x >> 1)) &&
	    (src_size_y < (dst_size_y >> 1))) {
		/* TODO: Iterate across "src" and use "self->vx_xops.vgxo_absfill"
		 *       to  fill  rects  associated with  visible  source pixels. */
	}
	TRACE_START("generic__bitstretchfill_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            color, src_size_x, src_size_y, bm);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y  = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		uintptr_t row_bitno = bm->vbm_skip + row_src_y * bm->vbm_scan;
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			uintptr_t bitno = row_bitno + row_src_x;
			if (((byte_t const *)bm->vbm_mask)[bitno / NBBY] & ((byte_t)1 << ((NBBY - 1) - (bitno % NBBY))))
				video_gfx_putabscolor(self, dst_x + x, row_dst_y, color);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("generic__bitstretchfill_n()\n");
}

/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic__blit(struct video_blit *__restrict self,
                           video_coord_t dst_x, video_coord_t dst_y,
                           video_coord_t src_x, video_coord_t src_y,
                           video_dim_t size_x, video_dim_t size_y) {
	video_dim_t x, y;
	struct video_gfx const *src = self->vb_src;
	struct video_gfx *dst = self->vb_dst;
	TRACE_START("generic__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_color_t color;
			color = video_gfx_getabscolor(src, src_x + x, src_y + y);
			video_gfx_putabscolor(dst, dst_x + x, dst_y + y, color);
		}
	}
	TRACE_END("generic__blit()\n");
}


INTERN NONNULL((1, 8)) void CC
libvideo_gfx_generic__bitblit(struct video_blit *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_coord_t src_x, video_coord_t src_y,
                              video_dim_t size_x, video_dim_t size_y,
                              struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip = bm->vbm_skip + src_x + src_y * bm->vbm_scan;
	TRACE_START("generic__bitblit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y, bm);
	do {
		video_dim_t x = 0;
		uintptr_t row_bitskip = bitskip;
		byte_t const *row = (byte_t const *)bm->vbm_mask;
		do {
			video_dim_t count;
			byte_t byte;
			shift_t bits;
			if (row_bitskip >= NBBY) {
				row += row_bitskip / NBBY;
				row_bitskip %= NBBY;
			}
			byte = *row;
			bits = NBBY - row_bitskip;

			/* Skip over 0-bits */
			for (;;) {
				--bits;
				++row_bitskip;
				if (byte & ((byte_t)1 << bits))
					break;
				++x;
				if (x >= size_x)
					goto next_row;
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
			}

			/* Count consecutive 1-bits */
			count = 1;
			while ((x + count) < size_x) {
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
				--bits;
				if (!(byte & ((byte_t)1 << bits)))
					break;
				++row_bitskip;
				++count;
			}
			(*self->vb_xops.vbxo_blit)(self,
			                           dst_x + x, dst_y,
			                           src_x + x, src_y,
			                           count, 1);
			x += count;
		} while (x < size_x);
next_row:
		bitskip += bm->vbm_scan;
		--size_y;
		++dst_y;
		++src_y;
	} while (size_y);
	TRACE_END("generic__bitblit()\n");
}



INTERN NONNULL((1)) void CC
libvideo_gfx_generic__stretch_l(struct video_blit *__restrict self,
                                video_coord_t dst_x_, video_coord_t dst_y_,
                                video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                video_coord_t src_x_, video_coord_t src_y_,
                                video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)     \
	{                                                                                 \
		video_color_t out = video_gfx_getabscolor(src, src_x, src_y);                 \
		(*dst->vx_xops.vgxo_absfill)(dst, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = video_gfx_getabscolor(src, src_x0, src_y);                \
		video_color_t src_y0_x1 = video_gfx_getabscolor(src, src_x1, src_y);                \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		(*dst->vx_xops.vgxo_absline_v)(dst, dst_x, dst_y, dst_size_y, out);                 \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = video_gfx_getabscolor(src, src_x, src_y0);                \
		video_color_t src_y1_x0 = video_gfx_getabscolor(src, src_x, src_y1);                \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		(*dst->vx_xops.vgxo_absline_h)(dst, dst_x, dst_y, dst_size_x, out);                 \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = video_gfx_getabscolor(src, src_x0, src_y0);                         \
		video_color_t src_y0_x1 = video_gfx_getabscolor(src, src_x1, src_y0);                         \
		video_color_t src_y1_x0 = video_gfx_getabscolor(src, src_x0, src_y1);                         \
		video_color_t src_y1_x1 = video_gfx_getabscolor(src, src_x1, src_y1);                         \
		video_color_t out       = interpolate_2d(src_y0_x0, src_y0_x1,                                \
		                                         src_y1_x0, src_y1_x1,                                \
		                                         frac_x0, frac_x1,                                    \
		                                         frac_y0, frac_y1);                                   \
		video_gfx_putabscolor(dst, dst_x, dst_y, out);                                                \
	}

	TRACE_START("generic__stretch_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   src_x_, src_y_, src_size_x_, src_size_y_,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("generic__stretch_l()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic__stretch_n(struct video_blit *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                video_coord_t src_x, video_coord_t src_y,
                                video_dim_t src_size_x, video_dim_t src_size_y) {
	video_dim_t y;
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	stretch_fp_t step_x, step_y, src_pos_y;
	TRACE_START("generic__stretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y  = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = src_y + STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		src_pos_x += STRETCH_FP(src_x);
		do {
			video_color_t color;
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			color = video_gfx_getabscolor(src, row_src_x, row_src_y);
			video_gfx_putabscolor(dst, dst_x + x, row_dst_y, color);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("generic__stretch_n()\n");
}



INTERN NONNULL((1, 10)) void CC
libvideo_gfx_generic__bitstretch_l(struct video_blit *__restrict self,
                                   video_coord_t dst_x_, video_coord_t dst_y_,
                                   video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                   video_coord_t src_x_, video_coord_t src_y_,
                                   video_dim_t src_size_x_, video_dim_t src_size_y_,
                                   struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip = bm->vbm_skip + src_x_ + src_y_ * bm->vbm_scan;
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
#define makealpha(raw_alpha, alpha_chan) \
	(channel_t)(((twochannels_t)(raw_alpha) * (alpha_chan)) / CHANNEL_MAX)
#define makecolor(color, alpha_chan)       \
	(((color) & ~VIDEO_COLOR_ALPHA_MASK) | \
	 ((video_color_t)makealpha(VIDEO_COLOR_GET_ALPHA(color), alpha_chan) << VIDEO_COLOR_ALPHA_SHIFT))
	if (bitskip > NBBY) {
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
	}

#define getbit(src_x, src_y)   bitmask2d_getbit(bitmask, bm->vbm_scan, (video_coord_t)bitskip + src_x, src_y)
#define getcolor(src_x, src_y) video_gfx_getabscolor(src, src_x, src_y)

#define bitstretch_blend_xmax_ymin bitstretch_blend_xmin_ymin
#define bitstretch_blend_xmin_ymax bitstretch_blend_xmin_ymin
#define bitstretch_blend_xmax_ymax bitstretch_blend_xmin_ymin
#define bitstretch_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)    \
	{                                                                                     \
		if (getbit(src_x, src_y)) {                                                       \
			video_color_t out = getcolor(src_x, src_y);                                   \
			(*dst->vx_xops.vgxo_absfill)(dst, dst_x, dst_y, dst_size_x, dst_size_y, out); \
		}                                                                                 \
	}

#define bitstretch_blend_ymax bitstretch_blend_ymin
#define bitstretch_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                            \
		channel_t chan_y0_x0 = getbit(src_x0, src_y);                                            \
		channel_t chan_y0_x1 = getbit(src_x1, src_y);                                            \
		channel_t chan = interpolate_channel_1d(chan_y0_x0, chan_y0_x1, frac_x0, frac_x1);       \
		if (chan) {                                                                              \
			video_color_t src_y0_x0 = getcolor(src_x0, src_y);                                   \
			video_color_t src_y0_x1 = getcolor(src_x1, src_y);                                   \
			video_color_t color = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);        \
			video_color_t out = makecolor(color, chan);                                          \
			(*dst->vx_xops.vgxo_absline_v)(dst, dst_x, dst_y, dst_size_y, out);                  \
		}                                                                                        \
	}

#define bitstretch_blend_xmax bitstretch_blend_xmin
#define bitstretch_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                            \
		channel_t chan_y0_x0 = getbit(src_x, src_y0);                                            \
		channel_t chan_y1_x0 = getbit(src_x, src_y1);                                            \
		channel_t chan = interpolate_channel_1d(chan_y0_x0, chan_y1_x0, frac_y0, frac_y1);       \
		if (chan) {                                                                              \
			video_color_t src_y0_x0 = getcolor(src_x, src_y0);                                   \
			video_color_t src_y1_x0 = getcolor(src_x, src_y1);                                   \
			video_color_t color = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);        \
			video_color_t out = makecolor(color, chan);                                          \
			(*dst->vx_xops.vgxo_absline_h)(dst, dst_x, dst_y, dst_size_x, out);                  \
		}                                                                                        \
	}

#define bitstretch_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                      \
		channel_t chan_y0_x0 = getbit(src_x0, src_y0);                                                     \
		channel_t chan_y0_x1 = getbit(src_x1, src_y0);                                                     \
		channel_t chan_y1_x0 = getbit(src_x0, src_y1);                                                     \
		channel_t chan_y1_x1 = getbit(src_x1, src_y1);                                                     \
		channel_t chan = interpolate_channel_2d(chan_y0_x0, chan_y0_x1,                                    \
		                                        chan_y1_x0, chan_y1_x1,                                    \
		                                        frac_x0, frac_x1,                                          \
		                                        frac_y0, frac_y1);                                         \
		if (chan) {                                                                                        \
			video_color_t src_y0_x0 = getcolor(src_x0, src_y0);                                            \
			video_color_t src_y0_x1 = getcolor(src_x1, src_y0);                                            \
			video_color_t src_y1_x0 = getcolor(src_x0, src_y1);                                            \
			video_color_t src_y1_x1 = getcolor(src_x1, src_y1);                                            \
			video_color_t color = interpolate_2d(src_y0_x0, src_y0_x1,                                     \
			                                     src_y1_x0, src_y1_x1,                                     \
			                                     frac_x0, frac_x1,                                         \
			                                     frac_y0, frac_y1);                                        \
			video_color_t out = makecolor(color, chan);                                                    \
			video_gfx_putabscolor(dst, dst_x, dst_y, out);                                                 \
		}                                                                                                  \
	}

	TRACE_START("generic__bitstretch_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_, bm);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   src_x_, src_y_, src_size_x_, src_size_y_,
	                   bitstretch_blend_xmin_ymin,
	                   bitstretch_blend_ymin,
	                   bitstretch_blend_xmax_ymin,
	                   bitstretch_blend_xmin,
	                   bitstretch_blend,
	                   bitstretch_blend_xmax,
	                   bitstretch_blend_xmin_ymax,
	                   bitstretch_blend_ymax,
	                   bitstretch_blend_xmax_ymax);
	TRACE_END("generic__bitstretch_l()\n");
#undef bitstretch_blend_xmin_ymin
#undef bitstretch_blend_ymin
#undef bitstretch_blend_xmax_ymin
#undef bitstretch_blend_xmin
#undef bitstretch_blend
#undef bitstretch_blend_xmax
#undef bitstretch_blend_xmin_ymax
#undef bitstretch_blend_ymax
#undef bitstretch_blend_xmax_ymax

#undef getbit
#undef makealpha
#undef makecolor
}

INTERN NONNULL((1, 10)) void CC
libvideo_gfx_generic__bitstretch_n(struct video_blit *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t dst_size_x, video_dim_t dst_size_y,
                                   video_coord_t src_x, video_coord_t src_y,
                                   video_dim_t src_size_x, video_dim_t src_size_y,
                                   struct video_bitmask const *__restrict bm) {
	video_dim_t y;
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	stretch_fp_t step_x, step_y, src_pos_y;
	uintptr_t bm_skip = bm->vbm_skip + src_x + src_y * bm->vbm_scan;
	TRACE_START("generic__bitstretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y, bm);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = src_y + STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		uintptr_t row_bitno = bm_skip + row_src_y * bm->vbm_scan;
		src_pos_x += STRETCH_FP(src_x);
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			uintptr_t bitno = row_bitno + row_src_x;
			if (((byte_t const *)bm->vbm_mask)[bitno / NBBY] & ((byte_t)1 << ((NBBY - 1) - (bitno % NBBY)))) {
				video_color_t color;
				color = video_gfx_getabscolor(src, row_src_x, row_src_y);
				video_gfx_putabscolor(dst, dst_x + x, row_dst_y, color);
			}
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("generic__bitstretch_n()\n");
}

/* Special impls for when the blit src/dst are identical */
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_samebuf__blit(struct video_blit *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_coord_t src_x, video_coord_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	/* TODO */
	libvideo_gfx_generic__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_samebuf__stretch_l(struct video_blit *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_coord_t src_x, video_coord_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_gfx_generic__stretch_l(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_samebuf__stretch_n(struct video_blit *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_coord_t src_x, video_coord_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_gfx_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
}

INTERN NONNULL((1, 8)) void CC
libvideo_gfx_generic_samebuf__bitblit(struct video_blit *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_coord_t src_x, video_coord_t src_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y, bm);
}

INTERN NONNULL((1, 10)) void CC
libvideo_gfx_generic_samebuf__bitstretch_l(struct video_blit *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_coord_t src_x, video_coord_t src_y,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__bitstretch_l(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                   src_x, src_y, src_size_x, src_size_y, bm);
}

INTERN NONNULL((1, 10)) void CC
libvideo_gfx_generic_samebuf__bitstretch_n(struct video_blit *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_coord_t src_x, video_coord_t src_y,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__bitstretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                   src_x, src_y, src_size_x, src_size_y, bm);
}







/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                                                                      */
/* PUBLIC API                                                           */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/




/************************************************************************/
/* CLIP()                                                               */
/************************************************************************/
INTERN ATTR_RETNONNULL NONNULL((1)) struct video_gfx *CC
libvideo_gfx_generic_clip(struct video_gfx *__restrict self,
                          video_offset_t clip_x, video_offset_t clip_y,
                          video_dim_t size_x, video_dim_t size_y) {
	video_offset_t cxend, cyend;
	if unlikely(!size_x || !size_y)
		goto empty_clip;

	/* Adjust clip rect */
	self->vx_cxoff += clip_x;
	self->vx_cyoff += clip_y;
	self->vx_cxsiz = size_x;
	self->vx_cysiz = size_y;

	/* Clamp buffer rect according to new clip rect */
	if ((video_offset_t)self->vx_bxmin < self->vx_cxoff) {
		self->vx_bxmin = (video_coord_t)self->vx_cxoff;
		if (self->vx_bxend <= self->vx_bxmin)
			goto empty_clip;
//		self->vx_bxsiz = self->vx_bxend - self->vx_bxmin;
	}
	if ((video_offset_t)self->vx_bymin < self->vx_cyoff) {
		self->vx_bymin = (video_coord_t)self->vx_cyoff;
		if (self->vx_byend <= self->vx_bymin)
			goto empty_clip;
//		self->vx_bysiz = self->vx_byend - self->vx_bymin;
	}

	if (!OVERFLOW_SADD(self->vx_cxoff, size_x, &cxend) &&
	    self->vx_bxend > (video_coord_t)cxend && cxend > 0) {
		self->vx_bxend = (video_coord_t)cxend;
		if (self->vx_bxend <= self->vx_bxmin)
			goto empty_clip;
//		self->vx_bxsiz = self->vx_bxend - self->vx_bxmin;
	}
	if (!OVERFLOW_SADD(self->vx_cyoff, size_y, &cyend) &&
	    self->vx_byend > (video_coord_t)cyend && cyend > 0) {
		self->vx_byend = (video_coord_t)cyend;
		if (self->vx_byend <= self->vx_bymin)
			goto empty_clip;
//		self->vx_bysiz = self->vx_byend - self->vx_bymin;
	}
	return self;
empty_clip:
	libvideo_gfx_setempty(self);
	return self;
}







/************************************************************************/
/* GETCOLOR()                                                           */
/************************************************************************/
INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_generic_getcolor(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y) {
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		return (*self->vx_xops.vgxo_getcolor)(self, (video_coord_t)x, (video_coord_t)y);
	return 0;
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_generic_getcolor_rdwrap(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_FRDXWRAP)
		x = wrap(x, self->vx_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FRDYWRAP)
		y = wrap(y, self->vx_cysiz);
	return libvideo_gfx_generic_getcolor(self, x, y);
}



/************************************************************************/
/* PUTCOLOR()                                                           */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_putcolor(struct video_gfx *__restrict self,
                              video_offset_t x, video_offset_t y,
                              video_color_t color) {
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		(*self->vx_xops.vgxo_putcolor)(self, (video_coord_t)x, (video_coord_t)y, color);
}
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_putcolor_wrwrap(struct video_gfx *__restrict self,
                                     video_offset_t x, video_offset_t y,
                                     video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP)
		x = wrap(x, self->vx_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP)
		y = wrap(y, self->vx_cysiz);
	libvideo_gfx_generic_putcolor(self, x, y, color);
}


/************************************************************************/
/* LINE()                                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_line(struct video_gfx *__restrict self,
                          video_offset_t x1, video_offset_t y1,
                          video_offset_t x2, video_offset_t y2,
                          video_color_t color) {
	/* >> Cohen-Sutherland algorithm
	 * https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm */
	int outcode0, outcode1, outcodeOut;
	video_offset_t temp, x, y;
#define COHSUTH_INSIDE 0 /* 0000 */
#define COHSUTH_XMIN   1 /* 0001 */
#define COHSUTH_XMAX   2 /* 0010 */
#define COHSUTH_YMIN   4 /* 0100 */
#define COHSUTH_YMAX   8 /* 1000 */
	x1 += self->vx_cxoff;
	y1 += self->vx_cyoff;
	x2 += self->vx_cxoff;
	y2 += self->vx_cyoff;
#define COHSUTH_COMPUTEOUTCODE(x, y, result)           \
	do {                                               \
		(result) = COHSUTH_INSIDE;                     \
		if ((x) < (video_offset_t)GFX_BXMIN) {         \
			(result) |= COHSUTH_XMIN;                  \
		} else if ((x) >= (video_offset_t)GFX_BXEND) { \
			(result) |= COHSUTH_XMAX;                  \
		}                                              \
		if ((y) < (video_offset_t)GFX_BYMIN) {         \
			(result) |= COHSUTH_YMIN;                  \
		} else if ((y) >= (video_offset_t)GFX_BYEND) { \
			(result) |= COHSUTH_YMAX;                  \
		}                                              \
	}	__WHILE0
	COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
	COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
	while ((outcode0 | outcode1) != 0) {
		if ((outcode0 & outcode1) != 0)
			return;
		outcodeOut = outcode0 ? outcode0 : outcode1;
		if ((outcodeOut & COHSUTH_YMAX) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMAX - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMAX;
		} else if ((outcodeOut & COHSUTH_YMIN) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMIN - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMIN;
		} else if ((outcodeOut & COHSUTH_XMAX) != 0) {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMAX - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMAX;
		} else /*if ((outcodeOut & COHSUTH_XMIN) != 0)*/ {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMIN - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMIN;
		}
		if (outcodeOut == outcode0) {
			x1 = x;
			y1 = y;
			COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
		} else {
			x2 = x;
			y2 = y;
			COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
		}
	}
	ASSERT_ABS_COORDS(self, (video_coord_t)x1, (video_coord_t)y1);
	ASSERT_ABS_COORDS(self, (video_coord_t)x2, (video_coord_t)y2);

	/* Coords are clamped! --> Now select the proper line algorithm */
	if (x1 > x2) {
		temp = x2, x2 = x1, x1 = temp;
		temp = y2, y2 = y1, y1 = temp;
	} else if (x1 == x2) {
		if (y1 > y2) {
			temp = y2;
			y2   = y1;
			y1   = temp;
		} else if (y1 == y2) {
			video_gfx_putabscolor(self,
			                      (video_coord_t)x1,
			                      (video_coord_t)y1,
			                      color);
			return;
		}
		(*self->vx_xops.vgxo_absline_v)(self, (video_coord_t)x1, (video_coord_t)y1,
		                                (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1,
		                                color);
		return;
	}
	assert(x2 > x1);
	if (y2 > y1) {
		(*self->vx_xops.vgxo_absline_llhh)(self, (video_coord_t)x1, (video_coord_t)y1,
		                                   (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1,
		                                   (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1,
		                                   color);
	} else if (y2 < y1) {
		(*self->vx_xops.vgxo_absline_lhhl)(self, (video_coord_t)x1, (video_coord_t)y1,
		                                   (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1,
		                                   (video_dim_t)((video_coord_t)y1 - (video_coord_t)y2) + 1,
		                                   color);
	} else {
		(*self->vx_xops.vgxo_absline_h)(self, (video_coord_t)x1, (video_coord_t)y1,
		                                (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1,
		                                color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_line_wrwrap(struct video_gfx *__restrict self,
                                 video_offset_t x1, video_offset_t y1,
                                 video_offset_t x2, video_offset_t y2,
                                 video_color_t color) {
	/* TODO */
	libvideo_gfx_generic_line(self, x1, y1, x2, y2, color);
}



/************************************************************************/
/* HLINE()                                                              */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_hline(struct video_gfx *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if unlikely(y < (video_offset_t)GFX_BYMIN)
		return;
	if unlikely(y >= (video_offset_t)GFX_BYEND)
		return;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(length <= off)
			return;
		length -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, length, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		length = GFX_BXEND - (video_coord_t)x;
	}

	(*self->vx_xops.vgxo_absline_h)(self, (video_coord_t)x, (video_coord_t)y, length, color);
}


INTERN NONNULL((1)) void CC
libvideo_gfx_generic_hline_wrwrap(struct video_gfx *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP)
		y = wrap(y, self->vx_cysiz);
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, length, &cxend) || length >= self->vx_cxsiz) {
			x = 0;
			length = self->vx_cxsiz;
		} else if (cxend > self->vx_cxsiz) {
			libvideo_gfx_generic_hline(self, 0, y, cxend - self->vx_cxsiz, color);
		}
	}
	libvideo_gfx_generic_hline(self, x, y, length, color);
}



/************************************************************************/
/* VLINE()                                                              */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_vline(struct video_gfx *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN)
		return;
	if unlikely(x >= (video_offset_t)GFX_BXEND)
		return;
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(length <= off)
			return;
		length -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, length, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		length = GFX_BYEND - (video_coord_t)y;
	}
	(*self->vx_xops.vgxo_absline_v)(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_vline_wrwrap(struct video_gfx *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP)
		x = wrap(x, self->vx_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, length, &cyend) || length >= self->vx_cysiz) {
			y = 0;
			length = self->vx_cysiz;
		} else if (cyend > self->vx_cysiz) {
			libvideo_gfx_generic_vline(self, x, 0, cyend - self->vx_cysiz, color);
		}
	}
	libvideo_gfx_generic_vline(self, x, y, length, color);
}



/************************************************************************/
/* FILL()                                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_fill(struct video_gfx *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
	}
	(*self->vx_xops.vgxo_absfill)(self, (video_coord_t)x, (video_coord_t)y,
	                              size_x, size_y, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_fill_wrwrap(struct video_gfx *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_cxsiz) {
			x = 0;
			size_x = self->vx_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_cysiz) {
			y = 0;
			size_y = self->vx_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) /* Must do a partial fill at the top-left */
		libvideo_gfx_generic_fill(self, 0, 0, xwrap, ywrap, color);
	if (xwrap) /* Must do a partial fill at the left */
		libvideo_gfx_generic_fill(self, 0, y, xwrap, size_y, color);
	if (ywrap) /* Must do a partial fill at the top */
		libvideo_gfx_generic_fill(self, x, 0, size_x, ywrap, color);
	libvideo_gfx_generic_fill(self, x, y, size_x, size_y, color);
}



/************************************************************************/
/* RECT()                                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
libvideo_gfx_generic_rect(struct video_gfx *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_dim_t temp;
#define LINE_XMIN 0x1
#define LINE_YMIN 0x2
#define LINE_XMAX 0x4
#define LINE_YMAX 0x8
	uint8_t draw_lines;
	if unlikely(!size_x || !size_y)
		return;
	draw_lines = 0xf;
	x += self->vx_cxoff;
	y += self->vx_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		draw_lines &= ~LINE_XMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		draw_lines &= ~LINE_YMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
		draw_lines &= ~LINE_XMAX;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
		draw_lines &= ~LINE_YMAX;
	}
#define HLINE(x, y, length) (*self->vx_xops.vgxo_absline_h)(self, x, y, length, color)
#define VLINE(x, y, length) (*self->vx_xops.vgxo_absline_v)(self, x, y, length, color)
	switch (draw_lines) {

		/* All 4 lines */
	case LINE_XMIN | LINE_YMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3) {
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
				if (size_x >= 2)
					VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
			}
		}
		break;

		/* 3-line combinations */
	case LINE_YMIN | LINE_YMAX | LINE_XMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
		}
		break;

	case LINE_YMIN | LINE_YMAX | LINE_XMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		}
		break;

		/* Adjacent lines */
	case LINE_XMIN | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		break;

	case LINE_XMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		break;


		/* Opposing lines */
	case LINE_XMIN | LINE_XMAX:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN */
		if (size_x >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y); /* XMAX */
		break;

	case LINE_YMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		break;

		/* Single lines */
	case LINE_XMAX:
		x += size_x - 1;
		ATTR_FALLTHROUGH
	case LINE_XMIN:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN / XMAX */
		break;

	case LINE_YMAX:
		y += size_y - 1;
		ATTR_FALLTHROUGH
	case LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN / YMAX */
		break;

	case 0: /* Completely out-of-bounds */
		break;

	default:
		__builtin_unreachable();
	}
#undef VLINE
#undef HLINE
}

INTERN NONNULL((1)) void CC
libvideo_gfx_generic_rect_wrwrap(struct video_gfx *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	if (size_x <= 1) {
		if unlikely(!size_x)
			return;
		libvideo_gfx_generic_vline_wrwrap(self, x, y, size_y, color);
	} else if (size_y <= 1) {
		if unlikely(!size_y)
			return;
		libvideo_gfx_generic_hline_wrwrap(self, x, y, size_x, color);
	} else {
		video_offset_t ymax = y + size_y - 1;
		libvideo_gfx_generic_hline_wrwrap(self, x, y, size_x, color);
		libvideo_gfx_generic_hline_wrwrap(self, x, ymax, size_x, color);
		if (size_y > 2) {
			video_offset_t xmax = x + size_x - 1;
			libvideo_gfx_generic_vline_wrwrap(self, x, y + 1, size_y - 2, color);
			libvideo_gfx_generic_vline_wrwrap(self, xmax, y + 1, size_y - 2, color);
		}
	}
}




/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_generic_bitfill(struct video_gfx *__restrict self,
                             video_offset_t dst_x, video_offset_t dst_y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t color,
                             struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if (!size_x || !size_y)
		return;
	dst_x += self->vx_cxoff;
	dst_y += self->vx_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= size_x)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += ((video_coord_t)dst_y) * fixed_bm.vbm_scan;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)GFX_BYMIN;
	}
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)dst_y;
	}
	(*self->vx_xops.vgxo_bitfill)(self,
	                              (video_coord_t)dst_x,
	                              (video_coord_t)dst_y,
	                              size_x, size_y, color, bm);
}

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_generic_bitfill_wrwrap(struct video_gfx *__restrict self,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t color,
                                    struct video_bitmask const *__restrict bm) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_cxsiz);
		if (size_x > self->vx_cxsiz)
			size_x = self->vx_cxsiz;
		cxend = (video_coord_t)dst_x + size_x;
		if (OVERFLOW_USUB(cxend, self->vx_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_cysiz);
		if (size_y > self->vx_cysiz)
			size_y = self->vx_cysiz;
		cyend = (video_coord_t)dst_y + size_y;
		if (OVERFLOW_USUB(cyend, self->vx_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_cysiz - (video_coord_t)dst_y;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb + (yinb * chunk_bm.vbm_scan);
		libvideo_gfx_generic_bitfill(self, 0, 0, xwrap, ywrap, color, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb;
		libvideo_gfx_generic_bitfill(self, 0, dst_y, xwrap, size_y, color, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += yinb * chunk_bm.vbm_scan;
		libvideo_gfx_generic_bitfill(self, dst_x, 0, size_x, ywrap, color, &chunk_bm);
	}
	libvideo_gfx_generic_bitfill(self, dst_x, dst_y, xinb, yinb, color, bm);
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_generic_bitstretchfill(struct video_gfx *__restrict self,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_color_t color,
                                    video_dim_t src_size_x, video_dim_t src_size_y,
                                    struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	dst_x += self->vx_cxoff;
	dst_y += self->vx_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		video_dim_t srcpart;
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= dst_size_x)
			return;
		srcpart = ((video_coord_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (video_coord_t)dst_x;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		video_dim_t srcpart;
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= dst_size_y)
			return;
		srcpart = ((video_coord_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (video_coord_t)dst_y;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart * fixed_bm.vbm_scan;
		dst_y = (video_offset_t)GFX_BYMIN;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &temp) || temp > GFX_BXEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		newdstsize = GFX_BXEND - (video_coord_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &temp) || temp > GFX_BYEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		newdstsize = GFX_BYEND - (video_coord_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
	if (dst_size_x == src_size_x && dst_size_y == src_size_y) {
		/* Can use copy-blit */
		(*self->vx_xops.vgxo_bitfill)(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                              dst_size_x, dst_size_y, color, bm);
	} else {
		/* Must use stretch-blit */
		(*self->vx_xops.vgxo_bitstretchfill)(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                                     dst_size_x, dst_size_y, color,
		                                     src_size_x, src_size_y, bm);
	}
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_generic_bitstretchfill_wrwrap(struct video_gfx *__restrict self,
                                           video_offset_t dst_x, video_offset_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_color_t color,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm) {
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_cxsiz);
		if (dst_size_x > self->vx_cxsiz) {
			src_size_x = xdst2src(self->vx_cxsiz);
			dst_size_x = self->vx_cxsiz;
		}
		cxend = (video_coord_t)dst_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, self->vx_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_cysiz);
		if (dst_size_y > self->vx_cysiz) {
			src_size_y = ydst2src(self->vx_cysiz);
			dst_size_y = self->vx_cysiz;
		}
		cyend = (video_coord_t)dst_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, self->vx_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_cysiz - (video_coord_t)dst_y;
		}
	}

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_x + (chunk_src_y * chunk_bm.vbm_scan);
		libvideo_gfx_generic_bitstretchfill(self, 0, 0, xwrap, ywrap, color,
		                                    chunk_src_size_x, chunk_src_size_y, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		chunk_bm.vbm_skip += chunk_src_x;
		libvideo_gfx_generic_bitstretchfill(self, 0, dst_y, xwrap, dst_size_y, color,
		                                    chunk_src_size_x, src_size_y, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_y * chunk_bm.vbm_scan;
		libvideo_gfx_generic_bitstretchfill(self, dst_x, 0, dst_size_x, ywrap, color,
		                                    src_size_x, chunk_src_size_y, &chunk_bm);
	}
	libvideo_gfx_generic_bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                    color, src_size_x, src_size_y, bm);
#undef xdst2src
#undef ydst2src
}



INTERN ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC
libvideo_gfx_generic__blitfrom_l(struct video_blit *__restrict ctx) {
	video_blit_setops(ctx);
	if (ctx->vb_src->vx_buffer == ctx->vb_dst->vx_buffer) {
		/* Need to use different impls here that essentially do a "memmove"-style blit,
		 * rather  than the usual  "memcpy"-style one (since in  this case, writing new
		 * pixels in an  incorrect order might  clobber other pixels  that have yet  to
		 * be read) */
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic_samebuf__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic_samebuf__bitblit;
		ctx->vb_xops.vbxo_stretch    = &libvideo_gfx_generic_samebuf__stretch_l;
		ctx->vb_xops.vbxo_bitstretch = &libvideo_gfx_generic_samebuf__bitstretch_l;
	} else {
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic__bitblit;
		ctx->vb_xops.vbxo_stretch    = &libvideo_gfx_generic__stretch_l;
		ctx->vb_xops.vbxo_bitstretch = &libvideo_gfx_generic__bitstretch_l;
	}
	return ctx;
}

INTERN ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC
libvideo_gfx_generic__blitfrom_n(struct video_blit *__restrict ctx) {
	video_blit_setops(ctx);
	if (ctx->vb_src->vx_buffer == ctx->vb_dst->vx_buffer) {
		/* Need to use different impls here that essentially do a "memmove"-style blit,
		 * rather  than the usual  "memcpy"-style one (since in  this case, writing new
		 * pixels in an  incorrect order might  clobber other pixels  that have yet  to
		 * be read) */
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic_samebuf__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic_samebuf__bitblit;
		ctx->vb_xops.vbxo_stretch    = &libvideo_gfx_generic_samebuf__stretch_n;
		ctx->vb_xops.vbxo_bitstretch = &libvideo_gfx_generic_samebuf__bitstretch_n;
	} else {
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic__bitblit;
		ctx->vb_xops.vbxo_stretch    = &libvideo_gfx_generic__stretch_n;
		ctx->vb_xops.vbxo_bitstretch = &libvideo_gfx_generic__bitstretch_n;
	}
	return ctx;
}


#undef libvideo_gfx_generic_ops
#undef libvideo_gfx_generic_ops_rdwrap
#undef libvideo_gfx_generic_ops_wrwrap
#undef libvideo_gfx_generic_ops_rdwrwrap
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_rdwrap = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_wrwrap = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_rdwrwrap = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops(void) {
	if unlikely(!libvideo_gfx_generic_ops.fxo_bitstretchfill) {
		libvideo_gfx_generic_ops.fxo_clip     = &libvideo_gfx_generic_clip;
		libvideo_gfx_generic_ops.fxo_getcolor = &libvideo_gfx_generic_getcolor;
		libvideo_gfx_generic_ops.fxo_putcolor = &libvideo_gfx_generic_putcolor;
		libvideo_gfx_generic_ops.fxo_line     = &libvideo_gfx_generic_line;
		libvideo_gfx_generic_ops.fxo_hline    = &libvideo_gfx_generic_hline;
		libvideo_gfx_generic_ops.fxo_vline    = &libvideo_gfx_generic_vline;
		libvideo_gfx_generic_ops.fxo_fill     = &libvideo_gfx_generic_fill;
		libvideo_gfx_generic_ops.fxo_rect     = &libvideo_gfx_generic_rect;
		libvideo_gfx_generic_ops.fxo_bitfill  = &libvideo_gfx_generic_bitfill;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_rdwrap.fxo_bitstretchfill) {
		libvideo_gfx_generic_ops_rdwrap.fxo_clip     = &libvideo_gfx_generic_clip;
		libvideo_gfx_generic_ops_rdwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor_rdwrap;
		libvideo_gfx_generic_ops_rdwrap.fxo_putcolor = &libvideo_gfx_generic_putcolor;
		libvideo_gfx_generic_ops_rdwrap.fxo_line     = &libvideo_gfx_generic_line;
		libvideo_gfx_generic_ops_rdwrap.fxo_hline    = &libvideo_gfx_generic_hline;
		libvideo_gfx_generic_ops_rdwrap.fxo_vline    = &libvideo_gfx_generic_vline;
		libvideo_gfx_generic_ops_rdwrap.fxo_fill     = &libvideo_gfx_generic_fill;
		libvideo_gfx_generic_ops_rdwrap.fxo_rect     = &libvideo_gfx_generic_rect;
		libvideo_gfx_generic_ops_rdwrap.fxo_bitfill  = &libvideo_gfx_generic_bitfill;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_rdwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_rdwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_wrwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_wrwrap.fxo_bitstretchfill) {
		libvideo_gfx_generic_ops_wrwrap.fxo_clip     = &libvideo_gfx_generic_clip;
		libvideo_gfx_generic_ops_wrwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor;
		libvideo_gfx_generic_ops_wrwrap.fxo_putcolor = &libvideo_gfx_generic_putcolor_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_line     = &libvideo_gfx_generic_line_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_hline    = &libvideo_gfx_generic_hline_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_vline    = &libvideo_gfx_generic_vline_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_fill     = &libvideo_gfx_generic_fill_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_rect     = &libvideo_gfx_generic_rect_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_bitfill  = &libvideo_gfx_generic_bitfill_wrwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_wrwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill_wrwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_wrwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_rdwrwrap.fxo_bitstretchfill) {
		libvideo_gfx_generic_ops_rdwrwrap.fxo_clip     = &libvideo_gfx_generic_clip;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor_rdwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_putcolor = &libvideo_gfx_generic_putcolor_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_line     = &libvideo_gfx_generic_line_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_hline    = &libvideo_gfx_generic_hline_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_vline    = &libvideo_gfx_generic_vline_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_fill     = &libvideo_gfx_generic_fill_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_rect     = &libvideo_gfx_generic_rect_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_bitfill  = &libvideo_gfx_generic_bitfill_wrwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_rdwrwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill_wrwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_rdwrwrap;
}
#define libvideo_gfx_generic_ops          (*_libvideo_gfx_generic_ops())
#define libvideo_gfx_generic_ops_rdwrap   (*_libvideo_gfx_generic_ops_rdwrap())
#define libvideo_gfx_generic_ops_wrwrap   (*_libvideo_gfx_generic_ops_wrwrap())
#define libvideo_gfx_generic_ops_rdwrwrap (*_libvideo_gfx_generic_ops_rdwrwrap())



/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/

#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_libvideo_gfx_generic_blit__and__stretch
#include "gfx/generic-blit.c.inl"
#define DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch
#include "gfx/generic-blit.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */

#undef libvideo_blit_generic_ops
#undef libvideo_blit_generic_ops_rdwrap
#undef libvideo_blit_generic_ops_wrap
PRIVATE struct video_blit_ops libvideo_blit_generic_ops = {};
PRIVATE struct video_blit_ops libvideo_blit_generic_ops_rdwrap = {};
PRIVATE struct video_blit_ops libvideo_blit_generic_ops_wrap = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops(void) {
	if unlikely(!libvideo_blit_generic_ops.vbo_bitstretch) {
		libvideo_blit_generic_ops.vbo_blit    = &libvideo_gfx_generic_blit;
		libvideo_blit_generic_ops.vbo_stretch = &libvideo_gfx_generic_stretch;
		libvideo_blit_generic_ops.vbo_bitblit = &libvideo_gfx_generic_bitblit;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops.vbo_bitstretch = &libvideo_gfx_generic_bitstretch;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops_rdwrap(void) {
	if unlikely(!libvideo_blit_generic_ops_rdwrap.vbo_bitstretch) {
		libvideo_blit_generic_ops_rdwrap.vbo_blit    = &libvideo_gfx_generic_blit_rdwrap;
		libvideo_blit_generic_ops_rdwrap.vbo_stretch = &libvideo_gfx_generic_stretch_rdwrap;
		libvideo_blit_generic_ops_rdwrap.vbo_bitblit = &libvideo_gfx_generic_bitblit_rdwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops_rdwrap.vbo_bitstretch = &libvideo_gfx_generic_bitstretch_rdwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops_rdwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops_wrap(void) {
	if unlikely(!libvideo_blit_generic_ops_wrap.vbo_bitstretch) {
		libvideo_blit_generic_ops_wrap.vbo_blit    = &libvideo_gfx_generic_blit_wrap;
		libvideo_blit_generic_ops_wrap.vbo_stretch = &libvideo_gfx_generic_stretch_wrap;
		libvideo_blit_generic_ops_wrap.vbo_bitblit = &libvideo_gfx_generic_bitblit_wrap;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops_wrap.vbo_bitstretch = &libvideo_gfx_generic_bitstretch_wrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops_wrap;
}
#define libvideo_blit_generic_ops        (*_libvideo_blit_generic_ops())
#define libvideo_blit_generic_ops_rdwrap (*_libvideo_blit_generic_ops_rdwrap())
#define libvideo_blit_generic_ops_wrap   (*_libvideo_blit_generic_ops_wrap())

DECL_END

#ifndef __INTELLISENSE__
#include "gfx/noblend.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
