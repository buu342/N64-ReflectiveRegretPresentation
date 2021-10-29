#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"

u16* spr_takeda;
u8*  spr_hansei;

void slide02_init()
{
    spr_takeda = (u16*)malloc(_spr_takedaSegmentRomEnd-_spr_takedaSegmentRomStart);
    spr_hansei = (u8*)malloc(_spr_hanseiSegmentRomEnd-_spr_hanseiSegmentRomStart);
    debug_assert(spr_takeda != NULL);
    debug_assert(spr_hansei != NULL);
    nuPiReadRom((u32)_spr_takedaSegmentRomStart, spr_takeda, _spr_takedaSegmentRomEnd-_spr_takedaSegmentRomStart);
    nuPiReadRom((u32)_spr_hanseiSegmentRomStart, spr_hansei, _spr_hanseiSegmentRomEnd-_spr_hanseiSegmentRomStart);
    
    // Put the image source
    text_setalign(ALIGN_CENTER);
    text_setfont(&font_small);
    text_setcolor(44, 44, 255, 255);
    text_create("https://nintendowire.com/news/2017/04/27/genyo-takeda-announces-retirement-nintendo/", SCREEN_WD_HD/2, SCREEN_HT_HD/2+148);
}

void slide02_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide02_draw()
{
    int i;
    
    // Draw Hansei
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPLoadTextureBlock_4b(glistp++, spr_hansei, G_IM_FMT_I, 128, 64, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, 
        (SCREEN_WD_HD/2-64) << 2, (64) << 2, 
        (SCREEN_WD_HD/2+64) << 2, (64+64) << 2, 
        G_TX_RENDERTILE, 
        0 << 5, 0 << 5, 
        1 << 10, 1 << 10
    );
    
    // Draw Genyo Takeda
    for (i=0; i<208; i+=8)
    {
        gDPLoadTextureBlock(glistp++, spr_takeda+i*256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 8, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++, 
            (SCREEN_WD_HD/2-128) << 2, (SCREEN_HT_HD/2 - 64+i) << 2, 
            (SCREEN_WD_HD/2+128) << 2, (SCREEN_HT_HD/2 - 64+i+8) << 2, 
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }
}

void slide02_cleanup()
{
    free(spr_takeda);
    free(spr_hansei);
}