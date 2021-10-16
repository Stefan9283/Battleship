#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void freematrix(int **map)
{
	int i;
		for(i=0;i<10;i++)
			free(map[i]);
		free(map);
	}
int can_i_place_it_here(int **map, int x, int y, int do_i_need_to_check_the_point)
{
	//SE VERIFICA DACA IN JURUL UNUI PUNCT DE COORDONATE X,Y EXISTA ALTE CASUTE OCUPATE
	int i;

	//PENTRU PUNCT
	if(do_i_need_to_check_the_point)
		if(map[x][y]!=0)
			return 0;
	//PENTRU INTERIOR
	if(x>0&&x<9&&y>0&&y<9)
		{
			for(i=-1;i<=1;i++)
				{
					if(map[x-1][y+i]!=0)return 0;
					if(map[x+1][y+i]!=0)return 0;
					if(map[x][y-1]!=0||map[x][y+1]!=0)return 0;
				}
		}
	//PENTRU COLTURI
		if(x==0)
			{	
				if(y+1<=9&&map[x][y+1]!=0)return 0;
				if(y==0)if(map[0][1]!=0||map[1][0]!=0||map[1][1]!=0)return 0;
				if(y==9)if(map[1][9]!=0||map[0][8]!=0||map[1][8]!=0)return 0;
			}
		if(x==9)
			{
				if(y+1<=9&&map[x][y+1]!=0)return 0;
				if(y==0)if(map[8][0]!=0||map[9][1]!=0||map[8][1]!=0)return 0;
				if(y==9)if(map[8][9]!=0||map[9][8]!=0||map[8][8]!=0)return 0;
			}
	//PENTRU MARGINI
			if(x==0) //din stanga
			{
				if(y>0&&y<9)
					{
						for(i=-1;i<=1;i++)if(map[x+1][y+i]!=0)return 0;
						if(map[x][y-1]!=0||map[x][y+1]!=0)return 0;
					}
			}
			if(x==9)	//din dreapta
			{
				if(y>0&&y<9)
					{
						for(i=-1;i<=1;i++)if(map[x-1][y+i]!=0)return 0;
						if(map[x][y-1]!=0||map[x][y+1]!=0)return 0;
					}
			}
			if(y==9)	//de jos
			{
				if(x>0&&x<9)
					{
						for(i=-1;i<=1;i++)if(map[x+i][y-1]!=0)return 0;
						if(map[x-1][y]!=0||map[x+1][y]!=0)return 0;
					}
			}
			if(y==0)	//de sus
			{
				if(x>0&&x<9)
					{
						for(i=-1;i<=1;i++)if(map[x+i][y+1]!=0)return 0;
						if(map[x-1][y]!=0||map[x+1][y]!=0)return 0;
					}

			}
	return 1;
}
int max(int **map,int x,int y,int *direction)
{
	int i;
	int MAX;
				int max_up=0,max_down=0,max_left=0,max_right=0;
				//SE CALCULEAZA DINSTANTELE MAXIME PANA LA URMATOAREA NAVA SAU LA MARGINE
				for(i=x+1;i<10;i++)
					{
						if((map[i][y])==0)max_down++;
									else {
										max_down--;
										break;
									}
					}

				MAX=max_down;
				*direction=2;
				for(i=x-1;i>=0;i--)
					{
						if((map[i][y])==0)max_up++;
									else 
										{
											max_up--;
											break;
										}
					}
				if(MAX<max_up)
					{
						MAX=max_up;
						*direction=0;
					}
				for(i=y-1;i>=0;i--)
					{
						if((map[x][i])==0)max_left++;
									else {
										max_left--;
										break;
									}
					}
				if(MAX<max_left)
					{
						MAX=max_left;
						*direction=3;
					}
				for(i=y+1;i<10;i++)
					{
						if((map[x][i])==0)max_right++;
									else {
										max_right--;
										break;
										}
					}
				if(MAX<max_up)
					{
						MAX=max_right;
						*direction=1;
					}
		//DIMENSIUNEA MAXIMA SE ALEGE SI SE VERIFICA CARE ESTE DIMENSIUNEA MAXIMA A UNEI NAVE CARE POATE FI PLASATA DIN PUNCTUL x,y
	return MAX;}
void init(int **map,int value)
{
	int i,j;
	for(i=0;i<10;i++)
		{
			map[i]=(int*)malloc(10*sizeof(int));
			for(j=0;j<10;j++)
			{
			map[i][j]=value;
			}
		}
}

void gen_computer_map(int **map,int **ships)
{

	int x,y;
	srand(time(0));
	int remaining_ships[]={4,3,2,1};
	init(map,0);
	int i,j,k=0;
	for(i=3;i>=0;i--)
	{
			while(remaining_ships[i])
		{
		x=rand()%10;
		y=rand()%10;
			if(can_i_place_it_here(map,x,y,1))
				{
				int MAX;
				int direction;
				MAX=max(map,x,y,&direction);
				if(MAX>=i)
					{
						if(i==0)
						{
							map[x][y]=1;
							ships[k]=(int*)malloc(sizeof(int)*5);//
							ships[k][0]=x;
							ships[k][1]=y;
							ships[k][2]=x;
							ships[k][3]=y;
							ships[k][4]=1;
							remaining_ships[i]--;k++;
							continue;
						}
						int ok=0;
						if(direction==0)
							{
								for(j=0;j<=i;j++)
									{if(can_i_place_it_here(map,x-j,y,1))ok++;}
									if(ok==i+1)
											{
												ships[k]=(int*)malloc(sizeof(int)*(i+5));//
												
												ships[k][0]=x;
												ships[k][1]=y;
												for(j=0;j<=i;j++)if(x-j<=9)
													{
														map[x-j][y]=1;
														if(j==i)
															{
															ships[k][2]=x-j;
															ships[k][3]=y;
															}
															ships[k][4+j]=1;

													}


												remaining_ships[i]--;k++;
											}
							}
							else if(direction==2)
							{
									for(j=0;j<=i;j++)
									if(can_i_place_it_here(map,x+j,y,1))ok++;
									if(ok==i+1)
										{
											ships[k]=(int*)malloc(sizeof(int)*(i+5));//
											ships[k][0]=x;
											ships[k][1]=y;										
											for(j=0;j<=i;j++)if(x+j<=9)
												{
													map[x+j][y]=1;
													if(j==i)
															{
															ships[k][2]=x+j;
															ships[k][3]=y;
															}
															ships[k][4+j]=1;
												}

												remaining_ships[i]--;k++;	
											}
								}
									else if(direction==1)
									{
										for(j=0;j<=i;j++)
										if(can_i_place_it_here(map,x,y+j,1))ok++;
										if(ok==i+1)
												{
													ships[k]=(int*)malloc(sizeof(int)*(i+5));
													ships[k][0]=x;
													ships[k][1]=y;
													for(j=0;j<=i;j++)if(y+j<=9)
														{
															map[x][y+j]=1;
															if(j==i)
															{
															ships[k][2]=x;
															ships[k][3]=y+j;
															}	
															ships[k][4+j]=1;
														}

													remaining_ships[i]--;k++;
												}
									}									
									else if(direction==3)
									{
										for(j=0;j<=i;j++)
										if(can_i_place_it_here(map,x,y-j,1))ok++;
										if(ok==i+1)
												{
													ships[k]=(int*)malloc(sizeof(int)*(i+5));
													ships[k][0]=x;
													ships[k][1]=y;
													for(j=0;j<=i;j++)if(y-j<=9)
														{
															map[x][y-j]=1;
															if(j==i)
															{
															ships[k][2]=x;
															ships[k][3]=y-j;
															}	
															ships[k][4+j]=1;
														}

													remaining_ships[i]--;k++;
													}
									}											
						}
				}
			}
	}

} 