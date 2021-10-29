#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"

void slide04_init()
{

}

void slide04_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide04_draw()
{

}

void slide04_cleanup()
{

}