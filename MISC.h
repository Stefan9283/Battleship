#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

typedef struct player
	{
		int remaining;
		int **map, **ships;
		int **chosen;
		int score;
	}player;

	typedef struct computer
	{
		int remaining;
		int **map, **ships;
	}computer;

void highlight_matrix_element(int h,int w,int x,int y,int **chosen,int x_sel,int y_sel)
{
	start_color();
	int j,k,l=0,m=0;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
			for(j=0;j<10;j++)
			{
			for(k=0;k<10;k++)
				{
					if(j==x_sel&&k==y_sel)
					{
						attron(A_STANDOUT);
						mvprintw(x+j+m,y+k+l,"%c",' ');
						mvprintw(x+j+m,y+k+l+1,"%c",' ');
						if(w>80||h>=36)
						{
							mvprintw(x+m+j,y+k+l+2,"%c",' ');
							mvprintw(x+m+j+1,y+k+l,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+1,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+2,"%c",' ');
							//l++;
						}
						attroff(A_STANDOUT);
					}
					
					if(w>80)l+=2;
					else l++;
					if(k==9)
						{
							if(w>80)m+=1;
							
							l=0;
						}
					
				}
			}
}



