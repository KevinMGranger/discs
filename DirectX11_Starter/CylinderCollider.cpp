#include "CylinderCollider.h"

using namespace DirectX;

CylinderCollider::CylinderCollider(XMFLOAT3 centroid, float half_height, float radius)
	: centroid(centroid), half_height(half_height), radius(radius)
{
}

bool CylinderCollider::IsColliding(CylinderCollider const &cyl_1, CylinderCollider const &cyl_2)
{
	// TODO: rotation

	float collision_length = cyl_1.radius + cyl_2.radius;

	bool y_colliding =
		(cyl_1.centroid.y + cyl_1.half_height > cyl_2.centroid.y - cyl_2.half_height) ||
		(cyl_2.centroid.y + cyl_2.half_height > cyl_1.centroid.y - cyl_1.half_height);

	XMVECTOR cent_1 = XMLoadFloat3(&cyl_1.centroid);
	XMVECTOR cent_2 = XMLoadFloat3(&cyl_2.centroid);
	XMVECTOR cent_1_2d = XMVectorSetY(cent_1, 0);
	XMVECTOR cent_2_2d = XMVectorSetY(cent_2, 0);

	float dist = XMVectorGetX(XMVector3Length(cent_2_2d - cent_1_2d));

	bool xz_colliding = dist <= collision_length;

	return y_colliding && xz_colliding;
}