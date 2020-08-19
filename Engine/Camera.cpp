#include "stdafx.h"
#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::CameraMove(D3DXVECTOR2 vec) {
	for (auto& child : childList) {
		child->setPos(child->getPos() + vec * globalTime);
	}
}

void Camera::CameraMove(float dx, float dy) {
	for (auto& child : childList) {
		child->setPos(child->getPosX() + dx, child->getPosY() + dy);
	}
}