#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide25_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("CPU Cache and Addresses", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Applications run in Kernel mode.", 64, 122+32*(texty++));
    text_create(BULLET1"CPU uses virtual addresses, RCP wants", 64, 122+32*(texty++));
    text_create("physical addresses.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"CPU virtual address translation by either:", 64, 122+32*(texty++));
    text_create(BULLET2"Direct mapping", 64, 122+32*(texty++));
    text_create(BULLET2"Translation lookaside buffer", 64, 122+32*(texty++));
    text_create(BULLET1"Writeback and Invalidate when using DMA", 64, 122+32*(texty++));
}

void slide25_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide25_draw()
{

}

void slide25_cleanup()
{

}