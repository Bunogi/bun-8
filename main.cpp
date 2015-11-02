//Standard includes
#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

//SFML includes
#include <SFML/System.hpp>

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
	
	initGraphics();
	
	sf::Clock clock;

	std::cerr << std::setprecision(10);

	while(true)
	{
		clock.restart();
			
		core.emulateCycle();

		if (core.drawFlag)
			drawScreen();
		
		while( clock.getElapsedTime().asMilliseconds() < 1000/60 ) //Chip-8 has a refresh rate of 60Hz, 60 times per second
			sf::sleep(sf::milliseconds( (1000/60) - clock.getElapsedTime().asMilliseconds()) );
			
		std::cerr << "\rFPS: " << (1 / clock.getElapsedTime().asSeconds()); 
	}	
}
