#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include "functions.h"
#include "window.h"
#include "colors.h"

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

typedef struct {
	int color;
	chtype ch;
} case_t;

int main() {
	// ncurses initialisation
	setlocale(LC_ALL, "");
  	ncurses_init();

	//Declarations
	char ch_1='0', ch_2='1';
	int i, j, posY_tools=0, posX_tools=0, posX_gates=8, ch, num_door=1, num_level=1, posX, posY;
	char* tools[13] = {"Delete", "Block", "Ladder", "Trap", "Gate", "Key", "Door", "Exit", "Start", "Robot", "Probe", "Life", "Bomb"};
	int gates_colors[4] = {FD_MAGENTA, FD_GREEN, FD_YELLOW, FD_BLUE};
	case_t level_matrice[20][60];

	window_t * w_level = window_create(0, 0, 62, 22, "Level", false);
	window_t * w_tools = window_create(62, 0, 15, 22, "Tools", false);
	window_t * w_information = window_create(0, 22, 77, 5, "Informations", false);

	// Colors initialisation and palette definition
  	ncurses_colors();
	palette();

	//Mouse initialisation
	ncurses_init_mouse();
	
	for(i=0 ; i<20 ; i++)
		for(j=0 ; j<60 ; j++){
			level_matrice[i][j].ch=' ';
			level_matrice[i][j].color=WHITE;
		}

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

	window_mvaddch_col(w_level, 0, 0, FD_CYAN, ' ');
	window_refresh(w_level);

	while((ch = getch()) != KEY_F(2)) {
		window_mvprintw_col(w_tools, posY_tools, posX_tools, WHITE, " ") ;
    
    // New position
    switch(ch) {
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
						level_matrice[posY-1][posX-1].color = WHITE;
						level_matrice[posY-1][posX-1].ch = ' ';
						window_mvaddch_col(w_level, posY-1, posX-1, WHITE, ' ');
					}
					if(level_matrice[posY-1][posX-1].color == WHITE && level_matrice[posY-1][posX-1].ch == ' '){
						switch(posY_tools){
							case POSY_BLOCK :
								level_matrice[posY-1][posX-1].color = FD_CYAN;
								level_matrice[posY-1][posX-1].ch = ' ';
								window_mvaddch_col(w_level, posY-1, posX-1, FD_CYAN, ' ');
								break;
							case POSY_TRAP :
								level_matrice[posY-1][posX-1].color = FD_CYAN;
								level_matrice[posY-1][posX-1].ch = '#';
								window_mvaddch_col(w_level, posY-1, posX-1, FD_CYAN, '#');
								break;
							case POSY_LIFE :
								level_matrice[posY-1][posX-1].color = RED;
								level_matrice[posY-1][posX-1].ch = 'V';
								window_mvaddch_col(w_level, posY-1, posX-1, RED, 'V');
								break;
							case POSY_BOMB :
								level_matrice[posY-1][posX-1].color = WHITE;
								level_matrice[posY-1][posX-1].ch = 'O';
								window_mvaddch_col(w_level, posY-1, posX-1, WHITE, 'O');
								break;
							case POSY_LADDER:
								//on vérifie qu'il y a la place pour placer l'échelle
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) 
								&& level_matrice[posY-1][posX-2].ch==' ' && level_matrice[posY-1][posX-2].color == WHITE
								&& level_matrice[posY-1][posX-1].ch==' ' && level_matrice[posY-1][posX-1].color == WHITE
								&& level_matrice[posY-1][posX].ch==' ' && level_matrice[posY-1][posX].color == WHITE){
									level_matrice[posY-1][posX-2].color = YELLOW;
									level_matrice[posY-1][posX-2].ch = ACS_LTEE;
									level_matrice[posY-1][posX-1].color = YELLOW;
									level_matrice[posY-1][posX-1].ch = ACS_HLINE;
									level_matrice[posY-1][posX].color = YELLOW;
									level_matrice[posY-1][posX].ch = ACS_RTEE;
									window_mvaddch_col(w_level, posY-1, posX-2, YELLOW, ACS_LTEE);
									window_mvaddch_col(w_level, posY-1, posX-1, YELLOW, ACS_HLINE);
									window_mvaddch_col(w_level, posY-1, posX, YELLOW, ACS_RTEE);
								}
								break;
							case POSY_START:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<4 ; i++)
										for(j=0 ; j<3 ; j++){
											level_matrice[posY-1-i][posX-j].color = FD_MAGENTA;
											level_matrice[posY-1-i][posX-j].ch = ' ';
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_MAGENTA, ' ');
										}
								}
								break;
							case POSY_EXIT:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<4 ; i++)
										for(j=0 ; j<3 ; j++){
											level_matrice[posY-1-i][posX-j].color = FD_YELLOW;
											level_matrice[posY-1-i][posX-j].ch = ' ';
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_YELLOW, ' ');
										}
								}
								break;
							case POSY_DOOR:
								if(window_isin(w_level, posX-1, posY) && window_isin(w_level, posX+1, posY) && window_isin(w_level, posX, posY-3)){
									for(i=0 ; i<3 ; i++)
										for(j=0 ; j<3 ; j++){
											level_matrice[posY-1-i][posX-j].color = FD_GREEN;
											level_matrice[posY-1-i][posX-j].ch = ' ';
											window_mvaddch_col(w_level, posY-1-i, posX-j, FD_GREEN, ' ');
										}
									if(num_door<10){
										level_matrice[posY-4][posX-2].color = WHITE;
										level_matrice[posY-4][posX-2].ch = '0';
										level_matrice[posY-4][posX-1].color = WHITE;
										level_matrice[posY-4][posX-1].ch = num_door+'0';
										level_matrice[posY-4][posX].color = FD_GREEN;
										level_matrice[posY-4][posX].ch = ' ';
										window_mvaddch_col(w_level, posY-4, posX-2, WHITE, '0');
										window_mvaddch_col(w_level, posY-4, posX-1, WHITE, num_door+'0');
										window_mvaddch_col(w_level, posY-4, posX, FD_GREEN, ' ');
									}
									else{
										ch_1 = ((int)num_door/10)+'0';
										ch_2 = (num_door%10)+'0';
										level_matrice[posY-4][posX-2].color = WHITE;
										level_matrice[posY-4][posX-2].ch = ch_1;
										level_matrice[posY-4][posX-1].color = WHITE;
										level_matrice[posY-4][posX-1].ch = ch_2;
										level_matrice[posY-4][posX].color = FD_GREEN;
										level_matrice[posY-4][posX].ch = ' ';
										window_mvaddch_col(w_level, posY-4, posX-2, WHITE, ch_1);
										window_mvaddch_col(w_level, posY-4, posX-1, WHITE, ch_2);
										window_mvaddch_col(w_level, posY-4, posX, FD_GREEN, ' ');
									}
										//window_mvaddch_col(w_tools, POSY_DOOR, 9, WHITE, "%d",num_door);
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

	for(i=0 ; i<20 ; i++){
		printf("\n\n");
		for(j=0 ; j<60 ; j++)
			printf("%d %c ;", level_matrice[i][j].color, level_matrice[i][j].ch);
	}

  	return EXIT_SUCCESS;
}
