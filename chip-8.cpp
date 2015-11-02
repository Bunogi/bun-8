//C++ includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

//C includes for random numbers, a little easier than using C++11's random, but yes I know it exists
#include <stdlib.h>
#include <time.h>

//Project includes
#include "chip-8.h"
#include "exceptions.h"

Chip8::Chip8()
{
	opcode = 0;
	I = 0;
	pc = 0x200; //Roms are loaded in starting at 0x200.
	stackPointer = 0; 
	dTimer = 0;
	soundTimer = 0;

	memset(stack, 0, sizeof stack);
	memset(key, 0, sizeof key);
	memset(memory, 0, sizeof memory);
	memset(V, 0, sizeof V);
	
	std::srand(time(NULL));

	for(int iii = 0; iii < 80; iii++)
		memory[iii] = fontset[iii];  // Load the fontset into memory
}

Chip8::~Chip8()
{
}

int Chip8::loadProgram(std::string file)
{
	std::ifstream romFile;
	romFile.open(file, std::ios::in | std::ios::binary | std::ios::ate);	
	int length = romFile.tellg();
	romFile.seekg(0, romFile.beg);
	
	char *buffer = new char [length];

	std::cerr << "File size: " << length << "\n";
	
	romFile.read(buffer, length);

	if(not romFile) return 1;

	for(int iii = 0; iii < length; iii++)
		memory[0x200 + iii] = buffer[iii];

	delete[] buffer;

	romFile.close();

	return 0;
}

void Chip8::emulateCycle()
{
	opcode = memory[pc] << 8 | memory[pc + 1]; // The actual opcode is two bytes long, so we merge two bytes here.
	int testCode = opcode & 0xF000;
	try {			
		switch(testCode) //
		{
			case 0x0000: //There are several possibilities from here
				switch(opcode)
				{
					case 0x00E0: //00E0, clear the screen
						std::cerr << "Please implement graphics!\n";
						pc += 2;
						break;
					
					case 0x00EE: //00EE, return from a subroutine
						stackPointer--;
						pc = stack[stackPointer];
						pc += 2;	
				}	
				break;
			case 0x1000: //1NNN, jump to NNN in memory
				pc = opcode & 0x0FFF;
				break;

			case 0x2000: //0x2NNN, calls subroutine at NNN
				stack[stackPointer] = pc;
				stackPointer++;
				pc = opcode & 0x0FFF;
				break;

			case 0x3000: //3XNN, skip next instruction if VX == NN
				if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
					pc += 2;
				pc += 2; //This way, there's no need for an else statement!
				break;

			case 0x4000: //4XNN, skips next instruction if VX != NN
				if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x0FF))
					pc += 2;
				pc += 2;
				break;

			case 0x5000: //5XY0, skip next instruction if V[X] == V[Y]
				if(V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
					pc += 2;
				pc += 2;
				break;

			case 0x6000: //6XNN, set V[X] = NN
				V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;	
				pc += 2;
				break;

			case 0x7000: //7XNN, adds NN to V[X]
				V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
				pc += 2;
				break;

			case 0x8000:
				switch(opcode & 0xF00F)
				{
					case 0x8000: //8XY0, sets V[X] to the value of V[Y]
						V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
						pc += 2;
						break;

				case 0x8001: //8XY1, V[X] == V[X] | V[Y]
					V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
					pc += 2;
					break;

				case 0x8002: //8XY2, V[X] = V[X] & V[Y]
					V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
					pc += 2;
					break;

				case 0x8003: //8XY3, V[X] = V[X] ^ V[Y]
					V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
					pc += 2;
					break;

				case 0x8004: //8XY4, Add V[Y] to V[X], set V[F] to 1 if the result is greater than 0xFF and caused overflow.
					if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))  //If Y is greater than 255 - X, overflow must have occured.
						V[0xF] = 1;
					else
						V[0xF] = 0;
					V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
					pc += 2;
					break;

				case 0x8005: //8XY5, Subtract V[Y] from V[X]
					if(V[(opcode & 0x00F0) >> 4] < (0xFF - V[(opcode & 0x0F00) >> 8]))
						V[0xF] = 1;
					else
						V[0xF] = 0;
					V[(opcode & 0x0F00) >> 8] -= V[((opcode & 0x00F0) >> 4)];
					pc += 2;
					break;

				case 0x8006: //8XY6, Shift V[X] right by one, V[F] is set to the least significant bit of V[X] before the shift
					V[0xF] = (V[opcode & 0x0F00] << 8) & 1;
					V[opcode & 0x0F00] >>= 1;
					pc += 2;
					break;

				case 0x8007: //8XY7, Sets V[X] = V[Y] - V[X], V[F] is set to 0 when there isn't a borrow, and 1 when it is.
					if(V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0) >> 4])
						V[0xF] = 1;
					else
						V[0xF] = 0;
					V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
					pc += 2;
					break;

				case 0x800E: //8XYE, shifts V[X] left by one, V[F] is set to the most significant bit of V[X] before the shift
					V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
					V[opcode & 0x0F00] <<= 1;
					pc += 2;
					break;

				default:
					throw(unknownOpcodeException(opcode, opcode & 0xF00F));
					break;
			}
			
			case 0x9000: //9XY0, skip next instruction if V[X] != V[Y]
				if(V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 8])
					pc += 2;
				pc += 2;
				break;

			case 0xA000: //ANNN, sets I to the adress NNN
				I = opcode & 0x0FFF;
				pc += 2;
				break;

			case 0xB000: //BNNN jump to the adress NNN + V[0]
				pc = (opcode &	0x0FFF) + V[0];
				break;
			
			case 0xC000: //CXNN, V[X] = random int & NNN
				V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x0FFF);
				pc += 2;
				break;

			case 0xD000: //DXYN, Draw a sprite and some things, not yet implemented
				std::cerr << "Please implement graphics!\n";
				pc += 2;
				break;

			case 0xE000: 
				switch(opcode & 0xF0FF)
				{
					case 0xE09E: //EX9E, Skip next instruction if the key stored in V[X] is pressed
						std::cerr << "Please implement input!\n";
						pc += 2;
						break;
					case 0xE0A1: //EXA1, Skip next instruction if the key stored in V[X] is not pressed
						std::cerr << "Please implement input!\n";
						pc += 2;
						break;
				}
				break;
			
		case 0xF000:
			switch(opcode & 0xF0FF)
			{
				case 0xF007: //FX07, set V[X] To the value of delay timer
					V[(opcode & 0x0F00) >> 8] = dTimer;
					pc += 2;
					break;
				
				case 0xF00A: //FX0A, a key press is awaited, and then stored in V[X];
					std::cerr << "Please implement input, opcode 0xFX0A!\n";
					pc += 2;
					break;
				
				case 0xF015: //FX15, set the delay timer to V[X]
					dTimer = ((opcode & 0x0F00) << 8);
					pc += 2;
					break;
			
				case 0xF018: //FX18, set the sound timer to V[X]
					soundTimer = ((opcode & 0x0F00) << 8);
					pc += 2;
					break;
				
				case 0xF01E: //FX1E, add V[X] to I
					I += V[(opcode & 0x0F00) >> 8];
					pc += 2;
					break;

				case 0xF029: //FX29, Set I to the location of the sprite for the character(symbol) in VX.
					I = V[(opcode & 0x0F00) >> 8] * 5;
					pc += 2;
					break;
				
				case 0xF033: //FX33, Stores the Binary-coded decimal representation of V[X] at the adresses I, I + 1, and I + 2.
					memory[I]     = V[(opcode & 0x0F00) >> 8] / 100;
					memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
					memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
					pc += 2;
					break;
			}
			
			case 0xF055: //FX55, stores V[0] to V[X] in memory starting at adress I.
				for(int iii = 0; iii <= ((opcode & 0x0F00) >> 8); iii++)
					memory[I + iii] = V[iii];

				I += ((opcode & 0x0F00) >> 8) + 1; //Original interpreter did this, adding in for improved accuracy.
				pc += 2;
				break;

			case 0xF065: //FX65, fill V[0] to V[X] with values from memory starting at I.
				for(int iii = 0; iii <= ((opcode & 0x0F00) >> 8); iii++)
					V[iii] = memory[I + iii];

				I += ((opcode & 0x0F00) >> 8) + 1; //For accuracy, original interpreter did this
				pc += 2;
				break;

			default:
				throw(unknownOpcodeException(opcode, testCode));
				break;
		}
	} catch(unknownOpcodeException ex) {
		std::cerr << "Unknown opcode 0x" << std::hex << ex.rawOpcode << " for instruction 0x" << ex.opcodeInstruction << ", terminating.. \n";
		exit(1);
		}

	if(dTimer != 0)
		dTimer--;
	if(soundTimer == 0)
		;
	else
		soundTimer--;

}	
