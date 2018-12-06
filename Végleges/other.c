#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "debugmalloc.h"
#include "Structs.h"
#include "other.h"

void registerPlayer(struct Player* player)
 {
	printf("Irjon be egy nevet (max 10 karakter):");
	scanf("%s", &player->name);
	printf("Valasszon nehezseget:\nKonnyu(1)      Kozepes(2)     Nehez(3)\n");
	int d = 0;
	scanf("%d", &d);
	if (d != 1 && d != 2 && d != 3) {
		perror("Nincs ilyen nehezseg");
		exit(-1);
	} else {
		player->difficulty = d;
	}
	player->halfHelpAvailable = true;
	player->audienceHelpAvailable = true;
}

bool askQuestionFromPlayer(struct Question *iterator, struct Player *player) {
	char choice;
	choice = printQuestionScreenAndGetUserInput(choice, player, iterator);

	if ((player->audienceHelpAvailable == true) && (choice == 'K')) {
		player->audienceHelpAvailable = false;
		printf("A kozonseg altal javasolt megoldas: %c \n\n", iterator->rightanwser);
		choice = printQuestionScreenAndGetUserInput(choice, player, iterator);
	}

	if ((player->halfHelpAvailable == true) && (choice == 'F')) {
		player->halfHelpAvailable = false;

		printf("A megmaradt opciok: \t%c  es ", iterator->rightanwser);
		if (iterator->rightanwser == 'D') {
			printf("\tC \n\n");
		} else {
			printf("\tD \n\n");
		}
		choice = printQuestionScreenAndGetUserInput(choice, player, iterator);
	}

	if (choice == iterator->rightanwser) {
		printf("Megjeloltuk: %c \n", choice);
		printf("A valasz helyes!\n\n\n");
		player->prize++;
		return true;

	} else {
		printf("Megjeloltuk: %c \n", choice);
		printf("A valasz helytelen. A jo valasz: %c\n\n\n", iterator->rightanwser);
		return false;
	}
}
void setPlayTime(int elapsedTime, struct Player* player) {
	player->gameTime = (struct GameTime*) malloc(sizeof(struct GameTime));
	player->gameTime->min = (int) floor(elapsedTime / 60);
	player->gameTime->sec = elapsedTime % 60;
}
clock_t measureTime() {
	clock_t timePoint;
	time(&timePoint);
	return timePoint;
}
void freeList (struct Question *q, struct Question *first)
{
    if (q==first)
    {
        return;
    }
    freeList(q->next, first);

    free(q);


}
