#include <nusys.h>
#include "../slides.h"

extern void slide00_init();
extern void slide00_update();
extern void slide00_draw();
extern void slide00_cleanup();
extern void slide01_init();
extern void slide01_update();
extern void slide01_draw();
extern void slide01_cleanup();
extern void slide02_init();
extern void slide02_update();
extern void slide02_draw();
extern void slide02_cleanup();
extern void slide03_init();
extern void slide03_update();
extern void slide03_draw();
extern void slide03_cleanup();

void (*slidefunc[][4])() = {
    {slide00_init, slide00_update, slide00_draw, slide00_cleanup}, 
    {slide01_init, slide01_update, slide01_draw, slide01_cleanup},
    {slide02_init, slide02_update, slide02_draw, slide02_cleanup},
    {slide03_init, slide03_update, slide03_draw, slide03_cleanup},
};