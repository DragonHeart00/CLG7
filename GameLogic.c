#include "GameLogic.h"
#include <unistd.h>

#define printf_s printf


void LoadSW(struct Game *game, char Message[10]) {

    for (int i = 0; i < 7; i++) {
        FlipCards(game->Piles[i].cardList);
    }
    strcpy(Message, "OK");
}


static bool isSecondComValid = false;

void Load(char filename[], struct Game *game, char Message[10], int flag) {
    char ReadFields[53][4];
    readFromFile(filename, "r", ReadFields, Message);
    int fileCoun = FileCount(filename, 0);

    if (fileCoun < 52 || fileCoun > 52) {
        strcpy(Message, "Failed");
    }


    if (strcmp(Message, "OK") == 0) {

        if (flag == 0) {


            int cardCount = 0;
            while (true) {
                for (int j = 0; j < 7; j++) {

                    if (cardCount < 7) {

                        game->Piles[j].cardList = (struct Card *) malloc(sizeof(struct Card));
                        game->Piles[j].cardList->Next = NULL;
                        char lo[3];
                        lo[0] = ReadFields[cardCount][0];
                        lo[1] = ReadFields[cardCount][1];
                        lo[2] = '\0';
                        game->Piles[j].cardList->fliped = false;
                        strcpy(game->Piles[j].cardList->value, lo);
                        game->Piles[j].cardList->color = game->Piles[j].cardList->value[1];

                    } else {
                        if (cardCount > 52 - 1) {
                            return;
                        }
                        //printf("hj");
                        struct Card *card = (struct Card *) malloc(sizeof(struct Card));
                        card->Next = NULL;

                        char lo[3];
                        lo[0] = ReadFields[cardCount][0];
                        lo[1] = ReadFields[cardCount][1];
                        lo[2] = '\0';


                        strcpy(card->value, lo);
                        card->color = card->value[1];


                        card->fliped = false;

                        AddCardToList(game->Piles[j].cardList, card);

                    }

                    cardCount++;
                }
            }
        } else if (flag == 1) {


            AddCardsToPile(game->Piles, ReadFields, 0, 0, 0, 0);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 1, 1, 6, 1);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 2, 7, 13, 2);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 3, 14, 21, 3);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 4, 22, 30, 4);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 5, 31, 40, 5);
            DisplayPiles(game);
            AddCardsToPile(game->Piles, ReadFields, 6, 41, 51, 6);
            DisplayPiles(game);
        }

    }


}


void LoadGame() {

    struct Game *_game = (struct Game *) malloc(sizeof(struct Game));
    Initialize(_game);

    Render(_game);
}


static struct Game *memory;
static int isPlayActive = false;

void Render(struct Game *game) {
    char inputString[50];
    newline(3);
//GameAction("p",game);

    bool isplayActiv = false;
    char LastComand[50];
    strcpy(LastComand, "");
    while (true) {
        printf("input:");
        fgets(inputString, 50, stdin);

        GameAction(inputString, game, LastComand, isplayActiv);
    }

}


void GameAction(char command[20], struct Game *game, char LastCommand[50], bool isPlayActiv) {

    char PlayerCommand[2][50];
    char splitch[] = " ";


    char _Message[10];


    split(PlayerCommand, command, splitch);
    char cr = ' ';
    if (canSplit(command, cr) == true) {
        isSecondComValid = true;

    } else {
        isSecondComValid = false;

    }


    if (strstr(PlayerCommand[0], "LD") != NULL && isPlayActive == false) {

        //Load(PlayerCommand[1],game,_Message);
        if (strlen(PlayerCommand[1]) > 4) {

            Load(PlayerCommand[0], game, _Message, 0);
        } else {
            Load("CardNames.txt", game, _Message, 0);
        }


        if (strcmp(_Message, "OK") == 0) {
            DisplayPiles(game);
        }

        //  printf_s("%s \n",_Message);

        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(PlayerCommand[0], "SW") != NULL && isPlayActive == false) {
        LoadSW(game, _Message);
        if (strcmp(_Message, "OK") == 0) {
            DisplayPiles(game);
        }


        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(PlayerCommand[0], "SI") != NULL && isPlayActive == false) {
        int nsplitNumber = 0;
        nsplitNumber = Randomize(1, 51);
        if (strcmp(PlayerCommand[1], "") != 0) {
            char *ptr;
            nsplitNumber = strtol(PlayerCommand[1], &ptr, 10);

        }

        SplitDeck(game, nsplitNumber, _Message);


        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(PlayerCommand[0], "SR") != NULL && isPlayActive == false) {

        RandomShuffle(game, _Message);


        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(PlayerCommand[0], "SD") != NULL && isPlayActive == false) {

        //ClearFile(PlayerCommand[1]);
        SaveDeckCards(game, PlayerCommand[1], _Message);

        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);

    } else if (strstr(PlayerCommand[0], "QQ") != NULL || isPlayActive == true) {
        printf("Exiting....");
        sleep(5);
        ExitGame();

    } else if (strstr(PlayerCommand[0], "P") != NULL && isPlayActive == false) {
        isPlayActive = true;
        Load("CardNames.txt", game, _Message, 1);
        memory = game;
        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(PlayerCommand[0], "Q") != NULL || isPlayActive == true) {

        ResetGame(memory, _Message);
        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", _Message);
        strcpy(LastCommand, command);
    } else if (strstr(command, "->") != NULL && isPlayActive == true) {
        char PlayCommand[2][50];
        char splitc1[] = "->";
        split(PlayCommand, command, splitc1);


        // char foundationStrings[10];
        /// char ColumnStrings[16];
        // strcpy(foundationStrings,"F4F3F2F1");
        ///    strcpy(ColumnStrings,"C1C2C3C4C5C6C7");

        char two[3];
        two[0] = PlayCommand[1][0];
        two[1] = PlayCommand[1][1];
        two[2] = '\0';


        if (strcmp("C1", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';
            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }
        if (strcmp("C2", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }
        if (strcmp("C3", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';
            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }


        if (strcmp("C4", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';
            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }


        if (strcmp("C5", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';
            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }
        if (strcmp("C6", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';
            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }
        }
        if (strcmp("C7", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToPile(game, ColNumber - 1, tw) == true) {
                DisplayPiles(game);
            }

        }

        if (strcmp("F4", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToFoundation(game, ColNumber - 1, tw) == true) {
                DisplayFoundations1(game);
            }

        }

        if (strcmp("F3", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToFoundation(game, ColNumber - 1, tw) == true) {
                DisplayFoundations1(game);
            }

        }

        if (strcmp("F2", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToFoundation(game, ColNumber - 1, tw) == true) {
                DisplayFoundations1(game);
            }

        }
        if (strcmp("F1", two) == 0) {

            int ColNumber = 0;
            ColNumber = CharToInt(PlayCommand[1][1]);

            char tw[3];
            tw[0] = PlayCommand[0][0];
            tw[1] = PlayCommand[0][1];
            tw[2] = '\0';

            if (MoveCardToFoundation(game, ColNumber - 1, tw) == true) {
                DisplayFoundations1(game);
            }

        }


        printf("Last Command:%s \n", LastCommand);
        printf("Message:%s \n\n", "OK");
        strcpy(LastCommand, command);
    } else {

        if (isPlayActive) {

            printf("Command not available on play mode\n");
        } else {
            printf("wrong command\n");
        }

        strcpy(LastCommand, command);
    }


}


char *RandomCardValue1() {
    char card[3];
    //Generate a random card from the 12 solitaire cards
    card[0] = solitaireCards[Randomize(0, 12)];
    //Generate a random suit from 4 solitaire suits
    card[1] = solitaireSuits[Randomize(0, 3)];
    card[2] = '\0';
    char *newCard = (char *) malloc(sizeof(char) * 2);
    // newCard=card;
    strcpy(newCard, card);

    return newCard;
}


bool isCardInPile(struct Card *cardList, char cardvalue[2]) {

    struct Card *next = cardList;
    bool cardExists = false;
    while (next != NULL) {
        if (strcmp(next->value, cardvalue) == 0) {
            cardExists = true;
            return cardExists;

        }


        next = next->Next;
    }
    return cardExists;
}


void FlipCards(struct Card *cardList) {
    struct Card *card = cardList;
    while (card != NULL) {
        if (card->fliped == false) {
            card->fliped = true;

        }


        card = card->Next;
    }

}


struct Card *GetCard(struct Card *List, int Index) {
    struct Card *card = List;


    int listCounter = 0;


    while (listCounter != Index) {
        card = card->Next;
        listCounter++;

    }

    return card;
};


struct Card *GetCard3(struct Card *List) {

    struct Card *card = List;

    struct Card *card1;
    while (card != NULL) {
        if (card != NULL) {
            card1 = card;

        }
        card = card->Next;

    }


    return card1;
};


struct Card *GetCard1(struct Card *cardList, char cardvalue[2]) {

    bool cardExists = false;
    struct Card *card = NULL;
    cardExists = isCardInPile(cardList, cardvalue);
    if (cardExists) {
        card = cardList;

        while (strcmp(card->value, cardvalue) != 0 && card->Next != NULL) {
            card = card->Next;

        }
    }
    return card;
}


void AddCardToList(struct Card *cardList, struct Card *CardToAdd) {

    if (cardList != NULL) {
        struct Card *card = NULL;

        card = GetCard3(cardList);

        if (card != NULL) {
            card->Next = CardToAdd;
        }
    } else {
        cardList = CardToAdd;
    }

}


void AddCardToList2(struct Game *game, struct Card *CardToAdd, int PNumber) {

    if (game->Piles[PNumber].cardList != NULL) {
        struct Card *card = NULL;

        card = GetCard3(game->Piles[PNumber].cardList);

        if (card != NULL) {
            card->Next = CardToAdd;

        }

    } else {
        game->Piles[PNumber].cardList = CardToAdd;
    }

}


int ListCount(struct Card *List1) {

    int listCounter = 0;
    if ((List1 != NULL)) {
        struct Card *card = List1;
//  if(card!=NULL)    listCounter+1;
        while (card != NULL) {
            card = card->Next;
            listCounter++;
        }

    }

    return listCounter;

}


void Initialize(struct Game *game) {
    //code goes here
    InitializePiles(game->Piles);
    InitializeFoundations(game->Foundations);
    printf_s("Foundations\n\n");
    DisplayFoundations(game->Foundations);
    //newline(1);
    DisplayPiles(game);


}


void InitializeFoundations(struct Foundation Foundations[]) {

    for (int j = 0; j < 4; j++) {
        Foundations[j].FoundationLetter = solitaireSuits[j];
        Foundations[j].cardList = NULL;
    }

}


void InitializePiles(struct Pile Piles[]) {
    for (int i = 0; i < 7; i++) {
        Piles[i].cardList = NULL;
    }


}


void DisplayFoundations(struct Foundation Foundations[]) {


    char DisplayGrid[4][13][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strcpy(DisplayGrid[i][j], "");

        }
    }
    for (int i = 0; i < 4; i++) {

        AddDisplayFoundation(Foundations, DisplayGrid, i);
    }


    for (int i = 0; i < 4; i++) {
        printf_s("%c\t", Foundations[i].FoundationLetter);
        for (int j = 0; j < 13; j++) {
            printf_s("%s\t", DisplayGrid[i][j]);

        }
        printf_s("\n");
    }

}


void DisplayFoundations1(struct Game *game) {

    char DisplayGrid[4][13][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strcpy(DisplayGrid[i][j], "");

        }
    }
    for (int i = 0; i < 4; i++) {

        AddDisplayFoundation(game->Foundations, DisplayGrid, i);
    }


    for (int i = 0; i < 4; i++) {
        printf_s("%c\t", game->Foundations[i].FoundationLetter);
        for (int j = 0; j < 13; j++) {
            printf_s("%s\t", DisplayGrid[i][j]);

        }
        printf_s("\n");
    }

}


struct MoveSummary IsValidMove(struct Card *lastCard, struct Card *CardToAdd) {


    struct MoveSummary movesummary;
    movesummary.isvalid = true;

    strcpy(movesummary.Message, "valid move");
    int currentCardIndex = 0;
    int lastCardIndex = 0;

    if (CardToAdd == NULL || lastCard == NULL) {

        movesummary.isvalid = true;

        strcpy(movesummary.Message, "Pile or card does not exists");

    } else {

        for (int i = 0; i < 13; i++) {

            if (solitaireCards[i] == lastCard->value[0]) {
                lastCardIndex = i;
            }
            if (solitaireCards[i] == CardToAdd->value[0]) {
                currentCardIndex = i;
            }
        }
        if (lastCard->color == CardToAdd->color) {

            movesummary.isvalid = false;
            strcpy(movesummary.Message, "color match");
        } else if (strcmp(lastCard->value, CardToAdd->value) == 0) {

            movesummary.isvalid = false;
            strcpy(movesummary.Message, "card match");
        } else if (CardToAdd->fliped == false) {
            movesummary.isvalid = false;
            strcpy(movesummary.Message, "card not visible");
        } else if (lastCardIndex < currentCardIndex) {
            movesummary.isvalid = false;
            strcpy(movesummary.Message, "card is bigger");
        }

    }


    return movesummary;

}


struct MoveSummary IsValidMove2(struct Card *lastCard, struct Card *CardToAdd) {


    struct MoveSummary movesummary;
    movesummary.isvalid = true;

    strcpy(movesummary.Message, "valid move");
    int currentCardIndex = 0;
    int lastCardIndex = 0;

    if (CardToAdd == NULL || lastCard == NULL) {

        movesummary.isvalid = false;

        strcpy(movesummary.Message, "Pile or card does not exists");

    } else {

        for (int i = 0; i < 13; i++) {

            if (solitaireCards[i] == lastCard->value[0]) {
                lastCardIndex = i;
            }
            if (solitaireCards[i] == CardToAdd->value[0]) {
                currentCardIndex = i;
            }
        }
        if (lastCard->color != CardToAdd->color) {

            movesummary.isvalid = false;
            strcpy(movesummary.Message, "color not match");
        } else if (lastCardIndex != currentCardIndex - 1) {
            movesummary.isvalid = false;
            strcpy(movesummary.Message, "card not in the correct order");
        }

    }


    return movesummary;

}


void AddDisplayFoundation(struct Foundation Foundations[], char PileGrid[][13][2], int column) {
    struct Card *card = Foundations[column].cardList;
    int counter = 0;
    while (card != NULL) {
        if (card->fliped == true) {

            strcpy(PileGrid[column][counter], card->value);
        } else {
            strcpy(PileGrid[column][counter], "[]");

        }

        card = card->Next;
        counter++;
    }
}


void DisplayPiles(struct Game *game) {

    int PileCounts[7];

    for (int i = 0; i < 7; i++) {
        PileCounts[i] = ListCount(game->Piles[i].cardList);

    }

    int highestRow = maximumValue(PileCounts, 7);


    char DisplayGrid[highestRow][7][3];
    for (int i = 0; i < highestRow; i++) {
        for (int j = 0; j < 7; j++) {
            char tmp[2] = "";
            strcpy(DisplayGrid[i][j], tmp);
        }

    }

    for (int i = 0; i < 7; i++) {

        AddDisplayPile(game->Piles[i], DisplayGrid, i);
    }
    printf_s("\n");
    for (int i = 0; i < 7; i++) {
        printf_s("C%d\t", i + 1);
    }

    printf_s("\n\n");

    for (int i = 0; i < highestRow; i++) {
        for (int j = 0; j < 7; j++) {
            printf_s("%s\t", DisplayGrid[i][j]);

        }
        printf_s("\n");
    }


}


void AddDisplayPile(struct Pile _Pile, char PileGrid[][7][3], int column) {
    if (_Pile.cardList != NULL) {

        struct Card *card = _Pile.cardList;
        int counter = 0;
        while (card != NULL) {
            if (card->fliped == true) {

                strcpy(PileGrid[counter][column], card->value);
            } else {
                char tmp[3] = "[]";
                tmp[2] = '\0';

                strcpy(PileGrid[counter][column], tmp);

            }

            card = card->Next;
            counter++;
        }
    }

}


void
AddCardsToPile(struct Pile Piles[], char data[53][4], int PileColumn, int startIndex, int endIndex, int flipCount) {
    int FlipCounter = 0;

    for (int i = startIndex; i <= endIndex; i++) {

        if (i == startIndex) {
            Piles[PileColumn].cardList = (struct Card *) malloc(sizeof(struct Card));
            Piles[PileColumn].cardList->Next = NULL;
            char lo[3];
            lo[0] = data[i][0];
            lo[1] = data[i][1];
            lo[2] = '\0';

            strcpy(Piles[PileColumn].cardList->value, lo);
            Piles[PileColumn].cardList->color = Piles[PileColumn].cardList->value[1];
            if (PileColumn != 0) {
                Piles[PileColumn].cardList->fliped = false;
            } else {
                Piles[PileColumn].cardList->fliped = true;
            }

        } else {
            struct Card *card = (struct Card *) malloc(sizeof(struct Card));
            card->Next = NULL;

            char lo[3];
            lo[0] = data[i][0];
            lo[1] = data[i][1];
            lo[2] = '\0';
            strcpy(card->value, lo);
            card->color = card->value[1];


            if ((FlipCounter + 1) < flipCount) {
                card->fliped = false;
                FlipCounter++;
            } else {
                card->fliped = true;
            }
            AddCardToList(Piles[PileColumn].cardList, card);
        }

    }


}


void SplitDeck(struct Game *game, int nSplitNumber, char message[]) {

    int iIndex = 0;

    while (nSplitNumber > 0) {

        int ListCounter =ListCount(game->Piles[iIndex].cardList);
        while (ListCounter > 0) {
            MoveCardToPile1(game, 6, iIndex);
            DisplayPiles(game);
            ListCounter--;

            nSplitNumber--;
            if (nSplitNumber < 1) {
                ListCounter = -1;
            }


        }
        if (iIndex < 7) {
            iIndex++;
        }


    }

    for (int i = 0; i < 5; i++) {
        if (game->Piles[i].cardList != NULL) {
            int ListCounter = ListCount(game->Piles[i].cardList);
            while (ListCounter > 0) {
                MoveCardToPile1(game, 5, i);
                DisplayPiles(game);
                ListCounter--;
            }
        }

    }
    strcpy(message, "OK");
}


void RandomShuffle(struct Game *game, char message[]) {
    int RandomPile = Randomize(0, 4);

    int iIndex = 5;
    while (iIndex < 7) {

        int ListCounter = ListCount(game->Piles[iIndex].cardList);
        while (ListCounter > 0) {
            MoveCardToPile2(game, RandomPile, iIndex);
            DisplayPiles(game);
            ListCounter--;


        }
        iIndex++;
    }
    strcpy(message, "OK");
}

void SaveDeckCards(struct Game *game, char filename[], char message[]) {
    if (filename[0] == '\0' || strlen(filename) < 5) {
        strcpy(filename, "CardNames.txt");
        ClearFile(filename);

    }



    // writeToFile(filename,"a","\n");
    for (int i = 0; i < 7; i++) {
        int mIndex = 0;
        int ListCounter = ListCount(game->Piles[i].cardList);
        while (mIndex < ListCounter) {
            struct Card *card = GetCard(game->Piles[i].cardList, mIndex);
            writeToFile(filename, "a", card->value);
            mIndex++;
        }
    }
    strcpy(message, "OK");
}


bool MoveCardToFoundation(struct Game *game, int FinalPileColumn, char data[2]) {


    struct Card *card1 = GetCard3(game->Foundations[FinalPileColumn].cardList);
    int currentPileColumn = 0;


    struct Card *lo = NULL;
    for (int i = 0; i < 7; i++) {
        struct Card *card3 = GetCard1(game->Piles[i].cardList, data);

        if (card3 != NULL) {

            currentPileColumn = i;

        }
    }
    lo = GetCard1(game->Piles[currentPileColumn].cardList, data);

    struct MoveSummary moveSum = IsValidMove2(card1, lo);

    if (moveSum.isvalid == false) {
        printf("%s\n", moveSum.Message);
        return false;
    } else {
        RemoveLastCard(game, currentPileColumn);


        AddCardToList3(game, lo, FinalPileColumn);


        struct Card *CardL = GetCard3(game->Piles[currentPileColumn].cardList);


        return true;

    }


}


void AddCardToList3(struct Game *game, struct Card *CardToAdd, int PNumber) {

    if (game->Foundations[PNumber].cardList != NULL) {
        struct Card *card = NULL;

        card = GetCard3(game->Foundations[PNumber].cardList);

        if (card != NULL) {
            card->Next = CardToAdd;

        }

    } else {
        game->Foundations[PNumber].cardList = CardToAdd;
    }

}


void MoveCardToPile1(struct Game *game, int FinalPileColumn, int currentPileColumn) {

    struct Card *card = GetCard3(game->Piles[currentPileColumn].cardList);
    RemoveLastCard(game, currentPileColumn);
    card->Next = NULL;
    AddCardToList(game->Piles[FinalPileColumn].cardList, card);

}

void MoveCardToPile2(struct Game *game, int FinalPileColumn, int currentPileColumn) {

    struct Card *card = GetCard3(game->Piles[currentPileColumn].cardList);
    RemoveLastCard(game, currentPileColumn);
    card->Next = NULL;
    if (game->Piles[FinalPileColumn].cardList == NULL) {
        game->Piles[FinalPileColumn].cardList = card;
    } else {
        AddCardToList(game->Piles[FinalPileColumn].cardList, card);
    }

}


bool MoveCardToPile(struct Game *game, int FinalPileColumn, char data[2]) {
    struct Card *card1 = GetCard3(game->Piles[FinalPileColumn].cardList);
    int currentPileColumn = 0;


    struct Card *lo = NULL;
    for (int i = 0; i < 7; i++) {
        struct Card *card3 = GetCard1(game->Piles[i].cardList, data);

        if (card3 != NULL) {

            currentPileColumn = i;

        }
    }
    lo = GetCard1(game->Piles[currentPileColumn].cardList, data);

    struct MoveSummary moveSum = IsValidMove(card1, lo);

    if (moveSum.isvalid == false) {
        printf("%s\n", moveSum.Message);
        return false;
    } else {
        RemoveLastCard(game, currentPileColumn);


        AddCardToList2(game, lo, FinalPileColumn);

        struct Card *CardL = GetCard3(game->Piles[currentPileColumn].cardList);
        if (CardL != NULL) {
            if (CardL->fliped == false) {
                CardL->fliped = true;
            }
        }

        return true;

    }
    // RemoveLastCard(game,currentPileColumn);
    // card->Next=NULL;
    //AddCardToList(game->Piles[FinalPileColumn].cardList,card);
}


void RemoveLastCard(struct Game *game, int pilenumber) {

    int listCounter = ListCount(game->Piles[pilenumber].cardList);
    int finalIndex = listCounter - 2;
    if (listCounter > 1) {
        struct Card *card3 = GetCard(game->Piles[pilenumber].cardList, finalIndex);
        if (finalIndex >= 0) {

            card3->Next = NULL;
        } else {
            card3 = NULL;// GetCard(cardList,0);
        }
    } else {
        game->Piles[pilenumber].cardList = NULL;
    }
}


void ResetGame(struct Game *game, char message[]) {
    strcpy(message, "Failed");
    DisplayPiles(game);


    strcpy(message, "Ok");

}


void ExitGame() {

    exit(0);
}
