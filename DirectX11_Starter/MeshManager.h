#pragma once
#include <unordered_map>
#include <string>
#include "Mesh.h"
#include "CylinderCollider.h"
#include "ModelLoading.h"

namespace MeshManager
{
	Mesh *LoadModel(std::string path, ID3D11Device *device);
	CylinderCollider *GetColliderForMesh(Mesh *);
};