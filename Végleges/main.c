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
#include "Fileio.h"
#include "other.h"

//Main
int main(){
    showMenu();

    srand(time(0));

     struct List* list;

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

        list = (struct List*) malloc(sizeof(struct List));
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
        printf("Your prize:%d\nYour time:%d:%d\n", player.prize,player.gameTime->min,player.gameTime->sec);

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
        freeList(list->first->next, list->first);
        free(list->first);
        free(list);

    }

    for (int i = 0; i <=4; i++)
    {
        free(highScores[i].gameTime);
    }







    return 0;
}

