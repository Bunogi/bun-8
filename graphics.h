#ifndef GRAPHICS_H
#define GRAPHICS_H

extern unsigned short screen [64 * 32]; //Monochrome display, we only need two pixel states
extern int pixelSizeX;
extern int pixelSizeY;

bool initGraphics();
void drawScreen();

#endif 
