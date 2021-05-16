#include <bits/stdc++.h>
#include <string>
#include <ctime>
#include <vector>
#include "Legal_Moves.h"
#include "Board.h"
using namespace std;

unsigned int countSetBits(unsigned long long n) { 
	unsigned int count = 0; 
	while (n) { 
		n &= (n - 1); 
		count++; 
	} 
	return count; 
} 

string Legal_Moves :: bits_to_position_string(unsigned long long current_position){

	string position;

	/*Determina pozitia in tabla de sah a pozitiei transmise
	ca parametru, sub forma unui string*/
	int index = index_bit(current_position);

	position += ('a' + (index % 8));
	position += ('0' + ((index / 8) + 1));

	return position;
}

unsigned long long int Legal_Moves :: pos_to_64bits(string pos){

	/* Determina numarul  pe care il reprezinta string-ul transmis
	ca parametru, gasing in functie de pozitia transmisa, bit-ul
	de 1 ocupat de aceasta pe tabla */

	int column = (pos[0] - 'a');
	int line = (pos[1] - '0');

	unsigned long long int my_number = (1ULL << ((line - 1) * 8));
	my_number = my_number << column;
	return my_number;
}

void Legal_Moves :: regular_move_message(string source, string destination){
	//fout << "move " << source << destination << endl;
	cout << "move " << source << destination << endl;   
}

void Legal_Moves :: pawn_promotion_message(string source, string destination){
	//fout << "move " << source << destination << endl;
	cout << "move " << source << destination << "q" << endl;	
}

int Legal_Moves :: index_bit(unsigned long long number){
	//Determina pozitia ocupata de bit-ul de 1 in number
	int position = 0;

	while(number != (1ULL << position) && position < 64){
		position++;
	}
	return position;
}

bool Legal_Moves :: check_first_move(string color, string position){
	/*Verifica daca pionul urmeaza sa execute prima sa miscare, prin
	validarea coniditiei ca acesta sa faca parte ori din randul 2, ori
	din randul 7*/

	if(color == "black" && position[1] == '7'){
		return true;
	}
	else{
		if(color == "white" && position[1] == '2'){
			return true;
		}
	}
	return false ;
}

void Legal_Moves :: place_piece(BitBoard &board, unsigned long long int source, 
                unsigned long long int destination){
	/*Se muta piesa de la adresa sursei, la adresa destinatiei, pe placa
	transmisa ca parametru */
    board.current_form = board.current_form ^ source;
    board.current_form = board.current_form | destination; 
}

void Legal_Moves :: make_move(unsigned long long int xboard_move_source, 
                			unsigned long long int xboard_move_destination,
                			ChessBoard &chess){
	/*Se gasesc placile din care face parte piesa-sursa si se elimina
	din aceasta si se adauga pe placa destinatie, folosind functie
	make_move */

	if((xboard_move_source & chess.black_pawns.current_form) != 0){
		place_piece(chess.black_pawns, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);
	}
	if((xboard_move_source & chess.black_rooks.current_form) != 0){
		place_piece(chess.black_rooks, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);

		if ((xboard_move_source & (1ULL << 56)) != 0) {
			chess.black_board.first_move_rook1 = false;
		} else if ((xboard_move_source & (1ULL << 63)) != 0) {
			chess.black_board.first_move_rook2 = false;
		}
	}
	if((xboard_move_source & chess.black_bishops.current_form) != 0){
		place_piece(chess.black_bishops, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);
	}
	if((xboard_move_source & chess.black_knights.current_form) != 0){
		place_piece(chess.black_knights, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);
	}
	if((xboard_move_source & chess.black_queen.current_form) != 0){
		place_piece(chess.black_queen, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);
		chess.black_board.queen_moved = true;
	}
	if((xboard_move_source & chess.black_king.current_form) != 0){
		place_piece(chess.black_king, xboard_move_source, xboard_move_destination);
		place_piece(chess.black_board, xboard_move_source, xboard_move_destination);
		chess.black_board.first_move_king = false;
	}
	if((xboard_move_source & chess.white_pawns.current_form) != 0){
		place_piece(chess.white_pawns, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);
	}
	if((xboard_move_source & chess.white_rooks.current_form) != 0){
		place_piece(chess.white_rooks, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);

		if ((xboard_move_source & (1ULL)) != 0) {
			chess.white_board.first_move_rook1 = false;
		} else if ((xboard_move_source & (1ULL << 7)) != 0) {
			chess.white_board.first_move_rook2 = false;
		}
	}
	if((xboard_move_source & chess.white_knights.current_form) != 0){
		place_piece(chess.white_knights, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);
	}
	if((xboard_move_source & chess.white_queen.current_form) != 0){
		place_piece(chess.white_queen, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);
		chess.white_board.queen_moved = true; 
	}
	if((xboard_move_source & chess.white_king.current_form) != 0){
		place_piece(chess.white_king, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);
		chess.white_board.first_move_king = false;
	}
	if((xboard_move_source & chess.white_bishops.current_form) != 0){
		place_piece(chess.white_bishops, xboard_move_source, xboard_move_destination);
		place_piece(chess.white_board, xboard_move_source, xboard_move_destination);
	}

	update_board(chess);
}

void Legal_Moves :: castling(string move, ChessBoard &chess){

	unsigned long long int xboard_move_source, xboard_move_destination;
	xboard_move_source = pos_to_64bits(move.substr(0,2));
	xboard_move_destination = pos_to_64bits(move.substr(2,4));
                
	if(move == "e8c8" || move == "e8g8"){
		//bot-ul muta piesele albe
		make_move(xboard_move_source, xboard_move_destination, chess);
		chess.black_board.castled = true;
	}
	else if(move == "e1c1" || move == "e1g1") {
		make_move(xboard_move_source, xboard_move_destination, chess);
		chess.white_board.castled = true;
	}

	if((move.substr(2,4)) == "c8"){
		//Muta tura stanga
		xboard_move_source = pos_to_64bits("a8");
		make_move(xboard_move_source, (xboard_move_destination << 1), chess);
		
	}
	else if((move.substr(2,4)) == "g8"){
		//Muta tura dreapta
		xboard_move_source = pos_to_64bits("h8");
		make_move(xboard_move_source, (xboard_move_destination >> 1), chess);
	}
	else if((move.substr(2,4)) == "c1"){
		//Muta tura dreapta
		xboard_move_source = pos_to_64bits("a1");
		make_move(xboard_move_source, (xboard_move_destination << 1), chess);
		
	}
	else if((move.substr(2,4)) == "g1"){
		//Muta tura dreapta
		xboard_move_source = pos_to_64bits("h1");
		make_move(xboard_move_source, (xboard_move_destination >> 1), chess);
	}
	update_board(chess);
}

void Legal_Moves :: pawn_promotion(string color, BitBoard &color_board, ChessBoard &chess,
					unsigned long long int source, unsigned long long int destination){

	//color reprezinta culoarea pionului "promovat"

	//Se extrage piesa din tabla pionilor
	if(color == "black"){
		chess.black_pawns.current_form = chess.black_pawns.current_form ^ destination;
	}
	else{
		chess.white_pawns.current_form = chess.white_pawns.current_form ^ destination;
	}

	//Fostul pion se adauga pe placa reginei
	if(color == "black"){
		chess.black_queen.current_form = chess.black_queen.current_form | destination;
	} else {	
		chess.white_queen.current_form = chess.white_queen.current_form | destination;
	}
	update_board(chess);
}

void Legal_Moves :: delete_piece(string attacked_color, BitBoard &white_board, BitBoard &black_board, 
                BitBoard &AttackedBoard, unsigned long long destination){
	//Se extrage piesa din placa de aceeasi culoare cu a sa
	if(attacked_color == "white"){
	    white_board.current_form = white_board.current_form ^ destination ;
	}
	else{
	    black_board.current_form = black_board.current_form ^ destination ;
	}

	//Se extrage piesa din placa atacata
	AttackedBoard.current_form = AttackedBoard.current_form ^ destination ; 
}

void Legal_Moves :: attack_move (unsigned long long int destination, ChessBoard &chess){

	/*Se realizeaza miscarea de atac asupra placii din care face parte
	destinatia(atac asupra altei placi) */
	if((destination & chess.black_pawns.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_pawns, destination);
	}
	if((destination & chess.black_rooks.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_rooks, destination);
	}
	if((destination & chess.black_bishops.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_bishops, destination);
	}
	if((destination & chess.black_knights.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_knights, destination);
	}
	if((destination & chess.black_queen.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_queen, destination);
	}
	if((destination & chess.black_king.current_form) != 0){
		delete_piece("black", chess.white_board, chess.black_board, chess.black_king, destination);
	}
	if((destination & chess.white_pawns.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_pawns, destination);
	}
	if((destination & chess.white_rooks.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_rooks, destination);
	}
	if((destination & chess.white_bishops.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_bishops, destination);
	}
 	if((destination & chess.white_knights.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_knights, destination);
	}
	if((destination & chess.white_queen.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_queen, destination);
	}
	if((destination & chess.white_king.current_form) != 0){
		delete_piece("white", chess.white_board, chess.black_board, chess.white_king, destination);
	}
}

void Legal_Moves :: attack_move_pawn(unsigned long long int destination, ChessBoard &chess) {
	if ((destination & chess.black_board.en_passant) != 0) {
		delete_piece("black", chess.white_board, chess.black_board, chess.black_pawns, destination >> 8);
	}
	else if ((destination & chess.white_board.en_passant) != 0) {
		delete_piece("white", chess.white_board, chess.black_board, chess.white_pawns, destination << 8);
	}
	attack_move(destination, chess);
}

Piece Legal_Moves :: pawn_moves(bool first_move, string pos, string color, ChessBoard &chess){

	Piece pawn;
	pawn.number_of_moves = 0; //mutari posibile din pozitia curenta
	unsigned long long position = pos_to_64bits(pos);
	unsigned long long aux = position;

	int index = index_bit(position);
	int j;

	if(color == "white") {
		j = 0;
		pawn.number_of_moves = 0;
		if(first_move == true) {

			//Pionul are voie sa se mute 2 pozitii in fata
			if(index < 48 && ((chess.black_board.current_form & (position << 8)) == 0) && 
				((chess.white_board.current_form & (position << 8)) == 0) &&
				((chess.black_board.current_form & (position << (8*2))) == 0) && 
				((chess.white_board.current_form & (position << (8*2))) == 0) ){
				
				position = aux ;
				pawn.possible_moves[j] = bits_to_position_string(position << (8 * 2));
				pawn.number_of_moves++;
				j++;
			}
		}
		//Pionul se muta o singura pozitie in fata
		if(index < 56 && ((chess.black_board.current_form & (position << 8)) == 0) &&
			((chess.white_board.current_form & (position << 8)) == 0) ){
			position = aux ;
			pawn.possible_moves[j] = bits_to_position_string(position << 8);
			pawn.number_of_moves++;
			j++;
		}
		
		//Mutari de atac

		//Diagonala stanga
		position = aux ;
		if((index % 8 != 0) && index < 56 && 
			(((chess.black_board.current_form & (position << 7)) != 0) || 
			(((position << 7) & chess.black_board.en_passant) != 0))) {

			pawn.possible_moves[j] = bits_to_position_string(position << 7);
			pawn.number_of_moves++;
			j++;
		}

		// En passant diagonala dreapta

		//Diagonala dreapta
		position = aux ;
		if(((index + 1) % 8 != 0) && index < 56 
			&& (((chess.black_board.current_form & (position << 9)) != 0) ||
				(((position << 9) & chess.black_board.en_passant) != 0))) {
			pawn.possible_moves[j] = bits_to_position_string(position << 9);
			pawn.number_of_moves++;
			j++;
		}
	}
	else {
		j = 0 ;
		pawn.number_of_moves = 0 ;
		if(first_move == true){

			if(index > 15 && ((chess.black_board.current_form & (position >> 8)) == 0) && 
				((chess.white_board.current_form & (position >> 8)) == 0) &&
				((chess.black_board.current_form & (position >> (8*2))) == 0) &&
				((chess.white_board.current_form & (position >> (8*2))) == 0)) {
				
				//Pionul are voie sa se mute 2 pozitii in fata
				position = aux ;
				pawn.possible_moves[j] = bits_to_position_string(position >> (8*2));
				pawn.number_of_moves++;
				j++;
			}
		}

		if(index > 7 && ((chess.black_board.current_form & (position >> 8)) == 0) && 
			((chess.white_board.current_form & (position >> 8)) == 0)){
				
			//Pionul se muta o singura pozitie in fata
			position = aux ;
			pawn.possible_moves[j] = bits_to_position_string(position >> 8);
			pawn.number_of_moves++;
			j++;
		}

		//Mutari de atac

		//Diagonala jos dreapta
		position = aux;
		if(((index + 1) % 8 != 0) && index > 7 && 
			(((chess.white_board.current_form & (position >> 7)) != 0) ||
			(((position >> 7) & chess.white_board.en_passant) != 0 ))) {
			
			pawn.possible_moves[j] = bits_to_position_string(position >> 7);
			pawn.number_of_moves++;
			j++;

		}

		//Diagonala jos stanga
		position = aux;
		if((index % 8 != 0) && index > 7 && 
			(((chess.white_board.current_form & (position >> 9)) != 0) ||
				(((position >> 9) & chess.white_board.en_passant) != 0))) {
			pawn.possible_moves[j] = bits_to_position_string(position >> 9);
			pawn.number_of_moves++;
			j++;

		}
	}
	return pawn;
}

Piece Legal_Moves :: rooks_moves(string pos, string color, ChessBoard &chess){
 
 	Piece rook;
 	BitBoard opposite_board, my_board;
	if(color == "white"){
		opposite_board = chess.black_board;
		my_board = chess.white_board;
	}
	else{
		opposite_board = chess.white_board;
		my_board = chess.black_board;
	}

	rook.number_of_moves = 0 ; //mutari posibile din pozitia curenta
	unsigned long long position = pos_to_64bits(pos);
	unsigned long long  aux = position;
	int crossed_pieces;

	int index = index_bit(position);
	int j, i;

	j = 0 ;
	rook.number_of_moves = 0 ;

	crossed_pieces = 0;
	for(i = 1 ; i <= (7 - (index / 8)) ; i++){
		//numarul de pozitii in sus pe care poate sa le urce turnul
		position = aux ;

		if(crossed_pieces == 0 &&
			((position << (8*i)) & my_board.current_form) == 0){

			rook.possible_moves[j] = bits_to_position_string(position << (8*i));
			rook.number_of_moves++;
			j++;

			if( ((position << (8*i)) & opposite_board.current_form) != 0){
				crossed_pieces++ ;
			}	
		}
		else{
			break ;
		}
	}

	crossed_pieces = 0 ;
	for(i = 1 ; i <= (index) / 8 ; i++){
		//Numarul de pozitii pe care poate sa le coboare turnul
		position = aux ;

		if(crossed_pieces == 0 &&
			((position >> (8*i)) & my_board.current_form) == 0){

			rook.possible_moves[j] = bits_to_position_string(position >> (8*i));
			rook.number_of_moves++ ;
			j++;

			if( ((position >> (8*i)) & opposite_board.current_form) != 0){
				crossed_pieces++ ;
			}
		}
		else{
			i = 9;
		}
			
	}

	crossed_pieces = 0;

	for(i = 1 ; i <= (index) % 8 ; i++){
		//Numarul de pozitii pe care poate sa se mute la stanga
		position = aux;

		if(crossed_pieces == 0 &&
			((position >> i) & my_board.current_form) == 0){
			rook.possible_moves[j] = bits_to_position_string(position >> i);
			rook.number_of_moves++;
			j++;

			if( ((position >> i) & opposite_board.current_form) != 0){
				crossed_pieces++;
			}
		}		
		else{
			break;
		}	
	}
	crossed_pieces = 0 ;
	for(i = 1 ; i <= (7 - (index) % 8) ; i++){
		//Numarul de pozitii pe care poate sa se mute la dreapta
		position = aux;

		if(crossed_pieces == 0 &&
			((position << i) & my_board.current_form) == 0){

			rook.possible_moves[j] = bits_to_position_string(position << i);
			rook.number_of_moves++;
			j++;

			if( ((position << i) & opposite_board.current_form) != 0){
				crossed_pieces++;
			}
		}
		else{
			break;
		}
			
	}

	return rook;
}

Piece Legal_Moves :: knight_moves(string pos, string color, ChessBoard &chess){
	Piece knight ;
	BitBoard  my_board ;
	if(color == "white"){
		my_board = chess.white_board;
	}
	else{
		my_board = chess.black_board;
	}

	knight.number_of_moves = 0 ; //mutari posibile din pozitia curenta
	unsigned long long position = pos_to_64bits(pos);
	
	int index = index_bit(position);
	int j, i;

	j = 0 ;
	
	//Micari in stanga/dreapta jos vertical

	if((index / 8) >= 2) {
		if((index % 8) >= 0 && (index % 8) < 7 && (((position >> 15) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position >> 15);
			j++;
			knight.number_of_moves++;
		}
		if((index % 8) > 0 && (index % 8) <= 7 && (((position >> 17) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position >> 17);
			j++;
			knight.number_of_moves++;
		}
	}

	//Miscari in stanga/dreapta sus vertical

	if((index / 8) < 6){
		if((index % 8) >= 0 && (index % 8) < 7 && (((position << 17) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position << 17);
			j++;
			knight.number_of_moves++;
		}
		if((index % 8) > 0 && (index % 8) <= 7 && (((position << 15) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position << 15);
			j++;
			knight.number_of_moves++;
		}
	}

	//Miscari stanga/dreapta jos orizontal
	if((index / 8) >= 1){
		if((index % 8) >= 0 && (index % 8) < 6 && (((position >> 6) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position >> 6);
			j++;
			knight.number_of_moves++;
		}
		if((index % 8) > 1 && (index % 8) <= 7 && (((position >> 10) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position >> 10);
			j++;
			knight.number_of_moves++;
		}
	}

	//Miscari stanga/dreapta sus orizontal

	if((index / 8) < 7){
		if((index % 8) >= 0 && (index % 8) < 6 && (((position << 10) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position << 10);
			j++ ;
			knight.number_of_moves++;
		}
		if((index % 8) > 1 && (index % 8) <= 7 && (((position << 6) & my_board.current_form) == 0) ){
			knight.possible_moves[j] = bits_to_position_string(position << 6);
			j++;
			knight.number_of_moves++;
		}
	}

	return knight;
}

Piece Legal_Moves :: bishop_moves(string pos, string color, ChessBoard &chess){

	Piece bishop;
	BitBoard opposite_board, my_board ;
	if(color == "white"){
		opposite_board = chess.black_board;
		my_board = chess.white_board ;
	}
	else{
		opposite_board = chess.white_board;
		my_board = chess.black_board;
	}

	bishop.number_of_moves = 0 ; //mutari posibile din pozitia curenta
	unsigned long long position = pos_to_64bits(pos);
	unsigned long long  aux = position;
	int crossed_pieces;
	
	int j = 0;
	
	//Diagonala dreapta sus
	crossed_pieces = 0 ;
	while(crossed_pieces == 0 && index_bit(position) <= 54 &&
			(index_bit(position << 9)) <= 63 &&
			((index_bit(position << 1)) % 8) != 0 && 
			(((position << 9) & my_board.current_form) == 0)){

		position = (position << 9) ;
		bishop.possible_moves[j] = bits_to_position_string(position);
		j++;
		bishop.number_of_moves++;
		if((position & opposite_board.current_form) != 0){
			crossed_pieces++ ;
		}

	}

	//Diagonala dreapta jos
	position = aux ;
	crossed_pieces = 0;
	while(crossed_pieces == 0 && index_bit(position) >= 8 &&
			(index_bit(position >> 7)) >= 0 &&
			((index_bit(position << 1) % 8) != 0) && 
			(((position >> 7) & my_board.current_form) == 0)){

		position = (position >> 7) ;
		bishop.possible_moves[j] = bits_to_position_string(position);
		j++;
		bishop.number_of_moves++;
		if((position & opposite_board.current_form) != 0){
			crossed_pieces++ ;
		}
	}

	//Diagonala stanga sus
	position = aux ;
	crossed_pieces = 0;
	while(crossed_pieces == 0 && index_bit(position) <= 55 &&
			(index_bit(position << 7)) <=  63 &&
			((index_bit(position)) % 8) != 0 && 
			(((position << 7) & my_board.current_form) == 0)){

		position = (position << 7);
		bishop.possible_moves[j] = bits_to_position_string(position);
		j++;
		bishop.number_of_moves++;
		if((position & opposite_board.current_form) != 0){
			crossed_pieces++ ;
		}

	}
	//Diagonala stanga jos
	position = aux ;
	crossed_pieces = 0;
	while(crossed_pieces == 0 && index_bit(position) >= 9 &&
			(index_bit(position >> 9)) >=  0 &&
			((index_bit(position)) % 8) != 0 && 
			(((position >> 9) & my_board.current_form) == 0)){

		position = position >> 9 ;
		bishop.possible_moves[j] = bits_to_position_string(position);
		j++;
		bishop.number_of_moves++;
		if((position & opposite_board.current_form) != 0){
			crossed_pieces++ ;
		}

	}

	return bishop;
}

Piece Legal_Moves :: queen_moves(string pos, string color, ChessBoard &chess){

	Piece queen ;
	Piece bishop, rook;
	bishop = bishop_moves(pos, color, chess);
	rook = rooks_moves(pos, color, chess);
	int i,j;

	queen.number_of_moves = 0 ; //mutari posibile din pozitia curenta
	queen.number_of_moves += bishop.number_of_moves ;
	queen.number_of_moves += rook.number_of_moves ;

	for(i = 0; i < rook.number_of_moves; i++){

		queen.possible_moves[i] = rook.possible_moves[i];
	}

	j = 0 ;
	for(i = rook.number_of_moves; i < queen.number_of_moves; i++){

		queen.possible_moves[i] = bishop.possible_moves[j];
		j++;
	}

	return queen ;
}

// verifica daca nu sunt piese intre tura si rege
// returneaza 0 daca nu se poate face nicio rocada
// 1 daca se poate face cu tura din stanga
// 2 daca se poate face cu tura din dreapta
// 3 daca se poate face cu ambele
int Legal_Moves :: no_pieces_rook_king(string color, BitBoard my_rooks,
						BitBoard my_board, BitBoard opposite_board) {

	int first = 1, second = 2, result = 0;
	unsigned long long int aux = 0;

	if ((color == "white" && 
		((1ULL) & my_rooks.current_form) == 0) ||
		(color == "black" && 
		((1ULL << 56) & my_rooks.current_form) == 0)){

		first = 0;

	} else {
		for (int i = 1; i <= 3; i++) {
			if (color == "white") {
				aux = (1ULL << i);
				if 	((aux & my_board.current_form) != 0 || 
					(aux & opposite_board.current_form) != 0) {
					first = 0;
					break;
				}
			} else {
				aux = (1ULL << (i + 56));
				if 	((aux & my_board.current_form) != 0 ||
					(aux & opposite_board.current_form) != 0) {
					first = 0;
					break;
				}
			}
		}
	}

	if ((color == "white" && 
		((1ULL << 7) & my_rooks.current_form) == 0) ||
		(color == "black" && 
		((1ULL << 63) & my_rooks.current_form) == 0)){

		second = 0;
	} else {
		for (int i = 5; i <= 6; i++) {
			if (color == "white") {
				aux = (1ULL << i);
				if ((aux & my_board.current_form) != 0 ||
					(aux & opposite_board.current_form) != 0) {
					second = 0;
					break;
				}
			} else {
				aux = (1ULL << (i + 56));
				if ((aux & my_board.current_form) != 0 ||
					(aux & opposite_board.current_form) != 0) {
					second = 0;
					break;
				}
			}
		}
	}

	result = first + second;
	return result;
}

bool Legal_Moves :: no_moves_left(string color, BitBoard pawns, BitBoard rooks,
					BitBoard knights, BitBoard bishops, BitBoard queen, 
					BitBoard king, BitBoard black_board, BitBoard white_board,
					ChessBoard &chess) {

    Piece current_piece; //instanta pentru a putea folosi obiectul returnat de pawn_moves
    string position; //Spre exemplu "e2", "a7", etc
    int i,k;
    unsigned long long int current_position;
    bool first_move;
    int number_of_moves = 0;

    for(i = 0; i < 64; i++){

        current_position = (1ULL << i);
        if((current_position & pawns.current_form) != 0){
            //Pe pozitia gasita se afla un pion
            position = bits_to_position_string(current_position);
            first_move = check_first_move(color, position);
            current_piece = pawn_moves(first_move, position, color , chess);
            number_of_moves += current_piece.number_of_moves;

        } else if ((current_position & rooks.current_form) != 0) {
        	position = bits_to_position_string(current_position);
        	current_piece = rooks_moves(position, color , chess);
            number_of_moves += current_piece.number_of_moves;

        } else if ((current_position & knights.current_form) != 0) {
        	position = bits_to_position_string(current_position);
        	current_piece = knight_moves(position, color , chess);
            number_of_moves += current_piece.number_of_moves;

        } else if ((current_position & bishops.current_form) != 0) {
        	position = bits_to_position_string(current_position);
        	current_piece = bishop_moves(position, color , chess);
            number_of_moves += current_piece.number_of_moves;

        } else if ((current_position & queen.current_form) != 0) {
        	position = bits_to_position_string(current_position);
        	current_piece = queen_moves(position, color , chess);
            number_of_moves += current_piece.number_of_moves;

        } else if ((current_position & king.current_form) != 0) {
        	position = bits_to_position_string(current_position);
        	current_piece = king_moves(position, color , chess);
            number_of_moves += current_piece.number_of_moves;
        }
    }

    if(number_of_moves == 0){
        return true;
    }

    return false;
}

bool Legal_Moves :: is_check (string color, unsigned long long int king_position, 
					ChessBoard &chess){
	int i, j;
	unsigned long long int current_position;
	BitBoard my_board, opposite_board;
	BitBoard opposite_pawns, opposite_rooks, opposite_bishops;
	BitBoard opposite_knights, opposite_king, opposite_queen;
	Piece current_piece;
	string position;
	string opposite_color;
	bool first_move;
	
	/*Pentru verificarea pozitiei de sah a regelui negru, se verifica
	pozitiile pieselor albe si invers*/
	if(color == "black"){
		my_board = chess.black_board;
		opposite_board = chess.white_board;
		opposite_pawns = chess.white_pawns;
		opposite_rooks = chess.white_rooks;
		opposite_knights = chess.white_knights;
		opposite_bishops = chess.white_bishops;
		opposite_king = chess.white_king;
		opposite_queen = chess.white_queen;
	} else {
		my_board = chess.white_board;
		opposite_board = chess.black_board;
		opposite_pawns = chess.black_pawns;
		opposite_rooks = chess.black_rooks;
		opposite_knights = chess.black_knights;
		opposite_bishops = chess.black_bishops;
		opposite_king = chess.black_king;
		opposite_queen = chess.black_queen;
	}

	my_board.current_form = (my_board.current_form ^ king_position);

	position = bits_to_position_string(king_position);
	
	//Indexarea coloanelor porneste de la 1
	int column = (position[0] - 'a') + 1; 
	int line = (position[1] - '0');
	int current_col, current_line;

	//Verificare dreapta
	current_position = king_position;
	current_col = column;

	//Verifica intersectia cu regele oponentului
	if(current_col < 8 && ((current_position << 1) & opposite_king.current_form) != 0) {
		return true;
	}

	while(current_col < 8 && (current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0){
		
		current_position = (current_position << 1);
		current_col++;
	}

	//Verifica intersectia cu tura/regina oponentului
	if(((current_position & opposite_rooks.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare stanga
	current_position = king_position;
	current_col = column;

	//Verifica intersectia cu regele oponentului
	if(current_col > 1 && ((current_position >> 1) & opposite_king.current_form) != 0) {
		return true;
	}

	while(current_col > 1 && (current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position >> 1);
		current_col--;
	}

	//Verifica intersectia cu tura/regina oponentului
	if(((current_position & opposite_rooks.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare sus
	current_position = king_position;
	current_line = line; 

	//Verifica intersectia cu regele oponentului
	if(current_line < 8 && ((current_position << 8) & opposite_king.current_form) != 0) {
		return true;
	}

	while((current_line < 8) && (current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position << 8);		
		current_line++;
	}

	//Verifica intersectia cu tura/regina oponentului
	if(((current_position & opposite_rooks.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare jos
	current_position = king_position;
	current_line = line;

	//Verifica intersectia cu regele oponentului
	if(current_line > 1 && ((current_position >> 8) & opposite_king.current_form) != 0) {
		return true;
	}

	while((current_line > 1) && (current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position >> 8);
		current_line--;
	}

	//Verifica intersectia cu tura/regina oponentului
	if(((current_position & opposite_rooks.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare diagonala dreapta sus
	current_position = king_position;
	current_col = column;
	current_line = line;

	//Verifica intersectia cu regele/pionii oponentului negru
	if(current_col < 8 && current_line < 8 &&
		(((current_position << 9) & opposite_king.current_form) != 0 ||
		((color == "white") && 
		((current_position << 9) & opposite_pawns.current_form) != 0))) {
		return true;
	}

	while((current_line < 8) && (current_col < 8) &&
		(current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position << 9);
		current_col++;
		current_line++;
	}

	//Verifica intersectia cu nebunii/regina oponentului
	if(((current_position & opposite_bishops.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare diagonala stanga sus
	current_position = king_position;
	current_col = column;
	current_line = line;

	//Verifica intersectia cu regele/pionii oponentului negru
	if(current_col > 1 && current_line < 8 &&
		(((current_position << 7) & opposite_king.current_form) != 0 ||
		((color == "white") &&
		((current_position << 7) & opposite_pawns.current_form) != 0))) {
		return true;
	}
	
	while((current_col > 1) && (current_line < 8) &&
		(current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position << 7);
		current_col--;
		current_line++;
	}

	//Verifica intersectia cu nebunii/regina oponentului
	if(((current_position & opposite_bishops.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare diagonala dreapta jos
	current_position = king_position;
	current_col = column;
	current_line = line;

	//Verifica intersectia cu regele/pionii oponentului alb
	if(current_col < 8 && current_line > 1 &&
		(((current_position >> 7) & opposite_king.current_form) != 0 ||
		((color == "black") &&
		((current_position >> 7) & opposite_pawns.current_form) != 0))) {
		return true;
	}
	
	while((current_col < 8) && (current_line > 1) && 
		(current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position >> 7);
		current_col++;
		current_line--;
	}

	//Verifica intersectia cu nebunii/regina oponentului
	if(((current_position & opposite_bishops.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare diagonala stanga jos
	current_position = king_position;
	current_col = column;
	current_line = line;

	//Verifica intersectia cu regele/pionii oponentului negru
	if(current_col > 1 && current_line > 1 &&
		(((current_position >> 9) & opposite_king.current_form) != 0 ||
		((color == "black") &&
		((current_position >> 9) & opposite_pawns.current_form) != 0))) {
		return true;
	}
	
	while ((current_col > 1) && (current_line > 1) && 
		(current_position & my_board.current_form) == 0 &&
		(current_position & opposite_board.current_form) == 0) {
		current_position = (current_position >> 9);
		current_line--;
		current_col--;
	}

	//Verifica intersectia cu nebunii/regina oponentului
	if(((current_position & opposite_bishops.current_form) != 0) ||
		((current_position & opposite_queen.current_form) != 0)) {
		return true;
	}

	//Verificare intersectie cai-rege
	current_position = king_position;
	current_col = column;
	current_line = line;

	if(((current_col < 7 && current_line > 1) && 
		((current_position >> 6) & opposite_knights.current_form) != 0) ||

		((current_col > 2 && current_line > 1) && 
		((current_position >> 10) & opposite_knights.current_form) != 0) ||

		((current_col > 1 && current_line > 2) && 
		((current_position >> 17) & opposite_knights.current_form) != 0) ||

		((current_col < 8 && current_line > 2) && 
		((current_position >> 15) & opposite_knights.current_form) != 0) ||

		((current_col > 2 && current_line < 8) && 
		((current_position << 6) & opposite_knights.current_form) != 0) ||

		((current_col < 7 && current_line < 8) && 
		((current_position << 10) & opposite_knights.current_form) != 0) ||

		((current_col < 8 && current_line < 7) && 
		((current_position << 17) & opposite_knights.current_form) != 0) ||

		((current_col > 1 && current_line < 7) && 
		((current_position << 15) & opposite_knights.current_form) != 0)) {

		return true;
	}
	return false;
}
bool Legal_Moves :: multiple_positions_check(string color, unsigned long long int king_position, 
								unsigned long long int destination, ChessBoard &chess){

	unsigned long long int temp_king_pos = king_position;
	unsigned long long int aux = king_position;
	ChessBoard chess_copy = chess;

	if(destination > temp_king_pos){
		//Mutare spre dreapta
		make_move(king_position, temp_king_pos, chess_copy);
		while((!is_check(color, temp_king_pos, chess_copy)) &&
			temp_king_pos < destination){
			aux = temp_king_pos;
			temp_king_pos = (temp_king_pos << 1);
			make_move(aux, temp_king_pos, chess_copy);
		}
	}
	else{
		//Mutare spre stanga
		make_move(king_position, temp_king_pos, chess_copy);
		while((!is_check(color, temp_king_pos, chess_copy)) &&
			temp_king_pos > destination){
			aux = temp_king_pos;
			temp_king_pos = (temp_king_pos >> 1);
			make_move(aux, temp_king_pos, chess_copy);
		}
	}

	if(temp_king_pos == destination){
		return true;
	}
	return false;
}


Piece Legal_Moves :: king_moves(string pos, string color, ChessBoard &chess){
	Piece king;
	BitBoard opposite_board, my_board, my_rooks;
	if(color == "white"){
		opposite_board = chess.black_board;
		my_board = chess.white_board;
		my_rooks = chess.white_rooks;
	}
	else{
		opposite_board = chess.white_board;
		my_board = chess.black_board;
		my_rooks = chess.black_rooks;
	}

	king.number_of_moves = 0; //mutari posibile din pozitia curenta
	unsigned long long position = pos_to_64bits(pos);
	unsigned long long aux = position;
	
	int index = index_bit(position);
	int j, i;

	j = 0;

	if((index / 8) > 0) {
		//Se poate muta o pozitie in jos
		if(((position >> 8) & my_board.current_form) == 0){
			king.possible_moves[j] = bits_to_position_string(position >> 8);
			j++;
		}
		if((index % 8) >= 0 && (index % 8) < 7 && ((position >> 7) & my_board.current_form) == 0){
			//Se poate muta o pozitie diagonala dreapta jos
			king.possible_moves[j] = bits_to_position_string(position >> 7);
			j++;
		}
		if((index % 8) > 0 && (index % 8) <= 7 && ((position >> 9) & my_board.current_form) == 0){
			//Se poate muta o pozitie diagonala stanga jos
			king.possible_moves[j] = bits_to_position_string(position >> 9);
			j++;
		}
	}
	if((index / 8) < 7){
		//Se poate muta o pozitie in sus
		if(((position << 8) & my_board.current_form) == 0){
			king.possible_moves[j] = bits_to_position_string(position << 8);
			j++;
		}
		if((index % 8) >= 0 && (index % 8) < 7 && ((position << 9) & my_board.current_form) == 0){
			//Se poate muta o pozitie diagonala dreapta sus
			king.possible_moves[j] = bits_to_position_string(position << 9);
			j++;
		}
		if((index % 8) > 0 && (index % 8) <= 7 && ((position << 7) & my_board.current_form) == 0){
			//Se poate muta o pozitie diagonala stanga sus
			king.possible_moves[j] = bits_to_position_string(position << 7);
			j++;
		}
	}

	if((index % 8) > 0 && ((position >> 1) & my_board.current_form) == 0){
		//Se poate muta o pozitie la stanga
		king.possible_moves[j] = bits_to_position_string(position >> 1);
		j++;
	}

	if((index % 8) < 7 && ((position << 1) & my_board.current_form) == 0){
		//Se poate muta o pozitie la dreapta
		king.possible_moves[j] = bits_to_position_string(position << 1);
		j++;
	}

	int count_castling = no_pieces_rook_king(color, my_rooks,my_board, opposite_board); 

	if (count_castling == 0) {
		king.number_of_moves = j;
		return king;
	}
	int crossed_pieces = 0;

	// rocada pentru culoarea alba
	int check_castling = 0;
	unsigned long long int destination ;

	if (color == "white") {
		check_castling = no_pieces_rook_king("white", my_rooks,
										my_board, opposite_board);

		if (my_board.first_move_king == true) {
			if (my_board.first_move_rook1 == true) {
				if (check_castling == 1 || check_castling == 3) {
					destination = pos_to_64bits("c1");
					if(multiple_positions_check(color, position,destination,chess)){
						king.possible_moves[j] = "c1";
						j++;
					}
				}
			}

			if (my_board.first_move_rook2 == true) {
				if (no_pieces_rook_king("white", my_rooks,
									my_board, opposite_board)) {

					if (check_castling == 2 || check_castling == 3) {
						destination = pos_to_64bits("g1");
						if(multiple_positions_check(color, position,destination,chess)){
							king.possible_moves[j] = "g1";
							j++;
						
						}
					}
				}
			}
		}
	} else {
		check_castling = no_pieces_rook_king("black", my_rooks,
											my_board, opposite_board);

		if (my_board.first_move_king == true) {
			if (my_board.first_move_rook1 == true) {
				if (check_castling == 1 || check_castling == 3) {
					destination = pos_to_64bits("c8");
					if(multiple_positions_check(color, position,destination,chess)){
						king.possible_moves[j] = "c8";
						j++;
						
					}
				}
			}
			
			if (my_board.first_move_rook2 == true) {
				if (check_castling == 2 || check_castling == 3) {
					destination = pos_to_64bits("g8");
					if(multiple_positions_check(color, position,destination,chess)){
						king.possible_moves[j] = "g8";
						j++;
						
					}
				}
			}
		}
	}

	king.number_of_moves = j;
	return king;
}

void Legal_Moves :: xboard_move(char input[], ChessBoard &chess){

	Board f;
	string xboard_move(input), color;
	string xboard_move_from, xboard_move_to;
	xboard_move_from = xboard_move.substr(0,2);
	xboard_move_to = xboard_move.substr(2,4);

	BitBoard engine_pawns;
	unsigned long long int king_position;
	bool is_pawn = false;
	
	if(chess.board.engine_color == "black"){
		color = "white";
		engine_pawns = chess.black_pawns;
		king_position = chess.black_king.current_form;
	}
	else{
		color = "black";
		engine_pawns = chess.white_pawns;
		king_position = chess.white_king.current_form;
	}
	
	unsigned long long int xboard_move_source, xboard_move_destination;
	xboard_move_source = pos_to_64bits(xboard_move_from);

	//Se verifica daca piesa mutata este un pion
	if(chess.board.engine_color == "black" && (xboard_move_source & chess.white_pawns.current_form) != 0){
		is_pawn = true;
	}
	else if(chess.board.engine_color == "white" && (xboard_move_source & chess.black_pawns.current_form) != 0){
		is_pawn = true;
	}

	xboard_move_destination = pos_to_64bits(xboard_move_to);
	
	//Destinatia(atac asupra altei placi)
	if (is_pawn == false) {
		attack_move(xboard_move_destination, chess);
	} else {
		attack_move_pawn(xboard_move_destination, chess);
	}

	//Se executa miscarea trasmisa de xboard
	make_move(xboard_move_source, xboard_move_destination, chess);

	int index_dest, index_source, dif_index;
	index_dest = index_bit(xboard_move_destination);
	index_source = index_bit(xboard_move_source);
	dif_index = abs(index_dest - index_source);

    if (is_pawn && check_first_move(color, xboard_move_from)) {
    	if (color == "black" && dif_index == 16) {
    		chess.black_board.en_passant = xboard_move_destination << 8;
    	} else if (color == "white" && dif_index == 16) {
    		chess.white_board.en_passant = xboard_move_destination >> 8;
    	}
	}       

	//Check for pawn promotion
	if((chess.board.engine_color == "black") && index_bit(xboard_move_destination) > 55
			&& is_pawn == true){
		pawn_promotion("white", chess.white_board, chess,
						xboard_move_source, xboard_move_destination);
			
    }
	else if((chess.board.engine_color == "white") && index_bit(xboard_move_destination) < 8
			&& is_pawn == true){
		pawn_promotion("black", chess.black_board, chess,
						xboard_move_source, xboard_move_destination);
	}

	if (color == "black") {
		chess.white_board.en_passant = 0;
	} else {
		chess.black_board.en_passant = 0;
	}

	// Check for endgame phase
	if (countSetBits(chess.board.current_form) <= 12) {
		chess.endgame = true;
	}

	update_board(chess);
}
