#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_cease.h"

static u8 slidestate;

static Mtx modelmatrix;
static modelHelper* ceasemodel;

void slide32_init()
{
    Mtx helper;
    slidestate = 0;
    
    // Load the N64 model overlay
    load_overlay(_gfx_ceaseSegmentStart,
        (u8*)_gfx_ceaseSegmentRomStart,  (u8*)_gfx_ceaseSegmentRomEnd, 
        (u8*)_gfx_ceaseSegmentTextStart, (u8*)_gfx_ceaseSegmentTextEnd, 
        (u8*)_gfx_ceaseSegmentDataStart, (u8*)_gfx_ceaseSegmentDataEnd, 
        (u8*)_gfx_ceaseSegmentBssStart,  (u8*)_gfx_ceaseSegmentBssEnd 
    );
    
    // Model memory allocation
    ceasemodel = (modelHelper*) malloc(sizeof(modelHelper));
    debug_assert(ceasemodel != NULL);
    ceasemodel->x = 0;
    ceasemodel->y = 0;
    ceasemodel->z = 0;
    ceasemodel->rotz = 0;
    ceasemodel->dl = gfx_mdl_cease;
    
    // Setup the main model matrix
    guTranslate(&helper, 4, 300, -1000);
    guRotateRPY(&ceasemodel->matrix, 10, 10, -45);
    guMtxCatL(&ceasemodel->matrix, &helper, &ceasemodel->matrix);
    guScale(&helper, 0.25, 0.25, 0.25);
    guMtxCatL(&ceasemodel->matrix, &helper, &ceasemodel->matrix);

    // Create the text
    text_setalign(ALIGN_CENTER);
    text_setpos(0, -256);
    text_setfont(&font_title);
    text_create("Homebrew, Demos, and the Future of", SCREEN_WD_HD/2, 64);
    text_create("N64 Development", SCREEN_WD_HD/2, 64+32);
    text_setfont(&font_default);
    text_create("History lesson time!", SCREEN_WD_HD/2, 64+64);
}

void slide32_update()
{
    int i;
    Mtx helper;
    
    // Handle the animation
    switch (slidestate)
    {
        case 0:
            if (text_gety() < 0)
                text_setpos(text_getx(), lerp(text_gety(), 0, 0.05));
            break;
        case 1:
            if (text_gety() > -180)
                text_setpos(text_getx(), lerp(text_gety(), -200, 0.05));
            else
            {
                slide_change(global_slide+1);
                return;
            }
            break;
    }
    
    // Setup the main model matrix
    guTranslate(&helper, 4, 300, 200+text_gety()*4);
    guRotateRPY(&ceasemodel->matrix, 10+13*text_gety()*0.01, 10+13*text_gety()*0.01, -45);
    guMtxCatL(&ceasemodel->matrix, &helper, &ceasemodel->matrix);
    guScale(&helper, 0.25, 0.25, 0.25);
    guMtxCatL(&ceasemodel->matrix, &helper, &ceasemodel->matrix);
    
    // Exit the slide when start is pressed
    if (contdata[0].trigger & START_BUTTON)
        slidestate++;
}

void slide32_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&ceasemodel->matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH)
    gSPDisplayList(glistp++, ceasemodel->dl);
}

void slide32_cleanup()
{
    free(ceasemodel);
}