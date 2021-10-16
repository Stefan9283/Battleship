#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void pships_create(int **player,int **pships)
{
	//matrice ce contine coordonatele capetelor navelor jucatorului
	int i;
	for(i=0;i<=9;i++)
	{
		int k;
		if(i==0)k=4;
			else if(i>0&&i<=2)k=3;
				else if(i>2&&i<6)k=2;
					else k=1;

					pships[i]=(int*)malloc(sizeof(int)*(k+5));
	}
	


		int l,k,j,n=0;
	
	int ships[4]={4,3,2,1};
	
	
	for(i=3;i>=0;i--)
		{
			for(j=0;j<=9&&ships[i];j++)
			for(k=0;k<=9&&k+i<=9&&ships[i];k++)
			{
				int ok=0;
				int x=j,y=k;
				if(x>=10)continue;
				if(y-1>=0){if(player[x][y-1]==1)continue;}
				if(y+i+1<=9){if(player[x][y+i+1]==1)continue;}
				for(l=0;l<=i;l++){if(player[x][y+l]==1)ok++;}

				if(ok==i+1)
					{
						ships[i]--;
						for(l=0;l<i+1;l++)
							{
								
								pships[n][4+l]=1;
							}
						pships[n][0]=x;
						pships[n][1]=y;
						pships[n][2]=x;
						pships[n][3]=y+i;
						n++;
					}
			}

			for(j=0;j<=9&&ships[i];j++)
			for(k=0;k<=9&&k+l<=9&&ships[i];k++)
			{
				int ok=0;
				int x=k,y=j;
				if(x>=10)continue;
				if(x-1>=0){if(player[x-1][y]==1)continue;}
				if(x+i+1<=9){if(player[x+i+1][y]==1)continue;}
				for(l=0;l<=i;l++){if(player[x+l][y]==1)ok++;}

				if(ok==i+1)
					{
						ships[i]--;
						for(l=0;l<i+1;l++)
							{
								
								pships[n][4+l]=1;
							}

						pships[n][0]=x;
						pships[n][1]=y;
						pships[n][2]=x+i;
						pships[n][3]=y;
						n++;
					}
			}
		}
}

void create_player_map(int **player,int **matrix)
{
	int i,j;
	for(i=0;i<10;i++)
		{
	player[i]=(int*)malloc(10*sizeof(int));
			for(j=0;j<10;j++)
				player[i][j]=matrix[i][j];
			
		}
}

