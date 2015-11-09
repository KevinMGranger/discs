#pragma once

#include <DirectXMath.h>
#include <memory>
#include "Mesh.h"
#include "SimpleShader.h"

using namespace DirectX;
using namespace std;

class GameObject
{
protected:
	XMFLOAT4X4 worldMat;

	XMFLOAT3 translation;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	
	bool worldMatIsDirty;


protected:
	void updateWorldMatrix();
	void init();

public:
	GameObject(Mesh* mesh);

	Mesh *mesh;

	//getters for worldmat elements
	XMFLOAT3 GetTranslation();
	XMFLOAT3 GetRotation();
	XMFLOAT3 GetScale();

	//setters for worldmat elements
	void SetTranslation(XMFLOAT3 translation);
	void SetRotation(XMFLOAT3 rotation);
	void SetScale(XMFLOAT3 scale);

	//helpers
	void Translate(XMFLOAT3 translation);
	void Scale(XMFLOAT3 scale);

	void Draw(ID3D11DeviceContext* context);
};
