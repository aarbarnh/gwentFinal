#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

using namespace std;

class Card
{
public:
	Card();
	Card(string name, string type, string effect, int attack); //constructor to initialize values
	//getters
	string GetName();
	string GetType();
	string GetEffect();
	int GetAttack();
	//setters
	void SetName(string name);
	void SetType(string type);
	void SetEffect(string effect);
	void SetAttack(int attack);
	void SetAttackNorm(int attack);
	//functions for card effects
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

