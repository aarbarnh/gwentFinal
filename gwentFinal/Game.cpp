#include "Card.h"
#include "Deck.h"
#include "Field.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <ctime> //for time()

using namespace std;

//function prototypes
void StartScreen();
void HelpScreen();
void PrintCrown(int wins);
bool PlayerPass();
string CoinFlip();


int main()
{
	system("color 0C"); //change background and text colors
	srand(time(0)); //seed rand
	string p1DeckChoice;
	string p2DeckChoice;
	string flipChoice;
	string flipResult;
	string playerOneChoice;
	string playerTwoChoice;
	bool mainGame = true;
	bool p1Pass = false;
	bool p2Pass = false;
	//three player pointers (might have too many pointers)
	unique_ptr<Player> monsterPlayer(new Player("Free Commander's Horn"));
	unique_ptr<Player> northernPlayer(new Player("Draw one card if you won the round."));
	unique_ptr<Player> elfPlayer(new Player("Draw one extra card at the start of the game."));
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

	StartScreen();
	do //loop for deck choice
	{
		int playerOneWins = 0;
		int playerTwoWins = 0;
		bool correctDeckChoice = false;
		while (!correctDeckChoice)
		{
			cout << "Player One, which deck would you like to choose? (Type 'elf' for Scoia'tael, 'northern' for Northern Realms, or 'monster' for Monsters)\nYour deck choice: "; //player1 chooses his/her own deck
			getline(cin,p1DeckChoice);
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
			}
			else if (p1DeckChoice == "monster")
			{
				pMonsterDeck->readCardFile("monsterDeck.txt");
				pMonsterDeck->ShuffleDeck();
				monsterPlayer->SetMonsterAbil(true);
				correctDeckChoice = true;
				cout << "\nYour Monsters deck has been built and shuffled...\n\n";
			}
			else
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}
		bool correctP2Choice = false;
		while (!correctP2Choice)
		{
			cout << "Player Two, which deck would you like to use? You cannot pick the same deck as Player One.\nYour deck choice: "; //player2 chooses deck
			getline(cin,p2DeckChoice);
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
					correctP2Choice = true;
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
					correctP2Choice = true;
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
					correctP2Choice = true;
					cout << "\nYour Monsters deck has been built and shuffled...\n\n";
				}
			}
			else
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}
		bool correctCall = false;
		while (!correctCall)
		{
			cout << "A coin will be flipped to determine who goes and who goes second.\nPlayer One will call it. If right Player One will go first, if wrong Player Two will go first.\n\nWould you like to call heads or tails? (Type 'heads' or 'tails'): ";
			try //make sure player calls only heads or tails 
			{
				getline(cin,flipChoice);
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
			cout << "\nPlayer One has called the flip, Player One goes first!\n\n";
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
				if (p1DeckChoice == "northern") //turn dependent on p1 deck choice
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pNorthernField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pNorthernField->GetHand();
							cout << "\n";
							pNorthernField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin,playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pNorthernField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pNorthernField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard);
										rightCard = true;
									}
								}
							}
							p1TurnChoice = true;
							system("pause");
							system("cls");
						}
						else if (playerOneChoice == "hand")
						{
							pNorthernField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pNorthernField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pNorthernField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pNorthernField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pNorthernField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Northern Realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p1DeckChoice == "elf")
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pElfField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pElfField->GetHand();
							cout << "\n";
							pElfField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin,playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" <<  playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "northern")
											{
												string tempName = pElfField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
											else
											{
												string tempName = pElfField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true;
						}
						else if (playerOneChoice == "hand")
						{
							pElfField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pElfField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pElfField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pElfField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pElfField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pElfField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Scoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pMonsterField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pMonsterField->GetHand();
							cout << "\n";
							pMonsterField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth")
										{
											cout << "Scorch was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pMonsterField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pMonsterField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pNorthernField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pNorthernField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pNorthernField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true;
						}
						else if (playerOneChoice == "hand")
						{
							pMonsterField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pMonsterField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pMonsterField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pMonsterField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pMonsterField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Monster ability: " << monsterPlayer->GetAbility() << "\n\n";
							char abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil())
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									cin >> abilUse;
									if (abilUse == 'Y' || abilUse == 'y')
									{
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == 'N' || abilUse == 'n')
									{
										cout << "\n\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\n\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//turn dependent on p2 deck choice 
				if (p2DeckChoice == "northern")
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pNorthernField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pNorthernField->GetHand();
							cout << "\n";
							pNorthernField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pNorthernField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pNorthernField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pNorthernField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pNorthernField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pNorthernField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pNorthernField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pNorthernField->ShowWeather();
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Northern Realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p2DeckChoice == "elf")
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pElfField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pElfField->GetHand();
							cout << "\n";
							pElfField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "northern")
											{
												string tempName = pElfField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
											else
											{
												string tempName = pElfField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pElfField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pElfField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pElfField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pElfField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pElfField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pElfField->ShowWeather();
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Scoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pMonsterField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pMonsterField->GetHand();
							cout << "\n";
							pMonsterField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth")
										{
											cout << playCard << " was activated!\n\n";
											if (p1DeckChoice == "elf")
											{
												string tempName = pMonsterField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pMonsterField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pNorthernField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pNorthernField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pNorthernField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pMonsterField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pMonsterField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pMonsterField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pMonsterField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pMonsterField->ShowWeather();
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Monster ability: " << monsterPlayer->GetAbility() << "\n\n";
							char abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil())
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									cin >> abilUse;
									if (abilUse == 'Y' || abilUse == 'y')
									{
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == 'N' || abilUse == 'n')
									{
										cout << "\n\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\n\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//end of the round, both players pass 
				if (p1Pass && p2Pass)
				{
					int p1RoundTotal = 0;
					int p2RoundTotal = 0;
					cout << "Totaling the attack values for both players for the round...\n\nDetermining winner...\n\n";
					if (p1DeckChoice == "elf") //p1 add up
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p1RoundTotal = pElfField->GetTPow();
					}
					else if (p1DeckChoice == "northern")
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p1RoundTotal = pNorthernField->GetTPow();
					}
					else if (p1DeckChoice == "monster")
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p1RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player One Total Attack Value: " << p1RoundTotal << "\n";
					//p2 add up
					if (p2DeckChoice == "elf") //p1 add up
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p2RoundTotal = pElfField->GetTPow();
					}
					else if (p2DeckChoice == "northern")
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p2RoundTotal = pNorthernField->GetTPow();
					}
					else if (p2DeckChoice == "monster")
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p2RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player Two Total Attack Value: " << p2RoundTotal << "\n\n";
					//compare attack values, give win
					if (p1RoundTotal > p2RoundTotal)
					{
						playerOneWins++;
						cout << "Player One wins the round!\n\n";
						PrintCrown(playerOneWins);
						if (p1DeckChoice == "northern") //allow northern to draw one card because of win
						{
							cout << "\n\nAs Northern Realms, Player One gets to draw one card for the round win.\n\n";
							pNorthernField->DrawCard(pNorthDeck->GetDeck());
							pNorthDeck->TakeFrom();
							pNorthernField->Reset(); 
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p2DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					else if (p1RoundTotal < p2RoundTotal)
					{
						playerTwoWins++;
						cout << "Player Two wins the round!\n\n";
						PrintCrown(playerTwoWins);
						if (p2DeckChoice == "northern")
						{
							cout << "\n\nAs Northern Realms, Player Two gets to draw one card for the round win.\n\n";
							pNorthernField->DrawCard(pNorthDeck->GetDeck());
							pNorthDeck->TakeFrom();
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p1DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					else
					{
						playerOneWins++;
						playerTwoWins++;
						cout << "The round was a tie! Both players get the round point.\n\n";
						if (p1DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						if (p2DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					p1Pass = false;
					p2Pass = false;
					system("pause");
					system("cls");
				}

			} while (playerOneWins < 2 && playerTwoWins < 2);
		}
		else //p2 goes first
		{
			cout << "\nPlayer Two has called the flip, Player Two goes first!\n\n";
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
				if (p2DeckChoice == "northern") //turn dependent on p2 deck choice 
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pNorthernField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pNorthernField->GetHand();
							cout << "\n";
							pNorthernField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pNorthernField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pNorthernField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pNorthernField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pNorthernField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pNorthernField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pNorthernField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pNorthernField->ShowWeather();
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Northern Realms ability" << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p2DeckChoice == "elf")
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pElfField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pElfField->GetHand();
							cout << "\n";
							pElfField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "northern")
											{
												string tempName = pElfField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
											else
											{
												string tempName = pElfField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "northern")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pElfField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pElfField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pElfField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pElfField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pElfField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pElfField->ShowWeather();
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Scoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pMonsterField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						if (playerTwoChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pMonsterField->GetHand();
							cout << "\n";
							pMonsterField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth")
										{
											cout << playCard << " was activated!\n\n";
											if (p1DeckChoice == "elf")
											{
												string tempName = pMonsterField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pMonsterField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pNorthernField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pNorthernField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pNorthernField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p1DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true;
						}
						else if (playerTwoChoice == "hand")
						{
							pMonsterField->ShowHand();
						}
						else if (playerTwoChoice == "melee")
						{
							pMonsterField->ShowMelee();
						}
						else if (playerTwoChoice == "ranged")
						{
							pMonsterField->ShowRanged();
						}
						else if (playerTwoChoice == "siege")
						{
							pMonsterField->ShowSiege();
						}
						else if (playerTwoChoice == "discard")
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerTwoChoice == "weather")
						{
							pMonsterField->ShowWeather();
						}
						else if (playerTwoChoice == "ability")
						{
							cout << "Monster ability: " << monsterPlayer->GetAbility() << "\n\n";
							char abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil())
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									cin >> abilUse;
									if (abilUse == 'Y' || abilUse == 'y')
									{
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == 'N' || abilUse == 'n')
									{
										cout << "\n\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\n\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerTwoChoice == "pass")
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//turn dependent on p1 deck choice
				if (p1DeckChoice == "northern")
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pNorthernField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pNorthernField->GetHand();
							cout << "\n";
							pNorthernField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pNorthernField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pNorthernField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true;
						}
						else if (playerOneChoice == "hand")
						{
							pNorthernField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pNorthernField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pNorthernField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pNorthernField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pNorthernField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Northern realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p1DeckChoice == "elf")
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pElfField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pElfField->GetHand();
							cout << "\n";
							pElfField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "northern")
											{
												string tempName = pElfField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
											else
											{
												string tempName = pElfField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->BitingFrost();
											}
											else
											{
												pMonsterField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->ImpenetrableFog();
											}
											else
											{
												pMonsterField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->TorrentialRain();
											}
											else
											{
												pMonsterField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "northern")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true;
						}
						else if (playerOneChoice == "hand")
						{
							pElfField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pElfField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pElfField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pElfField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pElfField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pElfField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Scoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pMonsterField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						if (playerOneChoice == "play")
						{
							string playCard;
							bool rightCard = false;
							vector<Card*> tempHand = pMonsterField->GetHand();
							cout << "\n";
							pMonsterField->ShowHand();
							while (!rightCard)
							{
								cout << "\n\nWhat card would you like play? (Type the name of the card you'd like to play exactly): ";
								getline(cin, playCard);
								for (int i = 0; i < tempHand.size(); i++)
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth")
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "elf")
											{
												string tempName = pMonsterField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege());
												pElfField->Scorched(tempName);
											}
											else
											{
												string tempName = pMonsterField->Scorch(pNorthernField->GetMelee(), pNorthernField->GetRanged(), pNorthernField->GetSiege());
												pNorthernField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->BitingFrost();
											}
											else
											{
												pNorthernField->BitingFrost();
											}
										}
										else if (tempHand[i]->GetName() == "Impenetrable Fog")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ImpenetrableFog();
											}
											else
											{
												pNorthernField->ImpenetrableFog();
											}
										}
										else if (tempHand[i]->GetName() == "Torrential Rain")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->TorrentialRain();
											}
											else
											{
												pNorthernField->TorrentialRain();
											}
										}
										else if (tempHand[i]->GetName() == "Clear Weather")
										{
											if (p2DeckChoice == "elf")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard);
										rightCard = true;
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true;
						}
						else if (playerOneChoice == "hand")
						{
							pMonsterField->ShowHand();
						}
						else if (playerOneChoice == "melee")
						{
							pMonsterField->ShowMelee();
						}
						else if (playerOneChoice == "ranged")
						{
							pMonsterField->ShowRanged();
						}
						else if (playerOneChoice == "siege")
						{
							pMonsterField->ShowSiege();
						}
						else if (playerOneChoice == "discard")
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerOneChoice == "weather")
						{
							pMonsterField->ShowWeather();
						}
						else if (playerOneChoice == "ability")
						{
							cout << "Monster ability: " << monsterPlayer->GetAbility() << "\n\n";
							char abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil())
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									cin >> abilUse;
									if (abilUse == 'Y' || abilUse == 'y')
									{
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == 'N' || abilUse == 'n')
									{
										cout << "\n\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\n\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerOneChoice == "pass")
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "help")
						{
							HelpScreen();
						}
						else
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//end of the round, both players pass 
				if (p1Pass && p2Pass)
				{
					int p1RoundTotal = 0;
					int p2RoundTotal = 0;
					cout << "Totaling the attack values for both players for the round...\n\nDetermining winner...\n\n";
					if (p1DeckChoice == "elf") //p1 add up
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p1RoundTotal = pElfField->GetTPow();
					}
					else if (p1DeckChoice == "northern")
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p1RoundTotal = pNorthernField->GetTPow();
					}
					else if (p1DeckChoice == "monster")
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p1RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player One Total Attack Value: " << p1RoundTotal << "\n";
					//p2 add up
					if (p2DeckChoice == "elf") //p1 add up
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p2RoundTotal = pElfField->GetTPow();
					}
					else if (p2DeckChoice == "northern")
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p2RoundTotal = pNorthernField->GetTPow();
					}
					else if (p2DeckChoice == "monster")
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p2RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player Two Total Attack Value: " << p2RoundTotal << "\n\n";
					//compare attack values, give win
					if (p1RoundTotal > p2RoundTotal)
					{
						playerOneWins++;
						cout << "Player One wins the round!\n\n";
						PrintCrown(playerOneWins);
						if (p1DeckChoice == "northern")
						{
							cout << "\n\nAs Northern Realms, Player One gets to draw one card for the round win.\n\n";
							pNorthernField->DrawCard(pNorthDeck->GetDeck());
							pNorthDeck->TakeFrom();
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p2DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					else if (p1RoundTotal < p2RoundTotal)
					{
						playerTwoWins++;
						cout << "Player Two wins the round!\n\n";
						PrintCrown(playerTwoWins);
						if(p2DeckChoice == "northern")
						{
							cout << "\n\nAs Northern Realms, Player Two gets to draw one card for the round win.\n\n";
							pNorthernField->DrawCard(pNorthDeck->GetDeck());
							pNorthDeck->TakeFrom();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p1DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					else
					{
						playerOneWins++;
						playerTwoWins++;
						cout << "The round was a tie! Both players get the round point.\n\n";
						if (p1DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						if (p2DeckChoice == "northern")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "elf")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						pNorthernField->ResetPower();
						pElfField->ResetPower();
						pMonsterField->ResetPower();
					}
					p1Pass = false;
					p2Pass = false;
					system("pause");
					system("cls");
				}
			} while (playerOneWins < 2 && playerTwoWins < 2);
		}
		//post game, ask to replay
		if (playerOneWins > playerTwoWins)
		{
			cout << "Player One has won at Gwent against Player Two!\n\n";
			cout << R"(                                           & @.                                          
                                         %,#,(,%.                                        
                                       %*,,%#./.#%.                                      
                                     %*,((/(% #./,#%.                                    
                                  *%/*((((/.%.%,(//,#(*                                  
                                 %*.(/(//((*%(/,///*/,#%.                                
                               %*,///(((///(*%.*,///(((,%%.                              
                             %*,((((/////((/,# #./(/////(,%%.                            
/*                         %/,/(((((/////(///%*%./////*////.%%*                        *(
//#.                     &,.(#((((((//(//(/((/%*,*////*/////(.#&                     .(*&
/,.%#.                   %*/((((/////(//////*,# ,.//(///////((/@                   .(//*&
(,((.##                  %*///*/(//////////&@%#,#./*//(///((/(*@                 .(/*(#,&
(,(#((.##*               %*/(/////****///&%   %##./////((((/(//@               *///#(((,&
(,(((((/.##              %*///******//,  %(   ,.,/////((//*//@             .(*/((((((*&
/.#(((((#(.##            %******,***.%#  %, (     &%**/***/**//@           .(*/////////,&
/,##((#((///.(#          %*/*******%#  %,...(   ,%  &&.********@         .(*//(/((//(*/,&
/./#(/(//(////.(#,       %******,%(  %,...,&&   # ,&  (&,,*****@       *(,((///*/**////,&
/.//**/**//(((#(./(,     %**,*,#(  %,...,%/%&   #...*#. (&*,,**@     */.*/(///****/****,&
/./*,,***,/*/((/**.(%    %**.%#  %, ...%(,/%&  .@&*...*&  %&,**@   .(,/(///*/**,****///.&
/.*/*/**/*/**///,,#&.    %,#(  %,....%(,.*/%@  %(@,...,&  %&(&    .@*//**/**,,,,,,,*,.&
/.**/,**/**,*//,.%(      &(  %,.,.*%/...,//%@  @&%**(%*.,.,&  *%      ((**,*,,***,,,***.%
/.,,***/*,,*/,,,.%(      %  /#.,..@@///*/%@ .@%%%&&@@..../(  %      ((,(//*,,,,*,,,,*.&
/ ,,,***,,,,,,,*.%(      %*%  %(....@@&(/**%@ #&%%&@@,.../&  #.@      ((,//,,,*,,.*,,,*.&
/.,,,,,**,,,,,,,,%(      %..*%  %/....@@%(%@( @%&@@....*&  #, /&      (/,,**//***,,*,,,.%
/.,,,,,,,,,......%&%%    %..,.*%  %/....&@@( @&@@....*&  %..**/&    %%&(,******,,,,,,,,.%
/.,,,..,.,,.,. .....*(   %.,,...*#  /(....& &@@....((  %,.,*//(&   %/..,,..,/*,..,,,,,,.&
/.*,,,,,. ...........*   %.,,,....*/. /(.., #..../( .#,.,,,,*,/&   # .......... ,,,,,*,.&
/.**..,,,............,#  %,,,,,,,,,.*(  %/..*,.*&  #..,,.,,,,,/&  %/............,....,*.%
&(.,,,,,,,.,,.........*  %,*,,,,...,,.,(  %/.,&  (.,,,,,**,,,,/&  ( ...................(%
  @%.,,,,.,..,,.,,..,.*% %,,,,,,,,,...,.,(    .(.,,,..,,,,,,,,/& &*..................#&  
    @#.................* &..,,,,,..........# #................*&.(    .............#&    
     ,%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%%%*.%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%.     
     %**************************************/ .***********************************/*     
   (*.,,,,,,,,,,,,,,,,,,..,,,.,,.,,,,,,,,,,./( (,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,***,/.   
 ./..........................................#  %*...............................,,,.*#  
..............................................   ....................................... 
     %***************************************# %**********************************//     
   (,.**,*///**,,,,,***,,,,,**,,,,,,,,,.,**%# #%,,,,,,,,,,,,,,,,,*****,,,,*,,,,,,,,*(.   
 ,*.,,*,,,,,,,,,,,,,.,,,,,,,,,,,,,,,,,,,,&&   &.,,,....,,,,,,,,,,,**,,,,,,,,,,,,,,,,,(#  )";
			cout << "\n\n";
			system("pause");
		}
		else if (playerTwoWins > playerOneWins)
		{
			cout << "Player Two has won at Gwent against Player One!\n\n";
			cout << R"(                                           & @.                                          
                                         %,#,(,%.                                        
                                       %*,,%#./.#%.                                      
                                     %*,((/(% #./,#%.                                    
                                  *%/*((((/.%.%,(//,#(*                                  
                                 %*.(/(//((*%(/,///*/,#%.                                
                               %*,///(((///(*%.*,///(((,%%.                              
                             %*,((((/////((/,# #./(/////(,%%.                            
/*                         %/,/(((((/////(///%*%./////*////.%%*                        *(
//#.                     &,.(#((((((//(//(/((/%*,*////*/////(.#&                     .(*&
/,.%#.                   %*/((((/////(//////*,# ,.//(///////((/@                   .(//*&
(,((.##                  %*///*/(//////////&@%#,#./*//(///((/(*@                 .(/*(#,&
(,(#((.##*               %*/(/////****///&%   %##./////((((/(//@               *///#(((,&
(,(((((/.##              %*///******//,  %(   ,.,/////((//*//@             .(*/((((((*&
/.#(((((#(.##            %******,***.%#  %, (     &%**/***/**//@           .(*/////////,&
/,##((#((///.(#          %*/*******%#  %,...(   ,%  &&.********@         .(*//(/((//(*/,&
/./#(/(//(////.(#,       %******,%(  %,...,&&   # ,&  (&,,*****@       *(,((///*/**////,&
/.//**/**//(((#(./(,     %**,*,#(  %,...,%/%&   #...*#. (&*,,**@     */.*/(///****/****,&
/./*,,***,/*/((/**.(%    %**.%#  %, ...%(,/%&  .@&*...*&  %&,**@   .(,/(///*/**,****///.&
/.*/*/**/*/**///,,#&.    %,#(  %,....%(,.*/%@  %(@,...,&  %&(&    .@*//**/**,,,,,,,*,.&
/.**/,**/**,*//,.%(      &(  %,.,.*%/...,//%@  @&%**(%*.,.,&  *%      ((**,*,,***,,,***.%
/.,,***/*,,*/,,,.%(      %  /#.,..@@///*/%@ .@%%%&&@@..../(  %      ((,(//*,,,,*,,,,*.&
/ ,,,***,,,,,,,*.%(      %*%  %(....@@&(/**%@ #&%%&@@,.../&  #.@      ((,//,,,*,,.*,,,*.&
/.,,,,,**,,,,,,,,%(      %..*%  %/....@@%(%@( @%&@@....*&  #, /&      (/,,**//***,,*,,,.%
/.,,,,,,,,,......%&%%    %..,.*%  %/....&@@( @&@@....*&  %..**/&    %%&(,******,,,,,,,,.%
/.,,,..,.,,.,. .....*(   %.,,...*#  /(....& &@@....((  %,.,*//(&   %/..,,..,/*,..,,,,,,.&
/.*,,,,,. ...........*   %.,,,....*/. /(.., #..../( .#,.,,,,*,/&   # .......... ,,,,,*,.&
/.**..,,,............,#  %,,,,,,,,,.*(  %/..*,.*&  #..,,.,,,,,/&  %/............,....,*.%
&(.,,,,,,,.,,.........*  %,*,,,,...,,.,(  %/.,&  (.,,,,,**,,,,/&  ( ...................(%
  @%.,,,,.,..,,.,,..,.*% %,,,,,,,,,...,.,(    .(.,,,..,,,,,,,,/& &*..................#&  
    @#.................* &..,,,,,..........# #................*&.(    .............#&    
     ,%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%%%*.%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%.     
     %**************************************/ .***********************************/*     
   (*.,,,,,,,,,,,,,,,,,,..,,,.,,.,,,,,,,,,,./( (,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,***,/.   
 ./..........................................#  %*...............................,,,.*#  
..............................................   ....................................... 
     %***************************************# %**********************************//     
   (,.**,*///**,,,,,***,,,,,**,,,,,,,,,.,**%# #%,,,,,,,,,,,,,,,,,*****,,,,*,,,,,,,,*(.   
 ,*.,,*,,,,,,,,,,,,,.,,,,,,,,,,,,,,,,,,,,&&   &.,,,....,,,,,,,,,,,**,,,,,,,,,,,,,,,,,(#  )";
			cout << "\n\n";
			system("pause");
		}
		else
		{
			cout << "Player One and Player Two have tied at Gwent!\n\n";
			system("pause");
		}
		system("cls");
		bool playAgain = false;
		while (!playAgain)
		{
			string againChoice;
			try
			{
				cout << "Would you like to play Gwent again? ('Y' for yes and 'N' for no): ";
				getline(cin,againChoice);
				if (againChoice == "Y" || againChoice == "y")
				{
					playAgain = true;
					pNorthernField->ClearAll(); //reset all northern
					pNorthernField->ResetPower();
					pNorthDeck->ResetDeck();
					pElfField->ClearAll(); //reset all elf
					pElfField->ResetPower();
					pElfDeck->ResetDeck();
					pMonsterField->ClearAll(); //reset all monster
					pMonsterField->ResetPower();
					pMonsterDeck->ResetDeck();
					system("pause");
					system("cls");
				}
				else if (againChoice == "N" || againChoice == "n")
				{
					playAgain = true;
					mainGame = false;
				}
				else
				{
					throw "You can only enter 'Y' or 'N'. Choose again.";
				}
			}
			catch (const char * msg)
			{
				cout << "\n\n" << msg << "\n\n";
			}
		}
	}while (mainGame);
	system("cls");
	cout << "Thank you for playing my C++ II Gwent Final! :)\n\n";
	system("pause");
	return 0;
}
bool PlayerPass()
{
	string yNAnswer;
	bool yNValid = false;
	while (!yNValid)
	{
		cout << "\nAre you sure you want to pass this round? (Enter 'y' or 'n' for yes or no): ";
		getline(cin,yNAnswer);
		if (yNAnswer == "y")
		{
			cout << "\nYou have passed this round. You will not be able to play again until the next round.\n\n";
			yNValid = true;
			system("pause");
			system("cls");
			return true;
		}
		else if (yNAnswer == "n")
		{
			cout << "\nYour turn won't be passed.\n\n";
			yNValid = true;
			system("pause");
			system("cls");
			return false;
		}
		else
		{
			cout << "\nYou can only choose 'y' or 'n', choose again.\n";
		}
	}
}

string CoinFlip()
{
	int flip = rand() % 2 + 1;
	if (flip == 1)
	{
		cout << "\n";
		cout << R"(                                    .,,,....,...,,,.    .                                
                             .*,*(((/*,.......,.,,,*/(((,,. ..                           
                      .../(#(, .,,.......... ......*.(/...,*(/*, ..                      
                   .,.%%#,....*, ,. .......*,.....,,,*,#....,. *#(..,.                   
                 ,.(&%. .......,,. .(..../((/((...,./,,,.....*/.. *#* ,,                 
               ,./@/../*......../(#*...    .,.      ..,(.....,.(*/(,.((.,,               
            .,.,....../. ........  .,./,*... ., ...*.. ..././......, .#..*             
           *.%@....... ..(,......, ...  ,,.* .,,,,,,..,.   ..........,,/.*#.,,           
         *.#@,./,. . .(,.......,        ....,#*.,*,, .,  /**..........,,.,.*/.*.         
        * %(... .,/.*/...  .  *      .... .../,,. .,,..  ...,....../,/......,#.*/        
       *.%/......  , .    .  *.   .,,,.   . ,,*,,**,. .,. .,,.,...............#.,/       
      *,@, .     . ...  .  .*    .,,....,.,.* ....,..*.,,**,,**................(*,/      
     /.@.    . . .        ...   ..,...,,.,.,/***.,(***.,,.     ,.. ............./.*(     
    /.#*                   .&%@*......,/,,*/ ,/**//*#.//((*** ..,   .............( ,,    
   .,,&   . .         .    *  *##*.      ../*//,*((*/**,(##,#.,,/      ..........,,.(    
   *.&,                  ...,,,. .      ,,*,,,,,*..,. . .,,,*/#/,          ..... ./.*/   
  ,,(&        .         ..    ..     ...,. .   ..*,..,,.. .   .*        .      . .,*,#.  
  ,.&(                  *       .....,.,,,,.*/,...,*,**. ,.,.. .*., .              *.(/  
  ..#.                .,     *  ...,,....,**..,/((%#**,.(...*.. ....               ,.(#  
 ..,/.                .%@,(*. . ......,,*,,    %(/#&%(*,/,..,.. *                ../%  
 ..*,                    ..   ,...      .*//(/&%* .. ..//%###/,,***                ../&  
 . *,                    .,//,             .,/.    .(*,*     .,*.     .            ..(%  
 ...*             ..     .,,.,,...      ..*((,    ..   **,....,....                ..(%  
  ../.               . .  ,. .........,*///,............/(/,,.(... ..              *,%#  
  *,/*             . . .../#%@%####(/*,.... . ........   ./*. *.......          . ,,*&,  
  .*./              .........,/%%(//*,,..      ...... ....,**,**..    .         . *.#(   
   *../              .. ..... . ...*/          .....   ....*/*//.,,   ,..        ..,@.   
    *,,.  .,. .,,/*.**.,*.,. *.,....,.      ....         ...(,**,,#, .*.*,*      **%/    
    .(,*  ./,*/,******,,,..(#.**,...,,      ....    ...      ,(%,.,.. * ,.      *,&&     
      (,*, . ..,*,,*..,,/.,,*......../,,.  .,.........         *  , ,,/.       ,,%#      
      .(*,,  ..*,,//*(*(/*/*/........./,..,*,,,,.,..            .  ..(.       ,/&%       
       .((.*   . ....................,.,,//*,....  ......       .,,,**      ,,/@%        
         *#,,, ..  . ................,..,,.        .........*%@@,.*/, .    ,*&&.         
          .%#.*. .      ............                ....*(@@@*.....      ,.#@%           
            *%(./.         .......,.    ..........,*#@@@##,......      ../@&.            
              .%#,,,  .     . ..  ,.,(%%@@@@@&%##(*,.,......... .    .,(@%,              
                ,#%,.*.    .. .. ,..., , ,...,   .., /, . .....   ..,&&%.                
                   ##%,.*.   .. ...... . ,... .  /.., /..,.     .,(&%/                   
                      ,(/(*..,.       ../......./.....,/.   .*(#%#,                      
                         .*(//(,. .,.                . .,*(/(#(                          
                              ,(,***,//*,,,,,,,,*(/**/,(#/.                            )";
		cout << "\n";
		return "heads";
	}
	else
	{
		cout << "\n";
	cout << R"(                                     ..,....,,,,...                                      
                              .,..    ..........,,...  .,,                               
                         .,.  .,/(//*,..,...*.....,,/**,... .,.                          
                     .,. ./#/..../,,,*....,,../....../*,,. ,/*,. .,                      
                  .*. ,(#...(...,.........,..,.,.,.*.,..*.*,/*.*/,. ,,                   
                ** ./#..,,.*...,//,,,(,........,....(**/.,((,..  ,*/*..*                 
              ,* .&*..*,....,,,(...****,.,,,*,,,,,**.,..,/... ./,*.. /*..*.              
            /..*#.   ....,(...*,...,,./*/,//,*./(**/*.//.....*.,*. .. ..(../             
          ,* ,%.*,.,*,..,.    .**(...,*.,. .,,,*.. ,..,(,   .  ./*/*. .,**(.,/           
        .( ,%.,*  *..(   .. ..*......./*(,,..*/*(,/,....,*..,, .  ...*, ,/,,/.*.         
       ,/ */./*./../. ...*,*,./.......        ,*.........,.,.,,*.   .*./*,..,#.*/        
      .( */./..,,*,  ..,,,,,*..,......%##&%#/*,#........,...,,,*.,....*,.  .,.(..(       
     ,( #,,**.  .  ,.**/,,.,... ,........*,,.,*//.......  .,.,.****//,..(/,.*/./*.(      
    ,# (..  ...* .** .. .,,,...,  ...... * . ...,,...   .,**,*,/  *  *  ..,*   .*,*(     
    /,,/. .*,,/  ,*  * ., ., , ,.*.       . ...       ,..,,, .,..* *. *  ., .,(. /.*,    
   /. %..,..**  ., ./ ,, ,,..., ,,.*/,.. . ....,....,*.,,.*. **,, , .  *  .,  ....,.#    
  *#.,,. ., .. .*..* ,, ,,,,.,, ,,,.,,****,,*.*.,,*/(/*, .*./,,.,,., .. , ...*  ,*,,*/   
  (*.#..  .(,  ,. / .,.,,  .. (, .,.,..,,,,...,.,***/** .*.*,   ,., . ., . ,,/    .,.%.  
 ./.*#   ..*. .* , .,,,.,,  ,. ,*.* .*,*,,,,.,.,,,,,, , *,**  .,  *,,.  ,.,,,.     ,.#/  
 **.#,/*,,(.,,*./.,.    ,**  ,,,.,.*.. ..  ..,.,.  .,.,./. ,. ..*, .  ,,*****. *#. ..(#  
 /,.#.     ,.**, ,  .    .//.,/ *..*, ,*,..,*,,,,..,/,,*, ,, .,*,. .  ...  .**,    ..(%  
 (,.#      ,.  , ,  .  . *.(,  , / .*,,*,.**//**,,.,/(... ,, ,(,.,  .  , ...,       ./&  
 (*.#.     ,.  , .  .  ,..(  /.*. ,  .,**,**(*,**,,*(,,.. *,/*.... .........*.  .  ..#%  
 */,(,     ,,  . .  . ...**    *// .,,./,,,//,**/*,,%,.,  ##.  ,.....  .....*    . ..#%  
 ,(,*(     ,,...    . . ,#..    ..(**..*///////**/%/(*.,(/.. .. ,....,....../  ..  ,,%#  
  %*.#      /. . * ,. .,*....     .   .*(.((,..,,*/%(*...........,, , //...,* .....**&,  
  (%*.,   . ,...  * ., **..           ,* */..*, ,,./.     ..,.......#*.....*. ... *,##   
  .%(,(   . .,... .,(,,*. . ..  ,,.,,,,,*,,.,*.(,,/../.. ...,,.**.*(. ,....*......**&.   
   .%/./ .  .,... ,  .(....,,//(//((////(*((*#(**(****//##////* ,.*(/*/*.,./ ..../*%(    
    /%/*, ...*,*,(#,,**,. *    ..,*...... .. ,... .. */... .,...,*../*..*,.(....*,%&     
     ,%(*/ ..*.(/.     . (( / .   /....  ,,/(*/#((,.......,.*  (..   ..........*,%%      
      /&(./ ....        ...,*.(..(... . ,,,..   ../.  ,...(*.#///,.,/,.,....../(&&       
       /%#,(  .  .,.,*,..,((#*(/.. ,, ** ,,....*.*..,.*././#...,..*.,*..,//#,*#@&        
        .%#(,,..* ..*..*,,/,  .,*,.**/,,,   ../. .,,*/*//*. ,*.....,.  ,.*,*(%@,         
          (%%*,,/../ ./.. .../***../ *..,///(, . ./,..*,.*.,......*.(((,,%&&           
           ,#**.#...  *.  ...///.   (#........//  ....../(..,*.....,/.*&&&,            
             .##%#..*,(. *,....   ,((*.............*(..  ..*,...*..(,,/&%&*              
                %&(%*,.(.*,....*(//.. .    .  ...,... .*.,,,*...(,.,#&&@,                
                  *&/#%*..,*(.,*...(..../,(./,.,..,**.*....*.(,.,#@%%#                   
                     ,%&/#%/, .*.,,...,.,,. //.... ..#,.., .*%&&/                      
                        .(%%,(&(/,.,. .,*/*((,./,... ..(#%&%#&%,                         
                             *#%#&,/(%%%(#(///(((%%%///&&%/.                             
                                     .,*/(###(#//,.                                      )";
		cout << "\n";
		return "tails";
	}
}

void HelpScreen()
{
	cout << "\nHelp: Action list\n\n";
	cout << "'player': Displays hand then prompts player for choice of card to play.\n'melee': Shows the player's melee row.\n'ranged': Shows the player's ranged row\n'siege': Shows the player's siege row\n'weather': Shows the player's active weather cards\n'discard': Shows the player's discard pile\n";
	cout << "'hand': Shows the player's hand.\n'ability': Shows the player's ability and, if playing with the Monster deck, activates the ability.\n'pass': Pass on the round for that player, cannot play again till next round starts.\n\nRemember when typing in the name of your card to play, spell it out exactly as shown.\n\n";
}

void StartScreen()
{
	cout << R"(                                                                                                                                                                                   
                                                                                       *///,                                                                                       
                                                                                     ,/((*//(,                                                                                     
                                                                         ,.        */((//(////(*        .,                                                                         
                                                                         /(/      *((///((**//((/      //*                                                                         
                                                                         /((/.    *////((***/(((/    ./((*                                                                         
                                                                         /(((//*  ***//,*,.*//*// .*/////*                                                                         
                                                                         */**/(*/ */*,,((*/(,*/(/,(//***//                                                                         
                                                                         *****,*, ****%//*#%%*/*, //**,,**                                                                         
             ,**************************///*****                         *,,,,,** ,,*/,/##%/**,*/.///*,,*/                         .***,,,*,,,,,,,,,,,,,,,,,,,,**************.     
           .//(%#((#######(#####(##(##(##%%(/#/                          **,,,..,***,,*/*,*/,,,*//.....,*/                          .(//(#((((#(#(((((((((#########%&%%%%#%#/.     
         ,/#(**(#////*****************(%%#(#*                            .//,,,,,*/***,****,,**/(*,,,,,/,                             ,(((###/*///////////////////////////#&(.     
       ./%#**///////////////////////%%%%(%/.                              .*,,,,,,,,*,,,*,*,,,,,,,,,,,,.                                ,#(#%%%/////////////////////((/(((%&(.     
     ./##,*/*%&&&&&&&&&&&&&&&&//#&%%(#*                                .,,*************,,************,,                                 .#((%&&&&&&&&&(////%&&&&&&&%/(((%&(.     
     .((/////&%#######%######*%@&%(%#,                                  *//(/*********/*/******/*****(*                                   ,#(###%%%#%%//((/%&%#%#(/(((&&(.     
     ./((////&%%(%*          *#%&%#%,     ,***********    ,**********,   .***********     ***********************.,**********.         .**********/,%/(#//(((%%/*#/#((((((&&(.     
     ./((((//&&%(#*          /%%(%(       ,(########(%,   //(####%##(/   ./#(####(((/.  ,(#%#%####%%&%%####%%%#(/.((#%##%##((.         (/(((((###((,%/(#//(((%%/*#/##(((%&%#,      
     ./(((((/&*#*          /#%,         ,((/,,,*#%#%,   /((/,,,*%%*/   .*(/,,,,(%(*,,//(,,,,,,,,,,,,,,,,,,,*#&(.((#/*,,*#&(.         (//(/***,#%(,%(##(((((%%/*#*##(%&.        
     ./(((((/&*#,          .,           ,((////(%%#%,   /(((///(%%//   ./(/////#%(*,*(/,//////////(((/((((((&%/.(/#/((((%@#*,        (//((/(((%%/.%/(#(((((%%/*#*##%%(*          
     ./(((((/&*#,          .*(#((((((((#*((//(/(%%,   *(((((/(%#*/   .*//////#&(*,*#(////(%%%%%%%%%%%%%%%#&%/.//#//((((%//*.     (/(((((((%%/,%*(#((##(%%/*#*##(.            
     ./(#(((/@*#,        .*(#*,,,*,*(%(#*((((((#&&(%,   *(((((((,/   .*/(///(%&/*,*((//(/#(#(#####((##((#(/,//#((((((((&@#/**    (//(#(((#/,#*/##(##(%%/*#/(*              
     ./(((((/@*#,       ,/#(,/(((((%&%/#*((((((#&&(%,   */(#(((#&(,/   .,/(((((%&/*,,((/(((%&(*. .       ..     //#((((((((((%@%/**. (//(#((#(%%/.#*/%#(###%%/*#*                
     ./((((((@@#/#,     */#/*/(((((((%&%/#*((((((#@@(%,   ,/##(((#@(,/   .,/#((((&&/,,*(#((((%(##((##(((((#(/   /*##(###%%######&%/**(//##(###&%/.#//######%%/,                  
     .(((((((@&(*#,   *((##&@@@&%((((%&%/#*((#(((#@@/%,   */###((#@(,/   .*/#((((&@/*,,(#((#((/////////////(/   /*##(###%@@%#####%@%/*//######%%/,#*/%##%%#&%/,                  
     .(#%((((@@(,#, .**********#%((##%&%/#*((#(##%@@/#,   /(###((#@(,/   ,**#(#(#&&/***(###################%/   /,######%&/%@&%#####@&/,(#####&%*.#*/%##%%%&%/,                  
     ./(#((((@@#*(,           ,(%(###&&%/#,*##(###&@///   */####(#@%,/.  .*/#####&&(/*(######%&&&&&&&&&&&&&&&/*   /,###%%#%&/*/%@@%##%%%@&%%##%#&%*,#*/%##%%%&%/,                  
     ./(%##((@@(,(,           ,(%####&&%*(.**%%###%@&*/(/.*/#%####%@(*/*..**%####&&/***(%%%##%&////////////////   /,%%#%%%&&(,,///&@%%%%%%&%%%%%&%*,(,*%%%%%%&%/,                  
     .*(####(@@%*(*           ,(%####&&%*#..*####%@&(,*/*/#%###%#&@%/,*/*/%%%%#%&***//%##%%%@(*/                /*##%%%%&&/.  ./*(@@%%%%%%%%%%&%*,(**#%%%%%&%/,                  
      ,/#####&@&(*#(          ,(%##%#&@%/(. **(&%%%%#%&%##*/#%%%%%%%%%&%#(*/%%%%%%&(/.,*#&%%%%&@%*,****           /*%#%%%%&&/.    ,(*(@&%%%%%%%%&%*,#*/%%%%%&@#/,                  
      .*#%###%&@@(**((,       ,(%#%%%&@%/(.  ./(&&%%%%%##%##%%%%%%%%%%%%%%%%%%%%#%%/*. */&&%%%%%&&%(//*,*//*,.    /*%%%&%%&&(.      ///%@%%%%%%%&%*,#*/%%%&&%&%/,                  
       .*%%##%##%&%#/***/((.  ,(%#%%%&@%*(.    .*/#@&%%%%%%%%%%%%%&@&%%%%%%%%%%%#%%/*.  ,*#&%#%%%%%%%##(((/(/**,*,/,&%%%&%@&(.       .(*(&&%%%&%@%*,(,*#%%&&%&%/,                  
        .(%&%%%%%%%####(/**/((/(%#%%%&@%*(.      .**(&@&&%%%%%%%%%@%#&@&%%%%%%%%%%&/*.   ,*(&@&%%%%%%%%%%%%##(((*,*,&%%%&%@&/.        */,%&%%&&%@%*,(**%%%&&%*,                  
         ./(%&%%%%%%%%#####(*,*(%%%%%&@%*(.         .*/*/&@&&%%%%%@(,///#&&&%%%%%&&/*.     .*//%&&&%%%%%%%%%%%,,*,&%%&&&@&/.         /,/%%%&&%@%*,(*/%%%&&&*,                  
            ,/#@@&%%%%%%%%%####%%%%%%&@%*/.              .***#@@&%@(,*  .,**#&@@%&@/*.         .,**/(%&@&&%%&&&(,,*,&%#%%&@&/.         /,,#%%&&%@%*,/,/%%%&&&*,                  
              ./*(&@&%%%%&&&&%%#%%%&%&@#,/.                  ,*,(%@(.*      .***#&&/,.              .,*,,*(%&@&(,,*,#%%%%#%#*,         /,,(######/,,/,*%%%&&&*,                  
                  .,**/&@@&&&&&&&&&&&&@#,/.                       .*,*           .,**.                      ..,//,                                  /,*%%%&&&*,                  
                       ,**(&@@&&&&&%%&@#,*.                                                                                                         /,*%%%&&&*,                  
                           .*,*%@@&&&@@#,*.                                                                                                         *,*%&&&%%#*,,                  
                               .,*/%&@@#,*.                                                                                                         *,,***,,*,,*,                  
                                   ..,**,*.                                                                                                                                        
                                        ..                                                                                                                                         
                                                                                                                                                                                   
                                                                                                                                                                                 )";
	cout << "\n\nWelcome to Gwent!\n\nA C++ II Final by Aaron Barnhart\n\n";
	cout << "Gwent is a card game with a max of three rounds. The first player to win two rounds is the winner!\n\n";
	cout << "Basic rules:\n1. You start with a ten card hand (unless playing as the Scoia'tael in which you get eleven).\n2. You can only play one card per turn.\n3. Each card can be played in either the melee row, ranged row, siege row, or weather row.\n";
	cout << "4. No cards are draw after the initial draw so use your cards wisely (unless playing as the Northern Realms in which you draw one card on round win).\n5. You can pass out of a round at anytime. This means you will not be able to play until the next round.\n6. Once both players pass the round is over.\n";
	cout << "7. To determine the winner of the round the total attack value will be determined for each player by adding up the attack values of all cards in all rows.\n\nCare for a round of Gwent?\n\n";
	system("pause");
	system("cls");
}

void PrintCrown(int wins)
{
	if (wins == 1)
	{
		cout << R"(                                                             .#      
                                                           .%,#      
                                                         .#*.(#.     
                                                       .%*,,/,%(     
                                                     .%**,/(/.##     
                                                   .%*,*((((/**#     
                                                 .%***((((((//.%*    
                                                #**./(((/((//(,%#    
                                             .%*,,(((((//*/////(#    
                                           .#*,./((/((((//////(,#.   
                                         .%**,/(/((/(////((((//,%/   
,                                      .#**,//(((((////(///////*##   
%,*                                  .%/*,(//(((((((///////(///(*#*  
%,#/*                               (*,,(##(((((((((///(//((//((,%#  
&/ .#(*                             (/.(((((((((///////////(//((*%#  
&(*(,*#(*                           (/./(//////////////////(/*,(,(#. 
&(*(((,.%(*                         (/.////*/////////*/(*////&%@#(#/ 
&(*((###,*%(*                       (/.////////////*/****/,&%#.  (## 
&(*((/(#((.*##*                     (/./(((////*/**/////,%%#.  .   % 
&(*((((##(((**#(*                   //.**///****,****/*%##.  #//     
&/*(((((((#/#(*,%(*                 //.********,*,**.%##.  */, (     
&/*(((((###(#(((*,#(*               //.***,**,,,*,*%##   #/..,.(     
&(*#((((/(/(((((//*,(#*             //.*********.%#(   */, ....#     
&/,/##((/(///((//*//*,((*           */.*******,##*   #*,.....%&&.    
&/,((/////**//((/((///*,#(*         */.**,**.##(   */,.....(%#&&.    
&/,/(/*,***,,**(///(#(//*.((*       */.***,%(*   #*,.....%%(*(%&.    
&/,/**,,,/***,*/*/(##//****,##*     **.,.((*   */,.....(%(*,*(%&.    
%*.,*/*********/***/(/*,,,(%%.      **.#(,   #*,.....##(*,.,/(%@     
%*.***//,*//*,,,,***//**/%&.        ,,(.   #/,.,...(#/,,...//(%@     
%*.**,*,***//***,*****,,(&/         ,*   */,.,,..(%#*.....*//(%@     
%*.,,,*,,*//**,****,,,*,(&*         ,   ,%/.,,../@@@%#////**/(%@     
&,.,,,*,,*/****,,**,,,,,(%,         #**   #(/.,...%@@&%(///**/#@     
%,.,,,,,,,,,,,,,,,,,,,,,(%*         (*,/(   *%/...../@@&%((**#&@     
%,.,,,,,,,*,*,,.,,,,,,,,(&/         (,. ,**   #%*.....%@@&%(#&@*     
&,.,,,,,,,,,,,,,,,..,..,/%(         (, ,..,*(   *#*...../@@&&@%      
&*.,,.,,,,,,,,.,,...,,,.,*,,,,,     /, ..,,.,**   #%*...../&@%       
&*.,,,,..,,,,,,,...  ...,....*(     /,.,,,.,..,/#   *#*.....(        
&*.*,,,,,,,,,,. ..............,,    /, ,,........*#   ##*.....       
%,,****,,...,......,..........,(    **.,,,,,,.....,/(   *#/../       
%*,*,.,,,,,,,,,................,,   **.,,,,,,,,,,,,.,*(.  *#*/       
#%/.,,,,,,,,,,,.,,...,.........,(.  */.*,,,,*,....,,...*/.  *%*      
 .&&(,,,,,,,,,,,,..,..,,........*(  **.,,..,,,,,,,...,...//.         
   .&%*.,,,,.,,,.,.,,.,,...,.,..*(  **.,,,,,,,,,,,.,.,,,,..*/        
     .&%(........................,# ,* .,,.,,,,,..............(      
       .&%%%%%%&%%%%%%%&%%&%%%%%&&%.,%&&&&&&&&&&&&&&&&&&&&&&&&%,     
                                                                     
       */,,,...................................................*.    
     */*.,,,,,,,,,,,,,,,,,,,,,,,,,..,,,,,,,,,,.,,,,,,,,,,..,,,./#    
    #*.,,,,,,,,,,,,,,,,,,,,,,,,,,,..,,,,,.,,,,...,,,,,.,,,,.,,,,#    
  #**///////////////*////////*////////*///////**////////////*///,*   
 ,,,,*********/////////(((((((((##((((((((((/////////*********,,,,   
        .,,,,,,,,********///////((((((((((((//////********,,,,,,,,   
      *%,.................................................... ,(%    
     #,.,***,*/////**,,*,,,,,****,,,,,,,,**,,,,,,,,,,,,,.,,*.%%/     
   **.,/*/*/**/****,***,,,,,,*,,,*,,,,,,,**,,*,,***,,,,,,*,#&(       
 ,/,#&&&&&&&&&&%&%%%%%%%&%#%%%%%%%%%%%%%%&&%%%%%%%%%%%%%#((&*      )";
	}
	else
	{
		cout << R"(    (/                                                               
    ,##.                                                             
     #.#(*                                                           
     // .##*                                                         
     .(.*,/##.                                                       
      #,,((*,#(*                                                     
      #*.(///,,##*                                                   
      (*./*////,/##.                                                 
      .*,*//////(/*#(*                                               
       (,,/////((/(,*%#*                                             
       #*./(/(((/(///,(%#.                                           
       //./////(/////((*,%(*                                         
       ,#.*//////////////.,%#*                                    .(&
        #,,///((/*///(*//((,(%#                                  (/*@
        /,.*/(/((////////((((.@*                              .(*,,#@
        .*.*///(//(/////(((((,@*                            .(/,,(*#@
         (.,*//*//////(((((#(,@*                           (//,((#,#@
         #..////*//////(((#((,@/                        .(/,/((((#*#@
         /..**/*//((((((/((/(,@(                      .(/,*(##((((,#@
         .,.**///(//((//////(,@(                     (/*,((#((((((,#@
          *&%,**////////(////,@#                   (***(##(/(/((((,#@
            .&&,********/////,@#                .(*.*////((//*////,#@
          #.  .&&*******/***/.               (/,*//((/(((//((//(,#@
         *.,#   *&&,,*******/.@#             (/,*((/*///**///(///(,#@
         ( ..*#.  .&&/,,,****.&(          .(*.*(((/*/*///*/*/*///*,#@
         #.....*#.  .&&(,,*,*.&(         (*,,//(/(//*//***//****//,#@
        .@%,....,*#   *&&*,,*.&/       (*,*//////*///***,*****/(((.#@
        #@#%@*.....*#.   &,.&/     ,%/,/(((/*//*/***,*,,**,,,**(.#@
       .&&%((&@,.....*#.   &%*       #@#,//***//***,,,,,,,,,,*,,.#@
       *@&%%*/(&%,....,*#   ,%#*         #%*,//**,*,,,***,,,,,,,,*.#@
       %@%%%/..,(&&,..,,.*#.   .         .#/,/(***,,,,,,*,,,,,,,**.(@
       @&%%%%%&&@@%....../&.   .          %(,((/(/*,,,,,,*,,,,,,,*.(@
      *@&%#%%&@@%,.....*&.   (,*          %(,*//,,,***,,,.,,,,,,**.(@
      %&%%&&@@%......(%.   (..%*          %(,,,*,,*,,****,,*,,,,,,.(&
     ,@&%&@@&.....,(&.  .(,..,%/         .%(.,***////**,****,,,,,,.(&
    /@&&@@&,....,/&.  .(. .,,.&/         ,#/*/**////*,*,,,,**,,,,,.(&
   ,@@@@@,.....*&/   (...,,**.&(      #...,/.*/**//*****,,,,,..,,,.(&
   &@@&.....,(&.  ./. ,,,,*//,     %( ,.,,.,,...//*,,..,,,,,,,,,.#@
   #&,.....*&.  *#. .,,,,,,,,.%#    /%*.................,.,..,,,,,.#@
   *,....*&/   #...,,,..,,,,,.%#    %( ..,............... .,,,*.,,.#&
   .*,./&.  **. ,,,,,,,....,,.%(   *#,.........................,**.#&
    /,%.  *(...,,,,,,**,,,,,,.%(  .%/.............................*/&
    &/  .(.....,,,,,,,,,,,,**.#/  ##,...........................,%&/ 
      *,..,.......,,,,,,,,,.,.&* .%/........................../&&.   
    .(..,,,.,,...,,,*,,*,,,,,.#* %(,........................(%&.     
     (#%%%%%%%%%%%&&&&&&&&%%&&(, %(###%%%%%%%%%&%%%%%#%#%%%.       
                                                                     
       (***************************************************(.        
       //..,,,,,,,,,,,,,,,,,,,..,,,.,,,,,,,,,,,,,,,,,,,,,,,,((       
        ,,..,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,***,,*,*,,****,./(.    
         (*,.............................................,,,,,.**(   
          ##%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&&&&&&&&&&&&&&&&&%%, 
                                                                     
       %(......,,,,.,,,,,,,,,,,.,,,,,,,,,,,,,,,,,,,,,,,,,,,/#        
      .%#.,,,,,,,,,,,,,,,,,,,,,,,,********,,,,,,,,**,,,,,,,,((*      
      %%,,,,,,,,,,,,,,,,,,,,,,,,,,**///**,,,,,,*,,,,,,,,,,,**,%#.    
     ,%*,,,,,,.....,,,*,,,,,,,,,,,,,,,,,***,,,,,,,,,,,,,,,,,,,,/(#   )";
	}
}