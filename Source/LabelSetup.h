#pragma once
#include "GameObject.h"
#include "Text.h"


class LabelSetup : public GameObject
{
public:
	LabelSetup(std::string tag, iPoint textPos = { 255 , 20 }, int size = 25);
	~LabelSetup();

	void Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

	void SetText(std::string text);

private:

	std::string sentence = "None";

	iPoint textPosition = { 0,0 };

	Text* text = nullptr;

	bool txtUpdated = false;
};

