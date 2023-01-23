#include "level.h"

void initialiser_level(level_t * level, int num){
    int i,j;
    level->num = num;
    for(i=0 ; i<20 ; i++)
		for(j=0 ; j<60 ; j++){
			initialiser_case(&level->matrice_cases[i][j]);
		}
}