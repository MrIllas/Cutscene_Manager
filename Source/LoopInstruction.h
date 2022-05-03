#pragma once
#include "CutInstruction.h"
#include "Timer.h"


class LoopInstruction : public CutInstruction
{
public:
	LoopInstruction(int iterations, float time = 0.0f) : CutInstruction(time)
	{

		ite = iterations;

		state = CONTINUOUS;
		subInstruction = LOOPCUT;
	}

	~LoopInstruction()
	{

	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{

		if (JumpCut)
		{
			for(cite; cite <= ite; ++cite)
			{
				while (item != nullptr)
				{
					item->data->Play(innerClock.getDeltaTime(), JumpCut);

					item = item->next;
				}
			}
			subInstruction = ONE;
			return;
		}


		if (item == nullptr && cite <= ite) 
		{
			item = instructions.start;
			item->data->Play(innerClock.getDeltaTime(), JumpCut);
			cleaned = false;
			cite++;
		}

		if (!cleaned)
		{
			innerClock.Reset();
			cleaned = true;
		}

		if (item->data->time < innerClock.getDeltaTime())
		{
			cleaned = false;

			item = item->next;

			if (item == nullptr) return;

			if (item->data->state != CONTINUOUS)
			{
				item->data->Play(innerClock.getDeltaTime());
			}
		}

		if (item->data->state == CONTINUOUS)
		{
			item->data->Play(innerClock.getDeltaTime());
		}

	}

	void AddInstruction(CutInstruction* instruction)
	{
		instructions.add(instruction);

		time += (instruction->time * ite);
	}

private:
	List<CutInstruction*> instructions;
	ListItem<CutInstruction*>* item;
	Timer innerClock;

	int cite = 0;
	int ite = 0;

	bool cleaned = false;
};