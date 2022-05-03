#pragma once
#include "CutInstruction.h"
#include "Timer.h"


class ParallelInstruction : public CutInstruction
{
public:
	ParallelInstruction(float time) : CutInstruction(time)
	{
		state = CONTINUOUS;
		subInstruction = ONE;
	}

	~ParallelInstruction()
	{
		instructions.clearPtr();
	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{

		if (!cleaned)
		{
			innerClock.Reset();
			cleaned = true;
		}

		int y = 0;

		for (int i = 0; i < instructions.count(); ++i)
		{
			std::cout << dt << std::endl;
			if (instructions[i]->time >= dt)
			{
				instructions[i]->Play(dt, JumpCut);
			}
			else ++y;
		}

		if (y >= instructions.count())
		{
			state = ONCE;
		}
	}

	void AddInstruction(CutInstruction* instruction)
	{
		instructions.add(instruction);

		if (instruction->time > time)
		{
			time = instruction->time;
		}
	}

private:
	List<CutInstruction*> instructions;
	Timer innerClock;

	bool cleaned = false;
};