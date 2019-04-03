#include "Card.h"
#include "Deck.h"
#include "Field.h"
#include <iostream>
#include <memory>
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
	string flipChoice;
	string flipResult;
	int playerWins = 0;
	int aiWins = 0;
	bool correctDeckChoice = false;
	bool correctAiChoice = false;
	bool correctCall = false;

	//three decks for the game, if created in if statement, destroyed outside of scope
	unique_ptr<Deck> pElfDeck(new Deck(20));
	unique_ptr<Field> pElfField(new Field());
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
				pNorthDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Northern Realms deck has been built and shuffled...\n\n";
			}
			else if (playerDeckChoice == "elf")
			{
				pElfDeck->readCardFile("elfDeck.txt");
				pElfDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Scoia'tael deck has been built and shuffled...\n\n";
				//pElfField->DrawCard(pElfDeck->GetDeck()); //save for later, don't forget how to format
				//pElfField->ShowHand();
			}
			else if (playerDeckChoice == "monster")
			{
				pMonsterDeck->readCardFile("monsterDeck.txt");
				pMonsterDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Monsters deck has been built and shuffled...\n\n";
			}
			else
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}
		while (!correctAiChoice)
		{
			cout << "Which deck would you like the AI to use? You cannot pick the same deck you picked for yourself.\nDeck choice for AI: "; //player chooses AI deck
			cin >> aiDeckChoice;
			if (aiDeckChoice == "northern")
			{
				if (aiDeckChoice == playerDeckChoice)
				{
					cout << "\nYou cannot have the same deck as the AI. Please choose again.\n\n";
				}
				else
				{
					pNorthDeck->readCardFile("northDeck.txt");
					pNorthDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nThe AI's Northern Realms deck has been built and shuffled...\n\n";
				}
			}
			else if (aiDeckChoice == "elf")
			{
				if (aiDeckChoice == playerDeckChoice)
				{
					cout << "You cannot have the same deck as the AI. Please choose again.\n\n";
				}
				else
				{
					pElfDeck->readCardFile("elfDeck.txt");
					pElfDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nThe AI's Scoia'tael deck has been built and shuffled...\n\n";
				}
			}
			else if (aiDeckChoice == "monster")
			{
				if (aiDeckChoice == playerDeckChoice)
				{
					cout << "You cannot have the same deck as the AI. Please choose again.\n\n";
				}
				else
				{
					pMonsterDeck->readCardFile("monsterDeck.txt");
					pMonsterDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nThe AI's Monsters deck has been built and shuffled...\n\n";
				}
			}
			else
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}

		while (!correctCall)
		{
			cout << "A coin will be flipped to determine who goes and who goes second.\nIf you call it right, you will go first.\n\nWould you like to call heads or tails? (Type 'heads' or 'tails'): ";
			try //make sure player calls only heads or tails 
			{
				cin >> flipChoice;
				if (flipChoice == "heads" || flipChoice == "tails")
				{
					correctCall = true;
				}
				else
				{
					throw "There is only two sides to a coin, heads or tails. Choose again.";
				}
			}
			catch (const char * msg)
			{
				cout << "\n" << msg << "\n\n";
			}	
		}
		flipResult = CoinFlip();
		if (flipResult == flipChoice)
		{
			do //loop for game (turns, get actions)
			{

			} while (playerWins < 2 && aiWins < 2);
		}
		else
		{
			do
			{
				
			} while (playerWins < 2 && aiWins < 2);
		}
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
