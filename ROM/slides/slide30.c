/***************************************************************
                           slide30.c

A brief overview of sound and music
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide30_init
    Initializes the slide
==============================*/

void slide30_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Sound and Music", SCREEN_WD_HD/2, 48);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Affected by region!", 64, 102+28*(texty++));
    text_create(BULLET1"You can just put whatever you want in an audio buffer", 64, 102+28*(texty++));
    text_create(BULLET1"Prepare data to avoid popping, use a queue. Helps to", 64, 102+28*(texty++));
    text_create("write a scheduler to interleave audio and graphic tasks.", 64+BULLET1SIZE, 102+28*(texty++));
    text_create(BULLET1"naudio", 64, 102+28*(texty++));
    text_create(BULLET2"ADPCM", 64, 102+28*(texty++));
    text_create(BULLET2"MIDI", 64, 102+28*(texty++));
    text_create(BULLET3"No limit on channels", 64, 102+28*(texty++));
    text_create(BULLET1"RSP Mixer", 64, 102+28*(texty++));
    text_create(BULLET2"Tracker Music (XM)", 64, 102+28*(texty++));
    text_create(BULLET1"MP3?", 64, 102+28*(texty++));
    text_create(BULLET1"Probably will eat up your ROM size", 64, 102+28*(texty++));
}


/*==============================
    slide30_update
    Update slide logic every
    frame.
==============================*/

void slide30_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide30_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide30_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide30_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide30_cleanup()
{
    // Nothing extra to cleanup
}