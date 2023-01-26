#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

void shuffle(unsigned int wDeck[][FACES]);//prototype
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]);//prototype

int main(void){
	
	srand(time(NULL));
	unsigned int deck[SUITS][FACES] = {0};//declares all array elements as 0
	
	shuffle(deck);
	
	const char *suit[SUITS] = {"Hearts", "Diamond", "Clubs", "Spades"};
	
	const char *face[FACES] = {"Ace", "Deuce", "Three", 
	"Four", "Five", "Six", "Seven", "Eight", 
	"Nine", "Ten", "Jack", "Queen", "King"};
	
	deal(deck, face, suit);//deal the deck
	return 0;
}
//shuffle cards in the deck
void shuffle(unsigned int wDeck[][FACES]){
	for(size_t card = 1; card <= CARDS; card++)
	{
		size_t row; //row number which is 4
		size_t column; // column number which is 13
		
		do{
			row = rand() % SUITS; //generates numbers from 0 - 3
			column = rand() % FACES; //generates numbers fron 0 - 12
		}
		while(wDeck[row][column] != 0);
		
		wDeck[row][column] = card;	
	}	
}

void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]){
	for(size_t card = 1; card <= CARDS; card++)
	{
		for(size_t row = 0; row < SUITS; row++)
		{
			for(size_t column = 0; column < FACES; column++)
			{
				if(wDeck[row][column] == card)
				{
					printf("%5s of %-8s\n", wFace[column], wSuit[row]);
				}
					
			}
		}
		
	}
		
}