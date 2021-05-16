#include <iostream>
#include <fstream>
#include <string.h>
#include <cctype>
#include <string>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <ctime>
#include "Board.h"
#include "Legal_Moves.h"
#include "Minimax.h"
#include "Transposition.h"
using namespace std;

#define STR_BUFF 256

HashTable tt;

bool check_regular_input(char input[]){

	if(strlen(input) != 4){
		return false;
	}
	if(!isalpha(input[0])){
		return false;
	}

	if(!isdigit(input[1])){
		return false;
	}

	if(!isalpha(input[2])){
		return false;
	}

	if(!isdigit(input[3])){
		return false;
	}

	return true ;

}

bool check_pawn_p_input(char input[]){

	if(strlen(input) != 5){
		return false;
	}
	if(!isalpha(input[0])){
		return false;
	}

	if(!isdigit(input[1])){
		return false;
	}

	if(!isalpha(input[2])){
		return false;
	}

	if(!isdigit(input[3])){
		return false;
	}
	if(input[4] != 'q'){
		return false;
	}
	return true ;
}

int main (int argc, const char *argv[])
{
	cout.setf(ios :: unitbuf);
	char input[STR_BUFF];
	char output[STR_BUFF];
	
	ChessBoard chess;
	Board board_functions;
	Legal_Moves moves_functions;

	unsigned long long int cast1 = moves_functions.pos_to_64bits("e1");
	unsigned long long int cast2 = moves_functions.pos_to_64bits("e8");

	board_functions.reset_all_pieces(chess);

	chess.board = board_functions.new_board(); //Sterge asta si se face OR intre tablele de mai sus
	chess.board = board_functions.set_engine_color("black", chess.board);
	chess.board = board_functions.force_mode_off(chess.board);
	cout << chess.board.engine_color;

	string color_on_move ;

	if(chess.board.engine_color == "black"){
		color_on_move = "white";
	}
	else{
		color_on_move = "black";
	}
	
	tt.z.computeHash(chess, 0);



	while(1) {
		update_board(chess);        
		cin >> input;

		if (strcmp(input,"xboard") == 0) {

			board_functions.xboard();
		}
		else if (strcmp(input, "protover") == 0) {
			
			board_functions.protover();
		}
		else if (strcmp(input,"new") == 0) {
			board_functions.reset_all_pieces(chess);
			chess.board = board_functions.new_board();
			chess.board = board_functions.set_engine_color("black", chess.board);
			tt.z.computeHash(chess, 0);
		}
		else if (strcmp(input,"go") == 0) {
			chess.board = board_functions.force_mode_off(chess.board);
			int player;

			if(color_on_move == "black") {
				chess.board = board_functions.set_engine_color("black", chess.board);
				player = -1;

			} else {
				chess.board = board_functions.set_engine_color("white", chess.board);
				player = 1;
			}

			string res;
			for (int i = 2; i <= 6; i++) {
				res = alfabeta_root(chess, player, i);
			}

			if(res == "") {
				board_functions.resign(chess.board);
			}

			else{
				apply_move(chess, res, color_on_move);
				cout << "move " << res << endl;
			}

			if(color_on_move == "black") {
				color_on_move = "white";

			} else {
				color_on_move = "black";
			}            
		}
		else if (strcmp(input,"force") == 0) {
			chess.board = board_functions.force_mode_on(chess.board);
		}
		
		else if (strcmp(input,"white") == 0) {
			chess.board = board_functions.set_engine_color("white", chess.board);
		}
		else if (strcmp(input,"black") == 0) {
			chess.board = board_functions.set_engine_color("black", chess.board);
		}
		else if (strcmp(input,"quit") == 0) {
			return 0;
		}
		else if(strcmp(input, "resign") == 0) {

			board_functions.resign(chess.board);
		}

		else if( (chess.board.force_mode == false) && ((check_regular_input(input) == true) ||
				(check_pawn_p_input(input) == true)) ) {
			apply_move(chess, input, color_on_move);

			if(chess.board.engine_color == "black") {
				color_on_move = "black";
			} else {
				color_on_move = "white";
			}

			int player;

			if(chess.board.engine_color == "black") {
				player = -1;
			} else {
				player = 1;
			}

			string res;
			for (int i = 2; i <= 6; i++) {
				res = alfabeta_root(chess, player, i);
			}

			if(res == "") {
				board_functions.resign(chess.board);
			}
			else{
				apply_move(chess, res, color_on_move);
				cout << "move " << res << endl;
			}

			// Update the en_passant variable
			if (chess.board.engine_color == "white") {
				chess.black_board.en_passant = 0;     
			} else {
				chess.white_board.en_passant = 0;
			}

			if(color_on_move == "black") {
				color_on_move = "white";

			} else {
				color_on_move = "black";
			}  

		}
		else if(chess.board.force_mode == true && ((check_regular_input(input) == true) ||
				(check_pawn_p_input(input) == true))) {

			BitBoard force_mode_board ;
			force_mode_board = chess.board;

			if(color_on_move == "black"){
				force_mode_board.engine_color = "white";
			}
			else{
				force_mode_board.engine_color = "black";
			}

			//Mutarea se va trata la fel ca miscarile xboard-ului
			moves_functions.xboard_move(input, chess);

			//Comutare culoare pentru a seta urmatoarea culoare pe move
			if(force_mode_board.engine_color == "black") {
				color_on_move = "black";
			}
			else{
				color_on_move = "white";
			}
		}
	}
	return 0;
}