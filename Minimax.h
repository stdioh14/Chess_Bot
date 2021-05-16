#ifndef MINIMAX
#define MINIMAX

#include "Legal_Moves.h"
#include "Board.h"
#include "Transposition.h"

extern HashTable tt;

#define INF (1 << 25)
#define PAWNS 0
#define ROOKS 1
#define KNIGHTS 2
#define BISHOPS 3
#define QUEENS 4
#define KINGS 5

vector<string> get_attack_moves(ChessBoard, string, int &, int &);
Moves get_possible_moves(ChessBoard &, string, int &, int &);

unsigned long long apply_move(ChessBoard &, string, string);
vector<string> gameOver(ChessBoard, int);
string alfabeta_root(ChessBoard, int, int);
int alfabeta_negamax (ChessBoard &, int, int, int, int, bool);
int Quiescence(ChessBoard, int, int, int);
#endif