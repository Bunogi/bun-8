#ifndef GRAPHICS_H
#define GRAPHICS_H

extern bool screen [64 * 32]; //Monochrome display, we only need two pixel states

bool initGraphics();
void drawScreen();

#endif 
