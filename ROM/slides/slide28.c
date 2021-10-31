#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide28_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Blender", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Blends colors set from CC to the ones in the", 64, 122+32*(texty++));
    text_create("framebuffer. Also does Anti-Aliasing and Z-", 64+BULLET1SIZE, 122+32*(texty++));
    text_create("Buffering.", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Many equations, but the main one is:", 64, 122+32*(texty++));
    text_setalign(ALIGN_CENTER);
    text_create("((a x p) + (b x m)) / (a + b)", SCREEN_WD_HD/2, 122+32*(texty++));
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Also supports two passes.", 64, 122+32*(texty++));
    text_create(BULLET1"Way too much to talk about, read the manual.", 64, 122+32*(texty++));
}

void slide28_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide28_draw()
{

}

void slide28_cleanup()
{

}