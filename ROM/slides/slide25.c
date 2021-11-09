/***************************************************************
                           slide25.c

An explanation regarding the necessity of performing transparent
caching in the CPU
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide25_init
    Initializes the slide
==============================*/

void slide25_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("CPU Cache and Addresses", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Applications run in Kernel mode.", 64, 122+32*(texty++));
    text_create(BULLET1"CPU uses virtual addresses, RCP wants", 64, 122+32*(texty++));
    text_create("physical addresses.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"CPU virtual address translation by either:", 64, 122+32*(texty++));
    text_create(BULLET2"Direct mapping", 64, 122+32*(texty++));
    text_create(BULLET2"Translation lookaside buffer", 64, 122+32*(texty++));
    text_create(BULLET1"Writeback and Invalidate when using DMA", 64, 122+32*(texty++));
}


/*==============================
    slide25_update
    Update slide logic every
    frame.
==============================*/

void slide25_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide25_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide25_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide25_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide25_cleanup()
{
    // Nothing extra to cleanup
}