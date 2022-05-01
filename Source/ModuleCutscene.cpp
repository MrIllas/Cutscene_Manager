#include "ModuleCutscene.h"

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
	

	return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleCutscene::Update()
{
	//std::cout << clock.getDeltaTime() << std::endl;
	//clock.Reset();
	if(!playing) return UpdateStatus::UPDATE_CONTINUE;
	//clock.Update();

	if (delay <= clock.getDeltaTime()) //Time passed
	{
		playing = container.Next();

		//Returns in case there is no instruction at all
		if (!playing) return UpdateStatus::UPDATE_CONTINUE;

		delay = container.currentTime();// *1000;
		clock.Reset();
		//std::cout << time << ", " << app->globalTime.getExecuteTime() << std::endl;
		
		if (!container.isContinuous())
		{
			container.PlayInstruction();
		}
	}
	
	if (container.isContinuous())
	{
		container.PlayCInstruction(clock.getDeltaTime());
	}

	return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleCutscene::PostUpdate()
{

	return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleCutscene::Load(std::string filename)
{
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

	clock.Reset();
	delay = 0.0f;
}

void ModuleCutscene::Pause()
{


}

void ModuleCutscene::Skip()
{

}


void ModuleCutscene::GetSaveData(pugi::xml_document& save)
{

}

void ModuleCutscene::LoadSaveData(pugi::xml_document& save)
{

}