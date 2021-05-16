#include <bits/stdc++.h> 
#include "Transposition.h"
#include "Legal_Moves.h"
#include "Board.h"
using namespace std;

void HashTable :: add(unsigned long long hashKey, HashEntry entry) {
	long index = (hashKey % TABLESIZE);
	table[index] = entry;
}

bool HashTable :: exists(unsigned long long hashKey) {
	long index = (hashKey % TABLESIZE);
	if (table.find(index) == table.end()) {
		return false;
	}
	return true;
}

HashEntry HashTable :: getEntry(unsigned long long hashKey) {
	long index = hashKey % TABLESIZE;
	return table[index];
}

void HashTable :: clearTable() {
	table.clear();
}

void HashEntry :: init(unsigned long long z, int d, int e, int f) {
	this -> zobrist = z;
	this -> depth = d;
	this -> value = e;
	this -> flag = f;
}

Zobrist :: Zobrist() {
	random_device randomDevice;
	mt19937_64 gen64bit(randomDevice());
	uniform_int_distribution<unsigned long long> dis(0, UINT64_MAX);

	if (!isInit) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 64; k++) {
					pieces[i][j][k] = dis(gen64bit);
				}
			}
		}
		side = dis(gen64bit);
		
		for (int i = 0; i < 4; i++) {
			white_castle[i] = dis(gen64bit);
		}	

		for (int i = 0; i < 4; i++) {
			black_castle[i] = dis(gen64bit);
		}

		isInit = true;
	}
}

unsigned long long Zobrist :: computeHash(ChessBoard &chess, int player) {
	unsigned long long hash = 0, position;
	int index;
	Legal_Moves legal;

	BitBoard white = chess.white_board;
	BitBoard black = chess.black_board;

	for (int i = 0; i < 64; i++) {
		position = (1ULL << i);
		if ((position & black.current_form) != 0) {
			if ((position & chess.black_pawns.current_form) != 0) {
				hash ^= pieces[PAWNS][0][i];
			} else if ((position & chess.black_rooks.current_form) != 0) {
				hash ^= pieces[ROOKS][0][i];
			} else if ((position & chess.black_knights.current_form) != 0) {
				hash ^= pieces[KNIGHTS][0][i];
			} else if ((position & chess.black_bishops.current_form) != 0) {
				hash ^= pieces[BISHOPS][0][i];
			} else if ((position & chess.black_queen.current_form) != 0) {
				hash ^= pieces[QUEENS][0][i];
			} else if ((position & chess.black_king.current_form) != 0) {
				hash ^= pieces[KINGS][0][i];
			}
		} else if ((position & white.current_form) != 0) {
			if ((position & chess.white_pawns.current_form) != 0) {
				hash ^= pieces[PAWNS][1][i];
			} else if ((position & chess.white_rooks.current_form) != 0) {
				hash ^= pieces[ROOKS][1][i];
			} else if ((position & chess.white_knights.current_form) != 0) {
				hash ^= pieces[KNIGHTS][1][i];
			} else if ((position & chess.white_bishops.current_form) != 0) {
				hash ^= pieces[BISHOPS][1][i];
			} else if ((position & chess.white_queen.current_form) != 0) {
				hash ^= pieces[QUEENS][1][i];
			} else if ((position & chess.white_king.current_form) != 0) {
				hash ^= pieces[KINGS][1][i];
			}
		}
	}

	if (white.castled == true) {
		hash ^= white_castle[3];
	} else {
		if (white.first_move_king == true) {
			if (white.first_move_rook1 && white.first_move_rook2) {
				hash ^= white_castle[0];
			} else if (white.first_move_rook1) {
				hash ^= white_castle[2];
			} else if (white.first_move_rook2) {
				hash ^= white_castle[1];
			} else {
				hash ^= white_castle[3];
			}

		} else {
			hash ^= white_castle[3];
		}
	}

	if (black.castled == true) {
		hash ^= black_castle[3];
	} else {
		if (black.first_move_king == true) {
			if (black.first_move_rook1 && black.first_move_rook2) {
				hash ^= black_castle[0];
			} else if (black.first_move_rook1) {
				hash ^= black_castle[2];
			} else if (black.first_move_rook2) {
				hash ^= black_castle[1];
			} else {
				hash ^= black_castle[3];
			}

		} else {
			hash ^= black_castle[3];
		}
	}

	if (player == -1) {
		hash ^= side;
	}

	chess.crt_hash = hash;

	return hash;
}