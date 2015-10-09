#include "Camera.h"


/// <summary>
/// Standard constructor.
/// </summary>
/// <param name="p">the starting position of the camera</param>
/// <param name="d">the initial facing direction of the camera</param>
/// <param name="ar">the aspect ratio of the window</param>
Camera::Camera(XMFLOAT3 p, XMFLOAT3 d, float ar)
{
	position = p;
	direction = d;

	rotX = 0;
	rotY = 0; 

	viewMatIsDirty = true;

	this->CreateProjMatrix(ar);
}

/// <summary>
/// Gets the current location of the camera.
/// </summary>
/// <returns>the location of the camera in world space</returns>
XMFLOAT3 Camera::GetPosition()
{
	return position;
}

/// <summary>
/// Gets the initial direction that the camera was facing.
/// 
/// This currently doesn't make much sense, and you probably 
/// don't need this value anyway, but if you want the direction
/// that the camera is currently facing, use this result in conjunction
/// with the results from Camera::GetXRotation and Camera::GetYRotation.
/// </summary>
/// <returns>the reference direction from which rotations are caluclated</returns>
XMFLOAT3 Camera::GetDirection()
{
	return direction;
	//TODO:  Make direction work more intelligently
}

/// <summary>
/// Gets the pitch of the camera in radians.
/// </summary>
/// <returns>the pitch of the camera</returns>
float Camera::GetXRotation()
{
	return rotX;
}

/// <summary>
/// Gets the yaw of the camera in radians.
/// </summary>
/// <returns>the yaw of the camera</returns>
float Camera::GetYRotation()
{
	return rotY;
}

/// <summary>
/// Builds the camera's left handed perspective matrix.  Call this
/// method whenever the size of the window changes.
/// 
/// Uses a FOV angle of 45 degrees (pi/4 rad) and the given aspect ratio.
/// Near and far clipping plane are at 0.1 and 100, respectively.
/// </summary>
/// <param name="aspectRatio">the aspect ratio of the window</param>
void Camera::CreateProjMatrix(float aspectRatio)
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		aspectRatio,		  	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projMat, XMMatrixTranspose(P)); // Transpose for HLSL!
}

/// <summary>
/// Sets the camera's view and perspective matrices in a shader,
/// assuming that the matrices in the shader are named "view" and
/// "projection" respectively.
/// 
/// This does NOT send buffer data.
/// </summary>
/// <param name="vertexShader">the vertex shader to set the matrices in</param>
void Camera::SetViewAndProjMatrices(SimpleVertexShader* vertexShader)
{
	vertexShader->SetMatrix4x4("view", viewMat);
	vertexShader->SetMatrix4x4("projection", projMat);
}

/// <summary>
/// Set the current position of the camera.
/// </summary>
/// <param name="p">the new position of the camera</param>
void Camera::SetPosition(XMFLOAT3 p)
{
	position = p;
	viewMatIsDirty = true;
}

/// <summary>
/// Sets a new "basis direction" for the camera to face and sets X and Y
/// rotation to 0.  You PROBABLY don't want to be using this function if
/// you're not sure what is meant by "basis direction"; a more rational
/// implementation of camera direction is forthcoming.
/// </summary>
/// <param name="d">the new "basis direction" of the camera</param>
void Camera::SetDirection(XMFLOAT3 d)
{
	direction = d;
	viewMatIsDirty = true;
}

/// <summary>
/// Sets the rotation of the camera around the X axis.  Also known as 'pitch'.
/// </summary>
/// <param name="x">the pitch of the camera in radians</param>
void Camera::SetRotationX(float x)
{
	rotX = x;
	viewMatIsDirty = true;
}

/// <summary>
/// Sets the rotation of the camera around the Y axis.  Also known as 'yaw'. 
/// </summary>
/// <param name="y">the yaw of the camera in radians</param>
void Camera::SetRotationY(float y)
{
	rotY = y;
	viewMatIsDirty = true;
}

/// <summary>
/// Rotate the camera from its current position.
/// </summary>
/// <param name="x">amount to rotate around the X axis, in radians (pitch)</param>
/// <param name="y">amount to rotate around the Y axis, in radians (yaw)</param>
void Camera::Rotate(float x, float y)
{
	rotX += x;
	rotY += y;

	viewMatIsDirty = true;
}


/// <summary>
/// Updates the view matrix, if it needs to be updated.
/// </summary>
/// <param name="deltaTime">time the last frame took, in seconds</param>
void Camera::Update(float deltaTime)
{
	XMVECTOR vPosition = XMLoadFloat3(&position);
	XMVECTOR vDirection = XMLoadFloat3(&direction);
	XMMATRIX mRotation = XMMatrixRotationRollPitchYaw(rotY, rotX, 0);
	XMVECTOR vFinalDirection = XMVector3Transform(vDirection, mRotation);
	XMVECTOR vUp = XMLoadFloat3(&XMFLOAT3(0, 1, 0));

	if (GetAsyncKeyState('W') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Normalize(vFinalDirection) * deltaTime;
		vPosition += vNeedToAdd;
		
		viewMatIsDirty = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Normalize(vFinalDirection) * deltaTime;
		vPosition -= vNeedToAdd;

		viewMatIsDirty = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Cross(vFinalDirection, vUp);
		vNeedToAdd = XMVector3Normalize(vNeedToAdd) * deltaTime;
		vPosition += vNeedToAdd;

		viewMatIsDirty = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Cross(vFinalDirection, vUp);
		vNeedToAdd = XMVector3Normalize(vNeedToAdd) * deltaTime;
		vPosition -= vNeedToAdd;

		viewMatIsDirty = true;
	}
	if (GetAsyncKeyState(' ') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Normalize(vUp) * deltaTime;
		vPosition += vNeedToAdd;

		viewMatIsDirty = true;
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		XMVECTOR vNeedToAdd = XMVector3Normalize(vUp) * deltaTime;
		vPosition -= vNeedToAdd;

		viewMatIsDirty = true;
	}

	XMStoreFloat3(&position, vPosition);

	if (viewMatIsDirty)
	{

		XMMATRIX vViewMat = XMMatrixLookToLH(
			vPosition,
			vFinalDirection, 
			vUp);

		XMStoreFloat4x4(&viewMat, XMMatrixTranspose(vViewMat));

		viewMatIsDirty = false;
	}
}

/// <summary>
/// Empty destructor.
/// </summary>
Camera::~Camera()
{
}