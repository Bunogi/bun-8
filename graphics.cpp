#include <iostream>

#include <SDL2/SDL.h>

#include "graphics.h"

const int screen_height = 400;
const int screen_width = 200;

bool screen[64 * 32] = { 0 }; //Monochrome display, we only need two pixel states
SDL_Window* window(nullptr);
SDL_Surface* screenSurface(nullptr);

void initGraphics()

{
	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
		std::cerr << "Failed to initialize SDL, " << SDL_GetError() << "\n";
	else
		window = SDL_CreateWindow("Bun-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_height, screen_width, SDL_WINDOW_SHOWN);
		if (window == nullptr) { std::cerr << "Failed to creat the window, " << SDL_GetError() << "\n"; return; }
}

void drawScreen()
{
		screenSurface = SDL_GetWindowSurface(window);	
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x0));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(2000);
		SDL_DestroyWindow(window);
		SDL_Quit();
}
