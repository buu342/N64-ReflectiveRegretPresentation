/***************************************************************
                           slide03.c

The joke presentation title
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
static u16* spr_insanity;


/*==============================
    slide03_init
    Initializes the slide
==============================*/

void slide03_init()
{
    // Grab the texture from ROM
    spr_insanity = (u16*)malloc(_spr_insanitySegmentRomEnd-_spr_insanitySegmentRomStart);
    debug_assert(spr_insanity != NULL);
    nuPiReadRom((u32)_spr_insanitySegmentRomStart, spr_insanity, _spr_insanitySegmentRomEnd-_spr_insanitySegmentRomStart);

    // Create the slide's title and the image's source
    text_setalign(ALIGN_CENTER);
    text_setfont(&font_title);
    text_create("A Case Study of Stockholm Syndrome", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_create("The Nintendo 64 Development Community", SCREEN_WD_HD/2, 64+32);
    text_setfont(&font_small);
    text_setcolor(44, 44, 255, 255);
    text_create("https://www.istockphoto.com/photo/crazy-woman-wearing-a-", SCREEN_WD_HD/2, SCREEN_HT_HD/2+190);
    text_create("straight-jacket-in-an-asylum-gm117144609-16633602", SCREEN_WD_HD/2, SCREEN_HT_HD/2+190+12);
}


/*==============================
    slide03_update
    Update slide logic every
    frame.
==============================*/

void slide03_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide03_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide03_draw()
{
    int i;
    
    // Setup the RDP
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    
    // Draw the texture in 400x4 blocks, since it's too big to fit in TMEM
    for (i=0; i<268; i+=4)
    {
        gDPLoadTextureBlock(glistp++, spr_insanity+i*400, G_IM_FMT_RGBA, G_IM_SIZ_16b, 400, 4, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++, 
            (SCREEN_WD_HD/2-200) << 2, (SCREEN_HT_HD/2 - 80+i) << 2, 
            (SCREEN_WD_HD/2+200) << 2, (SCREEN_HT_HD/2 - 80+i+4) << 2, 
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }
}


/*==============================
    slide03_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide03_cleanup()
{
    free(spr_insanity);
}