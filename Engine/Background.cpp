#include "stdafx.h"
#include "Background.h"

Background::Background() {
	background = new Sprite("Resources/Image/mario-background.png");
	background->setScale(0.5, 0.5);
	AddChild(background);
}

Background::~Background() {

}

void Background::Render() {
	Object::Render();
	background->Render();
}

void Background::Update(float dTime) {
	Object::Update(dTime);
}