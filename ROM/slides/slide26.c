/***************************************************************
                           slide26.c

A basic coverage of graphics programming
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

// The slide state
static u8 slidestate;

// A pointer for the grass texture
static u32* spr_grass;


/*==============================
    slide26_init
    Initializes the slide
==============================*/

void slide26_init()
{
    int texty = 0;
    slidestate = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Basic Graphics Programming", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Does N64 use OpenGL?", 64, 122+32*(texty++));
    text_create(BULLET1"Display lists", 64, 122+32*(texty++));
    text_create(BULLET1"Vertex cache", 64, 122+32*(texty++));
    text_create(BULLET2"Explicitly managed. Size depends on microcode.", 64, 122+32*(texty++));
    text_create(BULLET1"Matrix stack", 64, 122+32*(texty++));
    text_create(BULLET1"Vertex colors", 64, 122+32*(texty++));
    text_create(BULLET1"Texture memory", 64, 122+32*(texty++));
    text_create(BULLET2"4 Kilobytes!?", 64, 122+32*(texty++));
    text_create(BULLET3"Half if using Mip-Mapping", 64, 122+32*(texty++));
    
    // Load the SM64 grass texture from ROM
    spr_grass = (u32*)malloc(_spr_grassSegmentRomEnd-_spr_grassSegmentRomStart);
    debug_assert(spr_grass != NULL);
    nuPiReadRom((u32)_spr_grassSegmentRomStart, spr_grass, _spr_grassSegmentRomEnd-_spr_grassSegmentRomStart);
}


/*==============================
    slide26_update
    Update slide logic every
    frame.
==============================*/

void slide26_update()
{
    // Advance the slide state when START is pressed
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                break;
            case 2:
                slide_change(global_slide+1);
                break;
        }
    }
}


/*==============================
    slide26_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide26_draw()
{
    // Draw the grass texture
    if (slidestate == 1)
    {
        gDPSetCycleType(glistp++, G_CYC_1CYCLE);
        gSPClearGeometryMode(glistp++, G_ZBUFFER);
        gDPSetTexturePersp(glistp++, G_TP_NONE);
        gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF);
        gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        gDPSetTextureFilter(glistp++, G_TF_BILERP);
        gDPLoadTextureBlock(glistp++, spr_grass, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++, 
            SCREEN_WD_HD/2 - 16 << 2, SCREEN_HT_HD/2 - 16 << 2,
            SCREEN_WD_HD/2 + 16 << 2, SCREEN_HT_HD/2 + 16 << 2,
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }
}


/*==============================
    slide26_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide26_cleanup()
{
    free(spr_grass);
}