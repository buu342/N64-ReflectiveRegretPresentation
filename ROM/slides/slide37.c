/***************************************************************
                           slide37.c

Some cool N64 development communities
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


/*==============================
    slide37_init
    Initializes the slide
==============================*/

void slide37_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Communities", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"#n64dev @ EFnet IRC", 64, 122+32*(texty++));
    text_create(BULLET2"Oldest active community", 64, 122+32*(texty++));
    text_create(BULLET1"N64brew @ Discord", 64, 122+32*(texty++));
    text_create(BULLET1"Discord64, iQueBrew, Hack64", 64, 122+32*(texty++));
    text_create(BULLET2"Lots of dedicated hacking and decompilation", 64, 122+32*(texty++));
    text_create("servers", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"/r/N64Homebrew", 64, 122+32*(texty++));
}


/*==============================
    slide37_update
    Update slide logic every
    frame.
==============================*/

void slide37_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide37_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide37_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide37_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide37_cleanup()
{
    // Nothing extra to cleanup
}