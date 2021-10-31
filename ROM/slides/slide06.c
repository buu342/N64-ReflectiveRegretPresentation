#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_n64.h"

static u8 texty;
static OSTime timer;
static int slidestate;
static modelHelper* model;

void slide06_init()
{   
    Mtx helper;
    slidestate = 0;
    timer = osGetTime() + OS_USEC_TO_CYCLES(500000);
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
    model->dl = gfx_mdl_n64_cpu;
    model->x = 0;
    model->y = -200;
    model->z = 100;
    model->rotz = 0;
    model->correctpos = mdl_n64_correctpos_cpu;

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
    text_create("The CPU", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
}

void slide06_update()
{
    Mtx helper;

    if (slidestate < 10)
    {
        model->x = lerp(model->x, 40, 0.1);
        model->y = lerp(model->y, -130, 0.1);
        model->z = lerp(model->z, 125, 0.1);
    }

    // Create the bullet points
    if (slidestate < 9 && timer < osGetTime())
    {
        timer = osGetTime() + OS_USEC_TO_CYCLES(50000);
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_create(BULLET1"NEC VR4300 (MIPS R4300i)", 64, 122+32*(texty++));
                break;
            case 2:
                text_create(BULLET2"Runs at 93.75 MHz", 64, 122+32*(texty++));
                break;
            case 3:
                text_create(BULLET2"16 KB instruction cache", 64, 122+32*(texty++));
                break;
            case 4:
                text_create(BULLET2"Pretty good at floating point arithmetic. Actually", 64, 122+32*(texty++));
                break;
            case 5:
                text_create("faster than fixed point!", 64+BULLET2SIZE, 122+32*(texty++));
                break;
            case 6:
                text_create(BULLET2"Can do 64-Bit operations, but the system bus is", 64, 122+32*(texty++));
                break;
            case 7:
                text_create("32-Bits wide so games are designed with 32-Bit", 64+BULLET2SIZE, 122+32*(texty++));
                break;
            case 8:
                text_create("calling conventions to maximize performance.", 64+BULLET2SIZE, 122+32*(texty++));
                break;
            case 9:
                text_create(BULLET2"No blast processing. Sorry!", 64, 122+32*(texty++));
                break;
        }
    }

    // Go to the next slide
    if (slidestate == 9 && contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        text_cleanup();
    }

    // Finish the slide
    if (slidestate == 10)
    {
        model->x = lerp(model->x, 150, 0.1);
        if (model->x > 140)
        {
            slide_change(global_slide+1);
            return;
        }
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
    model->rotz = (model->rotz+1)%360;
}

void slide06_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&model->matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, model->dl);
}

void slide06_cleanup()
{
    free(model);
}