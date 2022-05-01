#pragma once

#include "Application.h"

class CamInstruction;
class WaitInstruction;


enum States
{
	EXECUTED = 0,
	CONTINUOUS,
	ONCE
};

enum SubInstruction
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE
};

class CutInstruction
{
public:
	CutInstruction()
	{
	}
	CutInstruction(float time)
	{
		this->time = time;

		Start();
	};

	virtual void Start()
	{
		app = app->GetInstance();
	}

	virtual ~CutInstruction()
	{
	}

	virtual void Play(float dt = 0.0f) {}

public:
	float time = 0;
	int state = ONCE;
	SubInstruction subInstruction = ONE;
protected:
	Application* app = nullptr;

	std::string tagged = "";
};