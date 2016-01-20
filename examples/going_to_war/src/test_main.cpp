#include "functions.cpp"
#include <cassert>

/* test prototypes */
void test();

/* register tests in main */
int main(){

  // tests here
	test();

  return 0;
}

/* test specifications */
void test(){

	for(int i = 0; i < (NSUITS*NVALUES); ++i)
		assert(i == rank_card(suit(i), value(i)));

	assert(true);
	return;
}
