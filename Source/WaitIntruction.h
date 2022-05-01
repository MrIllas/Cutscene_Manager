#pragma once
#include "CutInstruction.h"

class WaitInstruction : public CutInstruction
{
public:
	WaitInstruction(float time) : CutInstruction(time)
	{
	}

	~WaitInstruction()
	{
	}

	void Play(float dt = 0.0f) override
	{
		std::cout << "Waiting" << std::endl;
	}
};