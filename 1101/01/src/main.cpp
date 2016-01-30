#include <iostream>

using namespace std;

// returns the 3n+1 cycle length for a given number
long int tnp1(long int);

int main(){

  long int a, b; // input boundaries
  long int cycle; // current cycle
  long int max_cycle; // max cycle
  long int temp; // auxiliary variable

  // while there's a sequence
  while(cin >> a >> b){

    max_cycle = 0; // init the maximum for this sequence
    if(a > b) { temp = a; a = b; b = temp; } // check reverse order gotcha

    // test the cycle for each number between a and b
    for(long int i = a; i <= b; ++i){

      cycle = tnp1(i);

      // keep the max cycle
      if(cycle > max_cycle) max_cycle = cycle;
    }

    // output max cycle for this sequence
    cout << a << " " << b << " " << max_cycle << endl;

  }

  return 0;

}

long int tnp1(long int n){

  long int count = 1; // init counter to 1 accounting for the first element

  // execute the 3n + 1 algorithm until n = 1
  while(n != 1){

    if(n%2)
      n = 3*n + 1;
    else
      n /= 2;

    ++count; // keep track of how many steps until stop

  }

  return count;
}
