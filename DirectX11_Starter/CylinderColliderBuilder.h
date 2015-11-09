#pragma once

#include "CylinderCollider.h"
#include <tuple>


class CylinderColliderBuilder
{
public:
	CylinderColliderBuilder();
	CylinderColliderBuilder(XMFLOAT3 point);
	void Start(XMFLOAT3 point);
	void NewPoint(XMFLOAT3 point);

	CylinderCollider Finalize();

	XMFLOAT3 Max, Min;
};