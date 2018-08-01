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

    while (1) {
        player = P1;
        state = PLAYING;
        board = init_board();
        
        while (state == PLAYING) {
            system("clear");
            print_board(board);

            board = player_move(board, player);
            state = check_board(board);
     
            player = (player == P1) ? P2 : P1;
        }
        
        system("clear");
        print_board(board);

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

    
        printf("Would you like to play again? [y/n]\n");
        fgets(buf, LEN, stdin);
        sscanf(buf, "%c", &c);

        if (c == 'n') {
            break;
        } 
    }
    
    system("clear");
    printf("\n-------- Final Score --------\n");
    printf("\nPlayer 1: %d\tPlayer 2: %d\n\n", score1, score2);
    return 0;
}

struct board_t init_board()
{
    struct board_t board;

    int i;
    int j;
    int coord = 1;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board.board[i][j] = coord + '0';
            coord++;
        }
    }

    return board;
}

void print_board(struct board_t board) 
{
    int i;
    int j;
    
    puts("");
    printf("\n------- Tic Tac Toe -------\n\n");
    printf("\t");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %c ", board.board[i][j]);
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

struct board_t player_move(struct board_t board, int player)
{
    char buf[LEN];
    int coord = 0;
    int i;
    int j;

    while (coord == 0) {
        printf("Player %d's Turn\n", player);
        printf("Pick a spot on the board:\n");
        fgets(buf, LEN, stdin);
        sscanf(buf, "%d", &coord);
      
        i = (coord - 1) / SIZE;
        j = (coord + 2) % SIZE;
        // DEBUG: printf("coord = %d\tboard = %d\n", coord, board.board[(coord - 1) / SIZE][(coord + 2) % SIZE]); 
        if (board.board[i][j] - 48 != coord) {
            system("clear");
            printf("That is not a valid move, please try again"); 
            print_board(board);
            coord = 0;
        } 
    }

    board.board[i][j] = (player == P1) ? S1 : S2;

    return board;
}

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

    return PLAYING;
}
