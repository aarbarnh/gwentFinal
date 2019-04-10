#include "Card.h"

Card::Card()
{
}

Card::Card(string name, string type, string effect, int attack) //set up card values, used with deck readfile function
{
	cardName = name;
	cardType = type;
	cardEffect = effect;
	attackValue = attack;
	attackNorm = attack;
}

void Card::SetAttackNorm(int attack) //setter for attack norm
{
	attackNorm = attack;
}

void Card::ResetAttack() //reset attack to norm, after weather effects
{
	attackValue = attackNorm;
}

void Card::DoubleAttack() //double attack, bond
{
	attackValue *= 2;
}

void Card::IncrementAttack() //increment attack, morale
{
	attackValue++;
}

void Card::SetName(string name) //setter name
{
	cardName = name;
}

void Card::SetType(string type) //setter type
{
	cardType = type;
}

void Card::SetEffect(string effect) //setter effect
{
	cardEffect = effect;
}

void Card::SetAttack(int attack) //setter attack
{
	attackValue = attack;
}

string Card::GetName() //getter name
{
	return cardName;
}

string Card::GetType() //getter type
{
	return cardType;
}

string Card::GetEffect() //getter effect
{
	return cardEffect;
}

int Card::GetAttack() //getter attack
{
	return attackValue;
}

Card::~Card()
{
}
