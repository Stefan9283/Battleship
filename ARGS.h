#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void pretty_print(int h,int w,int x,int y,int **mat_citite)
{
	start_color();
	int j,k,l=0,m=0;
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
		
		if((w<80)&&(h<36))mvprintw(x-1,y,"1 2 3 4 5 6 7 8 9 10");
			else mvprintw(x-1,y,"1  2  3  4  5  6  7  8  9  10");
			for(j=0;j<10;j++)
			{
				
				mvprintw(x+j+m,y-2,"%d",j+1);

			for(k=0;k<10;k++)
				{



					if(mat_citite[j][k]==0){
						attron(COLOR_PAIR(3)|A_STANDOUT);
						mvprintw(x+m+j,y+k+l,"%c",' ');
						mvprintw(x+m+j,y+k+l+1,"%c",' ');
						if((w>80)||(h>=36))
						{
							mvprintw(x+m+j,y+k+l+2,"%c",' ');
							mvprintw(x+m+j+1,y+k+l,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+1,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+2,"%c",' ');
							l++;
						}
						attroff(COLOR_PAIR(3)|A_STANDOUT);
					}
					else 
					if(mat_citite[j][k]==1){
						attron(COLOR_PAIR(4)|A_STANDOUT);
						mvprintw(x+m+j,y+k+l,"%c",' ');
						mvprintw(x+m+j,y+k+l+1,"%c",' ');
						if((w>80)||(h>=36))
						{
							mvprintw(x+m+j,y+k+l+2,"%c",' ');
							mvprintw(x+m+j+1,y+k+l,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+1,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+2,"%c",' ');
							l++;
						}
						attroff(COLOR_PAIR(4)|A_STANDOUT);
					}
					else if(mat_citite[j][k]==4){
						attron(COLOR_PAIR(1)|A_STANDOUT);
						mvprintw(x+m+j,y+k+l,"%c",' ');
						mvprintw(x+m+j,y+k+l+1,"%c",' ');
						if((w>80)||(h>=36))
						{
							mvprintw(x+m+j,y+k+l+2,"%c",' ');
							mvprintw(x+m+j+1,y+k+l,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+1,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+2,"%c",' ');
							l++;
						}
						attroff(COLOR_PAIR(1)|A_STANDOUT);
						}
						else 
					if(mat_citite[j][k]==3){
						attron(COLOR_PAIR(2)|A_STANDOUT);
						mvprintw(x+m+j,y+k+l,"%c",' ');
						mvprintw(x+m+j,y+k+l+1,"%c",' ');
						if((w>80)||(h>=36))
						{
							mvprintw(x+m+j,y+k+l+2,"%c",' ');
							mvprintw(x+m+j+1,y+k+l,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+1,"%c",' ');
							mvprintw(x+m+j+1,y+k+l+2,"%c",' ');
							l++;
						}
						attroff(COLOR_PAIR(2)|A_STANDOUT);
					}
					l++;
					if(k==9)
						{
							if((w>80)||(h>=36))m+=1;
							
							l=0;
						}
				}
			}
		}

void citire_harti(int ***mat_citite,int argc,char *argv[])
{
	int i,j,k; char buffer[2];
	FILE *f;
	for(i=1;i<argc;i++)
	{
		mat_citite[i-1]=(int**)malloc(10*sizeof(int*));
		f=fopen(argv[i],"r");
		puts(argv[i]);		
		for(j=0;j<10;j++)
		{
			mat_citite[i-1][j]=(int*)malloc(10*sizeof(int));			
			for(k=0;k<10;k++)
				{
					fgets(buffer,2,f);
					sscanf(buffer,"%d",&mat_citite[i-1][j][k]);
					fgets(buffer,2,f);
				}
		}
				fclose(f);	
	}
}
void memcitire(int ***mat_citite,int argc)
{
	int i,j;
	for(i=0;i<argc-1;i++)
		{
			for(j=0;j<10;j++)
			{
			free(mat_citite[i][j]);
			}
		free(mat_citite[i]);
		}
	free(mat_citite);}
int meniu_selectie(int ***mat_citite, int argc)
{
	int selected=0;
	int ch;
	int y, x;
	WINDOW *my_win;
	while(1)
	{


				getmaxyx(stdscr,x,y);
				refresh();
	//mv_print_matrix(x/2,y/2,mat_citite[selected]);
	pretty_print(x,y,x/2-5,y/2-10,mat_citite[selected]); 		
	//pretty_print(x,y,2,3,mat_citite[selected]); 		
	raw();
	noecho();
	my_win = create_newwin(x, y,0,0);
	
	mvprintw(2,5,"Press left or right arrow key to change between the maps");
	mvprintw(3,5,"Press enter key to confirm");
	mvprintw(4,5,"Try pressing R if you're feeling lucky");
	mvprintw(5,5,"Press G to get a randomly generated map");
	ch = getch();
	
	if(ch=='r')
		{	
			srand(time(0));
			// printw("%d\n",rand()%(argc-1));	
			return rand()%(argc-1);		
		}
		else if(ch=='G'||ch=='g')
			{
				return argc+1;
			}
	if(ch==KEY_LEFT&&selected!=0)selected--;
	if(ch==KEY_RIGHT&&selected!=argc-2)selected++;
	if(ch==10)break;
	//ch = getch();

	//clear();
	
	}
	//clear();
	destroy_win(my_win);
	return selected;
}
void savegame(struct player p, struct computer c)
{
	FILE *fp;
	fp = fopen("./save.sav", "w");
	int i,j;
	for(i=0;i<=9;i++)
		for(j=0;j<=9;j++)
	{
		fprintf(fp, "%d\n",p.map[i][j]);
		//if(j==9)fprintf(fp, "\n");
	}

	for(i=0;i<=9;i++)
		for(j=0;j<=9;j++)
	{
		fprintf(fp, "%d\n",c.map[i][j]);
		//if(j==9)fprintf(fp, "\n");
	}

	for(i=0;i<=9;i++)
		for(j=0;j<=9;j++)
	{
		fprintf(fp, "%d\n",p.chosen[i][j]);
		//if(j==9)fprintf(fp, "\n");
	}
	int remaining_ships[]={1,2,3,4};

	int k=0;
	for(i=0;i<=3;i++)
	{
		
			while(remaining_ships[i])
		{
			
			for(j=0;j<=7-i;j++)
				{
					fprintf(fp, "%d\n",p.ships[k][j]);
					fprintf(fp, "%d\n",c.ships[k][j]);
				}
			remaining_ships[i]--;k++;
			//fprintf(fp, "\n" );
		}
		
	}
	fprintf(fp,"%d\n%d\n%d\n",p.remaining,c.remaining,p.score);

	fclose(fp);


}

void readfromsave(struct player *p, struct computer *c)
{

	FILE *fp;
	fp = fopen("./save.sav", "r");

	int i,j;

	for(i=0;i<=9;i++)
	{	
		p->map[i]=(int*)malloc(10*sizeof(int));
			for(j=0;j<=9;j++)
			{
				fscanf(fp, "%d",&(p->map[i][j]));
			}
	}	
	for(i=0;i<=9;i++)
	{
		c->map[i]=(int*)malloc(10*sizeof(int));
			for(j=0;j<=9;j++)
		{
			fscanf(fp, "%d",&(c->map[i][j]));
		}
	}
	for(i=0;i<=9;i++)
	{
		p->chosen[i]=(int*)malloc(10*sizeof(int));
			for(j=0;j<=9;j++)
		{
			fscanf(fp, "%d",&(p->chosen[i][j]));
		}
	}

	int remaining_ships[]={1,2,3,4};

	int k=0;
	for(i=0;i<=3;i++)
	{
		
			while(remaining_ships[i])
		{
			p->ships[k]=(int*)malloc(sizeof(int)*(8-i));
			c->ships[k]=(int*)malloc(sizeof(int)*(8-i));

			for(j=0;j<=7-i;j++)
				{
					fscanf(fp, "%d",&(p->ships[k][j]));
					fscanf(fp, "%d",&(c->ships[k][j]));
				}
			remaining_ships[i]--;k++;
		}
		
	}



	fscanf(fp,"%d\n%d\n%d\n",&(p->remaining),&(c->remaining),&(p->score));

	fclose(fp);
}