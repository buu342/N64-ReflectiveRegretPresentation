#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"

u16* spr_hardwaremap;

void slide11_init()
{
    spr_hardwaremap = (u16*)malloc(_spr_hardwaremapSegmentRomEnd-_spr_hardwaremapSegmentRomStart);
    debug_assert(spr_hardwaremap != NULL);
    nuPiReadRom((u32)_spr_hardwaremapSegmentRomStart, spr_hardwaremap, _spr_hardwaremapSegmentRomEnd-_spr_hardwaremapSegmentRomStart);

    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("How it's organized, and why you", SCREEN_WD_HD/2, 48);
    text_create("should care", SCREEN_WD_HD/2, 48+32);
}

void slide11_update()
{
    if (contdata[0].trigger & START_BUTTON)
        slide_change(global_slide+1);
}

void slide11_draw()
{
    int i;
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureFilter(glistp++, G_TF_BILERP);
    for (i=0; i<320; i+=4)
    {
        gDPLoadTextureBlock(glistp++, spr_hardwaremap+i*512, G_IM_FMT_RGBA, G_IM_SIZ_16b, 512, 4, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPTextureRectangle(glistp++, 
            (SCREEN_WD_HD/2-256) << 2, (SCREEN_HT_HD/2 - 100+i) << 2, 
            (SCREEN_WD_HD/2+256) << 2, (SCREEN_HT_HD/2 - 100+i+4) << 2, 
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }
}

void slide11_cleanup()
{
    free(spr_hardwaremap);
}