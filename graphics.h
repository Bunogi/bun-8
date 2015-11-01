#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Surface* screenSurface;

extern bool screen [64 * 32]; //Monochrome display, we only need two pixel states

void initGraphics();
void drawScreen();

#endif 
