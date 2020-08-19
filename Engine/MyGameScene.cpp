#include "stdafx.h"
#include "MyGameScene.h"

MyGameScene::MyGameScene() {
	arrowLen = 0;
	jumpCount = 0;
	score = goal = 0;
	isLBtnDown = false;
	isLBtnUp = false;

	cameraPos = cameraVector = D3DXVECTOR2(0, 0);

	//----------- Background -------------//
	Background* bg1 = new Background();
	bg1->setPos(0, SCREEN_HEIGHT - 1080 * 0.5);
	Background* bg2 = new Background();
	bg2->setPos(0, SCREEN_HEIGHT - 1080 * 1.0);
	Background* bg3 = new Background();
	bg3->setPos(0, SCREEN_HEIGHT - 1080 * 1.5);
	backgroundList.push_back(bg1);
	backgroundList.push_back(bg2);
	backgroundList.push_back(bg3);
	AddObject(bg1);
	AddObject(bg2);
	AddObject(bg3);

	//------------ Player ---------------//
	player = new Player();
	player->setPos(SCREEN_WIDTH / 2, 300);
	player->setScale(0.6, 0.6);
	AddObject(player);

	//------------ Arrow ---------------//
	arrow = new Sprite("Resources/Image/arrow.png");
	arrow->setRotationCenter(0, arrow->getHeight() / 2);
	AddObject(arrow);

	//------------ Wall ---------------//
	Wall* wall = new Wall("Resources/Image/groundV.png");
	wall->setPos(0, 0);
	wallList.push_back(wall);
	AddObject(wall);

	Wall* wall2 = new Wall("Resources/Image/groundV.png");
	wall2->setPos(SCREEN_WIDTH + 400, 0);
	wallList.push_back(wall2);
	AddObject(wall2);

	Wall* wall3 = new Wall("Resources/Image/groundH.png");
	wall3->setPos(200, SCREEN_HEIGHT - 300);
	wallList.push_back(wall3);
	AddObject(wall3);

	//--------------- Number ---------------//
	for (int i = 0; i < 4; i++) {
		numArray[i] = new Number();
		numArray[i]->setPos(10 + 50 * i, 10);
		AddUI(numArray[i]);
	}

	InstantiateCoin(100);
}

MyGameScene::~MyGameScene() {

}

void MyGameScene::Render() {
	for (auto& bg : backgroundList)
		bg->Render();
	for (auto& wall : wallList)
		wall->Render();
	for (auto& coin : coinList)
		coin->Render();

	player->Render();

	if (isLBtnDown)
		arrow->Render();

	for (int i = 0; i < 4; i++)
		numArray[i]->Render();
}

void MyGameScene::Update(float dTime) {
	Scene::Update(dTime);

	CollisionCheck(); 
	cameraVector.x = Lerp(cameraPos.x, player->getPosX(), 0.5);
	CameraMove(cameraVector.x, cameraVector.y);
	UISetting();
	DeleteObject();

	//-------------------------------------------//
	int tmpY = cameraPos.y;
	if (tmpY % 201 >= 200) {
		InstantiateCoin(-100);
	}
	if (tmpY % 401 >= 400) {
		InstantiateWall(0);
		InstantiateWall(2);
		cameraPos.y = 0;
	}

	if (jumpCount < 2) {
		MouseManage();
	}
	if (player->getPosY() > SCREEN_HEIGHT) {
		sceneManager->ChangeScene(new EndScene(score));
	}
}

void MyGameScene::CameraMove(D3DXVECTOR2 vec) {
	cameraPos += vec * globalTime;

	for (auto& bg : backgroundList)
		bg->setPos(bg->getPos() + vec * globalTime * 0.5);

	for (auto& wall : wallList)
		wall->setPos(wall->getPos() + vec * globalTime);

	for (auto& coin : coinList)
		coin->setPos(coin->getPos() + vec * globalTime);

	player->setPos(player->getPos() + vec * globalTime);
}

void MyGameScene::DeleteObject() {
	for (auto iter = wallList.begin(); iter != wallList.end(); iter++) {
		if ((*iter)->getPosY() > SCREEN_HEIGHT) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = wallList.erase(iter);

			if (iter == wallList.end())
				break;
		}
	}
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if ((*iter)->getPosY() > SCREEN_HEIGHT) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end())
				break;
		}
	}
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		if ((*iter)->getPosY() > SCREEN_HEIGHT) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);

			Background* tmpBg = new Background();
			tmpBg->setPos(0, SCREEN_HEIGHT - 1080 * 1.5);
			backgroundList.push_back(tmpBg);
			AddObject(tmpBg);

			if (iter == backgroundList.end())
				break;
		}
	}
}

void MyGameScene::InstantiateCoin(float y) {
	for (int i = 2; i <= 12; i++) {
		int tmp = rand() % 4;
		bool isRed = tmp == 0;

		Coin* coin = new Coin(isRed);
		coin->setPos(100 * i, y);
		AddObject(coin);
		coinList.push_back(coin);
		goal++;
	}
}

void MyGameScene::InstantiateWall(int tmp) {
	// tmp 0: ¼¼·Î 1: °¡·Î
	if (tmp == 0) {
		Wall* wall = new Wall("Resources/Image/groundV.png");
		wall->setPos(0, 0);
		wall->setScale(1, 0.5);
		wallList.push_back(wall);
		AddObject(wall);
	}
	else if (tmp == 1) {
		Wall* wall = new Wall("Resources/Image/groundH.png");
		wall->setPos(cameraPos.x, -230);
		wall->setScale(1, 0.3);
		wallList.push_back(wall);
		AddObject(wall);
	}
	else if (tmp == 2) {
		Wall* wall = new Wall("Resources/Image/groundV.png");
		wall->setPos(SCREEN_WIDTH, -230);
		wall->setScale(1, 0.3);
		wallList.push_back(wall);
		AddObject(wall);
	}
	else
		return;
}

void MyGameScene::CollisionCheck() {
	for (auto iter = wallList.begin(); iter != wallList.end(); iter++) {
		if (player->IsCollisionRect((*iter)) && !player->isGround) {
			//debug("collide");
			player->isGround = true;
			jumpCount = 0;
		}
	}

	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {

			// ÄÚÀÎ Ãæµ¹
			if ((*iter)->getIsRed())
				score += 10;
			else
				score += 1;

			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end())
				break;
		}
	}
}

void MyGameScene::MouseManage() {
	// mouse click
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		firstMousePos = inputManager->GetMousePos();
		isLBtnDown = true;
		globalTime = 0.35;
	}
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_UP) {
		isLBtnDown = false;
		isLBtnUp = true;
		globalTime = 1;
	}

	if (isLBtnDown) {
		//std::cout << "ÁÂÅ¬¸¯ Áß" << std::endl;

		currentMousePos = inputManager->GetMousePos();
		arrowVector = currentMousePos - firstMousePos;

		if (VecDistance(arrowVector) < 250)
			arrowLen = VecDistance(arrowVector);
		else
			arrowLen = 250;

		arrow->setScale(arrowLen / 250, 1);
		arrow->setRotation(VecAngle(arrowVector) + PI / 2);
		arrow->setPos(player->getPosCenter());
	}
	else if (isLBtnUp && arrowLen > 0) {
		//std::cout << "ÁÂÅ¬¸¯ ¶À" << std::endl;
		cameraVector.y = 1;
		isLBtnUp = false;

		player->isGround = false;
		player->PlayerJump(arrowVector / VecDistance(arrowVector) * 3, arrowLen);
		jumpCount++;
	}
}

void MyGameScene::UISetting() {
	numArray[0]->setNum(score / 1000);
	numArray[1]->setNum(score / 100 % 10);
	numArray[2]->setNum(score / 10 % 10);
	numArray[3]->setNum(score % 10);
}

void MyGameScene::CameraMove(float dx, float dy) {
	CameraMove(D3DXVECTOR2(-dx, dy));
}

float MyGameScene::VecDistance(D3DXVECTOR2 vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);;
}

float MyGameScene::VecAngle(D3DXVECTOR2 vec) {
	return -atan2(vec.x, vec.y);
}

float MyGameScene::Lerp(float p1, float p2, float d1) {
	return (1 - d1) * p1 + d1 * p2;
}