#pragma once
#include "CutInstruction.h"
#include "ModuleInput.h"

class WaitInstruction : public CutInstruction
{
public:
	WaitInstruction(float time) : CutInstruction(time)
	{

		state = ONCE;
		subInstruction = ONE;
	}

	WaitInstruction() : CutInstruction(time)
	{
		time = 0.0f;
		state = CONTINUOUS;
		subInstruction = JUMPCUT;
	}

	~WaitInstruction()
	{
	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{
		if (EXECUTED) return;
		
		switch (subInstruction)
		{
			case ONE:
				//WAITING :D


				break;

			case TWO: // Waiting for a key
				//Not implemented

				if (app->input->GetKey(SDL_NUM_SCANCODES) == KEY_DOWN)
				{
					
				}

				break;
		}

		if (state = ONCE)
		{
			state = EXECUTED;
		}
	}
};