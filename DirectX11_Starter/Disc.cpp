#include "Disc.h"
#include <math.h>


Disc::Disc(Mesh* m)
	: GameObject(m)
{
	translation = XMFLOAT3(0, 0, -5);
	isActive = false;
	SetScale(XMFLOAT3(1, 0.2, 1));
}


Disc::~Disc()
{
}

void Disc::MoveDisc(float dt)
{
	Translate(XMFLOAT3(velocity.x * dt, velocity.y * dt, velocity.z * dt));
	if (translation.z < 0)
	{
		translation = XMFLOAT3(0, 0, -5);
		isActive = false;
	}
	if (translation.z > 13.5)
	{
		velocity.z *= -1;
	}
	if (translation.x < -3.5)
	{
		velocity.x *= -1;
	}
	if (translation.x > 3.5)
	{
		velocity.x *= -1;
	}


}
void Disc::Launch(XMFLOAT3 p, XMFLOAT3 r)
{
	isActive = true;
	SetTranslation(p);
	SetRotation(r);
	//velocity = XMFLOAT3(10 * sin(rotation.y), 0, 10 * cos(rotation.y));
	velocity = XMFLOAT3(5, 0, 10 * cos(rotation.y));
}
