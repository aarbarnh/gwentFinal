#include "Player.h"

Player::Player()
{
}

Player::Player(string ability)
{
	pAbility = ability;
}

void Player::SetMonsterAbil(bool state)
{
	monsterAbil = state;
}

bool Player::GetMonsterAbil()
{
	return monsterAbil;
}

string Player::GetAbility()
{
	return pAbility;
}

Player::~Player()
{
}
