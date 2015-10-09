#include "Renderer.h"

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="c">the camera holding the correct view and projection matrices</param>
/// <param name="con">the device context to draw objects with</param>
Renderer::Renderer(Camera* c, ID3D11DeviceContext* con)
{
	camera = c;
	context = con;
}


/// <summary>
/// Empty destructor.
/// </summary>
Renderer::~Renderer()
{
}

/// <summary>
/// Do not use.  For test purposes only.
/// </summary>
/// <param name="light"></param>
/// <param name="light2"></param>
void Renderer::AddTestLights(DirectionalLight light, DirectionalLight light2)
{
	//TODO: actually write lighting stuff
	tl = light;
	tl2 = light2;
}

// In the future, this will add an object to a group
// of objects drawn with the same shaders, and when we're finished queuing up all
// objects to be drawn, this class will draw each batch of objects in front-to-back
// order.  This aims to reduce the number of times that shaders need to be switched and
// reduce the number of pixels that need to be redrawn, without putting the onus of
// deciding draw order on the developer writing the game logic.

/// <summary>
/// Draw a GameObject.
/// </summary>
/// <param name="object">the object to draw</param>
void Renderer::DrawObject(GameObject* object)
{
	Material mat = object->GetMaterial();

	mat.VertexShader->SetShader(false);
	mat.PixelShader->SetShader(false);

	mat.PixelShader->SetData(
		"light",
		&tl,
		sizeof(DirectionalLight));

	mat.PixelShader->SetData(
		"light2",
		&tl2,
		sizeof(DirectionalLight));

	mat.PixelShader->CopyAllBufferData();

	camera->SetViewAndProjMatrices(mat.VertexShader);

	object->Draw(context);
}
