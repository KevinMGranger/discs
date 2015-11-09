#pragma once

#include <DirectXMath.h>

using DirectX::XMFLOAT3;

class CylinderCollider
{
public:
	CylinderCollider() = default;
	CylinderCollider(XMFLOAT3 centroid, float half_height, float radius);

	static bool IsColliding(CylinderCollider const &cyl1, CylinderCollider const &cyl2);

	XMFLOAT3 Centroid;
	float HalfHeight, Radius;
};