#include "exceptions.h"

unknownOpcodeException::unknownOpcodeException(int code, int instruction)
{
	rawOpcode = code;
	opcodeInstruction = instruction;
}
