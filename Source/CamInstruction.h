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
	/*Camera*/
	CamInstruction(int posX, int posY, float time) : CutInstruction(time)
	{
		position = { posX, posY };

		state = ONCE;
		subInstruction = ONE;
		//Start();
	}

	/*CameraTarget*/
	CamInstruction(std::string tag, float time) : CutInstruction(time)
	{
		tagged = tag;

		state = ONCE;
		subInstruction = TWO;
	}
	/*CameraDisplacement*/
	CamInstruction(float speedX, float speedY, float time) : CutInstruction(time)
	{
		speed = { speedX, speedY };

		state = CONTINUOUS;
		subInstruction = THREE;
	}

	~CamInstruction()
	{
	}

	void Play(float dt = 0.0f) override
	{
		if (EXECUTED) return;
		//else if (CONTINUOUS) 
	
		app->renderer->camera->ReleaseTarget();

		switch (subInstruction)
		{
		case ONE://Position Setting
			
			app->renderer->camera->SetPosition(position);
			break;
		case TWO://Camera focus
			app->renderer->camera->SetTarget(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));
			break;
		case THREE://Camera displacement
			app->renderer->camera->x -= speed.x * dt;
			app->renderer->camera->y -= speed.y * dt;
			
			break;
		}
		
		if (state == ONCE)
		{
			state = EXECUTED;
		}
	}

private:
	iPoint position;
	std::string tagged = "";
	fPoint speed;
};
