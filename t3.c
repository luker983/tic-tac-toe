/**
 * @file t3.c
 * @brief tic tac toe game
 *
 * @author Luke Rindels
 * @date August 1, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "t3.h"

int main()
{
    struct board_t board;
    char buf[LEN];
    char c;
    int player = P1; 
    int state;    
    int score1 = 0;
    int score2 = 0;

    // new game loop
    while (1) {
        player = P1;
        state = PLAYING;
        board = init_board();
        
        // current game loop
        while (state == PLAYING) {
            // clear screen and print board
            system("clear");
            print_board(board, score1, score2);
            // player makes selection
            board = player_move(board, player, score1, score2);
            state = check_board(board);
            // switch player
            player = (player == P1) ? P2 : P1;
        }
        
        system("clear");
        print_board(board, score1, score2);

        // game over options
        switch (state) {
        case WIN1:
            printf("Player 1 Wins!!!\n");       
            score1++;
            break;
        case WIN2:
            printf("Player 2 Wins!!!\n");
            score2++;
            break;
        case DRAW:
            printf("Draw!!!\n");
        }   

        // play again?
        printf("Would you like to play again? [y/n]\n");
        fgets(buf, LEN, stdin);
        sscanf(buf, "%c", &c);

        if (c == 'n') {
            break;
        } 
    }
    
    // final score printing
    system("clear");
    printf("\n-------- Final Score --------\n");
    printf(C1 "\nPlayer 1: %d" RESET, score1);
    printf(C2 "\tPlayer 2: %d\n\n" RESET, score2);
    return 0;
}

/**
 * initializes the board with coordinates
 *
 * @return initialized board
 */
struct board_t init_board()
{
    struct board_t board;

    int i;
    int j;
    int coord = 1;

    // fills each space with a number (ascending) starts at 1
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board.board[i][j] = coord + '0';
            coord++;
        }
    }

    return board;
}

/**
 * prints board and score
 *
 * @param board the current game board
 * @param score1 player 1's score
 * @param score2 player 2's score
 */
void print_board(struct board_t board, int score1, int score2) 
{
    int i;
    int j;
    
    puts("");
    printf("\n------- Tic Tac Toe -------\n\n");
    printf(C1 "---- Player 1 Score: %d\n" RESET, score1);
    printf(C2 "---- Player 2 Score: %d\n\n" RESET, score2);
    printf("\t");
    // loops through the board and prints out each coordinate/taken space
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board.board[i][j] == S1) {
                printf(C1 " %c " RESET, board.board[i][j]);
            } else if (board.board[i][j] == S2) { 
                printf(C2 " %c " RESET, board.board[i][j]);
            } else {
                printf(" %c ", board.board[i][j]); 
            }
            if (j == SIZE - 1) {
                if (i != SIZE - 1) {
                    printf("\n\t___|___|___\n\t");
                }
            } else {
                printf("|");
            } 
        }
    }
    puts("\n"); 
}

/**
 * player selects move here
 *
 * @param board the board in play
 * @param player whose turn it is
 * @param score1 player 1's score
 * @param score2 player 2's score
 * @return new board
 */
struct board_t player_move(struct board_t board, int player, int score1, int score2)
{
    char buf[LEN];
    int coord = 0;
    int i;
    int j;

    // loop for error checking
    while (coord == 0) {
        // player selects coordinate
        printf("Player %d's Turn\n", player);
        printf("Pick a spot on the board:\n");
        fgets(buf, LEN, stdin);
        sscanf(buf, "%d", &coord);
      
        // formulas to convert game coordinate to array indices
        i = (coord - 1) / SIZE;
        j = (coord + 2) % SIZE;
        // DEBUG: printf("coord = %d\tboard = %d\n", coord, board.board[(coord - 1) / SIZE][(coord + 2) % SIZE]); 
        if (board.board[i][j] - 48 != coord) {
            system("clear");
            printf("That is not a valid move, please try again"); 
            print_board(board, score1, score2);
            coord = 0;
        } 
    }

    // places symbol on board depending on player turn
    board.board[i][j] = (player == P1) ? S1 : S2;

    return board;
}

/**
 * checks for a winning move or full board
 *
 * @param board the board in play
 * @return a game state
 */
int check_board(struct board_t board)
{
    int i;
    int j;
    int x;

    int state = PLAYING;
        
    // Horizontal rules
    for (i = 0; i < SIZE; i++) {
        x = board.board[i][0];
        for (j = 1; j < SIZE; j++) {
            if (board.board[i][j] != x) {
                break;
            }
            if (j == SIZE - 1) {
                return state = (x == S1) ? WIN1 : WIN2;
            }
        }
    }

    // Vertical rules
    for (j = 0; j < SIZE; j++) {
        x = board.board[0][j];
        for (i = 1; i < SIZE; i++) {
            if (board.board[i][j] != x) {
                break;
            }
            if (i == SIZE - 1) {
                return state = (x == S1) ? WIN1 : WIN2;
            }
        }
    }
    
    // Diagonal rules
    x = board.board[0][0];
    for (i = 1; i < SIZE; i++) {
        if (board.board[i][i] != x) {
            break;
        }
        if (i == SIZE - 1) {
            return state = (x == S1) ? WIN1 : WIN2;
        }
    }
    
    x = board.board[0][SIZE - 1];
    for (i = 1; i < SIZE; i++) {
        if (board.board[i][SIZE - (i + 1)] != x) {
            break;
        }
        if (i == SIZE - 1) {
            return state = (x == S1) ? WIN1 : WIN2;
        }
    }

    // Draw rule
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board.board[i][j] != S1 && board.board[i][j] != S2) {
                return PLAYING;
            }
            if (i == SIZE - 1 && j == SIZE - 1) {
                return DRAW;
            }
        }
    }

    // should never reach this point
    return PLAYING;
}
