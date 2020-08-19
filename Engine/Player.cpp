#include "stdafx.h"
#include "Player.h"

Player::Player() {
	isPlayerAnim = false;
	isGround = false;
	Vgravity = 0;
	Hgravity = 0;

	playerAnimation = new Animation(3);
	playerAnimation->AddFrame("Resources/Image/player-stop.png");
	playerAnimation->AddFrame("Resources/Image/player-run.png");
	AddChild(playerAnimation);

	rect = playerAnimation->getRect();
}

Player::~Player() {

}

void Player::Render() {
	Object::Render();
	if (isGround)
		playerAnimation->Render(0);
	else
		playerAnimation->Render(1);
}

void Player::Update(float dTime) {

	if (!isGround) {
		Vgravity += 9.8f;
		setPos(getPosX() + Hgravity * dTime * globalTime, getPosY() + Vgravity * dTime * globalTime);
	}
	else {
		Vgravity = 0;
		Hgravity = 0;
	}
}

void Player::PlayerJump(D3DXVECTOR2 jVec, float power) {
	Hgravity = jVec.x * power;
	Vgravity = jVec.y * power;
}

D3DXVECTOR2 Player::getPosCenter() {
	return D3DXVECTOR2(getPosX() + playerAnimation->getWidth() / 2 - 15, getPosY() + playerAnimation->getHeight() / 2 - 50);
}