#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void print_title(int x, int y)
{
	if(y>92&&x>33)
		{		
	        mvprintw(4,y/2-40,"d8888b.  .d8b.  d888888b d888888b db      d88888b .d8888. db   db d888888b d8888b. ");
	        mvprintw(5,y/2-40,"88  `8D d8' `8b `~~88~~' `~~88~~' 88      88'     88'  YP 88   88   `88'   88  `8D ");
	        mvprintw(6,y/2-40,"88oooY' 88ooo88    88       88    88      88ooooo `8bo.   88ooo88    88    88oodD' ");
	        mvprintw(7,y/2-40,"88~~~b. 88~~~88    88       88    88      88~~~~~   `Y8b. 88~~~88    88    88~~~   ");
	        mvprintw(8,y/2-40,"88   8D 88   88    88       88    88booo. 88.     db   8D 88   88   .88.   88      ");  
	        mvprintw(9,y/2-40,"Y8888P' YP   YP    YP       YP    Y88888P Y88888P `8888Y' YP   YP Y888888P 88     ");         
	    }
	    else mvprintw(x/2-9,y/2-5,"Battleship :)");
}
void Highlight(char *str, int ch,int h, int w)
{
		attron(A_STANDOUT);
		mvprintw(h/2-3,w/2-5,"@ %s",str);
		attroff(A_STANDOUT);
}
void select_option(int *ch, int *selected,int resume)
{
	raw();
	keypad(stdscr, TRUE);
	noecho();	
	
		*ch = getch();
		if(*ch==KEY_DOWN)
			{
				if(*selected!=2)
				{
					(*selected)++;
					if(*selected==1&&resume!=1)
						(*selected)++;
				}
				else (*selected)=0;
			}
		if(*ch==KEY_UP)
		{
			if(*selected!=0)
			{
				(*selected)--;
				if(*selected==1&&resume!=1)
					(*selected)--;
			}
				else (*selected)=2;
		}
}
void print_menu(int resume,int *selected,int *ch)
{
	curs_set(0);
	int y, x;
	WINDOW *my_win;
	
	
	char *Option[]={"New Game","Resume Game","Quit"};
	int i;
	while(1)
	{
		getmaxyx(stdscr,x,y);
		my_win = create_newwin(x,y,0,0);
		print_title(x,y);
		for(i=0;i<3;i++)//afisare optiuni
		{
			if(i==1&&resume!=1)continue;

			if(*selected==i)
				Highlight(Option[i],*selected,x,y);
				else mvprintw(x/2-3,y/2-7,"%s",Option[i]);
			x+=2;
		}	
		
		
		select_option(ch,selected,resume);
		clear();
		refresh();
		destroy_win(my_win);
		if(*ch==10||*ch=='q')break;

	}
}
void Menu(int argc,char *argv[])
{

	initscr();
	
	player p;
	p.map=(int**)malloc(10*sizeof(int*));
	p.ships=(int**)malloc(10*sizeof(int*));
	p.chosen=(int**)malloc(10*sizeof(int*));
	p.remaining=20;
	p.score=0;
	computer c;
	c.map=(int**)malloc(10*sizeof(int**));
	c.ships=(int**)malloc(10*sizeof(int*));
	c.remaining=20;


	int resume=-1;
	int selected=0,ch=1,i;

	if(fopen("save.sav","r"))
		{
			readfromsave(&p,&c);
			resume=1;
		}
	while(1)
	{
				
	print_menu(resume,&selected,&ch);

	if(ch==10&&selected==2)break;
		else if(ch==10)
		{

			switch(selected)
		{
			case 0: 
			
			if(resume!=-1)
			{
				for(i=0;i<=9;i++)
				{
					free(c.map[i]);
					free(p.chosen[i]);
					free(c.ships[i]);
					free(p.map[i]);
					free(p.ships[i]);
				}


			}
			resume=0;
			p.remaining=20;c.remaining=20; 
			p.score=0;
			gen_computer_map(c.map,c.ships);
			int ***mat_citite;
			mat_citite=(int***)malloc((argc-1)*sizeof(int**));
			citire_harti(mat_citite,argc,argv);
			int selected=meniu_selectie(mat_citite,argc);
			init(p.chosen,3);
			if(selected<argc)
			{
				create_player_map(p.map,mat_citite[selected]);
				pships_create(p.map,p.ships);
			}
			else
			gen_computer_map(p.map,p.ships);
			
			memcitire(mat_citite,argc);
			GAME(&resume,&p,&c);
			if(resume==1)savegame(p,c);	
				else if(fopen("save.sav","r"))remove("save.sav");
			break;		
			case 1:
			GAME(&resume,&p,&c);
			if(resume==1)savegame(p,c);
				else if(fopen("save.sav","r"))remove("save.sav");

		}
		selected=0;
		}
	if(ch=='q')break;
	}
	



	if(resume==-1)
	{
					free(c.map);
					free(p.chosen);
					free(c.ships);
					free(p.map);
					free(p.ships);
	}
	else
	{




		freematrix(c.map);
		freematrix(p.chosen);
		freematrix(c.ships);
		freematrix(p.map);
		freematrix(p.ships);
	}
	endwin();				
}
