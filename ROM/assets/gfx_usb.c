#include <nusys.h>
#include "tex_usb.h"

// Custom combine mode to allow mixing primitive and vertex colors
#ifndef G_CC_PRIMLITE
    #define G_CC_PRIMLITE SHADE,0,PRIMITIVE,0,0,0,0,PRIMITIVE
#endif

static Vtx vtx_mdl_usb[] = {
    {-2, 0, -1, 0, 0, 0, 0, 0, -127, 255}, /* 0 */
    {-2, 0, -1, 0, 0, 0, 0, 0, -127, 255}, /* 1 */
    {-1, 0, -1, 0, 0, 0, 0, 0, -127, 255}, /* 2 */
    {-1, 0, -1, 0, 0, 0, 0, 0, -127, 255}, /* 3 */
    {-1, 0, 1, 0, 0, 0, 0, -90, 90, 255}, /* 4 */
    {-1, 0, 1, 0, 0, 0, 0, 0, 127, 255}, /* 5 */
    {-2, 0, 1, 0, 0, 0, -90, 0, 90, 255}, /* 6 */
    {-2, 0, 1, 0, 0, 0, -60, -79, 79, 255}, /* 7 */
    {-1, 0, 1, 0, 0, 0, -93, -84, 21, 255}, /* 8 */
    {-1, 0, 1, 0, 0, 0, -93, 84, 21, 255}, /* 9 */
    {-1, 0, -1, 0, 0, 0, -93, 84, -21, 255}, /* 10 */
    {-1, 0, -1, 0, 0, 0, -93, -84, -21, 255}, /* 11 */
    {-1, 0, 1, 0, 0, 0, -67, -21, 106, 255}, /* 12 */
    {4, 0, 1, 0, 0, 0, 57, -27, 110, 255}, /* 13 */
    {4, 0, 1, 0, 0, 0, 46, 78, 89, 255}, /* 14 */
    {-1, 0, 1, 0, 0, 0, -54, 77, 86, 255}, /* 15 */
    {-1, 0, -1, 0, 0, 0, -54, 77, -86, 255}, /* 16 */
    {-1, 0, -1, 0, 0, 0, -67, -21, -106, 255}, /* 17 */
    {4, 0, 1, 0, 0, 0, 93, 82, 29, 255}, /* 18 */
    {4, 0, -1, 0, 0, 0, 93, 82, -29, 255}, /* 19 */
    {4, 0, -1, 0, 0, 0, 46, 78, -89, 255}, /* 20 */
    {4, 0, -1, 0, 0, 0, 57, -27, -110, 255}, /* 21 */
    {4, 0, 1, 0, 0, 0, 93, -82, 29, 255}, /* 22 */
    {4, 0, -1, 0, 0, 0, 93, -82, -29, 255}, /* 23 */
    {-2, 0, 1, 0, 0, 0, 0, 127, 0, 255}, /* 24 */
    {-1, 0, 1, 0, 1024, 0, 0, 127, 0, 255}, /* 25 */
    {-1, 0, -1, 0, 1024, 1024, 0, 127, 0, 255}, /* 26 */
    {-2, 0, -1, 0, 0, 1024, 0, 127, 0, 255}, /* 27 */
    {-1, 0, -1, 0, 0, 1024, 0, -127, 0, 255}, /* 28 */
    {4, 0, -1, 0, 2048, 1024, 0, -127, 0, 255}, /* 29 */
    {4, 0, 1, 0, 2048, 0, 0, -127, 0, 255}, /* 30 */
    {-1, 0, 1, 0, 0, 0, 0, -127, 0, 255}, /* 31 */
    {-2, 0, 1, 0, 0, 0, -65, -77, 77, 255}, /* 32 */
    {-2, 0, 1, 0, 1024, 0, -90, 0, 90, 255}, /* 33 */
    {-2, 0, -1, 0, 1024, 1024, -127, 0, 0, 255}, /* 34 */
    {-2, 0, -1, 0, 0, 1024, -90, -90, 0, 255}, /* 35 */
    {-1, 0, 1, 0, 1024, 0, 0, -90, 90, 255}, /* 36 */
    {-2, 0, 1, 0, 0, 0, -65, -77, 77, 255}, /* 37 */
    {-2, 0, -1, 0, 0, 1024, -90, -90, 0, 255}, /* 38 */
    {-1, 0, -1, 0, 1024, 1024, 0, -127, 0, 255}, /* 39 */
};

Gfx gfx_mdl_usb[] = {
    gsSPVertex(vtx_mdl_usb+0, 32, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_PRIMLITE, G_CC_PRIMLITE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 231, 231, 231, 255),
    gsDPPipeSync(),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPSetPrimColor(0, 0, 71, 71, 71, 255),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(10, 16, 17, 0, 10, 17, 11, 0),
    gsSP2Triangles(8, 12, 15, 0, 8, 15, 9, 0),
    gsSP2Triangles(9, 15, 16, 0, 9, 16, 10, 0),
    gsSP2Triangles(11, 17, 12, 0, 11, 12, 8, 0),
    gsSP2Triangles(14, 18, 19, 0, 14, 19, 20, 0),
    gsSP2Triangles(15, 14, 20, 0, 15, 20, 16, 0),
    gsSP2Triangles(16, 20, 21, 0, 16, 21, 17, 0),
    gsSP2Triangles(22, 23, 19, 0, 22, 19, 18, 0),
    gsSP2Triangles(21, 23, 22, 0, 21, 22, 13, 0),
    gsSP2Triangles(20, 19, 23, 0, 20, 23, 21, 0),
    gsSP2Triangles(13, 22, 18, 0, 13, 18, 14, 0),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPLoadTextureBlock(tex_usb_bottom, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsDPLoadTextureBlock(tex_usb_front, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),

    gsSPVertex(vtx_mdl_usb+32, 8, 0),
    gsDPLoadTextureBlock(tex_usb_slot, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(tex_usb_top, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};
