/***************************************************************
                           slide27.c

An explanation of the Color Combiner
***************************************************************/

#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"


/*********************************
              Macros
*********************************/

// Custom Color Combiner modes
#define SHOWMODE1 0,0,0,0, 0,0,0,0
#define SHOWMODE2 0,0,0,1, 0,0,0,0
#define SHOWMODE3 0,0,0,SHADE, 0,0,0,0
#define SHOWMODE4 0,0,0,TEXEL0, 0,0,0,0
#define SHOWMODE5 SHADE,0,TEXEL0,0, 0,0,0,0
#define SHOWMODE6 NOISE,0,SHADE,TEXEL0, 0,0,0,0
#define SHOWMODE7 0,0,0,COMBINED, 0,0,0,0
#define SHOWMODE8 COMBINED,0,ENVIRONMENT,0, 0,0,0,0


/*********************************
             Globals
*********************************/

// The slide's state
static u8 slidestate;

// A pointer to store our texture
static u8* tex_inercia __attribute__ ((aligned (64)));

// Color Combiner settings
static u8 selectedmode;
static float env;
static char modes1[][4][32] = {
    {"0","0","0","0"},
    {"0","0","0","1"},
    {"0","0","0","VERTEX"},
    {"0","0","0","TEXTURE"},
    {"VERTEX","0","TEXTURE","0"},
    {"NOISE","0","VERTEX","TEXTURE"},
    {"NOISE","0","VERTEX","TEXTURE"},
};
static char modes2[][4][32] = {
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"COMBINED","0","AMBIENT","0"},
};

// Collection of vertices that form a square
static Vtx vtx_square[] = {
    {-50, 0, 0, 0, 0, 1024, 255, 0, 0, 255},   /* 0 */
    {50, 0, 0, 0, 1024, 1024, 0, 0, 255, 255}, /* 1 */
    {50, 0, 100, 0, 1024, 0, 0, 0, 0, 255},    /* 2 */
    {-50, 0, 100, 0, 0, 0, 0, 255, 0, 255},    /* 3 */
};



/*==============================
    rerender_menu
    Recreates all the text in
    the Color Combiner 
    demonstration
==============================*/

void rerender_menu()
{
    int x = 0, y = 0, i;
    
    // If we're showing a 2 cycle mode, move the first block of text to the left
    if (selectedmode == 6)
        x = -64;
    env = 0;
    
    // Draw the CC formula
    text_setalign(ALIGN_CENTER);
    text_create("(a - b) x c + d", SCREEN_WD_HD/2, 64+(y++)*32);
    
    // Draw the first cycle
    text_setalign(ALIGN_LEFT);
    text_create("a = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("b = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("c = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("d = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    y -= 4;
    for (i=0; i<4; i++)
        text_create(modes1[selectedmode][i], SCREEN_WD_HD/2-64+32+x, 64+(y++)*32);
    
    // Draw the second cycle
    if (selectedmode == 6)
    {
        y = 1;
        x = 128;
        text_create("a = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("b = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("c = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("d = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        y -= 4;
        for (i=0; i<4; i++)
            text_create(modes2[selectedmode][i], SCREEN_WD_HD/2-64+32+x, 64+(y++)*32);
    }
}


/*==============================
    slide27_init
    Initializes the slide
==============================*/

void slide27_init()
{
    int i;
    int texty = 0;
    selectedmode = 0;
    slidestate = 0;
    
    // Create the slide's title text
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Color + Alpha Combiner", SCREEN_WD_HD/2, 64);
    
    // Create the text for the slide's body
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Closest thing to a fragment shader available", 64, 122+32*(texty++));
    text_create(BULLET1"Very simple equation:", 64, 122+32*(texty++));
    text_setalign(ALIGN_CENTER);
    text_create("(a - b) x c + d", SCREEN_WD_HD/2, 122+32*(texty++));
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Can be done in two passes", 64, 122+32*(texty++));
    
    // Grab the Inercia logo texture from ROM
    tex_inercia = (u8*)memalign(64, _tex_inerciaSegmentRomEnd-_tex_inerciaSegmentRomStart);
    debug_assert(tex_inercia != NULL);
    nuPiReadRom((u32)_tex_inerciaSegmentRomStart, tex_inercia, _tex_inerciaSegmentRomEnd-_tex_inerciaSegmentRomStart);
}


/*==============================
    slide27_update
    Update slide logic every
    frame.
==============================*/

void slide27_update()
{
    // Advance the slide state when we press START
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                rerender_menu();
                break;
            case 2:
                slide_change(global_slide+1);
                break;
        }
    }
    
    // If we're in the color combiner mode
    if (slidestate == 1)
    {
        // Go to the next CC mode if we press Up on the D-Pad
        if (contdata[0].trigger & U_JPAD && selectedmode != 6)
        {
            selectedmode++;
            text_cleanup();
            rerender_menu();
        }
        
        // Go to the previous CC mode if we press Up on the D-Pad
        if (contdata[0].trigger & D_JPAD && selectedmode != 0)
        {
            selectedmode--;
            text_cleanup();
            rerender_menu();
        }
        
        // Increment the environment color theta
        env += 0.03;
    }
}


/*==============================
    slide27_draw
    Draws extra stuff regarding
    this slide
==============================*/

void slide27_draw()
{
    // Draw the square with the different Color Combiner modes
    if (slidestate == 1)
    {
        gDPSetCycleType(glistp++, G_CYC_2CYCLE);
        gDPSetRenderMode(glistp++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
        gDPSetEnvColor(glistp++, abs(255*sinf(env)), abs(255*sinf(env)), abs(255*sinf(env)), 255);
        switch (selectedmode)
        {
            case 0: gDPSetCombineMode(glistp++, SHOWMODE1, SHOWMODE7); break;
            case 1: gDPSetCombineMode(glistp++, SHOWMODE2, SHOWMODE7); break;
            case 2: gDPSetCombineMode(glistp++, SHOWMODE3, SHOWMODE7); break;
            case 3: gDPSetCombineMode(glistp++, SHOWMODE4, SHOWMODE7); break;
            case 4: gDPSetCombineMode(glistp++, SHOWMODE5, SHOWMODE7); break;
            case 5: gDPSetCombineMode(glistp++, SHOWMODE6, SHOWMODE7); break;
            case 6: gDPSetCombineMode(glistp++, SHOWMODE6, SHOWMODE8); break;
        }
        gDPSetTextureFilter(glistp++, G_TF_BILERP);
        gSPClearGeometryMode(glistp++, G_LIGHTING);
        gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPLoadTextureBlock(glistp++, tex_inercia, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPVertex(glistp++, vtx_square+0, 4, 0);
        gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
    }
}


/*==============================
    slide27_cleanup
    Cleans up dynamic memory 
    allocated during this slide
==============================*/

void slide27_cleanup()
{
    free(tex_inercia);
}