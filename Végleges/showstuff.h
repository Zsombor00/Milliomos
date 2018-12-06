#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#ifndef SHOWSTUFF_H_INCLUDED
#define SHOWSTUFF_H_INCLUDED
void showScores(struct Player *player);

void showMenu();

void printAvailableHelp(struct Player* player);

char printQuestionScreenAndGetUserInput(char choice, struct Player* player, struct Question* iterator);

void printQuestion(struct Question* iterator);

#endif // SHOWSTUFF_H_INCLUDED
