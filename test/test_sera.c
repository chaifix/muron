#include <SDL\SDL.h>
#define SR_MODE_ARGB 1
#include "../src/sera.h"

int width = 300, height = 300;

// 
void* _24to32(void* buf, int w, int h)
{
    unsigned int * buf32 = (unsigned int *)calloc(w*h, sizeof(unsigned int));
    for (int i = 0; i < w * h; i++)
    {
        char* buf2 = (char*)buf + 3*i;
        unsigned int col = *((unsigned int*)(buf2));
        int alpha = col & 0xff;
        buf32[i] = col | (0xff << 24);
    }
    return buf32; 
}

float n = 0;
int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("2D software render", 0);
    SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    unsigned char* pixel = screen->pixels;
    sr_Buffer* buffer = sr_newBufferShared(pixel, width, height);
    SDL_Surface* img = SDL_LoadBMP("test.bmp");
    sr_Buffer* imgbuffer = sr_newBuffer(img->w, img->h);
    sr_loadPixels(imgbuffer, _24to32(img->pixels, img->w, img->h), SR_FMT_BGRA);
    sr_Rect t = {
        .x = 0, 
        .y = 0, 
        .w = 100, 
        .h = 100
    };
    sr_Transform trans = {
        .ox = 0, 
        .oy = 0, 
        .r = 45, 
        .sx = 1, 
        .sy = 1
    };
    SDL_Event e;
    int running = 1;
    while (running)
    {
        n += 0.01;
        sr_clear(buffer, sr_color(0, 0, 0));
        sr_drawBuffer(buffer, imgbuffer, 10, 10, &t, &trans);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0;
        }
        SDL_Flip(screen);
        SDL_Delay(17);
    }
    mr_close();
}
