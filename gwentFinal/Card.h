#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

using namespace std;

class Card
{
public:
	Card();
	Card(string name, string type, string effect, int attack);
	string GetName();
	string GetType();
	string GetEffect();
	void SetName(string name);
	void SetType(string type);
	void SetEffect(string effect);
	void SetAttack(int attack);
	int GetAttack();
	//card effects
	//void Medic(vector<Card*> discard,string card);
	//void Muster(/*add parameters*/);
	//void Scorch(/*add parameters*/);
	//void Bond(/*add parameters*/);
	//void Morale(/*add parameters*/);
	//void ClearWeather(/*add parameters*/); MOVED TO FIELD
	//void BitingFrost(/*add parameters*/);
	//void ImpenetrableFog(/*add parameters*/);
	//void TorrentialRain(/*add parameters*/);
	//void CommandersHorn(/*add parameters*/);
	~Card();
private:
	string cardName;
	string cardType;
	string cardEffect;
	int attackValue;
	int attackNorm;
};

#endif

