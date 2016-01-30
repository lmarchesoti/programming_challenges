#include "functions.cpp"
#include <cassert>

/* test prototypes */
void test_value();

void test_rank_hand();

void high_card();

void card_pair();

void two_pairs();

void three_of_a_kind();

void straight();

void flush();

void full_house();

void four_of_a_kind();

void straight_flush();

/* register tests in main */
int main(){

  // tests here
	test_value();
	test_rank_hand();


  return 0;
}

/* test specifications */
void test_value(){

	if(value('2') != 0) cout << "Error on value of 2" << endl;
	if(value('3') != 1) cout << "Error on value of 3" << endl;
	if(value('4') != 2) cout << "Error on value of 4" << endl;
	if(value('5') != 3) cout << "Error on value of 5" << endl;
	if(value('6') != 4) cout << "Error on value of 6" << endl;
	if(value('7') != 5) cout << "Error on value of 7" << endl;
	if(value('8') != 6) cout << "Error on value of 8" << endl;
	if(value('9') != 7) cout << "Error on value of 9" << endl;
	if(value('T') != 8) cout << "Error on value of T" << endl;
	if(value('J') != 9) cout << "Error on value of J" << endl;
	if(value('Q') != 10) cout << "Error on value of Q" << endl;
	if(value('K') != 11) cout << "Error on value of K" << endl;
	if(value('A') != 12) cout << "Error on value of A" << endl;

	return;
}

void test_rank_hand(){

	PLAYER p;

	// default
	p = {{0, 0, 0, 0, 0}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	high_card();
	card_pair();
	two_pairs();
	three_of_a_kind();
	straight();
	flush();
	full_house();
	four_of_a_kind();
	straight_flush();

	return;
}

void high_card(){

	// prepare player
	PLAYER p = {{0, 1, 3, 7, 11}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	if(p.type != 0) cout << "Wrong rank to high card" << endl;

	return;
}

void card_pair(){

	// prepare player
	PLAYER p = {{0, 1, 1, 7, 11}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 1);
	assert(p.freq[1] == 2);
	assert(p.same_val[2] == 1);

	return;
}

void two_pairs(){

	// prepare player
	PLAYER p = {{0, 1, 1, 7, 7}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 2);
	assert(p.freq[1] == 2);
	assert(p.freq[7] == 2);
	assert(p.same_val[2] == 2);

	return;
}

void three_of_a_kind(){

	// prepare player
	PLAYER p = {{0, 1, 1, 1, 7}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 3);
	assert(p.freq[1] == 3);
	assert(p.same_val[3] == 1);

	return;
}

void straight(){

	// prepare player
	PLAYER p = {{0, 1, 2, 3, 4}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 4);
	assert(p.freq[0] == 1);
	assert(p.freq[1] == 1);
	assert(p.freq[2] == 1);
	assert(p.freq[3] == 1);
	assert(p.freq[4] == 1);
	assert(p.same_val[1] == 5);

/*
	// prepare player
	p = {{0, 1, 2, 3, 12}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 4);
	assert(p.freq[0] == 1);
	assert(p.freq[1] == 1);
	assert(p.freq[2] == 1);
	assert(p.freq[3] == 1);
	assert(p.freq[12] == 1);
	assert(p.same_val[1] == 5);
*/
	return;
}

void flush(){

	// prepare player
	PLAYER p = {{0, 1, 1, 1, 7}, true, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 5);
	assert(p.flush == true);

	return;
}

void full_house(){

	// prepare player
	PLAYER p = {{0, 0, 1, 1, 1}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 6);
	assert(p.freq[0] == 2);
	assert(p.freq[1] == 3);
	assert(p.same_val[2] == 1);
	assert(p.same_val[3] == 1);

	return;
}

void four_of_a_kind(){

	// prepare player
	PLAYER p = {{0, 1, 1, 1, 1}, false, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 7);
	assert(p.freq[1] == 4);
	assert(p.same_val[4] == 1);

	return;
}

void straight_flush(){

	// prepare player
	PLAYER p = {{0, 1, 2, 3, 4}, true, true, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};

	// call method
	rank_hand(&p);

	// assert results
	assert(p.type == 8);
	assert(p.freq[0] == 1);
	assert(p.freq[1] == 1);
	assert(p.freq[2] == 1);
	assert(p.freq[3] == 1);
	assert(p.freq[4] == 1);
	assert(p.same_val[1] == 5);
	assert(p.flush == true);

	return;
}

