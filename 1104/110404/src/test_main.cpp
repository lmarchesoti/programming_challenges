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

	assert(rank_t(10, 30) == 630);
	assert(hours(630) == 10);
	assert(minutes(630) == 30);
	return;
}
