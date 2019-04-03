#include "Field.h"
#include <iostream>

using namespace std;

Field::Field()
{
}

void Field::mPowAdd()
{
	for (int i = 0; i < melee.size(); i++)
	{
		meleePower += melee[i]->GetAttack();
	}
}

void Field::rPowAdd()
{
	for (int i = 0; i < ranged.size(); i++)
	{
		rangedPower += ranged[i]->GetAttack();
	}
}

void Field::sPowAdd()
{
	for (int i = 0; i < siege.size(); i++)
	{
		siegePower += siege[i]->GetAttack();
	}
}

void Field::tPowAdd()
{
	totalPower = meleePower + rangedPower + siegePower;
}

void Field::DrawCard(vector<Card*> deck)
{
	vector<Card*> tempDeck = deck;
	hand.push_back(tempDeck[0]);
}

void Field::ShowHand()
{
	for (int i = 0; i < hand.size(); i++)
	{
		cout << hand[i]->GetName() << "\n" << hand[i]->GetType() << "\n" << hand[i]->GetEffect() << "\n" << hand[i]->GetAttack() << "\n\n";
	}
}

void Field::PlayCard(string card)
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->GetName() == card)
		{
			if (hand[i]->GetType() == "Weather")
			{
				weather.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Melee")
			{
				melee.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Ranged")
			{
				ranged.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Siege")
			{
				siege.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
			else
			{
				//leave space to activate effect later, implement effects
				discard.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
		}
	}
}


Field::~Field()
{
}
