#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "debugmalloc.h"
#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

void readRecords (struct Player *highscorePlayers);
void readQuestions(struct List *list);
void writeInFile (struct Player *highscorePlayers);

#endif // FILEIO_H_INCLUDED
