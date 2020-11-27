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
//every time this function is called it runs a round of betting
void BettingRound(double pot, double player_money[], int playernum, int players_folded[4]);
double GetPlayerBet();
double MakeCPUBet();

//This is the new function that draws random cards. it can add a card to either a players hand or the table.
void DrawRandomCard(int card_drawn[], int cards_already_drawn[][13]);
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
		//stores whether a play is folded
		//-1 is fold 1
		int players_folded[4] = {0,0,0,0};
		//deals the cards to players
		//PLAYER 1
		DrawRandomCard(card_drawn, cards_already_drawn);
		player1cards[0][0] = card_drawn[0];
		player1cards[0][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player1cards[1][0] = card_drawn[0];
		player1cards[1][1] = card_drawn[1];
		//PLAYER 2
		DrawRandomCard(card_drawn, cards_already_drawn);
		player2cards[0][0] = card_drawn[0];
		player2cards[0][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player2cards[1][0] = card_drawn[0];
		player2cards[1][1] = card_drawn[1];
		//PLAYER 3
		DrawRandomCard(card_drawn, cards_already_drawn);
		player3cards[0][0] = card_drawn[0];
		player3cards[0][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player3cards[1][0] = card_drawn[0];
		player3cards[1][1] = card_drawn[1];
		//PLAYER 4
		DrawRandomCard(card_drawn, cards_already_drawn);
		player4cards[0][0] = card_drawn[0];
		player4cards[0][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		player4cards[1][0] = card_drawn[0];
		player4cards[1][1] = card_drawn[1];


		//NEED TO ADD A DISPLAY CARDS TO THE REAL PLAYERS HERE, MAKE THIS IN A FUNCTION
		printf("CARD 1: %d, %d\n", player1cards[0][0], player1cards[0][1]);
		printf("CARD 2: %d, %d\n", player1cards[1][0], player1cards[1][1]);
		//HERE we enter the first round of betting
		BettingRound(pot, player_money, playerNum, players_folded);
		//first round of betting ends
		printf("\n\nTHE FLOP\n\n");
		//deals the FLOP(3 cards to the community cards)
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[0][0] = card_drawn[0];
		communitycards[0][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[1][0] = card_drawn[0];
		communitycards[1][1] = card_drawn[1];
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[2][0] = card_drawn[0];
		communitycards[2][1] = card_drawn[1];
		//HERE we enter the second round of betting
		BettingRound(pot, player_money, playerNum, players_folded);
		printf("\n\nTHE RIVER\n\n");
		//second round of beeting ends
		//we deal 1 more card to the comunity pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[3][0] = card_drawn[0];
		communitycards[3][1] = card_drawn[1];
		//here we enter the third round of betting
		BettingRound(pot, player_money, playerNum, players_folded);
		//third round of betting ends
		printf("\n\nTHE DRAW\n\n");
		//we deal 1 more last card to the community pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[4][0] = card_drawn[0];
		communitycards[4][1] = card_drawn[1];
		//last round of betting
		BettingRound(pot, player_money, playerNum, players_folded);
		//determine who has won
		printf("\n\nEND ROUND\n\n");
		//distrubute the money to the winner, or split in case of muttiple winner

		//clean up stuff
		//clear the player_bets--THIS MIGHT NEED TO BE DONE BETWEEN EVERY ROUND OF BETTING
		//clear the cards drawn
		//ask if they want to go again
		keep_playing = 'n';
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

void DrawRandomCard(int card_drawn[], int cards_already_drawn[][13]) {
	do {
		//Draws a random suit
		card_drawn[0] = rand() % 4;
		//Draws a random number value card
		card_drawn[1] = rand() % 13;
	} while(cards_already_drawn[card_drawn[0]][card_drawn[1]] == 1);//this checks if the card drawn has already been drawn
	//sets the card drawn to true in our cards already drawn matrix
	cards_already_drawn[card_drawn[0]][card_drawn[1]] = 1;
}
void BettingRound(double pot, double player_money[], int playernum, int players_folded[]) {
	//stores the current max of the bets IE what you would need to call to
	double current_max = 0;
	//stores each players current bets for the round
	double playerbets[4] = {0,0,0,0};
	//stores the number of players that are done with beeting
	int players_done_betting = 0;
	do {
		for (int i = 0; i < playernum; i++) { //player bets
			if (players_folded[i] == 0) {
				double their_bet = GetPlayerBet();
				if (their_bet == -1.0) { //THEY FOLDED
					players_folded[i] = their_bet;
				} else if (playerbets[i] + their_bet == current_max) {//THEY CALLED
					playerbets[i] += their_bet;
					player_money[i] -= their_bet;
					pot += their_bet;
				} else { //THEY RAISED
					playerbets[i] += their_bet;
					player_money[i] -= their_bet;
					current_max = playerbets[i];
					pot += their_bet;
				}
			}
		}
		for (int i = playernum; i < 4; i++) {//CPU BETS
			//CPUS always call
			double their_bet = current_max - playerbets[i];
			playerbets[i] += their_bet;
			player_money[i] -= their_bet;
			pot += their_bet;
		}
		printf("Currently bets are\nPlayer 1: %lf\n\nPlayer 2: %lf\n\nPlayer 3: %lf\n\nPlayer 4: %lf\n\n", playerbets[0], playerbets[1], playerbets[2], playerbets[3]);
		players_done_betting = 0;
		for(int i = 0; i < 4; i++) {
			if (players_folded[i] == -1) {//That player folded
				players_done_betting++;
			} else if (playerbets[i] == current_max) {//that player has called
				players_done_betting++;
			}
		}
	} while(players_done_betting < 4);
}
double GetPlayerBet() {
	double player_bet;
	printf("Enter your bet, to fold enter -1.\nBet: ");
	scanf("%lf", &player_bet);
	return player_bet;
}