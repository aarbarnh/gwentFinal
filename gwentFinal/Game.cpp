#include "Card.h" //include all file headers
#include "Deck.h"
#include "Field.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <ctime> //for time()
#include <boost/algorithm/string.hpp> //for upper copy

using namespace std; //no std::

//function prototypes
void StartScreen(bool *ptrBool);
void ShowBasicRules();
void HelpScreen();
void PrintCrown(int wins);
bool PlayerPass();
string CoinFlip();


int main()
{
	system("color 0C"); //change background and text colors
	srand(time(0)); //seed rand
	string p1DeckChoice; //strings to hold input
	string p2DeckChoice;
	string flipChoice;
	string flipResult;
	string playerOneChoice;
	string playerTwoChoice;
	bool mainGame = true; //main game loop condition 
	bool p1Pass = false; //turn passing for p1 and p2
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

	StartScreen(&mainGame); //run start screen, pass main game bool
	while (mainGame) //loop for entire game
	{
		int playerOneWins = 0; //player wins 
		int playerTwoWins = 0;
		bool correctDeckChoice = false;
		while (!correctDeckChoice) //loop to decide deck
		{
			cout << "Player One, which deck would you like to choose? (Type 'elf' for Scoia'tael, 'northern' for Northern Realms, or 'monster' for Monsters)\nYour deck choice: "; //player1 chooses his/her own deck
			getline(cin,p1DeckChoice); //getline for choice 
			boost::algorithm::to_upper(p1DeckChoice); //boost to upper to make all tests against caps
			if (p1DeckChoice == "NORTHERN") //read from northDeck file and build deck
			{
				pNorthDeck->readCardFile("northDeck.txt");
				pNorthDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Northern Realms deck has been built and shuffled...\n\n";
			}
			else if (p1DeckChoice == "ELF") //read from elfDeck file and build deck
			{
				pElfDeck->readCardFile("elfDeck.txt");
				pElfDeck->ShuffleDeck();
				correctDeckChoice = true;
				cout << "\nYour Scoia'tael deck has been built and shuffled...\n\n";
			}
			else if (p1DeckChoice == "MONSTER") //read from monsterDeck file and build deck
			{
				pMonsterDeck->readCardFile("monsterDeck.txt");
				pMonsterDeck->ShuffleDeck();
				monsterPlayer->SetMonsterAbil(true);
				correctDeckChoice = true;
				cout << "\nYour Monsters deck has been built and shuffled...\n\n";
			}
			else //non valid choice
			{
				cout << "\nThe only three decks that you can choose from are Scoia'tael, Northern Realms, or Monsters.\nUse 'elf' for Scoia'tael, 'northern' for Northern Realms, and 'monster' for Monsters.\n\n";
			}
		}
		bool correctP2Choice = false;
		while (!correctP2Choice) //p2 deck choice 
		{
			cout << "Player Two, which deck would you like to use? You cannot pick the same deck as Player One.\nYour deck choice: "; //player2 chooses deck
			getline(cin,p2DeckChoice);
			boost::algorithm::to_upper(p2DeckChoice);
			if (p2DeckChoice == "NORTHERN")
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
			else if (p2DeckChoice == "ELF")
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
			else if (p2DeckChoice == "MONSTER")
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
		while (!correctCall) //coin call for coin flip 
		{
			cout << "A coin will be flipped to determine who goes and who goes second.\nPlayer One will call it. If right Player One will go first, if wrong Player Two will go first.\n\nWould you like to call heads or tails? (Type 'heads' or 'tails'): ";
			try //make sure player calls only heads or tails 
			{
				getline(cin,flipChoice);
				boost::algorithm::to_upper(flipChoice); //to upper choice to test against caps
				if (flipChoice == "HEADS" || flipChoice == "TAILS")
				{
					correctCall = true; //true if heads or tails
				}
				else
				{
					throw "There is only two sides to a coin, heads or tails. Choose again."; //throw string exception for anything else
				}
			}
			catch (const char * msg) //catch exception 
			{
				cout << "\n" << msg << "\n\n";
			}
		}
		flipResult = CoinFlip(); //run coinflip
		if (flipResult == flipChoice) //p1 goes first
		{
			cout << "\nPlayer One has called the flip, Player One goes first!\n\n";
			system("pause");
			system("CLS");
			cout << "Player One drawing cards..." << "\n\n";
			//player one drawing
			if (p1DeckChoice == "ELF") 
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
				pElfField->SortHand();
			}
			else if (p1DeckChoice == "NORTHERN")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
				pNorthernField->SortHand();
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
				pMonsterField->SortHand();
			}

			//player two drawing
			cout << "Player Two drawing cards..." << "\n\n";
			if (p2DeckChoice == "ELF")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
				pElfField->SortHand();
			}
			else if (p2DeckChoice == "NORTHERN")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
				pNorthernField->SortHand();
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
				pMonsterField->SortHand();
			}
			do //loop for game (turns, get actions)
			{
				if (p1DeckChoice == "NORTHERN") //turn dependent on p1 deck choice
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pNorthernField->GetHand().empty() && !p1Pass) //if hand is not empty, p1 hasn't played a card, and p1 has not passed 
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice); //turn action prompt
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //if p1 wants to play a card
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
								for (int i = 0; i < tempHand.size(); i++) //test if card is in hand to play 
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //if the card was scorch (not in activateabilities in field class, check here)
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "ELF") //find p2 deck to scorch
											{
												string tempName = pNorthernField->Scorch(pElfField->GetMelee(), pElfField->GetRanged(), pElfField->GetSiege()); //get target
												pElfField->Scorched(tempName); //send target
											}
											else
											{
												string tempName = pNorthernField->Scorch(pMonsterField->GetMelee(), pMonsterField->GetRanged(), pMonsterField->GetSiege());
												pMonsterField->Scorched(tempName);
											}
										}
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather played, apply to p2 as well
										{
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard); //send playCard to PlayCard in field.cpp to play
										rightCard = true; //exit loop
									}
								}
							}
							p1TurnChoice = true; //p1 has played a card
							system("pause");
							system("cls");
						}
						else if (playerOneChoice == "HAND") //show hand 
						{
							pNorthernField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pNorthernField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged 
						{
							pNorthernField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pNorthernField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather 
						{
							pNorthernField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nNorthern Realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "PASS") //pass
						{
							p1Pass = PlayerPass(); //run pass
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice 
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p1DeckChoice == "ELF") //if elf is p1 choice
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pElfField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //play option
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
									if (tempHand[i]->GetName() == playCard) //check cards in hand
									{
										cout << "\n" <<  playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //if scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "NORTHERN")
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather is chosen, apply to p2 as well
										{
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard); //pass card to PlayCard
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true; //p1 turn over
						}
						else if (playerOneChoice == "HAND") //show hand
						{
							pElfField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pElfField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged
						{
							pElfField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pElfField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pElfField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather
						{
							pElfField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nScoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "PASS") //pass
						{
							p1Pass = PlayerPass(); //run pass
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else //p1 choice is monster
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pMonsterField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //play choice
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
									if (tempHand[i]->GetName() == playCard) //check hand for card
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth") //if scorch or villentretenmerth (monster card with scorch effect)
										{
											cout << "Scorch was activated!\n\n";
											if (p2DeckChoice == "ELF")
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
										else if (tempHand[i]->GetName() == "Biting Frost") //any weather card played, apply to p2 as well
										{
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true; //p1 played card
						}
						else if (playerOneChoice == "HAND") //show hand
						{
							pMonsterField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pMonsterField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged
						{
							pMonsterField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pMonsterField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather
						{
							pMonsterField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nMonster ability: " << monsterPlayer->GetAbility() << "\n\n";
							string abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil()) //ask to activate monster ability
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									getline(cin,abilUse);
									if (abilUse == "Y" || abilUse == "y") //if yes activate
									{
										cout << "\n";
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == "N" || abilUse == "n")
									{
										cout << "\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerOneChoice == "PASS") //pass
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//turn dependent on p2 deck choice 
				if (p2DeckChoice == "NORTHERN") //p2 deck choice, northern
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pNorthernField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice
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
									if (tempHand[i]->GetName() == playCard) //check cards in hand
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check if scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "ELF")
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather played, apply to p1 as well
										{
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //p1 played card
						}
						else if (playerTwoChoice == "HAND") //show hand
						{
							pNorthernField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pNorthernField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged 
						{
							pNorthernField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pNorthernField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pNorthernField->ShowWeather();
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nNorthern Realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "HELP") //show ability
						{
							HelpScreen();
						}
						else //non valid choice 
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p2DeckChoice == "elf") //p2 elf deck choice
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pElfField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check cards in hand 
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check if scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "NORTHERN")
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather played apply to p1 as well
										{
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //end p2 turn
						}
						else if (playerTwoChoice == "HAND") //show hand
						{
							pElfField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pElfField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged
						{
							pElfField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pElfField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pElfField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pElfField->ShowWeather();
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nScoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice 
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else //p2 monster choice 
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pMonsterField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check cards in hand
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth") //check for scorch or Vill with scorch effect
										{
											cout << playCard << " was activated!\n\n";
											if (p1DeckChoice == "ELF")
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
										else if (tempHand[i]->GetName() == "Biting Frost") //any weather played, apply to p1 as well
										{
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //p2 turn end
						}
						else if (playerTwoChoice == "HAND") //show hand
						{
							pMonsterField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pMonsterField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged
						{
							pMonsterField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pMonsterField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pMonsterField->ShowWeather();
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nMonster ability: " << monsterPlayer->GetAbility() << "\n\n";
							string abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil()) //ask to activate monster ability
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									getline(cin,abilUse);
									if (abilUse == "Y" || abilUse == "y")
									{
										cout << "\n";
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == "N" || abilUse == "n")
									{
										cout << "\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice 
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
					if (p1DeckChoice == "ELF") //p1 add up elf
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p1RoundTotal = pElfField->GetTPow();
					}
					else if (p1DeckChoice == "NORTHERN") //p1 add up northern
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p1RoundTotal = pNorthernField->GetTPow();
					}
					else if (p1DeckChoice == "MONSTER") //p1 add up monster
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p1RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player One Total Attack Value: " << p1RoundTotal << "\n"; //show total
					//p2 add up
					if (p2DeckChoice == "ELF") //p2 add up elf
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p2RoundTotal = pElfField->GetTPow();
					}
					else if (p2DeckChoice == "NORTHERN") //p2 add up northern
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p2RoundTotal = pNorthernField->GetTPow();
					}
					else if (p2DeckChoice == "MONSTER") //p2 add up monster
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p2RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player Two Total Attack Value: " << p2RoundTotal << "\n\n"; //show total
					//compare attack values, give win
					if (p1RoundTotal > p2RoundTotal) //p1 win, run resets
					{
						playerOneWins++;
						cout << "Player One wins the round!\n\n";
						PrintCrown(playerOneWins);
						if (p1DeckChoice == "NORTHERN") //allow northern to draw one card because of win
						{
							if (playerOneWins < 2)
							{
								cout << "\n\nAs Northern Realms, Player One gets to draw one card for the round win.\n\n";
								pNorthernField->DrawCard(pNorthDeck->GetDeck());
								pNorthDeck->TakeFrom();
							}
							pNorthernField->Reset(); 
						}
						else if (p1DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p2DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
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
					else if (p1RoundTotal < p2RoundTotal) //p2 win, run resets
					{
						playerTwoWins++;
						cout << "Player Two wins the round!\n\n";
						PrintCrown(playerTwoWins);
						if (p2DeckChoice == "NORTHERN")
						{
							if (playerTwoWins < 2)
							{
								cout << "\n\nAs Northern Realms, Player Two gets to draw one card for the round win.\n\n";
								pNorthernField->DrawCard(pNorthDeck->GetDeck());
								pNorthDeck->TakeFrom();
							}
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p1DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "ELF")
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
					else //both won, tie, run resets
					{
						playerOneWins++;
						playerTwoWins++;
						cout << "The round was a tie! Both players get the round point.\n\n";
						if (p1DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						if (p2DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
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

			} while (playerOneWins < 2 && playerTwoWins < 2); //keep going till p1 or p2 have 2 wins
		}
		else //p2 goes first
		{
			cout << "\nPlayer Two has called the flip, Player Two goes first!\n\n";
			system("pause");
			system("cls");
			//player two drawing
			cout << "Player Two drawing cards..." << "\n\n";
			if (p2DeckChoice == "ELF")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
				pElfField->SortHand();
			}
			else if (p2DeckChoice == "NORTHERN")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
				pNorthernField->SortHand();
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
				pMonsterField->SortHand();
			}
			cout << "Player One drawing cards..." << "\n\n";
			//player one drawing
			if (p1DeckChoice == "ELF")
			{
				for (int i = 0; i < 11; i++)
				{
					pElfField->DrawCard(pElfDeck->GetDeck());
					pElfDeck->TakeFrom();
				}
				pElfField->SortHand();
			}
			else if (p1DeckChoice == "NORTHERN")
			{
				for (int i = 0; i < 10; i++)
				{
					pNorthernField->DrawCard(pNorthDeck->GetDeck());
					pNorthDeck->TakeFrom();
				}
				pNorthernField->SortHand();
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					pMonsterField->DrawCard(pMonsterDeck->GetDeck());
					pMonsterDeck->TakeFrom();
				}
				pMonsterField->SortHand();
			}

			do
			{
				if (p2DeckChoice == "NORTHERN") //turn dependent on p2 deck choice 
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pNorthernField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice 
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
									if (tempHand[i]->GetName() == playCard) //check cards in hand
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check for scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "ELF") //run scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather activated, affect p1 as well
										{
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //p2 end turn
						}
						else if (playerTwoChoice == "HAND") //show hand 
						{
							pNorthernField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pNorthernField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged
						{
							pNorthernField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pNorthernField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pNorthernField->ShowWeather();
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nNorthern Realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid option 
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p2DeckChoice == "ELF") //p2 deck choice, elf
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pElfField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check cards in hand 
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check for scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "NORTHERN") //activate scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather activated, affect p1 as well 
										{
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
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
											if (p1DeckChoice == "NORTHERN")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard); //pass card to play 
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //end p2 turn
						}
						else if (playerTwoChoice == "HAND") //show hand
						{
							pElfField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pElfField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged
						{
							pElfField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pElfField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pElfField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pElfField->ShowWeather();
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nScoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else //p2 monster choice
				{
					bool p2TurnChoice = false;
					while (!p2TurnChoice && !pMonsterField->GetHand().empty() && !p2Pass)
					{
						cout << "What would you like to do, Player Two? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerTwoChoice);
						boost::algorithm::to_upper(playerTwoChoice);
						if (playerTwoChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check cards in hand 
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth") //check for scorch or Villen (scorch effect)
										{
											cout << playCard << " was activated!\n\n";
											if (p1DeckChoice == "ELF") //run scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather, affect p1 as well
										{
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
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
											if (p1DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard); //pass card to Play
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p2TurnChoice = true; //end p2 turn
						}
						else if (playerTwoChoice == "HAND") //show hand 
						{
							pMonsterField->ShowHand();
						}
						else if (playerTwoChoice == "MELEE") //show melee
						{
							pMonsterField->ShowMelee();
						}
						else if (playerTwoChoice == "RANGED") //show ranged
						{
							pMonsterField->ShowRanged();
						}
						else if (playerTwoChoice == "SIEGE") //show siege
						{
							pMonsterField->ShowSiege();
						}
						else if (playerTwoChoice == "DISCARD") //show discard
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerTwoChoice == "WEATHER") //show weather
						{
							pMonsterField->ShowWeather();
						}
						else if (playerTwoChoice == "ABILITY") //show ability
						{
							cout << "\nMonster ability: " << monsterPlayer->GetAbility() << "\n\n";
							string abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil()) //ask to use ability
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									getline(cin,abilUse);
									if (abilUse == "Y" || abilUse == "y")
									{
										cout << "\n";
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == "N" || abilUse == "n")
									{
										cout << "\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerTwoChoice == "PASS") //run pass
						{
							p2Pass = PlayerPass();
							if (p2Pass)
							{
								p2TurnChoice = true;
							}
						}
						else if (playerTwoChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				//turn dependent on p1 deck choice
				if (p1DeckChoice == "NORTHERN")
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pNorthernField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //play choice
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
								for (int i = 0; i < tempHand.size(); i++) //check cards in hand 
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check for scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "ELF") //activate scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather, affect p2 as well 
										{
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pNorthernField->PlayCard(playCard); //pass card
										rightCard = true; //exit loop
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true; //end p1 turn
						}
						else if (playerOneChoice == "HAND") //show hand
						{
							pNorthernField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pNorthernField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged
						{
							pNorthernField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pNorthernField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pNorthernField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather
						{
							pNorthernField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nNorthern realms ability: " << northernPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "PASS") //run pass
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice 
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else if (p1DeckChoice == "ELF") //if p1 deck choice
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pElfField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check hand for card
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch") //check for scorch
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "NORTHERN") //activate scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather, affect p2 as well
										{
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
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
											if (p2DeckChoice == "NORTHERN")
											{
												pNorthernField->ClearWeather();
											}
											else
											{
												pMonsterField->ClearWeather();
											}
										}
										pElfField->PlayCard(playCard); //pass card to play
										rightCard = true; //exit loop 
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true; //end p1 turn
						}
						else if (playerOneChoice == "HAND") //show hand 
						{
							pElfField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pElfField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged
						{
							pElfField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pElfField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pElfField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather
						{
							pElfField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nScoia'tael ability: " << elfPlayer->GetAbility() << "\n\n";
						}
						else if (playerOneChoice == "PASS") //run pass
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice
						{
							cout << "\n\nYou did not enter a valid action. If you need a reminder, type 'help'. Choose again.\n\n";
						}
					}
				}
				else //p1 monster deck choice 
				{
					bool p1TurnChoice = false;
					while (!p1TurnChoice && !pMonsterField->GetHand().empty() && !p1Pass)
					{
						cout << "What would you like to do, Player One? (Type one word lowercase actions, 'help' if you need a list of the actions): ";
						getline(cin,playerOneChoice);
						boost::algorithm::to_upper(playerOneChoice);
						if (playerOneChoice == "PLAY") //play choice 
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
								for (int i = 0; i < tempHand.size(); i++) //check hand for cards
								{
									if (tempHand[i]->GetName() == playCard)
									{
										cout << "\n" << playCard << " was played!\n\n";
										if (tempHand[i]->GetName() == "Scorch" || tempHand[i]->GetName() == "Villentretenmerth") //check for scorch or Villen (scorch effect)
										{
											cout << playCard << " was activated!\n\n";
											if (p2DeckChoice == "ELF") //activate scorch/scorched
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
										else if (tempHand[i]->GetName() == "Biting Frost") //if any weather, affect p2 as well
										{
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
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
											if (p2DeckChoice == "ELF")
											{
												pElfField->ClearWeather();
											}
											else
											{
												pNorthernField->ClearWeather();
											}
										}
										pMonsterField->PlayCard(playCard); //pass card to play
										rightCard = true; //exit loop 
										system("pause");
										system("cls");
									}
								}
							}
							p1TurnChoice = true; //end p1 turn
						}
						else if (playerOneChoice == "HAND") //show hand
						{
							pMonsterField->ShowHand();
						}
						else if (playerOneChoice == "MELEE") //show melee
						{
							pMonsterField->ShowMelee();
						}
						else if (playerOneChoice == "RANGED") //show ranged
						{
							pMonsterField->ShowRanged();
						}
						else if (playerOneChoice == "SIEGE") //show siege
						{
							pMonsterField->ShowSiege();
						}
						else if (playerOneChoice == "DISCARD") //show discard
						{
							pMonsterField->ShowDiscard();
						}
						else if (playerOneChoice == "WEATHER") //show weather
						{
							pMonsterField->ShowWeather();
						}
						else if (playerOneChoice == "ABILITY") //show ability
						{
							cout << "\nMonster ability: " << monsterPlayer->GetAbility() << "\n\n";
							string abilUse;
							bool useValid = false;
							if (monsterPlayer->GetMonsterAbil()) //ask to activate ability
							{
								while (!useValid)
								{
									cout << "Would you like to use your ability now? ('Y' or 'N'): ";
									getline(cin,abilUse);
									if (abilUse == "Y" || abilUse == "y")
									{
										cout << "\n";
										pMonsterField->CommandersHorn();
										monsterPlayer->SetMonsterAbil(false);
										useValid = true;
									}
									else if (abilUse == "N" || abilUse == "n")
									{
										cout << "\nYour ability was not used.\n\n";
										useValid = true;
									}
									else
									{
										cout << "\nYou can only enter 'Y' or 'N'. Choose again.\n\n";
									}
								}
							}
						}
						else if (playerOneChoice == "PASS") //run pass
						{
							p1Pass = PlayerPass();
							if (p1Pass)
							{
								p1TurnChoice = true;
							}
						}
						else if (playerOneChoice == "HELP") //show help
						{
							HelpScreen();
						}
						else //non valid choice 
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
					if (p1DeckChoice == "ELF") //p1 add up if elf
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p1RoundTotal = pElfField->GetTPow();
					}
					else if (p1DeckChoice == "NORTHERN") //p1 add up if northern
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p1RoundTotal = pNorthernField->GetTPow();
					}
					else if (p1DeckChoice == "MONSTER") //p1 add up if monster
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p1RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player One Total Attack Value: " << p1RoundTotal << "\n"; //show total 
					//p2 add up
					if (p2DeckChoice == "ELF") //p2 add up if elf
					{
						pElfField->mPowAdd();
						pElfField->rPowAdd();
						pElfField->sPowAdd();
						pElfField->tPowAdd();
						p2RoundTotal = pElfField->GetTPow();
					}
					else if (p2DeckChoice == "NORTHERN") //p2 add up if northern
					{
						pNorthernField->mPowAdd();
						pNorthernField->rPowAdd();
						pNorthernField->sPowAdd();
						pNorthernField->tPowAdd();
						p2RoundTotal = pNorthernField->GetTPow();
					}
					else if (p2DeckChoice == "MONSTER") //p2 add up if monster 
					{
						pMonsterField->mPowAdd();
						pMonsterField->rPowAdd();
						pMonsterField->sPowAdd();
						pMonsterField->tPowAdd();
						p2RoundTotal = pMonsterField->GetTPow();
					}
					cout << "Player Two Total Attack Value: " << p2RoundTotal << "\n\n"; //show total 
					//compare attack values, give win
					if (p1RoundTotal > p2RoundTotal) //if p1 wins, resets
					{
						playerOneWins++;
						cout << "Player One wins the round!\n\n";
						PrintCrown(playerOneWins);
						if (p1DeckChoice == "NORTHERN")
						{
							if (playerOneWins < 2) //nothern ability, draw card if win
							{
								cout << "\n\nAs Northern Realms, Player One gets to draw one card for the round win.\n\n";
								pNorthernField->DrawCard(pNorthDeck->GetDeck());
								pNorthDeck->TakeFrom();
							}
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p2DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
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
					else if (p1RoundTotal < p2RoundTotal) //p2 wins, resets
					{
						playerTwoWins++;
						cout << "Player Two wins the round!\n\n";
						PrintCrown(playerTwoWins);
						if(p2DeckChoice == "NORTHERN")
						{
							if (playerTwoWins < 2) //northern ability, draw card if win
							{
								cout << "\n\nAs Northern Realms, Player Two gets to draw one card for the round win.\n\n";
								pNorthernField->DrawCard(pNorthDeck->GetDeck());
								pNorthDeck->TakeFrom();
							}
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}

						if (p1DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "ELF")
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
					else //if tie, resets 
					{
						playerOneWins++;
						playerTwoWins++;
						cout << "The round was a tie! Both players get the round point.\n\n";
						if (p1DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p1DeckChoice == "ELF")
						{
							pElfField->Reset();
						}
						else
						{
							pMonsterField->Reset();
						}
						if (p2DeckChoice == "NORTHERN")
						{
							pNorthernField->Reset();
						}
						else if (p2DeckChoice == "ELF")
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
					p1Pass = false; //reset passes
					p2Pass = false;
					system("pause");
					system("cls");
				}
			} while (playerOneWins < 2 && playerTwoWins < 2); //while neither player has 2 wins
		}
		//post game, ask to replay
		if (playerOneWins > playerTwoWins) //show full crown if p1 won
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
		else if (playerTwoWins > playerOneWins) //show full crown if p2 won
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
		else //say both tied
		{
			cout << "Player One and Player Two have tied at Gwent!\n\n";
			system("pause");
		}
		system("cls");
		bool playAgain = false;
		while (!playAgain)
		{
			string againChoice;
			try //check if player wants to play again, exception 
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
				else //did not enter y or n
				{
					throw "You can only enter 'Y' or 'N'. Choose again.";
				}
			}
			catch (const char * msg) //catch string throw
			{
				cout << "\n" << msg << "\n\n";
			}
		}
	}
	system("cls"); //final thank you, goodbye
	cout << "Thank you for playing my C++ II Gwent Final! :)\n\n";
	cout << R"(                                         @%%@                                *,,/****(&                                                                      
                                        &&&@@@                          &(/******,////,,*****//(@                                                              
                                         @@@@@&                      (,..,,,,,,,**,///*,**//**,****                                                            
                                          @@@@@&                  #**,,,,,,..,**,,*,*//***,,**,******%                                                         
                   @                      &@@@@@&                 *,,,,,,,,***,**,****///***///////***%                                                        
               %%&&&%%@                    @@@@@@%               ,,,,,****////////**/(///////(####(((//                                                        
              %%&&@&@@&                     @@@@@@&             /*,,***/////////////(((//(((#########((                                                        
              &@@@@@@@@                      @@@@@@            @///(**////************////(////(((((##((                                                       
               @&@@@@@@                      &@&* (#           /*////////*,,,,,,,,***********//#((((##((&                                                      
                 %@@&&&@                     &@@,*%%%@       /*//////*****,,,,,,********/**/(#/(((###(((                                                     
                    &&&%&                      &&&&&&&%&&    @(**//**/***,*,,,,,**********/////##(((###(((                                                     
                     &%&%%                     @%#((&@@@&    #/***//**/*****//*,,,****////////((%(((##((#                                                      
                      &&&&&@                    @@@@@@@@     #///***//*****,,,,,,,,,****////////((((((((                                                       
                       &&&&&                      @@@@@@@    (/((((//*/**,**/(((/***/////((///(((%#%%#((#                                                      
                        &@@@@                     @@@@@@@@   //(((//*//***/#%%&&&&&@@@&&%%##%&&@@@@&&&((                                                       
                         &@@@&&                    @@@@@@@@  /##((////***/(#%&&&&%&@@@&&%(#%@@@&&%%@&%##&                                                      
                          %&@&&&                    @@@@@@@@&/#(/(//((**,,**(##%%&&%%%#(/,*(&&%%%&&(((##                                                     
                          (&&&%%&&@                  @@@@@@@#/(((#(#///**,,,,*//((((**//*,*(#####%&%##((##                                                     
                            %%##@@@@                  @@@@@@(#(((//(/((/*******////***/**,,/#%###%%%#((#                                                     
                            @@@@@@&@@                 @@@@@&((//(/(//(((/////((///**,**/***/#%%%%%%%%%#((                                                      
                             %&@@@@@@                  @@@@&//////**/(((((((///*/**/((*,*,,/((%&%%%##%((/(                                                     
                              &@@@@@@@                  @&&(****//(((((((((///**//(#//#(***(#%%%%%%##%((((                                                     
                                @@@@@@@@                 ##/(**///(((#((((((////(//((((((%&&&%%&&%%%#%(((((                                                    
                                 @@&&&@@&              @&%##/*//**/(((#####((((((#(((((((####%%%&&&%%#/(/(((#                                                  
                                  @@&&&&&&          %&&@@(**/***/(//(#%#########/*/##%%%&%##%%%&&%&(/(((((((%%&                                              
                                   @&&&&&&&        %&&@@&&(////*,*((/(##%%######/////(##%%%%%%&&%&@&((((#%%&%%%&@@@                                          
                                    @@&&&&&@    @@@@@@%#@(///,,*(&@%//(#%%%######((###%%%%%%&&&&&@@@@(/(&&&&%@&&&&&&&@                                       
                                      @&&&&%#%@@&&&%&&&@&(////***(%@@@(/((#%&&%%%##((######%%&&&&&@@@@@@&&&%%@&%%&%&&&&&&&&@@                                  
                                       %%@@&%%%&&@@@@&&&&/(/*/%%&&@@@%(((##%&&%%%######%%&&%%&&@@@@@&%&&%&%&%@%@&&&&&&&&&&&&&@                               
                                      &%%@%&&@@@@&@&&@&&&&&(((%%&&&&@@@@@@#(###%%&%%%%%##%%%%%&@@@@@@&%&%%&%%%%%&%&&&&&%&&&&&&&&&&@                            
                                    &&@@&&&&&%&&&&&&&&@&@&&&&%&&%&&&@@@@@@@@@%###%%%%&%%%&&@@@@@@@@&%&%%&@%&%#%%#%@%&%&%&%&&&&&&&&@@                         
                                   @@@@@&%%%%&%&&&%&&%*(%%%%%%%%&&&@@@@@@@@@@@@@#%%@@@@@@@@@@@@@&%%#%%@#@%@&%%%&%%%&%&&%%&%&&&&&&&&&&&&                      
                               @@&@@@&&&&&%%%%&%&&&%&%,*(%%&%%%%%&@@@@@@@@@@@@@@@@#%@@@@@@@@@@@@&%%%%%#@%@%&&&&%%%%%&&%&%%%&%&&%&&&&&&&&@                  
                              &&%&&&&&&&&@&&%&&%%%&%%&///(%&&&&%&&&@@@@@@@@@@@@@@@#&@@@@@@@@@@@%%%%%%%%%@%&&%#%%%#&%@%&%%%&%&&&&&&&&&&&                
                           @&&&%&%&&%&&%&&&&&%&&&%%%%&**/#%&&%&&&&@@@@@@@@@@@@@@@@%@@@@@@@@@@&%%%%&%&%#&%&%&&%@%@%#&%%#%#%&%&%%%&%&&&&&%@&&&&@             
                          &&&%&&%&%&&&&@&&&&@&%%%%%%%(//(%&&&&&&@@@@@@@@@@@@@@@@@@&@@@@@@@@@&&&&&&%&%#&%&%&&%&%&&%&%%##%#%%&%&%%%%%@%&&%&&&&&&&@           
                         &%&&&&&&%&&&&@@@&@%@&&%%%%%%((#%&@&&&&@@@@@@@@@@&&@@&@&@@@@@@%&@@@@&%%&&%#%&%#%%&%%@#&%&@%%###%##&%&%%%&%&%%&&&&&&&%&&        
                        %%%%&&&&&&&&@&@&@&&&%&%&%%%%%*/(#%&&&@@@@@@@@@@@@@@@@@@@@@@@@@&(@&&&&&@&%%%&&%%&%#&%%&%@%&@%&%%#%##%%&%%#%#&%&%&%&&&%&&&&&@      
                       &%&&&%&&&&&@&@@&@&@&%&%%%&&%%%*/(#&&@@@@@@%((//*****%@@@@@&@@@&%&&&%&&&&&&@&%%&&&%%&&&%&&&&%&%%###%%#@%&%@%@%&&%&&&&@@@@      
                      &@&%&&&&@&@@@@@@@&&&&&%&&&&&@%**//(%&&/*,****/(((((((#&@@@@@@@@@&%%%&%##%&&&@&%%%&%%&%&%#&%@&&&%&%%#%&%&%&%%%##@%@&&@&&&@@@@       
                    @&&&&&%%&&&@@@@@@&@@&&&@@@@@&@@////**,*******/(#%&&&%%&&@@@@@@@&&&&&&&#%%%&&%%%%&&&%%&&&%%&&@%@%&&%%%%%%#&%@&&%#%%%%&&@&@@@&&&&@@        
                 @@&&&&&&&&%%&&&@@&&&&%&@@@@@@@@@@#***,,,,,***/((###%#%%%%&@@@&@@@@@@@&%&%&&&&&&%%#&%%%&&&@&%%&&&%&@%@&&%%#%##&&@&@%&%%%&&@@@@@@&&@@@&@        
                 &&&&&&&%&&%&&&@@&&&&@@@@@@@@@@@******,,**/(((((////(#####@@@@@@@@@@@@@@&@@@&%&&%%%&%&&&&@&@&%%%%%%&&%&%%%%%@@&@&&&&&&&@@@@@@@@&&&@@@@       
               @&&&&&&&&%&&%@%%&@&@&&@@@@@@@@@@@@********/((////***//((#%%%%@@@@@@@@@@@@@@@@&@@&&@&&&@&&&&&&&&&&@&%%&%%&%%%&&@&@&&&&&&&@@@@@@@@&@&&@&@@@@      
             @&%%&&&&%&&%&%%&&&%&&@@@@@@@@@@@@@@********//////***/(##%&&&&&@&@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&@&%&&&%&@@&@&@&@@@@@@@@@@@@@@@@@@@@@@@      
            %%#%%&%%&%%@%%%&&%@%&&@@@@@@@@@@@@@(,**,****/(/////(######(((##%&@@@@@@@@@@@@@@@@@@@@@@@@@@&@&&&&&&&&&&&&@@%%&&&&@@@@@&@@@@@@@@@@@@@@@@&@@@@@@     
           &@@@@%#%%%#%%&&%@%%%&&@@@@@@@@@@@&,,*,**((/**//(###((#((((#%%%%%&&&%%%#%&@@@@@@@@&@@@@@@@@@@@&&&&&&&&&&&&@@@&&&@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@     
          &&&&&&&@%&%%%&&%@%%%&&&&&@@@&&@@@/,,**///**/(((##(((((((##%&&&&%&&%%&@&%&%&@@@@@@@@@&@&&@@@@@@&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    
         @&&&&&&&&%%&%%&&&%&&%%%%%%((%%%@@#,,,,,****/(/(((((((((#%%%%%&&%%%%@&&&@@@&&&%%@@@@@@@@@&&&&&&@@@@@&&&&&&&@&&@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@@@@@@@   
       &&&@&&&&&@%&&%%&&%%@&%#(####%&%%&/,,,,,,,*////((((((#%%%%%%%%#####%%&@@@&@@@&%&@@@@@@@@@@@@&&&@@&&&&&@&&&&&&&&&@@@@@@@@@@@@@@@@&@@@@@@@@@@@@@@@@@&@&&   
     @&&@@&&&@&&@&%&&&%###(#####(##%&%%&*,,,,***////((((#%%%%%%####(##%%&&@@&@&@&&@@@@@@@@@@@@&@&@@@&&&&&&%&&&&&&&@@@@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@&&@@@   
    &@&@@&@@@&&@%####%%%###########&&&&&*****///((((#####%%####%%%%%&&&&&@@@@@&&@@@&@@@@@@@@@@@@@@@@&@&@@&&&&%&&%%&&&&@@@@@@@@@@@@@@@@@@&@@@&@@@@@&@&&@@&&&@   
  @&&@@@&&##%#%#%%###########%%%%&&&&&(/*/////(((###%%%%%&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&%%%%&@@@@@@@@@@@@@@@@@@@@@@@@@&@@&@@@@&&@@@   
@@&@@%%#%%%%%%#####%#%%%%%#%#%%%%&&&&&&/(((####%%%%%%%%&&&&&&&&&@@@@@&&@@@@&&%%&%/#@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  
&&@%%%%%%#%%##%%%%%%%%%%%%%%%&%&&&@@@@@%###%%%&&&&&&&&&&&&&&&%/#&&&&@@@@@&@&&%&&&#&@&&@@@@@@@@@@&@@@@@@@@@@@&&&&&&@@@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@&@@@@  )";
	cout << "\n\n";
	system("pause");
	return 0;
}
bool PlayerPass() //passs function 
{
	string yNAnswer;
	bool yNValid = false;
	while (!yNValid)
	{
		cout << "\nAre you sure you want to pass this round? (Enter 'y' or 'n' for yes or no): ";
		getline(cin,yNAnswer);
		if (yNAnswer == "y" || yNAnswer == "Y")
		{
			cout << "\nYou have passed this round. You will not be able to play again until the next round.\n\n";
			yNValid = true;
			system("pause");
			system("cls");
			return true;
		}
		else if (yNAnswer == "n" || yNAnswer == "N")
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

string CoinFlip() //flip coin, show side
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
		return "HEADS";
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
		return "TAILS";
	}
}

void HelpScreen() //help, show all actions 
{
	cout << "\nHelp: Action list\n\n";
	cout << "'player': Displays hand then prompts player for choice of card to play.\n'melee': Shows the player's melee row.\n'ranged': Shows the player's ranged row\n'siege': Shows the player's siege row\n'weather': Shows the player's active weather cards\n'discard': Shows the player's discard pile\n";
	cout << "'hand': Shows the player's hand.\n'ability': Shows the player's ability and, if playing with the Monster deck, activates the ability.\n'pass': Pass on the round for that player, cannot play again till next round starts.\n\nRemember when typing in the name of your card to play, spell it out exactly as shown.\n\n";
}

void StartScreen(bool *ptrBool) //description and title, also menu options (play, rules, and quit)
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
	cout << "Gwent is a card game played in the video game 'The Witcher 3: Wild Hunt'\nCD Projekt Red owns the rights to 'The Witcher' video game series and the card game 'Gwent', I thought it would just be fun to make it into a text-based card game for the final.\n\n";
	cout << "Care for a round of Gwent ? \n\n";

	bool mainMenu = true;
	while (mainMenu)
	{
		try
		{
			string menuString;
			int menuInt;
			cout << "1. Play Gwent\n2. Show Rules\n3. Quit\n\nWhat would you like to do? (Enter the number shown in the menu): ";
			getline(cin, menuString);
			menuInt = stoi(menuString); //test if string is an int, catch exception
			if (menuInt < 1 || menuInt > 3) //catch out of range menu number
			{
				throw "You entered a number out of range of the menu. Only enter 1,2, or 3.\n";
			}
			switch (menuInt) //switch statement for menu choice
			{
			case 1: //if menuInt is 1
				mainMenu = false;
				break;
			case 2: //if menuInt is 2
				ShowBasicRules();
				break;
			case 3: //if menuInt is 3
				mainMenu = false;
				*ptrBool = false;
				break;
			}
		}
		catch (const char * msg) //oor string msg exception
		{
			cout << "\n\n" << msg << endl;
		}
		catch (exception& e) //stoi exception
		{
			cout << "\n\nException occured: " << e.what() << "\n\n";
		}
	}
	system("pause");
	system("cls");
}

void ShowBasicRules() //shows basic rules
{
	cout << "Gwent is a card game with a max of three rounds. The first player to win two rounds is the winner!\n\n";
	cout << "Basic rules:\n1. You start with a ten card hand (unless playing as the Scoia'tael in which you get eleven).\n2. You can only play one card per turn.\n3. Each card can be played in either the melee row, ranged row, siege row, or weather row.\n";
	cout << "4. No cards are draw after the initial draw so use your cards wisely (unless playing as the Northern Realms in which you draw one card on round win).\n5. You can pass out of a round at anytime. This means you will not be able to play until the next round.\n6. Once both players pass the round is over.\n";
	cout << "7. To determine the winner of the round the total attack value will be determined for each player by adding up the attack values of all cards in all rows.\n8. All actions for the game are single words like 'play' and 'pass'. To play a card though it must be spelled exactly as shown. If you ever need help or a reminder of the actions, type 'help'.\n\n";
}

void PrintCrown(int wins) //prints half crowns depending on win 1 or 2
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