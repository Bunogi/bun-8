#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include <SDL2/SDL.h>

#include "chip-8.h"
#include "exceptions.h"

Chip8::Chip8()
{
	opcode = 0;
	I = 0;
	pc = 0x200; //Roms are loaded in starting at 0x200.
	stackPointer = 0; 

	memset(stack, 0, sizeof stack);
	memset(key, 0, sizeof key);
	memset(memory, 0, sizeof memory);
	memset(V, 0, sizeof V);

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
				}
				}	
				break;
			case 0x1000: //1NNN, jump to NNN in memory
				pc = opcode & 0x0FFF;
				break;
			case 0x3000: //3XNN, skip next instruction if VX == NN
				if (V[opcode & 0x0F00] == opcode & 0x0FF)
					pc += 2;
				pc += 2; //This way, there's no need for an else statement!
				break;
			case 0x4000: //4XNN, skips next instruction if VX != NN
				if (V[opcode & 0x0F00] != opcode & 0x0FF)
					pc += 2;
				pc += 2;
				break;
			case 0x5000: //5XY0, skip next instruction if V[X] == V[Y]
				if(V[opcode & 0x0F00] == V[opcode & 0x00F0])
					pc += 2;
				pc += 2;
				break;
			case 0x6000: //6XNN, set V[X] = NN
				V[opcode & 0x0F00] = opcode & 0x00FF;	
				pc += 2;
				break;
			case 0x7000: //7XNN, adds NN to V[X]
				V[opcode & 0x0F00] += opcode & 0x00FF;
				pc += 2;
				break;
			case 0xA000: //ANNN, sets I to the adress NNN
				I = opcode & 0x0FFF; //Extract 3 last bytes of the opcode
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
}	
