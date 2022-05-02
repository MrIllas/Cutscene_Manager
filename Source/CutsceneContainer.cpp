#include "CutsceneContainer.h"
#include "CamInstruction.h"
#include "WaitIntruction.h"
#include "EntityInstruction.h"
#include "LabelInstruction.h"
#include "ParallelInstruction.h"
#include "LoopInstruction.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include <map>

CutsceneContainer::CutsceneContainer()
{
	app = Application::GetInstance();

	camInit = { app->renderer->camera->x, app->renderer->camera->y };
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

void CutsceneContainer::AddSetup(pugi::xml_node* element)
{
	std::string value = element->name();
	pugi::xml_node childElement; 

	switch (resolveElement(value))
	{
		case ENTITIES:
			
			childElement = element->first_child();

			while (childElement != NULL)
			{
				//Attributes collection
				std::string tag = childElement.attribute("tag").as_string();

				EntitySetup* entity = new EntitySetup(tag);

				fPoint position = { 0 , 0 };

				int width = 32;
				int height = 32;
				int layer = 1;
				float orderInLayer = 3.0f;
				float scale = 1;
				std::string path = "";

				//Position
				if (childElement.child("Position") != nullptr)
				{
					position = { childElement.child("Position").attribute("posX").as_float(),
								childElement.child("Position").attribute("posY").as_float() };
				}

				entity->SetPosition(position);

				//Texture
				if (childElement.child("Texture") != nullptr)
				{
					pugi::xml_node textureElement = childElement.child("Texture");
					/*width = textureElement.attribute("width").as_int();
					height = textureElement.attribute("height").as_int();*/
					layer = textureElement.attribute("layer").as_int();
					orderInLayer = textureElement.attribute("orderInLayer").as_float();
					scale = textureElement.attribute("scale").as_float();
					path = textureElement.attribute("path").as_string();
				}

				//Entity declaration
				entity->renderObjects[0].InitAsTexture(app->textures->Load(path), { 0 , 0 }, { 0, 0, 0, 0 }, scale, layer, orderInLayer);
				//entity->renderObjects[0].textureCenterX = width;
				//entity->renderObjects[0].textureCenterY = height;

				//Animations
				if (childElement.child("Animations") != nullptr)
				{
					pugi::xml_node animationElement = childElement.child("Animations").first_child();

					while (animationElement != NULL)
					{
						std::string name = animationElement.attribute("name").as_string();
						bool loop = animationElement.attribute("loop").as_bool();
						int frames = animationElement.attribute("frames").as_int();
						width = animationElement.attribute("width").as_int();
						height = animationElement.attribute("height").as_int();
						int line = animationElement.attribute("line").as_int();
						float speed = animationElement.attribute("speed").as_float();

						for (int i = 0; i < frames; i++)
						{
							entity->animations[resolveAnimation(name)].PushBack({ width * i, line * height, width, height });
							
						}

						entity->animations[resolveAnimation(name)].loop = loop;
						entity->animations[resolveAnimation(name)].hasIdle = false;
						entity->animations[resolveAnimation(name)].speed = speed;

						animationElement = animationElement.next_sibling();
					}
				}


				//entities.add(entity);

				childElement = childElement.next_sibling();
			}
			break;
		case LABEL:
			if (element != nullptr) {
				LabelSetup* lbl = new LabelSetup(element->attribute("tag").as_string(),
					{ element->attribute("posX").as_int(), element->attribute("posY").as_int() },
					element->attribute("scale").as_int());
			};
			

			/*if (element->first_child() != nullptr)
			{
				lbl->SetText(element->first_child().name());
			}*/

			break;
		case IMAGE:
			ImageSetup* img = new ImageSetup(element->attribute("tag").as_string(),
											 element->attribute("path").as_string(),
											{ element->attribute("posX").as_float(), element->attribute("posY").as_float() },
											 element->attribute("scale").as_int()
			);
			break;
	}
}

void CutsceneContainer::AddInstruction(pugi::xml_node* element)
{
	instructions.add(ReturnInstruction(element));
}

CutInstruction* CutsceneContainer::ReturnInstruction(pugi::xml_node* element)
{
	std::string value = element->name();
	pugi::xml_node ele;
	switch (resolveElement(value))
	{
		case CAMERA:
			return new CamInstruction(element->attribute("posX").as_int(),
												element->attribute("posY").as_int(),
												element->attribute("time").as_float()
			);
			break;
		case CAMERA_TARGET:
			return new CamInstruction(element->attribute("tag").as_string(),
												element->attribute("time").as_float()
			);
			break;
		case CAMERA_DISPLACEMENT:
			return new CamInstruction(element->attribute("speedX").as_float(),
												element->attribute("speedY").as_float(),
												element->attribute("time").as_float()
			);
			break;
		case WAIT:
			return new WaitInstruction(element->attribute("time").as_float());
			break;
		case JUMP:
			return new WaitInstruction();
			break;
		case ENTITY_MOVE:
			return new EntityInstruction(element->attribute("tag").as_string(),
												   element->attribute("speedX").as_int(),
												   element->attribute("speedY").as_int(),
												   element->attribute("time").as_float()
			);
			break;
		case LABEL_WRITE:
			return new LabelInstruction(element->attribute("tag").as_string(),
												  element->attribute("text").as_string(),
												  element->attribute("time").as_float()
			);
			break;
		case LABEL_CLEAR:
			return new LabelInstruction(element->attribute("tag").as_string());
			break;
		case PARALLEL:
			if (element != nullptr) {
				ele = element->first_child();

				ParallelInstruction* pll = new ParallelInstruction(2.0f);

				while (ele != NULL)
				{
					pll->AddInstruction(ReturnInstruction(&ele));

					ele = ele.next_sibling();
				}

				return pll;
			}
			break;
		case LOOP:
			if (element != nullptr)
			{
				ele = element->first_child();

				LoopInstruction* lp = new LoopInstruction(element->attribute("ite").as_int());

				while (ele != NULL)
				{
					lp->AddInstruction(ReturnInstruction(&ele));

					ele = ele.next_sibling();
				}
				
				return lp;
			}
			break;
		case INVALID:
		default:
			return nullptr;
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
		if (item) return true;
		else return false;
	}
	
	if (item->next != nullptr)
	{
		item = item->next;
		played = false;
		return true;
	}else
	//if (item->next == nullptr)
	{
		ClearCutscene();

		return false;
	}
	//return true;
}

void CutsceneContainer::ClearCutscene()
{
	app->scene->scenes[app->scene->currentScene]->CleanCutscene();

	if (app->renderer->camera != nullptr)
	{
		app->renderer->camera->ReleaseTarget();
	}

	app->renderer->camera->x = camInit.x;
	app->renderer->camera->y = camInit.y;

}

/// <summary>
/// 
/// </summary>
/// <returns>Is Continuous = TRUE
///			Isn't Continuous = FALSE</returns>
bool CutsceneContainer::IsContinuous()
{
	if (item->data == nullptr) return false;

	if(item->data->state == CONTINUOUS)
	{
		return true;
	}

	return false;
}

bool CutsceneContainer::IsJump()
{
	if (item->data == nullptr) return false;

	if (item->data->subInstruction == JUMPCUT)
	{
		return true;
	}

	return false;
}

bool CutsceneContainer::isLoop()
{
	if (item->data == nullptr) return false;

	if (item->data->subInstruction == LOOPCUT)
	{
		return true;
	}

	return false;
}

void CutsceneContainer::PlayInstruction(bool jumpCut)
{
	if (played) return;

	item->data->Play(0.0f, jumpCut);
	played = false;
}

void CutsceneContainer::PlayCInstruction(float dt, bool jumpCut)
{
	item->data->Play(dt, jumpCut);
}

Cut_Element CutsceneContainer::resolveElement(std::string input)
{
	std::map<std::string, Cut_Element> eleStrings{
		{"Entities", ENTITIES},
		{"Label", LABEL},
		{"Image", IMAGE},
		{"Wait", WAIT},
		{"Jump", JUMP},
		{"Camera", CAMERA},
		{"CameraTarget", CAMERA_TARGET},
		{"CameraDisplacement", CAMERA_DISPLACEMENT},
		{"EntityMove", ENTITY_MOVE},
		{"LabelWrite", LABEL_WRITE},
		{"LabelClear", LABEL_CLEAR},
		{"Parallel", PARALLEL},
		{"Loop", LOOP}
	};

	auto itr = eleStrings.find(input);
	if (itr != eleStrings.end())
	{
		return itr->second;
	}

	return INVALID;
}

Animation_Setup CutsceneContainer::resolveAnimation(std::string input)
{
	std::map<std::string, Animation_Setup> eleStrings{
		{"Idle", IDLE},
		{"Walk_up", WALK_UP},
		{"Walk_down", WALK_DOWN},
		{"Walk_left", WALK_LEFT},
		{"Walk_right", WALK_RIGHT},
		{"Attack", ATTACK},
		{"A_one", A_ONE},
		{"A_two", A_TWO},
		{"A_three", A_THREE},
		{"A_four", A_FOUR},
		{"A_five", A_FIVE}
	};

	auto itr = eleStrings.find(input);
	if (itr != eleStrings.end())
	{
		return itr->second;
	}

	return A_ONE;
}

