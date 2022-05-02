#pragma once
#include "CutInstruction.h"


class ParallelInstruction : public CutInstruction
{
public:
	ParallelInstruction(float time) : CutInstruction(time)
	{

	}

	~ParallelInstruction()
	{
			
	}
};