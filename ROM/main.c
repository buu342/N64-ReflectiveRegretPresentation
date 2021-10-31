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

static void callback_prenmi();
static void callback_vsync(int tasksleft);

// Controller data
NUContData contdata[1];

// Global variables
u8 global_highres = TRUE;
volatile u8 global_slide = 29;


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