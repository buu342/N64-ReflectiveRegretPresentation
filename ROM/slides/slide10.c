#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide10_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Reality Signal Processor", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Vector processor that controls the RDP and many", 64, 122+32*(texty++));
    text_create("other things", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET2"Programmable to do whatever you want via", 64, 122+32*(texty++));
    text_create("microcode", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET3"Be it graphics, audio, video, decompressing assets,", 64, 122+32*(texty++));
    text_create("or crash your console (requiring a full power cycle)", 64+BULLET3SIZE, 122+32*(texty++));
    text_create(BULLET2"Audio isn't great (16-Bit), but can do up to 48,000hz", 64, 122+32*(texty++));
    text_create("stereo.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"Use fixed-point numbers over floats for best", 64, 122+32*(texty++));
    text_create("performance", 64+BULLET2SIZE, 122+32*(texty++));
}

void slide10_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide10_draw()
{

}

void slide10_cleanup()
{

}