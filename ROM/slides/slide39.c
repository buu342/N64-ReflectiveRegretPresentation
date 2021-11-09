/***************************************************************
                           slide39.c

A collection of sources used in this presentation
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


/*==============================
    slide39_init
    Initializes the slide
==============================*/

void slide39_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Sources", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"N64 Programming Manual", 64, 122+26*(texty++));
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" http://en64.shoutwiki.com/wiki/N64_Memory", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://www.copetti.org/writings/consoles/nintendo", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("-64/", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://www.retroreversing.com/n64/", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://www.moria.us/tags/nintendo-64", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://web.archive.org/web/20021017102203/http://", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("www.dextrose.com/dx_index.htm", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://en.wikipedia.org/wiki/Nintendo_64_", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("programming_characteristics", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1, 64, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create(" https://en.wikipedia.org/wiki/Nintendo_64_", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("technical_specifications", 64+BULLET1SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
}


/*==============================
    slide39_update
    Update slide logic every
    frame.
==============================*/

void slide39_update()
{
    // Nothing to update
}


/*==============================
    slide39_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide39_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide39_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide39_cleanup()
{
    // Nothing extra to cleanup
}