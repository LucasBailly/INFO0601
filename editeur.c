#include <stdlib.h>
#include <locale.h>
#include "functions.h"
#include "window.h"
#include "colors.h"
#include "tableAdresse.h"

#define LONGUEUR 20
#define LARGEUR 60
#define POSY_DELETE 0
#define POSY_BLOCK 1
#define POSY_LADDER 2
#define POSY_TRAP 3
#define POSY_GATE 4
#define POSY_KEY 5
#define POSY_DOOR 6
#define POSY_EXIT 7
#define POSY_START 8
#define POSY_ROBOT 9
#define POSY_PROBE 10
#define POSY_LIFE 11
#define POSY_BOMB 12
#define POSY_LEVEL 16
#define POSY_DELETE_LEVEL 18
#define POSX_MAGENTA 8
#define POSX_GREEN 9
#define POSX_YELLOW 10
#define POSX_BLUE 11 

level_t chargerLevel(int num_level, window_t * w_level){
	int i = 0, j = 0;
	level_t level;
	if (access("fichTest.bin", F_OK) == 0){
		level = chargerEntree("fichTest.bin", num_level);
		
		for(i=0; i<LONGUEUR; i++){
			for(j=0; j<LARGEUR; j++){
				window_mvaddch_col(w_level, i, j, level.matrice_cases[i][j].color, level.matrice_cases[i][j].ch);
			}
		}
		
	}else{
		for(i=0; i<LONGUEUR; i++){
			for(j=0; j<LARGEUR; j++){
				window_mvaddch_col(w_level, i, j, WHITE, ' ');
			}
		}
		
	}
	return level;
}


int main() {
	// ncurses initialisation
	setlocale(LC_ALL, "");
  	ncurses_init();

	//Declarations
	char ch_1='0', ch_2='1';
	int i, j, gate_tmp=GATE_MAGENTA, key_tmp=KEY_MAGENTA, couleur_1=WHITE, couleur_2=WHITE, posY_tools=0, posX_tools=0, posX_gates=8, ch, num_door=1, num_level=1, posX, posY;
	char* tools[13] = {"Delete", "Block", "Ladder", "Trap", "Gate", "Key", "Door", "Exit", "Start", "Robot", "Probe", "Life", "Bomb"};
	int gates_colors[4] = {FD_MAGENTA, FD_GREEN, FD_YELLOW, FD_BLUE};
	level_t level;
	chtype tab_probe[2][3] = {{ ACS_LRCORNER, ACS_HLINE,  ACS_LLCORNER}, {ACS_RTEE, ACS_HLINE, ACS_LTEE }};
	chtype tab_robot[4][3] = {{ACS_URCORNER, ACS_BTEE, ACS_ULCORNER}, {ACS_HLINE, ACS_PLUS, ACS_HLINE}, {ACS_LRCORNER, ACS_TTEE, ACS_LLCORNER}, {ACS_URCORNER, ACS_BTEE, ACS_ULCORNER}};

	window_t * w_level = window_create(0, 0, LARGEUR+2, LONGUEUR+2, "Level", false);
	window_t * w_tools = window_create(62, 0, 15, 22, "Tools", false);
	window_t * w_information = window_create(0, 22, 77, 5, "Informations", false);


	
	// int fd1;
	
	if (access("fichTest.bin", F_OK) == 0) {
		level = chargerEntree("fichTest.bin", 1);
    } else {
        initialiser_level(&level, 1);
    }
	
	
	// Colors initialisation and palette definition
  	ncurses_colors();
	palette();
	
	for(i=0; i<LONGUEUR; i++){
		for(j=0; j<LARGEUR; j++){
			window_mvaddch_col(w_level, i, j, level.matrice_cases[i][j].color, level.matrice_cases[i][j].ch);
		}
	}
	window_refresh(w_level);
	//Mouse initialisation
	ncurses_init_mouse();

	window_mvprintw_col(w_tools, 0, 2, WHITE, tools[0]);
	for(i=1 ; i<13 ; i++)
		window_mvprintw_col(w_tools, i, 2, RED, tools[i]);

	window_mvprintw_col(w_tools, 14, 0, WHITE, "Current level");
	window_mvprintw_col(w_tools, 16, 3, WHITE, "< 001 >") ;
	window_mvprintw_col(w_tools, POSY_DELETE_LEVEL, 3, RED, "DELETE") ;
	window_mvprintw_col(w_tools, 0, 0, WHITE, ">") ;
	for(i=0;i<4;i++)
		window_mvprintw_col(w_tools, POSY_GATE, i+posX_gates, gates_colors[i], " ") ;
	window_mvprintw_col(w_tools, POSY_KEY, posX_gates, WHITE, "^") ;
	window_mvprintw_col(w_tools, POSY_DOOR, 8, WHITE, "<01>");
	window_refresh(w_tools);

	
	window_refresh(w_level);

	while((ch = getch()) != KEY_F(2)) {
		window_mvprintw_col(w_tools, posY_tools, posX_tools, WHITE, " ") ;
    
    // New position
    switch(ch) {
		case 115:
			
			supprimerEntree("fichTest.bin",num_level);
			level.num = num_level;
			
			ajoutEntree("fichTest.bin",level);
			break;
			
		case 114:
			if(posY_tools == POSY_DELETE_LEVEL){
				supprimerEntree("fichTest.bin",num_level);
				
				for(i=0; i<LONGUEUR; i++){
					for(j=0; j<LARGEUR; j++){
						window_mvaddch_col(w_level, i, j, WHITE, ' ');
					}
				}
				
			}
			
				
			break;
			
		case KEY_LEFT:
			if(posY_tools == POSY_GATE){
				if(posX_gates>8){
					window_mvaddch_col(w_tools, POSY_KEY, posX_gates, WHITE, ' ') ;
					posX_gates--;
					window_mvaddch_col(w_tools, POSY_KEY, posX_gates, WHITE, '^') ;
				}
			}
			if(posY_tools == POSY_DOOR){
				if(num_door>1){
					num_door--;
					if(num_door<10)
						window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "0%d",num_door);
					else
						window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "%d",num_door);
				}
			}
			
			
			
			
			
			if(posY_tools == POSY_LEVEL){
				if(num_level>1){
					num_level--;
					if(num_level<10)
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "00%d",num_level);
					else if(num_level<100)
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "0%d",num_level);
					else
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "%d",num_level);
				}
				//Chargemnt du prochain niveau sauvegardé si il y en a un
				level =  chargerLevel(num_level, w_level);
				
			}
			break;

     	case KEY_RIGHT:
			if(posY_tools == POSY_GATE){
				if(posX_gates<11){
					window_mvaddch_col(w_tools, POSY_KEY, posX_gates, WHITE, ' ') ;
					posX_gates++;
					window_mvaddch_col(w_tools, POSY_KEY, posX_gates, WHITE, '^') ;
				}
			}
			if(posY_tools == POSY_DOOR){
				if(num_door<99){
					num_door++;
					if(num_door<10)
						window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "0%d",num_door);
					else
						window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "%d",num_door);
				}
			}
			// here
			
			
			if(posY_tools == POSY_LEVEL){
				if(num_level<999){
					num_level++;
					if(num_level<10)
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "00%d",num_level);
					else if(num_level<100)
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "0%d",num_level);
					else
						window_mvprintw_col(w_tools, POSY_LEVEL, 5, WHITE, "%d",num_level);
				}
				//Chargemnt du prochain niveau sauvegardé si il y en a un
				level = chargerLevel(num_level, w_level);
			
			}
			break;

		case KEY_UP:
			if(posY_tools > 0){			
				if(posY_tools==POSY_DELETE_LEVEL){			
					posY_tools-=2;			
				}
				else{
					if(posY_tools==POSY_LEVEL){
						posY_tools-=4;
						window_mvprintw_col(w_tools, posY_tools, 2, WHITE, tools[posY_tools]);
					}
					else{ 
						window_mvprintw_col(w_tools, posY_tools, 2, RED, tools[posY_tools]);
						posY_tools--;
						window_mvprintw_col(w_tools, posY_tools, 2, WHITE, tools[posY_tools]);
					}
				}
			}
			break;

		case KEY_DOWN:
			if(posY_tools < POSY_DELETE_LEVEL){		
				if(posY_tools<POSY_BOMB){
					window_mvprintw_col(w_tools, posY_tools, 2, RED, tools[posY_tools]);
					posY_tools++;
					window_mvprintw_col(w_tools, posY_tools, 2, WHITE, tools[posY_tools]);
				}
				else{ 
					if(posY_tools==POSY_BOMB){
						window_mvprintw_col(w_tools, posY_tools, 2, RED, tools[posY_tools]);
						posY_tools+=4;
					}
					else
					 	posY_tools+=2;
				}	
			}
			break;
		
		case KEY_MOUSE:
			
			if(mouse_getpos(&posX, &posY) == OK) {
				window_mvprintw_col(w_information, 1, 1, WHITE, "pos(%d,%d)", posX, posY);
				if(window_isin(w_level, posX, posY)){
					if(posY_tools == POSY_DELETE){
						update_case(&level.matrice_cases[posY-1][posX-1], WHITE,-1 , ' ');
						window_mvaddch_col(w_level, posY-1, posX-1, WHITE, ' ');
					}
					if(level.matrice_cases[posY-1][posX-1].color == WHITE && level.matrice_cases[posY-1][posX-1].ch == ' '){
						switch(posY_tools){
							case POSY_BLOCK :
								update_case(&level.matrice_cases[posY-1][posX-1], FD_CYAN,BLOCK , ' ');
								window_mvaddch_col(w_level, posY-1, posX-1, FD_CYAN, ' ');
								break;
							case POSY_TRAP :
								update_case(&level.matrice_cases[posY-1][posX-1], FD_CYAN,TRAP , '#');
								window_mvaddch_col(w_level, posY-1, posX-1, FD_CYAN, '#');
								break;
							case POSY_LIFE :
								update_case(&level.matrice_cases[posY-1][posX-1], RED,LIFE , 'V');
								window_mvaddch_col(w_level, posY-1, posX-1, RED, 'V');
								break;
							case POSY_BOMB :
								update_case(&level.matrice_cases[posY-1][posX-1], WHITE,BOMB , 'o');
								window_mvaddch_col(w_level, posY-1, posX-1, WHITE, 'o');
								break;
							case POSY_LADDER:
								//on vérifie qu'il y a la place pour placer l'échelle
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) 
								&& level.matrice_cases[posY-1][posX-2].ch==' ' && level.matrice_cases[posY-1][posX-2].color == WHITE
								&& level.matrice_cases[posY-1][posX-1].ch==' ' && level.matrice_cases[posY-1][posX-1].color == WHITE
								&& level.matrice_cases[posY-1][posX].ch==' ' && level.matrice_cases[posY-1][posX].color == WHITE){
									update_case(&level.matrice_cases[posY-1][posX-2], YELLOW,LADDER , ACS_LTEE);
									update_case(&level.matrice_cases[posY-1][posX-1], YELLOW,LADDER , ACS_HLINE);
									update_case(&level.matrice_cases[posY-1][posX], YELLOW,LADDER , ACS_RTEE);
									window_mvaddch_col(w_level, posY-1, posX-2, YELLOW, ACS_LTEE);
									window_mvaddch_col(w_level, posY-1, posX-1, YELLOW, ACS_HLINE);
									window_mvaddch_col(w_level, posY-1, posX, YELLOW, ACS_RTEE);
								}
								break;
							case POSY_START:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<4 ; i++)
										for(j=0 ; j<3 ; j++){
											update_case(&level.matrice_cases[posY-1-i][posX-j], FD_MAGENTA,START , ' ');
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_MAGENTA, ' ');
										}
								}
								break;
							case POSY_EXIT:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<4 ; i++)
										for(j=0 ; j<3 ; j++){
											update_case(&level.matrice_cases[posY-1-i][posX-j], FD_YELLOW,EXIT , ' ');
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_YELLOW, ' ');
										}
								}
								break;
							case POSY_DOOR:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<3 ; i++)
										for(j=0 ; j<3 ; j++){
											update_case(&level.matrice_cases[posY-1-i][posX-j], FD_GREEN,DOOR+num_door , ' ');
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_GREEN, ' ');
										}
									if(num_door<10){
										ch_1 = '0';
										ch_2 = num_door+'0';
									}
									else{
										ch_1 = ((int)num_door/10)+'0';
										ch_2 = (num_door%10)+'0';	
									}
									update_case(&level.matrice_cases[posY-4][posX-2], WHITE ,DOOR+num_door , ch_1);
									update_case(&level.matrice_cases[posY-4][posX-1], WHITE,DOOR+num_door , ch_2);
									update_case(&level.matrice_cases[posY-4][posX], WHITE,DOOR+num_door , ' ');
									window_mvaddch_col(w_level, posY-4, posX-2, WHITE, ch_1);
									window_mvaddch_col(w_level, posY-4, posX-1, WHITE, ch_2);
									window_mvaddch_col(w_level, posY-4, posX, FD_GREEN, ' ');
								}
								break;	
							case POSY_GATE :
								switch(posX_gates){
									case POSX_MAGENTA :
										couleur_1 = MAGENTA;
										gate_tmp = GATE_MAGENTA;
										break;
									case POSX_GREEN :
										couleur_1 = GREEN;
										gate_tmp = GATE_GREEN;
										break;
									case POSX_YELLOW :
										couleur_1 = YELLOW;
										gate_tmp = GATE_YELLOW;
										break;
									case POSX_BLUE :
										couleur_1 = BLUE;
										gate_tmp = GATE_BLUE;
										break;	
								}
								update_case(&level.matrice_cases[posY-1][posX-1], couleur_1,gate_tmp , ACS_PLUS);
								window_mvaddch_col(w_level, posY-1, posX-1, couleur_1, ACS_PLUS);
								break;
							case POSY_KEY :
								if(window_isin(w_level, posX, posY-1)){
									switch(posX_gates){
										case POSX_MAGENTA :
											couleur_1 = MAGENTA;
											couleur_2 = FD_MAGENTA;
											key_tmp = KEY_MAGENTA;
											break;
										case POSX_GREEN :
											couleur_1 = GREEN;
											couleur_2 = FD_GREEN;
											key_tmp	= KEY_GREEN;
											break;
										case POSX_YELLOW :
											couleur_1 = YELLOW;
											couleur_2 = FD_YELLOW;
											key_tmp = KEY_YELLOW;
											break;
										case POSX_BLUE :
											couleur_1 = BLUE;
											couleur_2 = FD_BLUE;
											key_tmp = KEY_BLUE;
											break;	
									}
									update_case(&level.matrice_cases[posY-1][posX-1], couleur_1,key_tmp , ACS_LLCORNER);
									update_case(&level.matrice_cases[posY-2][posX-1], couleur_2, key_tmp, ' ');
									window_mvaddch_col(w_level, posY-1, posX-1, couleur_1, ACS_LLCORNER);
									window_mvaddch_col(w_level, posY-2, posX-1, couleur_2, ' ');								
								}
								break;
							case POSY_PROBE :
								if(window_isin(w_level, posX-1, posY-1) && window_isin(w_level, posX+1, posY-1)){
									for(i=0 ; i<2 ; i++)
										for(j=0 ; j<3 ; j++){
											update_case(&level.matrice_cases[posY-1-i][posX-j], WHITE, PROBE, tab_probe[i][j]);
											window_mvaddch_col(w_level, posY-1-i, posX-j, WHITE, tab_probe[i][j]);
										}
								}
								break;
							case POSY_ROBOT :
								if(window_isin(w_level, posX-1, posY-3) && window_isin(w_level, posX+1, posY-3)){
									for(i=0 ; i<4 ; i++)
										for(j=0 ; j<3 ; j++){
											update_case(&level.matrice_cases[posY-1-i][posX-j], WHITE, ROBOT, tab_robot[i][j]);
											window_mvaddch_col(w_level, posY-1-i, posX-j, WHITE, tab_robot[i][j]);
										}
								}
								break;
						}
					}
				}
			}
		}

		window_mvaddch_col(w_tools, posY_tools, posX_tools, WHITE, '>') ;
		window_refresh(w_tools);
		window_refresh(w_information);
		window_refresh(w_level);
  	}

	// Stop ncurses
  	ncurses_stop();

	window_delete(&w_level);
	window_delete(&w_tools);
	window_delete(&w_information);

	afficher_level(&level);
  	return EXIT_SUCCESS;
}
