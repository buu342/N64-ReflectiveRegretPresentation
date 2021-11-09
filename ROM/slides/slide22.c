/***************************************************************
                           slide22.c

An explanation of Microcode
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


/*==============================
    slide22_init
    Initializes the slide
==============================*/

void slide22_init()
{
    int texty = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Microcode", SCREEN_WD_HD/2, 56);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"When generating tasks for the RCP, the CPU chooses", 64, 102+28*(texty++));
    text_create("which microcode (ucode) will execute on the RSP to", 64+BULLET1SIZE, 102+28*(texty++));
    text_create("perform the task.", 64+BULLET1SIZE, 102+28*(texty++));
    text_create(BULLET1"Non comprehensive list of ucode (bold is proprietary):", 64, 102+28*(texty++));
    text_create(BULLET2"3D: "BOLD"F3DEX2"BOLD", "BOLD"Fast3D"BOLD", ugfx, libhfx", 64, 102+28*(texty++));
    text_create(BULLET2"2D: "BOLD"S2DEX"BOLD".", 64, 102+28*(texty++));
    text_create(BULLET2"Audio: "BOLD"naudio"BOLD", RSP Mixer", 64, 102+28*(texty++));
    text_create(BULLET2"Video: "BOLD"HVQM2"BOLD", H264", 64, 102+28*(texty++));
    text_create(BULLET1"The Cool Kids Club was given access to the source", 64, 102+28*(texty++));
    text_create("code for the original ucodes and documentation", 64+BULLET1SIZE, 102+28*(texty++));
    text_create("scribbled on a used paper napkin.", 64+BULLET1SIZE, 102+28*(texty++));
    text_create(BULLET2"r64emu", 64, 102+28*(texty++));
}


/*==============================
    slide22_update
    Update slide logic every
    frame.
==============================*/

void slide22_update()
{
    // Change slide when START is pressed
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}


/*==============================
    slide22_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide22_draw()
{
    // Nothing extra to draw besides text
}


/*==============================
    slide22_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide22_cleanup()
{
    // Nothing extra to cleanup
}