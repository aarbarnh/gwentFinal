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
	string p1DeckChoice;
	string p2DeckChoice;
	string flipChoice;
	string flipResult;
	int playerOneWins = 0;
	int playerTwoWins = 0;
	bool correctDeckChoice = false;
	bool correctAiChoice = false;
	bool correctCall = false;

	//three decks for the game, if created in if statement, destroyed outside of scope
	unique_ptr<Deck> pElfDeck(new Deck(20));
	unique_ptr<Deck> pNorthDeck(new Deck(20));
	unique_ptr<Deck> pMonsterDeck(new Deck(20));
	//three fields (elf, monster, northern)
	unique_ptr<Field> pElfField(new Field());
	unique_ptr<Field> pMonsterField(new Field());
	unique_ptr<Field> pNorthernField(new Field());
	//three players (elf, monster, northern)
	unique_ptr<Field> pElf(new Field());
	unique_ptr<Field> pMonster(new Field());
	unique_ptr<Field> pNorthern(new Field());

	do //loop for deck choice
	{
		while (!correctDeckChoice)
		{
			cout << "Player One, which deck would you like to choose? (Type 'elf' for Scoia'tael, 'northern' for Northern Realms, or 'monster' for Monsters)\nYour deck choice: "; //player1 chooses his/her own deck
			cin >> p1DeckChoice;
			if (p1DeckChoice == "northern")
			{
				pNorthDeck->readCardFile("northDeck.txt");
				pNorthDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Northern Realms deck has been built and shuffled...\n\n";
			}
			else if (p1DeckChoice == "elf")
			{
				pElfDeck->readCardFile("elfDeck.txt");
				pElfDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Scoia'tael deck has been built and shuffled...\n\n";
				//pElfField->DrawCard(pElfDeck->GetDeck()); //save for later, don't forget how to format
				//pElfField->ShowHand();
			}
			else if (p1DeckChoice == "monster")
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
			cout << "Player Two, which deck would you like to use? You cannot pick the same deck as Player One.\nYour deck choice: "; //player2 chooses deck
			cin >> p2DeckChoice;
			if (p2DeckChoice == "northern")
			{
				if (p2DeckChoice == p1DeckChoice)
				{
					cout << "\nYou cannot have the same deck as Player One. Please choose again.\n\n";
				}
				else
				{
					pNorthDeck->readCardFile("northDeck.txt");
					pNorthDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nYour Northern Realms deck has been built and shuffled...\n\n";
				}
			}
			else if (p2DeckChoice == "elf")
			{
				if (p2DeckChoice == p1DeckChoice)
				{
					cout << "You cannot have the same deck as Player One. Please choose again.\n\n";
				}
				else
				{
					pElfDeck->readCardFile("elfDeck.txt");
					pElfDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nYour Scoia'tael deck has been built and shuffled...\n\n";
				}
			}
			else if (p2DeckChoice == "monster")
			{
				if (p2DeckChoice == p1DeckChoice)
				{
					cout << "You cannot have the same deck as Player One. Please choose again.\n\n";
				}
				else
				{
					pMonsterDeck->readCardFile("monsterDeck.txt");
					pMonsterDeck->ShuffleDeck();
					correctAiChoice = true;
					cout << "\nYour Monsters deck has been built and shuffled...\n\n";
				}
			}
			else
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}

		while (!correctCall)
		{
			cout << "A coin will be flipped to determine who goes and who goes second.\nPlayer One will call it. If right Player One will go first, if wrong Player Two will go first.\n\nWould you like to call heads or tails? (Type 'heads' or 'tails'): ";
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
		if (flipResult == flipChoice) //p1 goes first
		{
			system("pause");
			system("CLS");
			cout << "Player One drawing cards..." << "\n\n";
			//player one drawing
			if (p1DeckChoice == "elf")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
			}
			else if (p1DeckChoice == "northern")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
			}

			//player two drawing
			cout << "Player Two drawing cards..." << "\n\n";
			if (p2DeckChoice == "elf")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
			}
			else if (p2DeckChoice == "northern")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
			}
			do //loop for game (turns, get actions)
			{
				if (p1DeckChoice == "northern")
				{
					
				}
			} while (playerOneWins < 2 && playerTwoWins < 2);
		}
		else //p2 goes first
		{
			system("pause");
			system("cls");
			//player two drawing
			cout << "Player Two drawing cards..." << "\n\n";
			if (p2DeckChoice == "elf")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
			}
			else if (p2DeckChoice == "northern")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
			}
			cout << "Player One drawing cards..." << "\n\n";
			//player one drawing
			if (p1DeckChoice == "elf")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
			}
			else if (p1DeckChoice == "northern")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
			}

			do
			{
				
			} while (playerOneWins < 2 && playerTwoWins < 2);
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
		return "heads";
	}
	else
	{
		return "tails";
	}
}
