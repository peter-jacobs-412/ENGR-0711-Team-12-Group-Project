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
//randomCard draws a card and CheckRand makes sure the card drawn isn't already drawn
void randomCard(int, int, int[][2], int[][2], int[][2], int[][2]);
int CheckRand(int, int, int[][2], int[][2], int[][2], int[][2]);

//randomCommunityCard draws community cards and CheckRandCommunity makes sure the community cards drawn aren't already drawn
void randomCommunityCard(int, int[][2]);
int CheckRandCommunity(int, int[][2]);

//main
int main() {
	//seeding for random number
	unsigned seed = 7;
	srand(seed);
	
	Directions();
	RunTexasHoldem();
	
	return 0;
}

//function definitions
//directions and welcoming to game
void Directions(void)
{
	printf("Welcome! This is a standard game of Texas Holdem. \nThe objective of the game is to have the best poker hand of everyone playing. \n");
	printf("In this game the ace has a low value instead of high, so it is only 1. \nThere is also a max of 4 players. \n\n");
	printf("Face number values are: \n\t1-Clubs \n\t2-Diamonds \n\t3-Hearts \n\t4-Spades \n\n");
	printf("Card Numbers are the same except: \n\t1-Ace \n\t11-Jack \n\t12-Queen \n\t13-King \n\n");
}

//this function runs the game and houses most of the other functions
// the order of dealings also goes into this
void RunTexasHoldem(void)
{
	//Variables
	//player bets
	double playerbets[4];
	//players cards
	//the first column holds the suite and second column is value
	//two private/hole cards for each player
	int player1cards[2][2], player2cards[2][2], player3cards[2][2], player4cards[2][2];

	//Five community cards
	//the first column holds suite and second column holds value
	int communitycards[5][2];

	//player choice function
	//i only made it a max of 4 players
	int playerNum, i, correct;
	playerNum = playerChoice();
	DefineBet(playerNum, playerbets);
	
	//start of game
	//opening round dealing of cards
	//first deal for participating players
	printf("First Deal: \n");
	for(i = 1; i <= playerNum; i++)
	{
		do
		{
			randomCard(i, 1, player1cards, player2cards, player3cards, player4cards);
			correct = CheckRand(i,1, player1cards, player2cards, player3cards, player4cards);
		}while(correct == 1);
		switch (i)
		{
			case 1:
			printf("\tP1: Face = %d Value = %d \n", player1cards[0][0], player1cards[0][1]);
			break;
			case 2:
			printf("\tP2: Face = %d Value = %d \n", player2cards[0][0], player2cards[0][1]);
			break;
			case 3:
			printf("\tP3: Face = %d Value = %d \n", player3cards[0][0], player3cards[0][1]);
			break;
			case 4:
			printf("\tP4: Face = %d Value = %d \n", player4cards[0][0], player4cards[0][1]);
			break;
		}
	}
	
	//deal for cpu's (no display to screen)
	for(i = 4; i > playerNum; i--)
	{
		do
		{
			randomCard(i, 1, player1cards, player2cards, player3cards, player4cards);
			correct = CheckRand(i,1, player1cards, player2cards, player3cards, player4cards);
		}while(correct == 1);
	}
	
	//second deal
	printf("\nSecond Deal:\n");
	for(i = 1; i <= playerNum; i++)
	{
		do
		{
			randomCard(i, 2, player1cards, player2cards, player3cards, player4cards);
			correct = CheckRand(i,2, player1cards, player2cards, player3cards, player4cards);
		}while(correct == 1);
		switch (i)
		{
			case 1:
			printf("\tP1: Face = %d Value = %d \n", player1cards[1][0], player1cards[1][1]);
			break;
			case 2:
			printf("\tP2: Face = %d Value = %d \n", player2cards[1][0], player2cards[1][1]);
			break;
			case 3:
			printf("\tP3: Face = %d Value = %d \n", player3cards[1][0], player3cards[1][1]);
			break;
			case 4:
			printf("\tP4: Face = %d Value = %d \n", player4cards[1][0], player4cards[1][1]);
			break;
		}
	}
	
	//second deal for cpu's
	for(i = 4; i > playerNum; i--)
	{
		do
		{
			randomCard(i, 2, player1cards, player2cards, player3cards, player4cards);
			correct = CheckRand(i,2, player1cards, player2cards, player3cards, player4cards);
		}while(correct == 1);
	}

	//The Flop
	//Dealer shows three community cards
	do
	{
		randomCommunityCard(1, communitycards);
		correct = CheckRandCommunity(1, communitycards);
	}while(correct == 1);

}

//choose number of players and returns number needed for betting
int playerChoice(void)
{
	int playerNum;
	do
	{
		printf("How many players are playing the game? (1-4) ");
		scanf("%d", &playerNum);
	}while(playerNum > 4 && playerNum < 1);
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
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4;
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
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4;
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
		printf("Player %d is the dealer, player %d is the small blind, and player %d is the big blind", dealer, (dealer+1)%4, (dealer+2)%4;
		printf("What is Player %d's bet? ", (dealer+3)%4);
		scanf("%lf", playerbets[(dealer+3)%4]);
		break;
	}
}

//this function essentially works as drawing the card for the player
//playeridentifier selects what player the system is drawing for
//draw is identifying what round is being drawn now
//for example draw would be 1 if it is the first round of drawings
void randomCard(int playeridentifier, int draw, int player1cards[][2], int player2cards[][2], int player3cards[][2], int player4cards[][2])
{
	int r, face, value;
	r = rand();
	face = (r% 4)+1;
	value = (r% 13) +1;
	switch(playeridentifier)
	{
		case 1:
		player1cards[draw - 1][0] = face;
		player1cards[draw - 1][1] = value;
		break;
		
		case 2:
		player2cards[draw - 1][0] = face;
		player2cards[draw - 1][1] = value;
		break;
		
		case 3:
		player3cards[draw - 1][0] = face;
		player3cards[draw - 1][1] = value;
		break;
		
		case 4:
		player4cards[draw - 1][0] = face;
		player4cards[draw - 1][1] = value;
		break;
	}
}

//this function checks to make sure the card chosen by randomCard is not already chosen
int CheckRand(int playeridentifier, int draw, int player1cards[][2], int player2cards[][2], int player3cards[][2], int player4cards[][2])
{
	int correct = 1;
	switch(playeridentifier)
	{
		case 1:
		if(player1cards[draw-1][0] == player2cards[draw - 1][0] && player1cards[draw-1][1] == player2cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player1cards[draw-1][0] == player3cards[draw - 1][0] && player1cards[draw-1][1] == player3cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player1cards[draw-1][0] == player4cards[draw - 1][0] && player1cards[draw-1][1] == player4cards[draw - 1][1])
		{
			correct = 1;
		}
		else
		{
			correct = 0;
		}
		break;
		
		case 2:
		if(player2cards[draw-1][0] == player1cards[draw - 1][0] && player2cards[draw-1][1] == player1cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player2cards[draw-1][0] == player3cards[draw - 1][0] && player2cards[draw-1][1] == player3cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player2cards[draw-1][0] == player4cards[draw - 1][0] && player2cards[draw-1][1] == player4cards[draw - 1][1])
		{
			correct = 1;
		}
		else
		{
			correct = 0;
		}
		break;
		
		case 3:
		if(player3cards[draw-1][0] == player1cards[draw - 1][0] && player3cards[draw-1][1] == player1cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player3cards[draw-1][0] == player2cards[draw - 1][0] && player3cards[draw-1][1] == player2cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player3cards[draw-1][0] == player4cards[draw - 1][0] && player3cards[draw-1][1] == player4cards[draw - 1][1])
		{
			correct = 1;
		}
		else
		{
			correct = 0;
		}
		break;
		
		case 4:
		if(player4cards[draw-1][0] == player1cards[draw - 1][0] && player4cards[draw-1][1] == player1cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player4cards[draw-1][0] == player3cards[draw - 1][0] && player4cards[draw-1][1] == player3cards[draw - 1][1])
		{
			correct = 1;
		}
		else if(player4cards[draw-1][0] == player3cards[draw - 1][0] && player4cards[draw-1][1] == player3cards[draw - 1][1])
		{
			correct = 1;
		}
		else
		{
			correct = 0;
		}
		break;
	}
	return(correct);
}

//This function draws the community cards
void randomCommunityCard(int draw, int communitycards[][2])
{
	int r, face, value, face2, value2, face3, value3;
	r = rand();
	face = (r% 4)+1;
	value = (r% 13) +1;
	switch(draw)
	{
		case 1: //The Flop
		
		do {
			face2 = (r% 4)+1;
			value2 = (r% 13) +1;
		} while (face == face2 && value == value2);
		
		do {
			face3 = (r% 4)+1;
			value3 = (r% 13) +1;
		} while ( (face == face3 && value == value3) || (face2 == face3 && value2 == value3) );
	
		communitycards[0][0] = face;
		communitycards[0][1] = value;
		communitycards[1][0] = face2;
		communitycards[1][1] = value2;
		communitycards[2][0] = face3;
		communitycards[2][1] = value3;
		break;
		
		case 2: //The Turn
		communitycards[3][0] = face;
		communitycards[3][1] = value;
		break;
		
		case 3: //The River
		communitycards[4][0] = face;
		communitycards[4][1] = value;
		break;
	}
}

//this function checks to make sure the cards/card chosen by randomCommunityCard is not already chosen
int CheckRandCommunity(int draw, int communitycards[][2])
{
	int correct = 0;
	switch(draw)
	{
		case 1: //The Flop
		{
			for (i=0; i<3; i++)
			{
				for (j=0; j<2; j++)
				{
					if (communitycards[i][0] == player1cards[j][0] && communitycards[i][1] == player1cards[j][1])
						correct = 1;
					if (communitycards[i][0] == player2cards[j][0] && communitycards[i][1] == player2cards[j][1])
						correct = 1;
					if (communitycards[i][0] == player3cards[j][0] && communitycards[i][1] == player3cards[j][1])
						correct = 1;
					if (communitycards[i][0] == player4cards[j][0] && communitycards[i][1] == player4cards[j][1])
						correct = 1;
				}
			}
		}
		break;

		case 2: //The Turn
			for (j=0; j<2; j++)
			{
				if (communitycards[3][0] == player1cards[j][0] && communitycards[3][1] == player1cards[j][1])
					correct = 1;
				if (communitycards[3][0] == player2cards[j][0] && communitycards[3][1] == player2cards[j][1])
					correct = 1;
				if (communitycards[3][0] == player3cards[j][0] && communitycards[3][1] == player3cards[j][1])
					correct = 1;
				if (communitycards[3][0] == player4cards[j][0] && communitycards[3][1] == player4cards[j][1])
					correct = 1;
			}
		break;

		case 3: //The River
			for (j=0; j<2; j++)
			{
				if (communitycards[4][0] == player1cards[j][0] && communitycards[4][1] == player1cards[j][1])
					correct = 1;
				if (communitycards[4][0] == player2cards[j][0] && communitycards[4][1] == player2cards[j][1])
					correct = 1;
				if (communitycards[4][0] == player3cards[j][0] && communitycards[4][1] == player3cards[j][1])
					correct = 1;
				if (communitycards[4][0] == player4cards[j][0] && communitycards[4][1] == player4cards[j][1])
					correct = 1;
				}
			}
		break;
	}
	return(correct);
}
