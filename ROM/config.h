#ifndef _PRESENTATION_CONFIG_H
#define _PRESENTATION_CONFIG_H

    /*********************************
           Configuration Macros
    *********************************/

    // TV Types
    #define NTSC    0
    #define PAL     1
    #define MPAL    2
    
    // TV setting
    #define TV_TYPE NTSC

    // Rendering resolution (Standard Definition)
    #define SCREEN_WD_SD 320
    #if TV_TYPE == NTSC
        #define SCREEN_HT_SD 240
    #else
        #define SCREEN_HT_SD 288
    #endif
    
    // Rendering resolution (High Definition)
    #define SCREEN_WD_HD 640
    #if TV_TYPE == NTSC
        #define SCREEN_HT_HD 480
    #else
        #define SCREEN_HT_HD 576
    #endif
    
    // RAM Bank Addresses
    #define RAMBANK_START 0x80000000
    #define RAMBANK_SIZE  0x100000
    #define RAMBANK_1 (RAMBANK_START + RAMBANK_SIZE*0)
    #define RAMBANK_2 (RAMBANK_START + RAMBANK_SIZE*1)
    #define RAMBANK_3 (RAMBANK_START + RAMBANK_SIZE*2)
    #define RAMBANK_4 (RAMBANK_START + RAMBANK_SIZE*3)
    #define RAMBANK_5 (RAMBANK_START + RAMBANK_SIZE*4)
    #define RAMBANK_6 (RAMBANK_START + RAMBANK_SIZE*5)
    #define RAMBANK_7 (RAMBANK_START + RAMBANK_SIZE*6)
    #define RAMBANK_8 (RAMBANK_START + RAMBANK_SIZE*7)
    
    // Address calculations
    #define ADDR_FB1_HD ((u16*)(RAMBANK_5))
    #define ADDR_FB2_HD ((u16*)(RAMBANK_6))
    #define ADDR_FB3_HD ((u16*)(RAMBANK_7))
    #define	ADDR_ZB_HD  ((u16*)(RAMBANK_8))
    #define ADDR_FB1_SD ((u16*)(RAMBANK_5))
    #define ADDR_FB2_SD ((u16*)(RAMBANK_6))
    #define ADDR_FB3_SD ((u16*)(RAMBANK_7))
    #define	ADDR_ZB_SD  ((u16*)(RAMBANK_8))
    
    // Bad framebuffer addresses
    #define SIZE_FB_HD     SCREEN_WD_HD*SCREEN_HT_HD*2
    #define ADDR_FB1_HDBAD ((u16*)(RAMBANK_5+SIZE_FB_HD*0))
    #define ADDR_FB2_HDBAD ((u16*)(RAMBANK_5+SIZE_FB_HD*2))
    #define ADDR_FB3_HDBAD ((u16*)(RAMBANK_5+SIZE_FB_HD*3))
    #define	ADDR_ZB_HDBAD  ((u16*)(RAMBANK_5+SIZE_FB_HD*1))

    // Array sizes
    #define GLIST_LENGTH 4096
    #define HEAP_LENGTH  1024
    
    
    /*********************************
                 Globals
    *********************************/
    
    extern Gfx glist[];
    extern Gfx* glistp;
    
    extern NUContData contdata[1];

    extern u8 global_highres;
    extern u8 global_slide;
    
#endif