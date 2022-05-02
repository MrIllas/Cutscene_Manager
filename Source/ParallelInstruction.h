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

		for (int i = 0; i < instructions.count(); ++i)
		{
			std::cout << innerClock.getDeltaTime() << std::endl;
			if (instructions[i]->time >= innerClock.getDeltaTime())
			{
				instructions[i]->Play(dt);
			}
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