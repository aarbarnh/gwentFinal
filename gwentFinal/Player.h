#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Field.h"

using namespace std;

class Player
{
public:
	Player();
	Player(string ability);
	string GetAbility();
	bool GetMonsterAbil();
	void SetMonsterAbil(bool state);
	~Player();
private:
	string pAbility;
	bool monsterAbil;
};

#endif

