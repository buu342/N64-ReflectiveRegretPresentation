#ifndef _PRESENTATION_TEXT_H
#define _PRESENTATION_TEXT_H
    
    typedef enum {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT,
    } textAlign;

    typedef struct {
        u8 w;
        u8 h;
        u16 offsetx;
        u16 offsety;
        u8* tex;
        u32 xpadding;
    } charDef;
    
    typedef struct {
        charDef ch[128-33];
    } fontDef;
    
    typedef struct {
        u16 x;
        u16 y;
        charDef* cdef;
    } letterDef;
    
    extern fontDef font_title;
    extern fontDef font_default;
    
    void text_initialize();
    void text_create(char* str, u16 x, u16 y);
    void text_render(Gfx** glistp);
    void text_rendernumber(Gfx** glistp, int num, u16 x, u16 y);
    void text_reset();
    void text_cleanup();
    void text_setfont(fontDef* font);
    void text_setalign(textAlign align);
    void text_setpos(s16 x, s16 y);
    void text_setcolor(u8 r, u8 g, u8 b, u8 a);
    
#endif