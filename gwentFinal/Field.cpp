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

void Field::ShowMelee()
{
	for (int i = 0; i < melee.size(); i++)
	{
		cout << melee[i]->GetName() << "\n" << melee[i]->GetType() << "\n" << melee[i]->GetEffect() << "\n" << melee[i]->GetAttack() << "\n\n";
	}
}

void Field::ShowRanged()
{
	for (int i = 0; i < ranged.size(); i++)
	{
		cout << ranged[i]->GetName() << "\n" << ranged[i]->GetType() << "\n" << ranged[i]->GetEffect() << "\n" << ranged[i]->GetAttack() << "\n\n";
	}
}

void Field::ShowSiege()
{
	for (int i = 0; i < siege.size(); i++)
	{
		cout << siege[i]->GetName() << "\n" << siege[i]->GetType() << "\n" << siege[i]->GetEffect() << "\n" << siege[i]->GetAttack() << "\n\n";
	}
}

void Field::ShowDiscard()
{
	for (int i = 0; i < discard.size(); i++)
	{
		cout << discard[i]->GetName() << "\n" << discard[i]->GetType() << "\n" << discard[i]->GetEffect() << "\n" << discard[i]->GetAttack() << "\n\n";
	}
}

void Field::ShowWeather()
{
	for (int i = 0; i < weather.size(); i++)
	{
		cout << weather[i]->GetName() << "\n" << weather[i]->GetType() << "\n" << weather[i]->GetEffect() << "\n" << weather[i]->GetAttack() << "\n\n";
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
				ActivateEffect(card);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Melee")
			{
				melee.push_back(hand[i]);
				ActivateEffect(card);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Ranged")
			{
				ranged.push_back(hand[i]);
				ActivateEffect(card);
				hand.erase(hand.begin() + i);
			}
			else if (hand[i]->GetType() == "Siege")
			{
				siege.push_back(hand[i]);
				ActivateEffect(card);
				hand.erase(hand.begin() + i);
			}
			else
			{
				ActivateEffect(card);
				discard.push_back(hand[i]);
				hand.erase(hand.begin() + i);
			}
		}
	}
}

void Field::Medic()
{
	string reviveCard;
	bool cardInDis = false;
	while (!cardInDis)
	{
		cout << "Medic effect was activated!\nWhich card would you like to bring back from the discard pile? (No weather or instants): ";
		cin >> reviveCard;
		for (int i = 0; i < discard.size(); i++)
		{
			if (discard[i]->GetName() == reviveCard)
			{
				if (discard[i]->GetType() == "Weather" || discard[i]->GetType() == "Instant")
				{
					cout << "\nYou cannot bring back a weather or instant card. Please choose one of your unit cards (melee, ranged, or siege).\n\n";
				}
				else
				{
					if (discard[i]->GetType() == "Melee")
					{
						//later
					}
					else if (discard[i]->GetType() == "Ranged")
					{
						//later
					}
					else if (discard[i]->GetType() == "Siege")
					{
						//later
					}
				}
			}
		}
	}
}

void Field::ActivateEffect(string card)
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->GetName() == card)
		{
			if (hand[i]->GetType() == "Instant" || hand[i]->GetType() == "Weather")
			{
				if (hand[i]->GetName() == "Clear Weather")
				{
					//activate clear weather
				}
				else if (hand[i]->GetName() == "Biting Frost")
				{
					//activate biting frost
				}
				else if (hand[i]->GetName() == "Impenetrable Fog")
				{
					//activate impenetrable fog
				}
				else if (hand[i]->GetName() == "Torrential Rain")
				{
					//activate torrential rain 
				}
				else if (hand[i]->GetName() == "Commander's Horn")
				{
					//activate commanders horn
				}
				else if (hand[i]->GetName() == "Scorch")
				{
					//activate scorch
				}
			}
			else
			{
				if (hand[i]->GetEffect() == "Medic")
				{
					//activate Medic
				}
				else if (hand[i]->GetEffect() == "Muster")
				{
					//activate Muster
				}
				else if (hand[i]->GetEffect() == "Scorch")
				{
					//activate scorch
				}
				else if (hand[i]->GetEffect() == "Bond")
				{
					//activate scorch
				}
				else if (hand[i]->GetEffect() == "Morale")
				{
					//activate morale
				}
			}
		}
	}
}

vector<Card*> Field::GetHand()
{
	return hand;
}

vector<Card*> Field::GetMelee()
{
	return melee;
}

vector<Card*> Field::GetRanged()
{
	return ranged;
}

vector<Card*> Field::GetSiege()
{
	return siege;
}

vector<Card*> Field::GetWeather()
{
	return weather;
}

vector<Card*> Field::GetDiscard()
{
	return discard;
}

Field::~Field()
{
}
