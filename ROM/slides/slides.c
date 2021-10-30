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
extern void slide04_init();
extern void slide04_update();
extern void slide04_draw();
extern void slide04_cleanup();
extern void slide05_init();
extern void slide05_update();
extern void slide05_draw();
extern void slide05_cleanup();
extern void slide06_init();
extern void slide06_update();
extern void slide06_draw();
extern void slide06_cleanup();
extern void slide07_init();
extern void slide07_update();
extern void slide07_draw();
extern void slide07_cleanup();
extern void slide08_init();
extern void slide08_update();
extern void slide08_draw();
extern void slide08_cleanup();
extern void slide09_init();
extern void slide09_update();
extern void slide09_draw();
extern void slide09_cleanup();
extern void slide10_init();
extern void slide10_update();
extern void slide10_draw();
extern void slide10_cleanup();
extern void slide11_init();
extern void slide11_update();
extern void slide11_draw();
extern void slide11_cleanup();
extern void slide12_init();
extern void slide12_update();
extern void slide12_draw();
extern void slide12_cleanup();
extern void slide13_init();
extern void slide13_update();
extern void slide13_draw();
extern void slide13_cleanup();
extern void slide14_init();
extern void slide14_update();
extern void slide14_draw();
extern void slide14_cleanup();
extern void slide15_init();
extern void slide15_update();
extern void slide15_draw();
extern void slide15_cleanup();
extern void slide16_init();
extern void slide16_update();
extern void slide16_draw();
extern void slide16_cleanup();
extern void slide17_init();
extern void slide17_update();
extern void slide17_draw();
extern void slide17_cleanup();
extern void slide18_init();
extern void slide18_update();
extern void slide18_draw();
extern void slide18_cleanup();
extern void slide19_init();
extern void slide19_update();
extern void slide19_draw();
extern void slide19_cleanup();
extern void slide20_init();
extern void slide20_update();
extern void slide20_draw();
extern void slide20_cleanup();

void (*slidefunc[][4])() = {
    {slide00_init, slide00_update, slide00_draw, slide00_cleanup}, 
    {slide01_init, slide01_update, slide01_draw, slide01_cleanup},
    {slide02_init, slide02_update, slide02_draw, slide02_cleanup},
    {slide03_init, slide03_update, slide03_draw, slide03_cleanup},
    {slide04_init, slide04_update, slide04_draw, slide04_cleanup},
    {slide05_init, slide05_update, slide05_draw, slide05_cleanup},
    {slide06_init, slide06_update, slide06_draw, slide06_cleanup},
    {slide07_init, slide07_update, slide07_draw, slide07_cleanup},
    {slide08_init, slide08_update, slide08_draw, slide08_cleanup},
    {slide09_init, slide09_update, slide09_draw, slide09_cleanup},
    {slide10_init, slide10_update, slide10_draw, slide10_cleanup},
    {slide11_init, slide11_update, slide11_draw, slide11_cleanup},
    {slide12_init, slide12_update, slide12_draw, slide12_cleanup},
    {slide13_init, slide13_update, slide13_draw, slide13_cleanup},
    {slide14_init, slide14_update, slide14_draw, slide14_cleanup},
    {slide15_init, slide15_update, slide15_draw, slide15_cleanup},
    {slide16_init, slide16_update, slide16_draw, slide16_cleanup},
    {slide17_init, slide17_update, slide17_draw, slide17_cleanup},
    {slide18_init, slide18_update, slide18_draw, slide18_cleanup},
    {slide19_init, slide19_update, slide19_draw, slide19_cleanup},
    {slide20_init, slide20_update, slide20_draw, slide20_cleanup},
};