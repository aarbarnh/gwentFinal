#include "Field.h"
#include <iostream>

using namespace std;

Field::Field()
{
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

Field::~Field()
{
}
