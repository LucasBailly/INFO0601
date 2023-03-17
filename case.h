#include <ncurses.h>
#include <stdlib.h>

#define BLOCK 1
#define LADDER 2
#define TRAP 3
#define GATE_MAGENTA 4
#define GATE_GREEN 5
#define GATE_YELLOW 6
#define GATE_BLUE 7
#define KEY_MAGENTA 8
#define KEY_GREEN 9
#define KEY_YELLOW 10
#define KEY_BLUE 11
#define DOOR 100 //ajouter le num de la porte à cette valeur
#define EXIT 12
#define START 13
#define ROBOT 14
#define PROBE 15
#define LIFE 16
#define BOMB 17

typedef struct{ //Pour être perfectionniste, on aurait pu utiliser 2 short à la place des deux int ici
	int color;
	int  element;
	chtype ch;
} case_t;

void initialiser_case(case_t *c);

void update_case(case_t *c, int couleur, int element, chtype ch);

void afficher_case(case_t *c);