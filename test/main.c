#include "../src/muron.h"

mr_color_t effect(mr_color_t curcolor, mr_texture_t* tex, mr_vector_t tex_coord, mr_vector_t screen_coord)
{
    mr_color_t col = mr_texel(tex, tex_coord); 
    
    return col; 
}

int main()
{
    mr_init(300, 300, MR_ARGB);
    mr_use(effect);
    //mr_drawimage();
    mr_unuse(); 
    //mr_color_t col = (mr_color_t)0xffffffff;
    unsigned int a; 

}