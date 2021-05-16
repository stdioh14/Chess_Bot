#ifndef LEGAL_MOVES
#define LEGAL_MOVES
#include "Board.h"
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;


typedef struct {  
    string possible_moves[32];
    int number_of_moves;
} Piece;

unsigned int countSetBits(unsigned long long);

class Legal_Moves
{
    public:
        void regular_move_message(string source, string destination);
        void pawn_promotion_message(string source, string destination);
        int index_bit(unsigned long long number);
        unsigned long long int pos_to_64bits(string pos);
        string bits_to_position_string(unsigned long long current_position);
        bool check_first_move(string color, string position) ;
        BitBoard board_type(unsigned long long int position,
                            ChessBoard &chess);

        void make_move(BitBoard &board, unsigned long long int source, 
                unsigned long long int destination);

        void place_piece(BitBoard &board, unsigned long long int source, 
                unsigned long long int destination);

        void make_move(unsigned long long int xboard_move_source, 
                            unsigned long long int xboard_move_destination,
                            ChessBoard &chess);

        void delete_piece(string attacked_color, BitBoard &white_board, 
                            BitBoard &black_board, 
                            BitBoard &AttackedBoard, 
                            unsigned long long destination) ;

        void attack_move (unsigned long long int destination,
                           ChessBoard &chess);

        void attack_move_pawn (unsigned long long int destination,
                           ChessBoard &chess);

        void xboard_move(char input[], ChessBoard &chess);

        string choose_random_piece(string color, BitBoard piece_board, 
                            BitBoard black_board, BitBoard white_board) ;

        bool no_moves_left(string color, BitBoard pawns, BitBoard rooks,
                    BitBoard knights, BitBoard bishops, BitBoard queen, 
                    BitBoard king, BitBoard black_board, BitBoard white_board,
                    ChessBoard &chess);

        bool is_check (string color, unsigned long long int king_position,
                    ChessBoard &chess);

        bool multiple_positions_check(string color, unsigned long long int king_position, 
                                unsigned long long int destination, ChessBoard &chess);

        void castling(string move, ChessBoard &chess);

        void pawn_promotion(string color, BitBoard &color_board, ChessBoard &chess,
                    unsigned long long int source, unsigned long long int destination);

        int no_pieces_rook_king(string, BitBoard, BitBoard, BitBoard);
        //void random_engine_move(ChessBoard &chess);

        Piece pawn_moves(bool first_move, string current_pos,string color,
                    ChessBoard &chess);

        Piece knight_moves(string current_pos,string color,
                    ChessBoard &chess);

        Piece rooks_moves(string current_pos,string color,
                    ChessBoard &chess);

        Piece bishop_moves(string current_pos,string color,ChessBoard &chess);

        Piece qb_moves(string current_pos,string color,ChessBoard &chess);

        Piece qr_moves(string current_pos,string color,ChessBoard &chess);



        Piece king_moves(string pos, string color, ChessBoard &chess);
        
        Piece queen_moves(string current_pos,string color, ChessBoard &chess);
};


#endif 