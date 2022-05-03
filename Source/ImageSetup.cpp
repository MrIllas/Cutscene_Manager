#include "ImageSetup.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


ImageSetup::ImageSetup(std::string tag,std::string path, fPoint imgPos, float scale) : GameObject ("EntitySetup", tag)
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
	Application::GetInstance()->renderer->AddTextureRenderQueue(tex, position, { 0 , 0, 0, 0 }, scale, 3, 0, 0, SDL_FLIP_NONE, 0.0f);

	GameObject::PostUpdate();
}

