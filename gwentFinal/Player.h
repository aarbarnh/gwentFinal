#ifndef PLAYER_H
#define PLAYER_H
#include <string>

using namespace std;

class Player
{
public:
	Player();
	Player(string ability);
	string GetAbility();
	~Player();
private:
	string pAbility;
};

#endif

