#include "Player.h"

Player::Player()
{
}

Player::Player(string ability)
{
	pAbility = ability;
}

string Player::GetAbility()
{
	return pAbility;
}

Player::~Player()
{
}
