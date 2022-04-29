#pragma once
#include "CutInstruction.h"
#include "Point.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "Scene.h"

#include <iostream>

class CamInstruction : public CutInstruction
{
public:
	CamInstruction(int posX, int posY, float time) : CutInstruction(time)
	{
		position = { posX, posY };
		state = ONCE;
		subInstruction = ONE;
		//Start();
	}

	CamInstruction(std::string tag, float time) : CutInstruction(time)
	{
		tagged = tag;

		state = ONCE;
		subInstruction = TWO;
	}

	~CamInstruction()
	{
	}

	void Play() override
	{
		if (EXECUTED) return;

		switch (subInstruction)
		{
		case ONE://Position Setting
			app->renderer->camera->SetPosition(position);
			break;
		case TWO://Camera displace focus
			app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged);
			break;
		}
		

		state = EXECUTED;
	}

private:
	iPoint position;
	std::string tagged = "";
};
