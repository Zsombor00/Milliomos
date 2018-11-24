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
#include <time.h>
#include <math.h>

//Structures definitions

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
};

typedef struct Player //A jattkosok "tulajdonsagai".
{
	char name[10]; //Neve (max 10 karakter).
	int difficulty; // A valasztott nehezseg.
	int prize; //Nyeremeny Ft-ban.
	bool audienceHelpAvailable;
	bool halfHelpAvailable;
	struct GameTime *gameTime;
};

//Function definitions
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

void registerPlayer(struct Player* player) {
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

void readRecords (struct Player *highscorePlayers)
{
    FILE* filePointer=fopen("records.txt", "r");
    if (filePointer==NULL) {
        perror("Error");
    } else{
    int i=0;
    while (!feof(filePointer))
    {

        fscanf(filePointer, "%d|%[^|]|%d|%d|%d", &highscorePlayers[i].difficulty, &highscorePlayers[i].name, &highscorePlayers[i].prize, &highscorePlayers[i].gameTime->min, &highscorePlayers[i].gameTime->sec);
        i++;

    }
    }
    fclose(filePointer);

}


void readQuestions(struct List *list) {
	printf("Reading questions...\n");

	FILE *filePointer = fopen("loim.txt", "r");
	if (filePointer == NULL) {
		perror("Error");
	} else {
		while (!feof(filePointer)) {
			struct Question *q = (struct Question*) malloc(sizeof(struct Question));

			fscanf(filePointer, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c", &q->level, &q->question, &q->anwserA, &q->anwserB, &q->anwserC, &q->anwserD,
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
		list->last->next=list->first; //Hogy ne fogyjunk ki kerdesekbol, a lancolt lista utolso eleme az elsore mutat.
	}
	fclose(filePointer);
	printf("Kerdesek beolvasva, lista merete: %d\n\n", list->size);
}

void printQuestion(struct Question* iterator) {
	printf("%s\t Nehezseg: %d \n\n", iterator->question, iterator->level);
	printf("A: %s\t B: %s\t C: %s\t D: %s \n", iterator->anwserA, iterator->anwserB, iterator->anwserC, iterator->anwserD);
	printf("_________________________________________________________________\n");
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

void writeInFile (struct Player *highscorePlayers)
{
    FILE *filePointer;
 filePointer=fopen("records.txt", "w");
 for(int h=0; h<=4; h++)
{
    fprintf(filePointer,"%d|%s|%d|%d|%d\n", highscorePlayers[h].difficulty, highscorePlayers[h].name, highscorePlayers[h].prize, highscorePlayers[h].gameTime->min, highscorePlayers[h].gameTime->sec);

}
fclose(filePointer);
}


//Main
int main()
{
    showMenu();

    srand(time(0));

    struct Player highScores[5];
    for (int k=0; k<=4 ; k++)
    {
        highScores[k].gameTime = (struct GameTime*)malloc(sizeof(struct GameTime));
        highScores[k].gameTime->min = 0;
        highScores[k].gameTime->sec = 0;
    }

    readRecords(highScores);


    char choice = toupper(getchar());

    if (choice == 'Q')
    {
        exit(1);
    }
    else if (choice == 'E')
    {
        showScores(highScores);

    }
    else if (choice == 'S')
    {
        struct Player player;
        registerPlayer(&player);

        struct List *list = (struct List*) malloc(sizeof(struct List));
        list->first = NULL;
        list->size = 0;
        readQuestions(list);

        clock_t startTime = measureTime();

        int money[16]= {0, 5000, 10000, 25000, 50000, 100000, 200000, 300000,
                        500000, 800000, 1500000, 3000000, 5000000, 10000000, 20000000, 40000000
                       };
        int i=0;

        struct Question *iterator = list->first;
        bool isAnswerRight = true;
        while (isAnswerRight)
        {
            for (int i = 0; i < (rand() % 1000); i++) //Move the iterator with a random number to avoid having the same questions
                iterator = iterator->next;
            switch (player.difficulty)
            {

            case 1:
                if (iterator->level <= 5)
                {
                    printf("%d Ft-os kerdes\n\n",money[i+1]);
                    isAnswerRight = askQuestionFromPlayer(iterator, &player);
                    player.prize=money[i];
                    i++;
                }
                break;
            case 2:
                if (5 < iterator->level && iterator->level <= 10)
                {
                    printf("%d Ft-os kerdes\n\n",money[i+1]);
                    isAnswerRight = askQuestionFromPlayer(iterator, &player);
                    player.prize=money[i];
                    i++;
                }
                break;
            case 3:
                if (10 < iterator->level)
                {
                    printf("%d Ft-os kerdes\n\n",money[i+1]);
                    isAnswerRight = askQuestionFromPlayer(iterator, &player);
                    player.prize=money[i];
                    i++;
                }
                break;
            default:
                perror("Invalid player level");
            }
        }
        clock_t finishTime = measureTime();
        int elapsedTime = difftime(finishTime, startTime);
        setPlayTime(elapsedTime, &player);
        printf("####GAME OVER####\n");

        int z=4;
        struct Player temp;


        if (player.prize>highScores[z].prize)
        {
            highScores[z]=player;
            while (highScores[z].prize>highScores[z-1].prize)
            {
                temp=highScores[z-1];
                highScores[z-1]=highScores[z];
                highScores[z]=temp;
                z--;
            }
        }

        writeInFile(highScores);
        showScores(highScores);
        free(player.gameTime);
    }
    for (int i = 0; i < 5; i++)
    {
        free(highScores[i].gameTime);
    }

    return 0;
}

