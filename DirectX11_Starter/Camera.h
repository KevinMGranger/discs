#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include "SimpleShader.h"

using namespace DirectX;

/// <summary>
/// Basic camera.
/// </summary>
class Camera
{
private:

	bool viewMatIsDirty;

	XMFLOAT4X4 viewMat;
	XMFLOAT4X4 projMat;

	XMFLOAT3 position;
	XMFLOAT3 direction;

	float rotX;
	float rotY;

public:
	Camera(XMFLOAT3 position, XMFLOAT3 direction, float aspectRatio);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetDirection();
	float GetXRotation();
	float GetYRotation();

	virtual void CreateProjMatrix(float aspectRatio);
	
	void SetViewAndProjMatrices(SimpleVertexShader* vertexShader);

	void SetPosition(XMFLOAT3 position);
	void SetDirection(XMFLOAT3 direction);
	void SetRotationX(float rotX);
	void SetRotationY(float rotY);
	void Rotate(float x, float y);

	virtual void Update(float deltaTime);

	~Camera();
};

