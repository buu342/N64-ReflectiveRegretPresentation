/***************************************************************
                           slide19.c

A discussion of the different development tools
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide19_init
    Initializes the slide
==============================*/

void slide19_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Other Development Tools", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"It's unlikely you'll have access to official hardware or", 64, 122+26*(texty++));
    text_create("software (not that it helps, a lot of it is finicky or", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("annoying to use).", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET1"You'll pretty much DIY everything, but you have", 64, 122+26*(texty++));
    text_create("community tools for:", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET2"Textures conversion", 64, 122+26*(texty++));
    text_create(BULLET2"Modeling and Animating", 64, 122+26*(texty++));
    text_create(BULLET2"Sound and Music", 64, 122+26*(texty++));
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://n64.dev", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1"There is no generic game engine for N64 (IE Unity).", 64, 122+26*(texty++));
    text_create(BULLET1"If you want to hack or mod games, you're asking the", 64, 122+26*(texty++));
    text_create("wrong person, but they have their own tools.", 64+BULLET1SIZE, 122+26*(texty++));
}


/*==============================
    slide19_update
    Update slide logic every
    frame.
==============================*/

void slide19_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide19_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide19_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide19_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide19_cleanup()
{
    // Nothing extra to cleanup
}