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

			GameObject* aux = app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged);
			iPoint iAux = { aux->GetPosition().x + speed.x, aux->GetPosition().y + speed.y };
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
