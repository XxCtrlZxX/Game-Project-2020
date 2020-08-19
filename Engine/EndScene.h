#pragma once

#include "Scene.h"
#include "MainScene.h"
#include "Background.h"
#include "Number.h"
#include "Sprite.h"

class EndScene : public Scene
{
private:
	Background* background;
	Number* numArray[4];
	Sprite* menuButton;

	int score;

public:
	EndScene(int score);
	~EndScene();

	void Render();
	void Update(float dTime);
};

