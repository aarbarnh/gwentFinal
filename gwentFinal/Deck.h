#ifndef DECK_H
#define DECK_H
#include <vector>
#include "Card.h"

using namespace std;

class Deck //deck class
{
public:
	Deck();
	Deck(int cards); //deck constructor to reserve spacec
	void readCardFile(string file); //file i/o function to read in cards 
	void ShuffleDeck(); //randomize deck
	void TakeFrom(); //take from, after draw
	void ResetDeck(); //reset
	vector<Card *> GetDeck(); //getter
	~Deck();
private:
	vector<Card *> deck;
};

#endif
