#include <nusys.h>
#include "../config.h"
#include "../helper.h"
#include "../slides.h"
#include "../text.h"
#include "../sausage64.h"
#include "../debug.h"
#include "../assets/segments.h"
#include "../assets/mdl_catherine.h"


typedef struct {
    float x;
    float y;
    float z;
    float rot;
    float speed;
    int state;
    int faceindex;
    int facetick;
    OSTime facetime;
    FaceAnim* face;
    Mtx* worldmtx;
    Mtx* meshesmtx;
    s64ModelHelper* mdl;
} catherineObj;

typedef struct {
    int x;
    int y;
    int state;
    OSTime frametime;
    u16* sprite;
} pyoroObj;


static u8 slidestate;
static void catherine_predraw(u16 part);


catherineObj* catherine;
pyoroObj*     pyoro;
u16* spr_pyoro_walk1;
u16* spr_pyoro_walk2;


void slide01_init()
{
    // Initialize catherine
    load_overlay(_gfx_catherineSegmentStart,
        (u8*)_gfx_catherineSegmentRomStart,  (u8*)_gfx_catherineSegmentRomEnd, 
        (u8*)_gfx_catherineSegmentTextStart, (u8*)_gfx_catherineSegmentTextEnd, 
        (u8*)_gfx_catherineSegmentDataStart, (u8*)_gfx_catherineSegmentDataEnd, 
        (u8*)_gfx_catherineSegmentBssStart,  (u8*)_gfx_catherineSegmentBssEnd 
    );
    catherine = (catherineObj*)malloc(sizeof(catherineObj));
    debug_assert(catherine != NULL);
    catherine->worldmtx = (Mtx*)malloc(sizeof(Mtx));
    catherine->meshesmtx = (Mtx*)malloc(sizeof(Mtx)*MESHCOUNT_Catherine);
    catherine->mdl = (s64ModelHelper*)malloc(sizeof(s64ModelHelper));
    debug_assert(catherine->worldmtx != NULL);
    debug_assert(catherine->meshesmtx != NULL);
    debug_assert(catherine->mdl != NULL);
    sausage64_initmodel(catherine->mdl, MODEL_Catherine, catherine->meshesmtx);
    sausage64_set_predrawfunc(catherine->mdl, catherine_predraw);
    sausage64_set_anim(catherine->mdl, ANIMATION_Catherine_Run);
    catherine->x = 600;
    catherine->y = 400;
    catherine->z = -100;
    catherine->rot = -90;
    catherine->speed = -7;
    catherine->state = -1;
    catherine->face = &catherine_faces[FACE_Catherine_neutral];
    catherine->facetick = 60;
    catherine->faceindex = 0;
    catherine->facetime = osGetTime() + OS_USEC_TO_CYCLES(22222);
    guMtxIdent(catherine->worldmtx);
    guTranslate(catherine->worldmtx, catherine->x, catherine->y, catherine->z);
    
    // Initialize Pyoro
    pyoro = (pyoroObj*)malloc(sizeof(pyoroObj));
    spr_pyoro_walk1 = (u16*)malloc(_spr_pyoro_walk1SegmentRomEnd-_spr_pyoro_walk1SegmentRomStart);
    spr_pyoro_walk2 = (u16*)malloc(_spr_pyoro_walk2SegmentRomEnd-_spr_pyoro_walk2SegmentRomStart);
    debug_assert(pyoro != NULL);
    debug_assert(spr_pyoro_walk1 != NULL);
    debug_assert(spr_pyoro_walk2 != NULL);
    nuPiReadRom((u32)_spr_pyoro_walk1SegmentRomStart, spr_pyoro_walk1, _spr_pyoro_walk1SegmentRomEnd-_spr_pyoro_walk1SegmentRomStart);
    nuPiReadRom((u32)_spr_pyoro_walk2SegmentRomStart, spr_pyoro_walk2, _spr_pyoro_walk2SegmentRomEnd-_spr_pyoro_walk2SegmentRomStart);
    pyoro->sprite = spr_pyoro_walk1;
    pyoro->x = SCREEN_WD_HD+32;
    pyoro->y = 350;
    pyoro->state = -1;
    pyoro->frametime = osGetTime() + OS_USEC_TO_CYCLES(22222);
    
    // Print text on the slide
    slidestate = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Who are you, and why should I care?", SCREEN_WD_HD/2, 64);
}

void slide01_update()
{
    Mtx helper;
    
    // Advance catherine's animation
    if (catherine->state != -1)
    {
        sausage64_advance_anim(catherine->mdl);
        switch (catherine->state)
        {
            case 0:
                if (catherine->mdl->animtick == 28)
                {
                    catherine->state++;
                    catherine->face = &catherine_faces[FACE_Catherine_gasp];
                }
                break;
            case 1:
                catherine->speed = lerp(catherine->speed, 0, 0.03);
                if (catherine->mdl->animtick == 30)
                    catherine->state++;
            case 2:
                catherine->rot = MIN(catherine->rot+3, 0);
                catherine->speed = lerp(catherine->speed, 0, 0.03);
                if (catherine->mdl->animtick == 45)
                    catherine->face = &catherine_faces[FACE_Catherine_neutral];
                if (catherine->mdl->animtick == 59)
                {
                    sausage64_set_anim(catherine->mdl, ANIMATION_Catherine_Idle);
                    catherine->rot = 0;
                    catherine->state++;
                    catherine->speed = 0;
                    catherine->face = &catherine_faces[FACE_Catherine_default];
                }
                break;
        }
        catherine->x += catherine->speed;
        
        // Catherine face blinking
        if (catherine->facetime < osGetTime())
        {
            catherine->facetick--;
            catherine->facetime = osGetTime() + OS_USEC_TO_CYCLES(22222);
            if (catherine->face->hasblink)
            {
                switch (catherine->facetick)
                {
                    case 3:
                    case 1:
                        catherine->faceindex = 1;
                        break;
                    case 2:
                        catherine->faceindex = 2;
                        break;
                    case 0:
                        catherine->faceindex = 0;
                        catherine->facetick = 60 + guRandom()%80;
                        break;
                }
            }
        }
    
        // Create Catherine's world matrix
        guMtxIdent(&helper);
        guMtxIdent(catherine->worldmtx);
        guRotateRPY(catherine->worldmtx, 0, 0, catherine->rot);
        guTranslate(&helper, catherine->x, catherine->y, catherine->z);
        guMtxCatL(catherine->worldmtx, &helper, catherine->worldmtx);
    }
    
    // Advance Pyoro's animation
    if (pyoro->state != -1)
    {
        switch (pyoro->state)
        {
            case 0:
                pyoro->x -= 5;
                if (pyoro->x < 400)
                {
                    pyoro->state++;
                    pyoro->sprite = spr_pyoro_walk1;
                }
                break;
        }
        
        // Pyoro walking animation
        if (pyoro->state == 0 && pyoro->frametime < osGetTime())
        {
            pyoro->frametime = osGetTime() + OS_USEC_TO_CYCLES(22222);
            pyoro->sprite = (pyoro->sprite == spr_pyoro_walk1) ? spr_pyoro_walk2 : spr_pyoro_walk1;
        }
    }
    
    // Handle pressing start
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1: 
                text_setfont(&font_default);
                text_setalign(ALIGN_CENTER);
                text_create("Buu342", SCREEN_WD_HD/2, SCREEN_HT_HD/2);
                pyoro->state = 0;
                break;
            case 2: catherine->state = 0; break;
            case 3: slide_change(global_slide+1); break;
        }
    }
}

void slide01_draw()
{
    // Draw catherine
    if (catherine->state != -1)
    {
        gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(catherine->worldmtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        sausage64_drawmodel(&glistp, catherine->mdl);
    }
    
    // Draw Pyoro
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPLoadTextureBlock(glistp++, pyoro->sprite, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, 2, 2);
    gDPPipeSync(glistp++);
    gSPScisTextureRectangle(glistp++, 
        pyoro->x << 2, pyoro->y << 2, 
        (pyoro->x+64) << 2, (pyoro->y+64) << 2, 
        G_TX_RENDERTILE, 
        0 << 5, 0 << 5, 
        1 << 10, 1 << 10
    );
}

void slide01_cleanup()
{
    free(catherine->mdl);
    free(catherine->worldmtx);
    free(catherine->meshesmtx);
    free(catherine);
    free(spr_pyoro_walk2);
    free(spr_pyoro_walk1);
    free(pyoro);
}

static void catherine_predraw(u16 part)
{
    // Handle face drawing
    switch (part)
    {
        case MESH_Catherine_Head:
            gDPLoadTextureBlock(glistp++, catherine->face->faces[catherine->faceindex], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
}