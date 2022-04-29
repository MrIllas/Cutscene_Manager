#pragma once

#include "External/PugiXml/src/pugixml.hpp"

#include "CutInstruction.h"

enum Cut_Element
{
	INVALID,
	CAMERA,
	WAIT
};

class CutsceneContainer
{
public:
	CutsceneContainer();
	~CutsceneContainer();

	void Start();

	void AddInstruction(pugi::xml_node* element);
	float currentTime();

	bool Next();
	bool isContinuous();
	void PlayInstruction();

private:
	Cut_Element resolveElement(std::string input);

public:
	bool played = false;

private:
	List<CutInstruction*> instructions;
	ListItem<CutInstruction*>* item = nullptr;

};

