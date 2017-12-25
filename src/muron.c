#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "muron.h"

static mr_Buffer* _buffer    = 0;              // render buffer object 
static int _width = 0, _height = 0;              // size of window 
static mr_Effect _effect     = 0;              // current pixel effect 
static mr_Texture* _texture  = 0;              // current binded texture
static mr_Color _color       = { 0xffffffff }; // current render color 

#define min(x, y) (x < y? x : y)
#define max(x, y) (x > y? x : y)
#define clamp(x, l, r) (min(max(x, l), r))

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
    _width = w;
    _height = h;
    _buffer = calloc(1, sizeof(mr_Buffer));
    _buffer->pixels = calloc(1, sizeof(mr_Color) * w * h);
    _buffer->size = w * h;
}

void mr_close() 
{
    if(_buffer != 0)
    {
        free(_buffer->pixels);
        free(_buffer); 
        _buffer = 0; 
    }
}

void mr_useshader(mr_Effect* effect)
{
    _effect = effect;
}

void mr_color(mr_Channel r, mr_Channel g, mr_Channel b, mr_Channel a)
{
    _color.rgba.r = r;
    _color.rgba.g = g;
    _color.rgba.b = b;
    _color.rgba.a = a;
}

void mr_post(unsigned int* dst)
{
    if (dst == 0) return; 
    memmove(dst, _buffer->pixels, sizeof(mr_Color) * _buffer->size);
}

static mr_Color _defaultdeffect(mr_Color color, mr_Texture* tex, mr_Vector texcoord, mr_Vector screencoord)
{
    return color; 
}

void mr_clear()
{
    memset(_buffer->pixels, 0, _buffer->size * sizeof(mr_Color));
}

void mr_drawtriangle(mr_render_mode mode, mr_Vector p1, mr_Vector p2, mr_Vector p3)
{
}

void mr_drawrectangle(mr_render_mode mode, mr_Vector p, int width, int height)
{
    if (p.x >= _width || p.y >= _height || p.x + width < 0 || p.y + height < 0)
        return;
    // clip
    int left = clamp(p.x, 0, _width - 1),
        top = clamp(p.y, 0, _height - 1),
        right = min(p.x + width, _width - 1),
        bottom = min(p.y + height, _height - 1);
    for(int x = left; x < right;x++)
        for (int y = top; y < bottom; y++)
        {
            if (_effect != 0)
            {
                mr_Vector uv = {0,0};
                mr_Vector tar = {x, y};
                //_buffer->pixels[x + y * _width] = _effect(_color, _texture, uv, tar);
                _effect(&(_buffer->pixels[x + y * _width]), &_color, &_texture, &uv, &tar);
            }
            else 
                _buffer->pixels[x + y * _width] = _color;
        }
}

