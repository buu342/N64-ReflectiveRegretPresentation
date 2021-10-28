#ifndef PRESENTATION_HELPER_H
#define PRESENTATION_HELPER_H
    
    /*********************************
                Functions
    *********************************/

    void rcp_init();
    void fb_clear(u8 r, u8 g, u8 b);
    
    
    /*********************************
                 Globals
    *********************************/

    extern Gfx rspinit_dl_low[];
    extern Gfx rdpinit_dl_low[];
    extern Gfx rspinit_dl_high[];
    extern Gfx rdpinit_dl_high[];

#endif