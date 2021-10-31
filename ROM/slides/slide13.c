#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide13_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Official Development Kits", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Direct support line to Nintendo.", 64, 122+32*(texty++));
    text_create(BULLET1"All compatible with that Silicon Graphics Indy", 64, 122+32*(texty++));
    text_create("or Onyx you have lying around.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Lots of cool hardware.", 64, 122+32*(texty++));
    text_create(BULLET1"Very cheap, lets go over it!", 64, 122+32*(texty++));
}

void slide13_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide13_draw()
{

}

void slide13_cleanup()
{

}