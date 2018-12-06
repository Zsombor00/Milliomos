#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "debugmalloc.h"
#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED


void registerPlayer(struct Player* player);
bool askQuestionFromPlayer(struct Question *iterator, struct Player *player);
void setPlayTime(int elapsedTime, struct Player* player);
clock_t measureTime();
void freeList (struct Question *q, struct Question *first);


#endif // OTHER_H_INCLUDED
