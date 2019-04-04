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

void Deck::Muster(string card)
{
	//implement later
}

void Deck::ShuffleDeck() //shuffles deck
{
	srand(time(0));
	random_shuffle(deck.begin(), deck.end());
}

void Deck::readCardFile(string file)
{
	//read file variables
	Card * cardPtr; //declare a pointer
	string inString;
	int inInt;
	int nCards;

	ifstream inFile(file);
	if (inFile.is_open())
	{
		getline(inFile, inString);
		nCards = stoi(inString);
		for (int i = 0; i < nCards; i++)
		{
			cardPtr = new Card(); //assign it to new Card
			getline(inFile, inString); //get name
			cardPtr->SetName(inString);
			getline(inFile,inString); //get type
			cardPtr->SetType(inString);
			getline(inFile,inString); //get effect
			cardPtr->SetEffect(inString);
			getline(inFile,inString); //get attack value
			inInt = stoi(inString);
			cardPtr->SetAttack(inInt);
			deck.push_back(cardPtr);
		}
	}
	inFile.close();
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
