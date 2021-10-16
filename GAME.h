#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void delay(int seconds)
{
    long pause;
    clock_t now,then;

    pause = seconds*CLOCKS_PER_SEC;
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int no_of_ships_down(int **ships)
{
	//numara cate nave au fost doborate
	int remaining_ships[]={4,3,2,1};
	int i,j,k=0,total=0;
	
		for(i=3;i>=0;i--)
	{
		remaining_ships[i]=4-i;

		while(remaining_ships[i])
		{
					
					int ok=0;
					for(j=0;j<=i;j++)
						{
							if(ships[k][4+j]==4)
								ok++;
						}
					k++;
					remaining_ships[i]--;
					if(ok==i+1)total++;
		



		}
	}
	return total;
}

void randomize(int **map,int **ships)
{

	int remaining_ships[]={4,3,2,1};
	int isthisshipdown[]={1,1,1,1,1,1,1,1,1,1};
	int n=0;
	//se plaseaza toate navele doborate in totalitate
	int i;
	for(i=3;i>=0;i--)
	{
			while(remaining_ships[i])
		{	
			
			int j;
			int ok=0;
			for(j=0;j<=i;j++)
				{
					if(ships[n][4+j]==4)ok++;
				}
			if(i+1==ok)
			{
				isthisshipdown[n]--;
				if(ships[n][0]==ships[n][2])
				{	
					for(j=ships[n][1];j<=ships[n][3];j++)
					{
						map[ships[n][0]][j]=4;
						
					}
				}
				else if(ships[n][1]==ships[n][3])
				{
					for(j=ships[n][0];j<=ships[n][2];j++)
					{
						map[j][ships[n][1]]=4;
					}

				}
				
			}
			
			n++;
			remaining_ships[i]--;

		}
	}

	//se alege la intamplare unde sa copiem navele ramase

	//n=0;


	for(i=0;i<=9;i++)
	{
	srand(time(0));	
	int j;
	if(i==0)j=3;
	else if(i==1||i==2) j=2;
		else if(i>=3&&i<=5) j=1;
				else if(i>=6) j=0;

				if(!isthisshipdown[i])
				{
					continue;


				}
				else 
				{
					while(isthisshipdown[i])
					{
						int ok=0,x=rand()%10,y=rand()%10,direction=rand()%2;
						int k;
						if(direction)
							{
								for(k=0;k<=j&&x+j<=9;k++)if(can_i_place_it_here(map,x+k,y,1))ok++;
																else break;

								if(ok>=j+1)
								{	
									isthisshipdown[i]=0;

									for(k=0;k<=j;k++)
									{
										map[x+k][y]=ships[i][4+k];
									}
									ships[i][0]=x;
									ships[i][1]=y;
									ships[i][2]=x+j;
									ships[i][3]=y;

								}
							}
							else
							{

								if(y+j<=9)
									for(k=0;k<=j&&x+j<=9;k++)
										{
											if(can_i_place_it_here(map,x,y+k,1))ok++;
																else break;
										}

								if(ok>=j+1&&y+j<=9)
								{	
									isthisshipdown[i]=0;

									for(k=0;k<=j;k++)
									{
										map[x][y+k]=ships[i][4+k];
									}
									ships[i][0]=x;
									ships[i][1]=y;
									ships[i][2]=x;
									ships[i][3]=y+j;

								}

							}
					}

				}
	}
}

void update(int **player,int **pships)
{
	//se face update matricii pships
	int i,j;
	for(i=0;i<=9;i++)
		{
			if(pships[i][0]==pships[i][2])
				{	
					int index=4;
					
					if(pships[i][1]<=pships[i][3])
					{
						for(j=pships[i][1];j<=pships[i][3];j++)
						{
							pships[i][index]=player[pships[i][0]][j];
							index++;
						}
					}
					else
					{
						for(j=pships[i][3];j<=pships[i][1];j++)
							{
								pships[i][index]=player[pships[i][0]][j];
								index++;
							}
					}
				}
				else if(pships[i][1]==pships[i][3])
				{
					int index=4;
					
					if(pships[i][0]<=pships[i][2])
					{
						for(j=pships[i][0];j<=pships[i][2];j++)
						{
							pships[i][index]=player[j][pships[i][1]];
							index++;
						}
					}
					else
					{
						for(j=pships[i][2];j<=pships[i][0];j++)
						{
							pships[i][index]=player[j][pships[i][1]];
							index++;
						}
					}		
				}

			
		}

}

void print_game_screen(WINDOW *my_win,struct player p,struct computer c)
{
	int x,y;
	getmaxyx(stdscr,x,y);
	my_win = create_newwin(x, y,0,0);
	pretty_print(x,y,x/2-5,y/2-30,p.map);
	pretty_print(x,y,x/2-5,y/2 +7,p.chosen); 
	if((y>80)&&(x>=36))
	{
	mvprintw(3,(y-strlen("Score: number"))/2,"Score: %d",p.score);
	mvprintw(4,(y-strlen("Remaining HP Player:   no"))/2,"Remaining HP Player:   %d",p.remaining);
	mvprintw(5,(y-strlen("Remaining HP Opponent: no"))/2,"Remaining HP Opponent: %d",c.remaining);
	mvprintw(x-2,1,"K : Kamikaze Kill");
	mvprintw(x-3,1,"R : Randomize");
	mvprintw(x-4,1,"D : Destroy In Advance");
	}
}
int opponent(int **player) 
{
	int posx=-1,posy=-1;
	int ones=0,zeros=0;
	srand(time(0));int incercari=0;
	while(zeros==0)
	{	
		if(posx==-1&&posy==-1)
		{
			int x,y;
			while(1)
			{
				x=rand()%10;
				y=rand()%10;
				if(player[x][y]!=4)
				{
					if(player[x][y]==1)
					{
						ones++;
						player[x][y]=4;
						posx=x;
						posy=y;
					}
					else
					{
					player[x][y]=4;
					posx=-1;
					posy=-1;
					zeros++;
					}
				break;
				}
			}
		}
		else
		{
			int direction=rand()%10;
			direction=rand()%4;
			int x0=posx,y0=posy;
			incercari++;
			if(direction==0)
			{
				x0-=1;
			}
			else if(direction==1)
			{
				y0+=1;
			}
			else if(direction==2)
			{
			x0+=1;
			}
			else if(direction==3)
			{
				y0-=1;
			}

			if(x0<=9&&x0>=0&&y0>=0&&y0<=9)
				if(player[x0][y0]!=4)
				{
					if(player[x0][y0]==1)
					{
						posx=x0;
						posy=y0;
						ones++;
					}
					if(player[x0][y0]==0)
					{
						zeros++;
						posx=-1;
						posy=-1;
					}
							
					player[x0][y0]=4;
				}
			if(incercari==30)
				{
					posx=-1;
					posy=-1;
				}
		}
	}
	return ones;
}
void destroy_in_advance(struct player *p,struct computer *c)
{
	int x,y;

	while(1)
	{
		x=rand()%10;
		y=rand()%10;
		if(p->map[x][y]!=4)
		{
			if(p->map[x][y]==1)(p->remaining)--;
			p->map[x][y]=4;
			break;
		}
	}
	while(1)
	{
		x=rand()%10;
		y=rand()%10;
		if(p->chosen[x][y]==3)
		{		
			p->chosen[x][y]=c->map[x][y];
			c->map[x][y]=4;
			if(p->chosen[x][y]==1)
				(c->remaining)--;
			break;
		}
	}	
}
int isthisshipdown(int choice,int **ships)
{
	int i;
	if(choice>=6)
			{
				if(ships[choice][4]==1)return 0;
			}
			else if(choice==0)
			{
				for(i=0;i<=3;i++)
					if(ships[choice][4+i]==1)
						{
							return 0;
						}
			}
			else if(choice==2||choice==1)
			{
				for(i=0;i<=2;i++)
					if(ships[choice][4+i]==1)
						{
							return 0;
						}
			}
			else 
			{
				for(i=0;i<=1;i++)
					if(ships[choice][4+i]==1)
						{
							return 0;
						}
			}
			return 1;

}
void finishship(int choice, int **ships, int **map,int *remaining)
{
	int j;
	if(ships[choice][0]==ships[choice][2])
	{
		if(ships[choice][1]<=ships[choice][3])
		{
			for(j=ships[choice][1];j<=ships[choice][3];j++)
			{
				if(map[ships[choice][0]][j]==1||map[ships[choice][0]][j]==3)
						(*remaining)--;
				map[ships[choice][0]][j]=4;
			}
		}
		else
		{
			for(j=ships[choice][3];j<=ships[choice][1];j++)
				{
				if(map[ships[choice][0]][j]==1||map[ships[choice][0]][j]==3)
					(*remaining)--;
				map[ships[choice][0]][j]=4;
				}
		}		
	}
	else
	{		
		if(ships[choice][0]<=ships[choice][2])
		{
			for(j=ships[choice][0];j<=ships[choice][2];j++)
			{
				if(map[j][ships[choice][1]]==1||map[j][ships[choice][1]]==3)
					(*remaining)--;
				map[j][ships[choice][1]]=4;
			}
		}
		else
		{
			for(j=ships[choice][2];j<=ships[choice][0];j++)
			{
				if(map[j][ships[choice][1]]==1||map[j][ships[choice][1]]==3)
					(*remaining)--;
				map[j][ships[choice][1]]=4;
			}
		}		
	}
}
void kamikazekill(struct player *p,struct computer *c)
{
	//navele doborate cu aceasta functie vor fi afisate cu rosu
	srand(time(0));
	int choice1,choice2,gasit=0;
	while(gasit!=2)
	{
		gasit=0;
		choice1=rand()%10;
		choice2=rand()%10;
		if(!isthisshipdown(choice1,p->ships))gasit++;
		if(!isthisshipdown(choice2,c->ships))gasit++;
	}

	finishship(choice1,p->ships,p->map,&(p->remaining));
	finishship(choice2,c->ships,p->chosen,&(c->remaining));
}
void GAME(int *resume,struct player *p, struct computer *c)
{

	srand(time(0)); 
	WINDOW *my_win;
	int ch;
	int streak=1;
	int y, x;
	int exit=0;
	int turn;
	int x_sel=0,y_sel=0;
	if(*resume==0)
		{
			if(rand()%2==0)
			turn=1;
			else turn=0;
		}
	else turn=1;
	clear();
	*resume=0;
	while(p->remaining>0&&p->remaining>0&&*resume==0)
	{
		start_color();
		cbreak();
		getmaxyx(stdscr,x,y);
		my_win = create_newwin(x, y,0,0);
		refresh();

		if(turn)
		{
			while(turn==1)
				{
					getmaxyx(stdscr,x,y);		
					//mv_print_matrix(x/2,y/4,p->map); 
					print_game_screen(my_win,*p,*c);
					highlight_matrix_element(x,y,x/2-5,y/2 +7,p->chosen,x_sel,y_sel);			
					ch=getch();				
					clear();
					refresh();
					//schimba pozitia cursorului jucatorului
					if(ch==KEY_DOWN&&x_sel<9)
						x_sel++;
					else if(ch==KEY_RIGHT&&y_sel<9)
						y_sel++;
					else if(ch==KEY_UP&&x_sel>0)
						x_sel--;
					else if(ch==KEY_LEFT&&y_sel>0)
						y_sel--;
					else if(ch=='q'||ch=='Q')
						{
							(*resume)=1;
							break;
						}
					else if(ch=='d'||ch=='D')
						{							
							int i;
							for(i=0;i<10;i++)
							{
								destroy_in_advance(p,c);
								if(c->remaining==0||(p->remaining)==0)
									{
										exit=1;
										break;
									}
							}
						}						
					else if(ch=='r'||ch=='R')
						{	
							update(p->map,p->ships);
							int i,j;
							for(i=0;i<=9;i++)
								for(j=0;j<=9;j++)
									p->map[i][j]=0;
							randomize(p->map,p->ships);
							update(p->map,p->ships);
						}
						else if(ch=='k'||ch=='K')
						{

							kamikazekill(p,c);
							int i,j;
							for(i=0;i<=9;i++)
								for(j=0;j<=9;j++)
									if(p->chosen[i][j]==4)
										c->map[i][j]=4;
							update(p->map,p->ships);
							update(c->map,c->ships);
						}

				if(ch==10)
					{

						if(p->chosen[x_sel][y_sel]!=3)continue; //se verifica daca punctul n-a mai fostales
						p->chosen[x_sel][y_sel]=p->map[x_sel][y_sel]; //se copiaza valoarea
						if(c->map[x_sel][y_sel]==1)
							{
								p->chosen[x_sel][y_sel]=1;
								c->map[x_sel][y_sel]=4;
								(c->remaining)--;
								streak++;
							} //daca este 1 atunci se scade HP
						else 	{
								turn--;	//altfel a fost 0 si tura se incheie
								p->score=p->score+10*streak;
								streak=0;
								p->chosen[x_sel][y_sel]=0;
									}
						
					}
				
					if(c->remaining==0||(p->remaining)==0)
						{
							exit=1;
							break;
						}
				}

			if(*resume||exit)break;	
		}
		else
		{
			my_win = create_newwin(x, y,0,0);
			//mvprintw(x/2,y/2-15,"It's the opponent's turn");
			delay(3);
			(p->remaining)=(p->remaining)-opponent(p->map);
			turn++;
			if(c->remaining==0||(p->remaining)==0)
				{
					exit=1;
					break;
				}
		}

		raw();
		noecho();
		clear();

	}

	if(c->remaining==0)
	{
	mvprintw(x/2,y/2-15,"You won");
	mvprintw(x/2+1,y/2-15,"Final score: %d",p->score);
	mvprintw(x/2+2,y/2-15,"You've taken down all the ships");
	update(p->map,p->ships);
	mvprintw(x/2+3,y/2-15,"%d of yours did not survive",no_of_ships_down(p->ships));
	ch=getch();

	}
	else 
	if((p->remaining)==0)
	{
	mvprintw(x/2,y/2,"You lost");
	mvprintw(x/2+1,y/2-15,"All of your ships have been taken down");
	update(c->map,c->ships);
	mvprintw(x/2+2,y/2-15,"%d of your opponent's ships were taken down",no_of_ships_down(c->ships));
	ch=getch();

	}
	destroy_win(my_win);	
}