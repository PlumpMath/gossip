/**************************************************************************/
/*                                                                        */
/* Table lookup implementation of extended Golay (24,12) Code             */
/*                                                                        */
/* emailto:chbrain@dircon.co.uk                                           */
/*                                                                        */
/**************************************************************************/

#include <stdio.h>
//#include "golay.h"

/*
 * the following array uses the 12 bit data as the index and returns
 * the parity value.
 *
 */

const short encode_table[]={
 0x000,0x5C7,0xB8D,0xE4A,0x2DE,0x719,0x953,0xC94,
 0x5BC,0x07B,0xE31,0xBF6,0x762,0x2A5,0xCEF,0x928,
 0xB78,0xEBF,0x0F5,0x532,0x9A6,0xC61,0x22B,0x7EC,
 0xEC4,0xB03,0x549,0x08E,0xC1A,0x9DD,0x797,0x250,
 0x337,0x6F0,0x8BA,0xD7D,0x1E9,0x42E,0xA64,0xFA3,
 0x68B,0x34C,0xD06,0x8C1,0x455,0x192,0xFD8,0xA1F,
 0x84F,0xD88,0x3C2,0x605,0xA91,0xF56,0x11C,0x4DB,
 0xDF3,0x834,0x67E,0x3B9,0xF2D,0xAEA,0x4A0,0x167,
 0x66D,0x3AA,0xDE0,0x827,0x4B3,0x174,0xF3E,0xAF9,
 0x3D1,0x616,0x85C,0xD9B,0x10F,0x4C8,0xA82,0xF45,
 0xD15,0x8D2,0x698,0x35F,0xFCB,0xA0C,0x446,0x181,
 0x8A9,0xD6E,0x324,0x6E3,0xA77,0xFB0,0x1FA,0x43D,
 0x55A,0x09D,0xED7,0xB10,0x784,0x243,0xC09,0x9CE,
 0x0E6,0x521,0xB6B,0xEAC,0x238,0x7FF,0x9B5,0xC72,
 0xE22,0xBE5,0x5AF,0x068,0xCFC,0x93B,0x771,0x2B6,
 0xB9E,0xE59,0x013,0x5D4,0x940,0xC87,0x2CD,0x70A,
 0xCD9,0x91E,0x754,0x293,0xE07,0xBC0,0x58A,0x04D,
 0x965,0xCA2,0x2E8,0x72F,0xBBB,0xE7C,0x036,0x5F1,
 0x7A1,0x266,0xC2C,0x9EB,0x57F,0x0B8,0xEF2,0xB35,
 0x21D,0x7DA,0x990,0xC57,0x0C3,0x504,0xB4E,0xE89,
 0xFEE,0xA29,0x463,0x1A4,0xD30,0x8F7,0x6BD,0x37A,
 0xA52,0xF95,0x1DF,0x418,0x88C,0xD4B,0x301,0x6C6,
 0x496,0x151,0xF1B,0xADC,0x648,0x38F,0xDC5,0x802,
 0x12A,0x4ED,0xAA7,0xF60,0x3F4,0x633,0x879,0xDBE,
 0xAB4,0xF73,0x139,0x4FE,0x86A,0xDAD,0x3E7,0x620,
 0xF08,0xACF,0x485,0x142,0xDD6,0x811,0x65B,0x39C,
 0x1CC,0x40B,0xA41,0xF86,0x312,0x6D5,0x89F,0xD58,
 0x470,0x1B7,0xFFD,0xA3A,0x6AE,0x369,0xD23,0x8E4,
 0x983,0xC44,0x20E,0x7C9,0xB5D,0xE9A,0x0D0,0x517,
 0xC3F,0x9F8,0x7B2,0x275,0xEE1,0xB26,0x56C,0x0AB,
 0x2FB,0x73C,0x976,0xCB1,0x025,0x5E2,0xBA8,0xE6F,
 0x747,0x280,0xCCA,0x90D,0x599,0x05E,0xE14,0xBD3,
 0xC76,0x9B1,0x7FB,0x23C,0xEA8,0xB6F,0x525,0x0E2,
 0x9CA,0xC0D,0x247,0x780,0xB14,0xED3,0x099,0x55E,
 0x70E,0x2C9,0xC83,0x944,0x5D0,0x017,0xE5D,0xB9A,
 0x2B2,0x775,0x93F,0xCF8,0x06C,0x5AB,0xBE1,0xE26,
 0xF41,0xA86,0x4CC,0x10B,0xD9F,0x858,0x612,0x3D5,
 0xAFD,0xF3A,0x170,0x4B7,0x823,0xDE4,0x3AE,0x669,
 0x439,0x1FE,0xFB4,0xA73,0x6E7,0x320,0xD6A,0x8AD,
 0x185,0x442,0xA08,0xFCF,0x35B,0x69C,0x8D6,0xD11,
 0xA1B,0xFDC,0x196,0x451,0x8C5,0xD02,0x348,0x68F,
 0xFA7,0xA60,0x42A,0x1ED,0xD79,0x8BE,0x6F4,0x333,
 0x163,0x4A4,0xAEE,0xF29,0x3BD,0x67A,0x830,0xDF7,
 0x4DF,0x118,0xF52,0xA95,0x601,0x3C6,0xD8C,0x84B,
 0x92C,0xCEB,0x2A1,0x766,0xBF2,0xE35,0x07F,0x5B8,
 0xC90,0x957,0x71D,0x2DA,0xE4E,0xB89,0x5C3,0x004,
 0x254,0x793,0x9D9,0xC1E,0x08A,0x54D,0xB07,0xEC0,
 0x7E8,0x22F,0xC65,0x9A2,0x536,0x0F1,0xEBB,0xB7C,
 0x0AF,0x568,0xB22,0xEE5,0x271,0x7B6,0x9FC,0xC3B,
 0x513,0x0D4,0xE9E,0xB59,0x7CD,0x20A,0xC40,0x987,
 0xBD7,0xE10,0x05A,0x59D,0x909,0xCCE,0x284,0x743,
 0xE6B,0xBAC,0x5E6,0x021,0xCB5,0x972,0x738,0x2FF,
 0x398,0x65F,0x815,0xDD2,0x146,0x481,0xACB,0xF0C,
 0x624,0x3E3,0xDA9,0x86E,0x4FA,0x13D,0xF77,0xAB0,
 0x8E0,0xD27,0x36D,0x6AA,0xA3E,0xFF9,0x1B3,0x474,
 0xD5C,0x89B,0x6D1,0x316,0xF82,0xA45,0x40F,0x1C8,
 0x6C2,0x305,0xD4F,0x888,0x41C,0x1DB,0xF91,0xA56,
 0x37E,0x6B9,0x8F3,0xD34,0x1A0,0x467,0xA2D,0xFEA,
 0xDBA,0x87D,0x637,0x3F0,0xF64,0xAA3,0x4E9,0x12E,
 0x806,0xDC1,0x38B,0x64C,0xAD8,0xF1F,0x155,0x492,
 0x5F5,0x032,0xE78,0xBBF,0x72B,0x2EC,0xCA6,0x961,
 0x049,0x58E,0xBC4,0xE03,0x297,0x750,0x91A,0xCDD,
 0xE8D,0xB4A,0x500,0x0C7,0xC53,0x994,0x7DE,0x219,
 0xB31,0xEF6,0x0BC,0x57B,0x9EF,0xC28,0x262,0x7A5,
 0xD2B,0x8EC,0x6A6,0x361,0xFF5,0xA32,0x478,0x1BF,
 0x897,0xD50,0x31A,0x6DD,0xA49,0xF8E,0x1C4,0x403,
 0x653,0x394,0xDDE,0x819,0x48D,0x14A,0xF00,0xAC7,
 0x3EF,0x628,0x862,0xDA5,0x131,0x4F6,0xABC,0xF7B,
 0xE1C,0xBDB,0x591,0x056,0xCC2,0x905,0x74F,0x288,
 0xBA0,0xE67,0x02D,0x5EA,0x97E,0xCB9,0x2F3,0x734,
 0x564,0x0A3,0xEE9,0xB2E,0x7BA,0x27D,0xC37,0x9F0,
 0x0D8,0x51F,0xB55,0xE92,0x206,0x7C1,0x98B,0xC4C,
 0xB46,0xE81,0x0CB,0x50C,0x998,0xC5F,0x215,0x7D2,
 0xEFA,0xB3D,0x577,0x0B0,0xC24,0x9E3,0x7A9,0x26E,
 0x03E,0x5F9,0xBB3,0xE74,0x2E0,0x727,0x96D,0xCAA,
 0x582,0x045,0xE0F,0xBC8,0x75C,0x29B,0xCD1,0x916,
 0x871,0xDB6,0x3FC,0x63B,0xAAF,0xF68,0x122,0x4E5,
 0xDCD,0x80A,0x640,0x387,0xF13,0xAD4,0x49E,0x159,
 0x309,0x6CE,0x884,0xD43,0x1D7,0x410,0xA5A,0xF9D,
 0x6B5,0x372,0xD38,0x8FF,0x46B,0x1AC,0xFE6,0xA21,
 0x1F2,0x435,0xA7F,0xFB8,0x32C,0x6EB,0x8A1,0xD66,
 0x44E,0x189,0xFC3,0xA04,0x690,0x357,0xD1D,0x8DA,
 0xA8A,0xF4D,0x107,0x4C0,0x854,0xD93,0x3D9,0x61E,
 0xF36,0xAF1,0x4BB,0x17C,0xDE8,0x82F,0x665,0x3A2,
 0x2C5,0x702,0x948,0xC8F,0x01B,0x5DC,0xB96,0xE51,
 0x779,0x2BE,0xCF4,0x933,0x5A7,0x060,0xE2A,0xBED,
 0x9BD,0xC7A,0x230,0x7F7,0xB63,0xEA4,0x0EE,0x529,
 0xC01,0x9C6,0x78C,0x24B,0xEDF,0xB18,0x552,0x095,
 0x79F,0x258,0xC12,0x9D5,0x541,0x086,0xECC,0xB0B,
 0x223,0x7E4,0x9AE,0xC69,0x0FD,0x53A,0xB70,0xEB7,
 0xCE7,0x920,0x76A,0x2AD,0xE39,0xBFE,0x5B4,0x073,
 0x95B,0xC9C,0x2D6,0x711,0xB85,0xE42,0x008,0x5CF,
 0x4A8,0x16F,0xF25,0xAE2,0x676,0x3B1,0xDFB,0x83C,
 0x114,0x4D3,0xA99,0xF5E,0x3CA,0x60D,0x847,0xD80,
 0xFD0,0xA17,0x45D,0x19A,0xD0E,0x8C9,0x683,0x344,
 0xA6C,0xFAB,0x1E1,0x426,0x8B2,0xD75,0x33F,0x6F8,
 0x15D,0x49A,0xAD0,0xF17,0x383,0x644,0x80E,0xDC9,
 0x4E1,0x126,0xF6C,0xAAB,0x63F,0x3F8,0xDB2,0x875,
 0xA25,0xFE2,0x1A8,0x46F,0x8FB,0xD3C,0x376,0x6B1,
 0xF99,0xA5E,0x414,0x1D3,0xD47,0x880,0x6CA,0x30D,
 0x26A,0x7AD,0x9E7,0xC20,0x0B4,0x573,0xB39,0xEFE,
 0x7D6,0x211,0xC5B,0x99C,0x508,0x0CF,0xE85,0xB42,
 0x912,0xCD5,0x29F,0x758,0xBCC,0xE0B,0x041,0x586,
 0xCAE,0x969,0x723,0x2E4,0xE70,0xBB7,0x5FD,0x03A,
 0x730,0x2F7,0xCBD,0x97A,0x5EE,0x029,0xE63,0xBA4,
 0x28C,0x74B,0x901,0xCC6,0x052,0x595,0xBDF,0xE18,
 0xC48,0x98F,0x7C5,0x202,0xE96,0xB51,0x51B,0x0DC,
 0x9F4,0xC33,0x279,0x7BE,0xB2A,0xEED,0x0A7,0x560,
 0x407,0x1C0,0xF8A,0xA4D,0x6D9,0x31E,0xD54,0x893,
 0x1BB,0x47C,0xA36,0xFF1,0x365,0x6A2,0x8E8,0xD2F,
 0xF7F,0xAB8,0x4F2,0x135,0xDA1,0x866,0x62C,0x3EB,
 0xAC3,0xF04,0x14E,0x489,0x81D,0xDDA,0x390,0x657,
 0xD84,0x843,0x609,0x3CE,0xF5A,0xA9D,0x4D7,0x110,
 0x838,0xDFF,0x3B5,0x672,0xAE6,0xF21,0x16B,0x4AC,
 0x6FC,0x33B,0xD71,0x8B6,0x422,0x1E5,0xFAF,0xA68,
 0x340,0x687,0x8CD,0xD0A,0x19E,0x459,0xA13,0xFD4,
 0xEB3,0xB74,0x53E,0x0F9,0xC6D,0x9AA,0x7E0,0x227,
 0xB0F,0xEC8,0x082,0x545,0x9D1,0xC16,0x25C,0x79B,
 0x5CB,0x00C,0xE46,0xB81,0x715,0x2D2,0xC98,0x95F,
 0x077,0x5B0,0xBFA,0xE3D,0x2A9,0x76E,0x924,0xCE3,
 0xBE9,0xE2E,0x064,0x5A3,0x937,0xCF0,0x2BA,0x77D,
 0xE55,0xB92,0x5D8,0x01F,0xC8B,0x94C,0x706,0x2C1,
 0x091,0x556,0xB1C,0xEDB,0x24F,0x788,0x9C2,0xC05,
 0x52D,0x0EA,0xEA0,0xB67,0x7F3,0x234,0xC7E,0x9B9,
 0x8DE,0xD19,0x353,0x694,0xA00,0xFC7,0x18D,0x44A,
 0xD62,0x8A5,0x6EF,0x328,0xFBC,0xA7B,0x431,0x1F6,
 0x3A6,0x661,0x82B,0xDEC,0x178,0x4BF,0xAF5,0xF32,
 0x61A,0x3DD,0xD97,0x850,0x4C4,0x103,0xF49,0xA8E,
 0xF92,0xA55,0x41F,0x1D8,0xD4C,0x88B,0x6C1,0x306,
 0xA2E,0xFE9,0x1A3,0x464,0x8F0,0xD37,0x37D,0x6BA,
 0x4EA,0x12D,0xF67,0xAA0,0x634,0x3F3,0xDB9,0x87E,
 0x156,0x491,0xADB,0xF1C,0x388,0x64F,0x805,0xDC2,
 0xCA5,0x962,0x728,0x2EF,0xE7B,0xBBC,0x5F6,0x031,
 0x919,0xCDE,0x294,0x753,0xBC7,0xE00,0x04A,0x58D,
 0x7DD,0x21A,0xC50,0x997,0x503,0x0C4,0xE8E,0xB49,
 0x261,0x7A6,0x9EC,0xC2B,0x0BF,0x578,0xB32,0xEF5,
 0x9FF,0xC38,0x272,0x7B5,0xB21,0xEE6,0x0AC,0x56B,
 0xC43,0x984,0x7CE,0x209,0xE9D,0xB5A,0x510,0x0D7,
 0x287,0x740,0x90A,0xCCD,0x059,0x59E,0xBD4,0xE13,
 0x73B,0x2FC,0xCB6,0x971,0x5E5,0x022,0xE68,0xBAF,
 0xAC8,0xF0F,0x145,0x482,0x816,0xDD1,0x39B,0x65C,
 0xF74,0xAB3,0x4F9,0x13E,0xDAA,0x86D,0x627,0x3E0,
 0x1B0,0x477,0xA3D,0xFFA,0x36E,0x6A9,0x8E3,0xD24,
 0x40C,0x1CB,0xF81,0xA46,0x6D2,0x315,0xD5F,0x898,
 0x34B,0x68C,0x8C6,0xD01,0x195,0x452,0xA18,0xFDF,
 0x6F7,0x330,0xD7A,0x8BD,0x429,0x1EE,0xFA4,0xA63,
 0x833,0xDF4,0x3BE,0x679,0xAED,0xF2A,0x160,0x4A7,
 0xD8F,0x848,0x602,0x3C5,0xF51,0xA96,0x4DC,0x11B,
 0x07C,0x5BB,0xBF1,0xE36,0x2A2,0x765,0x92F,0xCE8,
 0x5C0,0x007,0xE4D,0xB8A,0x71E,0x2D9,0xC93,0x954,
 0xB04,0xEC3,0x089,0x54E,0x9DA,0xC1D,0x257,0x790,
 0xEB8,0xB7F,0x535,0x0F2,0xC66,0x9A1,0x7EB,0x22C,
 0x526,0x0E1,0xEAB,0xB6C,0x7F8,0x23F,0xC75,0x9B2,
 0x09A,0x55D,0xB17,0xED0,0x244,0x783,0x9C9,0xC0E,
 0xE5E,0xB99,0x5D3,0x014,0xC80,0x947,0x70D,0x2CA,
 0xBE2,0xE25,0x06F,0x5A8,0x93C,0xCFB,0x2B1,0x776,
 0x611,0x3D6,0xD9C,0x85B,0x4CF,0x108,0xF42,0xA85,
 0x3AD,0x66A,0x820,0xDE7,0x173,0x4B4,0xAFE,0xF39,
 0xD69,0x8AE,0x6E4,0x323,0xFB7,0xA70,0x43A,0x1FD,
 0x8D5,0xD12,0x358,0x69F,0xA0B,0xFCC,0x186,0x441,
 0x3E4,0x623,0x869,0xDAE,0x13A,0x4FD,0xAB7,0xF70,
 0x658,0x39F,0xDD5,0x812,0x486,0x141,0xF0B,0xACC,
 0x89C,0xD5B,0x311,0x6D6,0xA42,0xF85,0x1CF,0x408,
 0xD20,0x8E7,0x6AD,0x36A,0xFFE,0xA39,0x473,0x1B4,
 0x0D3,0x514,0xB5E,0xE99,0x20D,0x7CA,0x980,0xC47,
 0x56F,0x0A8,0xEE2,0xB25,0x7B1,0x276,0xC3C,0x9FB,
 0xBAB,0xE6C,0x026,0x5E1,0x975,0xCB2,0x2F8,0x73F,
 0xE17,0xBD0,0x59A,0x05D,0xCC9,0x90E,0x744,0x283,
 0x589,0x04E,0xE04,0xBC3,0x757,0x290,0xCDA,0x91D,
 0x035,0x5F2,0xBB8,0xE7F,0x2EB,0x72C,0x966,0xCA1,
 0xEF1,0xB36,0x57C,0x0BB,0xC2F,0x9E8,0x7A2,0x265,
 0xB4D,0xE8A,0x0C0,0x507,0x993,0xC54,0x21E,0x7D9,
 0x6BE,0x379,0xD33,0x8F4,0x460,0x1A7,0xFED,0xA2A,
 0x302,0x6C5,0x88F,0xD48,0x1DC,0x41B,0xA51,0xF96,
 0xDC6,0x801,0x64B,0x38C,0xF18,0xADF,0x495,0x152,
 0x87A,0xDBD,0x3F7,0x630,0xAA4,0xF63,0x129,0x4EE,
 0xF3D,0xAFA,0x4B0,0x177,0xDE3,0x824,0x66E,0x3A9,
 0xA81,0xF46,0x10C,0x4CB,0x85F,0xD98,0x3D2,0x615,
 0x445,0x182,0xFC8,0xA0F,0x69B,0x35C,0xD16,0x8D1,
 0x1F9,0x43E,0xA74,0xFB3,0x327,0x6E0,0x8AA,0xD6D,
 0xC0A,0x9CD,0x787,0x240,0xED4,0xB13,0x559,0x09E,
 0x9B6,0xC71,0x23B,0x7FC,0xB68,0xEAF,0x0E5,0x522,
 0x772,0x2B5,0xCFF,0x938,0x5AC,0x06B,0xE21,0xBE6,
 0x2CE,0x709,0x943,0xC84,0x010,0x5D7,0xB9D,0xE5A,
 0x950,0xC97,0x2DD,0x71A,0xB8E,0xE49,0x003,0x5C4,
 0xCEC,0x92B,0x761,0x2A6,0xE32,0xBF5,0x5BF,0x078,
 0x228,0x7EF,0x9A5,0xC62,0x0F6,0x531,0xB7B,0xEBC,
 0x794,0x253,0xC19,0x9DE,0x54A,0x08D,0xEC7,0xB00,
 0xA67,0xFA0,0x1EA,0x42D,0x8B9,0xD7E,0x334,0x6F3,
 0xFDB,0xA1C,0x456,0x191,0xD05,0x8C2,0x688,0x34F,
 0x11F,0x4D8,0xA92,0xF55,0x3C1,0x606,0x84C,0xD8B,
 0x4A3,0x164,0xF2E,0xAE9,0x67D,0x3BA,0xDF0,0x837,
 0x2B9,0x77E,0x934,0xCF3,0x067,0x5A0,0xBEA,0xE2D,
 0x705,0x2C2,0xC88,0x94F,0x5DB,0x01C,0xE56,0xB91,
 0x9C1,0xC06,0x24C,0x78B,0xB1F,0xED8,0x092,0x555,
 0xC7D,0x9BA,0x7F0,0x237,0xEA3,0xB64,0x52E,0x0E9,
 0x18E,0x449,0xA03,0xFC4,0x350,0x697,0x8DD,0xD1A,
 0x432,0x1F5,0xFBF,0xA78,0x6EC,0x32B,0xD61,0x8A6,
 0xAF6,0xF31,0x17B,0x4BC,0x828,0xDEF,0x3A5,0x662,
 0xF4A,0xA8D,0x4C7,0x100,0xD94,0x853,0x619,0x3DE,
 0x4D4,0x113,0xF59,0xA9E,0x60A,0x3CD,0xD87,0x840,
 0x168,0x4AF,0xAE5,0xF22,0x3B6,0x671,0x83B,0xDFC,
 0xFAC,0xA6B,0x421,0x1E6,0xD72,0x8B5,0x6FF,0x338,
 0xA10,0xFD7,0x19D,0x45A,0x8CE,0xD09,0x343,0x684,
 0x7E3,0x224,0xC6E,0x9A9,0x53D,0x0FA,0xEB0,0xB77,
 0x25F,0x798,0x9D2,0xC15,0x081,0x546,0xB0C,0xECB,
 0xC9B,0x95C,0x716,0x2D1,0xE45,0xB82,0x5C8,0x00F,
 0x927,0xCE0,0x2AA,0x76D,0xBF9,0xE3E,0x074,0x5B3,
 0xE60,0xBA7,0x5ED,0x02A,0xCBE,0x979,0x733,0x2F4,
 0xBDC,0xE1B,0x051,0x596,0x902,0xCC5,0x28F,0x748,
 0x518,0x0DF,0xE95,0xB52,0x7C6,0x201,0xC4B,0x98C,
 0x0A4,0x563,0xB29,0xEEE,0x27A,0x7BD,0x9F7,0xC30,
 0xD57,0x890,0x6DA,0x31D,0xF89,0xA4E,0x404,0x1C3,
 0x8EB,0xD2C,0x366,0x6A1,0xA35,0xFF2,0x1B8,0x47F,
 0x62F,0x3E8,0xDA2,0x865,0x4F1,0x136,0xF7C,0xABB,
 0x393,0x654,0x81E,0xDD9,0x14D,0x48A,0xAC0,0xF07,
 0x80D,0xDCA,0x380,0x647,0xAD3,0xF14,0x15E,0x499,
 0xDB1,0x876,0x63C,0x3FB,0xF6F,0xAA8,0x4E2,0x125,
 0x375,0x6B2,0x8F8,0xD3F,0x1AB,0x46C,0xA26,0xFE1,
 0x6C9,0x30E,0xD44,0x883,0x417,0x1D0,0xF9A,0xA5D,
 0xB3A,0xEFD,0x0B7,0x570,0x9E4,0xC23,0x269,0x7AE,
 0xE86,0xB41,0x50B,0x0CC,0xC58,0x99F,0x7D5,0x212,
 0x042,0x585,0xBCF,0xE08,0x29C,0x75B,0x911,0xCD6,
 0x5FE,0x039,0xE73,0xBB4,0x720,0x2E7,0xCAD,0x96A,
 0xECF,0xB08,0x542,0x085,0xC11,0x9D6,0x79C,0x25B,
 0xB73,0xEB4,0x0FE,0x539,0x9AD,0xC6A,0x220,0x7E7,
 0x5B7,0x070,0xE3A,0xBFD,0x769,0x2AE,0xCE4,0x923,
 0x00B,0x5CC,0xB86,0xE41,0x2D5,0x712,0x958,0xC9F,
 0xDF8,0x83F,0x675,0x3B2,0xF26,0xAE1,0x4AB,0x16C,
 0x844,0xD83,0x3C9,0x60E,0xA9A,0xF5D,0x117,0x4D0,
 0x680,0x347,0xD0D,0x8CA,0x45E,0x199,0xFD3,0xA14,
 0x33C,0x6FB,0x8B1,0xD76,0x1E2,0x425,0xA6F,0xFA8,
 0x8A2,0xD65,0x32F,0x6E8,0xA7C,0xFBB,0x1F1,0x436,
 0xD1E,0x8D9,0x693,0x354,0xFC0,0xA07,0x44D,0x18A,
 0x3DA,0x61D,0x857,0xD90,0x104,0x4C3,0xA89,0xF4E,
 0x666,0x3A1,0xDEB,0x82C,0x4B8,0x17F,0xF35,0xAF2,
 0xB95,0xE52,0x018,0x5DF,0x94B,0xC8C,0x2C6,0x701,
 0xE29,0xBEE,0x5A4,0x063,0xCF7,0x930,0x77A,0x2BD,
 0x0ED,0x52A,0xB60,0xEA7,0x233,0x7F4,0x9BE,0xC79,
 0x551,0x096,0xEDC,0xB1B,0x78F,0x248,0xC02,0x9C5,
 0x216,0x7D1,0x99B,0xC5C,0x0C8,0x50F,0xB45,0xE82,
 0x7AA,0x26D,0xC27,0x9E0,0x574,0x0B3,0xEF9,0xB3E,
 0x96E,0xCA9,0x2E3,0x724,0xBB0,0xE77,0x03D,0x5FA,
 0xCD2,0x915,0x75F,0x298,0xE0C,0xBCB,0x581,0x046,
 0x121,0x4E6,0xAAC,0xF6B,0x3FF,0x638,0x872,0xDB5,
 0x49D,0x15A,0xF10,0xAD7,0x643,0x384,0xDCE,0x809,
 0xA59,0xF9E,0x1D4,0x413,0x887,0xD40,0x30A,0x6CD,
 0xFE5,0xA22,0x468,0x1AF,0xD3B,0x8FC,0x6B6,0x371,
 0x47B,0x1BC,0xFF6,0xA31,0x6A5,0x362,0xD28,0x8EF,
 0x1C7,0x400,0xA4A,0xF8D,0x319,0x6DE,0x894,0xD53,
 0xF03,0xAC4,0x48E,0x149,0xDDD,0x81A,0x650,0x397,
 0xABF,0xF78,0x132,0x4F5,0x861,0xDA6,0x3EC,0x62B,
 0x74C,0x28B,0xCC1,0x906,0x592,0x055,0xE1F,0xBD8,
 0x2F0,0x737,0x97D,0xCBA,0x02E,0x5E9,0xBA3,0xE64,
 0xC34,0x9F3,0x7B9,0x27E,0xEEA,0xB2D,0x567,0x0A0,
 0x988,0xC4F,0x205,0x7C2,0xB56,0xE91,0x0DB,0x51C,
 0xAE3,0xF24,0x16E,0x4A9,0x83D,0xDFA,0x3B0,0x677,
 0xF5F,0xA98,0x4D2,0x115,0xD81,0x846,0x60C,0x3CB,
 0x19B,0x45C,0xA16,0xFD1,0x345,0x682,0x8C8,0xD0F,
 0x427,0x1E0,0xFAA,0xA6D,0x6F9,0x33E,0xD74,0x8B3,
 0x9D4,0xC13,0x259,0x79E,0xB0A,0xECD,0x087,0x540,
 0xC68,0x9AF,0x7E5,0x222,0xEB6,0xB71,0x53B,0x0FC,
 0x2AC,0x76B,0x921,0xCE6,0x072,0x5B5,0xBFF,0xE38,
 0x710,0x2D7,0xC9D,0x95A,0x5CE,0x009,0xE43,0xB84,
 0xC8E,0x949,0x703,0x2C4,0xE50,0xB97,0x5DD,0x01A,
 0x932,0xCF5,0x2BF,0x778,0xBEC,0xE2B,0x061,0x5A6,
 0x7F6,0x231,0xC7B,0x9BC,0x528,0x0EF,0xEA5,0xB62,
 0x24A,0x78D,0x9C7,0xC00,0x094,0x553,0xB19,0xEDE,
 0xFB9,0xA7E,0x434,0x1F3,0xD67,0x8A0,0x6EA,0x32D,
 0xA05,0xFC2,0x188,0x44F,0x8DB,0xD1C,0x356,0x691,
 0x4C1,0x106,0xF4C,0xA8B,0x61F,0x3D8,0xD92,0x855,
 0x17D,0x4BA,0xAF0,0xF37,0x3A3,0x664,0x82E,0xDE9,
 0x63A,0x3FD,0xDB7,0x870,0x4E4,0x123,0xF69,0xAAE,
 0x386,0x641,0x80B,0xDCC,0x158,0x49F,0xAD5,0xF12,
 0xD42,0x885,0x6CF,0x308,0xF9C,0xA5B,0x411,0x1D6,
 0x8FE,0xD39,0x373,0x6B4,0xA20,0xFE7,0x1AD,0x46A,
 0x50D,0x0CA,0xE80,0xB47,0x7D3,0x214,0xC5E,0x999,
 0x0B1,0x576,0xB3C,0xEFB,0x26F,0x7A8,0x9E2,0xC25,
 0xE75,0xBB2,0x5F8,0x03F,0xCAB,0x96C,0x726,0x2E1,
 0xBC9,0xE0E,0x044,0x583,0x917,0xCD0,0x29A,0x75D,
 0x057,0x590,0xBDA,0xE1D,0x289,0x74E,0x904,0xCC3,
 0x5EB,0x02C,0xE66,0xBA1,0x735,0x2F2,0xCB8,0x97F,
 0xB2F,0xEE8,0x0A2,0x565,0x9F1,0xC36,0x27C,0x7BB,
 0xE93,0xB54,0x51E,0x0D9,0xC4D,0x98A,0x7C0,0x207,
 0x360,0x6A7,0x8ED,0xD2A,0x1BE,0x479,0xA33,0xFF4,
 0x6DC,0x31B,0xD51,0x896,0x402,0x1C5,0xF8F,0xA48,
 0x818,0xDDF,0x395,0x652,0xAC6,0xF01,0x14B,0x48C,
 0xDA4,0x863,0x629,0x3EE,0xF7A,0xABD,0x4F7,0x130,
 0x695,0x352,0xD18,0x8DF,0x44B,0x18C,0xFC6,0xA01,
 0x329,0x6EE,0x8A4,0xD63,0x1F7,0x430,0xA7A,0xFBD,
 0xDED,0x82A,0x660,0x3A7,0xF33,0xAF4,0x4BE,0x179,
 0x851,0xD96,0x3DC,0x61B,0xA8F,0xF48,0x102,0x4C5,
 0x5A2,0x065,0xE2F,0xBE8,0x77C,0x2BB,0xCF1,0x936,
 0x01E,0x5D9,0xB93,0xE54,0x2C0,0x707,0x94D,0xC8A,
 0xEDA,0xB1D,0x557,0x090,0xC04,0x9C3,0x789,0x24E,
 0xB66,0xEA1,0x0EB,0x52C,0x9B8,0xC7F,0x235,0x7F2,
 0x0F8,0x53F,0xB75,0xEB2,0x226,0x7E1,0x9AB,0xC6C,
 0x544,0x083,0xEC9,0xB0E,0x79A,0x25D,0xC17,0x9D0,
 0xB80,0xE47,0x00D,0x5CA,0x95E,0xC99,0x2D3,0x714,
 0xE3C,0xBFB,0x5B1,0x076,0xCE2,0x925,0x76F,0x2A8,
 0x3CF,0x608,0x842,0xD85,0x111,0x4D6,0xA9C,0xF5B,
 0x673,0x3B4,0xDFE,0x839,0x4AD,0x16A,0xF20,0xAE7,
 0x8B7,0xD70,0x33A,0x6FD,0xA69,0xFAE,0x1E4,0x423,
 0xD0B,0x8CC,0x686,0x341,0xFD5,0xA12,0x458,0x19F,
 0xA4C,0xF8B,0x1C1,0x406,0x892,0xD55,0x31F,0x6D8,
 0xFF0,0xA37,0x47D,0x1BA,0xD2E,0x8E9,0x6A3,0x364,
 0x134,0x4F3,0xAB9,0xF7E,0x3EA,0x62D,0x867,0xDA0,
 0x488,0x14F,0xF05,0xAC2,0x656,0x391,0xDDB,0x81C,
 0x97B,0xCBC,0x2F6,0x731,0xBA5,0xE62,0x028,0x5EF,
 0xCC7,0x900,0x74A,0x28D,0xE19,0xBDE,0x594,0x053,
 0x203,0x7C4,0x98E,0xC49,0x0DD,0x51A,0xB50,0xE97,
 0x7BF,0x278,0xC32,0x9F5,0x561,0x0A6,0xEEC,0xB2B,
 0xC21,0x9E6,0x7AC,0x26B,0xEFF,0xB38,0x572,0x0B5,
 0x99D,0xC5A,0x210,0x7D7,0xB43,0xE84,0x0CE,0x509,
 0x759,0x29E,0xCD4,0x913,0x587,0x040,0xE0A,0xBCD,
 0x2E5,0x722,0x968,0xCAF,0x03B,0x5FC,0xBB6,0xE71,
 0xF16,0xAD1,0x49B,0x15C,0xDC8,0x80F,0x645,0x382,
 0xAAA,0xF6D,0x127,0x4E0,0x874,0xDB3,0x3F9,0x63E,
 0x46E,0x1A9,0xFE3,0xA24,0x6B0,0x377,0xD3D,0x8FA,
 0x1D2,0x415,0xA5F,0xF98,0x30C,0x6CB,0x881,0xD46,
 0x7C8,0x20F,0xC45,0x982,0x516,0x0D1,0xE9B,0xB5C,
 0x274,0x7B3,0x9F9,0xC3E,0x0AA,0x56D,0xB27,0xEE0,
 0xCB0,0x977,0x73D,0x2FA,0xE6E,0xBA9,0x5E3,0x024,
 0x90C,0xCCB,0x281,0x746,0xBD2,0xE15,0x05F,0x598,
 0x4FF,0x138,0xF72,0xAB5,0x621,0x3E6,0xDAC,0x86B,
 0x143,0x484,0xACE,0xF09,0x39D,0x65A,0x810,0xDD7,
 0xF87,0xA40,0x40A,0x1CD,0xD59,0x89E,0x6D4,0x313,
 0xA3B,0xFFC,0x1B6,0x471,0x8E5,0xD22,0x368,0x6AF,
 0x1A5,0x462,0xA28,0xFEF,0x37B,0x6BC,0x8F6,0xD31,
 0x419,0x1DE,0xF94,0xA53,0x6C7,0x300,0xD4A,0x88D,
 0xADD,0xF1A,0x150,0x497,0x803,0xDC4,0x38E,0x649,
 0xF61,0xAA6,0x4EC,0x12B,0xDBF,0x878,0x632,0x3F5,
 0x292,0x755,0x91F,0xCD8,0x04C,0x58B,0xBC1,0xE06,
 0x72E,0x2E9,0xCA3,0x964,0x5F0,0x037,0xE7D,0xBBA,
 0x9EA,0xC2D,0x267,0x7A0,0xB34,0xEF3,0x0B9,0x57E,
 0xC56,0x991,0x7DB,0x21C,0xE88,0xB4F,0x505,0x0C2,
 0xB11,0xED6,0x09C,0x55B,0x9CF,0xC08,0x242,0x785,
 0xEAD,0xB6A,0x520,0x0E7,0xC73,0x9B4,0x7FE,0x239,
 0x069,0x5AE,0xBE4,0xE23,0x2B7,0x770,0x93A,0xCFD,
 0x5D5,0x012,0xE58,0xB9F,0x70B,0x2CC,0xC86,0x941,
 0x826,0xDE1,0x3AB,0x66C,0xAF8,0xF3F,0x175,0x4B2,
 0xD9A,0x85D,0x617,0x3D0,0xF44,0xA83,0x4C9,0x10E,
 0x35E,0x699,0x8D3,0xD14,0x180,0x447,0xA0D,0xFCA,
 0x6E2,0x325,0xD6F,0x8A8,0x43C,0x1FB,0xFB1,0xA76,
 0xD7C,0x8BB,0x6F1,0x336,0xFA2,0xA65,0x42F,0x1E8,
 0x8C0,0xD07,0x34D,0x68A,0xA1E,0xFD9,0x193,0x454,
 0x604,0x3C3,0xD89,0x84E,0x4DA,0x11D,0xF57,0xA90,
 0x3B8,0x67F,0x835,0xDF2,0x166,0x4A1,0xAEB,0xF2C,
 0xE4B,0xB8C,0x5C6,0x001,0xC95,0x952,0x718,0x2DF,
 0xBF7,0xE30,0x07A,0x5BD,0x929,0xCEE,0x2A4,0x763,
 0x533,0x0F4,0xEBE,0xB79,0x7ED,0x22A,0xC60,0x9A7,
 0x08F,0x548,0xB02,0xEC5,0x251,0x796,0x9DC,0xC1B,
 0xBBE,0xE79,0x033,0x5F4,0x960,0xCA7,0x2ED,0x72A,
 0xE02,0xBC5,0x58F,0x048,0xCDC,0x91B,0x751,0x296,
 0x0C6,0x501,0xB4B,0xE8C,0x218,0x7DF,0x995,0xC52,
 0x57A,0x0BD,0xEF7,0xB30,0x7A4,0x263,0xC29,0x9EE,
 0x889,0xD4E,0x304,0x6C3,0xA57,0xF90,0x1DA,0x41D,
 0xD35,0x8F2,0x6B8,0x37F,0xFEB,0xA2C,0x466,0x1A1,
 0x3F1,0x636,0x87C,0xDBB,0x12F,0x4E8,0xAA2,0xF65,
 0x64D,0x38A,0xDC0,0x807,0x493,0x154,0xF1E,0xAD9,
 0xDD3,0x814,0x65E,0x399,0xF0D,0xACA,0x480,0x147,
 0x86F,0xDA8,0x3E2,0x625,0xAB1,0xF76,0x13C,0x4FB,
 0x6AB,0x36C,0xD26,0x8E1,0x475,0x1B2,0xFF8,0xA3F,
 0x317,0x6D0,0x89A,0xD5D,0x1C9,0x40E,0xA44,0xF83,
 0xEE4,0xB23,0x569,0x0AE,0xC3A,0x9FD,0x7B7,0x270,
 0xB58,0xE9F,0x0D5,0x512,0x986,0xC41,0x20B,0x7CC,
 0x59C,0x05B,0xE11,0xBD6,0x742,0x285,0xCCF,0x908,
 0x020,0x5E7,0xBAD,0xE6A,0x2FE,0x739,0x973,0xCB4,
 0x767,0x2A0,0xCEA,0x92D,0x5B9,0x07E,0xE34,0xBF3,
 0x2DB,0x71C,0x956,0xC91,0x005,0x5C2,0xB88,0xE4F,
 0xC1F,0x9D8,0x792,0x255,0xEC1,0xB06,0x54C,0x08B,
 0x9A3,0xC64,0x22E,0x7E9,0xB7D,0xEBA,0x0F0,0x537,
 0x450,0x197,0xFDD,0xA1A,0x68E,0x349,0xD03,0x8C4,
 0x1EC,0x42B,0xA61,0xFA6,0x332,0x6F5,0x8BF,0xD78,
 0xF28,0xAEF,0x4A5,0x162,0xDF6,0x831,0x67B,0x3BC,
 0xA94,0xF53,0x119,0x4DE,0x84A,0xD8D,0x3C7,0x600,
 0x10A,0x4CD,0xA87,0xF40,0x3D4,0x613,0x859,0xD9E,
 0x4B6,0x171,0xF3B,0xAFC,0x668,0x3AF,0xDE5,0x822,
 0xA72,0xFB5,0x1FF,0x438,0x8AC,0xD6B,0x321,0x6E6,
 0xFCE,0xA09,0x443,0x184,0xD10,0x8D7,0x69D,0x35A,
 0x23D,0x7FA,0x9B0,0xC77,0x0E3,0x524,0xB6E,0xEA9,
 0x781,0x246,0xC0C,0x9CB,0x55F,0x098,0xED2,0xB15,
 0x945,0xC82,0x2C8,0x70F,0xB9B,0xE5C,0x016,0x5D1,
 0xCF9,0x93E,0x774,0x2B3,0xE27,0xBE0,0x5AA,0x06D,
 0x571,0x0B6,0xEFC,0xB3B,0x7AF,0x268,0xC22,0x9E5,
 0x0CD,0x50A,0xB40,0xE87,0x213,0x7D4,0x99E,0xC59,
 0xE09,0xBCE,0x584,0x043,0xCD7,0x910,0x75A,0x29D,
 0xBB5,0xE72,0x038,0x5FF,0x96B,0xCAC,0x2E6,0x721,
 0x646,0x381,0xDCB,0x80C,0x498,0x15F,0xF15,0xAD2,
 0x3FA,0x63D,0x877,0xDB0,0x124,0x4E3,0xAA9,0xF6E,
 0xD3E,0x8F9,0x6B3,0x374,0xFE0,0xA27,0x46D,0x1AA,
 0x882,0xD45,0x30F,0x6C8,0xA5C,0xF9B,0x1D1,0x416,
 0x31C,0x6DB,0x891,0xD56,0x1C2,0x405,0xA4F,0xF88,
 0x6A0,0x367,0xD2D,0x8EA,0x47E,0x1B9,0xFF3,0xA34,
 0x864,0xDA3,0x3E9,0x62E,0xABA,0xF7D,0x137,0x4F0,
 0xDD8,0x81F,0x655,0x392,0xF06,0xAC1,0x48B,0x14C,
 0x02B,0x5EC,0xBA6,0xE61,0x2F5,0x732,0x978,0xCBF,
 0x597,0x050,0xE1A,0xBDD,0x749,0x28E,0xCC4,0x903,
 0xB53,0xE94,0x0DE,0x519,0x98D,0xC4A,0x200,0x7C7,
 0xEEF,0xB28,0x562,0x0A5,0xC31,0x9F6,0x7BC,0x27B,
 0x9A8,0xC6F,0x225,0x7E2,0xB76,0xEB1,0x0FB,0x53C,
 0xC14,0x9D3,0x799,0x25E,0xECA,0xB0D,0x547,0x080,
 0x2D0,0x717,0x95D,0xC9A,0x00E,0x5C9,0xB83,0xE44,
 0x76C,0x2AB,0xCE1,0x926,0x5B2,0x075,0xE3F,0xBF8,
 0xA9F,0xF58,0x112,0x4D5,0x841,0xD86,0x3CC,0x60B,
 0xF23,0xAE4,0x4AE,0x169,0xDFD,0x83A,0x670,0x3B7,
 0x1E7,0x420,0xA6A,0xFAD,0x339,0x6FE,0x8B4,0xD73,
 0x45B,0x19C,0xFD6,0xA11,0x685,0x342,0xD08,0x8CF,
 0xFC5,0xA02,0x448,0x18F,0xD1B,0x8DC,0x696,0x351,
 0xA79,0xFBE,0x1F4,0x433,0x8A7,0xD60,0x32A,0x6ED,
 0x4BD,0x17A,0xF30,0xAF7,0x663,0x3A4,0xDEE,0x829,
 0x101,0x4C6,0xA8C,0xF4B,0x3DF,0x618,0x852,0xD95,
 0xCF2,0x935,0x77F,0x2B8,0xE2C,0xBEB,0x5A1,0x066,
 0x94E,0xC89,0x2C3,0x704,0xB90,0xE57,0x01D,0x5DA,
 0x78A,0x24D,0xC07,0x9C0,0x554,0x093,0xED9,0xB1E,
 0x236,0x7F1,0x9BB,0xC7C,0x0E8,0x52F,0xB65,0xEA2,
 0x907,0xCC0,0x28A,0x74D,0xBD9,0xE1E,0x054,0x593,
 0xCBB,0x97C,0x736,0x2F1,0xE65,0xBA2,0x5E8,0x02F,
 0x27F,0x7B8,0x9F2,0xC35,0x0A1,0x566,0xB2C,0xEEB,
 0x7C3,0x204,0xC4E,0x989,0x51D,0x0DA,0xE90,0xB57,
 0xA30,0xFF7,0x1BD,0x47A,0x8EE,0xD29,0x363,0x6A4,
 0xF8C,0xA4B,0x401,0x1C6,0xD52,0x895,0x6DF,0x318,
 0x148,0x48F,0xAC5,0xF02,0x396,0x651,0x81B,0xDDC,
 0x4F4,0x133,0xF79,0xABE,0x62A,0x3ED,0xDA7,0x860,
 0xF6A,0xAAD,0x4E7,0x120,0xDB4,0x873,0x639,0x3FE,
 0xAD6,0xF11,0x15B,0x49C,0x808,0xDCF,0x385,0x642,
 0x412,0x1D5,0xF9F,0xA58,0x6CC,0x30B,0xD41,0x886,
 0x1AE,0x469,0xA23,0xFE4,0x370,0x6B7,0x8FD,0xD3A,
 0xC5D,0x99A,0x7D0,0x217,0xE83,0xB44,0x50E,0x0C9,
 0x9E1,0xC26,0x26C,0x7AB,0xB3F,0xEF8,0x0B2,0x575,
 0x725,0x2E2,0xCA8,0x96F,0x5FB,0x03C,0xE76,0xBB1,
 0x299,0x75E,0x914,0xCD3,0x047,0x580,0xBCA,0xE0D,
 0x5DE,0x019,0xE53,0xB94,0x700,0x2C7,0xC8D,0x94A,
 0x062,0x5A5,0xBEF,0xE28,0x2BC,0x77B,0x931,0xCF6,
 0xEA6,0xB61,0x52B,0x0EC,0xC78,0x9BF,0x7F5,0x232,
 0xB1A,0xEDD,0x097,0x550,0x9C4,0xC03,0x249,0x78E,
 0x6E9,0x32E,0xD64,0x8A3,0x437,0x1F0,0xFBA,0xA7D,
 0x355,0x692,0x8D8,0xD1F,0x18B,0x44C,0xA06,0xFC1,
 0xD91,0x856,0x61C,0x3DB,0xF4F,0xA88,0x4C2,0x105,
 0x82D,0xDEA,0x3A0,0x667,0xAF3,0xF34,0x17E,0x4B9,
 0x3B3,0x674,0x83E,0xDF9,0x16D,0x4AA,0xAE0,0xF27,
 0x60F,0x3C8,0xD82,0x845,0x4D1,0x116,0xF5C,0xA9B,
 0x8CB,0xD0C,0x346,0x681,0xA15,0xFD2,0x198,0x45F,
 0xD77,0x8B0,0x6FA,0x33D,0xFA9,0xA6E,0x424,0x1E3,
 0x084,0x543,0xB09,0xECE,0x25A,0x79D,0x9D7,0xC10,
 0x538,0x0FF,0xEB5,0xB72,0x7E6,0x221,0xC6B,0x9AC,
 0xBFC,0xE3B,0x071,0x5B6,0x922,0xCE5,0x2AF,0x768,
 0xE40,0xB87,0x5CD,0x00A,0xC9E,0x959,0x713,0x2D4,
 0x85A,0xD9D,0x3D7,0x610,0xA84,0xF43,0x109,0x4CE,
 0xDE6,0x821,0x66B,0x3AC,0xF38,0xAFF,0x4B5,0x172,
 0x322,0x6E5,0x8AF,0xD68,0x1FC,0x43B,0xA71,0xFB6,
 0x69E,0x359,0xD13,0x8D4,0x440,0x187,0xFCD,0xA0A,
 0xB6D,0xEAA,0x0E0,0x527,0x9B3,0xC74,0x23E,0x7F9,
 0xED1,0xB16,0x55C,0x09B,0xC0F,0x9C8,0x782,0x245,
 0x015,0x5D2,0xB98,0xE5F,0x2CB,0x70C,0x946,0xC81,
 0x5A9,0x06E,0xE24,0xBE3,0x777,0x2B0,0xCFA,0x93D,
 0xE37,0xBF0,0x5BA,0x07D,0xCE9,0x92E,0x764,0x2A3,
 0xB8B,0xE4C,0x006,0x5C1,0x955,0xC92,0x2D8,0x71F,
 0x54F,0x088,0xEC2,0xB05,0x791,0x256,0xC1C,0x9DB,
 0x0F3,0x534,0xB7E,0xEB9,0x22D,0x7EA,0x9A0,0xC67,
 0xD00,0x8C7,0x68D,0x34A,0xFDE,0xA19,0x453,0x194,
 0x8BC,0xD7B,0x331,0x6F6,0xA62,0xFA5,0x1EF,0x428,
 0x678,0x3BF,0xDF5,0x832,0x4A6,0x161,0xF2B,0xAEC,
 0x3C4,0x603,0x849,0xD8E,0x11A,0x4DD,0xA97,0xF50,
 0x483,0x144,0xF0E,0xAC9,0x65D,0x39A,0xDD0,0x817,
 0x13F,0x4F8,0xAB2,0xF75,0x3E1,0x626,0x86C,0xDAB,
 0xFFB,0xA3C,0x476,0x1B1,0xD25,0x8E2,0x6A8,0x36F,
 0xA47,0xF80,0x1CA,0x40D,0x899,0xD5E,0x314,0x6D3,
 0x7B4,0x273,0xC39,0x9FE,0x56A,0x0AD,0xEE7,0xB20,
 0x208,0x7CF,0x985,0xC42,0x0D6,0x511,0xB5B,0xE9C,
 0xCCC,0x90B,0x741,0x286,0xE12,0xBD5,0x59F,0x058,
 0x970,0xCB7,0x2FD,0x73A,0xBAE,0xE69,0x023,0x5E4,
 0x2EE,0x729,0x963,0xCA4,0x030,0x5F7,0xBBD,0xE7A,
 0x752,0x295,0xCDF,0x918,0x58C,0x04B,0xE01,0xBC6,
 0x996,0xC51,0x21B,0x7DC,0xB48,0xE8F,0x0C5,0x502,
 0xC2A,0x9ED,0x7A7,0x260,0xEF4,0xB33,0x579,0x0BE,
 0x1D9,0x41E,0xA54,0xF93,0x307,0x6C0,0x88A,0xD4D,
 0x465,0x1A2,0xFE8,0xA2F,0x6BB,0x37C,0xD36,0x8F1,
 0xAA1,0xF66,0x12C,0x4EB,0x87F,0xDB8,0x3F2,0x635,
 0xF1D,0xADA,0x490,0x157,0xDC3,0x804,0x64E,0x389,
 0x42C,0x1EB,0xFA1,0xA66,0x6F2,0x335,0xD7F,0x8B8,
 0x190,0x457,0xA1D,0xFDA,0x34E,0x689,0x8C3,0xD04,
 0xF54,0xA93,0x4D9,0x11E,0xD8A,0x84D,0x607,0x3C0,
 0xAE8,0xF2F,0x165,0x4A2,0x836,0xDF1,0x3BB,0x67C,
 0x71B,0x2DC,0xC96,0x951,0x5C5,0x002,0xE48,0xB8F,
 0x2A7,0x760,0x92A,0xCED,0x079,0x5BE,0xBF4,0xE33,
 0xC63,0x9A4,0x7EE,0x229,0xEBD,0xB7A,0x530,0x0F7,
 0x9DF,0xC18,0x252,0x795,0xB01,0xEC6,0x08C,0x54B,
 0x241,0x786,0x9CC,0xC0B,0x09F,0x558,0xB12,0xED5,
 0x7FD,0x23A,0xC70,0x9B7,0x523,0x0E4,0xEAE,0xB69,
 0x939,0xCFE,0x2B4,0x773,0xBE7,0xE20,0x06A,0x5AD,
 0xC85,0x942,0x708,0x2CF,0xE5B,0xB9C,0x5D6,0x011,
 0x176,0x4B1,0xAFB,0xF3C,0x3A8,0x66F,0x825,0xDE2,
 0x4CA,0x10D,0xF47,0xA80,0x614,0x3D3,0xD99,0x85E,
 0xA0E,0xFC9,0x183,0x444,0x8D0,0xD17,0x35D,0x69A,
 0xFB2,0xA75,0x43F,0x1F8,0xD6C,0x8AB,0x6E1,0x326,
 0x8F5,0xD32,0x378,0x6BF,0xA2B,0xFEC,0x1A6,0x461,
 0xD49,0x88E,0x6C4,0x303,0xF97,0xA50,0x41A,0x1DD,
 0x38D,0x64A,0x800,0xDC7,0x153,0x494,0xADE,0xF19,
 0x631,0x3F6,0xDBC,0x87B,0x4EF,0x128,0xF62,0xAA5,
 0xBC2,0xE05,0x04F,0x588,0x91C,0xCDB,0x291,0x756,
 0xE7E,0xBB9,0x5F3,0x034,0xCA0,0x967,0x72D,0x2EA,
 0x0BA,0x57D,0xB37,0xEF0,0x264,0x7A3,0x9E9,0xC2E,
 0x506,0x0C1,0xE8B,0xB4C,0x7D8,0x21F,0xC55,0x992,
 0xE98,0xB5F,0x515,0x0D2,0xC46,0x981,0x7CB,0x20C,
 0xB24,0xEE3,0x0A9,0x56E,0x9FA,0xC3D,0x277,0x7B0,
 0x5E0,0x027,0xE6D,0xBAA,0x73E,0x2F9,0xCB3,0x974,
 0x05C,0x59B,0xBD1,0xE16,0x282,0x745,0x90F,0xCC8,
 0xDAF,0x868,0x622,0x3E5,0xF71,0xAB6,0x4FC,0x13B,
 0x813,0xDD4,0x39E,0x659,0xACD,0xF0A,0x140,0x487,
 0x6D7,0x310,0xD5A,0x89D,0x409,0x1CE,0xF84,0xA43,
 0x36B,0x6AC,0x8E6,0xD21,0x1B5,0x472,0xA38,0xFFF
};

/* Functions start here */
/*
int golay_encode(short data)
{
    int code;

    code = data;
    code <<= 12;
    code += encode_table[data];

    return code;
}
*/
#include <gossip/sim.h>
#include <iostream.h>

sim_port inputs[] =
{
	SIM_INT_PORT ("in",1),
	NULL
};

sim_port outputs[] =
{
	SIM_INT_PORT ("out",1),
	NULL
};


struct golay_enc : sim_int_comp {

  void step (const sim_int **in, sim_int **out)
  {
	out[0][0] = in[0][0];
	out[0][0] <<= 12;
	out[0][0] += encode_table[in[0][0]];
  }

};

SIM_DECLARE_BLOCK (golay_enc, NULL, NULL, inputs, outputs);
