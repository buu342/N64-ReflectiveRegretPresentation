/***************************************************************
                           helper.c
                               
Contains some convenience functions
***************************************************************/

#include <nusys.h>
#include "config.h"
#include "helper.h"
#include "debug.h"

// High resolution framebuffers array
u16* framebuffers_hires[] = {
    ADDR_FB1_HD,
    ADDR_FB2_HD,
    ADDR_FB3_HD,
};

// High resolution framebuffers array
u16* framebuffers_hiresbad[] = {
    ADDR_FB1_HDBAD,
    ADDR_FB2_HDBAD,
    ADDR_FB3_HDBAD,
};

// Low resolution framebuffers array
u16* framebuffers_lowres[] = {
    ADDR_FB1_SD,
    ADDR_FB2_SD,
    ADDR_FB3_SD,
};

void init_highres()
{
    global_highres = TRUE;
    
    // Wait for graphic tasks to end
    nuGfxTaskAllEndWait();
    
    // Set the VI mode based on the region
    switch (TV_TYPE)
    {
        case NTSC: osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]); break;
        case PAL : osViSetMode(&osViModeTable[OS_VI_FPAL_HAN1]); break;
        case MPAL: osViSetMode(&osViModeTable[OS_VI_MPAL_HAN1]); break;
    }

    // Turn the screen off
    nuGfxDisplayOff();

    // Set the framebuffer and z-buffer addresses
    nuGfxSetCfb(framebuffers_hires, sizeof(framebuffers_hires)/sizeof(framebuffers_hires[0]));
    nuGfxSetZBuffer(ADDR_ZB_HD);
    
    // Turn the display back on
    nuGfxDisplayOn();
}

void init_highresbad()
{
    global_highres = TRUE;
    
    // Wait for graphic tasks to end
    nuGfxTaskAllEndWait();
    
    // Set the VI mode based on the region
    switch (TV_TYPE)
    {
        case NTSC: osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]); break;
        case PAL : osViSetMode(&osViModeTable[OS_VI_FPAL_HAN1]); break;
        case MPAL: osViSetMode(&osViModeTable[OS_VI_MPAL_HAN1]); break;
    }

    // Turn the screen off
    nuGfxDisplayOff();

    // Set the framebuffer and z-buffer addresses
    nuGfxSetCfb(framebuffers_hiresbad, sizeof(framebuffers_hiresbad)/sizeof(framebuffers_hiresbad[0]));
    nuGfxSetZBuffer(ADDR_ZB_HDBAD);
    
    // Turn the display back on
    nuGfxDisplayOn();
}


void init_lowres()
{
    global_highres = FALSE;
    
    // Wait for graphic tasks to end
    nuGfxTaskAllEndWait();

    // Set the VI mode based on the region
    switch (TV_TYPE)
    {
        case NTSC: osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]); break;
        case PAL : osViSetMode(&osViModeTable[OS_VI_FPAL_LAN1]); break;
        case MPAL: osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]); break;
    }

    // Turn the screen off
    nuGfxDisplayOff();

    // Set the framebuffer and z-buffer addresses
    nuGfxSetCfb(framebuffers_lowres, sizeof(framebuffers_lowres)/sizeof(framebuffers_lowres[0]));
    nuGfxSetZBuffer(ADDR_ZB_SD);
    
    // Turn the display back on
    nuGfxDisplayOn();
}


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


/*==============================
    lerp
    Returns the linear interpolation of 
    two values given a fraction
    @param The first value
    @param The target value
    @param The fraction
==============================*/

inline f32 lerp(f32 a, f32 b, f32 f)
{
    return a + f*(b - a);
}

void load_overlay(u8* ramstart, u8* romstart, u8* romend, u8* textstart, u8* textend, u8* datastart, u8* dataend, u8* bssstart, u8* bssend)
{
    NUPiOverlaySegment	segment;
    
    // Perform the overlay operation
	segment.romStart	= romstart;
	segment.romEnd		= romend;
	segment.ramStart	= ramstart;
	segment.textStart	= textstart;
	segment.textEnd		= textend;
	segment.dataStart	= datastart;
	segment.dataEnd		= dataend;
	segment.bssStart	= bssstart;
	segment.bssEnd		= bssend;
    nuPiReadRomOverlay(&segment);
}

double fabs(double x)
{
    return (x < 0) ? -x : x;
}