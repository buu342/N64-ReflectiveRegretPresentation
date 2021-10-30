#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_n64.h"

typedef struct {
    float x;
    float y;
    float z;
    int rotz;
    float* correctpos;
    Gfx* dl;
    Mtx matrix;
} modelHelper;

static u8 texty;
static OSTime timer;
static int slidestate;
static modelHelper* model;

void slide08_init()
{   
    Mtx helper;
    slidestate = 0;
    timer = osGetTime() + OS_USEC_TO_CYCLES(1000000);
    texty = 0;

    // Load the N64 model overlay
    load_overlay(_gfx_n64SegmentStart,
        (u8*)_gfx_n64SegmentRomStart,  (u8*)_gfx_n64SegmentRomEnd, 
        (u8*)_gfx_n64SegmentTextStart, (u8*)_gfx_n64SegmentTextEnd, 
        (u8*)_gfx_n64SegmentDataStart, (u8*)_gfx_n64SegmentDataEnd, 
        (u8*)_gfx_n64SegmentBssStart,  (u8*)_gfx_n64SegmentBssEnd 
    );
    model = (modelHelper*) malloc(sizeof(modelHelper));
    debug_assert(model != NULL);
    model->dl = gfx_mdl_n64_rcp;
    model->x = 0;
    model->y = -200;
    model->z = -100;
    model->rotz = 0;
    model->correctpos = mdl_n64_correctpos_rcp;

    // Initialize the model matrix
    guMtxIdent(&model->matrix);
    guMtxIdent(&helper);
    guTranslate(&model->matrix, -model->correctpos[0], -model->correctpos[1], -model->correctpos[2]);
    guRotateRPY(&helper, -model->rotz, 90, -90);
    guMtxCatL(&model->matrix, &helper, &model->matrix);
    guScale(&helper, 0.25, 0.25, 0.25);
    guMtxCatL(&model->matrix, &helper, &model->matrix);
    guTranslate(&helper, model->x, model->y, model->z);
    guMtxCatL(&model->matrix, &helper, &model->matrix);

    // Create the title
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("The RCP", SCREEN_WD_HD/2, 48);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
}

void slide08_update()
{
    Mtx helper;

    if (slidestate == 0)
    {
        model->z = lerp(model->z, 100, 0.1);
        if (model->z > 98 && timer < osGetTime())
            slidestate++;
    }
    else if (slidestate < 13)
    {
        model->x = lerp(model->x, 40, 0.1);
        model->y = lerp(model->y, -130, 0.1);
        model->z = lerp(model->z, 135, 0.1);
    }

    // Create the bullet points
    if (slidestate < 13 && timer < osGetTime())
    {
        timer = osGetTime() + OS_USEC_TO_CYCLES(50000);
        slidestate++;
        switch (slidestate)
        {
            case 2:
                text_create(BULLET1"Reality Co-Processor", 64, 92+32*(texty++));
                break;
            case 3:
                text_create(BULLET2"???", 64, 92+32*(texty++));
                break;
            case 4:
                text_create(BULLET2"Created by Silicon Graphics", 64, 92+32*(texty++));
                break;
            case 5:
                text_create(BULLET2"Does everything that comes out of your TV, and", 64, 92+32*(texty++));
                break;
            case 6:
                text_create("then some (audio, graphics, I/O, etc...)", 64+BULLET2SIZE, 92+32*(texty++));
                break;
            case 7:
                text_create(BULLET2"Runs parallel to the CPU, at 62.5 MHz", 64, 92+32*(texty++));
                break;
            case 8:
                text_create(BULLET2"Acts like a whiny brat", 64, 92+32*(texty++));
                break;
            case 9:
                text_create(BULLET2"Literally magic. No official documentation.", 64, 92+32*(texty++));
                break;
            case 10:
                text_create(BULLET2"Split into three parts:", 64, 92+32*(texty++));
                break;
            case 11:
                text_create(BULLET3"Reality Display Processor", 64, 92+32*(texty++));
                break;
            case 12:
                text_create(BULLET3"Reality Signal Processor", 64, 92+32*(texty++));
                break;
            case 13:
                text_create(BULLET3"IO Interfaces", 64, 92+32*(texty++));
                break;
        }
    }

    // Go to the next slide
    if (slidestate == 13 && contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        text_cleanup();
    }

    // Finish the slide
    if (slidestate == 14)
    {
        model->x = lerp(model->x, 150, 0.1);
        if (model->x > 140)
            slide_change(global_slide+1);
    }

    // Setup the model matrix
    guMtxIdent(&model->matrix);
    guMtxIdent(&helper);
    guTranslate(&model->matrix, -model->correctpos[0], -model->correctpos[1], -model->correctpos[2]);
    guRotateRPY(&helper, -model->rotz, 90, -90);
    guMtxCatL(&model->matrix, &helper, &model->matrix);
    guScale(&helper, 0.25, 0.25, 0.25);
    guMtxCatL(&model->matrix, &helper, &model->matrix);
    guTranslate(&helper, model->x, model->y, model->z);
    guMtxCatL(&model->matrix, &helper, &model->matrix);
    if (slidestate != 0)
        model->rotz = (model->rotz+1)%360;
}

void slide08_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&model->matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, model->dl);
}

void slide08_cleanup()
{
    //free(model); // Freeing this causes a floating point exception!?
}