#pragma once

#include "External/PugiXml/src/pugixml.hpp"

#include "CutInstruction.h"
#include "EntitySetup.h"
#include "LabelSetup.h"

enum Cut_Element
{
	INVALID,
	ENTITIES,
	LABEL,
	WAIT,
	CAMERA,
	CAMERA_TARGET,
	CAMERA_DISPLACEMENT,
	ENTITY_MOVE,
	LABEL_WRITE
	
};

enum Animation_Setup
{
	WALK_UP,
	WALK_DOWN,
	WALK_LEFT,
	WALK_RIGHT,
	ATTACK,
	A_ONE,
	A_TWO,
	A_THREE,
	A_FOUR,
	A_FIVE
};

class CutsceneContainer
{
public:
	CutsceneContainer();
	~CutsceneContainer();

	void Start();

	void AddSetup(pugi::xml_node* element);

	void AddInstruction(pugi::xml_node* element);
	float currentTime();

	bool Next();
	bool isContinuous();
	void PlayInstruction();
	void PlayCInstruction(float dt);

	void ClearCutscene();

private:
	Cut_Element resolveElement(std::string input);
	Animation_Setup resolveAnimation(std::string input);
public:
	bool played = false;

private:
	List<CutInstruction*> instructions;
	List<EntitySetup*> entities;
	ListItem<CutInstruction*>* item = nullptr;

};

