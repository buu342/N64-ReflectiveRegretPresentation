/***************************************************************
                           slide34.c

The fall of the N64 homebrew scene
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


/*********************************
             Globals
*********************************/

// Pointer to store the noise texture
static u8* spr_noise;


/*==============================
    slide34_init
    Initializes the slide
==============================*/

void slide34_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("The Great Depression", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"1999"BIGDASH"The Oman Archives", 64, 122+32*(texty++));
    text_create(BULLET1"2001"BIGDASH"Project64 is released", 64, 122+32*(texty++));
    text_create(BULLET1"2002"BIGDASH"N64 is discontinued", 64, 122+32*(texty++));
    text_create(BULLET1"Interest in making new stuff for the system", 64, 122+32*(texty++));
    text_create("was very small, pretty much kept alive by a", 64+BULLET1SIZE, 122+32*(texty++));
    text_create("handful of users.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Infighting in the emulation scene.", 64, 122+32*(texty++));
    text_create(BULLET1"Preservation of games, hacks and translations.", 64, 122+32*(texty++));
    
    // Read the noise texture from ROM
    spr_noise = (u8*)malloc(_spr_noiseSegmentRomEnd-_spr_noiseSegmentRomStart);
    debug_assert(spr_noise != NULL);
    nuPiReadRom((u32)_spr_noiseSegmentRomStart, spr_noise, _spr_noiseSegmentRomEnd-_spr_noiseSegmentRomStart);
}


/*==============================
    slide34_update
    Update slide logic every
    frame.
==============================*/

void slide34_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide34_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide34_draw()
{
    // Draw noise over The Oman Archive text
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPLoadTextureBlock(glistp++, spr_noise, G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 7, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gDPSetPrimColor(glistp++, 0, 0, 0, 0, 0, 255);
    gSPScisTextureRectangle(glistp++, 
        152 << 2, 123 << 2, 
        152+183 << 2, 123+18 << 2, 
        G_TX_RENDERTILE, 
        osGetTime() << 5, osGetTime() << 5, 
        1 << 10, 1 << 10
    );
}


/*==============================
    slide34_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide34_cleanup()
{
    free(spr_noise);
}