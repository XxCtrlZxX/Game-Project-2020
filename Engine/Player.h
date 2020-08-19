#pragma once
#include "Object.h"
#include "Animation.h"

class Player : public Object
{
private :
	Animation* playerAnimation;
	float Vgravity, Hgravity;

	D3DXVECTOR2 center;

public :
	bool isPlayerAnim, isGround;

	Player();
	~Player();

	void Render();
	void Update(float dTime);

	void PlayerJump(D3DXVECTOR2 jVec, float power);

	D3DXVECTOR2 getPosCenter();
};