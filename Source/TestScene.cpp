#include "TestScene.h"
#include "Particle.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleMap.h"
#include "ModuleEvents.h"

#include "ModuleRender.h"

#include <iostream>

TestScene::TestScene() : SceneGame("testScene")
{

}

TestScene::~TestScene()
{
}

bool TestScene::Start()
{
    app->map->Load(TESTSCENE);


    Scene::Start();    
    
    return true;
}

bool TestScene::PreUpdate()
{

    if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetControllerButton(BUTTON_START) == KEY_DOWN) app->TogglePause(!app->isPause);

    //DEBUG KEYS
    if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
    {
        std::cout << app->renderer->camera->x << ", " << app->renderer->camera->y << std::endl;
    }

    Scene::PreUpdate();
    return true;
}

bool TestScene::Update()
{

    Scene::Update();

    return true;
}

bool TestScene::PostUpdate()
{

    Scene::PostUpdate();

    return true;
}

bool TestScene::CleanUp()
{
    app->events->TriggerEvent(GameEvent::DELETING_SCENE);

    Scene::CleanUp();
    return false;
}