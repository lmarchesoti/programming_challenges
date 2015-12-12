#include <iostream>

using namespace std;

/* data structures */

/* global variables */
int lm, ln; // left
int cm, cn; // current
int rm, rn; // right
int m, n;		// test case

/* function prototypes */

/* debug */

int main(){

	double ttest, tcur;

	while(cin >> m >> n, (m != 1) || (n != 1)){

		// init
		lm = 0; ln = 1;
		cm = cn = 1;
		rm = 1; rn = 0;

		while((m != cm) || (n != cn)){

			ttest = (double) m/n;
			tcur = (double) cm/cn;

			if (ttest > tcur) lm = cm, ln = cn, cm += rm, cn += rn, cout << "R";
			if (ttest < tcur) rm = cm, rn = cn, cm += lm, cn += ln, cout << "L";

		}

		cout << endl;

	}

  return 0;
}

/* functions */
