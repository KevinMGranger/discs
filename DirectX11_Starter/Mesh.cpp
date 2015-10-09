#include "Mesh.h"

using namespace DirectX;

/// <summary>
/// Constructor for a procedurally generated mesh.
/// </summary>
/// <param name="vertices">array of indexed vertices</param>
/// <param name="numVertices">number of vertices</param>
/// <param name="indices">array of indices</param>
/// <param name="numIndices">number of indices</param>
/// <param name="device">the device to create the buffers on</param>
Mesh::Mesh(const Vertex* vertices,
	int numVertices,
	int* indices,
	int numIndices,
	ID3D11Device* device)
{
	//create vertex buffer

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVertices;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;

	HR(device->CreateBuffer(&vbd, &vertexData, &vertexBuffer));

	// create index buffer

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * numIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;

	HR(device->CreateBuffer(&ibd, &indexData, &indexBuffer));

	// we'll need this to draw the mesh
	indexCount = numIndices;
}

/// <summary>
/// Constructor for building a mesh from an OBJ format file.
/// </summary>
/// <param name="filename">name of obj file</param>
/// <param name="device">the device to create the buffers on</param>
Mesh::Mesh(char* filename, ID3D11Device* device)
{
	// File input object
	std::ifstream obj(filename); // <-- Replace filename with your parameter

								 // Check for successful open
	if (!obj.is_open())
		return;

	// Variables used while reading the file
	std::vector<XMFLOAT3> positions;     // Positions from the file
	std::vector<XMFLOAT3> normals;       // Normals from the file
	std::vector<XMFLOAT2> uvs;           // UVs from the file
	std::vector<Vertex> verts;           // Verts we're assembling
	std::vector<UINT> indices;           // Indices of these verts
	unsigned int triangleCounter = 0;    // Count of triangles/indices
	char chars[100];                     // String for line reading

										 // Still good?
	while (obj.good())
	{
		// Get the line (100 characters should be more than enough)
		obj.getline(chars, 100);

		// Check the type of line
		if (chars[0] == 'v' && chars[1] == 'n')
		{
			// Read the 3 numbers directly into an XMFLOAT3
			XMFLOAT3 norm;
			sscanf_s(
				chars,
				"vn %f %f %f",
				&norm.x, &norm.y, &norm.z);

			// Add to the list of normals
			normals.push_back(norm);
		}
		else if (chars[0] == 'v' && chars[1] == 't')
		{
			// Read the 2 numbers directly into an XMFLOAT2
			XMFLOAT2 uv;
			sscanf_s(
				chars,
				"vt %f %f",
				&uv.x, &uv.y);

			// Add to the list of uv's
			uvs.push_back(uv);
		}
		else if (chars[0] == 'v')
		{
			// Read the 3 numbers directly into an XMFLOAT3
			XMFLOAT3 pos;
			sscanf_s(
				chars,
				"v %f %f %f",
				&pos.x, &pos.y, &pos.z);

			// Add to the positions
			positions.push_back(pos);
		}
		else if (chars[0] == 'f')
		{
			// Read the 9 face indices into an array
			unsigned int i[9];
			sscanf_s(
				chars,
				"f %d/%d/%d %d/%d/%d %d/%d/%d",
				&i[0], &i[1], &i[2],
				&i[3], &i[4], &i[5],
				&i[6], &i[7], &i[8]);

			// - Create the verts by looking up
			//    corresponding data from vectors
			// - OBJ File indices are 1-based, so
			//    they need to be adusted
			Vertex v1;
			v1.Position = positions[i[0] - 1];
			v1.Uv = uvs[i[1] - 1];
			v1.Normal = normals[i[2] - 1];

			Vertex v2;
			v2.Position = positions[i[3] - 1];
			v2.Uv = uvs[i[4] - 1];
			v2.Normal = normals[i[5] - 1];

			Vertex v3;
			v3.Position = positions[i[6] - 1];
			v3.Uv = uvs[i[7] - 1];
			v3.Normal = normals[i[8] - 1];

			// Add the verts to the vector
			verts.push_back(v1);
			verts.push_back(v2);
			verts.push_back(v3);

			// Add three more indices
			indices.push_back(triangleCounter++);
			indices.push_back(triangleCounter++);
			indices.push_back(triangleCounter++);
		}
	}

	// Close
	obj.close();

	// - At this point, "verts" is a vector of Vertex structs, and can be used
	//    directly to create a vertex buffer:  &verts[0] is the first vert
	// - The vector "indices" is similar. It's a vector of unsigned ints and
	//    can be used directly for the index buffer: &indices[0] is the first int
	// - "triangleCounter" is BOTH the number of vertices and the number of indices

	//create vertex buffer

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * triangleCounter;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &verts[0];

	HR(device->CreateBuffer(&vbd, &vertexData, &vertexBuffer));

	// create index buffer

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * triangleCounter;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &indices[0]; // <--- why doesn't vector::data work here?

	HR(device->CreateBuffer(&ibd, &indexData, &indexBuffer));

	// we'll need this to draw the mesh
	indexCount = triangleCounter;
}

/// <summary>
/// Gets the pointer to the ID3D11Buffer storing the indexed vertices for this mesh.
/// </summary>
/// <returns>pointer to the vertex buffer</returns>
ID3D11Buffer* Mesh::GetVertexBuffer() { return vertexBuffer; }

/// <summary>
/// Gets the pointer to the ID3D11Buffer storing the indices for this mesh.
/// </summary>
/// <returns>pointer to the index buffer</returns>
ID3D11Buffer* Mesh::GetIndexBuffer() { return indexBuffer; }

/// <summary>
/// Gets the number of indices in the index buffer.
/// </summary>
/// <returns>number of vertices in the index buffer</returns>
int Mesh::GetIndexCount() { return indexCount; }

// draw the mesh to the screen
// allows for reusability of the basic steps required to draw the mesh,
// and cleans up the main draw method so it's a bit clearer
/// <summary>
/// Draws the mesh.
/// </summary>
/// <param name="context">the context to use for drawing the mesh</param>
void Mesh::Draw(ID3D11DeviceContext* context)
{
	// set the buffers to be used
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//do the actual draw operation
	context->DrawIndexed(indexCount, 0, 0);
}

/// <summary>
/// Destructor.  Releases the vertex and index buffers on the graphics card.  
/// </summary>
Mesh::~Mesh()
{
	//release the buffers (this should be the only reference to them (we hope))
	vertexBuffer->Release();
	indexBuffer->Release();
}
