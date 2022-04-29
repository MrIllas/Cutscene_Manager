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

	void Play() override
	{

	}
};