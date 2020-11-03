//Team 12 Group Project
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/* ##################################################################### */
/* ############################ ERROR CODES ############################ */
/* ##################################################################### */
//
//
//
//
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DECLARATIONS ################### */
/* ##################################################################### */
void RunConnectFour();
void DisplayBoard(int board[][7]);
//This Function gets the players move and then passes it back to be executed
int GetPlayerMove();
//This Function Adds to move decided by the player or the AI
//Returns false if the move cant be executed
bool DoMove(int player, int colummn, int board[][7]);
int CheckNorth();
int CheckEast();
int CheckSouth();
int CheckWest();
int CheckNorthEast();
int CheckSouthEast();
int CheckSouthWest();
int CheckNorthWest();
int CheckWinner();
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
/* ##################################################################### */
/* ################################ MAIN ############################### */
/* ##################################################################### */
int main() {
    //asks them which game they want to play
    int which_game;
    printf("Would You like to play GAME 1 or GAME 2? (1/2): ");
    scanf("%d", &which_game);
    RunConnectFour();
}
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DEFINITIONS #################### */
/* ##################################################################### */
void RunConnectFour() {
    printf("DID A THING");
    bool game_over = false;
    int board[6][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};
    while (game_over == false) {
        int move_pos = GetPlayerMove();
        game_over = DoMove(1, move_pos, board);
        move_pos = GetPlayerMove();
        game_over = DoMove(2, move_pos, board);
        DisplayBoard(board);
    }

}
int GetPlayerMove() {
    printf("Enter Your Move: ");
    int move_colummn;
    scanf("%d", &move_colummn);
    return move_colummn;
}
bool DoMove(int player, int colummn, int board[][7]) {
    for (int i = 6; i > 0; i--) {
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
int CheckNorth();
int CheckEast();
int CheckSouth();
int CheckWest();
int CheckNorthEast();
int CheckSouthEast();
int CheckSouthWest();
int CheckNorthWest();
int CheckWinner();
/* ##################################################################### */
/* #################### GAME 2 FUNCTION DEFINITIONS #################### */
/* ##################################################################### */
//
//
//
//
//
//