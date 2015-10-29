#pragma once
#include "GameObject.h"

class Disc : public GameObject
{
public:
	Disc(Mesh* m);
	~Disc();
	void Launch(XMFLOAT3 p, XMFLOAT3 r);
	void MoveDisc(float dt);
	bool IsActive() const { return isActive; }
private:
	bool isActive;
	XMFLOAT3 velocity;
};

