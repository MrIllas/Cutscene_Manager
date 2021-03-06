#pragma once
#include "CutInstruction.h"
#include "Scene.h"
#include "ModuleScene.h"
#include "Point.h"

#include "Application.h"

class EntityInstruction : public CutInstruction
{
public:
	EntityInstruction(std::string tag, int speedX, int speedY, float time = 1.0f) : CutInstruction(time)
	{
		tagged = tag;
		speed = { speedX, speedY };

		maxNum = time / 0.0166666666666667f;

		state = CONTINUOUS;
		subInstruction = ONE;
	}

	EntityInstruction(std::string tag, int name) : CutInstruction(time)
	{
		time = 0.00f;
		tagged = tag;
		anim = name;

		state = ONCE;
		subInstruction = TWO;
	}

	~EntityInstruction()
	{
	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{
		if (EXECUTED) return;
		
		EntitySetup* aux = nullptr;
		fPoint iAux = { 0, 0 };

		switch (subInstruction)
		{
			case ONE: //Makes Entity Walk
				num++;

				aux = dynamic_cast<EntitySetup*>(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));
				iAux = { 0 , 0 };

				if (JumpCut)
				{
					maxNum = maxNum - num;
					speed.x = speed.x * maxNum;
					speed.y = speed.y * maxNum;
				}
			
				iAux = { aux->GetPosition().x + (speed.x * Application::GetInstance()->dt), aux->GetPosition().y + (speed.y * Application::GetInstance()->dt) };

				if (speed.y < 0)
				{ //Move Up
					aux->SetAnimation(WALK_UP);
				}
				if (speed.y > 0)
				{ //Move Down
					aux->SetAnimation(WALK_DOWN);
				}
				if (speed.x > 0)
				{ //Move Right
					aux->SetAnimation(WALK_RIGHT);
				}
				if (speed.x < 0)
				{ //Move Left
					aux->SetAnimation(WALK_LEFT);
				}

				aux->SetPosition(iAux);
				break;

			case TWO: //Sets an Animation

				aux = dynamic_cast<EntitySetup*>(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));

				aux->SetAnimation(anim);

				break;
		}

		if (state == ONCE)
		{
			state = EXECUTED;
		}
	}

private:
	iPoint position;
	iPoint speed;
	int num = 0;
	int maxNum = 0;
	int anim = 0;
};
