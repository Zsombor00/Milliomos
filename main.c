#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*int k;
    int stopwatch_start=time(0);
    scanf("%d",&k);
    int stopwatch_end=time(0);
    int gametime=stopwatch_end-stopwatch_start;
    ido elteltido=idofgv(gametime);
    printf("%d:%d:%d",elteltido.hour, elteltido.min, elteltido.sec );*/ //Stopper a játékidõ méréséhez.

typedef struct gameTime
{
    int hour;
    int min;
    int sec;
} gameTime;

gameTime idofgv (int masodpercben) //Másodpercet idõformátumba(óra, perc, másodperc) átváltó függvény.
{
    gameTime jatek;
    int marad;

    jatek.hour=masodpercben/3600;
    marad=masodpercben%3600;
    jatek.min=marad/60;
    jatek.sec=marad%60;

    return jatek;

}



typedef struct player_elem //A játékosok "tulajdonságai".
{
    const char name[15]; //Neve (max 15 karakter).
    int difficulty; // A választott nehézség.
    int prize; //Nyeremény Ft-ban.
    gameTime elapsed_time;//Játékidõ.
    struct player_elem* next_player;

} player_elem;

typedef struct question
{
    int difficulty;//Kérdés nehézsége.
    char question[200];//Kérdés.
    char anwserA[200];//A válasz.
    char anwserB[200];//B válasz.
    char anwserC[200];//C válasz.
    char anwserD[200];//D válasz.
    char rightanwser;//Helyes válasz betûje.
    struct question *next_question;
} question;

void show_record()
{

}

int read(question *questions, int counter, FILE *fp) //Egy sort beolvas a fileból és felbontja (ciklusba kellene rakni,de arra még nem találtam megoldást, hogy pontosan milyenbe.
{
    int i;
    i=fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c",&questions[counter].difficulty,&questions[counter].question,
             &questions[counter].anwserA,&questions[counter].anwserB,&questions[counter].anwserC,
             &questions[counter].anwserD,&questions[counter].rightanwser);
    return i;
}



int main()
{
    printf("________________________________________\n");
    printf("       LEGYEN ON IS MILLIOMOS!\n");
    printf("________________________________________\n");
    printf("________________________________________\n");
    printf(" -> Nyomjon S-t a jatek inditasahoz\n");
    printf(" -> Nyomjon E-t az eredmenyek megtekintesehez\n");
    printf(" -> Nyomjon Q-t a kilepeshez\n");
    printf("________________________________________\n");

    char choice;
    scanf ("%c",&choice);
    switch (choice) {
    case 'Q':
    case 'q':
    exit(1);
    break;

    case 'E':
    case 'e':
    show_record();
    break;

   case 'S':
   case 's':

       printf("\n");

        int difficulty;
        player_elem plyr;

        printf("Nev:");
        scanf("%s", &plyr.name);

        printf("Valasszon nehezseget:\nKonnyu(1)      Kozepes(2)     Nehez(3)\n");
        scanf("%d",&plyr.difficulty);

        FILE *filepointer=fopen("loim.txt","r");
        int row=0;
        question questions[2000];


        //read(questions,row,filepointer);

        while (!feof(filepointer))
           {
               read(questions,row,filepointer);


        printf("%s\n",questions[row].anwserC);
         row++;



               if (1<=difficulty<=5)
               {
                   read(questions,row,filepointer);
               }

               else if (6<=difficulty<=10)

               {
                   read(questions,row,filepointer);
               }

               else if (11<=difficulty<=15)
               {
                   read(questions,row,filepointer);
               }


           }

    break;
    }
    return 0;

}










