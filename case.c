#include "case.h"
#include "colors.h"


void initialiser_case(case_t *c){
    c->color = WHITE;
    c->element = -1;
    c->ch = ' ';  
}
void update_case(case_t *c, int couleur, int element, chtype ch){
    c->color = couleur;
    c->element = element;
    c->ch = ch;
}
void afficher_case(case_t *c){
    switch(c->element){
        case BLOCK :
            printf("%14s","(BLOCK) ");
            break;

        case LADDER :
            printf("%14s","(LADDER) ");
            break;

        case TRAP :
            printf("%14s","(TRAP) ");
            break;
        
        case GATE_MAGENTA :
            printf("%14s","(GATE_M) ");
            break;
        
        case GATE_BLUE :
            printf("%14s","(GATE_B) ");
            break;

        case GATE_GREEN :
            printf("%14s","(GATE_G) ");
            break;
        
        case GATE_YELLOW :
            printf("%14s","(GATE_Y) ");
            break;
        
        case KEY_YELLOW :
            printf("%14s","(KEY_Y) ");
            break;

        case KEY_BLUE :
            printf("%14s","(KEY_B) ");
            break;

        case KEY_GREEN :
            printf("%14s","(KEY_G) ");
            break;

        case KEY_MAGENTA :
            printf("%14s","(KEY_M) ");
            break;
        
        case EXIT :
            printf("%14s","(EXIT) ");
            break;
        
        case START :
            printf("%14s","(START) ");
            break;
        
        case ROBOT :
            printf("%14s","(ROBOT) ");
            break;
        
        case PROBE :
            printf("%14s","(PROBE) ");
            break;
        
        case LIFE :
            printf("%14s","(LIFE) ");
            break;
        
        case BOMB :
            printf("%14s","(BOMB) ");
            break;
        
        case -1 :
            printf("%14s","(VIDE) ");
            break;

        default :
            //Gestion de la door
            printf("%14s","(DOOR) ");
            break;
    }
    
}