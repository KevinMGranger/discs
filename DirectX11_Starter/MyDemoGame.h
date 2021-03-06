#pragma once

#include <DirectXMath.h>
#include "DirectXGameCore.h"
#include "SimpleShader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include "DirectionalLight.h"
#include "WICTextureLoader.h"

// Include run-time memory checking in debug builds, so 
// we can be notified of memory leaks
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// --------------------------------------------------------
// Game class which extends the base DirectXGameCore class
// --------------------------------------------------------
class MyDemoGame : public DirectXGameCore
{
public:
	MyDemoGame(HINSTANCE hInstance);
	~MyDemoGame();
	enum gameState { START, MAIN, GAME };
	// Overrides for base level methods
	bool Init();
	void OnResize();
	void UpdateScene(float deltaTime, float totalTime);
	void DrawScene(float deltaTime, float totalTime);

	// For handing mouse input
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	//-----------------------------------------------------------
	//NOTE:  Everything below is for testing/demo purposes only.  
	//This all should be removed/recycled when we move on to the 
	//full project.
	//-----------------------------------------------------------
	void CreateGeometry();
	void LoadShaders();
	void CreateObjects();
	void StartGame();
	void EndGame();

	Mesh* mesh;

	GameObject* object;

	Camera* camera;

	Renderer* renderer;
	gameState gState;
	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

};