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
	animations[0].Update();
	renderObjects[0].section = animations[0].GetCurrentFrame();

	GameObject::PostUpdate();
}

void EntitySetup::CleanUp()
{

}

void EntitySetup::SetAnimation()
{

}

void EntitySetup::SetPosition(iPoint position)
{
	this->position = position;
}