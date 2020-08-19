#pragma once

#include "Object.h"

class Camera : public Object
{
public:
	Camera();
	~Camera();

	void CameraMove(D3DXVECTOR2 vec);
	void CameraMove(float dx, float dy);
};

