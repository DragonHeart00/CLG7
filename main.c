#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GameLogic.h"
#include "Controller.h"

int main() {

    printf("Welcome to Yukon game\nGroup7\n\n");

    srand(time(0));

    LoadGame();

    return 0;
}
