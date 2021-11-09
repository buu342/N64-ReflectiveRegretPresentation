/***************************************************************
                           slide18.c

A discussion of the different programming languages for N64 dev
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide18_init
    Initializes the slide
==============================*/

void slide18_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Programming Languages", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"C", 64, 122+32*(texty++));
    text_create(BULLET2"C++", 64, 122+32*(texty++));
    text_create(BULLET1"MIPS Assembly", 64, 122+32*(texty++));
    text_create(BULLET2"BASS, armips, or GAS.", 64, 122+32*(texty++));
    text_create(BULLET2"Unlikely you ever need it. Welcome to the future of", 64, 122+32*(texty++));
    text_create("Game development.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"If you're so inclined (Don't expect any support!):", 64, 122+32*(texty++));
    text_create(BULLET2"Rust", 64, 122+32*(texty++));
    text_create(BULLET2"Zig", 64, 122+32*(texty++));
}


/*==============================
    slide18_update
    Update slide logic every
    frame.
==============================*/

void slide18_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide18_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide18_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide18_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide18_cleanup()
{
    // Nothing extra to cleanup
}