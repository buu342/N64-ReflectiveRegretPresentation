/***************************************************************
                           helper.c
                               
Contains some convenience functions
***************************************************************/

#include <nusys.h>
#include "config.h"
#include "helper.h"


/*==============================
    rcp_init
    Initializes the RCP before drawing anything.
==============================*/

void rcp_init()
{
    // Set the segment register
    gSPSegment(glistp++, 0, 0);
    
    // Initialize the RSP and RDP with a display list
    if (global_highres)
    {
        gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rspinit_dl_high));
        gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rdpinit_dl_high));
    }
    else
    {
        gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rspinit_dl_low));
        gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rdpinit_dl_low));    
    }
}


/*==============================
    fb_clear
    Initializes the framebuffer and Z-buffer
    @param The red value
    @param The green value
    @param The blue value
==============================*/

void fb_clear(u8 r, u8 g, u8 b)
{
    int w, h;
    
    // Set a value for width and height based on our resolution
    if (global_highres)
    {
        w = SCREEN_WD_HD;
        h = SCREEN_HT_HD;
    }
    else
    {
        w = SCREEN_WD_SD;
        h = SCREEN_HT_SD;    
    }
    
    // Clear the Z-buffer
    gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetFillColor(glistp++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 | GPACK_ZDZ(G_MAXFBZ,0)));
    gDPFillRectangle(glistp++, 0, 0, w-1, h-1);
    gDPPipeSync(glistp++);

    // Clear the framebuffer
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(r, g, b, 1) << 16 | 
                               GPACK_RGBA5551(r, g, b, 1)));
    gDPFillRectangle(glistp++, 0, 0, w-1, h-1);
    gDPPipeSync(glistp++);
}
