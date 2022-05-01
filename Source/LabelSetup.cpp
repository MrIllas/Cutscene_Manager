#include "LabelSetup.h"
#include "ModulePhysics.h"
#include "Trigger.h"
#include "Text.h"

#include <iostream>

LabelSetup::LabelSetup(std::string tag, iPoint textPos, int size) : GameObject("EntitySetup", tag)
{
	textPosition = textPos;

	Start();
}

LabelSetup::~LabelSetup()
{

}

void LabelSetup::Start()
{
	text = new Text(textPosition, sentence);
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