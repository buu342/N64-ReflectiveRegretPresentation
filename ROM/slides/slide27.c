#include <nusys.h>
#include "../config.h"
#include "../slides.h"
#include "../text.h"
#include "../helper.h"
#include "../debug.h"
#include "../assets/segments.h"

static u32* tex_inercia __attribute__ ((aligned (32)));
static u8 slidestate;
static u8 selectedmode;
static float env;
static char modes1[][4][32] = {
    {"0","0","0","0"},
    {"0","0","0","1"},
    {"0","0","0","VERTEX"},
    {"0","0","0","TEXEL0"},
    {"VERTEX","0","TEXEL0","0"},
    {"NOISE","0","VERTEX","TEXEL0"},
    {"NOISE","0","VERTEX","TEXEL0"},
};
static char modes2[][4][32] = {
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"0","0","0","0"},
    {"COMBINED","0","AMBIENT","0"},
};

#define SHOWMODE1 0,0,0,0, 0,0,0,0
#define SHOWMODE2 0,0,0,1, 0,0,0,0
#define SHOWMODE3 0,0,0,SHADE, 0,0,0,0
#define SHOWMODE4 0,0,0,TEXEL0, 0,0,0,0
#define SHOWMODE5 SHADE,0,TEXEL0,0, 0,0,0,0
#define SHOWMODE6 NOISE,0,SHADE,TEXEL0, 0,0,0,0
#define SHOWMODE7 0,0,0,COMBINED, 0,0,0,0
#define SHOWMODE8 COMBINED,0,ENVIRONMENT,0, 0,0,0,0

void rerender_menu()
{
    int x = 0, y = 0, i;
    
    if (selectedmode == 6)
        x = -64;
    env = 0;
    text_setalign(ALIGN_CENTER);
    text_create("(a - b) x c + d", SCREEN_WD_HD/2, 64+(y++)*32);
    text_setalign(ALIGN_LEFT);
    text_create("a = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("b = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("c = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    text_create("d = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
    y -= 4;
    for (i=0; i<4; i++)
        text_create(modes1[selectedmode][i], SCREEN_WD_HD/2-64+32+x, 64+(y++)*32);
        
    if (selectedmode == 6)
    {
        y = 1;
        x = 128;
        text_create("a = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("b = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("c = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        text_create("d = ", SCREEN_WD_HD/2-64+x, 64+(y++)*32);
        y -= 4;
        for (i=0; i<4; i++)
            text_create(modes2[selectedmode][i], SCREEN_WD_HD/2-64+32+x, 64+(y++)*32);
    }
}

void slide27_init()
{
    int texty = 0;
    selectedmode = 0;
    slidestate = 0;
    text_setfont(&font_title);
    text_setalign(ALIGN_CENTER);
    text_create("Color + Alpha Combiner", SCREEN_WD_HD/2, 64);
    text_setfont(&font_default);
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Closest thing to a fragment shader available", 64, 122+32*(texty++));
    text_create(BULLET1"Very simple equation:", 64, 122+32*(texty++));
    text_setalign(ALIGN_CENTER);
    text_create("(a - b) x c + d", SCREEN_WD_HD/2, 122+32*(texty++));
    text_setalign(ALIGN_LEFT);
    text_create(BULLET1"Can be done in two passes", 64, 122+32*(texty++));
    tex_inercia = (u32*)memalign(32, _tex_inerciaSegmentRomEnd-_tex_inerciaSegmentRomStart);
    debug_assert(tex_inercia != NULL);
    nuPiReadRom((u32)_tex_inerciaSegmentRomStart, tex_inercia, _tex_inerciaSegmentRomEnd-_tex_inerciaSegmentRomStart);
}

void slide27_update()
{
    if (contdata[0].trigger & START_BUTTON)
    {
        slidestate++;
        switch (slidestate)
        {
            case 1:
                text_cleanup();
                rerender_menu();
                break;
            case 2:
                slide_change(global_slide+1);
                break;
        }
    }
    
    if (slidestate == 1 && contdata[0].trigger & U_JPAD && selectedmode != 6)
    {
        selectedmode++;
        text_cleanup();
        rerender_menu();
    }
    if (slidestate == 1 && contdata[0].trigger & D_JPAD && selectedmode != 0)
    {
        selectedmode--;
        text_cleanup();
        rerender_menu();
    }
    env += 0.03;
}

static Vtx vtx_square[] = {
    {-50, 0, 0, 0, 0, 1024, 255, 0, 0, 255}, /* 0 */
    {50, 0, 0, 0, 1024, 1024, 0, 0, 255, 255}, /* 1 */
    {50, 0, 100, 0, 1024, 0, 0, 0, 0, 255}, /* 2 */
    {-50, 0, 100, 0, 0, 0, 0, 255, 0, 255}, /* 3 */
};

void slide27_draw()
{
    if (slidestate == 1)
    {
        gDPSetCycleType(glistp++, G_CYC_2CYCLE);
        gDPSetRenderMode(glistp++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
        gDPSetEnvColor(glistp++, abs(255*sinf(env)), abs(255*sinf(env)), abs(255*sinf(env)), 255);
        switch (selectedmode)
        {
            case 0: gDPSetCombineMode(glistp++, SHOWMODE1, SHOWMODE7); break;
            case 1: gDPSetCombineMode(glistp++, SHOWMODE2, SHOWMODE7); break;
            case 2: gDPSetCombineMode(glistp++, SHOWMODE3, SHOWMODE7); break;
            case 3: gDPSetCombineMode(glistp++, SHOWMODE4, SHOWMODE7); break;
            case 4: gDPSetCombineMode(glistp++, SHOWMODE5, SHOWMODE7); break;
            case 5: gDPSetCombineMode(glistp++, SHOWMODE6, SHOWMODE7); break;
            case 6: gDPSetCombineMode(glistp++, SHOWMODE6, SHOWMODE8); break;
        }
        gDPSetTextureFilter(glistp++, G_TF_BILERP);
        gSPClearGeometryMode(glistp++, G_LIGHTING);
        gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPLoadTextureBlock(glistp++, tex_inercia, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPVertex(glistp++, vtx_square+0, 4, 0);
        gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
    }
}

void slide27_cleanup()
{
    free(tex_inercia);
}