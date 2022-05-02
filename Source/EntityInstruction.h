#pragma once
#include "CutInstruction.h"
#include "Scene.h"
#include "ModuleScene.h"
#include "Point.h"


class EntityInstruction : public CutInstruction
{
public:
	EntityInstruction(std::string tag, int speedX = 1, int speedY = 1, float time = 1.0f) : CutInstruction(time)
	{
		tagged = tag;
		speed = { speedX, speedY };

		state = CONTINUOUS;
		subInstruction = ONE;
	}

	~EntityInstruction()
	{
	}

	void Play(float dt = 0.0f) override
	{
		if (EXECUTED) return;
		
		switch (subInstruction)
		{
		case ONE://Makes Entity Walk
			std::cout << "Moving Entity" << std::endl;

			EntitySetup* aux = dynamic_cast<EntitySetup*>(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));
			iPoint iAux = { aux->GetPosition().x + speed.x, aux->GetPosition().y + speed.y };

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
		}

		if (state == ONCE)
		{
			state = EXECUTED;
		}
	}

private:
	iPoint position;
	iPoint speed;

};
