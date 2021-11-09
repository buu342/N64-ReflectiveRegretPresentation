/***************************************************************
                           slide33.c

The beginnings of the N64 homebrew scene
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide33_init
    Initializes the slide
==============================*/

void slide33_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("The Humble Beginnings: Dextrose", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"1997"BIGDASH"Dextrose is created.", 64, 122+32*(texty++));
    text_create(BULLET1"1998"BIGDASH"Presence of Mind, the first N64", 64, 122+32*(texty++));
    text_create("development competition.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"1999"BIGDASH"PoM #2", 64, 122+32*(texty++));
    text_create(BULLET1"Lots of demos and intros are released during", 64, 122+32*(texty++));
    text_create("this timeframe.", 64+BULLET1SIZE, 122+32*(texty++));
}


/*==============================
    slide33_update
    Update slide logic every
    frame.
==============================*/

void slide33_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide33_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide33_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide33_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide33_cleanup()
{
    // Nothing extra to cleanup
}