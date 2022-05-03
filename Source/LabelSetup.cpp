#include "LabelSetup.h"
#include "ModulePhysics.h"
#include "Trigger.h"
#include "Text.h"

#include <iostream>

LabelSetup::LabelSetup(std::string tag, iPoint textPos, float size) : GameObject("EntitySetup", tag)
{
	textPosition = textPos;
	scale = size;
	Start();
}

LabelSetup::~LabelSetup()
{

}

void LabelSetup::Start()
{
	text = new Text(textPosition, sentence, "defaultFont", scale);
}

void LabelSetup::PreUpdate()
{
	if (txtUpdated)
	{
		text->SetText(sentence);
		text->position = textPosition;
		txtUpdated = false;
	}
}

void LabelSetup::Update()
{
}

void LabelSetup::PostUpdate()
{
	GameObject::PostUpdate();
}

void LabelSetup::CleanUp()
{
	text->~Text();
}

void LabelSetup::SetText(std::string text)
{
	sentence = text;
	txtUpdated = true;
}