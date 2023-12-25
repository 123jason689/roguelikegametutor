#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool pplaced = 0;
bool rplaced = 0;
int rsy, rsx;
int ry, rx;

void initmap(char ***m, int row, int col){
	*m = (char **)malloc(sizeof(char *) * row);
	for(int i = 0; i < row; i++){
		(*m)[i] = (char *)malloc(sizeof(char) * col);
	}
}

int dungeon(int row, int col, char **map, int * const x, int * const y, char c){
	
	srand(time(NULL));
	
	if(!rplaced){
		for(int yy = 0; yy < row; yy++){
			for(int xx = 0; xx < col; xx++){
				map[yy][xx] = '#';
			}
		}
	}
	
	for(int yy = 0; yy < row; yy++){
		for(int xx = 0; xx < col; xx++){
			if(map[yy][xx] == ' ') mvaddch(yy, xx, ' ');
			else mvaddch(yy, xx, '#');
		}
	}
	
	if(!rplaced){
		
		// make room point
		do{
			ry = rand() % row - 3;
			rx = rand() % col - 3;
		}while(ry < 1 || rx < 1);
		
		// generate size
		do{
			rsy = rand() % 11 + 1;
			rsx = rand() % 22 + 1;
		} while(ry + rsy > row-2 || rx + rsx > col-2);
		
		for(int yy = ry; yy < ry+rsy; yy++){
			for(int xx = rx; xx < rx+rsx; xx++){
				map[yy][xx] = ' ';
				mvaddch(yy, xx, ' ');
			}
		}
		rplaced =1;
	}
	
	if(!pplaced){
		do{
			*y = rand() % row;
			*x = rand() % col;
		} while(map[*y][*x] != ' ');
		pplaced = 1;
	}
	
	if(c == 'w' &&  map[(*y)-1][*x] == ' ') (*y)--;
	else if(c == 's' && map[(*y)+1][*x] == ' ') (*y)++;
	else if(c == 'a' && map[*y][(*x)-1] == ' ') (*x)--;
	else if(c == 'd' && map[*y][(*x)+1] == ' ') (*x)++;
	
	mvaddch(*y, *x, '@'); //print the character to the screen with a spesific x and y coordinates
}

//int movement(char c, int * const x, int * const y) // a constant pointer to a changable value if (const int *p) it makes the value inside the pointer const not the pointer it self

int main(){

	getchar(); // i want to prompt the user to fullscreen the game first before playing


	char c = '\0';
	int x = 11, y = 11;
	int row, col;
	char **map;
	
	
	initscr(); // initialize the window screen
	keypad(stdscr, TRUE); // allows the use of other characters such as key_up and key_down
	
	noecho(); //hide the echo (hide the character that is getting inputed form the console)
	curs_set(0); // set the cursor invisible
	
	getmaxyx(stdscr, row, col); // get the screen maximum or the screen size in character wise units
//	printw("row: %d col: %d\n", row, col);

	initmap(&map, row, col);
	
	
	do{
//		clear(); //for clearing the console (simmilar to the windows system("cls")

		dungeon(row, col, map, &x, &y, c); // a function for handling the display of the dungeon

	}while((c = getch()) != 27); // 27 == escape button
	
//	c = getch(); // normal getch
//	mvaddch(y,x, c); // print a char at a spesific postition in the console
	
	
	refresh();
	endwin();
	return 0;
}
