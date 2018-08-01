/**
 * @file t3.h
 * @brief header file for t3.c
 *
 * @author Luke Rindels
 * @date August 1, 2018
 */

#ifndef HANG_H
#define HANG_H

#define LEN 1024 // buffer length
#define SIZE 3 // size of game board

#define C1  "\x1b[31m"
#define C2  "\x1b[34m"
#define RESET "\x1b[0m"

#define S1 88
#define S2 79

struct board_t {
    char board[SIZE][SIZE];
};

enum player {
    P1 = 1, P2 = 2
};

enum state {
    PLAYING, WIN1, WIN2, DRAW
};

struct board_t init_board();
void print_board(struct board_t board, int score1, int score2);
struct board_t player_move(struct board_t board, int player, int score1, int score2);
int check_board(struct board_t board);
#endif
