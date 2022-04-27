#include "TestScene.h"
#include "Particle.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "CommonTree.h"
#include "ModuleWindow.h"

TestScene::TestScene() : SceneGame("testScene")
{

}

TestScene::~TestScene()
{
}

bool TestScene::Start()
{


    Scene::Start();    
    
    return true;
}

bool TestScene::PreUpdate()
{

    if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetControllerButton(BUTTON_START) == KEY_DOWN) app->TogglePause(!app->isPause);

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