#ifndef _PRESENTATION_SLIDESS_H
#define _PRESENTATION_SLIDESS_H

    extern Mtx projection, viewing, modeling;
    extern u16 normal;
    extern float campos[3];
    extern float camang[3];

    
    /*********************************
            Function Prototypes
    *********************************/

    // Stage functions
    void slide_common_init();
    void slide_common_update();
    void slide_common_draw_start();
    void slide_common_draw_end();
    void slide_common_cleanup();
    
    extern void (*slidefunc[][4])();
    
#endif