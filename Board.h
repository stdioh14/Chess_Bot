#ifndef BITBOARD
#define BITBOARD
#include "Board.h"
#include <string>
#include <vector>
using namespace std;

typedef struct {
    string engine_color;
    string color;
    bool force_mode;
    unsigned long long int current_form;
    unsigned long long int en_passant = 0;
    bool first_move_king = true;
    bool first_move_rook1 = true;
    bool first_move_rook2 = true;
    bool castled = false;
    bool queen_moved = false;
    unsigned char attacked = 0;
    unsigned char defended = 0;
} BitBoard;

typedef struct chess {
    BitBoard white_pawns; // pioni albi
    BitBoard white_rooks; // turnuri albe
    BitBoard white_knights; // cai albi
    BitBoard white_bishops; // nebuni albi
    BitBoard white_queen; // regina alba
    BitBoard white_king; // regele alb
    
    BitBoard black_pawns;
    BitBoard black_rooks;
    BitBoard black_knights;
    BitBoard black_bishops;
    BitBoard black_queen;
    BitBoard black_king;

    BitBoard black_board;
    BitBoard white_board;
    BitBoard board;
    bool endgame = false;
    bool opening = true;

    unsigned long long crt_hash;
} ChessBoard;

typedef struct {
    ChessBoard table;
    int player;
    string move;
} ChessBoardState;

class Board {
    public:
        void xboard();
        BitBoard reset_pieces_position(string type, string color);
        void reset_all_pieces(ChessBoard &board);

        BitBoard set_engine_color(string color, BitBoard &board);
        string piece_type(unsigned long long int piece_location, ChessBoard board);
        
        void resign(BitBoard board);
        void protover();
        BitBoard new_board();
        BitBoard set_to_start();
        BitBoard force_mode_on(BitBoard &board);
        BitBoard force_mode_off(BitBoard &board);
};

class Moves {
    public: 
        vector<string> quiet;
        vector<string> good_captures;
        vector<string> bad_captures;
        vector<string> even_captures;
};

void update_board(ChessBoard &chess);

#endif 