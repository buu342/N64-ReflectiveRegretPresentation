#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide09_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Reality Display Processor", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Fixed-pipeline rasterizer + shader", 64, 122+32*(texty++));
    text_create(BULLET2"Supports Z-buffering, mip-mapping, anti-aliasing,", 64, 122+32*(texty++));
    text_create("lots of other futuristic stuff,", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"Tiny texture cache (4KB!?). Manual syncing.", 64, 122+32*(texty++));
    text_create(BULLET2"HD 640x480 experience (though usually 320x240)", 64, 122+32*(texty++));
    text_create(BULLET2"90% chance your game is fill rate limited, not", 64, 122+32*(texty++));
    text_create("geometry limited", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"No vertex/fragment shaders, but you "BOLD"can"BOLD" do", 64, 122+32*(texty++));
    text_create("some cool effects with the Color Combiner and", 64+BULLET2SIZE, 122+32*(texty++));
    text_create("the Blender", 64+BULLET2SIZE, 122+32*(texty++));
}

void slide09_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide09_draw()
{

}

void slide09_cleanup()
{

}