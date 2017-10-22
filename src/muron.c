#include <math.h>
#include <memory.h>
#include <assert.h>
#include "muron.h"

static mr_buffer_t* _buffer    = 0;                        // render buffer object 
static mr_effect_t* _effect    = 0;                        // current pixel effect 
static mr_color_t _color       = {0xff, 0xff, 0xff, 0xff}; // current render color 
static const mr_color_t _white = {0xff, 0xff, 0xff, 0xff}; // current render color 

#define min(x, y) (x < y? x : y)
#define max(x, y) (x > y? x : y)
#define clamp(x, l, r) (min(max(x, l), r)

static void swap(float x, float y)
{
    float t = x; 
    x = y; 
    y = t;
}

int mr_init(int w, int h) 
{
    if(_buffer != 0)
    {
        free(_buffer); 
        _buffer = 0; 
    }        
    _buffer = mealloc(); 
}

void mr_close() 
{
    if(_buffer != 0)
    {
        free(_buffer); 
        _buffer = 0; 
    }
}

void mr_use(mr_effect_t* effect)
{
    _effect = effect;
}

void mr_unuse()
{
    _effect = 0; 
}

void mr_color(mr_color_t col)
{
    _color = col; 
}

static mr_rgba(unsigned int col, mr_mode mode)
{
    mr_channel_t r, g, b, a;
    switch (mode)
    {

    }
}

void mr_post(unsigned char* dst, mr_mode mode)
{
    if (dst != 0)
    {
    }
}

static mr_color_t _defaultdeffect(mr_color_t color, mr_texture_t* tex, mr_vector_t texcoord, mr_vector_t screencoord)
{
    return color; 
}


