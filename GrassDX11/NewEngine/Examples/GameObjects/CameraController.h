#pragma once

#include "../../Engine/Graphics/Camera2.h"
#include "../../Engine/Graphics/CameraClass.h"

class CameraController {
private:
	Camera2 camera;
	//CameraClass camera2;

	float mouseSensitivity;
	float movementSpeed;

public:
	CameraController(int windowWidth, int windowHeight);
	~CameraController();

	void update();

	Camera2& getCamera();
	//CameraClass& getCamera();
};