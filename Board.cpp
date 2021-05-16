#include "Board.h"
#include <iostream>
#include <string.h>
#include <string>

void Board :: xboard() {
	cout << '\n';
}

void Board :: protover() {
	cout << "feature sigint=0 san=0" << endl;
}

string Board :: piece_type(unsigned long long int my_piece, ChessBoard board) {
	string type;
	if((my_piece & board.white_pawns.current_form) > 0) {
		type = "white pawn";
		return type;
	}
	if((my_piece & board.white_rooks.current_form) > 0) {
		type = "white rook";
		return type;
	}
	if((my_piece & board.white_knights.current_form) > 0) {
		type = "white knight";
		return type;
	}
	if((my_piece & board.white_bishops.current_form) > 0) {
		type = "white bishop";
		return type;
	}
	if((my_piece & board.white_queen.current_form) > 0) {
		type = "white queen";
		return type;
	}
	if((my_piece & board.white_king.current_form) > 0) {
		type = "white king";
		return type;
	}
	if((my_piece & board.black_pawns.current_form) > 0) {
		type = "black pawn";
		return type;
	}
	if((my_piece & board.black_rooks.current_form) > 0) {
		type = "black rook";
		return type;
	}
	if((my_piece & board.black_knights.current_form) > 0) {
		type = "black knight";
		return type;
	}
	if((my_piece & board.black_bishops.current_form) > 0) {
		type = "black bishop";
		return type;
	}
	if((my_piece & board.black_queen.current_form) > 0) {
		type = "black queen";
		return type;
	}
	if((my_piece & board.black_king.current_form) > 0) {
		type = "black king";
		return type;
	}

	return "no piece";    
}

BitBoard Board :: reset_pieces_position(string color, string type) {
	//Se reseteaza tabla de joc pentru piesele de tipul type

	BitBoard my_board;
	my_board.current_form = 0;
	int i;
	if(type == "pawns"){
		if(color =="white"){
			for(i = 8 ; i < 16 ; i++){
				//Pentru partea inferioara a tablei
				my_board.current_form += (1ULL << i);
			}
		}
		else{
			for(i = 9 ; i <= 16 ; i++){
				//Pentru partea superioara a tablei
				my_board.current_form += (1ULL << (64-i));
			}
		}
		return my_board ;	
	}

	if(type == "rooks"){
		if(color == "white"){
			my_board.current_form += 1;
			my_board.current_form += (1ULL << 7);

		}
		else{
			my_board.current_form += (1ULL << 63);
			my_board.current_form += (1ULL << 56);

		}
		return my_board ;
	}

	if(type == "knights"){
		if(color =="white"){
			my_board.current_form += (1ULL << 1);
			my_board.current_form += (1ULL << 6);
		}
		else{
			my_board.current_form += (1ULL << 62);
			my_board.current_form += (1ULL << 57);
		}
		return my_board ;
	}

	if(type == "bishops"){
		if(color =="white"){
			my_board.current_form += (1ULL << 2);
			my_board.current_form += (1ULL << 5);
		}
		else{
			my_board.current_form += (1ULL << 61);
			my_board.current_form += (1ULL << 58);
		}

		return my_board ;
	}

	if(type == "king"){
		if(color =="white"){
			my_board.current_form += (1ULL << 4);
		}
		else{
			my_board.current_form += (1ULL << 60);
		}
	}

	if(type == "queen"){
		if(color =="white"){
			my_board.current_form += (1ULL << 3) ;
		}
		else{
			my_board.current_form += (1ULL << 59) ;
		}
		return my_board ;
	}
}

void Board :: reset_all_pieces(ChessBoard &board){
	board.white_pawns = reset_pieces_position("white", "pawns"); //pioni albi
	board.white_rooks = reset_pieces_position("white", "rooks");  //turnuri albe
	board.white_knights = reset_pieces_position("white", "knights");  //cai albi
	board.white_bishops = reset_pieces_position("white", "bishops");  //nebuni albi
	board.white_queen = reset_pieces_position("white", "queen");  //regina alba
	board.white_king = reset_pieces_position("white", "king");  //regele alb
	
	board.black_pawns = reset_pieces_position("black", "pawns"); 
	board.black_rooks = reset_pieces_position("black", "rooks"); 
	board.black_knights = reset_pieces_position("black", "knights"); 
	board.black_bishops = reset_pieces_position("black", "bishops"); 
	board.black_queen = reset_pieces_position("black", "queen"); 
	board.black_king = reset_pieces_position("black", "king"); 

}

BitBoard Board :: set_engine_color(string color, BitBoard &my_board){
	my_board.engine_color = color;
	return my_board;
}

BitBoard Board :: new_board(){
	//returneaza toata tabla

	BitBoard new_board;
	new_board.current_form = 0;
	int i;

	for(i = 0; i < 16; i++){
		//Pentru partea alba 
		new_board.current_form |= (1ULL << i);

		//Pentru partea neagra
		new_board.current_form |= (1ULL << (64 - i + 1));
	}

	return new_board;
}

void Board :: resign(BitBoard board){

	//Mesajele de resign sunt transmise de engine
	if(board.engine_color == "black"){
		cout << "1-0 {BLACK resigns}" << endl;
	}
	else{
		cout << "0-1 {WHITE resigns}" << endl ;
	}
}

BitBoard Board :: force_mode_on(BitBoard &board){
	board.force_mode = true;
	return board ;
}

BitBoard Board :: force_mode_off(BitBoard &board){
	board.force_mode = false;
	return board ;
}

void update_board(ChessBoard &chess) {
    chess.black_board.current_form = (chess.black_pawns.current_form | chess.black_rooks.current_form | 
                            chess.black_knights.current_form | chess.black_bishops.current_form |
                            chess.black_king.current_form | chess.black_queen.current_form);

    chess.white_board.current_form = (chess.white_pawns.current_form  | chess.white_rooks.current_form  |
                        chess.white_knights.current_form | chess.white_bishops.current_form | 
                        chess.white_king.current_form | chess.white_queen.current_form );
    chess.board.current_form = chess.white_board.current_form | chess.black_board.current_form;
}