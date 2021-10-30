#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_n64.h"

static u8 slidestate;

void slide20_init()
{
    slidestate = 0;

    // Create the text
    text_setalign(ALIGN_CENTER);
    text_setpos(0, -256);
    text_setfont(&font_title);
    text_create("Development Process", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_create("The boring stuff is out of the way, let's get to the fun part!", SCREEN_WD_HD/2, 64+32);
}

void slide20_update()
{
    int i;
    Mtx helper;
    
    // Handle the animation
    switch (slidestate)
    {
        case 0:
            if (text_gety() < 0)
                text_setpos(text_getx(), lerp(text_gety(), 0, 0.05));
            break;
        case 1:
            if (text_gety() > -140)
                text_setpos(text_getx(), lerp(text_gety(), -160, 0.05));
            else
                slide_change(global_slide+1);
            break;
    }
    
    if (contdata[0].trigger & START_BUTTON)
        slidestate++;
}

void slide20_draw()
{

}

void slide20_cleanup()
{

}