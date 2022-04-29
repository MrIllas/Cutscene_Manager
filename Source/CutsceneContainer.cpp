#include "CutsceneContainer.h"
#include "CamInstruction.h"
#include "WaitIntruction.h"

#include <map>

CutsceneContainer::CutsceneContainer()
{

}

CutsceneContainer::~CutsceneContainer()
{
	instructions.clearPtr();
	if (item != nullptr)
	{
		//delete item;
	}
	
	item = nullptr;
}

void CutsceneContainer::AddInstruction(pugi::xml_node* element)
{
	std::string value = element->name();
	switch (resolveElement(value))
	{
		case CAMERA:
			instructions.add(new CamInstruction(element->attribute("posX").as_int(),
												element->attribute("posY").as_int(),
												element->attribute("time").as_float()
			));
			break;
		case CAMERA_TARGET:
			instructions.add(new CamInstruction(element->attribute("tag").as_string(),
												element->attribute("time").as_float()
			));
			break;
		case WAIT:
			instructions.add(new WaitInstruction(element->attribute("time").as_float()));
			break;
		case INVALID:
		default:

			break;
	}
}

float CutsceneContainer::currentTime()
{
	return item->data->time;
}

bool CutsceneContainer::Next()
{
	if (item == nullptr)
	{
		item = instructions.start;
		return true;
	}

	item = item->next;
	played = false;

	if (item->next == nullptr)
	{
		return false;
	}
	return true;
}

bool CutsceneContainer::isContinuous()
{
	if (item != nullptr) return false;

	if(item->data->state == 0)
	{
		return true;
	}

	return false;
}

void CutsceneContainer::PlayInstruction()
{
	if (played) return;

	item->data->Play();
	played = false;
}

Cut_Element CutsceneContainer::resolveElement(std::string input)
{
	std::map<std::string, Cut_Element> eleStrings{
		{"Camera", CAMERA},
		{"CameraTarget", CAMERA_TARGET},
		{"Wait", WAIT}
	};

	auto itr = eleStrings.find(input);
	if (itr != eleStrings.end())
	{
		return itr->second;
	}

	return INVALID;
}

