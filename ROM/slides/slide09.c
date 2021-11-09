/***************************************************************
                           slide09.c

A description of the RDP
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide09_init
    Initializes the slide
==============================*/

void slide09_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Reality Display Processor", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Fixed-pipeline rasterizer + shader", 64, 122+32*(texty++));
    text_create(BULLET2"Supports Z-buffering, mip-mapping, anti-aliasing,", 64, 122+32*(texty++));
    text_create("lots of other futuristic stuff,", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"Tiny texture cache (4KB!?). Manual syncing.", 64, 122+32*(texty++));
    text_create(BULLET2"HD 640x480 experience (though usually 320x240)", 64, 122+32*(texty++));
    text_create(BULLET2"90% chance your game is fill rate limited, not", 64, 122+32*(texty++));
    text_create("geometry limited", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"No vertex/fragment shaders, but you "BOLD"can"BOLD" do", 64, 122+32*(texty++));
    text_create("some cool effects with the Color Combiner and", 64+BULLET2SIZE, 122+32*(texty++));
    text_create("the Blender", 64+BULLET2SIZE, 122+32*(texty++));
}


/*==============================
    slide09_update
    Update slide logic every
    frame.
==============================*/

void slide09_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide09_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide09_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide09_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide09_cleanup()
{
    // Nothing extra to cleanup
}