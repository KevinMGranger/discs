#include "CylinderColliderBuilder.h"

using namespace DirectX;

CylinderColliderBuilder::CylinderColliderBuilder() :
	max(0,0,0), min(0,0,0)
{ }

CylinderColliderBuilder::CylinderColliderBuilder(XMFLOAT3 point) :
	max(point), min(point)
{ }

void CylinderColliderBuilder::start(XMFLOAT3 point)
{
	max = point;
	min = point;
}

void CylinderColliderBuilder::new_point(XMFLOAT3 point)
{
	if (point.x > max.x) max.x = point.x;
	if (point.y > max.y) max.y = point.y;
	if (point.z > max.z) max.z = point.z;

	if (point.x < min.x) min.x = point.x;
	if (point.y < min.y) min.y = point.y;
	if (point.z < min.z) min.z = point.z;
}


CylinderCollider CylinderColliderBuilder::finalize()
{
	XMVECTOR max = XMLoadFloat3(&this->max);
	XMVECTOR min = XMLoadFloat3(&this->min);

	XMVECTOR v_centroid = (max + min) / 2;
	XMVECTOR v_halves = max - v_centroid;

	XMFLOAT3 centroid, halves;

	XMStoreFloat3(&centroid, v_centroid);
	XMStoreFloat3(&halves, v_halves);

	// this isn't correct
	float radius = (halves.x > halves.z) ? halves.x : halves.z;

	return CylinderCollider(centroid, halves.y, radius);
}