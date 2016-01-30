#include <iostream>

using namespace std;

// the extra slots account for the out of bounds cases
typedef int FIELD[102][102];

// reads an input matrix to the field variable
void read_field(FIELD *field, int m, int n);

// get correct numbers for surrounding *
void fill_count(FIELD *field, int m, int n);

// print the field matrix
void print_field(FIELD *field, int m, int n);

// tries to increase the count in the given position
void increase_count(FIELD *field, int m, int n, int i, int j);

int main(){

  FIELD field; // field
  int m; // first field dimension
  int n; // second field dimension
  int x = 1; // field number

  // read field dimensions for each test case 
  for(cin >> m >> n; m != 0 && n != 0; cin >> m >> n){

    // only add newlines if not on the last case 
    if(x != 1)
      cout << endl;

    // read field in
    read_field(&field, m, n);

    // alter the field to hold the correct numbers
    fill_count(&field, m, n);

    // print solution to this case
    cout << "Field #" << x << ":" << endl;
    print_field(&field, m, n);

    ++x; // increase test case count

  }

  return 0;

}

void read_field(FIELD *field, int m, int n){

  char temp; // input character
  for(int i = 1; i <= m; ++i){
    for(int j = 1; j <= n; ++j){

      // convert from character to int
      cin >> temp;
      if(temp == '.')
	(*field)[i][j] = 0;
      if(temp == '*')
	(*field)[i][j] = -1;

    }
  }

  return;

}

void fill_count(FIELD *field, int m, int n){

  // for each position call a method to increase
  // the count of surrounding tiles by one
  for(int i = 1; i <= m; ++i){
    for(int j = 1; j <= n; ++j){

      if((*field)[i][j] == -1){

	increase_count(field, m, n, i - 1, j - 1 );
	increase_count(field, m, n, i - 1, j );
	increase_count(field, m, n, i - 1, j + 1 );
	increase_count(field, m, n, i, j - 1 );
	increase_count(field, m, n, i, j + 1 );
	increase_count(field, m, n, i + 1, j - 1);
	increase_count(field, m, n, i + 1, j);
	increase_count(field, m, n, i + 1, j + 1);
      }

    }
  }

  return;

}

void print_field(FIELD *field, int m, int n){

  for(int i = 1; i <= m; ++i){
    for(int j = 1; j <= n; ++j){

      if((*field)[i][j] == -1)
	cout << "*";
      else cout << (*field)[i][j];

    }
    cout << endl;
  }

  return;

}

void increase_count(FIELD *field, int m, int n, int i, int j){

  // increase the count of the desired position if not a bomb
  if((*field)[i][j] != -1) (*field)[i][j] += 1;

  return;
}
