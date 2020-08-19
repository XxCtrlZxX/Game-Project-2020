#pragma once

#include "Object.h"
#include "Sprite.h"

class Wall : public Object
{
private:
	Sprite* wall;

public:
	Wall(const char* path);
	~Wall();

	void Update(float dTime);
	void Render();

	Sprite* getSprite();
};

