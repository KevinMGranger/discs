#pragma once
#include "GameObject.h"

class Player;

class Disc : public GameObject
{
public:
	Disc(Mesh* m, Material* mat, Player* p);
	~Disc();
	void Launch(XMFLOAT3 p, XMFLOAT3 r);
	void MoveDisc(float dt);
	bool IsActive() const { return isActive; }
private:
	bool isActive;
	XMFLOAT3 velocity;
	Player* player;
};

