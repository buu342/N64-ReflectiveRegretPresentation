/***************************************************************
                           slide00.c

The introductory slide
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_the_n.h"


/*********************************
             Globals
*********************************/

// The slide state
static u8  slidestate;

// Globals regarding the N model's transformation
static Mtx n_matrix;
static Mtx rotmatrix;
static Mtx transmatrix;
static float angle;


/*==============================
    slide00_init
    Initializes the slide
==============================*/

void slide00_init()
{
    Mtx helper;
    slidestate = 0;
    
    // Initialize the N
    load_overlay(_gfx_the_nSegmentStart,
        (u8*)_gfx_the_nSegmentRomStart,  (u8*)_gfx_the_nSegmentRomEnd, 
        (u8*)_gfx_the_nSegmentTextStart, (u8*)_gfx_the_nSegmentTextEnd, 
        (u8*)_gfx_the_nSegmentDataStart, (u8*)_gfx_the_nSegmentDataEnd, 
        (u8*)_gfx_the_nSegmentBssStart,  (u8*)_gfx_the_nSegmentBssEnd 
    );
    
    // Setup the N on the screen
    guScale(&helper, 0.075, 0.075, 0.075);
    guRotateRPY(&n_matrix, 100, -10, 45);
    guMtxCatL(&n_matrix, &helper, &n_matrix);
    guTranslate(&helper, 0, 0, 50);
    guMtxCatL(&n_matrix, &helper, &n_matrix);
    
    // Initialize the N's angle
    angle = 0.0;

    // Show the starting text
    text_setalign(ALIGN_CENTER);
    text_create("Press START to begin the presentation", SCREEN_WD_HD/2, SCREEN_HT_HD/2);
}


/*==============================
    slide00_update
    Update slide logic every
    frame.
==============================*/

void slide00_update()
{
    // Increment the slide state with the controller
    if (contdata[0].trigger & START_BUTTON)
    {
        switch(slidestate)
        {
            case 0: // Write out the presentation title
                text_cleanup();
                text_setpos(0, -256);
                text_setfont(&font_title);
                text_create("Reflective Regret", SCREEN_WD_HD/2, 64);
                text_setfont(&font_default);
                text_create("Adventures in Nintendo 64 Homebrew Development", SCREEN_WD_HD/2, 64+32);
                slidestate++; 
                break;
            case 1: // Slide the text away
                slidestate++;
                break;
        }
    }
    
    // Slide the text in
    if (slidestate == 1)
        if (text_gety() < 0)
            text_setpos(text_getx(), lerp(text_gety(), 0, 0.05));
           
    // Slide the text out
    if (slidestate == 2)
        if (text_gety() > -140)
            text_setpos(text_getx(), lerp(text_gety(), -160, 0.05));
        else
        {
            slide_change(global_slide+1);
            return;
        }
        
    // Make the N do stuff
    #if (TV_TYPE == NTSC)
        angle += 1.5;
    #else
        angle += 1.8;
    #endif
    guRotateRPY(&rotmatrix, 0, angle, 0);
    if (slidestate != 0)
        guTranslate(&transmatrix, 0, text_gety()*20, 0);
    else
        guTranslate(&transmatrix, 0, -10000, 0);
}


/*==============================
    slide00_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide00_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&n_matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&transmatrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&rotmatrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, gfx_mdl_the_n);
}


/*==============================
    slide00_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide00_cleanup()
{
    // Nothing to clean up
}