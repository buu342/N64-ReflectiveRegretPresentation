#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../debug.h"
#include "../assets/the_n.h"

static Mtx n_matrix;
static Mtx rotmatrix;
static float angle;

void slide00_init()
{
    Mtx helper;
    
    // Setup the N on the screen
    guMtxIdent(&helper);
    guMtxIdent(&n_matrix);
    guScale(&helper, 0.075, 0.075, 0.075);
    guRotateRPY(&n_matrix, 100, -10, 45);
    guMtxCatL(&n_matrix, &helper, &n_matrix);
    guTranslate(&helper, 0, 0, 50);
    guMtxCatL(&n_matrix, &helper, &n_matrix);
    
    // Initialize the N's angle
    angle = 0.0;
    
    // Write out the presentation title
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Reflective Regret", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_create("Adventures in Nintendo 64 homebrew development", SCREEN_WD_HD/2, 64+32);
}

void slide00_update()
{
    guMtxIdent(&rotmatrix);
    #if (TV_TYPE == NTSC)
        angle += 1.5;
    #else
        angle += 1.8;
    #endif
    guRotateRPY(&rotmatrix, 0, angle, 0);
}

void slide00_draw()
{
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&n_matrix), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&rotmatrix), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, mdl_the_n_gfx);
}

void slide00_cleanup()
{

}