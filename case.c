#include "case.h"
#include "colors.h"

void initialiser_case(case_t *c){
    c->color = WHITE;
    c->ch = ' ';
}
void update_case(case_t *c, int couleur, chtype ch){
    c->color = couleur;
    c->ch = ch;
}
void afficher_case(case_t *c){
    printf("(%d,%c) ; ", c->color, c->ch);
}