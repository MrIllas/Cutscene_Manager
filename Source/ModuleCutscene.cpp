#include "ModuleCutscene.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include <iostream>

ModuleCutscene::ModuleCutscene()
{
	name = "cutscene";

	Start();
}

ModuleCutscene::~ModuleCutscene()
{
}

bool ModuleCutscene::Init(pugi::xml_node& config)
{
	this->config = config;

	folder = (config.child("folder").child_value());

	return true;
}

bool ModuleCutscene::Start()
{
	bool ret = true;


	return ret;
}

UpdateStatus ModuleCutscene::PreUpdate()
{
	if (!playing) return UpdateStatus::UPDATE_CONTINUE;

	//Skip / Cut cutscene
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		container.ClearCutscene();
		playing = false;
		jumpCut = false;
	}

	//Jump
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		jumpCut = true;

		if (container.IsContinuous())
		{
			container.PlayCInstruction(clock.getDeltaTime(), jumpCut);
		}
	}


	return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleCutscene::Update()
{
	//std::cout << clock.getDeltaTime() << std::endl;
	//clock.Reset();
	if(!playing) return UpdateStatus::UPDATE_CONTINUE;

	if (delay <= clock.getDeltaTime() || (jumpCut && !container.isLoop())) //Time passed
	{
		playing = container.Next();

		//Returns in case there is no instruction at all
		if (!playing) return UpdateStatus::UPDATE_CONTINUE;

		delay = container.currentTime();// *1000;
		clock.Reset();
		

		if (!container.IsContinuous())
		{
			container.PlayInstruction(jumpCut);
		}
		else if (container.IsJump())
		{ //JumpCut Finish
			jumpCut = false;
			//return UpdateStatus::UPDATE_CONTINUE;
		}
	}
	
	if (container.IsContinuous())
	{
		container.PlayCInstruction(clock.getDeltaTime(), jumpCut);
	}

	return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleCutscene::PostUpdate()
{

	return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleCutscene::Load(std::string filename)
{
	if (playing) return false;
	bool ret = true;

	std::string tmp = folder + filename;

	pugi::xml_document cutFile;
	pugi::xml_parse_result result = cutFile.load_file(tmp.c_str());

	if (result == NULL)
	{
		LOG("Could not load cutscene xml file %s. pugi error: %s", filename, result.description());
		ret = false;
	}

	if (!ret) return ret;

	container.~CutsceneContainer();
	container = CutsceneContainer();

	pugi::xml_node node = cutFile.child("cutscene");
	pugi::xml_node element = node.first_child();

	std::string setup = element.name();
	//Loads Entities and other additional things into the container
	if (!setup.compare("Setup"))
	{
		pugi::xml_node setUpElement = element.first_child();
		while (setUpElement != NULL)
		{
			container.AddSetup(&setUpElement);
			setUpElement = setUpElement.next_sibling();
		}
		element = element.next_sibling();
	}

	//Loads Instructions into the container
	while (element != NULL)
	{
		container.AddInstruction(&element);
		element = element.next_sibling();
	}

	return ret;
}

void ModuleCutscene::Play()
{
	playing = true;
	jumpCut = false;

	clock.Reset();
	delay = 0.0f;
}

void ModuleCutscene::GetSaveData(pugi::xml_document& save)
{

}

void ModuleCutscene::LoadSaveData(pugi::xml_document& save)
{

}