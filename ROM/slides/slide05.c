/***************************************************************
                           slide05.c

Chapter 1 - A look into the N64's hardware.
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_n64.h"


/*********************************
              Macros
*********************************/

// Number of different separate bits in the N64 console model
#define NUM_MODELS 8


/*********************************
             Structs
*********************************/

// Model data struct
typedef struct {
    float x;
    float y;
    float z;
    float rotz;
    Gfx* dl;
    Mtx matrix;
    u8 render;
} n64MdlMesh;


/*********************************
             Globals
*********************************/

// Slide state
static int slidestate;

// N64 model data
static n64MdlMesh* n64parts;
static Mtx* n64_matrix;
static int n64Angle;


/*==============================
    slide05_init
    Initializes the slide
==============================*/

void slide05_init()
{
    int i;
    Mtx helper;
    Gfx* models[NUM_MODELS];
    n64Angle = 0;
    slidestate = 0;
    
    // Load the N64 model overlay
    load_overlay(_gfx_n64SegmentStart,
        (u8*)_gfx_n64SegmentRomStart,  (u8*)_gfx_n64SegmentRomEnd, 
        (u8*)_gfx_n64SegmentTextStart, (u8*)_gfx_n64SegmentTextEnd, 
        (u8*)_gfx_n64SegmentDataStart, (u8*)_gfx_n64SegmentDataEnd, 
        (u8*)_gfx_n64SegmentBssStart,  (u8*)_gfx_n64SegmentBssEnd 
    );
    models[0] = gfx_mdl_n64_cart;
    models[1] = gfx_mdl_n64_shelltop;
    models[2] = gfx_mdl_n64_heatsink;
    models[3] = gfx_mdl_n64_shellbot;
    models[4] = gfx_mdl_n64_motherboard;
    models[5] = gfx_mdl_n64_rcp;
    models[6] = gfx_mdl_n64_ram;
    models[7] = gfx_mdl_n64_cpu;
    
    // Setup the models
    n64parts = (n64MdlMesh*) malloc(sizeof(n64MdlMesh)*NUM_MODELS);
    debug_assert(n64parts != NULL);
    for (i=0; i<NUM_MODELS; i++)
    {
        n64parts[i].x = 0;
        n64parts[i].y = 0;
        n64parts[i].z = 0;
        n64parts[i].rotz = 0;
        n64parts[i].dl = models[i];
        n64parts[i].render = TRUE;
        guMtxIdent(&n64parts[i].matrix);
    }
    
    // Setup the main model matrix
    n64_matrix = (Mtx*) malloc(sizeof(Mtx));
    debug_assert(n64_matrix != NULL);
    guTranslate(&helper, 4, 100, 0);
    guScale(n64_matrix, 0.25, 0.25, 0.25);
    guMtxCatL(n64_matrix, &helper, n64_matrix);
    
    // Create the text
    text_setalign(ALIGN_CENTER);
    text_setpos(0, -256);
    text_setfont(&font_title);
    text_create("The Hardware", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_create("The boring, but necessary evil", SCREEN_WD_HD/2, 64+32);
}


/*==============================
    slide05_update
    Update slide logic every
    frame.
==============================*/

void slide05_update()
{
    int i;
    Mtx helper;
    
    // Handle the teardown animation
    switch (slidestate)
    {
        case 0: // Move the console to the center
            if (text_gety() < 0)
            {
                text_setpos(text_getx(), lerp(text_gety(), 0, 0.05));
                guTranslate(&helper, 4, 100, text_gety());
                guScale(n64_matrix, 0.25, 0.25, 0.25);
                guMtxCatL(n64_matrix, &helper, n64_matrix);
            }
            else
                slidestate++;
            break;
        case 1: // Remove the cartridge
            n64parts[0].z = lerp(n64parts[0].z, 200, 0.1);
            guTranslate(&n64parts[0].matrix, 0, 0, n64parts[0].z);
            if (n64parts[0].z > 190)
                slidestate++;
            break;
        case 2: // Move the cartridge aside and remove the top shell
            n64parts[0].x = lerp(n64parts[0].x, 1300, 0.1);
            n64parts[1].z = lerp(n64parts[1].z, 200, 0.1);
            guTranslate(&n64parts[0].matrix, n64parts[0].x, 0, 200);
            guTranslate(&n64parts[1].matrix, 0, 0, n64parts[1].z);
            if (n64parts[0].x > 1250)
            {
                n64parts[0].render = FALSE;
                slidestate++;
            }
            break;
        case 3: // Move the top shell aside and remove the heatsink
            n64parts[1].x = lerp(n64parts[1].x, -1500, 0.1);
            n64parts[2].z = lerp(n64parts[2].z, 200, 0.1);
            guTranslate(&n64parts[1].matrix, n64parts[1].x, 0, 200);
            guTranslate(&n64parts[2].matrix, 0, 0, n64parts[2].z);
            if (n64parts[1].x < -1450)
            {
                n64parts[1].render = FALSE;
                slidestate++;
            }
            break;
        case 4: // Move the heatsink aside
            n64parts[2].x = lerp(n64parts[2].x, 1500, 0.1);
            guTranslate(&n64parts[2].matrix, n64parts[2].x, 0, 200);
            if (n64parts[2].x > 1450)
            {
                n64parts[2].render = FALSE;
                slidestate++;
            }
            break;
        case 5: // Remove the bottom shell
            n64parts[3].z = lerp(n64parts[3].z, -100, 0.1);
            guTranslate(&n64parts[3].matrix, 0, 0, n64parts[3].z);
            if (n64parts[3].z < -95)
                slidestate++;
            break;
        case 6: // Move the bottom shell aside
            n64parts[3].y = lerp(n64parts[3].y, -1000, 0.1);
            guTranslate(&n64parts[3].matrix, 0, n64parts[3].y, -100);
            if (n64parts[3].y < -990)
            {
                n64parts[3].render = FALSE;
                slidestate++;
            }
            break;
        case 11: // Split the CPU from the motherboard
            text_setpos(text_getx(), lerp(text_gety(), -160, 0.05));
            for (i=4; i<7; i++)
            {
                n64parts[i].z = lerp(n64parts[i].z, -100, 0.1);
                guTranslate(&n64parts[i].matrix, 0, 0, n64parts[i].z);
            }
            if (n64parts[6].z < -95)
                slidestate++;
            break;
        case 12: // Move everything aside and put the CPU in the center of the screen
            for (i=4; i<7; i++)
            {
                n64parts[i].y = lerp(n64parts[i].y, 1100, 0.1);
                guTranslate(&n64parts[i].matrix, 0, n64parts[i].y, -100);
            }
            n64parts[7].x = lerp(n64parts[7].x, 123, 0.1);
            n64parts[7].y = lerp(n64parts[7].y, 18, 0.1);
            n64parts[7].z = lerp(n64parts[7].z, 660, 0.1);
            n64parts[7].rotz = lerp(n64parts[7].rotz, -90, 0.1);
            guRotateRPY(&helper, 0, 0, n64parts[7].rotz);
            guTranslate(&n64parts[7].matrix, n64parts[7].x, n64parts[7].y, n64parts[7].z);
            guMtxCatL(&n64parts[7].matrix, &helper, &n64parts[7].matrix);
            
            // Go to the next slide when the animation ends
            if (n64parts[7].rotz < -89.9)
            {
                slide_change(global_slide+1);
                return; // Important! Return to prevent the rest of this code from being executed or we get null pointers!
            }
            break;
    }
    
    // If we removed the heatsink, rotate the console so we can see the top
    if (slidestate > 3 && n64Angle < 90)
    {
        n64Angle++;
        guScale(n64_matrix, 0.25, 0.25, 0.25);
        guRotateRPY(&helper, n64Angle, 0, 0);
        guMtxCatL(n64_matrix, &helper, n64_matrix);
        guTranslate(&helper, 4+n64Angle*0.033, 100-n64Angle*1.33, n64Angle);
        guMtxCatL(n64_matrix, &helper, n64_matrix);
    }

    // Advance the slide state as we press START unless we're doing the CPU animation
    if (contdata[0].trigger & START_BUTTON && slidestate < 11)
    {
        slidestate++;
        switch (slidestate)
        {
            case 8: // Put a label over the CPU
                text_setalign(ALIGN_LEFT);
                text_setfont(&font_default);
                text_setcolor(255, 0, 0, 255);
                text_create(BOLD"CPU", 227, 277);
                break;
            case 9: // Put a label over the RAM
                text_create(BOLD"RAM", 298, 307);
                text_create(BOLD"RAM", 298, 332);
                break;
            case 10: // Put a label over the RCP
                text_create(BOLD"RCP", 303, 263);
                break;
            case 11: // Remove the labels and redraw the title
                text_cleanup();
                text_reset();
                text_setalign(ALIGN_CENTER);
                text_setpos(0, 0);
                text_setfont(&font_title);
                text_create("The Hardware", SCREEN_WD_HD/2, 64);
                text_setfont(&font_default);
                text_create("The boring, but necessary evil", SCREEN_WD_HD/2, 64+32);
                break;
        }
    }
}


/*==============================
    slide05_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide05_draw()
{
    int i;
    // Load the initial model matrix
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(n64_matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    
    // Push each models' matrix and draw each bit
    for (i=0; i<NUM_MODELS; i++)
    {
        if (n64parts[i].render)
        {
            gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&n64parts[i].matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH)
            gSPDisplayList(glistp++, n64parts[i].dl);
            gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
        }
    }
}


/*==============================
    slide05_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide05_cleanup()
{
    free(n64_matrix);
    free(n64parts);
}