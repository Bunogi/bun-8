//Standard includes
#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

//SFML includes
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include <cstring>

//This project's headers includes
#include "graphics.h"
#include "chip-8.h"
#include "constants.h"
#include "keys.h"

extern sf::RenderWindow window;

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
		std::memset(core.key, false, sizeof core.key);
		
		sf::Event event;	
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyPressed:
				{
					unsigned short pressedKey = getKeypress();
					if(pressedKey != 0xFF)
						//std::cerr << "You pressed the key " << std::hex << pressedKey << "\n";
						core.key[pressedKey] = true;
				
					break;
				}	
				default:
					break;
			}
		}
				
		core.emulateCycle();

		if (core.drawFlag)
			drawScreen();
		
		while( clock.getElapsedTime().asMilliseconds() < 1000/60 ) //Chip-8 has a refresh rate of 60Hz, 60 times per second
			sf::sleep(sf::milliseconds( (1000/60) - clock.getElapsedTime().asMilliseconds()) );
			
		std::cerr << "\rFPS: " << (1 / clock.getElapsedTime().asSeconds()); 
	}	
}
