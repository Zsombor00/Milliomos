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
//#include <string.h>

//Structures definitions

//Ehelyett nem tudsz time.h-t hasznalni?
typedef struct GameTime {
  int hour;
  int min;
  int sec;
};

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
  const char name[15]; //Neve (max 15 karakter).
  int difficulty; // A v�lasztott neh�zs�g.
  int prize; //Nyerem�ny Ft-ban.
  struct GameTime elapsed_time; //J�t�kid�.
  struct Player* next_player;
};


//Function definitions

struct GameTime idofgv(int masodpercben) //M�sodpercet id�form�tumba(�ra, perc, m�sodperc) �tv�lt� f�ggv�ny.
{
  struct GameTime jatek;
  int marad;

  jatek.hour = masodpercben / 3600;
  marad = masodpercben % 3600;
  jatek.min = marad / 60;
  jatek.sec = marad % 60;

  return jatek;

}

void show_record() {

}

void readQuestions(struct List *list) {
  printf("Reading questions...");

  FILE *filepointer = fopen("/Users/kornelkotan/workspaces/eclipse-cpp-ws/millionaire/src/loim.txt", "r");
  if (filepointer == NULL) {
    perror("Error");
  } else {
    while (!feof(filepointer)) {

      struct Question *q = (struct Question*) malloc(sizeof(struct Question));

      fscanf(filepointer, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c", &q->difficulty, &q->question, &q->anwserA, &q->anwserB, &q->anwserC, &q->anwserD,
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
}
//Main

int main() {
  menu: printf("________________________________________\n");
  printf("       LEGYEN ON IS MILLIOMOS!\n");
  printf("________________________________________\n");
  printf("________________________________________\n");
  printf(" -> Nyomjon S-t a jatek inditasahoz\n");
  printf(" -> Nyomjon E-t az eredmenyek megtekintesehez\n");
  printf(" -> Nyomjon Q-t a kilepeshez\n");
  printf("________________________________________\n");

  char choice = toupper(getchar());

  if (choice == 'Q') {
    exit(1);
  } else if (choice == 'E') {
    show_record();
    goto menu;
  } else if (choice == 'S') {
    int difficulty;
    struct Player player;

    printf("Nev:");
    scanf("%s", &player.name);

    printf("Valasszon nehezseget:\nKonnyuk(1)      Kozepes(2)     Nehez(3)\n");
    scanf("%d", &player.difficulty);

    struct List *list = malloc(sizeof(struct List));

    readQuestions(list);

//    Talald ki h a nehezeseg mert nem jo vszeg vmi a pointerrel
//    Egy listaban tarolod oket aztan majd mikor hasznalod akkor csekkolod h mekkora a difficulty vmi confitionnel if(&list->last->difficulty > 10)...
//    Assszem amugyis majd rendezned kell a listat
    printf("Lista merete: %d\n", list->size);
    printf("Elso elem: kerdes: %s, valasz: %s, nehezseg: %d \n", &list->first->question, &list->first->rightanwser, &list->first->difficulty);

    printf("Masodik elem: kerdes: %s, valasz: %s, nehezseg: %d \n", &list->first->next->question, &list->first->next->rightanwser,
        &list->first->next->difficulty);

    printf("Uccso elem: kerdes: %s, valasz: %s, nehezseg: %d \n", &list->last->question, &list->last->rightanwser, &list->last->difficulty);

  }
  return 0;

}

