#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "MISC.h"
#include "mapgen.h"
#include "ARGS.h"
#include "GAME.h"
#include "NEWGAME.h"
#include "Menu.h"
int main(int argc, char *argv[])
{
	
	if(argc==1)
		{
			printf("Eroare: nu exista argumente\n");
 			return 1;
 		}
 		else
 		{
			int i;
			for(i=1;i<argc;i++)
			{
				if(fopen(argv[i],"r")==NULL)
				{
					printf("[Eroare]: Fisierul %s nu poate fi deschis.\n",argv[i]);
					return 1;
				}
			}



		 	initscr(); 
		 	refresh(); 
			raw();
		 	Menu(argc,argv);

		 	endwin();
 		} 
 	return 0;
 } 