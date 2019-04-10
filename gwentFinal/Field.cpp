#include "Field.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

Field::Field()
{
}

void Field::mPowAdd() //add all melee row attack value
{
	for (int i = 0; i < melee.size(); i++)
	{
		meleePower += melee[i]->GetAttack();
	}
}

void Field::rPowAdd() //add all ranged row attack value 
{
	for (int i = 0; i < ranged.size(); i++)
	{
		rangedPower += ranged[i]->GetAttack();
	}
}

void Field::sPowAdd() //add all siege row attack value 
{
	for (int i = 0; i < siege.size(); i++)
	{
		siegePower += siege[i]->GetAttack();
	}
}

void Field::tPowAdd() //add all attack values together
{
	totalPower = meleePower + rangedPower + siegePower;
}

void Field::Reset() //reset all rows after round
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

void Field::ResetPower() //reset power counts after round 
{
	meleePower = 0;
	rangedPower = 0;
	siegePower = 0;
	totalPower = 0;
	bondDoubles = 0;
}

void Field::ClearAll() //clear all after game
{
	hand.clear();
	melee.clear();
	ranged.clear();
	siege.clear();
	weather.clear();
	discard.clear();
}

void Field::DrawCard(vector<Card*> deck) //draw card
{
	vector<Card*> tempDeck = deck;
	hand.push_back(tempDeck[0]);
}

void Field::ShowHand() //show hand
{
	if (hand.empty()) //prompt if empty
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

void Field::ShowMelee() //show melee
{
	if (melee.empty()) //prompt if empty
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

void Field::ShowRanged() //show ranged
{
	if (ranged.empty()) //prompt if empty
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

void Field::ShowSiege() //show siege 
{
	if (siege.empty()) //prompt if empty
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

void Field::ShowDiscard() //show discard
{
	if (discard.empty()) //prompt if empty
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

void Field::ShowWeather() //show weather
{
	if (weather.empty()) //prompt if empty
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

void Field::PlayCard(string card) //play card, string parameter
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->GetName() == card) //if name matches, determine type then put in matching row (vector)
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

void Field::Medic() //medic effect for cards 
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
			for (int i = 0; i < discard.size(); i++) //look through discard for that card
			{
				if (discard[i]->GetName() == reviveCard)
				{
					if (discard[i]->GetType() == "Weather" || discard[i]->GetType() == "Instant") //can't bring back weather/instant
					{
						cout << "\n\nYou cannot bring back a weather or instant card. Please choose one of your unit cards (melee, ranged, or siege).\n";
					}
					else
					{
						if (discard[i]->GetType() == "Melee") //determine type
						{
							if (bFActivated) //if weather active affect attack value
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

void Field::ClearWeather() //clear weather card effect
{
	for (int i = 0; i < weather.size(); i++)
	{
		discard.push_back(weather[i]);
	}
	weather.clear(); //clear weather and reset bools
	bFActivated = false;
	iFActivated = false;
	tRActivated = false;
	for (int i = 0; i < melee.size(); i++) //reset all attacks to norm
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

void Field::CommandersHorn() //commanders horn effect 
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
			for (int i = 0; i < melee.size(); i++) //increase row 
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

void Field::BitingFrost() //biting frost effect
{
	bFActivated = true;
	for (int i = 0; i < melee.size(); i++)
	{
		melee[i]->SetAttack(1);
	}
}

void Field::ImpenetrableFog() //imprenetrable fog effect 
{
	iFActivated = true;
	for (int i = 0; i < ranged.size(); i++)
	{
		ranged[i]->SetAttack(1);
	}
}

void Field::TorrentialRain() //torrential rain effect 
{
	tRActivated = true;
	for (int i = 0; i < siege.size(); i++)
	{
		siege[i]->SetAttack(1);
	}
}

void Field::Bond(string card) //bond effect, use of boost to get rid of digit identifiers
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
	if (bondDoubles > 1) //if more than 1 copy of a card in row (all bonds are melee) double both
	{
		for (int i = 0; i < melee.size(); i++)
		{
			melee[i]->DoubleAttack();
		}
	}
}

void Field::Morale(Card * typeCheck) //morale effect 
{
	if (typeCheck->GetType() == "Melee") //determine type to affect row
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

void Field::SortHand() //sort hand using swap and nested for
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

int Field::GetTPow() //getter for total
{
	return totalPower;
}

string Field::Scorch(vector<Card*>mRow, vector<Card*>rRow, vector<Card*>sRow) //scorch effect 
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
			cout << "Would you like to see the other players zones? ('Y' for yes, 'N' for no): "; //let player see rows of opponent
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
	while (!correctRChoice) //decide which row to scorch in
	{
		cout << "Which row is the card in that you would like to destroy? ('melee', 'ranged' or 'siege'): ";
		getline(cin,rowChoice);
		boost::algorithm::to_upper(rowChoice);
		if (rowChoice == "MELEE")
		{
			while (!correctSChoice) //decide which card to scorch in that row 
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
			while (!correctSChoice)
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
		}
		else if (rowChoice == "SIEGE")
		{
			while (!correctSChoice)
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


}

void Field::Scorched(string sChoice) //scorched effect, pairs with scorch in game.cpp
{
	for (int i = 0; i < melee.size(); i++) //look through all rows, find card to destroy
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

void Field::ActivateEffect(string card) //activate card effects 
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->GetName() == card)
		{
			if (hand[i]->GetType() == "Instant" || hand[i]->GetType() == "Weather") //if weather/instant type
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
			else //if melee,ranged, or siege
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

vector<Card*> Field::GetHand() //getter hand
{
	return hand;
}

vector<Card*> Field::GetMelee() //getter melee
{
	return melee;
}

vector<Card*> Field::GetRanged() //getter ranged
{
	return ranged;
}

vector<Card*> Field::GetSiege() //getter siege
{
	return siege;
}

vector<Card*> Field::GetWeather() //getter weather
{
	return weather;
}

vector<Card*> Field::GetDiscard() //getter discard
{
	return discard;
}

Field::~Field() //destructor
{
}
