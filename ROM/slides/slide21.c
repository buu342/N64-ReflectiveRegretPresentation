/***************************************************************
                           slide21.c

An explanation of the thread system
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide21_init
    Initializes the slide
==============================*/

void slide21_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Threads and Tasks", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Preemptive scheduler", 64, 122+32*(texty++));
    text_create(BULLET2"Threads only yield when they want to, you don't", 64, 122+32*(texty++));
    text_create("have something like a round-robin scheduler.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"The CPU generates tasks for the RCP to perform.", 64, 122+32*(texty++));
    text_create(BULLET2"The RCP will interrupt the CPU when it's done", 64, 122+32*(texty++));
    text_create("with a task.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"Threads communicate with each other via", 64, 122+32*(texty++));
    text_create("messages", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Libdragon doesn't have threads (yet).", 64, 122+32*(texty++));
}


/*==============================
    slide21_update
    Update slide logic every
    frame.
==============================*/

void slide21_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide21_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide21_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide21_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide21_cleanup()
{
    // Nothing extra to cleanup
}