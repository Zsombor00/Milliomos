/*
 ============================================================================
 Name        : helloworld.c
 Author      : ZsK
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Structures definitions

//Ehelyett nem tudsz time.h-t hasznalni?
//typedef struct GameTime {
//	int hour;
//	int min;
//	int sec;
//};

typedef struct Question //Ideiglenes, am�g nem v�logatom sz�t a k�rd�seket neh�zs�g szerint (tesztel�si c�l).
{
	int difficulty;
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
};

typedef struct Player //A j�t�kosok "tulajdons�gai".
{
	char name[15]; //Neve (max 15 karakter).
	int difficulty; // A v�lasztott neh�zs�g.
	int prize; //Nyerem�ny Ft-ban.
//	struct GameTime elapsed_time; //J�t�kid�.
	struct Player* next_player;
};

//Function definitions

//struct GameTime idofgv(int masodpercben) //M�sodpercet id�form�tumba(�ra, perc, m�sodperc) �tv�lt� f�ggv�ny.
//{
//	struct GameTime jatek;
//	int marad;
//
//	jatek.hour = masodpercben / 3600;
//	marad = masodpercben % 3600;
//	jatek.min = marad / 60;
//	jatek.sec = marad % 60;
//
//	return jatek;
//
//}
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

void showScores(struct Player *player) {
	printf("________________________________________\n");
	printf("\t\tBEST SCORES\n");
	printf("________________________________________\n");
	printf("________________________________________\n");
	printf(" 1:\t %s \t %d Rounds \n", player->name, player->prize);
	printf("________________________________________\n");
}

void registerPlayer(struct Player* player) {
	printf("Nev:");
	scanf("%s", &player->name);
	printf("Valasszon nehezseget:\nKonnyu(1)      Kozepes(2)     Nehez(3)\n");
	scanf("%d", &player->difficulty);
}

void readQuestions(struct List *list) {
	printf("Reading questions...\n");

	FILE *filePointer = fopen("src/loim.txt", "r");
	if (filePointer == NULL) {
		perror("Error");
	} else {
		while (!feof(filePointer)) {
			struct Question *q = (struct Question*) malloc(sizeof(struct Question));

			fscanf(filePointer, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c", &q->difficulty, &q->question, &q->anwserA, &q->anwserB, &q->anwserC, &q->anwserD,
					&q->rightanwser);
			q->next = NULL;

			if (list->first == NULL) {
				list->first = q;
			} else {
				list->last->next = q;
			}

			list->last = q;
			list->size++;
		}
	}
	fclose(filePointer);
	printf("Kerdesek beolvasva, lista merete: %d\n\n", list->size);
}

void printQuestion(struct Question* iterator) {
	printf("%s\t Nehezseg: %d \n", iterator->question, iterator->difficulty);
	printf("A: %s\t B: %s\t C: %s\t D: %s \n", iterator->anwserA, iterator->anwserB, iterator->anwserC, iterator->anwserD);
}

bool askQuestion(struct Question *iterator) {

		printQuestion(iterator);

		getchar(); //to read empty new line
		char answer = toupper(getchar());

		printf("A valaszt megjeloltuk: %c\n", answer);

		if (answer == iterator->rightanwser) {
			printf("A valasz helyes!\n\n\n");
			return true;

		} else {
			printf("A valasz helytelen. A jo valasz: %c\n\n\n", iterator->rightanwser);
			iterator = iterator->next;
			return false;
		}
	}


//Main
int main() {
	showMenu();

	char choice = toupper(getchar());

	if (choice == 'Q') {
		exit(1);
	} else if (choice == 'E') {
//		showScores();
	} else if (choice == 'S') {
		struct Player player;

		registerPlayer(&player);

		struct List *list = malloc(sizeof(struct List));
		readQuestions(list);

		struct Question *iterator = list->first;
		bool isAnswerRight = true;
		while(isAnswerRight){
			isAnswerRight = askQuestion(iterator);
			if(isAnswerRight){
				player.prize++;
			}
			iterator = iterator->next;
		}

		printf("####GAME OVER####\n");
		showScores(&player);
	}
	return 0;
}

