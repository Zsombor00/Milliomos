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
#include "showstuff.h"
void showScores(struct Player *player) {
	printf("_____________________________________________________________________________________\n");
	printf("\t\t\t\tBEST SCORES\n");
	printf("_____________________________________________________________________________________\n");
	printf("Rank\t Difficulty\t Name\t\t Prize\t\t Time\n");
	for (int k=0; k<=4; k++)
 {
 printf("%d.\t %d\t\t %s    \t\ %dFt   \t %d:%d\n", k+1 ,player[k].difficulty,player[k].name, player[k].prize,player[k].gameTime->min, player[k].gameTime->sec);
 }

    printf("_____________________________________________________________________________________\n");

	/*printf(" 1:\t %s\t %d\t %dm %ds \n", player->name, player->prize, player->gameTime->min, player->gameTime->sec);
	printf("____________________________________________________________________\n");*/
}
void showMenu() {
	printf("________________________________________\n");
	printf("       LEGYEN ON IS MILLIOMOS!\n");
	printf("________________________________________\n");
	printf("________________________________________\n");
	printf(" -> Nyomjon S-t a jatek inditasahoz\n");
	printf(" -> Nyomjon E-t az eredmenyek megtekintesehez\n");
	printf(" -> Nyomjon Q-t a kilepeshez\n");
	printf("________________________________________\n");
}
void printAvailableHelp(struct Player* player) {
	printf("_________________________________________________________________\n");
	printf("Hasznalhato segitsegek: ");
	if (player->audienceHelpAvailable == true) {
		printf("\t Kozonseg (K)");
	}
	if (player->halfHelpAvailable == true) {
		printf("\t Felezes (F) ");
	}
	printf("\n\n");
}
char printQuestionScreenAndGetUserInput(char choice, struct Player* player, struct Question* iterator) {
	printAvailableHelp(player);
	printQuestion(iterator);
	getchar(); //to read empty new line
	choice = toupper(getchar());
	if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'K' && choice != 'F') {
		printf("Nincs ilyen opcio: %c  - Valassz mast!\n", choice);
		choice = printQuestionScreenAndGetUserInput(choice, player, iterator);
	}
	return choice;
}
void printQuestion(struct Question* iterator) {
	printf("%s\t Nehezseg: %d \n\n", iterator->question, iterator->level);
	printf("A: %s\t B: %s\t C: %s\t D: %s \n", iterator->anwserA, iterator->anwserB, iterator->anwserC, iterator->anwserD);
	printf("_________________________________________________________________\n");
}
