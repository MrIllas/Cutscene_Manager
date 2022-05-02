#pragma once
#include "CutInstruction.h"
#include "Timer.h"


class LoopInstruction : public CutInstruction
{
public:
	LoopInstruction(float time, int iterations) : CutInstruction(time)
	{

	}

	~LoopInstruction()
	{

	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{

		if (!cleaned)
		{
			innerClock.Reset();
			cleaned = true;
		}

		for (int i = 0; i < instructions.count(); ++i)
		{
			std::cout << innerClock.getDeltaTime() << std::endl;
			if (instructions[i]->time >= innerClock.getDeltaTime())
			{
				instructions[i]->Play(dt, JumpCut);
			}
		}
	}
private:
	List<CutInstruction*> instructions;
	Timer innerClock;

	bool cleaned = false;
};