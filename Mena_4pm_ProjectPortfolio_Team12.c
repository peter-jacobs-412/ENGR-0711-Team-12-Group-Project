//Team 12 Group Project, Peter Jacobs, Aaron Wang, Arun Guduru
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DECLARATIONS ################### */
/* ##################################################################### */
//Everything needed to run the connect 4 game will be contained inside this function to keep main cleaner.
void RunConnectFour();

//This function displays the board
//currently very simple formattting we should try and improve this if possible
void DisplayBoard(int board[][7]);

//This Function gets the players move and then passes it back to be executed
int GetPlayerMove();

//This Function Adds the move decided by the player or the AI
//Returns false if the move cant be executed
bool DoMove(int player, int colummn, int board[][7]);

//this set of functions checks how many pieces of equal value are in that direction given a location in the array
//when working with the functions we will use iterators of i and j for the rows and columns specifically.
//note that becasue of the way array indexes work south is defined as postive i direction and east is defined as postive j
int CheckNorth(int row, int col, int board[][7]);
int CheckEast(int row, int col, int board[][7]);
int CheckSouth(int row, int col, int board[][7]);
int CheckWest(int row, int col, int board[][7]);
int CheckNorthEast(int row, int col, int board[][7]);
int CheckSouthEast(int row, int col, int board[][7]);
int CheckSouthWest(int row, int col, int board[][7]);
int CheckNorthWest(int row, int col, int board[][7]);

//This Function Should return a value between 1 and 4 based on the maximum amount of tiles in a row at the given space. it dtermines the given space by being passed a i and a j value
int CheckSpot(int row, int col, int board[][7]);

//This function should check the board for any winning sequences of 4 or more tiles in a row to detect any wins and saves the location of any wins in winningSpace
bool CheckWinner(int board[][7], int winningSpace[]);

//this function is meant for debugging and testing purposes it will have a bunch of diffrent code in it all of which can be commented out in order to test specifc things
void TesterFunction(int board[][7]);
//
/* ====================================================== */
/* ==================== GAME 1 NOTES ==================== */
/* ====================================================== */
//The Board will use three diffrent values in its array 0-empty 1-PLayer1(red) 2-Player2(yellow)
//
//
/* ##################################################################### */
/* ################### GAME 2 FUNCTION DECLARATIONS #################### */
/* ##################################################################### */
//
//displays opening directions
void Directions(void);

//runs game(same idea as in Connect4 to clear up main)
void RunTexasHoldem(void);

//chooses how many players are playing
int playerChoice(void);

//betting function(still working on)
//every time this function is called it runs a round of betting
//returns the new pot
double BettingRound(double pot, double player_money[], int playernum, int players_folded[4]);

//gets a player's bet
double GetPlayerBet();

//displays players cards to the players
void DisplayCards(int player1cards[][2], int player2cards[][2], int player3cards[][2], int player4cards[][2]);

//This is the new function that draws random cards. It can add a card to either a players hand or the table.
void DrawRandomCard(int card_drawn[], int cards_already_drawn[][13]);

//this function distrubutes the money to the player(s) that won
void DistrubuteMoney(double pot, double player_money[]);
//this function displays players money
void DisplayMoney(double player_money[], double pot);
/* ##################################################################### */
/* ################################ MAIN ############################### */
/* ##################################################################### */
int main() {
    //asks them which game they want to play
    int which_game;
    printf("Would You like to play GAME 1 (Connect Four) or GAME 2 (Texas hold 'em)? (1/2): ");
    scanf("%d", &which_game);
    //Error check
    while (which_game != 1 && which_game != 2) {
        printf("ERROR! Please enter 1 for GAME 1 or 2 for GAME 2: ");
        scanf("%d", &which_game);
    }
    unsigned int seed;
    printf("please enter a random integer seed for the games: ");
    scanf("%d", &seed);
    srand(seed);
    switch(which_game) {
        case 1:
            RunConnectFour();
            break;
        case 2:
            RunTexasHoldem();
            break;
    }
}
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DEFINITIONS #################### */
/* ##################################################################### */
void RunConnectFour() {
    bool game_over = false;
    bool valid_move = false;
    //This stores the board and all of its values 0-empty 1-player 1 2-player 2
    int board[6][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};
	int winning_space[2];
    while (game_over == false) {
        DisplayBoard(board);
        do {
            valid_move = DoMove(1, GetPlayerMove(), board);
        } while (valid_move == false);
		game_over = CheckWinner(board, winning_space);
		if (game_over == true) break;
        DisplayBoard(board);
        do {
            valid_move = DoMove(2, GetPlayerMove(), board);
        } while (valid_move == false);
		game_over = CheckWinner(board, winning_space);
    }
	printf("GAME OVER!!!\n");
	printf("PLAYER %d WON WITH A CONNECT 4 AT %d, %d\n", board[winning_space[0]][winning_space[1]], 6 - winning_space[0], winning_space[1] + 1);
	DisplayBoard(board);
}
int GetPlayerMove() {
    printf("Enter Your Move: ");
    int move_colummn;
    scanf("%d", &move_colummn);
    while (move_colummn < 1 || move_colummn > 7) {
        printf("ERROR 001 MOVE OUT OF RANGE PLEASE TRY AGAIN: ");
        scanf("%d", &move_colummn);
    }
    return move_colummn - 1;
}
bool DoMove(int player, int colummn, int board[][7]) {
    for (int i = 6; i >= 0; i--) {
        if (board[i][colummn] == 0) {
            board[i][colummn] = player;
            return true;
        }
    }
    return false;
}
void DisplayBoard(int board[][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n\n\n\n\n");
    }
}
int CheckNorth(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    if (i == 0) {
        return 1;
    }
    while (board[i][col] == board[i-1][col]) {
        count++;
        i--;
        if (i == 0) {
            break;
        }
    }
    return count;
}
int CheckEast(int row, int col, int board[][7]) {
    int count = 1;
    int j = col;
    if (j == 6) {
        return 1;
    }
    while (board[row][j] == board[row][j+1]) {
        count++;
        j++;
        if (j == 6) {
            break;
        }
    }
    return count;
}
int CheckSouth(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    if (i  == 5) {
        return 1;
    }
    while (board[i][col] == board[i+1][col]) {
        count++;
        i++;
        if (i == 5) {
            break;
        }
    }
    return count;
}
int CheckWest(int row, int col, int board[][7]) {
    int count = 1;
    int j = col;
    if (j == 0) {
        return 1;
    }
    while (board[row][j] == board[row][j-1]) {
        count++;
        j--;
        if (j == 0) {
            break;
        }
    }
    return count;
}
int CheckNorthEast(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    int j = col;
    if (i == 0 || j == 6) {
        return 1;
    }
    while (board[i][j] == board[i-1][j+1]) {
        count++;
        i--;
        j++;
        if (i == 0 || j == 6) {
            break;
        }
    }
    return count;
}
int CheckSouthEast(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    int j = col;
    if (i == 5 || j == 6) {
        return 1;
    }
    while (board[i][j] == board[i+1][j+1]) {
        count++;
        i++;
        j++;
        if (i == 5 || j == 6) {
            break;
        }
    }
    return count;
}
int CheckSouthWest(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    int j = col;
    if (i == 5 || j == 0) {
        return 1;
    }
    while (board[i][j] == board[i+1][j-1]) {
        count++;
        i++;
        j--;
        if (i == 5 || j == 0) {
            break;
        }
    }
    return count;
}
int CheckNorthWest(int row, int col, int board[][7]) {
    int count = 1;
    int i = row;
    int j = col;
    if (i == 0 || j == 0) {
        return 1;
    }
    while (board[i][j] == board[i-1][j-1]) {
        count++;
        i--;
        j--;
        if (i == 0 || j == 0) {
            break;
        }
    }
    return count;
}
int CheckSpot(int row, int col, int board[][7]) {
    int outputs[8];
    outputs[0] = CheckNorth(row, col, board);
    outputs[1] = CheckNorthEast(row, col, board);
    outputs[2] = CheckEast(row, col, board);
    outputs[3] = CheckSouthEast(row, col, board);
    outputs[4] = CheckSouth(row, col, board);
    outputs[5] = CheckSouthWest(row, col, board);
    outputs[6] = CheckWest(row, col, board);
    outputs[7] = CheckNorthWest(row, col, board);
    int max = 0;
    for (int i = 0; i < 8; i++) {
        if (outputs[i] > max) {
            max = outputs[i];
        }
    }
    return max;
}
bool CheckWinner(int board[][7], int winningSpace[]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
			if (board[i][j] != 0) {
				if (CheckSpot(i, j, board) >= 4) {
					//If a win is detected, return true and save the location the win was at in the winningSpace array
					winningSpace[0] = i;
					winningSpace[1] = j;
					return true;
				}
			}
        }
    }
    //If no win is detected, return false
    return false;
}
void TesterFunction(int board[][7]) {
    //check the return value of north west east and south for a given i and j location
    int row, colummn;
    printf("Enter row and col: ");
    scanf("%d%d", &row, &colummn);
    printf("At row = %d and colummn = %d: \n", row, colummn);
    printf("East is %d\nWest is %d\nNorth is %d\nSouth is %d\n", CheckEast(row, colummn, board), CheckWest(row, colummn, board), CheckNorth(row, colummn, board), CheckSouth(row, colummn, board));

}
/* ##################################################################### */
/* #################### GAME 2 FUNCTION DEFINITIONS #################### */
/* ##################################################################### */
//directions and welcoming to game
void Directions(void) {
	printf("Welcome! This is a standard game of Texas Holdem. \nThe objective of the game is to have the best poker hand of everyone playing. \n");
	printf("In this game the ace has a low value instead of high, so it is only 1. \nThere is also a max of 4 players. \n\n");
	printf("Face number values are: \n\t1-Clubs \n\t2-Diamonds \n\t3-Hearts \n\t4-Spades \n\n");
	printf("Card Numbers are the same except:\n\t11-Jack \n\t12-Queen \n\t13-King \n\t14-Ace\n\n");
}

//this function runs the game and houses most of the other functions
// the order of dealings also goes into this
void RunTexasHoldem(void) {
	//displays directions
	Directions();
	//stores each players money total
	double player_money[4] = {5000, 5000, 5000, 5000};
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
	//stores whether a play is folded
	//-1 is fold 1
	int players_folded[4];
	//This stores cards that have been drawn this round
	int cards_already_drawn[4][13];
	//stores the pot of the current round
	double pot = 0;
	//game flow
	do {
		//resets certain vars
		for (int i = 0; i < 4; i++) {
			players_folded[i] = 0;
			for (int j = 0; j < 13; j++) {
				cards_already_drawn[i][j] = 0;
			}
		}
		pot = 0;
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
		//Displays players cards to them
		DisplayCards(player1cards, player2cards, player3cards, player4cards);
		//displays players money to them
		DisplayMoney(player_money, pot);
		//HERE we enter the first round of betting
		pot = BettingRound(pot, player_money, playerNum, players_folded);
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
		//displays the cards on the table
		printf("\nTable Cards: \n");
		printf("Card 1: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[0][0], communitycards[0][1]);
		printf("Card 2: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[1][0], communitycards[1][1]);
		printf("Card 3: \n");
		printf("\tSuit: %d Value: %d\n\n", communitycards[2][0], communitycards[2][1]);
		//displays players money to them
		DisplayMoney(player_money, pot);
		//HERE we enter the second round of betting
		pot = BettingRound(pot, player_money, playerNum, players_folded);
		//second round of beeting ends
		printf("\n\nTHE RIVER\n\n");
		//we deal 1 more card to the community pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[3][0] = card_drawn[0];
		communitycards[3][1] = card_drawn[1];
		//displays table cards
		printf("\nTable Cards: \n");
		printf("Card 1: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[0][0], communitycards[0][1]);
		printf("Card 2: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[1][0], communitycards[1][1]);
		printf("Card 3: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[2][0], communitycards[2][1]);
		printf("Card 4: \n");
		printf("\tSuit: %d Value: %d\n\n", communitycards[3][0], communitycards[3][1]);
		//displays players money to them
		DisplayMoney(player_money, pot);
		//here we enter the third round of betting
		pot = BettingRound(pot, player_money, playerNum, players_folded);
		//third round of betting ends
		printf("\n\nTHE DRAW\n\n");
		//we deal 1 more last card to the community pile
		DrawRandomCard(card_drawn, cards_already_drawn);
		communitycards[4][0] = card_drawn[0];
		communitycards[4][1] = card_drawn[1];
		//displays table cards
		printf("\nTable Cards: \n");
		printf("Card 1: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[0][0], communitycards[0][1]);
		printf("Card 2: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[1][0], communitycards[1][1]);
		printf("Card 3: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[2][0], communitycards[2][1]);
		printf("Card 4: \n");
		printf("\tSuit: %d Value: %d\n", communitycards[3][0], communitycards[3][1]);
		printf("Card 5: \n");
		printf("\tSuit: %d Value: %d\n\n", communitycards[4][0], communitycards[4][1]);
		//displays players money to them
		DisplayMoney(player_money, pot);
		//last round of betting
		pot = BettingRound(pot, player_money, playerNum, players_folded);
		//determine who has won
		printf("\n\nEND ROUND\n\n");
		//distrubute the money to the winner, or split in case of muttiple winner
		DistrubuteMoney(pot, player_money);
		//displays players money to them
		DisplayMoney(player_money, 0);
		//ask if they want to go again
		do {
			printf("Would you like to go again? (y/n)");
			scanf(" %c", &keep_playing);
		} while(keep_playing != 'y' && keep_playing != 'n');
	} while(keep_playing == 'y');
	printf("GAME OVER\n");
	//displays players money to them
	DisplayMoney(player_money, 0);
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

void DrawRandomCard(int card_drawn[], int cards_already_drawn[][13]) {
	do {
		//Draws a random suit
		card_drawn[0] = rand() % 4 + 1;
		//Draws a random number value card
		card_drawn[1] = rand() % 13 + 2;
	} while(cards_already_drawn[card_drawn[0]][card_drawn[1]] == 1);//this checks if the card drawn has already been drawn
	//sets the card drawn to true in our cards already drawn matrix
	cards_already_drawn[card_drawn[0]][card_drawn[1]] = 1;
}
double BettingRound(double pot, double player_money[], int playernum, int players_folded[]) {
	//stores the current max of the bets IE what you would need to call to
	double current_max = 0;
	//stores each players current bets for the round
	double playerbets[4] = {0,0,0,0};
	//stores the number of players that are done with beeting
	int players_done_betting = 0;
	do {
		for (int i = 0; i < playernum; i++) { //player bets
			if (players_folded[i] != -1) {
				printf("Player %d \n", i+1);
				double their_bet = GetPlayerBet();
				if (their_bet == -1.0) { //THEY FOLDED
					players_folded[i] = their_bet;
				} else if (playerbets[i] + their_bet == current_max) {//THEY CALLED
					playerbets[i] += their_bet;
					player_money[i] -= their_bet;
				} else { //THEY RAISED
					playerbets[i] += their_bet;
					player_money[i] -= their_bet;
					current_max = playerbets[i];
				}
			}
		}
		for (int i = playernum; i < 4; i++) {//CPU BETS
			//CPUS always call
			double their_bet = current_max - playerbets[i];
			playerbets[i] += their_bet;
			player_money[i] -= their_bet;
		}
		printf("\nCurrently bets are\nPlayer 1: %lf\n\nPlayer 2: %lf\n\nPlayer 3: %lf\n\nPlayer 4: %lf\n\n", playerbets[0], playerbets[1], playerbets[2], playerbets[3]);
		players_done_betting = 0;
		for(int i = 0; i < 4; i++) {
			if (players_folded[i] == -1) {//That player folded
				players_done_betting++;
			} else if (playerbets[i] == current_max) {//that player has called
				players_done_betting++;
			}
		}
	} while(players_done_betting < 4);
	pot = pot + playerbets[0] + playerbets[1] + playerbets[2] + playerbets[3];
	return pot;
}
double GetPlayerBet() {
	double player_bet;
	printf("Enter your bet, to fold enter -1.\nBet: ");
	scanf("%lf", &player_bet);
	return player_bet;
}

//Displays each player's private/hole cards to that player
void DisplayCards(int player1cards[][2], int player2cards[][2], int player3cards[][2], int player4cards[][2]) {
	
	int response;
	
	//Display Player 1's cards
	printf("Make sure only Player 1 is looking at the screen \n");
	do {
		printf("When ready, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	printf("Player 1, here are your hole cards:\n");
	printf("Card 1: \n");
	printf("\tSuit: %d Value: %d\n", player1cards[0][0], player1cards[0][1]);
	printf("Card 2: \n");
	printf("\tSuit: %d Value: %d\n", player1cards[1][0], player1cards[1][1]);
	do {
		printf("When you have finished looking at your cards, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	//Clears the screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	//Display Player 2's cards
		printf("Make sure only Player 2 is looking at the screen \n");
	do {
		printf("When ready, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	printf("Player 2, here are your hole cards:\n");
	printf("Card 1: \n");
	printf("\tSuit: %d Value: %d\n", player2cards[0][0], player2cards[0][1]);
	printf("Card 2: \n");
	printf("\tSuit: %d Value: %d\n", player2cards[1][0], player2cards[1][1]);
	do {
		printf("When you have finished looking at your cards, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	//Clears the screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	//Display Player 3's cards
	printf("Make sure only Player 3 is looking at the screen \n");
	do {
		printf("When ready, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	printf("Player 3, here are your hole cards:\n");
	printf("Card 1: \n");
	printf("\tSuit: %d Value: %d\n", player3cards[0][0], player3cards[0][1]);
	printf("Card 2: \n");
	printf("\tSuit: %d Value: %d\n", player3cards[1][0], player3cards[1][1]);
	do {
		printf("When you have finished looking at your cards, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	//Clears the screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");


	//Display Player 4's cards
	printf("Make sure only Player 4 is looking at the screen \n");
	do {
		printf("When ready, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	printf("Player 4, here are your hole cards:\n");
	printf("Card 1: \n");
	printf("\tSuit: %d Value: %d\n", player4cards[0][0], player4cards[0][1]);
	printf("Card 2: \n");
	printf("\tSuit: %d Value: %d\n", player4cards[1][0], player4cards[1][1]);
	do {
		printf("When you have finished looking at your cards, type \"1\". ");
		scanf("%d", &response);
	} while (response != 1);
	//Clears the screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
void DistrubuteMoney(double pot, double player_money[]) {
	int num_players_won;
	do {
		printf("How Many players won this round?");
		scanf("%d", &num_players_won);
	} while (num_players_won < 1 || num_players_won > 4);
	double money_won = pot / num_players_won;
	int players_won[4];
	switch (num_players_won) {
	case 1:
		printf("Which player won?");
		scanf("%d", &players_won[0]);
		player_money[players_won[0] - 1] += money_won;
		break;
	case 2:
		printf("Which players won? (seperate by a space)");
		scanf("%d%d", &players_won[0], &players_won[1]);
		player_money[players_won[0] - 1] += money_won;
		player_money[players_won[1] - 1] += money_won;
		break;
	case 3:
		printf("Which players won? (seperate by a space)");
		scanf("%d%d%d", &players_won[0], &players_won[1], &players_won[2]);
		player_money[players_won[0] - 1] += money_won;
		player_money[players_won[1] - 1] += money_won;
		player_money[players_won[2] - 1] += money_won;
		break;
	case 4:
		printf("Which players won? (seperate by a space)");
		scanf("%d%d%d%d", &players_won[0], &players_won[1], &players_won[2], &players_won[3]);
		player_money[players_won[0] - 1] += money_won;
		player_money[players_won[1] - 1] += money_won;
		player_money[players_won[2] - 1] += money_won;
		player_money[players_won[3] - 1] += money_won;
		break;
	default:
		printf("ERROR NO MONEY DISTRUBTUED");
		break;
	}
}
void DisplayMoney(double player_money[], double pot) {
	printf("\nPlayer 1 Money:\n");
	printf("%lf\n", player_money[0]);
	printf("Player 2 Money:\n");
	printf("%lf\n", player_money[1]);
	printf("Player 3 Money:\n");
	printf("%lf\n", player_money[2]);
	printf("Player 4 Money:\n");
	printf("%lf\n", player_money[3]);
	printf("Pot is:\n");
	printf("%lf\n\n", pot);
}
