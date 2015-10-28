#pragma once
#include "GameObject.h"
#include "Disc.h"

class Player: public GameObject
{
public:
	Player(Mesh* m);
	~Player();
	void Fire(Disc* d);
	void ReloadDisc();
private:
	bool ableToFire;
};

