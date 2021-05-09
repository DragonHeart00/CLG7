#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "Controller.h"

 static const char solitaireSuits[5]={'H','D','S','C','\0'};
 static const char solitaireCards[14]={'K','Q','J','T','9','8','7','6','5','4','3','2','A','\0'};
 static const char solitaireCardsReverse[14]={'A','2','3','4','5','6','7','8','9','T','J','Q','K','\0'};
struct Card{
    //This holds our card
    //First char stores our card value e.g A for Ace
    //The second char stores our card Foundation e.g H for Hearts
    char value[3];
    //This pointer represents a memory address of the next card in our linked list
    struct Card *Next;
    bool fliped;
    char color;

};


struct Pile{

   struct Card * cardList;

};

struct Foundation{
     char FoundationLetter;
     struct Card * cardList;
};

struct Game{

struct Pile Piles[7];
struct Foundation Foundations[4];
//
};

struct MoveSummary{
bool isvalid;
char  Message[50];
};
//Card will be used to represent the cardItem and its row/column


//Prototypes
void Initialize(struct Game *game);
void InitializePiles(struct Pile Piles[]);
void InitializeFoundations(struct Foundation Foundations[]);
void LoadGame();
void LoadSW(struct Game* game,char Message[10]);
void FlipCards(struct Card * cardList);
void Load(char filename[],struct Game *Game,char Message[4],int flag);
void DisplayPiles(struct Game *Game);
void DisplayFoundations(struct Foundation Foundations[]);
void Render(struct Game *game);
void DisplayCardList(struct Card * cardList);
void AddDisplayFoundation(struct Foundation Foundations[],char PileGrid[][13][2],int column);
void AddDisplayPile(struct Pile _Pile,char PileGrid[][7][3],int column);
void Shuffle(struct Pile Piles[]);
void Split(struct Pile Piles[]);
bool isCardInPile(struct Card * card,char cardvalue[2]);
bool isCardInPile1(struct Card * cardList,int index);
struct Card * GetCard(struct Card * cardList, int Index);
struct Card * GetCard1(struct Card * cardList, char cardvalue[2]);
char * RandomCardValue1();
void MovePileCardsToFoundation();
int ListCount(struct Card * cardList);
void AddCardToList(struct Card*cardList,struct Card *CardToAdd);
struct MoveSummary IsValidMove(struct Card*cardList,struct Card *CardToAdd);

void AddCardsToPile(struct Pile Piles[],char data[53][4], int PileColumn,int startIndex,int endIndex,int flipedStartIndex);
void GameAction(char command[20],struct Game* game,char LastComand[50],bool isPlayActive);
  void RandomCardValue(char RandomCard[2]);
  bool MoveCardToPile(struct Game *game,int FinalPileColumn,char data[2]);
  bool MoveCardToFoundation(struct Game *game,int FinalPileColumn,char data[2]);
   void DisplayFoundations1(struct Game*game);
  void RemoveLastCard(struct Game* game,int pilenumber);
void GenerateDiffPileCard(struct Card * cardList, char cardvalue[2]);
void SaveToFile(char filename[],struct Pile Piles[],int column );
void DisplayMovSumMessage(struct  MoveSummary sum);
void MoveCardToPile1(struct Game* game,int FinalPileColumn,int currentPileColumn);
void SplitDeck(struct Game*game,int nSplitNumber,char message[]);
void RandomShuffle(struct Game*game,char message[]);
void SaveDeckCards(struct Game*game,char fileName[],char message[]);
void ResetGame(struct Game *game,char message[]);
void MoveCardToPile2(struct Game* game,int FinalPileColumn,int currentPileColumn);
void ExitGame();
void AddCardToList2(struct Game *game,struct Card *CardToAdd,int PNumber);
void AddCardToList3(struct Game *game,struct Card *CardToAdd,int PNumber);
struct MoveSummary IsValidMove2(struct Card*lastCard,struct Card *CardToAdd);



#endif // GAMELOGIC_H_INCLUDED
