#pragma once
#include "GameObject.h"
#include "Animation.h"


class EntitySetup : public GameObject
{
public:
	EntitySetup(std::string tag);

	~EntitySetup();

	void Start() override;

	void PostUpdate() override;

	void CleanUp() override;

public:
	void SetAnimation();

	void SetPosition(iPoint position);

public:
	Animation animations[10];

};

