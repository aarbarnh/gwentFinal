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
	void ResetAttack();
	void DoubleAttack();
	void IncrementAttack();
	~Card();
private:
	string cardName;
	string cardType;
	string cardEffect;
	int attackValue;
	int attackNorm;
};

#endif

