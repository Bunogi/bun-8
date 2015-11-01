#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class unknownOpcodeException
{
	public:
		int rawOpcode;
		int opcodeInstruction;
		unknownOpcodeException(int code, int instruction);
};

#endif
