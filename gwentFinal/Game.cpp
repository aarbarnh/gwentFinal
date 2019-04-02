#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <memory>
#include <fstream> //read from files 
#include <ctime> //for time()

using namespace std;

//function prototypes
void StartScreen();
void HelpScreen();
string CoinFlip();


int main()
{
	srand(time(0)); //seed rand
	string playerDeckChoice;
	string aiDeckChoice;
	int playerWins = 0;
	int aiWins = 0;
	bool correctDeckChoice = false;

	//three decks for the game, if created in if statement, destroyed outside of scope
	unique_ptr<Deck> pElfDeck(new Deck(20));
	unique_ptr<Deck> pNorthDeck(new Deck(20));
	unique_ptr<Deck> pMonsterDeck(new Deck(20));

	do //loop for deck choice
	{
		while (!correctDeckChoice)
		{
			cout << "Which deck would you like to choose? (Type 'elf' for Scoia'tael, 'northern' for Northern Realms, or 'monster' for Monsters)\nDeck choice: "; //player chooses his/her own deck
			cin >> playerDeckChoice;
			if (playerDeckChoice == "northern")
			{
				pNorthDeck->readCardFile("northDeck.txt");
			}
			vector<Card *> tempDeck = pNorthDeck->GetDeck();
			for (int i = 0; i < tempDeck.size();i++)
			{
				cout << tempDeck[i]->GetName() << "\n" << tempDeck[i]->GetType() << "\n" << tempDeck[i]->GetEffect() << "\n" << tempDeck[i]->GetAttack() << "\n\n";
			}
		}
		cout << "\nWhich deck would you like the AI to use?\nDeck choice for AI: "; //player chooses AI deck
		cin >> aiDeckChoice;
		do //loop for game (turns, get actions)
		{
			
		} while (playerWins < 2 && aiWins < 2);
	}
	while (true);
	system("pause");
	return 0;
}

string CoinFlip()
{
	int flip = rand() % 2 + 1;
	if (flip == 1)
	{
		return "Heads";
	}
	else
	{
		return "Tails";
	}
}
