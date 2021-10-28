/***************************************************************
                            main.c
                               
Program entrypoint.
***************************************************************/

#include <nusys.h>
#include "config.h"
#include "slides.h"
#include "text.h"
#include "debug.h"


/*********************************
        Function Prototypes
*********************************/

static void init_highres();
static void init_lowres();
static void callback_prenmi();
static void callback_vsync(int tasksleft);

// Controller data
NUContData contdata[1];

// High resolution framebuffers array
u16* framebuffers_hires[3] = {
    ADDR_FB1_HD,
    ADDR_FB2_HD,
    ADDR_FB3_HD,
};

// Low resolution framebuffers array
u16* framebuffers_lowres[3] = {
    ADDR_FB1_SD,
    ADDR_FB2_SD,
    ADDR_FB3_SD,
};

// Global variables
u8 global_highres = TRUE;
volatile u8 global_slide = 0;


/*==============================
    mainproc
    Initializes the game
==============================*/

void mainproc()
{
    // Initialize and activate the graphics thread and Graphics Task Manager.
    nuGfxInit();
    
    // Initialize the controller
    nuContInit();
    
    // Initialize USB debug mode
    debug_initialize();
    
    // Check for expansion PAK
    if (osMemSize < RAMBANK_SIZE*8)
    {
        debug_printf("Expansion pak missing! Stopping.\n");
        return;
    }
    
    // Initialize the heap, give it an entire RAM bank to itself
    InitHeap(RAMBANK_3, RAMBANK_SIZE);
    
    // Start in high resolution mode
    init_highres();
    
    // Initialize the font system
    text_initialize();
        
    // Initialize slide 0
    slide_common_init();
    (slidefunc[global_slide][0])();
        
    // Set callback functions for reset and graphics
    nuGfxFuncSet((NUGfxFunc)callback_vsync);
    
    // Turn on the screen and loop forever to keep the idle thread busy
    nuGfxDisplayOn();
    while(1)
        ;
}


/*==============================
    callback_vsync
    Code that runs on on the graphics
    thread
    @param The number of tasks left to execute
==============================*/

static void callback_vsync(int tasksleft)
{
    // Update the slide, then draw it when the RDP is ready
    slide_common_update();
    (slidefunc[global_slide][1])();
    if (tasksleft < 1)
    {
        slide_common_draw_start();
        (slidefunc[global_slide][2])();
        slide_common_draw_end();
    }
}

void init_highres()
{
    global_highres = TRUE;
    
    // Wait for graphic tasks to end
    nuGfxTaskAllEndWait();
    
    // Set the VI mode based on the region
    switch (TV_TYPE)
    {
        case NTSC: osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]); break;
        case PAL : osViSetMode(&osViModeTable[OS_VI_FPAL_HAN1]); break;
        case MPAL: osViSetMode(&osViModeTable[OS_VI_MPAL_HAN1]); break;
    }

    // Turn the screen off
    nuGfxDisplayOff();

    // Set the framebuffer and z-buffer addresses
    nuGfxSetCfb(framebuffers_hires, sizeof(framebuffers_hires)/sizeof(framebuffers_hires[0]));
    nuGfxSetZBuffer(ADDR_ZB_HD);
    
    // Turn the display back on
    nuGfxDisplayOn();
}

void init_lowres()
{
    global_highres = FALSE;
    
    // Wait for graphic tasks to end
    nuGfxTaskAllEndWait();

    // Set the VI mode based on the region
    switch (TV_TYPE)
    {
        case NTSC: osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]); break;
        case PAL : osViSetMode(&osViModeTable[OS_VI_FPAL_LAN1]); break;
        case MPAL: osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]); break;
    }

    // Turn the screen off
    nuGfxDisplayOff();

    // Set the framebuffer and z-buffer addresses
    nuGfxSetCfb(framebuffers_lowres, sizeof(framebuffers_lowres)/sizeof(framebuffers_lowres[0]));
    nuGfxSetZBuffer(ADDR_ZB_SD);
    
    // Turn the display back on
    nuGfxDisplayOn();
}