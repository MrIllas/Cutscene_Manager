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

		maxNum = time / 0.0166666666666667f;

		state = CONTINUOUS;
		subInstruction = THREE;
	}

	~CamInstruction()
	{
	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{
		if (EXECUTED) return;
		//else if (CONTINUOUS) 		

		switch (subInstruction)
		{
		case ONE://Position Setting
			std::cout << "Camera Position set" << std::endl;
			app->renderer->camera->ReleaseTarget();
			app->renderer->camera->SetPosition(position);
			break;
		case TWO://Camera focus
			std::cout << "Camera focus" << std::endl;
			app->renderer->camera->ReleaseTarget();
			app->renderer->camera->SetTarget(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));
			break;
		case THREE://Camera displacement
			std::cout << "Displacing camera" << std::endl;

			app->renderer->camera->ReleaseTarget();



			num++;
			if (JumpCut)
			{
				maxNum = maxNum - num;
				speed.x = speed.x * maxNum;
				speed.y = speed.y * maxNum;
			}

			app->renderer->camera->x -= (speed.x * Application::GetInstance()->dt) * -1;
			app->renderer->camera->y -= (speed.y * Application::GetInstance()->dt) * -1;
			
			break;
		}
		
		if (state == ONCE)
		{
			state = EXECUTED;
		}
	}

private:
	iPoint position;
	fPoint speed;
	int num = 0;
	int maxNum = 0;
};
