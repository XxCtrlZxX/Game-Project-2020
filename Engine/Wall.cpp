#include "stdafx.h"
#include "Wall.h"

Wall::Wall(const char* path) {
	wall = new Sprite(path);
	AddChild(wall);

	rect = wall->getRect();
}

Wall::~Wall() {

}

void Wall::Render() {
	Object::Render();
	wall->Render();
}

void Wall::Update(float dTime) {
	Object::Update(dTime);
}

Sprite* Wall::getSprite() {
	return wall;
}