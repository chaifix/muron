#ifndef __MURON_H
#define __MURON_H

#if MR_MODE_RGBA
#define MR_CHANNELS r, g, b, a
#define MR_RGB_MASK 0xffffff
#elif MR_MODE_ARGB
#define MR_CHANNELS a, r, g, b
#define MR_RGB_MASK 0xffffff00
#elif MR_MODE_ABGR
#define MR_CHANNELS a, b, g, r
#define MR_RGB_MASK 0xffffff00
#else
#define MR_CHANNELS b, g, r, a
#define MR_RGB_MASK 0xffffff
#endif

typedef unsigned int mr_Size; 

typedef unsigned char mr_Channel;

typedef union 
{
    unsigned int word; 
    struct { mr_Channel MR_CHANNELS;} rgba; // byte order
} mr_Color;

typedef struct 
{
    mr_Color* pixels;
    mr_Size size;
} mr_Buffer;

typedef struct 
{
    mr_Color* pixels; 
    mr_Size width, height;
} mr_Texture;

typedef struct { float x, y; } mr_Vector;

int mr_init(int w, int h); 
void mr_close();
void mr_clear(); 
mr_Color mr_makecolor(unsigned int pixel);
mr_Vector mr_makevector(float x, float y);
mr_Texture mr_maketexture(unsigned char* pixel, int w, int h);
void mr_freetexture(mr_Texture* tex);

// shader type 
typedef void(*mr_Effect)\
(mr_Color* outcolor, const mr_Color* color, const mr_Texture* tex, const mr_Vector* tex_coord, const mr_Vector* screen_coord);

// use shader 
void mr_useshader(mr_Effect shader); 
// øº¬«∂‡÷ÿŒ∆¿Ì
mr_Color mr_texel(mr_Texture* texture, mr_Vector texture_coord);
void mr_color(mr_Channel r, mr_Channel g, mr_Channel b, mr_Channel a);

void mr_copybuffer(mr_Buffer* dst, mr_Buffer* src, mr_Size length);
void mr_post(unsigned int* dst);

typedef enum 
{
    MR_RENDER_LINE, 
    MR_RENDER_FILL
}mr_render_mode;

void mr_drawline(mr_render_mode mode, mr_Vector start, mr_Vector end);
void mr_drawcircle(mr_render_mode mode, mr_Vector center, float radius);
void mr_drawtriangle(mr_render_mode mode, mr_Vector p1, mr_Vector p2, mr_Vector p3);
void mr_drawrectangle(mr_render_mode mode, mr_Vector p, int width, int height);
void mr_drawpolygon(mr_render_mode mode, mr_Vector* points);

#define mr_newshader(name, program)\
void name\
(mr_Color* outcolor, const mr_Color* color, const mr_Texture* tex, const mr_Vector* tex_coord, const mr_Vector* screen_coord)\
{program; }

#endif