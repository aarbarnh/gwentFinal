#include "Field.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

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

void Field::Reset()
{
	for (int i = 0; i < melee.size(); i++) //push to discard for all rows
	{
		discard.push_back(melee[i]);
	}
	for (int i = 0; i < ranged.size(); i++)
	{
		discard.push_back(ranged[i]);
	}
	for (int i = 0; i < siege.size(); i++)
	{
		discard.push_back(siege[i]);
	}
	for (int i = 0; i < weather.size(); i++)
	{
		discard.push_back(weather[i]);
	}
	melee.clear(); //clear all rows
	ranged.clear();
	siege.clear();
	weather.clear();
	//reset weather bools
	bFActivated = false;
	iFActivated = false;
	tRActivated = false;
}

void Field::ResetPower()
{
	meleePower = 0;
	rangedPower = 0;
	siegePower = 0;
	totalPower = 0;
	bondDoubles = 0;
}

void Field::ClearAll()
{
	hand.clear();
	melee.clear();
	ranged.clear();
	siege.clear();
	weather.clear();
	discard.clear();
}

void Field::DrawCard(vector<Card*> deck)
{
	vector<Card*> tempDeck = deck;
	hand.push_back(tempDeck[0]);
}

void Field::ShowHand()
{
	if (hand.empty())
	{
		cout << "\nHand is empty.\n\n";
	}
	else
	{
		for (int i = 0; i < hand.size(); i++)
		{
			if (hand[i]->GetType() == "Weather" || hand[i]->GetType() == "Instant")
			{
				cout << "\n" << hand[i]->GetName() << "\n" << hand[i]->GetType() << "\n" << hand[i]->GetEffect() << "\n\n";
			}
			else 
			{
				cout << "\n" << hand[i]->GetName() << "\n" << hand[i]->GetType() << "\n" << hand[i]->GetEffect() << "\n" << hand[i]->GetAttack() << "\n\n";
			}
		}
	}
}

void Field::ShowMelee()
{
	if (melee.empty())
	{
		cout << "\nMelee row is empty.\n\n";
	}
	else
	{
		for (int i = 0; i < melee.size(); i++)
		{
			cout << "\n" << melee[i]->GetName() << "\n" << melee[i]->GetType() << "\n" << melee[i]->GetEffect() << "\n" << melee[i]->GetAttack() << "\n\n";
		}
	}
}

void Field::ShowRanged()
{
	if (ranged.empty())
	{
		cout << "\nRanged row is empty.\n\n";
	}
	else
	{
		for (int i = 0; i < ranged.size(); i++)
		{
			cout << "\n" << ranged[i]->GetName() << "\n" << ranged[i]->GetType() << "\n" << ranged[i]->GetEffect() << "\n" << ranged[i]->GetAttack() << "\n\n";
		}
	}
}

void Field::ShowSiege()
{
	if (siege.empty())
	{
		cout << "\nSiege row is empty.\n\n";
	}
	else
	{
		for (int i = 0; i < siege.size(); i++)
		{
			cout << "\n" << siege[i]->GetName() << "\n" << siege[i]->GetType() << "\n" << siege[i]->GetEffect() << "\n" << siege[i]->GetAttack() << "\n\n";
		}
	}
}

void Field::ShowDiscard()
{
	if (discard.empty())
	{
		cout << "\nDiscard pile is empty.\n\n";
	}
	else
	{
		for (int i = 0; i < discard.size(); i++)
		{
			if (discard[i]->GetType() == "Weather" || discard[i]->GetType() == "Instant")
			{
				cout << "\n" << discard[i]->GetName() << "\n" << discard[i]->GetType() << "\n" << discard[i]->GetEffect() << "\n\n";
			}
			else
			{
				cout << "\n" << discard[i]->GetName() << "\n" << discard[i]->GetType() << "\n" << discard[i]->GetEffect() << "\n" << discard[i]->GetAttack() << "\n\n";
			}
		}
	}
}

void Field::ShowWeather()
{
	if (weather.empty())
	{
		cout << "\nNo weather cards in effect.\n\n";
	}
	else
	{
		for (int i = 0; i < weather.size(); i++)
		{
			cout << "\n" << weather[i]->GetName() << "\n" << weather[i]->GetType() << "\n" << weather[i]->GetEffect() << "\n\n";
		}
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
				ActivateEffect(card);
				weather.push_back(hand[i]);
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
	if (!discard.empty())
	{
		ShowDiscard();
		while (!cardInDis)
		{
			cout << "\nMedic effect was activated!\n\n";
			cout << "Which card would you like to bring back from the discard pile? (No weather or instants): ";
			getline(cin, reviveCard);
			for (int i = 0; i < discard.size(); i++)
			{
				if (discard[i]->GetName() == reviveCard)
				{
					if (discard[i]->GetType() == "Weather" || discard[i]->GetType() == "Instant")
					{
						cout << "\n\nYou cannot bring back a weather or instant card. Please choose one of your unit cards (melee, ranged, or siege).\n";
					}
					else
					{
						if (discard[i]->GetType() == "Melee")
						{
							if (bFActivated)
							{
								discard[i]->SetAttack(1);
								melee.push_back(discard[i]);
								discard.erase(discard.begin() + i);
								cardInDis = true;
							}
							else
							{
								discard[i]->ResetAttack();
								melee.push_back(discard[i]);
								discard.erase(discard.begin() + i);
								cardInDis = true;
							}
						}
						else if (discard[i]->GetType() == "Ranged")
						{
							if (iFActivated)
							{
								discard[i]->SetAttack(1);
								ranged.push_back(discard[i]);
								discard.erase(discard.begin() + i);
								cardInDis = true;
							}
							else
							{
								discard[i]->ResetAttack();
								ranged.push_back(discard[i]);
								discard.erase(discard.begin() + i);
								cardInDis = true;
							}
						}
						else if (discard[i]->GetType() == "Siege")
						{
							if (tRActivated)
							{
								discard[i]->SetAttack(1);
								siege.push_back(discard[i]);
								discard.erase(discard.begin() + i);
								cardInDis = true;
							}
							else
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
	}
}

void Field::ClearWeather()
{
	for (int i = 0; i < weather.size(); i++)
	{
		discard.push_back(weather[i]);
	}
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
		getline(cin,rowChoice);
		boost::algorithm::to_upper(rowChoice); //make the player's choice uppercase
		if (rowChoice == "MELEE")
		{
			for (int i = 0; i < melee.size(); i++)
			{
				melee[i]->DoubleAttack();
			}
			correctChoice = true;
		}
		else if (rowChoice == "RANGED")
		{
			for (int i = 0; i < ranged.size(); i++)
			{
				ranged[i]->DoubleAttack();
			}
			correctChoice = true;
		}
		else if (rowChoice == "SIEGE")
		{
			for (int i = 0; i < siege.size(); i++)
			{
				siege[i]->DoubleAttack();
			}
			correctChoice = true;
		}
	}
	cout << "\n";
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

void Field::Bond(string card)
{
	string paramName = boost::algorithm::trim_left_copy_if(card, boost::is_digit()); //get rid of the 1/2 (digits) out of the name
	for (int i = 0; i < melee.size(); i++)
	{
		string cardName = boost::algorithm::trim_left_copy_if(melee[i]->GetName(), boost::is_digit()); //get rid of the 1/2 (digits) out of the name
		if (cardName == paramName)
		{
			bondDoubles++;
		}
	}
	if (bondDoubles > 1)
	{
		for (int i = 0; i < melee.size(); i++)
		{
			melee[i]->DoubleAttack();
		}
	}
}

void Field::Morale(Card * typeCheck)
{
	if (typeCheck->GetType() == "Melee")
	{
		for (int i = 0; i < melee.size(); i++)
		{
			melee[i]->IncrementAttack();
		}
	}
	else if (typeCheck->GetType() == "Ranged")
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

void Field::SortHand()
{
	for (int i = 0; i < hand.size(); i++) //sorts the hand, tried different numbers but using its own size seems to always work
	{
		for (int j = 1; j < hand.size(); j++)
		{
			if (hand[j]->GetAttack() > hand[j - 1]->GetAttack())
			{
				swap(hand[j], hand[j - 1]);
			}
		}
	}
}

int Field::GetTPow()
{
	return totalPower;
}

string Field::Scorch(vector<Card*>mRow, vector<Card*>rRow, vector<Card*>sRow)
{
	string scorchChoice;
	string rowChoice;
	char yNChoice;
	bool correctSChoice = false;
	bool correctRChoice = false;
	bool yNValid = false;
	vector<Card*> mTemp = mRow;
	vector<Card*> rTemp = rRow;
	vector<Card*> sTemp = sRow;

	while (!yNValid) //show rows y/n loop with validation, try
	{
		try
		{
			cout << "Would you like to see the other players zones? ('Y' for yes, 'N' for no): ";
			cin >> yNChoice;
			if (yNChoice == 'Y' || yNChoice == 'y')
			{
				cout << "\nMelee row:\n\n";
				for (int i = 0; i < mTemp.size(); i++)
				{
					cout << mTemp[i]->GetName() << "\n";
					cout << mTemp[i]->GetAttack() << "\n\n";
				}
				cout << "Ranged row:\n\n";
				for (int i = 0; i < rTemp.size(); i++)
				{
					cout << rTemp[i]->GetName() << "\n";
					cout << rTemp[i]->GetAttack() << "\n\n";
				}
				cout << "Siege row:\n\n";
				for (int i = 0; i < sTemp.size(); i++)
				{
					cout << sTemp[i]->GetName() << "\n";
					cout << sTemp[i]->GetAttack() << "\n\n";
				}
				yNValid = true;
			}
			else if (yNChoice == 'N' || yNChoice == 'n')
			{
				yNValid = true;
			}
			else
			{
				throw "You can only enter 'Y' or 'N'.";
			}
		}
		catch (const char * msg)
		{
			cout << msg << "\n\n";
		}

	}
	while (!correctRChoice)
	{
		cout << "Which row is the card in that you would like to destroy? ('melee', 'ranged' or 'siege'): ";
		getline(cin,rowChoice);
		boost::algorithm::to_upper(rowChoice);
		if (rowChoice == "MELEE")
		{
			while (!correctSChoice)
			{
				cout << "\nWhich card in this row would you like to destroy? (Spell out the name exactly as shown above): ";
				getline(cin, scorchChoice);
				for (int i = 0; i < mTemp.size(); i++)
				{
					if (mTemp[i]->GetName() == scorchChoice)
					{
						correctSChoice = true;
						return mTemp[i]->GetName();
					}
				}
			}
		}
		else if (rowChoice == "RANGED")
		{
			cout << "\nWhich card in this row would you like to destroy? (Spell out the name exactly as shown above): ";
			getline(cin, scorchChoice);
			for (int i = 0; i < rTemp.size(); i++)
			{
				if (rTemp[i]->GetName() == scorchChoice)
				{
					correctSChoice = true;
					return rTemp[i]->GetName();
				}
			}
		}
		else if (rowChoice == "SIEGE")
		{
			cout << "\nWhich card in this row would you like to destroy? (Spell out the name exactly as shown above): ";
			getline(cin, scorchChoice);
			for (int i = 0; i < sTemp.size(); i++)
			{
				if (sTemp[i]->GetName() == scorchChoice)
				{
					correctSChoice = true;
					return sTemp[i]->GetName();
				}
			}
		}
	}


}

void Field::Scorched(string sChoice)
{
	for (int i = 0; i < melee.size(); i++)
	{
		if (melee[i]->GetName() == sChoice)
		{
			discard.push_back(melee[i]);
			melee.erase(melee.begin() + i);
		}
	}
	for (int i = 0; i < ranged.size(); i++)
	{
		if (ranged[i]->GetName() == sChoice)
		{
			discard.push_back(ranged[i]);
			ranged.erase(ranged.begin() + i);
		}
	}
	for (int i = 0; i < siege.size(); i++)
	{
		if (siege[i]->GetName() == sChoice)
		{
			discard.push_back(siege[i]);
			siege.erase(siege.begin() + i);
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
					Bond(card);
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
