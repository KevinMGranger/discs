#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//TODO:  Create point light
struct DirectionalLight
{
	XMFLOAT4 AmbientColor;
	XMFLOAT4 DiffuseColor;
	XMFLOAT3 Direction;
};