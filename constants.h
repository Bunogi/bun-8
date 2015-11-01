#ifndef CONSTS_H
#define CONSTS_H
extern const int screen_height;
extern const int screen_width;

extern const int pixel_heigh; //Display resolution of CHIP-8 is 64x32, this way we can scale them and resize our own window
extern const int pixel_width; //The remainder doesn't matter, we can't illuminate half a pixel and therefore we ignore them 

extern bool screen[64 * 32]; //Chip-8 is monochrome, and therefore each pixel can be represented with a bool without problems

extern unsigned char memory[4096]; //4KB of memory

//CPU registers
extern unsigned char V[16]; //General purpose registers
extern unsigned short I; // Index register
extern unsigned short pc; //Program counter

//Stack
extern unsigned short stack[16];
extern unsigned short stackPointer; 

//Keyboard state
extern unsigned char key[16];

#endif
