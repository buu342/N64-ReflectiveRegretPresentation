#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_the_n.h"

static modelHelper* the_n;
static u8 slidestate;

extern NUDebTaskPerf* nuDebTaskPerfPtr;

void slide23_init()
{
    int texty = 0;
    slidestate = 0;
    the_n = NULL;
    
    // Initialize the N
    load_overlay(_gfx_the_nSegmentStart,
        (u8*)_gfx_the_nSegmentRomStart,  (u8*)_gfx_the_nSegmentRomEnd, 
        (u8*)_gfx_the_nSegmentTextStart, (u8*)_gfx_the_nSegmentTextEnd, 
        (u8*)_gfx_the_nSegmentDataStart, (u8*)_gfx_the_nSegmentDataEnd, 
        (u8*)_gfx_the_nSegmentBssStart,  (u8*)_gfx_the_nSegmentBssEnd 
    );
    
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Framebuffer", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"No VRAM, Framebuffer and whatnot must be", 64, 122+30*(texty++));
    text_create("stored in RAM.", 64+BULLET1SIZE, 122+30*(texty++));
    text_create(BULLET1"Different sizes and framerates based on region", 64, 122+30*(texty++));
    text_create("(PAL vs NTSC)", 64+BULLET1SIZE, 122+30*(texty++));
    text_create(BULLET2"320x240 vs 320x288", 64, 122+30*(texty++));
    text_create(BULLET2"640x480 vs 640x576", 64, 122+30*(texty++));
    text_create(BULLET1"16-Bit or 32-Bit", 64, 122+30*(texty++));
    text_create(BULLET2"Gets outputted as 24-Bit color, so probably not", 64, 122+30*(texty++));
    text_create("worth the memory penalty going 32-Bit", 64+BULLET2SIZE, 122+30*(texty++));
    text_create(BULLET1"Position in RAM is important!!!", 64, 122+30*(texty++));
}

void slide23_update()
{
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                init_lowres();
                the_n = (modelHelper*) malloc(sizeof(modelHelper));
                debug_assert(the_n != NULL);
                the_n->dl = gfx_mdl_the_n;
                the_n->rotz = 0;
                break;
            case 2:
                init_lowresbad();
                break;
            case 3:
                slide_change(global_slide+1);
                return;
        }
    }
    
    // Setup the N's matrix
    if (the_n != NULL)
    {
        Mtx helper;
        the_n->rotz = (the_n->rotz+1)%360;
        guScale(&helper, 0.075, 0.075, 0.075);
        guRotateRPY(&the_n->matrix, 0, the_n->rotz, 0);
        guMtxCatL(&the_n->matrix, &helper, &the_n->matrix);
        guRotateRPY(&helper, 100, -10, 45);
        guMtxCatL(&the_n->matrix, &helper, &the_n->matrix);
        guTranslate(&helper, 0, 50, 80);
        guMtxCatL(&the_n->matrix, &helper, &the_n->matrix);
    }
}

void slide23_draw()
{
    if (the_n != NULL)
    {
        int i;
        s64 StartTime = nuDebTaskPerfPtr->gfxTaskTime[0].rspStart;
        s64 EndTime =  nuDebTaskPerfPtr->gfxTaskTime[0].rdpEnd;
        gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&the_n->matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        for (i=0; i<20; i++)
            gSPDisplayList(glistp++, the_n->dl);
        text_rendernumber((EndTime - StartTime)/1000, 64, 64);
    }
}

void slide23_cleanup()
{
    init_highres();
    if (the_n != NULL)
        free(the_n);
}