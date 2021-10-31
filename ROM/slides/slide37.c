#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


void slide37_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Communities", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"#n64dev @ EFnet IRC", 64, 122+32*(texty++));
    text_create(BULLET2"Oldest active community", 64, 122+32*(texty++));
    text_create(BULLET1"N64brew @ Discord", 64, 122+32*(texty++));
    text_create(BULLET1"Discord64, iQueBrew, Hack64", 64, 122+32*(texty++));
    text_create(BULLET2"Lots of dedicated hacking and decompilation", 64, 122+32*(texty++));
    text_create(BULLET2"servers", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"/r/N64Homebrew", 64, 122+32*(texty++));
}

void slide37_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}
void slide37_draw()
{

}

void slide37_cleanup()
{

}