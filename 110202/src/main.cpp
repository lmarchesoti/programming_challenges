#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define NUM_CARDS 13
#define HAND_SIZE 5

using namespace std;

/* data structures */
typedef struct s_player{

	int cards[5];
	bool flush;
	bool straight;
	int freq[13]; // records frequency of each card
	int same_val[5]; // records number of same-valued cards
	int type; // type of hand
	vector<int> score; // scoring priority for comparison
} PLAYER;

/* global variables */
PLAYER black, white;

/* function prototypes */

// reads hand and initializes scoring structures of player
void init_player(PLAYER*);

// returns suit-agnostic value of a card
int value(char card);

// rank_hands the player
void rank_hand(PLAYER*);

// extracts scoring patterns from the player's hand
void extract_patterns(PLAYER *p);

// compares the two players related to their scores
int compare(PLAYER *b, PLAYER *w);

/* debug */
template class std::vector<int>;

int main(){

	int cmp; // temp comparison variable
	int t = 0;

	while((cin.peek() != '\n') && !cin.eof()){
		++t;

		// read and convert hands
		init_player(&black);
		scanf(" "); // each whitespace between hands
		init_player(&white);
		scanf("\n");

		// rank each hand
		rank_hand(&black);
		rank_hand(&white);

		// compare and print results
		cmp = compare(&black, &white);
		if(cmp == 1) printf("Black wins.\n");
		if(cmp == -1) printf("White wins.\n");
		if(cmp == 0) printf("Tie.\n");

	}

  return 0;
}

/* functions */
void init_player(PLAYER *p){

		char v1, v2, v3, v4, v5; // temp card values
		char s1, s2, s3, s4, s5; // temp card suits

		scanf("%c%c %c%c %c%c %c%c %c%c", &v1, &s1, &v2, &s2, &v3, &s3, &v4, &s4, &v5, &s5);

		p->flush = false;
		// mark if all have the same suit
		if((s1 == s2) && (s2 == s3) && (s3 == s4) && (s4 == s5)) p->flush = true;

		// keep only card values
		p->cards[0] = value(v1);
		p->cards[1] = value(v2);
		p->cards[2] = value(v3);
		p->cards[3] = value(v4);
		p->cards[4] = value(v5);

		// init scoring structures
		for(int i = 0; i < NUM_CARDS; ++i) p->freq[i] = 0;
		for(int i = 0; i < HAND_SIZE; ++i) p->same_val[i] = 0;
		p->straight = true;
		p->score.clear();

	return;
}

int value(char card){

	int v; // return value

	switch(card){

		case 'T': v = 8; break;
		case 'J': v = 9; break;
		case 'Q': v = 10; break;
		case 'K': v = 11; break;
		case 'A': v = 12; break;
		
		default: v = (card - 50) % 13;

	}

	return v;

}

void rank_hand(PLAYER* p){

	bool straight;

	// sort hand
	sort(p->cards, p->cards + HAND_SIZE);

	// extract patterns
	extract_patterns(p);

	// match patterns to types
	p->type = 0;
	if(p->same_val[2]) p->type = 1;
	if(p->same_val[2] == 2) p->type = 2;
	if(p->same_val[3]) p->type = 3;
	if(p->straight) p->type = 4;
	if(p->flush) p->type = 5;
	if(p->same_val[3] && p->same_val[2]) p->type = 6;
	if(p->same_val[4]) p->type = 7;
	if((p->straight) && (p->flush)) p->type = 8;

	// fill score priorities
	switch(p->type){

		case 0:
			for(int i = 0; i < HAND_SIZE; ++i)
				p->score.push_back(p->cards[i]);
			break;

		case 1:
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 1) p->score.push_back(i);
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 2) p->score.push_back(i);
			break;

		case 2:
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 1) p->score.push_back(i);
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 2) p->score.push_back(i);
			break;

		case 3:
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 1) p->score.push_back(i);
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 3) p->score.push_back(i);
			break;

		case 4: p->score.push_back(p->cards[HAND_SIZE-1]); break;

		case 5:
			for(int i = 0; i < NUM_CARDS; ++i)
				p->score.push_back(p->cards[i]);
			break;

		case 6:
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 3) p->score.push_back(i);
			break;

		case 7:
			for(int i = 0; i < NUM_CARDS; ++i)
				 if(p->freq[i] == 4) p->score.push_back(i);
			break;

		case 8: p->score.push_back(p->cards[HAND_SIZE-1]); break;

		default: break;

	}

	return;
}

void extract_patterns(PLAYER *p){

	// track straight
	for(int i = 0; i < 4; ++i)
		if((p->cards[i+1] - p->cards[i]) != 1) p->straight = false;

/*
	if(((p->cards[HAND_SIZE - 1] - p->cards[HAND_SIZE - 2]) != 1)
			&& ((p->cards[HAND_SIZE - 1] == 12) && (p->cards[0] != 0))) p->straight = false;
*/

	// fill frequency
	for(int i = 0; i < HAND_SIZE; ++i) ++p->freq[p->cards[i]];

	// extract final frequencies
	for(int i = 0; i < NUM_CARDS; ++i) ++p->same_val[p->freq[i]];

	return;
}

int compare(PLAYER *b, PLAYER *w){

	if(b->type > w->type) return 1;
	if(b->type < w->type) return -1;
	
	for(; (b->score.size() > 0) && (w->score.size() > 0); b->score.pop_back(), w->score.pop_back()){

		if(b->score.back() > w->score.back()) return 1;
		if(b->score.back() < w->score.back()) return -1;

	}

	return 0;
}
