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
	void ShowMelee();
	void ShowRanged();
	void ShowSiege();
	void ShowWeather();
	void ShowDiscard();
	void PlayCard(string card);
	void ActivateEffect(string card);
	void mPowAdd();
	void rPowAdd();
	void sPowAdd();
	void tPowAdd();
	//effects
	void ClearWeather();
	void BitingFrost();
	void ImpenetrableFog();
	void TorrentialRain();
	void CommandersHorn();
	void Reset(); //end of round resets!
	void ClearAll(); //end of round clear rows
	void ResetPower(); //end of round power reset, wont affect new rounds
	void Medic();
	int GetTPow();
	string Scorch(vector<Card*>mRow,vector<Card*>rRow,vector<Card*>sRow);
	void Scorched(string sChoice);
	void Bond(string card);
	void Morale(Card * typeCheck);
	//getters
	vector<Card*> GetHand();
	vector<Card*> GetMelee();
	vector<Card*> GetRanged();
	vector<Card*> GetSiege();
	vector<Card*> GetWeather();
	vector<Card*> GetDiscard();
private:
	int meleePower;
	int rangedPower;
	int siegePower;
	int totalPower;
	int bondDoubles;
	vector<Card *> hand;
	vector<Card *> melee;
	vector<Card *> ranged;
	vector<Card *> siege;
	vector<Card *> discard;
	vector<Card *> weather;
	bool bFActivated;
	bool iFActivated;
	bool tRActivated;
};

#endif

