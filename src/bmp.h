/*
* Single.h/bmp.h 
*/

#ifndef SINGLE_H_BMP_H
#define SINGLE_H_BMP_H

//void* loadBMP(const char* file, unsigned short bpp, unsigned int* w, unsigned int* h);

#define BMP_IMPLEMENT
#ifdef BMP_IMPLEMENT
#include <assert.h>
#include <stdio.h>

void* loadBMP(const char* file, unsigned short bpp, unsigned int* w, unsigned int* h)
{
    assert(bpp == 24 || bpp == 32);
    void* pColor; 

}

#endif

#endif
