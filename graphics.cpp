#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "graphics.h"

const int screen_width = 400;
const int screen_height = 200;

sf::Vector2<float> size( 5, 5);

sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Bun-8");
sf::RectangleShape pixels[64][32] = {};
sf::Text text[64] = {};
sf::Font font;

unsigned short screen[64 * 32] = { };

bool initGraphics()
{
	for(int iii = 0; iii < 64; iii++)
	{
		for(int jjj = 0; jjj < 32; jjj++)
		{
			pixels[iii][jjj] = sf::RectangleShape(size);
			pixels[iii][jjj].setPosition(jjj* size.x, iii * size.y);
		}
		text[iii].setPosition(iii * 5, (32 * 5) + 3);
		text[iii].setString(std::to_string(iii));
	}
	font.loadFromFile("./font.ttf");

	return true;
}

void drawScreen()
{
	window.clear(sf::Color::Black);
	for(int iii = 0; iii < 32*64; iii++)
	{
		int x, y;
		if( iii % 64 == 0 ) // y is zero
		{	
			x = iii / 64;
			y = 0;
		}
		else
		{
			int leftover = iii % 64;
			x = ((iii - leftover) / 64);
			y = leftover;
		}
		
		if( screen[iii] )
		{
			pixels[x][y].setFillColor(sf::Color(255, 0, 0));	
		}
		else
			pixels[x][y].setFillColor(sf::Color(0, 255, 0));
			
	
		window.draw(pixels[x][y]);	
	}
	window.display();	
}
