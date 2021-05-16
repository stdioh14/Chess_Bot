#include <string>
#include <fstream>
#include "Minimax.h"
#include "Board.h"
#include "Legal_Moves.h"
#include "Evaluation.h"
#include "Transposition.h"
using namespace std;



vector<string> get_attack_moves(ChessBoard chess, string color) {
	unsigned long long int position;
	BitBoard engine_pawns, engine_rooks, engine_knights, engine_bishops;
	BitBoard engine_queen, engine_king, my_board;
	bool first_move;
	string source, destination, move;
	Piece pawn, rook, knight, bishop, queen, king;
	Legal_Moves legal;

	if(color == "black") {
		engine_pawns = chess.black_pawns;
		engine_rooks = chess.black_rooks;
		engine_knights = chess.black_knights;
		engine_bishops = chess.black_bishops;
		engine_queen = chess.black_queen;
		engine_king = chess.black_king;
	} else {
		engine_pawns = chess.white_pawns;
		engine_rooks = chess.white_rooks;
		engine_knights = chess.white_knights;
		engine_bishops = chess.white_bishops;
		engine_queen = chess.white_queen;
		engine_king = chess.white_king;	
	}

	unsigned long long int to;
	vector<string> moves;

	for (int i = 0; i < 64; i++) {
		position = (1ULL << i);
		if ((position & engine_pawns.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			first_move = legal.check_first_move(color, source);
			pawn = legal.pawn_moves(first_move, source, color, chess);
			for (int i = 0; i < pawn.number_of_moves; i++) {
				string dest = pawn.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form)) 
					moves.emplace_back(move);
			}
		} else if ((position & engine_rooks.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			rook = legal.rooks_moves(source, color, chess);
			for (int i = 0; i < rook.number_of_moves; i++) {
				string dest = rook.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form)) 
					moves.emplace_back(move);
			}
		} else if ((position & engine_knights.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			knight = legal.knight_moves(source, color,chess);
			for (int i = 0; i < knight.number_of_moves; i++) {
				string dest = knight.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form)) 
					moves.emplace_back(move);
			}
		} else if ((position & engine_bishops.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			bishop = legal.bishop_moves(source, color, chess);
			for (int i = 0; i < bishop.number_of_moves; i++) {
				string dest = bishop.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form))
					moves.emplace_back(move);
			}
		} else if ((position & engine_queen.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			queen = legal.queen_moves(source, color, chess);
			for (int i = 0; i < queen.number_of_moves; i++) {
				string dest = queen.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form)) 
					moves.emplace_back(move);
			}
		} else if ((position & engine_king.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			king = legal.king_moves(source, color, chess);
			for (int i = 0; i < king.number_of_moves; i++) {
				string dest = king.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form) || (to & chess.black_board.current_form)) 
					moves.emplace_back(move);
			}
		}
	}  
	return moves;
}

int get_move_score(string color, ChessBoard &chess, unsigned long long position) {
	int score = 0;

	if (color == "white") {
		if ((position & chess.white_pawns.current_form) != 0) {
			score += P;
		} else if ((position & chess.white_rooks.current_form) != 0) {
			score += R;
		} else if ((position & chess.white_knights.current_form) != 0) {
			score += N;
		} else if ((position & chess.white_bishops.current_form) != 0) {
			score += B;
		} else if ((position & chess.white_queen.current_form) != 0) {
			score += Q;
		} else if ((position & chess.white_king.current_form) != 0) {
			score += K;
		}
	} else if (color == "black") {
		if ((position & chess.black_pawns.current_form) != 0) {
			score += P;
		} else if ((position & chess.black_rooks.current_form) != 0) {
			score += R;
		} else if ((position & chess.black_knights.current_form) != 0) {
			score += N;
		} else if ((position & chess.black_bishops.current_form) != 0) {
			score += B;
		} else if ((position & chess.black_queen.current_form) != 0) {
			score += Q;
		} else if ((position & chess.black_king.current_form) != 0) {
			score += K;
		}
	}

	return score;
}

Moves get_possible_moves(ChessBoard &chess, string color) {
	unsigned long long int position;
	BitBoard engine_pawns, engine_rooks, engine_knights, engine_bishops;
	BitBoard engine_queen, engine_king, my_board;
	bool first_move;
	string source, destination, move;
	Piece pawn, rook, knight, bishop, queen, king;
	Legal_Moves legal;
	Moves moves;
	int score;

	if(color == "black") {
		engine_pawns = chess.black_pawns;
		engine_rooks = chess.black_rooks;
		engine_knights = chess.black_knights;
		engine_bishops = chess.black_bishops;
		engine_queen = chess.black_queen;
		engine_king = chess.black_king;
	} else {
		engine_pawns = chess.white_pawns;
		engine_rooks = chess.white_rooks;
		engine_knights = chess.white_knights;
		engine_bishops = chess.white_bishops;
		engine_queen = chess.white_queen;
		engine_king = chess.white_king;	
	}

	unsigned long long int to;
	vector<string> killers;
	vector<string> quiet;
	// Pune toate mutarile posibile intr-un vector, pentru fiecare tip de piesa
	for (int i = 0; i < 64; i++) {
		position = (1ULL << i);
		if ((position & engine_pawns.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			first_move = legal.check_first_move(color, source);
			pawn = legal.pawn_moves(first_move, source, color, chess);
			for (int i = 0; i < pawn.number_of_moves; i++) {
				string dest = pawn.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - P;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - P;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		} else if ((position & engine_rooks.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			rook = legal.rooks_moves(source, color, chess);
			for (int i = 0; i < rook.number_of_moves; i++) {
				string dest = rook.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - R;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - R;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		} else if ((position & engine_knights.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			knight = legal.knight_moves(source, color,chess);
			for (int i = 0; i < knight.number_of_moves; i++) {
				string dest = knight.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - N;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - N;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		} else if ((position & engine_bishops.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			bishop = legal.bishop_moves(source, color, chess);
			for (int i = 0; i < bishop.number_of_moves; i++) {
				string dest = bishop.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - B;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - B;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		} else if ((position & engine_queen.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			queen = legal.queen_moves(source, color, chess);
			for (int i = 0; i < queen.number_of_moves; i++) {
				string dest = queen.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - Q;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - Q;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		} else if ((position & engine_king.current_form) != 0) {
			source = legal.bits_to_position_string(position);
			king = legal.king_moves(source, color, chess);
			for (int i = 0; i < king.number_of_moves; i++) {
				string dest = king.possible_moves[i];
				move = source + dest;
				to = legal.pos_to_64bits(dest);
				if((to & chess.white_board.current_form)) {
					score = get_move_score("white", chess, to);
					score = score - K;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else if ((to & chess.black_board.current_form)) {
					score = get_move_score("black", chess, to);
					score = score - K;
					if (score > 0) {
						moves.good_captures.push_back(move);
					} else if (score == 0) {
						moves.even_captures.push_back(move);
					} else {
						moves.bad_captures.push_back(move);
					}
				} else moves.quiet.push_back(move);
			}
		}
	}
	return moves;
}

unsigned long long apply_move(ChessBoard &chess, string move, string color) {
	BitBoard crt_player;
	int col;
	if(color == "white") {
		crt_player = chess.white_board;
		col = 1;
	}
	else{
	 	crt_player = chess.black_board;
	 	col = 0; 
	}

 	bool bfirst_move_king = crt_player.first_move_king;
	bool bfirst_move_rook1 = crt_player.first_move_rook1;
    bool bfirst_move_rook2 = crt_player.first_move_rook2;
    bool bcastled = crt_player.castled;

	string source_str, destination_str;
	unsigned long long int source, destination;
	bool is_pawn = false;
	Legal_Moves legal;
	
	source_str = move.substr(0, 2);
	source = legal.pos_to_64bits(source_str);

	destination_str = move.substr(2, 2);
	destination = legal.pos_to_64bits(destination_str);

	int sbit = legal.index_bit(source) - 1;
	int dbit = legal.index_bit(destination) - 1;

	if(color == "black" 
		&& (source & chess.black_pawns.current_form) != 0) {
		is_pawn = true;
	} else if(color == "white" 
		&& (source & chess.white_pawns.current_form) != 0) {
		is_pawn = true;
	}

	unsigned long long int k1 = legal.pos_to_64bits("e1"); 
	unsigned long long int k2 = legal.pos_to_64bits("e8"); 

	unsigned long long hash = chess.crt_hash;

	if (color == "black") {
			if ((source & chess.black_pawns.current_form) != 0) {
				hash ^= tt.z.pieces[PAWNS][0][dbit];
				hash ^= tt.z.pieces[PAWNS][0][sbit];
			} else if ((source & chess.black_rooks.current_form) != 0) {
				hash ^= tt.z.pieces[ROOKS][0][dbit];
				hash ^= tt.z.pieces[ROOKS][0][sbit];
			} else if ((source & chess.black_knights.current_form) != 0) {
				hash ^= tt.z.pieces[KNIGHTS][0][dbit];
				hash ^= tt.z.pieces[KNIGHTS][0][sbit];
			} else if ((source & chess.black_bishops.current_form) != 0) {
				hash ^= tt.z.pieces[BISHOPS][0][dbit];
				hash ^= tt.z.pieces[BISHOPS][0][sbit];
			} else if ((source & chess.black_queen.current_form) != 0) {
				hash ^= tt.z.pieces[QUEENS][0][dbit];
				hash ^= tt.z.pieces[QUEENS][0][sbit];
			} else if ((source & chess.black_king.current_form) != 0) {
				hash ^= tt.z.pieces[KINGS][0][dbit];
				hash ^= tt.z.pieces[KINGS][0][sbit];
			}
		} else {
			if ((source & chess.white_pawns.current_form) != 0) {
				hash ^= tt.z.pieces[PAWNS][1][dbit];
				hash ^= tt.z.pieces[PAWNS][1][sbit];
			} else if ((source & chess.white_rooks.current_form) != 0) {
				hash ^= tt.z.pieces[ROOKS][1][dbit];
				hash ^= tt.z.pieces[ROOKS][1][sbit];
			} else if ((source & chess.white_knights.current_form) != 0) {
				hash ^= tt.z.pieces[KNIGHTS][1][dbit];
				hash ^= tt.z.pieces[KNIGHTS][1][sbit];
			} else if ((source & chess.white_bishops.current_form) != 0) {
				hash ^= tt.z.pieces[BISHOPS][1][dbit];
				hash ^= tt.z.pieces[BISHOPS][1][sbit];
			} else if ((source & chess.white_queen.current_form) != 0) {
				hash ^= tt.z.pieces[QUEENS][1][dbit];
				hash ^= tt.z.pieces[QUEENS][1][sbit];
			} else if ((source & chess.white_king.current_form) != 0) {
				hash ^= tt.z.pieces[KINGS][1][dbit];
				hash ^= tt.z.pieces[KINGS][1][sbit];
			}
		}



	// Make the move
	if ((((move == "e1g1") || (move == "e1c1")) && (k1 & chess.white_king.current_form)) 
		|| (((move == "e8g8")|| (move == "e8c8")) && (k2 & chess.black_king.current_form))) {
		legal.castling(move, chess);
		if(destination_str[0] == 'c' && color == "white"){
			hash ^= tt.z.pieces[ROOKS][1][3];
			hash ^= tt.z.pieces[ROOKS][1][0];
			
		} else if(destination_str[0] == 'g' && color == "white"){
			hash ^= tt.z.pieces[ROOKS][1][7];
			hash ^= tt.z.pieces[ROOKS][1][5];
		} else if(destination_str[0] == 'c' && color == "black"){
			hash ^= tt.z.pieces[ROOKS][0][59];
			hash ^= tt.z.pieces[ROOKS][0][56];
		} else if(destination_str[0] == 'g' && color == "black"){
			hash ^= tt.z.pieces[ROOKS][0][63];
			hash ^= tt.z.pieces[ROOKS][0][61];
		} 
	} else {
		if (is_pawn == false) {
			legal.attack_move(destination, chess);
			if (color == "white") {
				if ((destination & chess.black_pawns.current_form) != 0) {
					hash ^= tt.z.pieces[PAWNS][0][dbit];
				} else if ((destination & chess.black_rooks.current_form) != 0) {
					hash ^= tt.z.pieces[ROOKS][0][dbit];
				} else if ((destination & chess.black_knights.current_form) != 0) {
					hash ^= tt.z.pieces[KNIGHTS][0][dbit];
				} else if ((destination & chess.black_bishops.current_form) != 0) {
					hash ^= tt.z.pieces[BISHOPS][0][dbit];
				} else if ((destination & chess.black_queen.current_form) != 0) {
					hash ^= tt.z.pieces[QUEENS][0][dbit];
				} else if ((destination & chess.black_king.current_form) != 0) {
					hash ^= tt.z.pieces[KINGS][0][dbit];
				}
			} else {
				if ((destination & chess.white_pawns.current_form) != 0) {
					hash ^= tt.z.pieces[PAWNS][1][dbit];
				} else if ((destination & chess.white_rooks.current_form) != 0) {
					hash ^= tt.z.pieces[ROOKS][1][dbit];
				} else if ((destination & chess.white_knights.current_form) != 0) {
					hash ^= tt.z.pieces[KNIGHTS][1][dbit];
				} else if ((destination & chess.white_bishops.current_form) != 0) {
					hash ^= tt.z.pieces[BISHOPS][1][dbit];
				} else if ((destination & chess.white_queen.current_form) != 0) {
					hash ^= tt.z.pieces[QUEENS][1][dbit];
				} else if ((destination & chess.white_king.current_form) != 0) {
					hash ^= tt.z.pieces[KINGS][1][dbit];
				}
			}
		} else {
			legal.attack_move_pawn(destination, chess);
			if (color == "white") {
				if ((destination & chess.black_pawns.current_form) != 0) {
					hash ^= tt.z.pieces[PAWNS][0][dbit];
				} else if ((destination & chess.black_rooks.current_form) != 0) {
					hash ^= tt.z.pieces[ROOKS][0][dbit];
				} else if ((destination & chess.black_knights.current_form) != 0) {
					hash ^= tt.z.pieces[KNIGHTS][0][dbit];
				} else if ((destination & chess.black_bishops.current_form) != 0) {
					hash ^= tt.z.pieces[BISHOPS][0][dbit];
				} else if ((destination & chess.black_queen.current_form) != 0) {
					hash ^= tt.z.pieces[QUEENS][0][dbit];
				} else if ((destination & chess.black_king.current_form) != 0) {
					hash ^= tt.z.pieces[KINGS][0][dbit];
				}
			} else {
				if ((destination & chess.white_pawns.current_form) != 0) {
					hash ^= tt.z.pieces[PAWNS][1][dbit];
				} else if ((destination & chess.white_rooks.current_form) != 0) {
					hash ^= tt.z.pieces[ROOKS][1][dbit];
				} else if ((destination & chess.white_knights.current_form) != 0) {
					hash ^= tt.z.pieces[KNIGHTS][1][dbit];
				} else if ((destination & chess.white_bishops.current_form) != 0) {
					hash ^= tt.z.pieces[BISHOPS][1][dbit];
				} else if ((destination & chess.white_queen.current_form) != 0) {
					hash ^= tt.z.pieces[QUEENS][1][dbit];
				} else if ((destination & chess.white_king.current_form) != 0) {
					hash ^= tt.z.pieces[KINGS][1][dbit];
				}
			}
		}
		legal.make_move(source, destination, chess);
		
	}

	if(is_pawn && (destination & chess.black_board.en_passant)){
		hash ^= tt.z.pieces[PAWNS][0][dbit - 8];
	} else if(is_pawn && (destination & chess.white_board.en_passant)) {
		hash ^= tt.z.pieces[PAWNS][1][dbit + 8];
	}

	// Update the en_passant variable
	if (color == "white") {
		chess.black_board.en_passant = 0;     
	} else {
		chess.white_board.en_passant = 0;
	}

	int index_dest, index_source, dif_index;
	index_dest = legal.index_bit(destination);
	index_source = legal.index_bit(source);
	dif_index = abs(index_dest - index_source);
	if (is_pawn && legal.check_first_move(color, source_str)) {
		if (color == "black" && dif_index == 16) {
			chess.black_board.en_passant = destination << 8;
		} else if (color == "white" && dif_index == 16) {
			chess.white_board.en_passant = destination >> 8;
		}
	}

	//Check for pawn promotion
	if((color == "black") && legal.index_bit(destination) < 8 && is_pawn == true) {
		legal.pawn_promotion("black", chess.black_board, chess, source, destination);
		hash ^= tt.z.pieces[PAWNS][0][dbit];
		hash ^= tt.z.pieces[QUEENS][0][dbit];
	} else if((color == "white") && legal.index_bit(destination) > 55 && is_pawn == true) {
		legal.pawn_promotion("white", chess.white_board, chess, source, destination);
		hash ^= tt.z.pieces[PAWNS][1][dbit];
		hash ^= tt.z.pieces[QUEENS][1][dbit];
	}

	if (crt_player.castled ^ bcastled) {
		if(col == 1)hash ^= tt.z.white_castle[3];
		else hash ^= tt.z.black_castle[3];
	} else {
		if (crt_player.first_move_king ^ bfirst_move_king) {
			if ((crt_player.first_move_rook1 ^ bfirst_move_rook1) && (crt_player.first_move_rook2 ^ bfirst_move_rook2)) {
				if(col == 1)hash ^= tt.z.white_castle[0];
				else hash ^= tt.z.black_castle[0];
			} else if (crt_player.first_move_rook1 ^ bfirst_move_rook1) {
				if(col == 1)hash ^= tt.z.white_castle[2];
				else hash ^= tt.z.black_castle[2];
			} else if (crt_player.first_move_rook2 ^ bfirst_move_rook2) {
				if(col == 1)hash ^= tt.z.white_castle[1];
				else hash ^= tt.z.black_castle[1];
			}
		}
	}

	// Check for endgame phase
	if (countSetBits(chess.board.current_form) <= 12) {
		chess.endgame = true;
	}

	if (countSetBits(chess.board.current_form) <= 30) {
		chess.opening = false;
	}

	chess.crt_hash = hash;
	return hash;
}

bool operator<(const ChessBoardState& b1, const ChessBoardState& b2){
	int p = b1.player;
	return table_value(b1.table, p) > table_value(b2.table, p);
}

vector<ChessBoardState> sortMoves(vector<string> &moves, ChessBoard chess, int player) {
	vector<ChessBoardState> results;
	string color;

	if (player == 1) {
		color = "white";
	} else {
		color = "black";
	}

	for(string move : moves) {
		ChessBoard chess_copy = chess;
		apply_move(chess_copy, move, color);
		ChessBoardState new_state;
		new_state.table = chess_copy;
		new_state.player = player;
		new_state.move = move;
		results.emplace_back(new_state);
	}

	sort(results.begin(),results.end());
	return results;
}

string alfabeta_root(ChessBoard chess, int player, int depth) {
	string color, best_move = "";
	int max_score = -(1<<25);
	int score;

	if (player == 1) {
		color = "white";
	} else {
		color = "black";
	}

	Moves all_moves = get_possible_moves(chess, color);
	Legal_Moves legal;

	int alfa = -(1<<25);
	int beta = (1<<25);
	

	int moves = all_moves.quiet.size() + all_moves.good_captures.size() + 
				all_moves.even_captures.size() + all_moves.bad_captures.size();

	if(all_moves.quiet.empty() && all_moves.good_captures.empty() &&
		all_moves.even_captures.empty() && all_moves.bad_captures.empty()) {
		return "";
	}

	depth--;
	/*if (moves < 15) {
		depth++;
	} else if (moves > 40) {
		depth--;
	}*/

	unsigned long long int king;
	ChessBoard chess_copy;

	for(string move : all_moves.good_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) {
			continue;
		}

		score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		
		if(score > max_score) {
			alfa = score;
			max_score = score;
			best_move = move;
		}

	}

	for(string move : all_moves.even_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) {
			continue;
		}

		score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		
		if(score > max_score) {
			alfa = score;
			max_score = score;
			best_move = move;
		}

	}	

	for(string move : all_moves.quiet) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) {
			continue;
		}

		score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		
		if(score > max_score) {
			alfa = score;
			max_score = score;
			best_move = move;
		}

	}	

	for(string move : all_moves.bad_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) {
			continue;
		}

		score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		
		if(score > max_score) {
			alfa = score;
			max_score = score;
			best_move = move;
		}
	}		

	return best_move;
}

int alfabeta_negamax (ChessBoard &chess, int player, int alfa, int beta, int depth, bool allowNull) {
	Legal_Moves legal;
	string color, best_move;
	HashEntry entry;
	int eval = 0;
	
	if (player == 1) {
		color = "white";
	} else {
		color = "black";
	}

	int score = -(1<<25), current_score;
	unsigned long long int king;
	if (player == 1) {
		king = chess.white_king.current_form;
	} else if (player == -1) {
		king = chess.black_king.current_form;
	}

	/*if (allowNull && !legal.is_check(color, king, chess) && !chess.endgame && (depth >= 3)) {
		score = -alfabeta_negamax(chess, -player, -beta, -beta + 1, depth - 3, false);
		if (score >= beta) {
			return score;
		}
	}*/

	unsigned long long hashBoard = chess.crt_hash;
	if (tt.exists(hashBoard)) {
		HashEntry tte = tt.getEntry(hashBoard);
		if (tte.depth >= depth) {
			if (tte.flag == EXACT) {
				return tte.value;
			} else if (tte.flag == LOWER && tte.value > alfa) {
				alfa = tte.value;
			} else if (tte.flag == UPPER && tte.value < beta) {
				beta = tte.value;
			}

			if (alfa >= beta) {
				return tte.value;
			}
		}
	}

	Moves all_moves = get_possible_moves(chess, color);
	int moves = 0;

	if(all_moves.quiet.empty() && all_moves.good_captures.empty() &&
		all_moves.even_captures.empty() && all_moves.bad_captures.empty()) {
		return -(1<<25);
	} else {
		// o tabla e mai valoroasa cu cat sunt mai multe posibilitati (mobilitate)
		moves = all_moves.quiet.size() + all_moves.good_captures.size() + 
				all_moves.even_captures.size() + all_moves.bad_captures.size(); 
	}

	//aceeasi evaluare daca depth e 0 returneaza evaluarea tablei
	if (depth == 0) {
		eval = moves + evaluateBoardScore(chess, player);
		//eval = moves + Quiescence(chess, player, alfa, beta);
		if (eval <= alfa) {
			entry.init(hashBoard, depth, eval, LOWER);
			tt.add(hashBoard, entry);
		} else if (eval >= beta) {
			entry.init(hashBoard, depth, eval, UPPER);
			tt.add(hashBoard, entry);
		} else {
			entry.init(hashBoard, depth, eval, EXACT);
			tt.add(hashBoard, entry);
		}
		return eval;
	}

	ChessBoard chess_copy;


	for (string move : all_moves.good_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) continue;

		current_score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		if(current_score > score) {
			score = current_score;
		}

		if (score > alfa) {
			alfa = score;
		}

		if (alfa >= beta) {
			score = alfa;
			goto out;
		}
	}

	for (string move : all_moves.even_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) continue;

		current_score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		if(current_score > score) {
			score = current_score;
		}

		if (score > alfa) {
			alfa = score;
		}

		if (alfa >= beta) {
			score = alfa;
			goto out;
		}
	}

	for (string move : all_moves.quiet) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) continue;

		current_score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		if(current_score > score) {
			score = current_score;
		}

		if (score > alfa) {
			alfa = score;
		}

		if (alfa >= beta) {
			score = alfa;
			goto out;
		}
	}

	for (string move : all_moves.bad_captures) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		if (player == 1) {
			king = chess_copy.white_king.current_form;
		} else if (player == -1) {
			king = chess_copy.black_king.current_form;
		}

		if(legal.is_check(color, king, chess_copy)) continue;

		current_score = -alfabeta_negamax(chess_copy, -player, -beta, -alfa, depth - 1, true);
		if(current_score > score) {
			score = current_score;
		}

		if (score > alfa) {
			alfa = score;
		}

		if (alfa >= beta) {
			score = alfa;
			goto out;
		}
	}

	out:

	if (score <= alfa) {
		entry.init(hashBoard, depth, score, LOWER);
		tt.add(hashBoard, entry);
	} else if (score >= beta) {
		entry.init(hashBoard, depth, score, UPPER);
		tt.add(hashBoard, entry);
	} else {
		entry.init(hashBoard, depth, score, EXACT);
		tt.add(hashBoard, entry);
	}

	if(alfa == -(1<<25)) {
		return -(1<<25) - depth;
	}

	return alfa;
}


int Quiescence(ChessBoard chess, int player, int alfa, int beta) {
	string color;
	int score, current_score;
	Legal_Moves legal;
	if (player == 1) {
		color = "white";
	} else {
		color = "black";
	}

	vector<string> attack_moves = get_attack_moves(chess, color);
	score = evaluateBoardScore(chess, player);
	if (attack_moves.empty()) {
		return score;
	}

	if (score >= beta) {
		return beta;
	}

	if (score > alfa) {
		alfa = score;
	}

	ChessBoard chess_copy;

	for (string move: attack_moves) {
		chess_copy = chess;
		apply_move(chess_copy, move, color);

		current_score = -Quiescence(chess_copy, -player, -beta, -alfa);

		if (current_score >= beta) {
			return beta;
		}

		if (score > alfa) {
			alfa = score;
		}
	}

	return alfa;
}