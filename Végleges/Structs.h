#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "debugmalloc.h"
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct GameTime {
	int min;
	int sec;
};

typedef struct Question
{
	int level;
	char question[200];
	char anwserA[200];
	char anwserB[200];
	char anwserC[200];
	char anwserD[200];
	char rightanwser;

	struct Question *next;
};

typedef struct List {
	struct Question *first;
	struct Question *last;

	int size;
}List;

typedef struct Player //A jattkosok "tulajdonsagai".
{
	char name[10]; //Neve (max 10 karakter).
	int difficulty; // A valasztott nehezseg.
	int prize; //Nyeremeny Ft-ban.
	bool audienceHelpAvailable;
	bool halfHelpAvailable;
	struct GameTime *gameTime;
};

#endif // STRUCTS_H_INCLUDED
