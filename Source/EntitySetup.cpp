#include "EntitySetup.h"

EntitySetup::EntitySetup(std::string tag) : GameObject("EntitySetup", tag)
{

}

EntitySetup::~EntitySetup()
{

}

void EntitySetup::Start()
{

}

void EntitySetup::PostUpdate()
{
	animations[currentAnimation].Update();
	renderObjects[0].section = animations[currentAnimation].GetCurrentFrame();

	currentAnimation = 0;

	GameObject::PostUpdate();
}

void EntitySetup::CleanUp()
{

}

void EntitySetup::SetAnimation(int direction)
{
	currentAnimation = direction;
}

void EntitySetup::SetPosition(fPoint position)
{
	this->position = position;
}