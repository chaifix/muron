#include <SDL\SDL.h>
#define MR_MODE_ARGB 1
#include "../src/muron.h"

// shader
mr_color_t effect(mr_color_t color, mr_texture_t* tex, mr_vector_t tex_coord, mr_vector_t screen_coord)
{
    return color;
}

int width = 300, height = 300;

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_WM_SetCaption("2D software render", 0);
    SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    unsigned char* pixel = screen->pixels;
    mr_init(width, height); 
    mr_color(255, 0, 0, 255);
    //
    SDL_Event e; 
    int running = 1; 
    while(running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0; 
        }   
        mr_clear();
        mr_vector_t v = {20, 20};
        mr_use(effect); 
        mr_drawrectangle(MR_RENDER_FILL, v, 100, 200);
        mr_unuse();
        mr_post(pixel);
        SDL_Flip(screen);
        SDL_Delay(17);
    }
    mr_close(); 
}