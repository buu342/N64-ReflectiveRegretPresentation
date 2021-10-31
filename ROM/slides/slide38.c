#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


void slide38_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Thanks for putting up with me!", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Lots of ways of getting in touch:", 32, 122+26*(texty++));
    text_create(BULLET2, 32, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create("buu342@hotmail.com", 32+BULLET2SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET2, 32, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create("https://github.com/buu342", 32+BULLET2SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET2, 32, 122+26*texty);
    text_setcolor(44, 44, 255, 255);
    text_create("https://www.youtube.com/c/Buuu342/", 32+BULLET2SIZE, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET2"Buu342#1427", 32, 122+26*(texty++));
    text_create(BULLET1"Special thanks to:", 32, 122+26*(texty++));
    text_create(BULLET2"Rasky, Bigbass, Hazematman, Meeq, mikeryan for", 32, 122+26*(texty++));
    text_create("proofreading, correcting me, and answering questions.", 32+BULLET2SIZE, 122+26*(texty++));
    text_create(BULLET2"marshallh, krom, mikeryan, hcs, Dragonminded, Zoinkitty,", 32, 122+26*(texty++));
    text_create("Zilmar + angrylion for keeping the N64 community alive.", 32+BULLET2SIZE, 122+26*(texty++));
    text_create(BULLET2"N64brew for being an awesome community <3", 32, 122+26*(texty++));
    text_create(BULLET2"Inercia for inviting me and hosting such a wonderful event!", 32, 122+26*(texty++));
}

void slide38_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}
void slide38_draw()
{

}

void slide38_cleanup()
{

}