#include <SFML/Window/Keyboard.hpp>

#include "keys.h"

unsigned short getKeypress()
{
	//To remap keys, just change these enums values according to the enum in http://www.sfml-dev.org/documentation/2.0/classsf_1_1Keyboard.php	
	//{ 1 } { 2 } { 3 } { C }
	if( sf::Keyboard::isKeyPressed(NUM1))
		return 0x1;
	else if( sf::Keyboard::isKeyPressed(NUM2))
		return 0x2;
	else if( sf::Keyboard::isKeyPressed(NUM3))
		return 0x3;
	else if( sf::Keyboard::isKeyPressed(KEYC))
		return 0xA;
	
	//{ 4 } { 5 } { 6 } { D }
	else if( sf::Keyboard::isKeyPressed(NUM4))
		return 0x4;
	else if( sf::Keyboard::isKeyPressed(NUM5))
		return 0x5;
	else if( sf::Keyboard::isKeyPressed(NUM6))
		return 0x6;
	else if( sf::Keyboard::isKeyPressed(KEYD))
		return 0xD;
	//{ 7 } { 8 } { 9 } { E }
	else if( sf::Keyboard::isKeyPressed(NUM7))
		return 0x7;
	else if( sf::Keyboard::isKeyPressed(NUM8))
		return 0x8;
	else if( sf::Keyboard::isKeyPressed(NUM9))
		return 0x9; 
	else if( sf::Keyboard::isKeyPressed(KEYE))
		return 0xE; 

	//{ A } { 0 } { B } { F }
	else if( sf::Keyboard::isKeyPressed(KEYA))
		return 0xA; 
	else if( sf::Keyboard::isKeyPressed(NUM0))
		return 0x0; 
	else if( sf::Keyboard::isKeyPressed(KEYB))
		return 0xB; 
	else if( sf::Keyboard::isKeyPressed(KEYF))
		return 0xF; 
	else
		return 0xFF;
}
