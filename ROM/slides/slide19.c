#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide19_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Other Development Tools", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"It's unlikely you'll have access to official hardware or", 64, 122+26*(texty++));
    text_create("software (not that it helps, a lot of it is finicky or", 64+BULLET1SIZE, 122+26*(texty++));
    text_create("annoying to use).", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET1"You'll pretty much DIY everything, but you have", 64, 122+26*(texty++));
    text_create("community tools for:", 64+BULLET1SIZE, 122+26*(texty++));
    text_create(BULLET2"Textures conversion", 64, 122+26*(texty++));
    text_create(BULLET2"Modeling and Animating", 64, 122+26*(texty++));
    text_create(BULLET2"Sound and Music", 64, 122+26*(texty++));
    text_setcolor(44, 44, 255, 255);
    text_create(BULLET1"https://n64.dev", 64, 122+26*(texty++));
    text_setcolor(0, 0, 0, 255);
    text_create(BULLET1"There is no generic game engine for N64 (IE Unity).", 64, 122+26*(texty++));
    text_create(BULLET1"If you want to hack or mod games, you're asking the", 64, 122+26*(texty++));
    text_create("wrong person, but they have their own tools.", 64+BULLET1SIZE, 122+26*(texty++));
}

void slide19_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide19_draw()
{

}

void slide19_cleanup()
{

}