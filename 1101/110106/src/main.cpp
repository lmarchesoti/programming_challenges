#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#define MEMORY_SIZE 1000
#define CELL_SIZE 4
#define REGISTER_SIZE 10

using namespace std;

typedef char MEM_CELL[CELL_SIZE]; // memory cell

// executes the next instruction and updates the program counter
int execute_next(MEM_CELL ram[MEMORY_SIZE], int reg[REGISTER_SIZE], int *pc);

int main(){

  int test_count; // number of test cases
  int reg[REGISTER_SIZE]; // registers
  int pc; // program counter
  MEM_CELL ram[MEMORY_SIZE]; // memory
  unsigned long int counter; // execution record
  int first = 1; // dull flag

  cin >> test_count; // read number of test cases
  cin.get(); // remove newline

  // while in the range of test cases
  for(; test_count > 0; --test_count){

    // print newline after each input
    if(first)
      first = 0;
    else
      cout << endl;

    // init execution varibles
    pc = 0;
    counter = 1;

    // reset memory
    for(int i = 0; i < MEMORY_SIZE; ++i) strcpy(ram[i], "000\0");

    // reset registers
    for(int i = 0; i < REGISTER_SIZE; ++i) reg[i] = 0;

    // read memory from input
    cin.get(); // discard newline between each input sequence
    for(int i = 0; (i < 1000) && (cin.peek() != '\n'); ++i) cin.getline(ram[i], CELL_SIZE);

    // while instruction execution doesn't halt,
    // increment the execution counter
    while(execute_next(ram, reg, &pc)) ++counter;

    // print execution record separated by a blank line
    cout << counter << endl;
  }

  return 0;
}

int execute_next(MEM_CELL ram[MEMORY_SIZE], int reg[REGISTER_SIZE], int *pc){

  int iop; // instruction operator
  int ifv; // first operand value
  int isv; // second operand value

  // decode instruction from char to int
  iop = ram[(*pc)][0] - 48;
  ifv = ram[(*pc)][1] - 48;
  isv = ram[(*pc)][2] - 48;

  // execute it
  switch(iop){

    // halt
    case 1: if((ifv == 0) && (isv == 0)) return 0; break;

    // assign constant to register
    case 2: reg[ifv] = isv; break;

    // add constant to register
    case 3: reg[ifv] = (reg[ifv] + isv) % 1000; break;

    // multiply constant to register
    case 4: reg[ifv] = (reg[ifv] * isv) % 1000; break;

    // assign register value to register
    case 5: reg[ifv] = reg[isv]; break;

    // add register value to register
    case 6: reg [ifv] = (reg[ifv] + reg[isv]) % 1000; break;

    // multiply register value to register
    case 7: reg[ifv] = (reg[ifv] * reg[isv]) % 1000; break;

    // indirect load
    case 8: reg[ifv] = atoi(ram[reg[isv]]); break;

    // set indirect store
    case 9: snprintf(ram[reg[isv]], CELL_SIZE, "%d", reg[ifv]); break;

    // jump
    case 0: if(reg[isv]){ (*pc) = reg[ifv]; return 1; } break;

    default: break;

  }

  (*pc) = (++(*pc)) % 1000; // increment pc

  return 1;
}
