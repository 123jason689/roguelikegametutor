#include <stdio.h>
#include <ncurses.h>
#include <windows.h>
#include <stdlib.h>

char **map;

void initmap(char ***m, int row, int col){
	*m = (char **)malloc(sizeof(char *) * row);
	for(int i = 0; i < row; i++){
		(*m)[i] = (char *)malloc(sizeof(char) * col);
	}
}

int dungeon(int row, int col){
	for(int yy = 0; yy < row; yy++){
		for(int xx = 0; xx < col; xx++){
			map[yy][xx] = '#';
			mvaddch(yy, xx, '#');
		}
	}
	
	for(int yy = 11; yy < row/2+10; yy++){
		for(int xx = 11; xx < col/2+10; xx++){
			map[yy][xx] = ' ';
			mvaddch(yy, xx, ' ');
		}
	}
}

int movement(char c, int * const x, int * const y){ // a constant pointer to a changable value if (const int *p) it makes the value inside the pointer const not the pointer it self
	if(c == 'w' &&  map[(*y)-1][*x] == ' ') {
	    (*y)--;
	} else if(c == 's' && map[(*y)+1][*x] == ' ') {
	    (*y)++;
	} else if(c == 'a' && map[*y][(*x)-1] == ' ') {
	    (*x)--;
	} else if(c == 'd' && map[*y][(*x)+1] == ' ') {
	    (*x)++;
	}
}

int main(){

	getchar(); // i want to prompt the user to fullscreen the game first before playing


	char c = '\0';
	int x = 11, y = 11;
	int row, col;
	
	
	initscr(); // initialize the window screen
	keypad(stdscr, TRUE); // allows the use of other characters such as key_up and key_down
	
	noecho(); //hide the echo (hide the character that is getting inputed form the console)
	curs_set(0); // set the cursor invisible
	
	getmaxyx(stdscr, row, col); // get the screen maximum or the screen size in character wise units
//	printw("row: %d col: %d\n", row, col);

	initmap(&map, row, col);
	
	
	do{
//		clear(); //for clearing the console (simmilar to the windows system("cls")

		dungeon(row, col); // a function for handling the display of the dungeon
		
		movement(c, &x, &y);
		
		mvaddch(y, x, '@'); //print the character to the screen with a spesific x and y coordinates

	}while((c = getch()) != 27); // 27 == escape button
	
//	c = getch(); // normal getch
//	mvaddch(y,x, c); // print a char at a spesific postition in the console
	
	
	refresh();
	endwin();
	return 0;
}
