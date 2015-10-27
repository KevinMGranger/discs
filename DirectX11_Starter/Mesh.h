#pragma once

#include <d3d11.h>
#include <vector>
#include <DirectXMath.h>
#include "Vertex.h"
#include "hr.h"

class Mesh
{
private:
	//data required to make the draw call
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int indexCount;

protected:
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();

public:
	Mesh(const Vertex* vertices,
		int vertexCount,
		UINT* indices,
		int indexCount,
		ID3D11Device* device);

	// draws the mesh to the screen
	virtual void Draw(ID3D11DeviceContext* context);

	~Mesh();
};

