#ifdef TEST
#include <SDL\SDL.h>
#define MR_MODE_ARGB 1
#include "../src/muron.h"

int width = 300, height = 300;

float n = 0; 

mr_newshader(effect,
    outcolor->rgba.r = 255 * n ;
    outcolor->rgba.g = 255;
    outcolor->rgba.b = 255;
    outcolor->rgba.a = 255;
)

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_WM_SetCaption("2D software render", 0);
    SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    unsigned char* pixel = screen->pixels;
    mr_init(width, height); 
    mr_color(255, 0, 0, 255);
    
    SDL_Event e; 
    int running = 1; 
    while(running)
    {
        n += 0.01; 
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0; 
        }   
        mr_clear();
        mr_Vector v = {20, 20};
        mr_useshader(effect); 
        mr_drawrectangle(MR_RENDER_FILL, v, 100, 200);
        mr_useshader(0);
        mr_post(pixel);
        SDL_Flip(screen);
        SDL_Delay(17);
    }
    mr_close(); 
}
#endif