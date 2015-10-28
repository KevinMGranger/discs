#pragma once

#include "CylinderCollider.h"
#include <tuple>


class CylinderColliderBuilder
{
public:
	CylinderColliderBuilder();
	CylinderColliderBuilder(XMFLOAT3 point);
	void start(XMFLOAT3 point);
	void new_point(XMFLOAT3 point);

	CylinderCollider finalize();

	XMFLOAT3 max, min;
};