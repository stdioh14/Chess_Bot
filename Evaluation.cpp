#include "Evaluation.h"
#include "Board.h"
using namespace std;

// Numara piesele din fiecare tip pentru tabla mea
int table_value(ChessBoard chess, int player) {
	int score = 0;
	unsigned long long position;
	string color;

	if (player == 1) {
		color = "white";
	} else if (player == -1) {
		color = "black";
	} 

	if (color == "black") {
		for (int i = 0; i < 64; i++) {
			position = (1ULL << i);
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
			} else if ((position & chess.white_pawns.current_form) != 0) {
				score -= P;
			} else if ((position & chess.white_rooks.current_form) != 0) {
				score -= R;
			} else if ((position & chess.white_knights.current_form) != 0) {
				score -= N;
			} else if ((position & chess.white_bishops.current_form) != 0) {
				score -= B;
			} else if ((position & chess.white_queen.current_form) != 0) {
				score -= Q;
			} else if ((position & chess.white_king.current_form) != 0) {
				score -= K;
			}
		}
	} else {
		for (int i = 0; i < 64; i++) {
			position = (1ULL << i);
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
			} else if ((position & chess.black_pawns.current_form) != 0) {
				score -= P;
			} else if ((position & chess.black_rooks.current_form) != 0) {
				score -= R;
			} else if ((position & chess.black_knights.current_form) != 0) {
				score -= N;
			} else if ((position & chess.black_bishops.current_form) != 0) {
				score -= B;
			} else if ((position & chess.black_queen.current_form) != 0) {
				score -= Q;
			} else if ((position & chess.black_king.current_form) != 0) {
				score -= K;
			}
		}
	}
	return score;
}

int pawn_eval(ChessBoard chess, string color, unsigned long long position) {
	int score = 0, column, line;
	Legal_Moves legal;
	int index = legal.index_bit(position);

	// variabile folosite pentru a verifica "double pawns"
	unsigned long long pawn_left, pawn_right;
	pawn_right = position << 1;
	pawn_left = position >> 1;

	// penalizam pionii de pe margini
	column = (index % 8);
	line = (index / 8) + 1;
	if (column == 0) {
		// nu exista pion in stanga
		pawn_left = 0;
		score -= 15;

	} else if (column == 7) {
		// nu exista pion in dreapta
		pawn_right = 0;
		score -= 15;
	}

	// Verificare double pawns
	line = (index / 8);
	unsigned long long aux_position;

	if (color == "white") {
		aux_position = position >> 8;
		for(int i = line - 1; i >= 0; i--) {
			if((aux_position & chess.white_pawns.current_form) != 0){
				score -= 10;
				break;
			}
			else {
				aux_position = aux_position >> 8;
			}
		}

		aux_position = position << 8;
		for(int i = line + 1; i < 8; i++) {
			if((aux_position & chess.black_pawns.current_form) != 0){
				score -= 10;
				break;
			}
			else {
				aux_position = aux_position << 8;
			}
		}
	} else {
		aux_position = position << 8;
		for(int i = line + 1; i < 8; i++) {
			if((aux_position & chess.black_pawns.current_form) != 0){
				score -= 10;
				break;
			}
			else {
				aux_position = aux_position << 8;
			}
		}
		aux_position = aux_position >> 8;
		for(int i = line - 1; i >= 0; i--) {
			if((aux_position & chess.black_pawns.current_form) != 0){
				score -= 10;
				break;
			}
			else {
				aux_position = aux_position >> 8;
			}
		}
	}

	// Descurajam pionul care sta pe pozitia de inceput
	if (color == "white") {
		if (line == 2) {
			score -= 10;
		}
	} else if (color == "black") {
		if (line == 7) {
			score -= 10;
		}
	}

	// Passed pawns
	line = (index / 8);
	bool passed_pawn = false;
	aux_position = position;

	if(color == "white"){
		for(int i = line; i < 8; i++){
			if((aux_position & chess.black_pawns.current_form) != 0 ||
				((column != 7) && 
					((aux_position << 1) & chess.black_pawns.current_form) != 0) ||
				((column != 0) &&
					((aux_position >> 1) & chess.black_pawns.current_form) != 0)){
				
				passed_pawn = false;
				break;
			}
			else{
				aux_position = aux_position << 8;
			}
		}
	} else {
		for(int i = line; i >= 0 ; i--){
			if((aux_position & chess.white_pawns.current_form) != 0 ||
				((column != 7) &&
				((aux_position << 1) & chess.black_pawns.current_form) != 0) ||
				((column != 0) &&
				((aux_position >> 1) & chess.black_pawns.current_form) != 0)){
				
				passed_pawn = false;
				break;
			}
			else{
				aux_position = aux_position >> 8;
			}
		}
	}

	// Incurajam si pionii mai aproape de promovare
	if(passed_pawn){
		score += 50;
		if (color == "white") {
			if (line == 6) {
				score += 10;			
			} else if (line == 5) {
				score += 5;
			}
		} else if (color == "black") {
			if (line == 1) {
				score += 10;
			} else if (line == 2) {
				score += 5;
			}
		}
	}

	// Verificare isolated pawns
	
	
	// Verificare backward pawns

	return score;
}

int center_position(int index, bool endgame, bool king) {
	int score = 0, return_score = 0, line, column;

	line = (index / 8) + 1;
	column = (index % 8) + 1;
	if (line == 4 || line == 5) {
		if (column == 4 || column == 5) {
			score += 15;
		} else if (column == 3 || column == 6) {
			score += 10;
		}
	} else if (line == 3 || line == 6) {
		if (column == 4 || column == 5) {
			score += 10;
		} else if (column == 3 || column == 6) {
			score += 5;
		}
	}

	if (endgame == false) {
		if (king == false) {
			return_score = score;
		}
	} else {
		if (king == true) {
			return_score = score;
		}
	}

	return return_score;
}

int bishop_eval() {
	int score = 0;
	return score;
}

int rook_eval() {
	int score = 0;
	return score;
}

int king_eval() {
	int score = 0;
	return score;
}

int evaluate(ChessBoard chess, int player) {
	BitBoard my_board;
	Legal_Moves legal;
	int score = 0, bishop_count = 0;
	string color, opponent;
	unsigned long long position;

	if (player == 1) {
		my_board = chess.white_board;
		color = "white";
		opponent = "black";
	} else if (player == -1) {
		my_board = chess.black_board;
		color = "black";
		opponent = "white";
	}

	int nr_queens = 0 ;
	if (color == "white") {
		if (chess.white_board.castled == true) {
			// incurajam rocada
			score += 50;
		}
		for (int i = 0; i < 64; i++) {
			position = (1ULL << i);
			if ((position & chess.white_board.current_form) != 0) {
				if ((position & chess.white_king.current_form) == 0) {
					score += center_position(i, chess.endgame, false);
				} else {
					score += center_position(i, chess.endgame, true);
				}
			}	

			if ((position & chess.white_pawns.current_form) != 0) {
				score += WHITE_PAWN_EVAL[i];
				score += pawn_eval(chess, color, position);
				score += P;
			} else if ((position & chess.white_rooks.current_form) != 0) {
				score += WHITE_ROOK_EVAL[i];
				score += R;
				string current_pos = legal.bits_to_position_string(position);
				Piece my_rook = legal.rooks_moves(current_pos, color, chess);
				score += (2 * my_rook.number_of_moves);
			} else if ((position & chess.white_knights.current_form) != 0) {
				// caii sunt mai putini valorosi la finalul jocului
				score += WHITE_KNIGHT_EVAL[i];
				if (chess.endgame == true) {
					score -= 10;
				}
				score += N;
			} else if ((position & chess.white_bishops.current_form) != 0) {
				score += WHITE_BISHOP_EVAL[i];
				bishop_count++;
				if (bishop_count == 2) {
					// doi nebuni sunt mai avantajosi (in special la finalul jocului)
					score += 40;
				}
				if (chess.endgame == true) {
					score += 10;
				}
				string current_pos = legal.bits_to_position_string(position);
				Piece my_bishop = legal.bishop_moves(current_pos, color, chess);
				score += (2 * my_bishop.number_of_moves);
				score += B;
			} else if ((position & chess.white_queen.current_form) != 0) {
				score += WHITE_QUEEN_EVAL[i];
				score += Q;
				if (chess.opening == true && chess.white_board.queen_moved == true) {
					score -= 100;
				}
				nr_queens++;
			} else if ((position & chess.white_king.current_form) != 0) {
				if (chess.endgame == true) {
					score += WHITE_KING_ENDGAME[i];
				} else {
					score += WHITE_KING_EVAL[i];	
				}
				score += K;
			}
		}
	} else {
		if (chess.black_board.castled == true) {
			score += 50;
		}

		for (int i = 0; i < 64; i++) {
			position = (1ULL << i);
			if ((position & chess.black_board.current_form) != 0) {
				if ((position & chess.black_king.current_form) == 0) {
					score += center_position(i, chess.endgame, false);
				} else {
					score += center_position(i, chess.endgame, true);
				}
			}	
			if ((position & chess.black_pawns.current_form) != 0) {
				score += BLACK_PAWN_EVAL[i];
				score += pawn_eval(chess, color, position);
				score += P;
			} else if ((position & chess.black_rooks.current_form) != 0) {
				score += BLACK_ROOK_EVAL[i];
				score += R;
				string current_pos = legal.bits_to_position_string(position);
				Piece my_rook = legal.rooks_moves(current_pos, color, chess);
				score += (2 * my_rook.number_of_moves);
			} else if ((position & chess.black_knights.current_form) != 0) {
				score += BLACK_KNIGHT_EVAL[i];
				if (chess.endgame == true) {
					score -= 10;
				}
				score += N;
			} else if ((position & chess.black_bishops.current_form) != 0) {
				score += BLACK_BISHOP_EVAL[i];
				bishop_count++;
				if (bishop_count == 2) {
					// doi nebuni sunt mai avantajosi (in special la finalul jocului)
					score += 40;
				}

				if (chess.endgame == true) {
					score += 10;
				}
				string current_pos = legal.bits_to_position_string(position);
				Piece my_bishop = legal.bishop_moves(current_pos, color, chess);
				score += (2 * my_bishop.number_of_moves);
				score += B;
			} else if ((position & chess.black_queen.current_form) != 0) {
				score += BLACK_QUEEN_EVAL[i];
				score += Q;
				if (chess.opening == true && chess.black_board.queen_moved == true) {
					score -= 100;
				}
				nr_queens++;
			} else if ((position & chess.black_king.current_form) != 0) {
				if (chess.endgame == true) {
					score += BLACK_KING_ENDGAME[i];
				} else {
					score += BLACK_KING_EVAL[i];	
				}
				score += K;
			}
		}
	}
	if(nr_queens >1){
		score += nr_queens * 40;
	}
	return score;
}

int evaluateBoardScore(ChessBoard chess, int player) {
	return evaluate(chess, player) - evaluate(chess, -player);
}
