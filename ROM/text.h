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

    extern u8        textrender_bold;
    extern fontDef*  textrender_font;
    extern textAlign textrender_align;
    extern u16       textrender_startx;
    extern u16       textrender_starty;
    extern u8        textrender_r;
    extern u8        textrender_g;
    extern u8        textrender_b;
    extern u8        textrender_a;
    
    extern fontDef font_title;
    
    void initialize_text();
    void create_text(char* str, u16 x, u16 y);
    void render_text(Gfx** glistp);
    void render_number(Gfx** glistp, int num, u16 x, u16 y);
    void reset_text();
    void cleanup_text();

#endif