#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide21_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Threads and Tasks", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Preemptive scheduler", 64, 122+32*(texty++));
    text_create(BULLET2"Threads only yield when they want to, you don't", 64, 122+32*(texty++));
    text_create("have something like a round-robin scheduler.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET2"The CPU generates tasks for the RCP to perform.", 64, 122+32*(texty++));
    text_create(BULLET2"The RCP will interrupt the CPU when it's done", 64, 122+32*(texty++));
    text_create("with a task.", 64+BULLET2SIZE, 122+32*(texty++));
    text_create(BULLET1"Threads communicate with each other via", 64, 122+32*(texty++));
    text_create("messages", 64+BULLET1SIZE, 122+32*(texty++));
    text_create(BULLET1"Libdragon doesn't have threads (yet).", 64, 122+32*(texty++));
}

void slide21_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide21_draw()
{

}

void slide21_cleanup()
{

}