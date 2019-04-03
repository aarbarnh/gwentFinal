#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "Deck.h"

using namespace std;

class Field
{
public:
	Field();
	~Field();
	void DrawCard(vector<Card*> deck);
	void ShowHand();
	void PlayCard(string card);
	void mPowAdd();
	void rPowAdd();
	void sPowAdd();
	void tPowAdd();
private:
	int meleePower;
	int rangedPower;
	int siegePower;
	int totalPower;
	vector<Card *> hand;
	vector<Card *> melee;
	vector<Card *> ranged;
	vector<Card *> siege;
	vector<Card *> discard;
	vector<Card *> weather;
};

#endif

