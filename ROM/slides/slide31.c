#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide31_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("My Game Runs Like Crap!", SCREEN_WD_HD/2, 48);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Yes it does. Get used to it.", 64, 102+28*(texty++));
    text_create(BULLET2"Only one commercial game runs at a near stable ", 64, 102+28*(texty++));
    text_create("60FPS (50FPS on PAL), everything else pretty much", 64+BULLET2SIZE, 102+28*(texty++));
    text_create("runs at 30 or lower.", 64+BULLET2SIZE, 102+28*(texty++));
    text_create(BULLET2"Most games are fillrate limited.", 64, 102+28*(texty++));
    text_create(BULLET1"Optimize your texture calls.", 64, 102+28*(texty++));
    text_create(BULLET1"Optimize your drawing order.", 64, 102+28*(texty++));
    text_create(BULLET2"Selectively disable the Z-Buffer.", 64, 102+28*(texty++));
    text_create(BULLET1"Cull. LODs.", 64, 102+28*(texty++));
    text_create(BULLET1"Align data as much as possible.", 64, 102+28*(texty++));
    text_create(BULLET1"Use compiler optimizations. Duh.", 64, 102+28*(texty++));
    text_create(BULLET1"RTFM :)", 64, 102+28*(texty++));
}

void slide31_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide31_draw()
{

}

void slide31_cleanup()
{

}