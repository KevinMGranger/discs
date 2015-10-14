#include "CylinderCollider.h"

using namespace DirectX;

CylinderCollider::CylinderCollider(XMFLOAT3 centroid, float half_height, float radius)
	: centroid(centroid), half_height(half_height), radius(radius)
{
}

bool CylinderCollider::is_colliding(CylinderCollider const &cyl1, CylinderCollider const &cyl2)
{
	// TODO: rotation

	float collision_length = cyl1.radius + cyl2.radius;

	bool y_colliding =
		(cyl1.centroid.y + cyl1.half_height > cyl2.centroid.y - cyl2.half_height) ||
		(cyl2.centroid.y + cyl2.half_height > cyl1.centroid.y - cyl1.half_height);

	XMVECTOR cent1 = XMLoadFloat3(&cyl1.centroid);
	XMVECTOR cent2 = XMLoadFloat3(&cyl2.centroid);
	XMVECTOR cent1_2d = XMVectorSetY(cent1, 0);
	XMVECTOR cent2_2d = XMVectorSetY(cent2, 0);

	float dist = XMVectorGetX(XMVector3Length(cent2_2d - cent1_2d));

	bool xz_colliding = dist <= collision_length;

	return y_colliding && xz_colliding;
}