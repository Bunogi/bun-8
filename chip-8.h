#ifndef CHIP_8_H
#define CHIP_8_H

#include <string>

class Chip8
{

	unsigned short opcode; //Stores current opcode

	unsigned char memory[4096]; //4KB of memory

	//CPU registers
	unsigned char V[16]; //General purpose registers
	unsigned short I;// Index register
	unsigned short pc; //Program counter

	//Stack
	unsigned short stack[16];
	unsigned short stackPointer; 

	//Keyboard state
	unsigned char key[16];

	//fontset
	unsigned char fontset[80] =	{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  /* F */ }; //Casually stolen from multigesture, used to draw characters to the screen

	//Timers
	unsigned int dTimer;
	unsigned int soundTimer;

	public:
		Chip8();
		int loadProgram(std::string file);
		void emulateCycle();
		void refreshKeys();
		bool drawFlag; //Determine whenever or not to redraw the screen

};

#endif 
