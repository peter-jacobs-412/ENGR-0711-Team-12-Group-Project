//Team 12 Group Project
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/* ##################################################################### */
/* ############################ ERROR CODES ############################ */
/* ##################################################################### */
//001-Move entered by player out of range
//
//test
//
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DECLARATIONS ################### */
/* ##################################################################### */
//Everything needed to run the connect 4 game will be contained inside this function to keep main cleaner.
//Depending on how we do the game this might have an input for Player Vs AI or Player Vs Player.
//One idea i have for this if we make it an option is its an int 0 is player 1 is easy Ai 2 is medium AI 3 is Hard AI
void RunConnectFour();

//This function displays the board
//currently very simple formattting we should try and improve this if possible
void DisplayBoard(int board[][7]);

//This Function gets the players move and then passes it back to be executed
int GetPlayerMove();

//This Function Adds the move decided by the player or the AI
//Returns false if the move cant be executed
bool DoMove(int player, int colummn, int board[][7]);

//this sets of functions checks how many pieces of equal value are in that direction given a location in the array
//when working with the functions wee will use iterators of i and j for the rows and coluummns specfically.
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
int CheckWinner();

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
/* ##################################################################### */
/* ################################ MAIN ############################### */
/* ##################################################################### */
int main() {
    //asks them which game they want to play
    int which_game;
    printf("Would You like to play GAME 1 or GAME 2? (1/2): ");
    scanf("%d", &which_game);
    RunConnectFour();
    //Error check
    while (which_game != 1 && which_game != 2) {
        printf("ERROR! Please enter 1 for GAME 1 or 2 for GAME 2: ");
        scanf("%d", &which_game);
    }
}
/* ##################################################################### */
/* #################### GAME 1 FUNCTION DEFINITIONS #################### */
/* ##################################################################### */
void RunConnectFour() {
    bool game_over = false;
    //This stores the board and all of its values 0-empty 1-player 1 2-player 2
    int board[6][7] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};
    while (game_over == false) {
        game_over = !DoMove(1, GetPlayerMove(), board);
        game_over = !DoMove(2, GetPlayerMove(), board);
        DisplayBoard(board);
        TesterFunction(board);
    }
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
int CheckWinner() {

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
//
//
//
//
//
//
