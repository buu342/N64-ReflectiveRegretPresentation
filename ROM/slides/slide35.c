#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"


void slide35_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("The Renaissance", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Collectors get ahold of the original disks and hardware", 64, 122+26*(texty++));
    text_create(BULLET1"2008 "BIGDASH" Alt_libn64 is released", 64, 122+26*(texty++));
    text_create(BULLET1"2010 "BIGDASH" Libdragon merges with alt_libn64", 64, 122+26*(texty++));
    text_create(BULLET1"2011 "BIGDASH" marshallh's MGC demo, CIC is RE'd, 64Drive", 64, 122+26*(texty++));
    text_create("is released", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET1"2016 "BIGDASH" N64Brew is created", 64, 122+26*(texty++));
    text_create(BULLET1"2018 "BIGDASH" Pyoro64", 64, 122+26*(texty++));
    text_create(BULLET1"2019 "BIGDASH" SM64 RE project goes public", 64, 122+26*(texty++));
    text_create(BULLET1"2020 "BIGDASH" The first N64 Homebrew game Jam happens,", 64, 122+26*(texty++));
    text_create("20 years after the last PoM.", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET2, 64, 122+26*(texty));
    text_setcolor(44, 44, 255, 255);
    text_create(" https://n64brew.dev", 64+BULLET2SIZE, 122+26*(texty++));   
}

void slide35_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}
void slide35_draw()
{

}

void slide35_cleanup()
{

}