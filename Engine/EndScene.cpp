#include "stdafx.h"
#include "EndScene.h"

EndScene::EndScene(int score) {
	this->score = score;

	background = new Background();
	AddObject(background);

	menuButton = new Sprite("Resources/Image/in.png");
	menuButton->setScale(0.7, 0.7);
	AddObject(menuButton);
	menuButton->setPos(SCREEN_WIDTH / 2 - menuButton->getWidth() * 0.7 / 2, 350);

	for (int i = 0; i < 4; i++) {
		numArray[i] = new Number();
		numArray[i]->setScale(1.5, 1.5);
		numArray[i]->setPos(SCREEN_WIDTH / 2 - 150 + 75 * i, 100);
		AddUI(numArray[i]);
	}

	numArray[0]->setNum(score / 1000);
	numArray[1]->setNum(score / 100 % 10);
	numArray[2]->setNum(score / 10 % 10);
	numArray[3]->setNum(score % 10);
}

EndScene::~EndScene() {

}

void EndScene::Render() {
	background->Render();
	menuButton->Render();
	for (int i = 0; i < 4; i++)
		numArray[i]->Render();
}

void EndScene::Update(float dTime) {
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		if (menuButton->IsPointInRect(inputManager->GetMousePos())) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}
	}
}