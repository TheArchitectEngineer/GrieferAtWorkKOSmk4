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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_DECODE_CP437_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_DECODE_CP437_C_INL 1

#ifdef __INTELLISENSE__
#include "output.c"
DECL_BEGIN
#endif

/* Conversion table: LATIN-1 --> CP437 */
PRIVATE u8 const cp437_from_latin1[256] = {
/*[[[deemon
local l = [0] * 256;
l[0x00] = 0;
l[0x20] = 32;
l[0x21] = 33;
l[0x22] = 34;
l[0x23] = 35;
l[0x24] = 36;
l[0x25] = 37;
l[0x26] = 38;
l[0x27] = 39;
l[0x28] = 40;
l[0x29] = 41;
l[0x2A] = 42;
l[0x2B] = 43;
l[0x2C] = 44;
l[0x2D] = 45;
l[0x2E] = 46;
l[0x2F] = 47;
l[0x30] = 48;
l[0x31] = 49;
l[0x32] = 50;
l[0x33] = 51;
l[0x34] = 52;
l[0x35] = 53;
l[0x36] = 54;
l[0x37] = 55;
l[0x38] = 56;
l[0x39] = 57;
l[0x3A] = 58;
l[0x3B] = 59;
l[0x3C] = 60;
l[0x3D] = 61;
l[0x3E] = 62;
l[0x3F] = 63;
l[0x40] = 64;
l[0x41] = 65;
l[0x42] = 66;
l[0x43] = 67;
l[0x44] = 68;
l[0x45] = 69;
l[0x46] = 70;
l[0x47] = 71;
l[0x48] = 72;
l[0x49] = 73;
l[0x4A] = 74;
l[0x4B] = 75;
l[0x4C] = 76;
l[0x4D] = 77;
l[0x4E] = 78;
l[0x4F] = 79;
l[0x50] = 80;
l[0x51] = 81;
l[0x52] = 82;
l[0x53] = 83;
l[0x54] = 84;
l[0x55] = 85;
l[0x56] = 86;
l[0x57] = 87;
l[0x58] = 88;
l[0x59] = 89;
l[0x5A] = 90;
l[0x5B] = 91;
l[0x5C] = 92;
l[0x5D] = 93;
l[0x5E] = 94;
l[0x5F] = 95;
l[0x60] = 96;
l[0x61] = 97;
l[0x62] = 98;
l[0x63] = 99;
l[0x64] = 100;
l[0x65] = 101;
l[0x66] = 102;
l[0x67] = 103;
l[0x68] = 104;
l[0x69] = 105;
l[0x6A] = 106;
l[0x6B] = 107;
l[0x6C] = 108;
l[0x6D] = 109;
l[0x6E] = 110;
l[0x6F] = 111;
l[0x70] = 112;
l[0x71] = 113;
l[0x72] = 114;
l[0x73] = 115;
l[0x74] = 116;
l[0x75] = 117;
l[0x76] = 118;
l[0x77] = 119;
l[0x78] = 120;
l[0x79] = 121;
l[0x7A] = 122;
l[0x7B] = 123;
l[0x7C] = 124;
l[0x7D] = 125;
l[0x7E] = 126;
l[0xA0] = 255;
l[0xA1] = 173;
l[0xA2] = 155;
l[0xA3] = 156;
l[0xA5] = 157;
l[0xA7] = 21;
l[0xAA] = 166;
l[0xAB] = 174;
l[0xAC] = 170;
l[0xB0] = 248;
l[0xB1] = 241;
l[0xB2] = 253;
l[0xB5] = 230;
l[0xB6] = 20;
l[0xB7] = 250;
l[0xBA] = 167;
l[0xBB] = 175;
l[0xBC] = 172;
l[0xBD] = 171;
l[0xBF] = 168;
l[0xC4] = 142;
l[0xC5] = 143;
l[0xC6] = 146;
l[0xC7] = 128;
l[0xC9] = 144;
l[0xD1] = 165;
l[0xD6] = 153;
l[0xDC] = 154;
l[0xDF] = 225;
l[0xE0] = 133;
l[0xE1] = 160;
l[0xE2] = 131;
l[0xE4] = 132;
l[0xE5] = 134;
l[0xE6] = 145;
l[0xE7] = 135;
l[0xE8] = 138;
l[0xE9] = 130;
l[0xEA] = 136;
l[0xEB] = 137;
l[0xEC] = 141;
l[0xED] = 161;
l[0xEE] = 140;
l[0xEF] = 139;
l[0xF1] = 164;
l[0xF2] = 149;
l[0xF3] = 162;
l[0xF4] = 147;
l[0xF6] = 148;
l[0xF7] = 246;
l[0xF9] = 151;
l[0xFA] = 163;
l[0xFB] = 150;
l[0xFC] = 129;
l[0xFF] = 152;
#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print "0x%.2I8x" % x,;
}
]]]*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xad,0x9b,0x9c,0x00,0x9d,0x00,0x15,0x00,0x00,0xa6,0xae,0xaa,0x00,0x00,0x00,
	0xf8,0xf1,0xfd,0x00,0x00,0xe6,0x14,0xfa,0x00,0x00,0xa7,0xaf,0xac,0xab,0x00,0xa8,
	0x00,0x00,0x00,0x00,0x8e,0x8f,0x92,0x80,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xa5,0x00,0x00,0x00,0x00,0x99,0x00,0x00,0x00,0x00,0x00,0x9a,0x00,0x00,0xe1,
	0x85,0xa0,0x83,0x00,0x84,0x86,0x91,0x87,0x8a,0x82,0x88,0x89,0x8d,0xa1,0x8c,0x8b,
	0x00,0xa4,0x95,0xa2,0x93,0x00,0x94,0xf6,0x00,0x97,0xa3,0x96,0x81,0x00,0x00,0x98
//[[[end]]]
};


/* Encode the given unicode character `ch' using cp437 (the codepage
 * used by VGA) If the character can't be encoded, return 0 instead.
 * s.a.: https://en.wikipedia.org/wiki/Code_page_437  */
LOCAL ATTR_COLDTEXT u8 NOTHROW(KCALL cp437_encode)(/*utf-32*/ u32 ch) {
	u8 result;
	if (ch <= 0xff) {
		result = cp437_from_latin1[ch];
		if (result)
			return result;
	} else {
		switch (ch) {
		case 0x0192: result = 159; break;
		case 0x0393: result = 226; break;
		case 0x0398: result = 233; break;
		case 0x03A3: result = 228; break;
		case 0x03A6: result = 232; break;
		case 0x03A9: result = 234; break;
		case 0x03B1: result = 224; break;
		case 0x03B4: result = 235; break;
		case 0x03B5: result = 238; break;
		case 0x03C0: result = 227; break;
		case 0x03C3: result = 229; break;
		case 0x03C4: result = 231; break;
		case 0x03C6: result = 237; break;
		case 0x2022: result = 7; break;
		case 0x203C: result = 19; break;
		case 0x207F: result = 252; break;
		case 0x20A7: result = 158; break;
		case 0x2190: result = 27; break;
		case 0x2191: result = 24; break;
		case 0x2192: result = 26; break;
		case 0x2193: result = 25; break;
		case 0x2194: result = 29; break;
		case 0x2195: result = 18; break;
		case 0x21A8: result = 23; break;
		case 0x2219: result = 249; break;
		case 0x221A: result = 251; break;
		case 0x221E: result = 236; break;
		case 0x221F: result = 28; break;
		case 0x2229: result = 239; break;
		case 0x2248: result = 247; break;
		case 0x2261: result = 240; break;
		case 0x2264: result = 243; break;
		case 0x2265: result = 242; break;
		case 0x2302: result = 127; break;
		case 0x2310: result = 169; break;
		case 0x2320: result = 244; break;
		case 0x2321: result = 245; break;
		case 0x2500: result = 196; break;
		case 0x2502: result = 179; break;
		case 0x250C: result = 218; break;
		case 0x2510: result = 191; break;
		case 0x2514: result = 192; break;
		case 0x2518: result = 217; break;
		case 0x251C: result = 195; break;
		case 0x2524: result = 180; break;
		case 0x252C: result = 194; break;
		case 0x2534: result = 193; break;
		case 0x253C: result = 197; break;
		case 0x2550: result = 205; break;
		case 0x2551: result = 186; break;
		case 0x2552: result = 213; break;
		case 0x2553: result = 214; break;
		case 0x2554: result = 201; break;
		case 0x2555: result = 184; break;
		case 0x2556: result = 183; break;
		case 0x2557: result = 187; break;
		case 0x2558: result = 212; break;
		case 0x2559: result = 211; break;
		case 0x255A: result = 200; break;
		case 0x255B: result = 190; break;
		case 0x255C: result = 189; break;
		case 0x255D: result = 188; break;
		case 0x255E: result = 198; break;
		case 0x255F: result = 199; break;
		case 0x2560: result = 204; break;
		case 0x2561: result = 181; break;
		case 0x2562: result = 182; break;
		case 0x2563: result = 185; break;
		case 0x2564: result = 209; break;
		case 0x2565: result = 210; break;
		case 0x2566: result = 203; break;
		case 0x2567: result = 207; break;
		case 0x2568: result = 208; break;
		case 0x2569: result = 202; break;
		case 0x256A: result = 216; break;
		case 0x256B: result = 215; break;
		case 0x256C: result = 206; break;
		case 0x2580: result = 223; break;
		case 0x2584: result = 220; break;
		case 0x2588: result = 219; break;
		case 0x258C: result = 221; break;
		case 0x2590: result = 222; break;
		case 0x2591: result = 176; break;
		case 0x2592: result = 177; break;
		case 0x2593: result = 178; break;
		case 0x25A0: result = 254; break;
		case 0x25AC: result = 22; break;
		case 0x25B2: result = 30; break;
		case 0x25BA: result = 16; break;
		case 0x25BC: result = 31; break;
		case 0x25C4: result = 17; break;
		case 0x25CB: result = 9; break;
		case 0x25D8: result = 8; break;
		case 0x25D9: result = 10; break;
		case 0x263A: result = 1; break;
		case 0x263B: result = 2; break;
		case 0x263C: result = 15; break;
		case 0x2640: result = 12; break;
		case 0x2642: result = 11; break;
		case 0x2660: result = 6; break;
		case 0x2663: result = 5; break;
		case 0x2665: result = 3; break;
		case 0x2666: result = 4; break;
		case 0x266A: result = 13; break;
		case 0x266B: result = 14; break;
		default: result = 0; break;
		}
	}
	return result;
}


#ifdef __INTELLISENSE__
DECL_END
#endif

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_DECODE_CP437_C_INL */
