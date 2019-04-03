#include "Card.h"

Card::Card()
{
}

Card::Card(string name, string type, string effect, int attack)
{
	cardName = name;
	cardType = type;
	cardEffect = effect;
	attackValue = attack;
}

void Card::SetName(string name)
{
	cardName = name;
}

void Card::SetType(string type)
{
	cardType = type;
}

void Card::SetEffect(string effect)
{
	cardEffect = effect;
}

void Card::SetAttack(int attack)
{
	attackValue = attack;
	attackNorm = attack;
}

string Card::GetName()
{
	return cardName;
}

string Card::GetType() 
{
	return cardType;
}

string Card::GetEffect()
{
	return cardEffect;
}

int Card::GetAttack()
{
	return attackValue;
}

Card::~Card()
{
}
