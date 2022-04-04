#pragma once

#include "../../pch.h"

class Camera2 {
private:
	XMMATRIX projectionMatrix;
	XMMATRIX viewMatrix;

	XMVECTOR position;
	XMVECTOR lookAt;
	XMVECTOR worldUp;

	XMVECTOR forward;
	XMVECTOR left;
	XMVECTOR up;

	float pitch;
	float yaw;

	void updateDirectionVectors();
	void updateViewMatrix();

public:
	Camera2(float fov, float aspectRatio, float nearZ, float farZ, XMVECTOR startPos);
	~Camera2();

	void setPosition(XMVECTOR newPos);
	void move(XMVECTOR dirV);
	void rotate(XMVECTOR dirV);

	const XMMATRIX& getProjectionMatrix() const;
	const XMMATRIX& getViewMatrix();	
	const XMFLOAT3 getPosition() const;
};