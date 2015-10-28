#include "Player.h"



Player::Player(Mesh* m)
	: GameObject(m)
{
	ableToFire = true;
}


Player::~Player()
{}

void Player::Fire(Disc* d)
{
	if (ableToFire)
	{
		d->Launch(translation, rotation);
		ableToFire = false;
	}
}

void Player::ReloadDisc()
{
	ableToFire = true;
}
