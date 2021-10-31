#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

static u8 slidestate;

void slide27_init()
{
    int texty = 0;
    slidestate = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Color + Alpha Combiner", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Closest thing to a fragment shader available", 64, 122+32*(texty++));
    text_create(BULLET1"Very simple equation:", 64, 122+32*(texty++));
    text_setalign(ALIGN_CENTER);
    text_create("(a - b) x c + d", SCREEN_WD_HD/2, 122+32*(texty++));
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Can be done in two passes", 64, 122+32*(texty++));
}

void slide27_update()
{
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                break;
            case 2:
                slide_change(global_slide+1);
                break;
        }
    }
}

void slide27_draw()
{

}

void slide27_cleanup()
{

}