#pragma once
#include "GameObject.h"


class ImageSetup : public GameObject
{
public:
	ImageSetup(std::string tag, std::string path, fPoint imgPos = { 255 , 20 }, int scale = 1);
	~ImageSetup();

	void Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

	void SetImage(std::string path);

private:

	int scale = 1;
	std::string path = "";

	SDL_Texture* tex;

};

