#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include "EndScene.h"
#include <list>
#include <math.h>

// 오브젝트 헤더
#include "Player.h"
#include "Wall.h"
#include "Number.h"
#include "Coin.h"
#include "Background.h"

class MyGameScene : public Scene
{
private:
	Player* player;
	Sprite* arrow;
	
	std::list<Background*> backgroundList;
	std::list<Wall*> wallList;
	std::list<Coin*> coinList;
	
	Number* numArray[4];
	

	float arrowLen;
	bool isLBtnDown, isLBtnUp;
	int jumpCount, score, goal;

	D3DXVECTOR2 firstMousePos, currentMousePos, cameraPos;
	D3DXVECTOR2 arrowVector, cameraVector;

public:
	MyGameScene();
	~MyGameScene();

	void Render();
	void Update(float dTime);

	void InstantiateCoin(float y);
	void InstantiateWall(int tmp);
	void DeleteObject();

	void CollisionCheck();
	void MouseManage();
	void UISetting();
	
	void CameraMove(D3DXVECTOR2 vec);
	void CameraMove(float dx, float dy);

	float VecDistance(D3DXVECTOR2 vec);
	float VecAngle(D3DXVECTOR2 vec);
	float Lerp(float p1, float p2, float d1);
};

