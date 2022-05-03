#pragma once
#include "CutInstruction.h"
#include "Scene.h"
#include "ModuleScene.h"

class LabelInstruction : public CutInstruction
{
public:
	LabelInstruction(std::string tag, std::string text, float time) : CutInstruction (time)
	{
		tagged = tag;
		this->text = text;
		this->time = time;

		state = CONTINUOUS;
		subInstruction = ONE;
	}

	LabelInstruction(std::string tag) : CutInstruction(time)
	{
		tagged = tag;
		
		time = 0.0f;

		state = ONCE;
		subInstruction = TWO;
	}

	~LabelInstruction()
	{

	}

	void Play(float dt = 0.0f, bool JumpCut = false) override
	{
		if (EXECUTED) return;

		LabelSetup* aux = aux = dynamic_cast<LabelSetup*>(app->scene->scenes[app->scene->currentScene]->GetGameObjectByTag(tagged));

		switch (subInstruction)
		{
			case ONE:				
				aux->SetText(text);

				break;
			case TWO:
				aux->SetText("");

				break;
		}

		if (state = ONCE)
		{
			state = EXECUTED;
		}
	}

private:
	std::string text = "NONE";
};