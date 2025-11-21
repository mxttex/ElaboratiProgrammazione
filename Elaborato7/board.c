#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

//controllo bordo mappa generico
int check_map_corners(int coord) {
    //restituisce tot valori se si è vicino ai bordi o meno
    if (coord < 0)
        return 0;
    else if (coord > GAME_COLS - 1)
        return GAME_COLS - 1;

    return coord;
}

//conta le mine in uno spazio 3x3 
int num_neighbor_mines(int board[][GAME_COLS], unsigned int ro, unsigned int col) {

    int neighbor_mines = 0;
    int i, j;
    int min_x = check_map_corners((int)ro - 1);
    int max_x = check_map_corners((int)ro + 1);

    int min_y = check_map_corners((int)(col)-1);
    int max_y = check_map_corners((int)(col)+1);

    for (i = min_x; i <= max_x; i++) {
        for (j = min_y; j <= max_y; j++) {
            neighbor_mines += (board[i][j] == UNKN_MINE || board[i][j] == FLAG_MINE);
        }
    }

    return neighbor_mines;
}

int num_neighbor_flags(int board[][GAME_COLS], unsigned int ro, unsigned int col) {

    int neighbor_flags = 0;
    int i, j;
    int min_x = check_map_corners((int)ro - 1);
    int max_x = check_map_corners((int)ro + 1);

    int min_y = check_map_corners((int)(col)-1);
    int max_y = check_map_corners((int)(col)+1);
    for (i = min_x; i <= max_x; i++) {
        for (j = min_y; j <= max_y; j++) {
            neighbor_flags += (board[i][j] == FLAG_FREE || board[i][j] == FLAG_MINE);
        }
    }

    return neighbor_flags;
}

int display_cell(int board[][GAME_COLS], unsigned int ro, unsigned int col, int num_disp_cells) {

    int mines = num_neighbor_mines(board, ro, col);
    
    int next_num_disp_cells = num_disp_cells;

    switch (mines) {
    case 1:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C1;
            return next_num_disp_cells + 1;
        }
    case 2:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C2;
            return next_num_disp_cells + 1;
        }
    case 3:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C3;
            return next_num_disp_cells + 1;
        }
    case 4:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C4;
            return next_num_disp_cells + 1;
        }
    case 5:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C5;
            return next_num_disp_cells + 1;
        }
    case 6:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C6;
            return next_num_disp_cells + 1;
        }
    case 7:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C7;
            return next_num_disp_cells + 1;
        }
    case 8:
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C8;
            return next_num_disp_cells + 1;
        }
    case 0:
        
        //ogni volta che è c0, fa il display di tutte le zone intorno (quindi da UNKN_FREE diventa una costante dell'enum)
        //se ritrova un altro c0 in quell'intorno, ripete questa cosa finché non esauriscono i C0 in quegli intorni.
        //infine restituisce il numero di celle displayate (inizio 8, poi somma piano piano quelle che scopre).
        if (board[ro][col] == UNKN_FREE) {
            board[ro][col] = C0;
            next_num_disp_cells += 1;
        }      

        int i, j;
        int min_x = check_map_corners((int)(ro)-1);
        int max_x = check_map_corners((int)ro + 1);

        int min_y = check_map_corners((int)(col)-1);
        int max_y = check_map_corners((int)col + 1);

        for (i = min_x; i <= max_x; i++) {
            for (j = min_y; j <= max_y; j++) {
                if (board[i][j] == UNKN_FREE) {
                    next_num_disp_cells = display_cell(board, i, j, next_num_disp_cells);
                }
            }
        }
        
    }
    return next_num_disp_cells;
}


//controllo che la posizione i,j sia sempre libera assieme al suo intorno
void check_start(int board[][GAME_COLS], unsigned int ro, unsigned int col, int min_left) {
    //contatori per cicli for per matrice
    int i, j;
    int min_x = check_map_corners((int)ro - 1);
    int max_x = check_map_corners((int)ro + 1);

    int min_y = check_map_corners((int)(col)-1);
    int max_y = check_map_corners((int)(col)+1);
    //parto dalla posizione data - 1 così scorro quello precedente, l'attuale e il successivo (controllo 3*3)
    // (i > 0 && i < GAME_ROWS) && (j > 0 && j < GAME_COLS)
    for (i = min_x; i <= max_x; i++) {
        for (j = min_y; j <= max_y; j++) {
            min_left += (board[i][j] != UNKN_FREE);
        }
    }
}

//min_left += (board[i][j] != UNKN_FREE);

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {

    //riempio la matrice con un random e continuo finché non c'è il numero totale di mine.
    //quindi viene ripetuta più volte controllando che in caso quella cella non sia occupata da una mina.
    srand(time(NULL));

    int rnd_x, rnd_y;
    int mines_left = num_mines;
    int k, f;

    for (k = 0; k < GAME_ROWS; k++) {
        for (f = 0; f < GAME_COLS; f++) {
            board[k][f] = UNKN_FREE;
        }
    }

    while (mines_left > 0) {
        rnd_x = rand() % rows;
        rnd_y = rand() % cols;

        check_start(board, i, j, mines_left);

        if (board[rnd_x][rnd_y] != UNKN_MINE) {
            board[rnd_x][rnd_y] = UNKN_MINE;
            mines_left--;
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
        //rimuove i flag
    case FLAG_MINE:
        board[i][j] = UNKN_MINE;
        return -1;
    case FLAG_FREE:
        board[i][j] = UNKN_FREE;
        return -1;
        //aggiunge i flag
    case UNKN_FREE:
        board[i][j] = FLAG_FREE;
        return 1;
    case UNKN_MINE:
        board[i][j] = FLAG_MINE;
        return 1;
    }

    return 0;
}

/*
* Displays position i,j in the board. Returns the number of
* displayed cells or -1 if i,j contains a mine.
*/

int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    int total_cells_displayed = 0;

    if (board[i][j] != UNKN_FREE && board[i][j] != UNKN_MINE)
        return 0;

    switch (board[i][j]) {
    case UNKN_MINE:
        board[i][j] = MINE;
        return -1;
    case UNKN_FREE:
        total_cells_displayed = display_cell(board, i, j, total_cells_displayed);
        //da fare funzione ricorsiva per C0

    }

    return total_cells_displayed;

}


/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    int total_cells_expanded = 0;
    int neighbor_flags = num_neighbor_flags(board, i, j);
    int neighbor_mines = num_neighbor_mines(board, i, j);

    // contatori for per vedere se nell'intorno di i,j ci sono mine non flaggate
    int k, f;
    int min_x = check_map_corners((int)i - 1);
    int max_x = check_map_corners((int)i + 1);

    int min_y = check_map_corners((int)(j)-1);
    int max_y = check_map_corners((int)j + 1);

    if (board[i][j] != UNKN_FREE && board[i][j] != UNKN_MINE) {
        for (k = min_x; k <= max_x ; k++) {
            for (f = min_y; f <= max_y; f++) {
                //il numero di flag è uguale al numero definito dalla costante dell'enumerable ma almeno 1 flag è piazzata male
                //quindi restituisce -1
                if (board[k][f] == UNKN_MINE && neighbor_flags == neighbor_mines) {
                    return -1;
                }
            }
        }

        //se il numero di flag corrisponde al numero definito dalla costante enum allora procede a fare l'expand sfruttando il display_board
        if (neighbor_flags == neighbor_mines) {
            total_cells_expanded = display_cell(board, i, j, total_cells_expanded);
        }
    }

    return total_cells_expanded;
}


#endif

