#include <stdio.h>
#include <stdlib.h>
#include <time.h> //This library allows us generating random numbers

#define NUM_LOTTO_MAX 49 //Given Ranges
#define NUM_LUCKY_MAX 34
#define NUM_LUCKY_EXTRA_MAX 14
#define NUM_SUPER_MAX 54

#define POINTS_NUM_LOTTO_6 256 //These variables are the given scores, if the user makes a correct guess
#define POINTS_NUM_LOTTO_5 128 // Numerical Lotto
#define POINTS_NUM_LOTTO_4 64
#define POINTS_NUM_LOTTO_3 32

#define POINTS_LUCKY_5_AND_1 256 //Lucky Ball Scores
#define POINTS_LUCKY_5 128
#define POINTS_LUCKY_4_AND_1 64
#define POINTS_LUCKY_4 32
#define POINTS_LUCKY_3_AND_1 16
#define POINTS_LUCKY_3 8
#define POINTS_LUCKY_2_AND_1 4
#define POINTS_LUCKY_1_AND_1 2

#define POINTS_SUPER_6 256 //Super Lotto Scores
#define POINTS_SUPER_5 128
#define POINTS_SUPER_4 64
#define POINTS_SUPER_3 32

int read_int_in_range(int min, int max) { //This function takes a number from the user and returns the number if it is in the range
  int num;
  do {
    printf("Enter a number in the range [%d-%d]: ", min, max);
    scanf("%d", &num);
  } while (num < min || num > max);
  return num;
}

void shuffle(int *arr, size_t n) { //This function takes an array and a size_t parameter
  // Fisher-Yates shuffle
  for (size_t i = n - 1; i > 0; i--) { 
    size_t j = rand() % (i + 1);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void play_numarical_lotto(int *selected_numbers, int *computer_numbers, int *score) { //This is the function for Numerical Lotto
  printf("\nPlaying Numarical Lotto...\n");	 // It takes the selected numbers and number

  for (int i = 0; i < 6; i++) {
  	// Prompt the user to enter a number in the range 1 to NUM_LOTTO_MAX
    // and store it in the selected_numbers array
    selected_numbers[i] = read_int_in_range(1, NUM_LOTTO_MAX);
  }

  for (int i = 0; i < 6; i++) {
  	// Generate 6 numbers in the range 1 to NUM_LOTTO_MAX
    // and store them in the computer_numbers array
    computer_numbers[i] = i + 1;
  }
	
   // Shuffle the computer_numbers array
  shuffle(computer_numbers, 6);

  int hits = 0;
  for (int i = 0; i < 6; i++) {
  	// Check if the element in selected_numbers at index i is equal
    // to the element in computer_numbers at index i
    if (selected_numbers[i] == computer_numbers[i]) {
    // If they are equal, increment hits
      hits++;
    }
  }
  
	// Print out the selected numbers, computer's numbers, and the number of hits
  printf("Your numbers: ");
  for (int i = 0; i < 6; i++) {
    printf("%d ", selected_numbers[i]);
  }
  printf("\nComputer's numbers: ");
  for (int i = 0; i < 6; i++) {
    printf("%d ", computer_numbers[i]);
}
printf("\nHits: %d\n", hits);
	
	// Use a switch statement to add a certain number of points to the score
	// based on the number of hits
	switch (hits) {
		case 6:
			*score += POINTS_NUM_LOTTO_6;
			break;
		case 5:
			*score += POINTS_NUM_LOTTO_5;
			break;
		case 4:
			*score += POINTS_NUM_LOTTO_4;
			break;
		case 3:
			*score += POINTS_NUM_LOTTO_3;
			break;
	}
}

void play_lucky_ball(int *selected_numbers, int *computer_numbers, int *score) { //This is the function for Lucky Ball
	printf("\nPlaying Lucky Ball...\n"); //It takes the selected numbers, computer numbers and score as input

	// Prompt the user to enter a number in the range 1 to NUM_LUCKY_MAX
	for (int i = 0; i < 5; i++) {
		selected_numbers[i] = read_int_in_range(1, NUM_LUCKY_MAX);
	}
	selected_numbers[5] = read_int_in_range(1, NUM_LUCKY_EXTRA_MAX);

	for (int i = 0; i < 5; i++) {
		computer_numbers[i] = i + 1;
	}
	computer_numbers[5] = rand() % NUM_LUCKY_EXTRA_MAX + 1;

	shuffle(computer_numbers, 5);

	int hits = 0;
	for (int i = 0; i < 5; i++) {
		if (selected_numbers[i] == computer_numbers[i]) {
			hits++;
		}
	}
		if (selected_numbers[5] == computer_numbers[5]) {
			hits++;
		}

	printf("Your numbers: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", selected_numbers[i]);
	}
	printf("%d\n", selected_numbers[5]);
	printf("Computer's numbers: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", computer_numbers[i]);
	}
	printf("%d\n", computer_numbers[5]);
	printf("Hits: %d\n", hits);

	switch (hits) {
		case 6:
			*score += POINTS_LUCKY_5_AND_1;
			break;
		case 5:
			*score += POINTS_LUCKY_5;
			break;
		case 4:
			*score += POINTS_LUCKY_4_AND_1;
			break;
		case 3:
			*score += POINTS_LUCKY_4;
			break;
		case 2:
			*score += POINTS_LUCKY_3_AND_1;
			break;
		case 1:
			*score += POINTS_LUCKY_3;
			break;
		case 0:
			*score += POINTS_LUCKY_2_AND_1;
			break;
	}
}

void play_super_lotto(int *selected_numbers, int *computer_numbers, int * score) {
	printf("\nPlaying Super Lotto...\n");

	for (int i = 0; i < 6; i++) {
		selected_numbers[i] = read_int_in_range(1, NUM_SUPER_MAX);
	}

	for (int i = 0; i < 6; i++) {
		computer_numbers[i] = i + 1;
	}

	shuffle(computer_numbers, 6);

	int hits = 0;
	for (int i = 0; i < 6; i++) {
		if (selected_numbers[i] == computer_numbers[i]) {
			hits++;
		}
	}

	printf("Your numbers: ");
	for (int i = 0; i < 6; i++) {
		printf("%d ", selected_numbers[i]);
	}
	printf("\nComputer's numbers: ");
	for (int i = 0; i < 6; i++) {
		printf("%d ", computer_numbers[i]);
	}
	printf("\nHits: %d\n", hits);

	switch (hits) {
		case 6:
			*score += POINTS_SUPER_6;
			break;
		case 5:
			*score += POINTS_SUPER_5;
			break;
		case 4:
			*score += POINTS_SUPER_4;
			break;
		case 3:
			*score += POINTS_SUPER_3;
			break;
	}
	}

int main(void) {
	srand(time(NULL)); // Seed the random number generator with the current time

	int choice, score = 0; //Choice variable and the score first initiliazed at 0
	int selected_numbers[6], computer_numbers[6]; // Declare arrays to store the selected numbers and the computer's numbers
	char play_again; //char variable for the user to decide if he/she's going to continue playing the game

	do {
		printf("\nLOTTERY GAMES MENU\n"); //Creating the main menu
		printf("1. Play Numerical Lotto\n");
		printf("2. Play Lucky Ball\n");
		printf("3. Play Super Lotto\n");
		printf("4. Exit\n");
		printf("(Your total reward: %d points)\n", score);
		printf("Enter your choice: ");
		scanf("%d", &choice); // Choice must be 1-2-3-4 or it gives a error message

	switch (choice) { //Switch case statement for the each game
  		case 1:
    		play_numarical_lotto(selected_numbers, computer_numbers, &score); // Play the Numarical Lotto game
    		printf("Play again (Y/N)? ");
    		do {
      			scanf(" %c", &play_again);
    		} while (play_again != 'Y' && play_again != 'y' && play_again != 'N' && play_again != 'n');
    		break;
  		case 2:
    		play_lucky_ball(selected_numbers, computer_numbers, &score); // Play the Lucky Ball game
    		printf("Play again (Y/N)? ");
    		do {
      			scanf(" %c", &play_again);
    		} while (play_again != 'Y' && play_again != 'y' && play_again != 'N' && play_again != 'n');
    		break;
  		case 3:
    		play_super_lotto(selected_numbers, computer_numbers, &score); // Play the Super Lotto game
    		printf("Play again (Y/N )? ");
			do {
				scanf(" %c", &play_again);
			} while (play_again != 'Y' && play_again != 'y' && play_again != 'N' && play_again != 'n');
			break;
		case 4: //Exit the program and return 0
			printf("Exiting program...\n");
			return 0;
		default: //If user inputs other than 1-2-3-4, it says invalid choice.
			printf("Invalid choice. Please try again.\n");
	}
	} while (choice != 4 || (choice >= 1 && choice <= 3 && play_again == 'Y') || (choice >= 1 && choice <= 3 && play_again == 'y'));

	return 0;
}

