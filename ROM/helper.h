#ifndef PRESENTATION_HELPER_H
#define PRESENTATION_HELPER_H
    
    typedef struct {
        u8 hasblink;
        u16* faces[3];
    } FaceAnim;
    
    typedef struct {
        float x;
        float y;
        float z;
        int rotz;
        float* correctpos;
        Gfx* dl;
        Mtx matrix;
    } modelHelper;

    
    /*********************************
                Functions
    *********************************/

    void init_highres();
    void init_lowres();
    void init_highresbad();
    void rcp_init();
    void fb_clear(u8 r, u8 g, u8 b);
    f32  lerp(f32 a, f32 b, f32 f);
    void load_overlay(u8* ramstart, u8* romstart, u8* romend, u8* textstart, u8* textend, u8* datastart, u8* dataend, u8* bssstart, u8* bssend);
    double fabs(double x);
    
    
    /*********************************
                 Globals
    *********************************/

    extern Gfx rspinit_dl_low[];
    extern Gfx rdpinit_dl_low[];
    extern Gfx rspinit_dl_high[];
    extern Gfx rdpinit_dl_high[];

#endif