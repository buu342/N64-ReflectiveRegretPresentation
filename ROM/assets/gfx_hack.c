/***************************************************************
                           gfx_hack.c

Contains the model data and display lists for the vertex cache
hack model
***************************************************************/

#include <nusys.h>


/*********************************
              Models
*********************************/

static Vtx vtx_hack[] = {
    {0, 0, -55, 0, 0, 0, 0, 0, 255, 255}, /* 0 */    // Blue, bottom right
    {-110, 0, 0, 0, 0, 0, 0, 0, 255, 255}, /* 1 */   // Blue, top left
    {-110, 0, -55, 0, 0, 0, 0, 0, 255, 255}, /* 2 */ // Blue, bottom left
    {0, 0, 0, 0, 0, 0, 255, 0, 0, 255}, /* 3 */      // Red
    {55, 0, 0, 0, 0, 0, 0, 255, 0, 255}, /* 4 */     // Green, bottom right
    {55, 0, 110, 0, 0, 0, 0, 255, 0, 255}, /* 5 */   // Green, top right
    {0, 0, 110, 0, 0, 0, 0, 255, 0, 255}, /* 6 */    // Green, top left
};

Gfx gfx_hack_blue[] = {
    gsSPVertex(vtx_hack, 4, 0),
    gsSP2Triangles(1, 2, 0, 0, 1, 0, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gfx_hack_green[] = {
    gsSPVertex(vtx_hack+4, 3, 4),
    gsSP2Triangles(6, 3, 4, 0, 6, 4, 5, 0),
    gsSPEndDisplayList(),
};

Gfx gfx_hack_red[] = {
    gsSP1Triangle(3, 0, 4, 0),
    gsSPEndDisplayList(),
};