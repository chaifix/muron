#ifndef __MURON_H
#define __MURON_H

typedef unsigned int mr_size_t; 

typedef unsigned char mr_channel_t;

typedef struct mr_color_t
{
    mr_channel_t r, g, b, a;
} mr_color_t;

// RGBA buffer 
typedef struct mr_buffer_t
{
    mr_color_t* pixels;
    mr_size_t size;
} mr_buffer_t;

// outside mode 
typedef enum mr_mode
{
    MR_RGBA,
    MR_ARGB,
} mr_mode;

typedef struct mr_texutre_t
{
    mr_buffer_t buffer;
    int width, height; 
} mr_texture_t ;

typedef struct mr_vector_t
{
    float x, y;
} mr_vector_t;

int mr_init(int w, int h); 
void mr_close();

mr_color_t mr_makecolor(unsigned int pixel);
mr_vector_t mr_makevector(float x, float y);
mr_texture_t mr_maketexture(unsigned char* pixel, int w, int h, mr_mode mode);
void mr_freetexture(mr_texture_t* tex);

// shader type 
typedef mr_color_t (*mr_effect_t)(mr_color_t color, mr_texture_t* texture, mr_vector_t texture_coord, mr_vector_t screen_coord); 

// use shader 
void mr_use(mr_effect_t effect); 
// unuse shader 
void mr_unuse();
// øº¬«∂‡÷ÿŒ∆¿Ì
mr_color_t mr_texel(mr_texture_t* texture, mr_vector_t texture_coord);
void mr_color(mr_color_t col); 

void mr_copybuffer(mr_buffer_t* dst, mr_buffer_t* src, mr_size_t length);
void mr_post(unsigned char* dst, mr_mode mode);

typedef enum mr_render_mode
{
    MR_RENDER_LINE, 
    MR_RENDER_FILL
}mr_render_mode;

void mr_drawline(mr_render_mode mode, mr_vector_t start, mr_vector_t end);
void mr_drawcircle(mr_render_mode mode, mr_vector_t center, float radius);
void mr_drawtriangle(mr_render_mode mode, mr_vector_t p1, mr_vector_t p2, mr_vector_t p3);
void mr_drawrectangle(mr_render_mode mode, mr_vector_t p, int width, int height);
void mr_drawpolygon(mr_render_mode mode, mr_vector_t* points);

#endif