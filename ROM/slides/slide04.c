/***************************************************************
                           slide04.c

Reasons to take up N64 homebrew development
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


/*********************************
             Globals
*********************************/

// The slide's state and the last text block's Y position
static u8 slidestate;
static u8 texty;


/*==============================
    slide04_init
    Initializes the slide
==============================*/

void slide04_init()
{
    slidestate = 0;
    texty = 0;
    
    // Create the title
    text_setalign(ALIGN_CENTER);
    text_setfont(&font_title);
    text_create("Why do this to yourself?", SCREEN_WD_HD/2, 64);
}


/*==============================
    slide04_update
    Update slide logic every
    frame.
==============================*/

void slide04_update()
{
    // Advance the slide's state when START is pressed
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_setfont(&font_default);
                text_setalign(ALIGN_LEFT);
                text_create("1.", 64, 122+32*texty);
                text_create("The N64 is in that era where an entire game could", 98, 122+32*(texty++));
                text_create("be made in a reasonable time frame by a single", 98, 122+32*(texty++));
                text_create("person and not look out of place.", 98, 122+32*(texty++));
                break;
            case 2:
                text_setfont(&font_default);
                text_setalign(ALIGN_LEFT);
                text_create("2.", 64, 122+32*texty);
                text_create("No assembly experience required (but it helps!)", 98, 122+32*(texty++));
                break;
            case 3:
                text_setfont(&font_default);
                text_setalign(ALIGN_LEFT);
                text_create("3.", 64, 122+32*texty);
                text_create("No need for specialized hardware, just get a", 98, 122+32*(texty++));
                text_create("flashcart and you're all set (or don't, but I wouldn't", 98, 122+32*(texty++));
                text_create("recommend it). A used N64 + controller is like 70$.", 98, 122+32*(texty++));
                break;
            case 4:
                text_setfont(&font_default);
                text_setalign(ALIGN_LEFT);
                text_create("4.", 64, 122+32*texty);
                text_create("It feels awesome to see your custom code running", 98, 122+32*(texty++));
                text_create("on the system.", 98, 122+32*(texty++));
                break;
            case 5:
                slide_change(global_slide+1);
                return;
        }
    }
}


/*==============================
    slide04_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide04_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide04_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide04_cleanup()
{
    // Nothing extra to cleanup
}