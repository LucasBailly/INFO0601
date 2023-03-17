#include "case.h"
#include <stdlib.h>

typedef struct level
{
    int num ;
    case_t matrice_cases[20][60];
} level_t;

void initialiser_level(level_t * level, int num);

void afficher_level(level_t * level);