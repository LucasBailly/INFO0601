

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "level.h"

#define N 10	//taille de la table d'@
typedef struct tableAdresse{
	off_t posDebut;
	off_t tableA[N];
	int numtableA[N];
}tableAdresse_t;

tableAdresse_t creerTableAdresse(off_t posDebut);
int ecrireTableAdresse(char * fich, tableAdresse_t table);
tableAdresse_t lireTableAdresse(char * fich, off_t pos);
void afficherTableAdresse(tableAdresse_t tableAd);
void ajoutEntree(char * fich, level_t level);
int supprimerEntree(char * fich, int num);
level_t chargerEntree(char * fich, int num);

