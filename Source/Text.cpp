#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Scene.h"

Text::Text(iPoint position, std::string text, std::string font, float size) : position(position), text(text)
{
	app = Application::GetInstance();

#pragma region Init with XML

	std::string path = app->config.child("fonts").child(font.c_str()).attribute("path").as_string();

	int width = app->config.child("fonts").child(font.c_str()).attribute("width").as_int(1);

	int height = app->config.child("fonts").child(font.c_str()).attribute("height").as_int(1);

	int layer = app->config.child("fonts").child(font.c_str()).attribute("layer").as_int(1);

	float orderInLayer = app->config.child("fonts").child(font.c_str()).attribute("orderInLayer").as_float(1);

	float scale = size;  app->config.child("fonts").child(font.c_str()).attribute("scale").as_float(1);

	spaceInLetter = app->config.child("fonts").child(font.c_str()).attribute("spaceInLetter").as_int(0);

	// Init Color
	SDL_Color color;

	color.r = app->config.child("fonts").child(font.c_str()).attribute("r").as_int(255);
	color.g = app->config.child("fonts").child(font.c_str()).attribute("g").as_int(255);
	color.b = app->config.child("fonts").child(font.c_str()).attribute("b").as_int(255);
	color.a = app->config.child("fonts").child(font.c_str()).attribute("a").as_int(255);

	SetColor(color);

#pragma endregion

	//Init text
	SaveTextInAscii();

	// Load texture
	SDL_Texture* tex = app->textures->Load(path);

	// Init renderObjecy
	textRO.InitAsTexture(tex, position, { 0,0,width,height }, scale, layer, orderInLayer);
	textRO.speedRegardCamera = 0;
	textRO.name = "Text";

	// Add this text in current scen text list
	app->scene->scenes[app->scene->currentScene]->AddText(this);
}

Text::~Text()
{
}

void Text::PreUpdate()
{
}

void Text::Update()
{
	textCountTime -= app->dt;
}

void Text::PostUpdate()
{
	for (int i = 0; i < textInCode.count(); i++)
	{
		// Space in letters
		int space = 0;

		if (i > 0) space = spaceInLetter * textRO.scale * i;

		// Get Seccion for every letter
		textRO.section.x = textRO.section.w * textInCode[i];

		// Offset to the right
		int tempPosX = textRO.destRect.x;

		textRO.destRect.x = tempPosX + (i * textRO.section.w * textRO.scale) + space;

		app->renderer->AddRenderObjectRenderQueue(textRO);

		textRO.destRect.x = tempPosX;
	}
}

void Text::SetText(std::string text)
{
	this->text = text;

	SaveTextInAscii();
}

void Text::SetColor(SDL_Color color)
{
	textRO.SetColor(color);
}

void Text::ChangeDrawMode()
{
	if (textRO.speedRegardCamera < 1.0f) textRO.speedRegardCamera = 1.0f;
	else textRO.speedRegardCamera = 0.0f;
}

void Text::DrawTextStepToStep()
{

}

void Text::SaveTextInAscii()
{
	int length = text.length();

	textInCode.clear();

	for (int i = 0; i < length; ++i)
	{
		int ascii = text[i];

		for (int i = 0; i < LETTER_NUMS; i++)
		{
			if (textToAscii[i] == ascii) textInCode.add(i);
		}
	}
}