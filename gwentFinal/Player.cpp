#include "Player.h"

Player::Player()
{
}

Player::Player(string ability) //construct with ability
{
	pAbility = ability;
}

void Player::SetMonsterAbil(bool state) //set monster abil state
{
	monsterAbil = state;
}

bool Player::GetMonsterAbil() //get monster abil
{
	return monsterAbil;
}

string Player::GetAbility() //get ability
{
	return pAbility;
}

Player::~Player()
{
}
