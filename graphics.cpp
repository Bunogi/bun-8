#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "graphics.h"

const int screen_width = 1000;
const int screen_height = 500;

sf::Vector2<float> size( screen_width / 64, screen_height / 32);

sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Bun-8");
sf::RectangleShape pixels[64][32] = {};
//sf::Text text[64] = {};
//sf::Font font;

unsigned short screen[64 * 32] = { };

bool initGraphics()
{
	for(int iii = 0; iii < 64; iii++)
	{
		for(int jjj = 0; jjj < 32; jjj++)
		{
			pixels[iii][jjj] = sf::RectangleShape(size);
			pixels[iii][jjj].setPosition(iii * size.x, jjj * size.y);
		}
	}

	return true;
}

void drawScreen()
{
	window.clear(sf::Color::Black);
	for(int iii = 0; iii < 32*64; iii++)
	{
		int x, y;
		if( iii <= 63 )
		{
			x = 0;	
			y = iii;
		}
		if( iii % 64 == 0) // y is zero
		{	
			x = iii / 64;
			y = 0;
		}
		else if (iii % 64 != 0 )
		{
			int leftover = iii % 64;
			x = ((iii - leftover) / 64);
			y = leftover;
		}
		
		if( screen[iii] != 0)
		{
			pixels[y][x].setFillColor(sf::Color(255, 255, 255));	
		}
		else
			pixels[y][x].setFillColor(sf::Color(0, 0, 0));
			
	}
	for (int x = 0; x < 64; x++)
		for(int y = 0; y < 32; y++)
			window.draw(pixels[x][y]);
	
	window.display();	
}
