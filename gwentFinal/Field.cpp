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
				if (bFActivated)
				{
					hand[i]->SetAttack(1);
					melee.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
				else
				{
					melee.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
			}
			else if (hand[i]->GetType() == "Ranged")
			{
				if (iFActivated)
				{
					hand[i]->SetAttack(1);
					ranged.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
				else
				{
					ranged.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
			}
			else if (hand[i]->GetType() == "Siege")
			{
				if (tRActivated)
				{
					hand[i]->SetAttack(1);
					siege.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
				else
				{
					siege.push_back(hand[i]);
					ActivateEffect(card);
					hand.erase(hand.begin() + i);
				}
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
						discard[i]->ResetAttack();
						melee.push_back(discard[i]);
						discard.erase(discard.begin() + i);
						cardInDis = true;
					}
					else if (discard[i]->GetType() == "Ranged")
					{
						discard[i]->ResetAttack();
						ranged.push_back(discard[i]);
						discard.erase(discard.begin() + i);
						cardInDis = true;
					}
					else if (discard[i]->GetType() == "Siege")
					{
						discard[i]->ResetAttack();
						siege.push_back(discard[i]);
						discard.erase(discard.begin() + i);
						cardInDis = true;
					}
				}
			}
		}
	}
}

void Field::ClearWeather()
{
	weather.clear();
	bFActivated = false;
	iFActivated = false;
	tRActivated = false;
	for (int i = 0; i < melee.size(); i++)
	{
		melee[i]->ResetAttack();
	}
	for (int i = 0; i < ranged.size(); i++)
	{
		ranged[i]->ResetAttack();
	}
	for (int i = 0; i < siege.size(); i++)
	{
		siege[i]->ResetAttack();
	}
}

void Field::CommandersHorn()
{
	string rowChoice;
	bool correctChoice = false;
	while (!correctChoice)
	{
		cout << "Commander's Horn was activated!\nWhich row would you like to double all units attack value? (melee, ranged, or siege): ";
		cin >> rowChoice;
		if (rowChoice == "melee")
		{
			for (int i = 0; i < melee.size(); i++)
			{
				melee[i]->DoubleAttack();
			}
			correctChoice = true;
		}
		else if (rowChoice == "ranged")
		{
			for (int i = 0; i < ranged.size(); i++)
			{
				ranged[i]->DoubleAttack();
			}
		}
		else if (rowChoice == "siege")
		{
			for (int i = 0; i < siege.size(); i++)
			{
				siege[i]->DoubleAttack();
			}
		}
	}
}

void Field::BitingFrost()
{
	bFActivated = true;
	for (int i = 0; i < melee.size(); i++)
	{
		melee[i]->SetAttack(1);
	}
}

void Field::ImpenetrableFog()
{
	iFActivated = true;
	for (int i = 0; i < ranged.size(); i++)
	{
		ranged[i]->SetAttack(1);
	}
}

void Field::TorrentialRain()
{
	tRActivated = true;
	for (int i = 0; i < siege.size(); i++)
	{
		siege[i]->SetAttack(1);
	}
}

void Field::Bond(string card, Card * pCard)
{
	int sameCards = 0;
	for (int i = 0; i < melee.size(); i++)
	{
		if (melee[i]->GetName() == card)
		{
			melee[i]->DoubleAttack();
			sameCards++;
		}
	}
	if (sameCards == 3)
	{
		pCard->DoubleAttack();
		pCard->DoubleAttack();
	}
	else if (sameCards == 2)
	{
		pCard->DoubleAttack();
	}
}

void Field::Morale(Card * typeCheck)
{
	if (typeCheck->GetType() == "Ranged")
	{
		for (int i = 0; i < ranged.size(); i++)
		{
			ranged[i]->IncrementAttack();
		}
	}
	else if (typeCheck->GetType() == "Siege")
	{
		for (int i = 0; i < siege.size(); i++)
		{
			siege[i]->IncrementAttack();
		}
	}
}

void Field::Scorch()
{
	
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
					ClearWeather();
				}
				else if (hand[i]->GetName() == "Biting Frost")
				{
					BitingFrost();
				}
				else if (hand[i]->GetName() == "Impenetrable Fog")
				{
					ImpenetrableFog();
				}
				else if (hand[i]->GetName() == "Torrential Rain")
				{
					TorrentialRain();
				}
				else if (hand[i]->GetName() == "Commander's Horn")
				{
					CommandersHorn();
				}
			}
			else
			{
				if (hand[i]->GetEffect() == "Medic")
				{
					Medic();
				}
				else if (hand[i]->GetEffect() == "Bond")
				{
					Bond(card, hand[i]);
				}
				else if (hand[i]->GetEffect() == "Morale")
				{
					Morale(hand[i]);
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
