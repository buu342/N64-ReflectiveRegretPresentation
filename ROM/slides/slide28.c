/***************************************************************
                           slide28.c

A super brief introduction to the Blender
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide28_init
    Initializes the slide
==============================*/

void slide28_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Blender", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Blends colors set from CC to the ones in the", 64, 122+32*(texty++));
    text_create("framebuffer. Also does Anti-Aliasing and Z-", 64+BULLET1SIZE, 122+32*(texty++));
    text_create("Buffering.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Many equations, but the main one is:", 64, 122+32*(texty++));
    text_setalign(ALIGN_CENTER);
    text_create("((a x p) + (b x m)) / (a + b)", SCREEN_WD_HD/2, 122+32*(texty++));
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Also supports two passes.", 64, 122+32*(texty++));
    text_create(BULLET1"Way too much to talk about, read the manual.", 64, 122+32*(texty++));
}


/*==============================
    slide28_update
    Update slide logic every
    frame.
==============================*/

void slide28_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide28_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide28_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide28_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide28_cleanup()
{
    // Nothing extra to cleanup
}