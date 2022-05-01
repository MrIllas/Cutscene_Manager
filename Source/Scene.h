#ifndef __SCENE_H__
#define __SCENE_H__

#include "GameObject.h"
#include "List.h"
#include "Text.h"

class Scene
{
protected:

	int ID = 0;

	int platformLenght = 2;

	Application* app = nullptr;

	List<GameObject*> gameObjects;

	//List<SDL_Texture*> sceneTextures;

	List<Text*> texts;

public:
	// Constructor
	Scene(std::string name = "null");

	// Destructor
	~Scene();

	virtual bool InitScene();

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update();

	virtual bool PostUpdate();

	virtual bool CleanUp();
	
	void CleanCutscene();

	void AddGameObject(GameObject* gameObject);

	GameObject* GetGameObjectByTag(std::string tag);

	void AddText(Text* text);

	void DestroyGameObject(GameObject* gameObject);

	void DestroyText(Text* text);

	virtual void SetSaveData();

	virtual void LoadSaveData(pugi::xml_node save);

	int getID()
	{
		return ID;
	}

	int lastID = 0;

	int isWin = false;

	std::string name = "null";
};

#endif //_SCENE_H_