#pragma once
#include "Module.h"
#include "CutsceneContainer.h"


class ModuleCutscene : public Module
{
public:
	ModuleCutscene();
	~ModuleCutscene();

	bool Init(pugi::xml_node&);
	bool Start();

	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	bool Cleanup();

	void GetSaveData(pugi::xml_document& save) override;

	void LoadSaveData(pugi::xml_document& save) override;

public:
	bool Load(std::string filename);
	bool LoadInstructions(pugi::xml_node instructions);
	void Play();
	//bool LoadnPlay(std::string path);

	bool Clear();

private:
	pugi::xml_document file;
	std::string folder = "";
	bool playing = false;
	bool jumpCut = false;

	CutsceneContainer container;
	float delay = 1.0f;
	Timer clock;
};

