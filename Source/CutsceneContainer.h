#pragma once

#include "External/PugiXml/src/pugixml.hpp"

#include "CutInstruction.h"
#include "EntitySetup.h"
#include "LabelSetup.h"
#include "ImageSetup.h"

enum Cut_Element
{
	INVALID,
	ENTITIES,
	LABEL,
	IMAGE,
	WAIT,
	JUMP,
	CAMERA,
	CAMERA_TARGET,
	CAMERA_DISPLACEMENT,
	ENTITY_MOVE,
	LABEL_WRITE,
	LABEL_CLEAR,
	PARALLEL	
};

enum Animation_Setup
{
	IDLE,
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
	CutInstruction* ReturnInstruction(pugi::xml_node* element);
	float currentTime();

	bool Next();
	bool IsContinuous();
	bool IsJump();
	void PlayInstruction(bool jumpCut = false);
	void PlayCInstruction(float dt, bool jumpCut = false);

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

	iPoint camInit = { 0,0 };

	Application* app = nullptr;
};

