#include "Deck.h"
#include <algorithm>
#include <ctime>
#include <fstream>


Deck::Deck()
{
}

Deck::Deck(int cards) //reserve the space for deck vector size (20)
{
	deck.reserve(cards);
}

/*void Deck::AddCard(Card card) //function to put all card objects into deck
{
	deck.push_back(card);
}*/
void Deck::ShuffleDeck() //shuffles deck
{
	srand(time(0));
	random_shuffle(deck.begin(), deck.end());
}

void Deck::readCardFile(string file)
{
	//read file variables
	Card * cardPtr;
	string inString;
	int inInt;
	int nCards;

	ifstream inFile(file);
	if (inFile.is_open())
	{
		inFile >> nCards;
		for (int i = 0; i < 1; i++)
		{
			cardPtr = new Card();
			inFile >> inString; //get name
			cardPtr->SetName(inString);
			inFile >> inString; //get type
			cardPtr->SetType(inString);
			inFile >> inString; //get effect
			cardPtr->SetEffect(inString);
			inFile >> inString; //get attack value
			inInt = stoi(inString);
			cardPtr->SetAttack(inInt);
			deck.push_back(cardPtr); 
		}
	}
}


void Deck::TakeFrom() //subtracts top card, when player draws
{
	deck.erase(deck.begin());
}

vector<Card *> Deck::GetDeck() //returns the private data, deck
{
	return deck;
}

Deck::~Deck()
{
}
