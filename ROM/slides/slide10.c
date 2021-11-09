/***************************************************************
                           slide10.c

A description of the RDP
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide10_init
    Initializes the slide
==============================*/

void slide10_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Reality Signal Processor", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Vector processor that controls the RDP and many", 64, 122+32*(texty++));
    text_create("other things", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET2"Programmable to do whatever you want via", 64, 122+32*(texty++));
    text_create("microcode", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET3"Be it graphics, audio, video, decompressing assets,", 64, 122+32*(texty++));
    text_create("or crash your console (requiring a full power cycle)", 64+BULLET3SIZE, 122+32*(texty++));
    text_create(BULLET2"Audio isn't great (16-Bit), but can do up to 48,000hz", 64, 122+32*(texty++));
    text_create("stereo.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"Use fixed-point numbers over floats for best", 64, 122+32*(texty++));
    text_create("performance", 64+BULLET2SIZE, 122+32*(texty++));
}


/*==============================
    slide10_update
    Update slide logic every
    frame.
==============================*/

void slide10_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide10_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide10_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide10_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide10_cleanup()
{
    // Nothing extra to cleanup
}