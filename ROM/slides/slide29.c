#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../sausage64.h"
#include "../assets/segments.h"
#include "../assets/mdl_catherine.h"
#include "../assets/mdl_skinned.h"
#include "../assets/mdl_hack.h"

static void catherine_predraw(u16 part);

static u8 slidestate;
static Mtx* modelmatrix;
static s64ModelHelper* catherine;
static Vtx* frames[5];
static Vtx* skinnedmodelcopy;
static u32 frametime;
static u8 animtime;

static void makeslide29text()
{
    int texty = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Model Animation", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Sausage links", 64, 122+32*(texty++));
    text_create(BULLET1"Entire models of animation frames", 64, 122+32*(texty++));
    text_create(BULLET2"Hybrid", 64, 122+32*(texty++));
    text_create(BULLET2"Skeleton system", 64, 122+32*(texty++));
    text_create(BULLET1"Vertex cache hack", 64, 122+32*(texty++));
    
    // Initialize catherine
    load_overlay(_gfx_catherineSegmentStart,
        (u8*)_gfx_catherineSegmentRomStart,  (u8*)_gfx_catherineSegmentRomEnd, 
        (u8*)_gfx_catherineSegmentTextStart, (u8*)_gfx_catherineSegmentTextEnd, 
        (u8*)_gfx_catherineSegmentDataStart, (u8*)_gfx_catherineSegmentDataEnd, 
        (u8*)_gfx_catherineSegmentBssStart,  (u8*)_gfx_catherineSegmentBssEnd 
    );
    modelmatrix = (Mtx*)malloc(sizeof(Mtx));
    catherine = (s64ModelHelper*)malloc(sizeof(s64ModelHelper));
    debug_assert(modelmatrix != NULL);
    debug_assert(catherine != NULL);
    catherine->matrix = (Mtx*)malloc(sizeof(Mtx)*MESHCOUNT_Catherine);
    debug_assert(catherine->matrix != NULL);
    sausage64_initmodel(catherine, MODEL_Catherine, catherine->matrix);
    sausage64_set_predrawfunc(catherine, catherine_predraw);
    
    // Initialize skinned model
    load_overlay(_gfx_skinnedSegmentStart,
        (u8*)_gfx_skinnedSegmentRomStart,  (u8*)_gfx_skinnedSegmentRomEnd, 
        (u8*)_gfx_skinnedSegmentTextStart, (u8*)_gfx_skinnedSegmentTextEnd, 
        (u8*)_gfx_skinnedSegmentDataStart, (u8*)_gfx_skinnedSegmentDataEnd, 
        (u8*)_gfx_skinnedSegmentBssStart,  (u8*)_gfx_skinnedSegmentBssEnd 
    );
    frames[0] = vtx_skinned_frame00;
    frames[1] = vtx_skinned_frame10;
    frames[2] = vtx_skinned_frame00;
    frames[3] = vtx_skinned_frame30;
    frames[4] = vtx_skinned_frame00;
    skinnedmodelcopy = (Vtx*)malloc(sizeof(Vtx)*12);
    
    // Initialize vertex cache hack model
    load_overlay(_gfx_hackSegmentStart,
        (u8*)_gfx_hackSegmentRomStart,  (u8*)_gfx_hackSegmentRomEnd, 
        (u8*)_gfx_hackSegmentTextStart, (u8*)_gfx_hackSegmentTextEnd, 
        (u8*)_gfx_hackSegmentDataStart, (u8*)_gfx_hackSegmentDataEnd, 
        (u8*)_gfx_hackSegmentBssStart,  (u8*)_gfx_hackSegmentBssEnd 
    );
}

void slide29_init()
{
    slidestate = 0;
    makeslide29text();
}

void slide29_update()
{
    Mtx helper;
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                sausage64_set_anim(catherine, ANIMATION_Catherine_Broken);
                guTranslate(modelmatrix, 0, 40, -20);
                break;
            case 2:
                makeslide29text();
                break;
            case 3:
                frametime = 0;
                guScale(&helper, 0.4, 0.4, 0.4);
                guRotateRPY(modelmatrix, 0, 0, 90);
                guMtxCatL(modelmatrix, &helper, modelmatrix);
                guTranslate(&helper, 0, 300, 0);
                guMtxCatL(modelmatrix, &helper, modelmatrix);
                text_cleanup();
                break;
            case 4:
                break;
            case 5:
                makeslide29text();
                break;
            case 6:
                text_cleanup();
                break;
            case 9:
                slide_change(global_slide+1);
                break;
        }
    }
    
    if (slidestate == 1 && catherine->animtick < 29)
        sausage64_advance_anim(catherine);
        
    if (slidestate == 3 || slidestate == 4)
    {
        frametime = (frametime+1)%40;
        switch(frametime)
        {
            case 0: animtime = 0; break;
            case 10: animtime = 1; break;
            case 20: animtime = 2; break;
            case 30: animtime = 3; break;
            case 40: animtime = 4; break;
        }
        memcpy(skinnedmodelcopy, frames[animtime], 12*sizeof(Vtx));
        if (slidestate == 4)
        {
            int i;
            for (i=0; i<12; i++)
            {
                skinnedmodelcopy[i].v.ob[0] = lerp(skinnedmodelcopy[i].v.ob[0], frames[(animtime+1)%5][i].v.ob[0], (((float)(frametime%10))/10));
                skinnedmodelcopy[i].v.ob[1] = lerp(skinnedmodelcopy[i].v.ob[1], frames[(animtime+1)%5][i].v.ob[1], (((float)(frametime%10))/10));
                skinnedmodelcopy[i].v.ob[2] = lerp(skinnedmodelcopy[i].v.ob[2], frames[(animtime+1)%5][i].v.ob[2], (((float)(frametime%10))/10));
            }
        }        
    }
}

void slide29_draw()
{
    if (slidestate == 1)
    {
        gSPMatrix(glistp++, modelmatrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        sausage64_drawmodel(&glistp, catherine);
    }

    if (slidestate == 3 || slidestate == 4)
    {
        #define G_CC_PRIMLITE SHADE,0,PRIMITIVE,0,0,0,0,PRIMITIVE
        gSPMatrix(glistp++, modelmatrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPVertex(glistp++, skinnedmodelcopy, 12, 0);
        gDPSetCycleType(glistp++, G_CYC_1CYCLE);
        gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gDPSetCombineMode(glistp++, G_CC_PRIMLITE, G_CC_PRIMLITE);
        gDPSetTextureFilter(glistp++, G_TF_BILERP);
        gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
        gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH | G_LIGHTING);
        gDPSetPrimColor(glistp++, 0, 0, 0, 255, 255, 255);
        gDPPipeSync(glistp++);
        gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
        gSP2Triangles(glistp++, 4, 5, 6, 0, 4, 6, 7, 0);
        gSP2Triangles(glistp++, 8, 4, 7, 0, 8, 7, 9, 0);
        gSP2Triangles(glistp++, 9, 7, 6, 0, 9, 6, 10, 0);
        gSP2Triangles(glistp++, 10, 6, 5, 0, 10, 5, 11, 0);
        gSP2Triangles(glistp++, 8, 0, 3, 0, 8, 3, 11, 0);
        gSP2Triangles(glistp++, 4, 8, 11, 0, 4, 11, 5, 0);
        gSP2Triangles(glistp++, 2, 10, 11, 0, 2, 11, 3, 0);
        gSP2Triangles(glistp++, 1, 9, 10, 0, 1, 10, 2, 0);
        gSP2Triangles(glistp++, 0, 8, 9, 0, 0, 9, 1, 0);
    }
    
    if (slidestate > 5)
    {
        gSPClearGeometryMode(glistp++, G_LIGHTING);
        gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);
        gDPPipeSync(glistp++);
        switch(slidestate)
        {
            case 8:
                gSPDisplayList(glistp++, gfx_hack_red);
            case 7:
                gSPDisplayList(glistp++, gfx_hack_green);
            case 6:
                gSPDisplayList(glistp++, gfx_hack_blue);
                break;
        }
    }
}

void slide29_cleanup()
{
    if (catherine != NULL)
    {
        free(catherine->matrix);
        free(catherine);
        catherine = NULL;
    }
    free(skinnedmodelcopy);
    free(modelmatrix);
}



static void catherine_predraw(u16 part)
{
    // Handle face drawing
    switch (part)
    {
        case MESH_Catherine_Head:
            gDPLoadTextureBlock(glistp++, catherine_faces[FACE_Catherine_gasp].faces[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_MIRROR, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
}