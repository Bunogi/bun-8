//Standard includes
#include <iostream>
#include <memory>
#include <string>

//This project's headers includes
#include "graphics.h"
#include "chip-8.h"
#include "constants.h"

//const int pixel_height = screen_height / 64; //Display resolution of CHIP-8 is 64x32, this way we can scale them and resize our own window
//const int pixel_width = screen_width / 32;	 //The remainder doesn't matter, we can't illuminate half a pixel and therefore we ignore them 

int main(int argc, const char *argv[])
{
	Chip8 core;	
	if(core.loadProgram(std::string(argv[1])) != 0) return 1;

	if(not initGraphics())
		return 1;

	while(true)
	{
		core.emulateCycle();
		drawScreen();
	}	
}
