#include <stdlib.h>
#include <locale.h>
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

int main() {
	// ncurses initialisation
	setlocale(LC_ALL, "");
  ncurses_init();

	//Declarations
	int i, posY_tools=0, posX_tools=0, posX_gates=8, ch, num_gate=1, num_level=1;
	char* tools[13] = {"Delete", "Block", "Ladder", "Trap", "Gate", "Key", "Door", "Exit", "Start", "Robot", "Probe", "Life", "Bomb"};
	int gates_colors[4] = {FD_MAGENTA, FD_GREEN, FD_YELLOW, FD_BLUE};

	// Colors initialisation and palette definition
  ncurses_colors();
	palette();
	
	
	// Background Black
	/*
	attron(FD_BLACK);
	for(i=0 ; i<LINES ; i++){
		for(j=0 ; j<COLS ; j++){
			mvaddch(i,j,' ');
		}
	}
	attroff(FD_BLACK);
	*/

	//window_t *window_create(int posX, int posY, int width, int height, char *title, bool scroll)
	window_t * w_level = window_create(0, 0, 62, 22, "Level", false);
	window_t * w_tools = window_create(62, 0, 15, 22, "Tools", false);
	window_t * w_information = window_create(0, 22, 77, 5, "Informations", false);
	
	
	//wbkgd(w_level->inner, FD_BLACK);
	//wbkgd(w_tools, COLOR_PAIR(FD_BLACK));
	//wbkgd(w_information->inner, FD_BLACK);
	//window_refresh(w_tools);
	
	window_refresh(w_level);
	window_refresh(w_tools);
	window_refresh(w_information);
	
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

	while((ch = getch()) != KEY_F(2)) {
		window_mvprintw_col(w_tools, posY_tools, posX_tools, WHITE, " ") ;
    
    // New position
    switch(ch) {
      case KEY_LEFT:
      	if(posY_tools == POSY_GATE){
					if(posX_gates>8){
						window_mvprintw_col(w_tools, POSY_KEY, posX_gates, WHITE, " ") ;
						posX_gates--;
						window_mvprintw_col(w_tools, POSY_KEY, posX_gates, WHITE, "^") ;
					}
				}
				if(posY_tools == POSY_DOOR){
					if(num_gate>1){
						num_gate--;
						if(num_gate<10)
							window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "0%d",num_gate);
					 	else
							window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "%d",num_gate);
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
						window_mvprintw_col(w_tools, POSY_KEY, posX_gates, WHITE, " ") ;
						posX_gates++;
						window_mvprintw_col(w_tools, POSY_KEY, posX_gates, WHITE, "^") ;
					}
				}
				if(posY_tools == POSY_DOOR){
					if(num_gate<99){
						num_gate++;
						if(num_gate<10)
							window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "0%d",num_gate);
					 	else
							window_mvprintw_col(w_tools, POSY_DOOR, 9, WHITE, "%d",num_gate);
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
				window_mvprintw_col(w_information, 0, 0, WHITE, "posy = %d",posY_tools);
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
						else posY_tools+=2;
					}
					
				}
				window_mvprintw_col(w_information, 0, 0, WHITE, "posy = %d",posY_tools);
        break;
    }
    
    // Display character
		window_mvprintw_col(w_tools, posY_tools, posX_tools, WHITE, ">") ;
		window_refresh(w_tools);
		window_refresh(w_information);
  }

	// Stop ncurses
  ncurses_stop();

	window_delete(&w_level);
	window_delete(&w_tools);
	window_delete(&w_information);

  return EXIT_SUCCESS;
}
