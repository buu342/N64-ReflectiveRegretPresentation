#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide24_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("1MB Limit on Code", SCREEN_WD_HD/2, 64);
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

void slide24_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide24_draw()
{

}

void slide24_cleanup()
{

}