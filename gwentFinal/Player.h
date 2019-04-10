#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Field.h"

using namespace std;

class Player
{
public:
	Player();
	Player(string ability); //set player ability
	//getters
	string GetAbility();
	bool GetMonsterAbil();
	//setter
	void SetMonsterAbil(bool state);
	~Player();
private:
	string pAbility;
	bool monsterAbil; //test if monster player can use ability (only once per game)
};

#endif

