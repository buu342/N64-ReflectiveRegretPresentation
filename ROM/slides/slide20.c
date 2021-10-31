#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_n64.h"
#include "../assets/mdl_usb.h"

static u8 slidestate;

static Mtx modelmatrix;
static modelHelper* cartmodel;
static modelHelper* usbmodel;

void slide20_init()
{
    Mtx helper;
    slidestate = 0;
    
    // Load the N64 model overlay
    load_overlay(_gfx_n64SegmentStart,
        (u8*)_gfx_n64SegmentRomStart,  (u8*)_gfx_n64SegmentRomEnd, 
        (u8*)_gfx_n64SegmentTextStart, (u8*)_gfx_n64SegmentTextEnd, 
        (u8*)_gfx_n64SegmentDataStart, (u8*)_gfx_n64SegmentDataEnd, 
        (u8*)_gfx_n64SegmentBssStart,  (u8*)_gfx_n64SegmentBssEnd 
    );
    
    // Load the USB model overlay
    load_overlay(_gfx_usbSegmentStart,
        (u8*)_gfx_usbSegmentRomStart,  (u8*)_gfx_usbSegmentRomEnd, 
        (u8*)_gfx_usbSegmentTextStart, (u8*)_gfx_usbSegmentTextEnd, 
        (u8*)_gfx_usbSegmentDataStart, (u8*)_gfx_usbSegmentDataEnd, 
        (u8*)_gfx_usbSegmentBssStart,  (u8*)_gfx_usbSegmentBssEnd 
    );
    
    // Model memory allocation
    cartmodel = (modelHelper*) malloc(sizeof(modelHelper));
    usbmodel = (modelHelper*) malloc(sizeof(modelHelper));
    debug_assert(cartmodel != NULL);
    debug_assert(usbmodel != NULL);
    usbmodel->x = 0;
    usbmodel->y = 0;
    usbmodel->z = 0;
    usbmodel->rotz = 0;
    usbmodel->correctpos = NULL;
    usbmodel->dl = gfx_mdl_usb;
    cartmodel->x = 0;
    cartmodel->y = 0;
    cartmodel->z = 0;
    cartmodel->rotz = 0;
    cartmodel->correctpos = mdl_n64_correctpos_cart;
    cartmodel->dl = gfx_mdl_n64_cart;
    
    // Setup the global model matrix
    guMtxIdent(&cartmodel->matrix);
    guMtxIdent(&usbmodel->matrix);
    guScale(&helper, 0.25, 0.25, 0.25);
    guTranslate(&modelmatrix, 4, 100, -256);
    guMtxCatL(&modelmatrix, &helper, &modelmatrix);

    // Create the text
    text_setalign(ALIGN_CENTER);
    text_setpos(0, -256);
    text_setfont(&font_title);
    text_create("Development Process", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_create("The boring stuff is out of the way, let's get to the fun part!", SCREEN_WD_HD/2, 64+32);
}

void slide20_update()
{
    int i;
    Mtx helper;
    float prevx = usbmodel->x;
    
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
    
    // USB animation (we're using its Y as theta, Z as X rotation, and rotz as its state)
    usbmodel->y += 0.1;
    switch (usbmodel->rotz)
    {
        case 10:
            usbmodel->z = lerp(usbmodel->z, 0, 0.1);
            if (usbmodel->z > -2)
            {
                prevx = 0;
                usbmodel->x = 0;
                usbmodel->z = 0;
                usbmodel->y = 0;
                usbmodel->rotz = 0;
            }
            break;
        case 4:
            usbmodel->z = lerp(usbmodel->z, -180, 0.1);
            if (usbmodel->z < -178)
            {
                prevx = 0;
                usbmodel->x = 0;
                usbmodel->z = -180;
                usbmodel->y = 0;
                usbmodel->rotz = 6;
            }
            break;
        case 9:
        case 7:
        case 3:
        case 1:
        case 8:
        case 6:
        case 2:
        case 0:
            usbmodel->x = -fabs(sinf(usbmodel->y))*50;
            if ((usbmodel->rotz%2 == 0 && prevx < usbmodel->x) || (usbmodel->rotz%2 == 1 && prevx > usbmodel->x))
                usbmodel->rotz++;
            break;
    }
    
    // Setup the global model matrix
    guScale(&helper, 0.25, 0.25, 0.25);
    guTranslate(&modelmatrix, 4, 100, text_gety());
    guMtxCatL(&modelmatrix, &helper, &modelmatrix);
    
    // Setup the models
    guTranslate(&cartmodel->matrix, -cartmodel->correctpos[0]-150, -cartmodel->correctpos[1], -cartmodel->correctpos[2]+350+text_gety()*2.171875);
    guRotateRPY(&usbmodel->matrix, usbmodel->z, 0, 0);
    guTranslate(&helper, 150+usbmodel->x, 0, 300+text_gety()*2.171875);
    guMtxCatL(&usbmodel->matrix, &helper, &usbmodel->matrix);
    
    // Exit the slide when start is pressed
    if (contdata[0].trigger & START_BUTTON)
        slidestate++;
}

void slide20_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&modelmatrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&cartmodel->matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(glistp++, cartmodel->dl);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&usbmodel->matrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(glistp++, usbmodel->dl);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
}

void slide20_cleanup()
{
    free(cartmodel);
    free(usbmodel);
}