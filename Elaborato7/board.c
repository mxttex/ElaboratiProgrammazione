#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <stdlib.h>

//controllo bordo mappa generico
void check_map_corners(int board[][GAME_COLS], unsigned int ro, unsigned int col) {

}

int num_neighbor_mines(int board[][GAME_COLS], unsigned int ro, unsigned int col) {

    int neighbor_mines = 0;
    int i, j;
    for (i = ro-1; i <= ro+1; i++) {
        for (j = col-1; j <= col+1; j++) {
            neighbor_mines = (board[i][j] == UNKN_MINE) ? + 1 : + 0;
        }
    }

    return neighbor_mines;
}

//controllo che la posizione i,j sia sempre libera assieme al suo intorno
void check_start(int board[][GAME_COLS],unsigned int ro, unsigned int col, int min_left) {
    //contatori per cicli for per matrice
    int i, j;
    //parto dalla posizione data - 1 così scorro quello precedente, l'attuale e il successivo (controllo 3*3)

    for (i = ro-1; i <= ro+1; i++) {
        for (j = col-1; j <= col+1; j++)
            if (board[i][j] != UNKN_FREE) {
                board[i][j] = UNKN_FREE;
                min_left++;
            }
    }

    board[ro][col] = C0;
}

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {

    //riempio la matrice con un random e continuo finché non c'è il numero totale di mine.
    //quindi viene ripetuta più volte controllando che in caso quella cella non sia occupata da una mina.
    int r, c;
    srand(time(NULL));

    int random_mines;
    int mines_left = num_mines;
    while (mines_left != 0) {
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                random_mines = rand() % 3;

                check_start(board, i, j, mines_left);

                if (board[r][c] != UNKN_MINE && random_mines == 1) {
                    board[r][c] = UNKN_MINE;
                    mines_left--;
                }
                    
                else
                    board[r][c] = UNKN_FREE;
            }
        }
    }
}


/*
* Flags/unflags the i,j position in the board. Returns
* - -1 if the position was flagged. Removes the flag
* -  0 if the position is already displyed
* -  1 if the position is not flagged and not already
*    displayed. Puts a flag in position i,j.
*/
int flag_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    switch (board[i][j]) {
        case FLAG_MINE:
            board[i][j] == UNKN_MINE;
            return -1;
        case FLAG_FREE:
            board[i][j] == UNKN_FREE;
            return -1;
        case UNKN_FREE:
            board[i][j] == FLAG_FREE;
            return 1;
        case UNKN_MINE:
            board[i][j] == FLAG_MINE;
            return 1;
    }

    return 0;
}

/*
* Displays position i,j in the board. Returns the number of
* displayed cells or -1 if i,j contains a mine.
*/

int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    int mines = num_neighbor_mines(board, i, j);

    if (board[i][j] != UNKN_FREE && board[i][j] != UNKN_MINE)
        return 0;

    switch (board[i][j]) {
        case UNKN_MINE:
            board[i][j] == MINE;
            return -1;
        case UNKN_FREE:
            //switch da cambiare
            switch (mines) {
            case 1:
                board[i][j] == C1;
            case 2:
                board[i][j] == C2;
            case 3:
                board[i][j] == C3;
            case 4:
                board[i][j] == C4;
            case 5:
                board[i][j] == C5;
            case 6:
                board[i][j] == C6;
            case 7:
                board[i][j] == C7;
            case 8:
                board[i][j] == C8;
            default:
                board[i][j] == C0;


            }

    }

}


/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    return 0;
}


#endif