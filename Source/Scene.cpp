#include "Scene.h"
#include "ModuleRender.h"
#include "ModuleEvents.h"

Scene::Scene(std::string name)
{
	app = Application::GetInstance();
	this->name = name;
}

Scene::~Scene()
{
}

bool Scene::InitScene()
{
	return true;
}

bool Scene::Start()
{
	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (gameObjects[i])
		{
			gameObjects[i]->Start();
		}
	}

	return true;
}

bool Scene::PreUpdate()
{
	if (app->isPause) return true;

	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (!gameObjects[i]) continue;

		if (gameObjects[i]->pendingToDelete)
		{
			DestroyGameObject(gameObjects[i]);
		}

		else if (gameObjects[i]->enable)gameObjects[i]->PreUpdate();
	}

	for (int i = 0; i < texts.count(); i++)
	{
		if (!texts[i]) continue;

		if (texts[i]->pendingToDelate) DestroyText(texts[i]);

		else texts[i]->PreUpdate();
	}

	return true;
}

bool Scene::Update()
{
	if (app->isPause) return true;

	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (gameObjects[i] && gameObjects[i]->enable) gameObjects[i]->Update();
	}

	for (int i = 0; i < texts.count(); i++)
	{
		if (texts[i]) texts[i]->Update();
	}

	return true;
}

bool Scene::PostUpdate()
{
	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (gameObjects[i] && gameObjects[i]->enable) gameObjects[i]->PostUpdate();
	}

	for (int i = 0; i < texts.count(); i++)
	{
		if (texts[i]) texts[i]->PostUpdate();
	}

	return true;
}

bool Scene::CleanUp()
{
	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (gameObjects[i])
		{		
			gameObjects[i]->CleanUp();
		}
	}

	gameObjects.clearPtr();

	texts.clearPtr();

	if (app->renderer->camera != nullptr)
	{
		app->renderer->camera->ReleaseTarget();
	}

	return true;
}

void Scene::CleanCutscene()
{
	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (!gameObjects[i]->name.compare("EntitySetup"))
		{
			gameObjects[i]->CleanUp();
			RELEASE(gameObjects[i]);
			gameObjects[i] = nullptr;
			gameObjects.del(gameObjects.At(i));
			i--;
		}
	}
}

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.add(gameObject);
}

GameObject* Scene::GetGameObjectByTag(std::string tag)
{
	for (int i = 0; i < gameObjects.count(); i++)
	{
		if (!gameObjects[i]) continue;

		if (gameObjects[i]->tag == tag)
		{
			return gameObjects[i];
		}
	}

	return nullptr;
}

void Scene::AddText(Text* text)
{
	texts.add(text);
}

void Scene::DestroyGameObject(GameObject* gameObject)
{
	int index = gameObjects.find(gameObject);

	if (index >= 0)
	{
		gameObject->CleanUp();
		gameObjects.delPtr(gameObjects.At(index));
	}
}

void Scene::DestroyText(Text* text)
{
	int index = texts.find(text);

	if (index >= 0)
	{
		texts.delPtr(texts.At(index));
	}
}

void Scene::SetSaveData()
{
}

void Scene::LoadSaveData(pugi::xml_node save)
{
}