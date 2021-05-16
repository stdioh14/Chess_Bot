#ifndef TRANSPOSITION
#define TRANSPOSITION

#include <bits/stdc++.h>
#include "Board.h" 
using namespace std;

#define TABLESIZE (1024 * 1024 * 60)

#define PAWNS 0
#define ROOKS 1
#define KNIGHTS 2
#define BISHOPS 3
#define QUEENS 4
#define KINGS 5

#define EXACT 0
#define LOWER 1
#define UPPER 2

class HashEntry {
	public:
		unsigned long long zobrist;
		int depth;
		int value;
		int flag;
		string move;

		void init(unsigned long long z, int d, int e, int f);
};

class Zobrist {
	public:
		unsigned long long pieces[6][2][64];
		unsigned long long white_castle[4]; // 0 = both, 1 = short, 2 = long, 3 = none
		unsigned long long black_castle[4];
		unsigned long long computeHash(ChessBoard &, int); 
		bool isInit = false;
		unsigned long long side;
		Zobrist();
};

class HashTable {
	public: 
		unordered_map<unsigned long long, HashEntry> table;
		Zobrist z;
		void add(unsigned long long, HashEntry);
		bool exists(unsigned long long);
		HashEntry getEntry(unsigned long long);
		void clearTable();
};


#endif