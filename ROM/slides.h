#ifndef _PRESENTATION_SLIDESS_H
#define _PRESENTATION_SLIDESS_H

    
    /*********************************
            Function Prototypes
    *********************************/

    // Stage functions
    void slide_common_init();
    void slide_common_update();
    void slide_common_draw_start();
    void slide_common_draw_end();
    void slide_common_cleanup();
    void slide_change(u8 slide);
    
    extern void (*slidefunc[][4])();


    /*********************************
                 Globals
    *********************************/

    extern Mtx projection, viewing, modeling;
    extern u16 normal;
    extern float campos[3];
    extern float camang[3];

#endif