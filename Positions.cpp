#include <bits/stdc++.h>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<string, char> init_pos(int color) {
	unordered_map<string, char> result;

	if(color = 0){		//white
		result.insert(
			{
				{"a2", 'P'}, 
				{"b2", 'P'},
				{"c2", 'P'},
				{"d2", 'P'},
				{"e2", 'P'},
				{"f2", 'P'},
				{"g2", 'P'},
				{"h2", 'P'},
				
				{"a1", 'R'}, 
				{"b1", 'N'},
				{"c1", 'B'},
				{"d1", 'Q'},
				{"e1", 'K'},
				{"f1", 'B'},
				{"g1", 'N'},
				{"h1", 'R'},
			}
		);
	} else {			//black
		result.insert(
			{
				{"a7", 'P'}, 
				{"b7", 'P'},
				{"c7", 'P'},
				{"d7", 'P'},
				{"e7", 'P'},
				{"f7", 'P'},
				{"g7", 'P'},
				{"h7", 'P'},
				
				{"a8", 'R'}, 
				{"b8", 'N'},
				{"c8", 'B'},
				{"d8", 'Q'},
				{"e8", 'K'},
				{"f8", 'B'},
				{"g8", 'N'},
				{"h8", 'R'},
			}
		);
	}

	return result;
}

