#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene() {
	background = new Sprite("Resources/Image/Background.png");
	AddObject(background);
	background->setPos(SCREEN_WIDTH / 2 - background->getWidth() / 2, 0);

	title = new Sprite("Resources/Image/mainname.png");
	AddObject(title);
	title->setPos(SCREEN_WIDTH / 2 - title->getWidth() / 2, 0);

	startButton = new Sprite("Resources/Image/in.png");
	startButton->setScale(0.7, 0.7);
	AddObject(startButton);
	startButton->setPos(SCREEN_WIDTH / 2 - startButton->getWidth() * 0.7 / 2, 350);

	exitButton = new Sprite("Resources/Image/out.png");
	exitButton->setScale(0.7, 0.7);
	AddObject(exitButton);
	exitButton->setPos(SCREEN_WIDTH / 2 - exitButton->getWidth() * 0.7 / 2, 500);

	//soundManager->LoadWave("Resources/Sound/MusicSurround.wav", "Background");
	//soundManager->Play("Background", true);
}

MainScene::~MainScene() {

}

void MainScene::Render() {
	background->Render();
	title->Render();
	startButton->Render();
	exitButton->Render();
}

void MainScene::Update(float dTime) {
	Scene::Update(dTime);

	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {

		if (startButton->IsPointInRect(inputManager->GetMousePos())) {
			//sceneManager->ChangeScene(new GameScene());
			sceneManager->ChangeScene(new MyGameScene());
			return;
		}

		if (exitButton->IsPointInRect(inputManager->GetMousePos())) {
			PostQuitMessage(0);
			return;
		}

	}
}