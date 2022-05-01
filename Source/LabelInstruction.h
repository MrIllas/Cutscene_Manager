#pragma once
#include "CutInstruction.h"

class LabelInstruction : public CutInstruction
{
public:
	LabelInstruction(std::string tag, std::string text, float time) : CutInstruction (time)
	{

		state = ONCE;
		subInstruction = ONE;
	}

	~LabelInstruction()
	{

	}

private:
};