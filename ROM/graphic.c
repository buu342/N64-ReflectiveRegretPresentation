/***************************************************************
                           graphic.c
                               
Graphic related display lists, need to be in their own object.
***************************************************************/

#include <nusys.h>
#include "config.h"

// Display list
Gfx glist[GLIST_LENGTH];
Gfx* glistp;

// Initializes the game camera in low res mode
static Vp viewport_low = {
    SCREEN_WD_SD*2, SCREEN_HT_SD*2, G_MAXZ/2, 0,
    SCREEN_WD_SD*2, SCREEN_HT_SD*2, G_MAXZ/2, 0,
};

// Initializes the RSP in low res mode
Gfx rspinit_dl_low[] = {
    gsSPViewport(&viewport_low),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
                        G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                        G_TEXTURE_GEN_LINEAR | G_LOD),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

// Initializes the RDP in low res mode
Gfx rdpinit_dl_low[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD_SD, SCREEN_HT_SD),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// Initializes the game camera in high res mode
static Vp viewport_high = {
    SCREEN_WD_HD*2, SCREEN_HT_HD*2, G_MAXZ/2, 0,
    SCREEN_WD_HD*2, SCREEN_HT_HD*2, G_MAXZ/2, 0,
};

// Initializes the RSP in high res mode
Gfx rspinit_dl_high[] = {
    gsSPViewport(&viewport_high),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
                        G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                        G_TEXTURE_GEN_LINEAR | G_LOD),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

// Initializes the RDP in high res mode
Gfx rdpinit_dl_high[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD_HD, SCREEN_HT_HD),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};