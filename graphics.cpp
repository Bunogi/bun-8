#include <iostream>

#include <SMFL/Graphics>

#include "graphics.h"

const int screen_height = 400;
const int screen_width = 200;

sf::RenderWindow window(sf::VideoMode(screen_height, screen_width));
sf::CircleShape shape(100.f);
shape.setFillColor(sf::Color::Green);

bool screen[64 * 32] = { }; //Monochrome display, we only need two pixel states

bool initGraphics()
{
	
}

void drawScreen()
{
	window.clear();
	window.draw(shape);
	window.display();
}
