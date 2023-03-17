#include "tableAdresse.h"

tableAdresse_t creerTableAdresse(off_t posDebut){
	int i;
	tableAdresse_t tabtmp;
	tabtmp.posDebut = posDebut;
	for(i=0;i<N;i++){
		tabtmp.tableA[i] = 0;
		tabtmp.numtableA[i] = 0;
	}

	return tabtmp;
}

int ecrireTableAdresse(char * fich, tableAdresse_t table){
	int i, fd1;
	if((fd1 = open(fich, O_RDWR|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR)) == -1) {
		if(errno == EEXIST){
			// perror("le fichier existe deja");
			if((fd1 = open(fich, O_RDWR, S_IRUSR|S_IWUSR)) == -1){
				perror("Error opening file");
				exit(EXIT_FAILURE);
			}
		}else{
			perror("Error creating file 'toto.bin'");
			exit(EXIT_FAILURE);
		}
    }
	
	
	
	
	
	lseek(fd1, table.posDebut, SEEK_SET);
	for(i=0;i<N;i++){
		if(write(fd1, &table.tableA[i] , sizeof(off_t)) == -1) {
			perror("Error saving off_t");
			exit(EXIT_FAILURE);
		}
		if(write(fd1, &table.numtableA[i] , sizeof(int)) == -1) {
			perror("Error saving int");
			exit(EXIT_FAILURE);
		}
	}
	
	if(close(fd1) == -1) {
        perror("Error closing file (2)");
        exit(EXIT_FAILURE);
    }
	
	return 0;
}

tableAdresse_t lireTableAdresse(char * fich, off_t pos){
	int i, fd1;
	// off_t pos2;
	tableAdresse_t tableAdresse1;
	tableAdresse1 = creerTableAdresse(pos);
	
	
	if((fd1 = open(fich, O_RDONLY, S_IRUSR|S_IWUSR)) == -1) {
        perror("Error opening file ");
        exit(EXIT_FAILURE);
    }
	
	lseek(fd1, pos, SEEK_SET);
	// printf("position de lecture : %ld\n",pos2);
	
	for(i=0;i<N;i++){
		if(read(fd1, &tableAdresse1.tableA[i] , sizeof(off_t)) == -1) {
			perror("Error saving off_t");
			exit(EXIT_FAILURE);
		}
		if(read(fd1, &tableAdresse1.numtableA[i] , sizeof(int)) == -1) {
			perror("Error saving off_t");
			exit(EXIT_FAILURE);
		}
	}
	
	if(close(fd1) == -1) {
        perror("Error closing file (2)");
        exit(EXIT_FAILURE);
    }
	
	return tableAdresse1;
}

void afficherTableAdresse(tableAdresse_t tableAd){
	int i;
	printf("Position Debut de la table : %ld\n",tableAd.posDebut);
	for(i=0;i<N;i++){
		printf("position : %ld\nnumero : %d\n ",tableAd.tableA[i], tableAd.numtableA[i]);
	}
	printf("\n");
}

void ajoutEntree(char * fich, level_t level){
	int fd1;
	int numero;
	off_t pos, posEntree, posnewtable;
	tableAdresse_t tableAdresseInit;
	tableAdresse_t tableAdresseNew;
	int cond = 1, compteur = 0;
	int i = 0, j = 0;
	
	tableAdresseInit = creerTableAdresse(0);
	
	if((fd1 = open(fich, O_RDWR|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR)) == -1) {
		if(errno == EEXIST){
			// perror("le fichier existe deja");
			if((fd1 = open(fich, O_RDWR, S_IRUSR|S_IWUSR)) == -1){
				perror("Error opening file");
				exit(EXIT_FAILURE);
			}
		}else{
			perror("Error creating file");
			exit(EXIT_FAILURE);
		}
    }
	
	pos = lseek(fd1, 0, SEEK_SET);
	//verification qu'il ai bien une table d'adresse déjà présente
	if(read(fd1, &pos , sizeof(off_t)) == -1) {
		perror("Error reading off_t");
		exit(EXIT_FAILURE);
	}
	if(pos == 0){
		ecrireTableAdresse(fich,tableAdresseInit);
	}
	
	
	
	
	lseek(fd1,0,SEEK_SET);
	while(cond){
		if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		if(read(fd1, &numero , sizeof(int)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		// printf("position de la table pour mettre l'entrée : %ld\n",posEntree);
		//recherche d'une place libre pour l'entrée
		if(posEntree == 0 || numero == 0){
			pos = lseek(fd1, -1*(sizeof(off_t)+sizeof(int)), SEEK_CUR);
			if(posEntree == 0){
				posEntree = lseek(fd1, 0, SEEK_END);
			}else{
				lseek(fd1, posEntree, SEEK_SET);
			}
			
			//ecriture du level
			if(write(fd1, &level.num, sizeof(int)) == -1) {
				perror("Error saving size");
				perror("wut");
				exit(EXIT_FAILURE);
			}    
			// printf("level num == %d",level.num);
			for(i=0 ; i<20 ; i++){
				for(j=0 ; j<60 ; j++){
					if(write(fd1, &level.matrice_cases[i][j].color, sizeof(int)) == -1) {
						perror("Error saving string");
						exit(EXIT_FAILURE);
					}
					
					if(write(fd1, &level.matrice_cases[i][j].element, sizeof(int)) == -1) {
						perror("Error saving string");
						exit(EXIT_FAILURE);
					}
					
					if(write(fd1, &level.matrice_cases[i][j].ch, sizeof(chtype)) == -1) {
						perror("Error saving string");
						exit(EXIT_FAILURE);
					}
				}
			}
			
			
			
			
			lseek(fd1, pos, SEEK_SET);
			if(write(fd1, &posEntree, sizeof(off_t)) == -1) {
				perror("Error saving size");
				exit(EXIT_FAILURE);
			} 
			if(write(fd1, &level.num, sizeof(int)) == -1) {
				perror("Error saving size");
				exit(EXIT_FAILURE);
			}  
			cond = 0;
		}
	
		compteur++;
		//si la dernière case de la table d'@ est vide alors on recrée une table d'@ à la fin du fichier, sinon on passe à la prochaine table d'@.
		if(compteur == N-1){
			if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
				perror("Error saving off_t");
				exit(EXIT_FAILURE);
			}
			if(read(fd1, &numero , sizeof(int)) == -1) {
				perror("Error reading int");
				exit(EXIT_FAILURE);
			}
			pos = lseek(fd1, -1*(sizeof(off_t)+sizeof(int)), SEEK_CUR);
			if(posEntree == 0){
				// printf("AJout d'une table d'adressage\n");
				
				// exit(EXIT_FAILURE);
				posnewtable = lseek(fd1, 0, SEEK_END);
				tableAdresseNew = creerTableAdresse(posnewtable);
				
				ecrireTableAdresse(fich,tableAdresseNew);
				
				
				lseek(fd1, pos, SEEK_SET);
				if(write(fd1, &posnewtable, sizeof(off_t)) == -1) {
					perror("Error saving size");
					exit(EXIT_FAILURE);
				} 
				 
				compteur = 0;
				lseek(fd1,posnewtable,SEEK_SET);
			}else{
				lseek(fd1,posEntree,SEEK_SET);
				compteur = 0;
			}
		}
		
	}
	
	
	
	
	
	
	if(close(fd1) == -1) {
        perror("Error closing file (2)");
        exit(EXIT_FAILURE);
    }
}

int supprimerEntree(char * fich, int num){
	int fd1;
	int numero;
	off_t posEntree ;
	int tmp = 0;
	int cond = 1, compteur = 0;
	
	
	if (access(fich, F_OK) == 0) {
        if((fd1 = open(fich, O_RDWR, S_IRUSR|S_IWUSR)) == -1){
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
    } else {
        return -1;
    }
	
	
	
	lseek(fd1,0,SEEK_SET);
	while(cond){
		if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		if(read(fd1, &numero , sizeof(int)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		//verif si le numero == num, alors le num passe à 0 pour indiquer que l'entree a été supprimé
		if(numero == num){
			lseek(fd1, -1*(sizeof(off_t)+sizeof(int)), SEEK_CUR);
			if(write(fd1, &posEntree, sizeof(off_t)) == -1) {
				perror("Error saving size");
				exit(EXIT_FAILURE);
			} 
			
			if(write(fd1, &tmp, sizeof(int)) == -1) {
				perror("Error saving size");
				exit(EXIT_FAILURE);
			}  
			cond = 0;
		}
		
		
		
	
		compteur++;
		
		if(compteur == N-1){
			if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
				perror("Error saving off_t");
				exit(EXIT_FAILURE);
			}
			if(read(fd1, &numero , sizeof(int)) == -1) {
				perror("Error reading int");
				exit(EXIT_FAILURE);
			}
			lseek(fd1, -1*(sizeof(off_t)+sizeof(int)), SEEK_CUR);
			
			if(posEntree == 0){
				// printf("Fin du fichier, aucune entree avec ce numero\n");
				
				cond = 0;
			}else{
				lseek(fd1,posEntree,SEEK_SET);
				compteur = 0;
			}
		}
		
	}
	
	
	if(close(fd1) == -1) {
        perror("Error closing file (2)");
        exit(EXIT_FAILURE);
    }
	return 0;
}

level_t chargerEntree(char * fich, int num){
	int fd1;
	int numero;
	off_t posEntree ;
	level_t level;
	int i = 0, j = 0;
	int cond = 1, compteur = 0;
	
	if((fd1 = open(fich, O_RDWR, S_IRUSR|S_IWUSR)) == -1){
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	
	lseek(fd1,0,SEEK_SET);
	while(cond){
		if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		if(read(fd1, &numero , sizeof(int)) == -1) {
			perror("Error reading off_t");
			exit(EXIT_FAILURE);
		}
		//verif si le numero == num, alors on va à la position de l'entree
		if(numero == num){
			// printf("position : %ld\n", posEntree);
			lseek(fd1, posEntree, SEEK_SET);
			if(read(fd1, &numero , sizeof(int)) == -1) {
				perror("Error reading off_t");
				exit(EXIT_FAILURE);
			}
			// printf("num = %d\n", num);
			// printf("numero = %d\n", numero);
			level.num = numero;
			for(i=0 ; i<20 ; i++){
				for(j=0 ; j<60 ; j++){
					if(read(fd1, &level.matrice_cases[i][j].color , sizeof(int)) == -1) {
						perror("Error reading off_t");
						exit(EXIT_FAILURE);
					}
					
					if(read(fd1, &level.matrice_cases[i][j].element , sizeof(int)) == -1) {
						perror("Error reading off_t");
						exit(EXIT_FAILURE);
					}
					
					if(read(fd1, &level.matrice_cases[i][j].ch , sizeof(chtype)) == -1) {
						perror("Error reading off_t");
						exit(EXIT_FAILURE);
					}
					
				}
			}
			cond = 0;
		}
		
		
		
	
		compteur++;
		
		if(compteur == N-1){
			if(read(fd1, &posEntree , sizeof(off_t)) == -1) {
				perror("Error saving off_t");
				exit(EXIT_FAILURE);
			}
			if(read(fd1, &numero , sizeof(int)) == -1) {
				perror("Error reading int");
				exit(EXIT_FAILURE);
			}
			lseek(fd1, -1*(sizeof(off_t)+sizeof(int)), SEEK_CUR);
			
			if(posEntree == 0){
				// printf("Fin du fichier, aucune entree avec ce numero\n");
				initialiser_level(&level, num);
				cond = 0;
			}else{
				lseek(fd1,posEntree,SEEK_SET);
				compteur = 0;
			}
		}
		
	}
	
	
	if(close(fd1) == -1) {
        perror("Error closing file (2)");
        exit(EXIT_FAILURE);
    }
	
	return level;
}

