#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide18_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Programming Languages", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"C", 64, 122+32*(texty++));
    text_create(BULLET2"C++", 64, 122+32*(texty++));
    text_create(BULLET1"MIPS Assembly", 64, 122+32*(texty++));
    text_create(BULLET2"BASS, armips, or GAS.", 64, 122+32*(texty++));
    text_create(BULLET2"Unlikely you ever need it. Welcome to the future of", 64, 122+32*(texty++));
    text_create("Game development.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"If you're so inclined (Don't expect any support!):", 64, 122+32*(texty++));
    text_create(BULLET2"Rust", 64, 122+32*(texty++));
    text_create(BULLET2"Zig", 64, 122+32*(texty++));
}

void slide18_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide18_draw()
{

}

void slide18_cleanup()
{

}