/***************************************************************
                           slide24.c

An explanation of the framebuffer and a demonstration of the
importance of memory alignment
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide24_init
    Initializes the slide
==============================*/

void slide24_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("1MB Limit on Code", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"The bootcode only loads the first MB of code", 64, 122+32*(texty++));
    text_create("into RAM and executes it.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET2"Don't link your assets to the codesegment. Load", 64, 122+32*(texty++));
    text_create("them as you need them from the cartridge. ", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"If you do hit it, are solutions:", 64, 122+32*(texty++));
    text_create(BULLET2"Overlays", 64, 122+32*(texty++));
    text_create(BULLET2"Relocatable modules", 64, 122+32*(texty++));
    text_create(BULLET1"Libdragon has a built in filesystem.", 64, 122+32*(texty++));
}


/*==============================
    slide24_update
    Update slide logic every
    frame.
==============================*/

void slide24_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide24_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide24_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide24_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide24_cleanup()
{
    // Nothing extra to cleanup
}