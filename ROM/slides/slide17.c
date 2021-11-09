/***************************************************************
                           slide17.c

A discussion of the different flashcart solutions
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide17_init
    Initializes the slide
==============================*/

void slide17_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Flashcarts", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"In case I haven't said it enough, get a Flashcart", 64, 122+29*(texty++));
    text_create("with USB!", 64+BULLET1SIZE, 122+29*(texty++));
    text_create(BULLET2"64Drive", 64, 122+29*(texty++));
    text_create(BULLET2"EverDrive X7", 64, 122+29*(texty++));
    text_create(BULLET2"DIY options: SummerCart64", 64, 122+29*(texty++));
    text_create(BULLET1"With USB, not only do you get debugging, but you get", 64, 122+29*(texty++));
    text_create("a faster workflow (no fiddling with SD cards).", 64+BULLET1SIZE, 122+29*(texty++));
    text_create(BULLET1"UNFLoader :)", 64, 122+29*(texty++));
    text_create(BULLET1"Don't trust emulators", 64, 122+29*(texty++));
    text_create(BULLET2"No, really", 64, 122+29*(texty++));
    text_create(BULLET2"Not even CEN64", 64, 122+29*(texty++));
}


/*==============================
    slide17_update
    Update slide logic every
    frame.
==============================*/

void slide17_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide17_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide17_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide17_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide17_cleanup()
{
    // Nothing extra to cleanup
}