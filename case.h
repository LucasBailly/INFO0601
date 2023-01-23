#include <ncurses.h>
#include <stdlib.h>
typedef struct{
	int color;
	chtype ch;
} case_t;

void initialiser_case(case_t *c);

void update_case(case_t *c, int couleur, chtype ch);

void afficher_case(case_t *c);