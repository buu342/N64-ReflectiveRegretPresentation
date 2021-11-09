/***************************************************************
                           slide15.c

A set of tables showcasing different unofficial development
setups and their prices
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

// Global to store the texture we grab from ROM
u16* spr_slide;


/*==============================
    slide15_init
    Initializes the slide
==============================*/

void slide15_init()
{
    // Load the texture from ROM
    spr_slide = (u16*)malloc(_spr_slide15SegmentRomEnd-_spr_slide15SegmentRomStart);
    debug_assert(spr_slide != NULL);
    nuPiReadRom((u32)_spr_slide15SegmentRomStart, spr_slide, _spr_slide15SegmentRomEnd-_spr_slide15SegmentRomStart);
}


/*==============================
    slide15_update
    Update slide logic every
    frame.
==============================*/

void slide15_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide15_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide15_draw()
{
    int i;
    
    // Initialize the RDP
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureFilter(glistp++, G_TF_BILERP);
    
    // Draw the texture in 640x3 blocks, since it's too big to fit in TMEM
    for (i=0; i<480; i+=3)
    {
        gDPLoadTextureBlock(glistp++, spr_slide+i*640, G_IM_FMT_RGBA, G_IM_SIZ_16b, 640, 3, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++, 
            0 << 2, i << 2, 
            640 << 2, i+3 << 2, 
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }
}


/*==============================
    slide15_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide15_cleanup()
{
    free(spr_slide);
}