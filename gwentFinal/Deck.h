#ifndef DECK_H
#define DECK_H
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
public:
	Deck();
	Deck(int cards);
	void readCardFile(string file);
	void ShuffleDeck();
	void TakeFrom();
	//effects
	void Muster(string card);
	vector<Card *> GetDeck();
	~Deck();
private:
	vector<Card *> deck;
};

#endif
