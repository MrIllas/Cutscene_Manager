#pragma once
#include "CutInstruction.h"
#include "Point.h"
#include "ModuleRender.h"

#include <iostream>

class CamInstruction : public CutInstruction
{
public:
	CamInstruction(int posX, int posY, float time) : CutInstruction(time)
	{
		position = { posX, posY };
		state = ONCE;
		//Start();
	}

	~CamInstruction()
	{
	}

	void Play() override
	{
		if (EXECUTED) return;

		app->renderer->camera->SetPosition(position);

		state = EXECUTED;
	}

private:
	iPoint position;
};
