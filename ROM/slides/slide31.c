/***************************************************************
                           slide31.c

A quick performance tuning guide
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide31_init
    Initializes the slide
==============================*/

void slide31_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("My Game Runs Like Crap!", SCREEN_WD_HD/2, 48);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Yes it does. Get used to it.", 64, 102+28*(texty++));
    text_create(BULLET2"Only one commercial game runs at a near stable ", 64, 102+28*(texty++));
    text_create("60FPS (50FPS on PAL), everything else pretty much", 64+BULLET2SIZE, 102+28*(texty++));
    text_create("runs at 30 or lower.", 64+BULLET2SIZE, 102+28*(texty++));
    text_create(BULLET2"Most games are fillrate limited.", 64, 102+28*(texty++));
    text_create(BULLET1"Optimize your texture calls.", 64, 102+28*(texty++));
    text_create(BULLET1"Optimize your drawing order.", 64, 102+28*(texty++));
    text_create(BULLET2"Selectively disable the Z-Buffer.", 64, 102+28*(texty++));
    text_create(BULLET1"Cull. LODs.", 64, 102+28*(texty++));
    text_create(BULLET1"Align data as much as possible.", 64, 102+28*(texty++));
    text_create(BULLET1"Use compiler optimizations. Duh.", 64, 102+28*(texty++));
    text_create(BULLET1"RTFM :)", 64, 102+28*(texty++));
}


/*==============================
    slide31_update
    Update slide logic every
    frame.
==============================*/

void slide31_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide31_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide31_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide31_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide31_cleanup()
{
    // Nothing extra to cleanup
}