#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(void);
void gmng(void);
void tetris(void);
void maze(void);
void compare(int x,int y);
int equal(int x,int y);


int main(void)
{
	menu();
	return 0;
}


void menu(void)
{
	int choice;
	printf("-----------------------Welcome to the Game Arena-----------------------");
	printf("\n                  1. Guess My Number Game");
	printf("\n                  2. Tetris Game");
	printf("\n                  3. Maze Solver");
	printf("\n                  4. Quit");
	printf("\nChoose 1,2,3 or 4: ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:
			gmng();
			menu();
			break;
			
		case 2:
			tetris();
			menu();
			break;
		
		case 3:
			maze();
			menu();
			break;
			
		case 4:
			break;
			
		default:
			printf("You have entered a wrong number!\n");
			menu();
			break;
		
	}
	
}


void gmng(void)
{
	srand(time(NULL));
	int guess, flag = 0, counter = 0, num = rand()%100;
	printf("\nGuess My Number Game\n");
	do
	{
		counter++;		
		printf("\n\nEnter a guess between 1 and 100\n: ");
		scanf("%d", &guess);
		compare(guess,num);
		flag = equal(guess,num);
	}while(flag != 1);
	
	printf("\nCorrect! You got it in %d guesses!\n\n", counter);
}

void compare(int x,int y)
{
	if(x > y)
		printf("Too high, try again!");
	
	else if(x < y)
		printf("Too low, try again!");
}

int equal(int x,int y)
{
	if (x == y)
		return(1);
	
	else
		return(0);
}


void tetris(void)
{
	
	
}


void maze(void)
{
	srand(time(NULL));
	int n, row, column, start=0, exit=0, counter;
	printf("\nMaze Solver\nEnter row number: ");
	scanf("%d", &n);

	do{
		start = rand()%(n*n+1);
		exit = rand()%(n*n+1);	
	}while(start >= exit);
	
	counter = exit - start - 1;
	
	for(row = 0; row<n; row++)
	{
		for(column = 0; column<n; column++)
		{
			if(start == 0)
				printf("S");
				
			else if(exit == 0)
				printf("E");
				
			else
				printf(".");
			
			start--;
			exit--;
		}
		
		printf("\n");
	}
	
	printf("Number of dots between S and E from left to right is %d\n", counter);
}