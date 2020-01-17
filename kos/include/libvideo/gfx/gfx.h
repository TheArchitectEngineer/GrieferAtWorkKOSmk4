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
#ifndef _LIBVIDEO_GFX_GFX_H
#define _LIBVIDEO_GFX_GFX_H 1

#include <__stdinc.h>

#include <bits/types.h>

#include <libvideo/codec/pixel.h>

#ifdef __cplusplus
#include <type_traits>
#endif /* __cplusplus */

#include "api.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

__DECL_BEGIN


/* Surface blend definitions. */
#define GFX_BLENDMODE_ZERO                     0x00 /* 0 */
#define GFX_BLENDMODE_ONE                      0x01 /* 1  (max intensity; channel=0xff) */
#define GFX_BLENDMODE_SRC_COLOR                0x02 /* source_color */
#define GFX_BLENDMODE_ONE_MINUS_SRC_COLOR      0x03 /* 1 - source_color */
#define GFX_BLENDMODE_DST_COLOR                0x04 /* destination_color */
#define GFX_BLENDMODE_ONE_MINUS_DST_COLOR      0x05 /* 1 - destination_color */
#define GFX_BLENDMODE_SRC_ALPHA                0x06 /* source_alpha */
#define GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA      0x07 /* 1 - source_alpha */
#define GFX_BLENDMODE_DST_ALPHA                0x08 /* destination_alpha */
#define GFX_BLENDMODE_ONE_MINUS_DST_ALPHA      0x09 /* 1 - destination_alpha */
#define GFX_BLENDMODE_SRC_ALPHA_SATURATE       0x0a /* min(source_alpha, 1 - destination_alpha) */
#define GFX_BLENDMODE_CONSTANT_COLOR           0x0b /* CR/CG/CB */
#define GFX_BLENDMODE_ONE_MINUS_CONSTANT_COLOR 0x0c /* 1 - CR/CG/CB */
#define GFX_BLENDMODE_CONSTANT_ALPHA           0x0d /* CA */
#define GFX_BLENDMODE_ONE_MINUS_CONSTANT_ALPHA 0x0e /* 1 - CA */
/*      GFX_BLENDMODE_...                      0x0f  * ... */

#define GFX_BLENDFUNC_ADD                      0x00 /* a + b */
#define GFX_BLENDFUNC_SUBTRACT                 0x01 /* a - b */
#define GFX_BLENDFUNC_REVERSE_SUBTRACT         0x02 /* b - a */
#define GFX_BLENDFUNC_MIN                      0x03 /* a < b ? a : b */
#define GFX_BLENDFUNC_MAX                      0x04 /* a > b ? a : b */
/*      GFX_BLENDFUNC_...                      0x05  * ... */
/*      GFX_BLENDFUNC_...                      0x06  * ... */
/*      GFX_BLENDFUNC_...                      0x07  * ... */

#define GFX_BLENDINFO_GET_SRCRGB(info) (__CCAST(__uint8_t)((info)&0xf))        /* Source color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_SRCA(info)   (__CCAST(__uint8_t)(((info)>>4)&0xf))   /* Source alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTRGB(info) (__CCAST(__uint8_t)(((info)>>8)&0xf))   /* Destination color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTA(info)   (__CCAST(__uint8_t)(((info)>>12)&0xf))  /* Destination alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_FUNRGB(info) (__CCAST(__uint8_t)(((info)>>15)&0x7))  /* Color blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_FUNA(info)   (__CCAST(__uint8_t)(((info)>>18)&0x7))  /* Alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_CR(info)     (__CCAST(__uint8_t)(((info)>>56)&0xff)) /* Constant color red */
#define GFX_BLENDINFO_GET_CG(info)     (__CCAST(__uint8_t)(((info)>>48)&0xff)) /* Constant color green */
#define GFX_BLENDINFO_GET_CB(info)     (__CCAST(__uint8_t)(((info)>>40)&0xff)) /* Constant color blue */
#define GFX_BLENDINFO_GET_CA(info)     (__CCAST(__uint8_t)(((info)>>32)&0xff)) /* Constant color alpha */

/* Helper macros for creating blend modes.
 * @param: src:  Source color/alpha (One of `GFX_BLENDMODE_*')
 * @param: dst:  Destination color/alpha (One of `GFX_BLENDMODE_*')
 * @param: func: Color/alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO(src, dst, func) \
	GFX_BLENDINFO_EX(src, src, dst, dst, func, func, 0, 0, 0, 0)
#define GFX_BLENDINFO_EX(rgb_src, a_src, rgb_dst, a_dst, \
                         rgb_fun, a_fun, cr, cg, cb, ca) \
	(__CCAST(gfx_blendmode_t)((rgb_src)&0xf) |           \
	 (__CCAST(gfx_blendmode_t)((a_src)&0xf) << 4) |      \
	 (__CCAST(gfx_blendmode_t)((rgb_dst)&0xf) << 8) |    \
	 (__CCAST(gfx_blendmode_t)((a_dst)&0xf) << 12) |     \
	 (__CCAST(gfx_blendmode_t)((rgb_fun)&0x7) << 15) |   \
	 (__CCAST(gfx_blendmode_t)((a_fun)&0x7) << 18) |     \
	 (__CCAST(gfx_blendmode_t)((cr)&0xff) << 56) |       \
	 (__CCAST(gfx_blendmode_t)((cg)&0xff) << 48) |       \
	 (__CCAST(gfx_blendmode_t)((cb)&0xff) << 40) |       \
	 (__CCAST(gfx_blendmode_t)((ca)&0xff) << 32))
#ifdef __CC__
typedef __uint64_t gfx_blendmode_t;
#endif /* __CC__ */

/* Conventional alpha blending */
#define GFX_BLENDINFO_ALPHA \
	GFX_BLENDINFO(GFX_BLENDMODE_SRC_ALPHA, GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA, GFX_BLENDFUNC_ADD)

/* Override destination (no blending done) */
#define GFX_BLENDINFO_OVERRIDE \
	GFX_BLENDINFO(GFX_BLENDMODE_ONE, GFX_BLENDMODE_ZERO, GFX_BLENDFUNC_ADD)



/* Video graphic flags. */
#define VIDEO_GFX_FNORMAL     0x0000 /* Normal render flags. */
#define VIDEO_GFX_FAALINES    0x0001 /* Render smooth lines. */
#define VIDEO_GFX_FLINEARBLIT 0x0002 /* Use linear interpolation for stretch() (else: use nearest) */


#ifdef __CC__
struct video_buffer;
struct video_buffer_gfx;

struct video_gfx_ops {
	/* All of the following callbacks are [1..1] */

	/* Get the __color of a pixel */
	video_color_t (LIBVIDEO_GFX_CC *fxo_getcolor)(struct video_buffer_gfx const *__restrict __self,
	                                              __uintptr_t __x, __uintptr_t __y);
	/* Place a colored pixel ontop of the graphic */
	void (LIBVIDEO_GFX_CC *fxo_putcolor)(struct video_buffer_gfx *__restrict __self,
	                                     __uintptr_t __x, __uintptr_t __y, video_color_t __color);
	/* Draw a line */
	void (LIBVIDEO_GFX_CC *fxo_line)(struct video_buffer_gfx *__restrict __self,
	                                 __intptr_t __x1, __intptr_t __y1,
	                                 __intptr_t __x2, __intptr_t __y2,
	                                 video_color_t __color);
	/* Vertical line */
	void (LIBVIDEO_GFX_CC *fxo_vline)(struct video_buffer_gfx *__restrict __self, __uintptr_t __x,
	                                  __uintptr_t __y1, __uintptr_t __y2, video_color_t __color);
	/* Horizontal line */
	void (LIBVIDEO_GFX_CC *fxo_hline)(struct video_buffer_gfx *__restrict __self, __uintptr_t __y,
	                                  __uintptr_t __x1, __uintptr_t __x2, video_color_t __color);
	/* Fill an area with a solid __color. */
	void (LIBVIDEO_GFX_CC *fxo_fill)(struct video_buffer_gfx *__restrict __self,
	                                 __uintptr_t __x, __uintptr_t __y,
	                                 __size_t __size_x, __size_t __size_y,
	                                 video_color_t __color);
	/* Outline an area with a rectangle. */
	void (LIBVIDEO_GFX_CC *fxo_rect)(struct video_buffer_gfx *__restrict __self,
	                                 __uintptr_t __x, __uintptr_t __y,
	                                 __size_t __size_x, __size_t __size_y,
	                                 video_color_t __color);
	/* Blit the contents of another video buffer into this one. */
	void (LIBVIDEO_GFX_CC *fxo_blit)(struct video_buffer_gfx *__self,
	                                 __intptr_t __dst_x, __intptr_t __dst_y,
	                                 struct video_buffer_gfx const *__src,
	                                 __intptr_t __src_x, __intptr_t __src_y,
	                                 __size_t __size_x, __size_t __size_y);
	/* Same as `fxo_blit', but stretch the contents */
	void (LIBVIDEO_GFX_CC *fxo_stretch)(struct video_buffer_gfx *__self,
	                                    __intptr_t __dst_x, __intptr_t __dst_y,
	                                    __size_t __dst_size_x, __size_t __dst_size_y,
	                                    struct video_buffer_gfx const *__src,
	                                    __intptr_t __src_x, __intptr_t __src_y,
	                                    __size_t __src_size_x, __size_t __src_size_y);
};

/* Default GFX functions (using get/put pixel) */
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_LINE)(struct video_buffer_gfx *__restrict __self, __intptr_t __x1, __intptr_t __y1, __intptr_t __x2, __intptr_t __y2, video_color_t __color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_VLINE)(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y1, __uintptr_t __y2, video_color_t __color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_HLINE)(struct video_buffer_gfx *__restrict __self, __uintptr_t __y, __uintptr_t __x1, __uintptr_t __x2, video_color_t __color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_FILL)(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y, __size_t __size_x, __size_t __size_y, video_color_t __color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_RECT)(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y, __size_t __size_x, __size_t __size_y, video_color_t __color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_BLIT)(struct video_buffer_gfx *__self, __intptr_t __dst_x, __intptr_t __dst_y, struct video_buffer_gfx const *__src, __intptr_t __src_x, __intptr_t __src_y, __size_t __size_x, __size_t __size_y);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_STRETCH)(struct video_buffer_gfx *__self, __intptr_t __dst_x, __intptr_t __dst_y, __size_t __dst_size_x, __size_t __dst_size_y, struct video_buffer_gfx const *__src, __intptr_t __src_x, __intptr_t __src_y, __size_t __src_size_x, __size_t __src_size_y);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_line(struct video_buffer_gfx *__restrict __self, __intptr_t __x1, __intptr_t __y1, __intptr_t __x2, __intptr_t __y2, video_color_t __color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_vline(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y1, __uintptr_t __y2, video_color_t __color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_hline(struct video_buffer_gfx *__restrict __self, __uintptr_t __y, __uintptr_t __x1, __uintptr_t __x2, video_color_t __color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_fill(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y, __size_t __size_x, __size_t __size_y, video_color_t __color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_rect(struct video_buffer_gfx *__restrict __self, __uintptr_t __x, __uintptr_t __y, __size_t __size_x, __size_t __size_y, video_color_t __color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_blit(struct video_buffer_gfx *__self, __intptr_t __dst_x, __intptr_t __dst_y, struct video_buffer_gfx const *__src, __intptr_t __src_x, __intptr_t __src_y, __size_t __size_x, __size_t __size_y);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_stretch(struct video_buffer_gfx *__self, __intptr_t __dst_x, __intptr_t __dst_y, __size_t __dst_size_x, __size_t __dst_size_y, struct video_buffer_gfx const *__src, __intptr_t __src_x, __intptr_t __src_y, __size_t __src_size_x, __size_t __src_size_y);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


#ifdef __cplusplus
extern "C++" {
#endif /* __cplusplus */

struct video_buffer_gfx {
	struct video_gfx_ops bfx_ops;       /* [const] Graphics operations. */
	struct video_buffer *bfx_buffer;    /* [1..1][const] The associated buffer. */
	gfx_blendmode_t      bfx_blend;     /* [const] Blending mode. */
	__uintptr_t          bfx_flags;     /* [const] Additional rendering flags (Set of `VIDEO_GFX_F*'). */
	video_color_t        bfx_colorkey;  /* [const] Transparent __color key (or any __color with alpha=0 when disabled). */
	void                *bfx_driver[4]; /* [?..?] Driver-specific graphics data. */

#ifdef __cplusplus
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("getcolor")
#pragma push_macro("putcolor")
#pragma push_macro("line")
#pragma push_macro("vline")
#pragma push_macro("hline")
#pragma push_macro("fill")
#pragma push_macro("rect")
#pragma push_macro("blit")
#pragma push_macro("stretch")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef getcolor
#undef putcolor
#undef line
#undef vline
#undef hline
#undef fill
#undef rect
#undef blit
#undef stretch

public:
	/* Get a pixel */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, video_color_t>::type
	LIBVIDEO_GFX_CC getcolor(T __x, T __y) const {
		return (*bfx_ops.fxo_getcolor)(this, (__uintptr_t)__x, (__uintptr_t)__y);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, video_color_t>::type
	LIBVIDEO_GFX_CC getcolor(T __x, T __y) const {
		typedef typename std::make_unsigned<T>::type TU;
		if (__x < 0 || __y < 0)
			return 0;
		return getcolor<TU>((TU)__x, (TU)__y);
	}

	/* Place a colored pixel ontop of the graphic */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC putcolor(T __x, T __y, video_color_t __color) {
		(*bfx_ops.fxo_putcolor)(this, (__uintptr_t)__x, (__uintptr_t)__y, __color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	putcolor(T __x, T __y, video_color_t __color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (__x >= 0 && __y >= 0)
			putcolor<TU>((TU)__x, (TU)__y, __color);
	}

	/* Draw a line */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC line(__intptr_t __x1, __intptr_t __y1,
	                                            __intptr_t __x2, __intptr_t __y2,
	                                            video_color_t __color) {
		(*bfx_ops.fxo_line)(this, __x1, __y1, __x2, __y2, __color);
	}

	/* Vertical line */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC vline(T __x, T __y1, T __y2, video_color_t __color) {
		(*bfx_ops.fxo_vline)(this, (__uintptr_t)__x, (__uintptr_t)__y1, (__uintptr_t)__y2, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC vline(TX __x, TY __y1, TY __y2, video_color_t __color) {
		if (__x < 0)
			return;
		vline((__uintptr_t)__x, (__uintptr_t)__y1, (__uintptr_t)__y2, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC vline(TX __x, TY __y1, TY __y2, video_color_t __color) {
		if (__y1 < 0)
			__y1 = 0;
		if (__y2 < 0)
			__y2 = 0;
		vline((__uintptr_t)__x, (__uintptr_t)__y1, (__uintptr_t)__y2, __color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	LIBVIDEO_GFX_CC vline(T __x, T __y1, T __y2, video_color_t __color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (__x < 0)
			return;
		vline((TU)__x, __y1, __y2, __color);
	}

	/* Horizontal line */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC hline(T __y, T __x1, T __x2, video_color_t __color) {
		(*bfx_ops.fxo_hline)(this, (__uintptr_t)__y, (__uintptr_t)__x1, (__uintptr_t)__x2, __color);
	}
	template<class TY, class TX>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TY>::value && std::is_unsigned<TX>::value, void>::type
	LIBVIDEO_GFX_CC hline(TY __y, TX __x1, TX __x2, video_color_t __color) {
		if (__y < 0)
			return;
		hline((__uintptr_t)__y, (__uintptr_t)__x1, (__uintptr_t)__x2, __color);
	}
	template<class TY, class TX>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TY>::value && std::is_signed<TX>::value, void>::type
	LIBVIDEO_GFX_CC hline(TY __y, TX __x1, TX __x2, video_color_t __color) {
		if (__x1 < 0)
			__x1 = 0;
		if (__x2 < 0)
			__x2 = 0;
		hline((__uintptr_t)__y, (__uintptr_t)__x1, (__uintptr_t)__x2, __color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	LIBVIDEO_GFX_CC hline(T __y, T __x1, T __x2, video_color_t __color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (__y < 0)
			return;
		hline((TU)__y, __x1, __x2, __color);
	}

	/* Fill an area with a solid color. */
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC fill(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		(*bfx_ops.fxo_fill)(this, (__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC fill(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__x < 0) {
			__x = -__x;
			if (__size_x <= (__size_t)__x)
				return;
			__size_x -= (__size_t)__x;
			__x = 0;
		}
		if (__y < 0) {
			__y = -__y;
			if (__size_y <= (__size_t)__y)
				return;
			__size_y -= (__size_t)__y;
			__y = 0;
		}
		fill((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC fill(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__x < 0) {
			__x = -__x;
			if (__size_x <= (__size_t)__x)
				return;
			__size_x -= (__size_t)__x;
			__x = 0;
		}
		fill((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC fill(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__y < 0) {
			__y = -__y;
			if (__size_y <= (__size_t)__y)
				return;
			__size_y -= (__size_t)__y;
			__y = 0;
		}
		fill((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}

	/* Outline an area with a rectangle. */
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC rect(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		(*bfx_ops.fxo_rect)(this, (__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC rect(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__x < 0) {
			__x = -__x;
			if (__size_x <= (__size_t)__x)
				return;
			__size_x -= (__size_t)__x;
			__x = 0;
		}
		if (__y < 0) {
			__y = -__y;
			if (__size_y <= (__size_t)__y)
				return;
			__size_y -= (__size_t)__y;
			__y = 0;
		}
		rect((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC rect(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__x < 0) {
			__x = -__x;
			if (__size_x <= (__size_t)__x)
				return;
			__size_x -= (__size_t)__x;
			__x = 0;
		}
		rect((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC rect(TX __x, TY __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		if (__y < 0) {
			__y = -__y;
			if (__size_y <= (__size_t)__y)
				return;
			__size_y -= (__size_t)__y;
			__y = 0;
		}
		rect((__uintptr_t)__x, (__uintptr_t)__y, __size_x, __size_y, __color);
	}

	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC blit(__intptr_t __dst_x, __intptr_t __dst_y,
	                                            struct video_buffer_gfx const &__src,
	                                            __intptr_t __src_x, __intptr_t __src_y,
	                                            __size_t __size_x, __size_t __size_y) {
		(*bfx_ops.fxo_blit)(this, __dst_x, __dst_y,
		                    &__src, __src_x, __src_y,
		                    __size_x, __size_y);
	}

	/* Same as `fxo_blit', but stretch the contents */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC stretch(__intptr_t __dst_x, __intptr_t __dst_y,
	                                               __size_t __dst_size_x, __size_t __dst_size_y,
	                                               struct video_buffer_gfx const &__src,
	                                               __intptr_t __src_x, __intptr_t __src_y,
	                                               __size_t __src_size_x, __size_t __src_size_y) {
		(*bfx_ops.fxo_stretch)(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                       &__src, __src_x, __src_y, __src_size_x, __src_size_y);
	}

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("stretch")
#pragma pop_macro("blit")
#pragma pop_macro("rect")
#pragma pop_macro("fill")
#pragma pop_macro("hline")
#pragma pop_macro("vline")
#pragma pop_macro("line")
#pragma pop_macro("putcolor")
#pragma pop_macro("getcolor")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __cplusplus */
};

#ifdef __cplusplus
} /* extern "C++" */
#endif /* __cplusplus */
#endif /* __CC__ */



__DECL_END

#endif /* !_LIBVIDEO_GFX_GFX_H */
