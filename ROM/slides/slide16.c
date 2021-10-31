#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"

void slide16_init()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Software Development Kit", SCREEN_WD_HD/2, 48);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"As of making this presentation, you currently ", 64, 102+26*(texty++));
    text_create("have two reliable options for SDK's:", 64+BULLET1SIZE, 102+26*(texty++));
    text_create(BULLET2"Libultra - The official SDK", 64, 102+26*(texty++));
    text_create(BULLET3"Obtainable from your local company liquidation", 64, 102+26*(texty++));
    text_create("auction or shady trench coat guy. Proprietary.", 64+BULLET3SIZE, 102+26*(texty++));
    text_create(BULLET3"Works on Windows 95 to XP out of the box, but we", 64, 102+26*(texty++));
    text_create("have modern alternatives that run off DOSBox,", 64+BULLET3SIZE, 102+26*(texty++));
    text_create("Wine, Windows 10 via WSL, or Linux/macOS.", 64+BULLET3SIZE, 102+26*(texty++));
    text_create(BULLET2"Libdragon – A free and open source SDK", 64, 102+26*(texty++));
    text_create(BULLET3"Only supports 2D, but this is changing very soon!!!", 64, 102+26*(texty++));
    text_create(BULLET3"Will work on any modern system. You can even", 64, 102+26*(texty++));
    text_create("get it for Docker!", 64+BULLET3SIZE, 102+26*(texty++));
    text_create(BULLET3"Easier to use as it doesn't expose much of the OS.", 64, 102+26*(texty++));
}
    
void slide16_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide16_draw()
{

}

void slide16_cleanup()
{

}