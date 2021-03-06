/***************************************************************
                         slide_common.c
                               
Handles stuff that's common between all slides.
***************************************************************/

#include <nusys.h>
#include "config.h"
#include "helper.h"
#include "slides.h"
#include "sausage64.h"
#include "debug.h"
#include "assets/mdl_axis.h"
#include "assets/spr_laser.h"


/*********************************
              Macros
*********************************/

#define RENDER_AXIS FALSE
#define ALLOW_CAMERA FALSE


/*********************************
        Function Prototypes
*********************************/

void draw_menu();


/*********************************
             Globals
*********************************/

// Matricies and vectors
Mtx projection, viewing, modeling;
u16 normal;

// Lights
static Light light_amb;
static Light light_dir;

// Camera
float campos[3] = {0, -100, -300};
float camang[3] = {0, 0, -90};

// Laser pointer
static u8 laser = FALSE;
static s32 laserx = 0;
static s32 lasery = 0;


/*==============================
    slide_common_init
    Initialize the slide
==============================*/

void slide_common_init()
{
    // Reset the text rendering settings to their default values
    text_reset();
    
    // Initialize the camera position
    campos[0] = 0;
    campos[1] = -100;
    campos[2] = -300;
    camang[0] = 0;
    camang[1] = 0;
    camang[2] = -90;
}


/*==============================
    slide_common_update
    Update slide variables every frame
==============================*/

void slide_common_update()
{   
    nuContDataGetEx(contdata, 0);

    // Handle the laser pointer
    if (contdata[0].button & L_TRIG)
    {
        if (!laser)
        {
            laser = TRUE;
            laserx = SCREEN_WD_HD/2;
            lasery = SCREEN_HT_HD/2;
        }
        laserx += contdata->stick_x/10;
        lasery -= contdata->stick_y/10;
    }
    else if (laser)
        laser = FALSE;

    // Force slide changes
    if (contdata[0].trigger & R_CBUTTONS && global_slide != 39)
    {
        slide_change(global_slide+1);
        return;
    }
    else if (contdata[0].trigger & L_CBUTTONS && global_slide != 0)
    {
        slide_change(global_slide-1);
        return;
    }
    
    // Handle camera movement and rotation
    #if ALLOW_CAMERA
        if (contdata[0].button & Z_TRIG)
        {
            campos[2] += contdata->stick_y/10;
        }
        else if (contdata[0].button & R_TRIG)
        {
            camang[0] += contdata->stick_x/10;
            camang[2] -= contdata->stick_y/10;
        }
        else
        {
            campos[0] += contdata->stick_x/10;
            campos[1] += contdata->stick_y/10;
        }
    #endif
}


/*==============================
    slide_common_draw_start
    Draws stuff before the actual slide
    is rendered.
==============================*/

void slide_common_draw_start()
{
    int i, ambcol = 100;
    float fmat1[4][4], fmat2[4][4];
    
    // Assign our glist pointer to our glist array for ease of access
    glistp = glist;

    // Initialize the RCP and framebuffer
    rcp_init();
    fb_clear(255, 255, 255);
    
    // Setup the projection matrix
    if (global_highres)
        guPerspective(&projection, &normal, 45, (float)SCREEN_WD_HD / (float)SCREEN_HT_HD, 64, 1000, 0.1);
    else
        guPerspective(&projection, &normal, 45, (float)SCREEN_WD_SD / (float)SCREEN_HT_SD, 64, 1000, 0.1);
        
    // Setup the lights
    for (i=0; i<3; i++)
    {
        light_amb.l.col[i] = ambcol;
        light_amb.l.colc[i] = ambcol;
        light_dir.l.col[i] = 255;
        light_dir.l.colc[i] = 255;
    }
    
    // Calculate the light direction so it's always projecting from the camera's position
    light_dir.l.dir[0] = -127*sinf(camang[0]*0.0174532925);
    light_dir.l.dir[1] = 127*sinf(camang[2]*0.0174532925)*cosf(camang[0]*0.0174532925);
    light_dir.l.dir[2] = 127*cosf(camang[2]*0.0174532925)*cosf(camang[0]*0.0174532925);
    
    // Send the light struct to the RSP
    gSPNumLights(glistp++, NUMLIGHTS_1);
    gSPLight(glistp++, &light_dir, 1);
    gSPLight(glistp++, &light_amb, 2);
    gDPPipeSync(glistp++);
    
    // Rotate and position the view
    guMtxIdentF(fmat1);
    guRotateRPYF(fmat2, camang[2], camang[0], camang[1]);
    guMtxCatF(fmat1, fmat2, fmat1);
    guTranslateF(fmat2, campos[0], campos[1], campos[2]);
    guMtxCatF(fmat1, fmat2, fmat1);
    guMtxF2L(fmat1, &viewing);
    
    // Apply the projection matrix
    gSPMatrix(glistp++, &projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &viewing, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPPerspNormalize(glistp++, &normal);
    
    // Initialize the model matrix
    guMtxIdent(&modeling);
    gSPMatrix(glistp++, &modeling, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    // Initialize the RCP to draw stuff nicely
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetDepthSource(glistp++, G_ZS_PIXEL);
    gSPClearGeometryMode(glistp++,0xFFFFFFFF);
    gSPSetGeometryMode(glistp++, G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH | G_LIGHTING);
    gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF);
    gDPSetCombineMode(glistp++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    gDPSetTextureFilter(glistp++, G_TF_BILERP);
    gDPSetTextureConvert(glistp++, G_TC_FILT);
    gDPSetTextureLOD(glistp++, G_TL_TILE);
    gDPSetTextureDetail(glistp++, G_TD_CLAMP);
    gDPSetTextureLUT(glistp++, G_TT_NONE);
    
    // Render a helper axis
    #if RENDER_AXIS
        gSPDisplayList(glistp++, gfx_axis);
    #endif
}


/*==============================
    slide_common_draw_end
    Draws stuff after a slide has been 
    rendered.
==============================*/

void slide_common_draw_end()
{
    // Render the text last
    text_render();

    // Show a laser pointer
    if (laser)
    {
        gDPSetTextureFilter(glistp++, G_TF_BILERP);
        gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, 255);
        gDPLoadTextureBlock(glistp++, spr_laser, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPScisTextureRectangle(glistp++, 
            (laserx-16) << 2, (lasery-16) << 2, 
            (laserx+16) << 2, (lasery+16) << 2, 
            G_TX_RENDERTILE, 
            0 << 5, 0 << 5, 
            1 << 10, 1 << 10
        );
    }

    // Syncronize the RCP and CPU and specify that our display list has ended
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);
    
    // Ensure the chache lines are valid
    osWritebackDCache(&projection, sizeof(projection));
    osWritebackDCache(&modeling, sizeof(modeling));
    
    // Ensure we haven't gone over the display list size, and start the graphics task
    debug_assert((glistp-glist) < GLIST_LENGTH);
    nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}


/*==============================
    slide_common_cleanup
    Cleans up a slide when its changed
==============================*/

void slide_common_cleanup()
{
    text_cleanup();
}


/*==============================
    slide_change
    Changes the current slide
==============================*/

void slide_change(u8 slide)
{
    debug_printf("Changing slide to %d\n", slide);
    nuGfxTaskAllEndWait();
    //nuGfxDisplayOff();
    
    // Cleanup the slides
    slidefunc[global_slide][3]();
    slide_common_cleanup();
    
    // Change the global slide variable
    global_slide = slide;
    
    // Initialize the next slide
    slide_common_init();
    slidefunc[global_slide][0]();
    //nuGfxDisplayOn();
    debug_printf("Done\n");
}