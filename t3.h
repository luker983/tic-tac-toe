/**
 * @file t3.h
 * @brief header file for t3.c
 *
 * @author Luke Rindels
 * @date August 1, 2018
 */

#ifndef HANG_H
#define HANG_H

#define LEN 1024
#define SIZE 3

struct board_t {
    char board[SIZE][SIZE];
};

enum player {
    P1 = 1, P2 = 2
};

enum state {
    PLAYING, WIN1, WIN2, DRAW
};

enum symbols {
    S1 = 88, S2 = 79
};

struct board_t init_board();
void print_board(struct board_t board);
struct board_t player_move(struct board_t board, int player);
int check_board(struct board_t board);
#endif
