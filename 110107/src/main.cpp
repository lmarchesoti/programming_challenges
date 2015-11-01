#include <iostream>
#define BOARD_SIZE 8

using namespace std;

typedef char BOARD[BOARD_SIZE][BOARD_SIZE];

// global variables
BOARD board;

// reads in the board and returns 1 if it is to be processed
int read_board();

// check if there's a check for either side of the game
int check_if_check();

/* these functions try all valid moves for the given piece while    *
 * searching for the desired piece. It returns the target if found, *
 * or * otherwise */

char move_rook(int, int, char);

char move_bishop(int, int, char);

char move_queen(int, int, char);

char move_knight(int, int, char);

char move_pawn(int, int, char);

char move_king(int, int, char);

/* end */

// perpetuates moving along a certain axis until check or block
int keep_moving(int, int, int, int, char);

// returns 1 if position is valid(within boarders), 0 otherwise
int is_position_valid(int, int);

int main(){

  // read board
  for(int game = 1; read_board(); ++game){

    cout << "Game #" << game << ": ";
    // check if check and output result accordingly
    switch(check_if_check()){

      // no check
      case 0: cout << "no"; break;

      // black check
      case 1: cout << "black"; break;

      // white check
      case 2: cout << "white"; break;

      default: break;

    }

    cout << " king is in check." << endl;

  }

  return 0;
}

int check_if_check(){

  char check = '*'; // holds information about who was checked if any

  // go through the board
  for(int i = 0; i < BOARD_SIZE; ++i)
    for(int j = 0; j < BOARD_SIZE; ++j){

    // generate a valid move for every piece and keep the check code
    switch(board[i][j]){

      // rook
      case 'r': check = move_rook(i, j, 'K'); break;
      case 'R': check = move_rook(i, j, 'k'); break;

      // bishop
      case 'b': check = move_bishop(i, j, 'K'); break;
      case 'B': check = move_bishop(i, j, 'k'); break;

      // queen
      case 'q': check = move_queen(i, j, 'K'); break;
      case 'Q': check = move_queen(i, j, 'k'); break;

      // knight
      case 'n': check = move_knight(i, j, 'K'); break;
      case 'N': check = move_knight(i, j, 'k'); break;

      // pawn
      case 'p': check = move_pawn(i + 1, j, 'K'); break;
      case 'P': check = move_pawn(i - 1, j, 'k'); break;

      // king (not really needed)
      case 'k': check = move_king(i, j, 'K'); break;
      case 'K': check = move_king(i, j, 'k'); break;

      // open spaces
      default: break;

    }

    // return the check if any
    if(check == 'k') return 1;
    if(check == 'K') return 2;
  }

  return 0; // return no check if none
}

char move_rook(int x, int y, char target){

  // move left
  if(keep_moving(x, y, -1, 0, target)) return target;

  // move right
  if(keep_moving(x, y, 1, 0, target)) return target;

  // move top
  if(keep_moving(x, y, 0, -1, target)) return target;

  // move bottom
  if(keep_moving(x, y, 0, +1, target)) return target;

  return '*';
}

char move_bishop(int x, int y, char target){

  // move top/left
  if(keep_moving(x, y, -1, -1, target)) return target;

  // move top/right
  if(keep_moving(x, y, -1, +1, target)) return target;

  // move bottom/left
  if(keep_moving(x, y, +1, -1, target)) return target;

  // move bottom/right
  if(keep_moving(x, y, +1, +1, target)) return target;

  return '*';
}

char move_queen(int x, int y, char target){

  if(move_rook(x, y, target) == target) return target;
  if(move_bishop(x, y, target) == target) return target;

  return '*';
}

char move_knight(int x, int y, char target){

  int tx, ty; // current tentative position

  // check each possibility from top to bottom, left to right
  tx = x - 2; ty = y - 1; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x - 2; ty = y + 1; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x - 1; ty = y - 2; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x - 1; ty = y + 2; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x + 1; ty = y - 2; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x + 1; ty = y + 2; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x + 2; ty = y - 1; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  tx = x + 2; ty = y + 1; 
  if(is_position_valid(tx, ty) && (board[tx][ty] == target)) return target;

  return '*';
}

char move_pawn(int x, int y, char target){

  // left
  if(is_position_valid(x, y - 1) && (board[x][y - 1] == target)) return target;

  // right
  if(is_position_valid(x, y + 1) && (board[x][y + 1] == target)) return target;

  return '*';
}

int keep_moving(int x, int y, int modx, int mody, char target){

  x += modx; y += mody; // update position

  if(!is_position_valid(x, y)) return 0;

  if(board[x][y] == target) return 1; // found target
  if(board[x][y] != '.') return 0; // found block
  return keep_moving(x, y, modx, mody, target); // found nothing, keep going

}

int is_position_valid(int x, int y){

  if((x < 0) || (y < 0) || (x > (BOARD_SIZE - 1)) || (y > (BOARD_SIZE - 1)))
    return 0;

  return 1;
}

int read_board(){

  int proc = 0;

  for(int i = 0; i < BOARD_SIZE; ++i)
    for(int j = 0; j < BOARD_SIZE; ++j){
      cin >> board[i][j];
      if(board[i][j] != '.') proc = 1;
    }

  return proc;
}

char move_king(int x, int y, char target){

  for(int i = x - 1; i <= x + 1; ++i)
    for(int j = y - 1; j <= y + 1; ++j)
      if(is_position_valid(i, j) && (board[i][j] == target)) return target;

  return '*';
}
