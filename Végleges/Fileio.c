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
#include "Fileio.h"
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





