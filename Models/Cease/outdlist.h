// Generated by Arabiki64 V1.0
// By Buu342

// Model convenience macro
#define MODEL_mdl_cease (&mdl_mdl_cease)

// Mesh data
#define MESHCOUNT_mdl_cease 1

#define MESH_mdl_cease_None 0

// Animation data
#define ANIMATIONCOUNT_mdl_cease 0



// Custom combine mode to allow mixing primitive and vertex colors
#ifndef G_CC_PRIMLITE
    #define G_CC_PRIMLITE SHADE,0,PRIMITIVE,0,0,0,0,PRIMITIVE
#endif


/*********************************
              Models
*********************************/

static Vtx vtx_mdl_cease_None[] = {
    {395, 344, 0, 0, 0, 0, 73, 73, -73, 255}, /* 0 */
    {395, 344, 154, 0, 0, 0, 90, 90, 0, 255}, /* 1 */
    {395, -344, 154, 0, 0, 0, 90, -90, 0, 255}, /* 2 */
    {395, -344, 0, 0, 0, 0, 73, -73, -73, 255}, /* 3 */
    {-395, -344, 154, 0, 0, 0, -90, -90, 0, 255}, /* 4 */
    {-395, -344, 0, 0, 0, 0, -73, -73, -73, 255}, /* 5 */
    {-395, 344, 154, 0, 0, 0, -90, 90, 0, 255}, /* 6 */
    {-395, 344, 0, 0, 0, 0, -73, 73, -73, 255}, /* 7 */
    {-406, -353, 192, 0, -256, 1024, -79, -60, 79, 255}, /* 8 */
    {406, -353, 192, 0, 2304, 1024, 79, -60, 79, 255}, /* 9 */
    {406, 0, 192, 0, 2304, 0, 0, 0, 127, 255}, /* 10 */
    {-406, 0, 192, 0, -256, 0, 0, 0, 127, 255}, /* 11 */
    {-406, 0, 192, 0, -256, 1024, 0, 0, 127, 255}, /* 12 */
    {406, 0, 192, 0, 2304, 1024, 0, 0, 127, 255}, /* 13 */
    {406, 353, 192, 0, 2304, 0, 79, 60, 79, 255}, /* 14 */
    {-406, 353, 192, 0, -256, 0, -79, 60, 79, 255}, /* 15 */
    {406, -353, 112, 0, 0, 0, 89, -90, 0, 255}, /* 16 */
    {406, -353, 33, 0, 0, 512, 90, -90, 0, 255}, /* 17 */
    {406, 353, 33, 0, 4096, 512, 90, 90, 0, 255}, /* 18 */
    {406, 353, 112, 0, 4096, 0, 91, 88, 0, 255}, /* 19 */
    {406, 353, 112, 0, 0, 0, 87, 92, 0, 255}, /* 20 */
    {406, 353, 33, 0, 0, 512, 90, 90, 0, 255}, /* 21 */
    {-406, 353, 33, 0, 4096, 512, -90, 90, 0, 255}, /* 22 */
    {-406, 353, 112, 0, 4096, 0, -88, 91, 0, 255}, /* 23 */
    {-406, 353, 112, 0, 0, 0, -92, 87, 0, 255}, /* 24 */
    {-406, 353, 33, 0, 0, 512, -90, 90, 0, 255}, /* 25 */
    {-406, -353, 33, 0, 4096, 512, -90, -90, 0, 255}, /* 26 */
    {-406, -353, 112, 0, 4096, 0, -91, -88, 0, 255}, /* 27 */
    {-406, -353, 112, 0, 0, 0, -87, -92, 0, 255}, /* 28 */
    {-406, -353, 33, 0, 0, 512, -90, -90, 0, 255}, /* 29 */
    {406, -353, 33, 0, 4096, 512, 90, -90, 0, 255}, /* 30 */
    {406, -353, 112, 0, 4096, 0, 89, -90, 0, 255}, /* 31 */
    {-406, -353, 192, 0, 0, 0, -77, -65, 77, 255}, /* 32 */
    {-406, -353, 112, 0, 0, 512, -87, -92, 0, 255}, /* 33 */
    {406, -353, 112, 0, 4096, 512, 90, -90, 0, 255}, /* 34 */
    {406, -353, 192, 0, 4096, 0, 77, -65, 77, 255}, /* 35 */
    {-406, 353, 192, 0, 0, 0, -77, 65, 77, 255}, /* 36 */
    {-406, 353, 112, 0, 0, 512, -92, 87, 0, 255}, /* 37 */
    {-406, -353, 112, 0, 4096, 512, -93, -86, 0, 255}, /* 38 */
    {-406, -353, 192, 0, 4096, 0, -77, -65, 77, 255}, /* 39 */
    {406, 353, 192, 0, 0, 0, 77, 65, 77, 255}, /* 40 */
    {406, 353, 112, 0, 0, 512, 87, 92, 0, 255}, /* 41 */
    {-406, 353, 112, 0, 4096, 512, -86, 93, 0, 255}, /* 42 */
    {-406, 353, 192, 0, 4096, 0, -77, 65, 77, 255}, /* 43 */
    {406, -353, 192, 0, 0, 0, 77, -65, 77, 255}, /* 44 */
    {406, -353, 112, 0, 0, 512, 90, -89, 0, 255}, /* 45 */
    {406, 353, 112, 0, 4096, 512, 93, 86, 0, 255}, /* 46 */
    {406, 353, 192, 0, 4096, 0, 77, 65, 77, 255}, /* 47 */
};

static Gfx gfx_mdl_cease_None[] = {
    gsSPVertex(vtx_mdl_cease_None+0, 16, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_PRIMLITE, G_CC_PRIMLITE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 56, 56, 56, 255),
    gsDPPipeSync(),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
    gsSP2Triangles(7, 6, 1, 0, 7, 1, 0, 0),
    gsSP2Triangles(7, 0, 3, 0, 7, 3, 5, 0),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPLoadTextureBlock(tex_cease_top, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_MIRROR, G_TX_MIRROR, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),

    gsSPVertex(vtx_mdl_cease_None+16, 32, 0),
    gsDPLoadTextureBlock(tex_cease_side, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 16, 0, G_TX_MIRROR, G_TX_MIRROR, 7, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsSPEndDisplayList(),
};


/*********************************
          Animation Data
*********************************/


/*********************************
        Sausage64 Structs
*********************************/

static s64Mesh meshes_mdl_cease[] = {
    {"None", gfx_mdl_cease_None},
};

static s64Animation anims_mdl_cease[] = {
};

static s64ModelData mdl_mdl_cease = {1, 0, meshes_mdl_cease, anims_mdl_cease};