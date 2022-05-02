#include "ImageSetup.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


ImageSetup::ImageSetup(std::string tag,std::string path, iPoint imgPos, int scale) : GameObject ("EntitySetup", tag)
{
	position = imgPos;
	this->scale = scale;
	this->path = path;

	ImageSetup::Start();
}

ImageSetup::~ImageSetup()
{

}

void ImageSetup::Start()
{
	//renderObjects[0].InitAsTexture(Application::GetInstance()->textures->Load(path), { 0, 0 }, { 0, 0, 0, 0 }, scale, 4, 10);
	tex = Application::GetInstance()->textures->Load(path);
	
}

void ImageSetup::CleanUp()
{

}

void ImageSetup::PreUpdate()
{

}

void ImageSetup::Update()
{

}

void ImageSetup::PostUpdate()
{
	//renderObjects[0].section;// = { 0, 0, 140, 94 };

	Application::GetInstance()->renderer->AddTextureRenderQueue(tex, position, { 0 , 0, 0, 0 }, scale, 3, 0, 0, SDL_FLIP_NONE, 0.0f);

	GameObject::PostUpdate();
}

