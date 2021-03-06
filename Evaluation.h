#ifndef EVALUATION 
#define EVALUATION

#include "Board.h"
#include "Legal_Moves.h"

#define P 100
#define R 500
#define N 320
#define B 330
#define Q 1100
#define K 20000

const int WHITE_PAWN_EVAL[64] = {
0,  0,  0,  0,  0,  0,  0,  0,
5, 10, 10,-20,-20, 10, 10,  5,
5, -5,-10,  0,  0,-10, -5,  5,
0,  0,  0, 20, 20,  0,  0,  0,
5,  5, 10, 25, 25, 10,  5,  5,
10, 10, 20, 30, 30, 20, 10, 10,
50, 50, 50, 50, 50, 50, 50, 50,
70, 70, 70, 70, 70, 70, 70, 70
};

const int BLACK_PAWN_EVAL[64] = {
70, 70, 70, 70, 70, 70, 70, 70,
50, 50, 50, 50, 50, 50, 50, 50,
10, 10, 20, 30, 30, 20, 10, 10,
5,  5, 10, 25, 25, 10,  5,  5,
0,  0,  0, 20, 20,  0,  0,  0,
5, -5,-10,  0,  0,-10, -5,  5,
5, 10, 10,-20,-20, 10, 10,  5,
0,  0,  0,  0,  0,  0,  0,  0
};

const int WHITE_KNIGHT_EVAL[64] = {
-50,-40,-30,-30,-30,-30,-40,-50,
-40,-20,  0,  0,  0,  0, -20,-40,
-30,  0, 10, 15, 15, 10,  0, -30,
-30,  5, 15, 20, 20, 15,  5, -30,
-30,  0, 15, 20, 20, 15,  0, -30,
-30,  5, 10, 15, 15, 10,  5, -30,
-40,-20,  0,  5,  5,  0,-20, -40,
-50,-40,-30,-30,-30,-30,-40,-50
};

const int BLACK_KNIGHT_EVAL[64] = {
-50,-40,-30,-30,-30,-30,-40,-50, 
-40,-20,  0,  5,  5,  0,-20, -40,
-30,  5, 10, 15, 15, 10,  5, -30,
-30,  0, 15, 20, 20, 15,  0, -30,
-30,  5, 15, 20, 20, 15,  5, -30,
-30,  0, 10, 15, 15, 10,  0, -30,
-40,-20,  0,  0,  0,  0, -20,-40,
-50,-40,-30,-30,-30,-30, -40,-50
};

const int WHITE_BISHOP_EVAL[64] = {
-20,-10,-10,-10,-10,-10,-10, -20,
-10,  5,  0,  0,  0,  0,  5, -10,
-10, 10, 10, 10, 10, 10, 10, -10,
-10,  0, 10, 10, 10, 10,  0, -10,
-10,  5,  5, 10, 10,  5,  5, -10,
-10,  0,  5, 10, 10,  5,  0, -10,
-10,  0,  0,  0,  0,  0,  0, -10,
-20,-10,-10,-10,-10,-10,-10,-20
};

const int BLACK_BISHOP_EVAL[64] = {
-20,-10,-10,-10,-10,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0, -10,
-10,  0,  5, 10, 10,  5,  0, -10,
-10,  5,  5, 10, 10,  5,  5, -10,
-10,  0, 10, 10, 10, 10,  0, -10,
-10, 10, 10, 10, 10, 10, 10, -10,
-10,  5,  0,  0,  0,  0,  5, -10,
-20,-10,-10,-10,-10,-10,-10, -20
};

const int WHITE_ROOK_EVAL[64] = {
 0,  0,  0,  0,  0,  0,  0,  0,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
 5, 10, 10, 10, 10, 10, 10,  5,
 0,  0,  0,  5,  5,  0,  0,  0
};

const int BLACK_ROOK_EVAL[64] = {
 0,  0,  0,  0,  0,  0,  0,  0,
 5, 10, 10, 10, 10, 10, 10,  5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
 0,  0,  0,  5,  5,  0,  0,  0
};

const int WHITE_QUEEN_EVAL[64] = {
-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  5,  0,  0,  0,  0,-10,
-10,  5,  5,  5,  5,  5,  0,-10,
  0,  0,  5,  5,  5,  5,  0, -5,
 -5,  0,  5,  5,  5,  5,  0, -5,
-10,  0,  5,  5,  5,  5,  0,-10,
-10,  0,  0,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20
};

const int BLACK_QUEEN_EVAL[64] = {
-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5,  5,  5,  5,  0,-10,
 -5,  0,  5,  5,  5,  5,  0, -5,
  0,  0,  5,  5,  5,  5,  0, -5,
-10,  5,  5,  5,  5,  5,  0,-10,
-10,  0,  5,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20
};

const int BLACK_KING_EVAL[64] = {
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-20,-30,-30,-40,-40,-30,-30,-20,
-10,-20,-20,-20,-20,-20,-20,-10,
 20, 20,  0,  0,  0,  0, 20, 20,
 20, 30, 10,  0,  0, 10, 30, 20
};

 const int WHITE_KING_EVAL[64] = {
 20, 30, 10,  0,  0, 10, 30, 20,
 20, 20,  0,  0,  0,  0, 20, 20,
-10,-20,-20,-20,-20,-20,-20,-10,
-20,-30,-30,-40,-40,-30,-30,-20,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30
};

const int BLACK_KING_ENDGAME[64] = {
-50,-40,-30,-20,-20,-30,-40,-50,
-30,-20,-10,  0,  0,-10,-20,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-30,  0,  0,  0,  0,-30,-30,
-50,-30,-30,-30,-30,-30,-30,-50
};

const int WHITE_KING_ENDGAME[64] = {
-50,-30,-30,-30,-30,-30,-30,-50,
-30,-30,  0,  0,  0,  0,-30,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 30, 40, 40, 30,-10,-30,
-30,-10, 20, 30, 30, 20,-10,-30,
-30,-20,-10,  0,  0,-10,-20,-30,
-50,-40,-30,-20,-20,-30,-40,-50
};

// Evaluation functions
int pawn_eval(ChessBoard, string, unsigned long long);
int table_value(ChessBoard, int);
int evaluate(ChessBoard, int,int,int,int,int);
int evaluateBoardScore(ChessBoard, int,int,int,int, int);

#endif