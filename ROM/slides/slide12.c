#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide12_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Cartridges", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"The N64 uses cartridges over disks. Cartridges", 64, 122+29*(texty++));
    text_create("were a great idea because:", 64+BULLET1SIZE, 122+29*(texty++));
    text_create(BULLET2"Cartridges are fast! No loading screens because you", 64, 122+29*(texty++));
    text_create("can "BOLD"almost"BOLD" stream data from it.", 64+BULLET2SIZE, 122+29*(texty++));
    text_create(BULLET2"You can fit extra hardware in the cartridges. Built in", 64, 122+29*(texty++));
    text_create("game saves! Real Time Clock!? MODEM!!!", 64+BULLET2SIZE, 122+29*(texty++));
    text_create(BULLET2"Can probably survive a nuclear blast.", 64, 122+29*(texty++));
    text_create(BULLET1"Cartridges were a terrible idea because:", 64, 122+29*(texty++));
    text_create(BULLET2"Expensive to make.", 64, 122+29*(texty++));
    text_create(BULLET2"Game size can balloon the cartridge cost.", 64, 122+29*(texty++));
    text_create(BULLET2"Blow into it to make it work... After the 2nd try.", 64, 122+29*(texty++));
}

void slide12_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide12_draw()
{

}

void slide12_cleanup()
{

}