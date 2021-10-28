#include <nusys.h>
#include "../slides.h"

void slide00_init();
void slide00_update();
void slide00_draw();
void slide00_cleanup();
void slide01_init();
void slide01_update();
void slide01_draw();
void slide01_cleanup();

void (*slidefunc[][4])() = {
    {slide00_init, slide00_update, slide00_draw, slide00_cleanup}, 
    {slide01_init, slide01_update, slide01_draw, slide01_cleanup},
};