#pragma once

#include <DirectXMath.h>

using DirectX::XMFLOAT3;

class GameObject {};

class CylinderCollider
{
public:
	CylinderCollider() = default;
	CylinderCollider(XMFLOAT3 centroid, float half_height, float radius);

	static bool is_colliding(CylinderCollider const &cyl1, CylinderCollider const &cyl2);

	XMFLOAT3 centroid;
	float half_height, radius;
};