#include <iostream>
#define MAX 100			// maximum n/k

/* recursive version can't handle large test case */
/* use matrix version instead											*/

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// calculates binomial coefficient recursively
int rec_bin(int, int);

// calculates binomial coefficient by using a matrix
long long int mat_bin(int, int);

/* debug */

int main(){

	int n, k; // n choose k

	while((cin.peek() != '\n') && !cin.eof()){

		cin >> n >> k; cin.get();

		//cout << rec_bin(n, k) << endl;
		cout << mat_bin(n, k) << endl;

	}

  return 0;
}

/* functions */
int rec_bin(int n, int k){

	if(k == 0) return 1;
	if(n == k) return 1;

	return rec_bin(n-1, k-1) + rec_bin(n-1, k);
}

long long int mat_bin(int n, int k){

	long long int m[MAX][MAX];

	// set base cases
	for(int i = 0; i <= n; ++i) m[i][0] = 1;
	for(int i = 0; i <= n; ++i) m[i][i] = 1;

	// set general case up to n choose k
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= k; ++j)
			m[i][j] = m[i-1][j-1] + m[i-1][j];

	return m[n][k];
}
