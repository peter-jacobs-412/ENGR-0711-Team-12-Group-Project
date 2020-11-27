//Write the texas holdem game here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//function prototypes
//i put a little bit more detail at the bottom for each function's definitions
//displays opening directions
void Directions(void);
//runs game(same idea as in Connect4 to clear up main)
void RunTexasHoldem(void);
//chooses how many players are playing
int playerChoice(void);
//betting function(still working on)
void DefineBet(int, double[]);

//This is the new function that draws random cards. it can add a card to either a players hand or the table.
void DrawRandomCard(int card_drawn[2], int cards_already_drawn[4][13]);
/* ##################################################################### */
/* ################################ MAIN ############################### */
/* ##################################################################### */
int main() {
	//seeding for random number
	unsigned seed = 7;
	srand(seed);
	
	Directions();
	RunTexasHoldem();
	
	return 0;
}

/* ##################################################################### */
/* ######################## function definitions ####################### */
/* ##################################################################### */
//directions and welcoming to game
void Directions(void) {
	printf("Welcome! This is a standard game of Texas Holdem. \nThe objective of the game is to have the best poker hand of everyone playing. \n");
	printf("In this game the ace has a low value instead of high, so it is only 1. \nThere is also a max of 4 players. \n\n");
	printf("Face number values are: \n\t1-Clubs \n\t2-Diamonds \n\t3-Hearts \n\t4-Spades \n\n");
	printf("Card Numbers are the same except: \n\t1-Ace \n\t11-Jack \n\t12-Queen \n\t13-King \n\n");
}

//this function runs the game and houses most of the other functions
// the order of dealings also goes into this
void RunTexasHoldem(void) {
	//player bets
	double playerbets[4];
	//stores the pot of the current round
	double pot;
	//stores each players money total
	double player_money[4];
	//This stores cards that have been drawn this round
	int cards_already_drawn[4][13];
	//stores the card drawn by the draw card function
	int card_drawn[2];
	//players cards
	//the first column holds the suite and second column is value
	//two private/hole cards for each player
	int player1cards[2][2], player2cards[2][2], player3cards[2][2], player4cards[2][2];
	//Five community cards
	//the first column holds suite and second column holds value
	int communitycards[5][2];
	//player choice function
	//i only made it a max of 4 players
	int playerNum;
	//gets the number of non CPU players
	playerNum = playerChoice();
	//stores if they want to keep playing
	char keep_playing = 'y';
	
	//game flow
	do {
		//deals the cards to players
		//PLAYER 1
		DrawRandomCard(card_drawn, cards_already_drawn);
		player1cards[0][0] = card_drawn[0];
		player1cards[0][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player1cards[1][0] = card_drawn[0];
		player1cards[1][1] = cards_already_drawn[1];
		//PLAYER 2
		DrawRandomCard(card_drawn, cards_already_drawn);
		player2cards[0][0] = card_drawn[0];
		player2cards[0][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player2cards[1][0] = card_drawn[0];
		player2cards[1][1] = cards_already_drawn[1];
		//PLAYER 3
		DrawRandomCard(card_drawn, cards_already_drawn);
		player3cards[0][0] = card_drawn[0];
		player3cards[0][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player3cards[1][0] = card_drawn[0];
		player3cards[1][1] = cards_already_drawn[1];
		//PLAYER 4
		DrawRandomCard(card_drawn, cards_already_drawn);
		player4cards[0][0] = card_drawn[0];
		player4cards[0][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player4cards[1][0] = card_drawn[0];
		player4cards[1][1] = cards_already_drawn[1];


		//NEED TO ADD A DISPLAY CARDS TO THE REAL PLAYERS HERE, MAKE THIS IN A FUNCTION

		//HERE we enter the first round of betting
		//first round of betting ends
		//deals the FLOP(3 cards to the community cards)
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[0][0] = card_drawn[0];
		communitycards[0][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[1][0] = card_drawn[0];
		communitycards[1][1] = cards_already_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[2][0] = card_drawn[0];
		communitycards[2][1] = cards_already_drawn[1];
		//HERE we enter the second round of betting
		//second round of beeting ends
		//we deal 1 more card to the comunity pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[3][0] = card_drawn[0];
		communitycards[3][1] = cards_already_drawn[1];
		//here we enter the third round of betting
		//third round of betting ends
		//we deal 1 more last card to the community pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[4][0] = card_drawn[0];
		communitycards[4][1] = cards_already_drawn[1];
		//last round of betting

		//determine who has won

		//distrubute the money to the winner, or split in case of muttiple winner

		//clean up stuff
		//clear the player_bets--THIS MIGHT NEED TO BE DONE BETWEEN EVERY ROUND OF BETTING
		//clear the cards drawn
		//ask if they want to go again
	} while(keep_playing == 'y');


}

//choose number of players and returns number needed for betting
int playerChoice(void) {
	int playerNum;
	do {
		printf("How many players are playing the game? (1-4) ");
		scanf("%d", &playerNum);
	} while(playerNum > 4 && playerNum < 1);
	printf("\n%d player game \n\n", playerNum);
	return(playerNum);
}

//defines the initial bets for the players and cpu's if applicable
//i am not too familiar with betting in this game so I will leave it to one of you guys to figure it out
//i made this function for the bets, but I don't know how the blinds and different roles factor in
void DefineBet(int playerNum, double playerbets[])
{
	//players are player1=0, player2=1, player3=2, and player4=3, going clockwise
	int dealer = 0; //Start with first player=0 as dealer
	int smallblind = (dealer+1)%4;
	int bigblind = (dealer+2)%4;


	//Define initial bets
	switch(playerNum)
	{
		//one player 3 cpu
		case 1:
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, smallblind, bigblind);
		playerbets[smallblind] = 1;
		playerbets[bigblind] = 2;
		//cpus are players 1, 2, and 3
		if ((dealer+3)%4 == 4)
		{
			printf("What is Player %d's bet? ", (dealer+3)%4);
			scanf("%lf", playerbets[(dealer+3)%4]);
		}
		else
		{
			playerbets[(dealer+3)%4] = 2;
		}
		
		
		
		break;
		
		//two players two cpu
		//cpus are players 1 and 2
		case 2:
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4);
		if ((dealer+3)%4 >= 3)
		{
			printf("What is Player %d's bet? ", (dealer+3)%4);
			scanf("%lf", playerbets[(dealer+3)%4]);
		}
		else
		{
			playerbets[(dealer+3)%4] = 2;
		}
		
		break;
		
		//three players one cpu
		//cpu is player 1
		case 3:
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4);
		if ((dealer+3)%4 >= 2)
		{
			printf("What is Player %d's bet? ", (dealer+3)%4);
			scanf("%lf", playerbets[(dealer+3)%4]);
		}
		else
		{
			playerbets[(dealer+3)%4] = 2;
		}
		break;
		
		//four players no cpu
		case 4:
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4);
		printf("What is Player %d's bet? ", (dealer+3)%4);
		scanf("%lf", playerbets[(dealer+3)%4]);
		break;
	}
}
void DrawRandomCard(int card_drawn[2], int cards_already_drawn[4][13]) {
	do {
		//Draws a random suit
		card_drawn[0] = rand() % 4;
		//Draws a random number value card
		card_drawn[1] = rand() % 13;
	} while(cards_already_drawn[card_drawn[0]][card_drawn[1]] == 1);//this checks if the card drawn has already been drawn
	//sets the card drawn to true in our cards already drawn matrix
	cards_already_drawn[card_drawn[0]][card_drawn[1]] = 1;
}
