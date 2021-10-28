/***************************************************************
                             text.c
                             
Renders text using optimized texture loads
***************************************************************/

#include <nusys.h>
#include "datastructs.h"
#include "text.h"
#include "debug.h"
#include "assets/font_title.h"

#define SPACESIZE 8
#define MAXMIMUM_FONTTEXTURES 32

u8        textrender_bold;
fontDef*  textrender_font;
textAlign textrender_align;
u16       textrender_startx;
u16       textrender_starty;
u8        textrender_r;
u8        textrender_g;
u8        textrender_b;
u8        textrender_a;

static int        textrender_fontkey;
static Dictionary textrender_addressmap;
static linkedList textrender_loadlist[MAXMIMUM_FONTTEXTURES];

void initialize_text()
{
    textrender_fontkey = 0;
    memset(&textrender_addressmap, 0, sizeof(Dictionary));
    memset(&textrender_loadlist, 0, sizeof(linkedList)*MAXMIMUM_FONTTEXTURES);
    reset_text();
}
void create_text(char* str, u16 x, u16 y)
{
    int i;
    int charcount = 0;
    int hsize = 0, xreal;
    
    // Iterate through all characters in the string to calculate the text size and create table keys
    for (i=0; str[i] != '\0'; i++) 
    {
        int texaddr;
        charDef* cdef;
        dictNode* node;
        
        // Skip spaces
        if (str[i] == ' ')
        {
            hsize += SPACESIZE;
            continue;
        }
        charcount++;
            
        // Check if the current font's texture has been added to the dictionary (that maps font definition addresses to a key)
        cdef = &textrender_font->ch[str[i]-33];
        texaddr = (int)cdef->tex;
        hsize += cdef->w + cdef->xpadding;
        node = dict_get(&textrender_addressmap, texaddr);
        
        // If it hasn't been added, then do so
        if (node == NULL)
        {
            node = dict_append(&textrender_addressmap, texaddr, (int*)textrender_fontkey);
            textrender_fontkey++;
        }
    }
    
    // Calculate horizontal alignment
    switch (textrender_align)
    {
        case ALIGN_LEFT:   xreal = x;         break;
        case ALIGN_CENTER: xreal = x-hsize/2; break;
        case ALIGN_RIGHT:  xreal = x-hsize;   break;
    }
    
    // Iterate through all characters in the string again, allocating memory for the letters to render
    for (i=0; str[i] != '\0'; i++)
    {
        int texaddr, texkey;
        charDef* cdef;
        dictNode* node;
        letterDef* letter;
        
        // Skip spaces
        if (str[i] == ' ')
        {
            xreal += SPACESIZE;
            continue;
        }
            
        // Get this character's info
        cdef = &textrender_font->ch[str[i]-33];
        texaddr = (int)cdef->tex;
        node = dict_get(&textrender_addressmap, texaddr);
        
        // Get our "real" key for the linked list array
        texkey = (int)node->value;
        
        // Allocate memory for a letter, and initialize it
        letter = (letterDef*) malloc(sizeof(letterDef));
        letter->x = xreal;
        letter->y = y+cdef->offsety;
        letter->cdef = cdef;
        
        // Add this letter to our hashtable
        list_append(&textrender_loadlist[texkey], letter);
        
        // Calculate the next letter's position
        xreal += cdef->w + cdef->xpadding;
    }
}

void render_text(Gfx** glistp)
{
    int i;
    gDPSetCycleType((*glistp)++, G_CYC_1CYCLE);
    gDPSetTexturePersp((*glistp)++, G_TP_NONE);
    gDPSetPrimColor((*glistp)++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode((*glistp)++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF);
    gDPSetCombineMode((*glistp)++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (i=0; textrender_loadlist[i].size != 0; i++)
    {
        listNode* node = textrender_loadlist[i].head;
        gDPLoadTextureBlock((*glistp)++, ((letterDef*)(node->data))->cdef->tex, G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync((*glistp)++);
        for (; node != NULL; node = node->next)
        {
            letterDef* letter = (letterDef*)node->data;
            charDef* cdef = letter->cdef;
            gSPScisTextureRectangle((*glistp)++, 
                letter->x << 2, letter->y << 2, 
                (letter->x+cdef->w) << 2, (letter->y+cdef->h) << 2, 
                G_TX_RENDERTILE, 
                cdef->offsetx << 5, cdef->offsety << 5, 
                1 << 10, 1 << 10
            );
        }
    }
}

void render_number(Gfx** glistp, int num, u16 x, u16 y)
{

}

void reset_text()
{
    textrender_bold = FALSE;
    textrender_font = NULL;
    textrender_align = ALIGN_LEFT;
    textrender_startx = 0;
    textrender_starty = 0;
    textrender_r = 0;
    textrender_g = 0;
    textrender_b = 0;
    textrender_a = 255;
}

void cleanup_text()
{
    int i;
    for (i=0; i<MAXMIMUM_FONTTEXTURES; i++)
        list_destroy_deep(&textrender_loadlist[i]);
}