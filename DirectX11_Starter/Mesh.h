#pragma once

#include <d3d11.h>
#include <vector>
#include <DirectXMath.h>
#include <tuple>
#include <memory>
#include "Vertex.h"
#include "hr.h"
#include "Material.h"

class Mesh
{
public:
	//data required to make the draw call
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int indexCount;

	Material *material;

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();

	Mesh(std::pair<std::vector<Vertex>, std::vector<UINT>> &verts_and_indices, ID3D11Device *device);
	Mesh(const Vertex* vertices,
		int vertexCount,
		UINT* indices,
		int indexCount,
		ID3D11Device* device);

	// draws the mesh to the screen
	virtual void Draw(DirectX::XMFLOAT4X4 &worldMatrix, ID3D11DeviceContext* context);

	~Mesh();

private:
	void setup(const Vertex *vertices, int numVertices, UINT *indices, int numIndices, ID3D11Device *device);
};