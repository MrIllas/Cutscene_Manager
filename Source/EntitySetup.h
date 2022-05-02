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
	void SetAnimation(int direction);

	void SetPosition(fPoint position);

public:
	Animation animations[11];

	int currentAnimation = 0;

};

