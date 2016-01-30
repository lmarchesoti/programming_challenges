#include <iostream>
#define MAX_SIZE 251

using namespace std;

// global variables
int M; // matrix width
int N; // matrix height
char image[MAX_SIZE][MAX_SIZE]; // image matrix

// clear image to contain all 0s
void clear_matrix();

// applies smart fill to pixel (x, y) depending on its color
void smart_fill(int, int, char, char);

// creates a new image and clears it
void init_image();

// colors a single pixel
void paint_pixel();

// draw a vertical line
void draw_vertical();

// draw a horizontal line
void draw_horizontal();

// draw a fill rectangle
void fill_rectangle();

// saves file
void save();

// wrapper that reads input and calls smart fill function
void smart_fill_wrapper();

int main(){

  char command; // command
  char color; // color placeholder

  // until the command is 'X', read next command
  for(cin >> command; command != 'X'; cin >> command){
    
    // execute specified command on the matrix
    switch(command){

      case 'I': init_image(); break;

      case 'C': clear_matrix(); break;

      case 'L': paint_pixel(); break;

      case 'V': draw_vertical(); break;

      case 'H': draw_horizontal(); break;

      case 'K': fill_rectangle(); break;

      case 'F': smart_fill_wrapper(); break;

      case 'S': save();	break;

      default: break;

    }

  }

  return 1;
}

void clear_matrix(){

  for(int i = 1; i <= N; ++i) for(int j = 1; j <= M; ++j) image[i][j] = 'O';

  return;
}

void smart_fill(int x, int y, char color, char new_color){

  // return if trying for coordinates out of bound
  if((x < 1) || (x > N) || (y < 1) || (y > M)) return;

  // return if trying for the same color
  // or if the pixel isn't to be changed
  if((color == new_color) || (image[x][y] != color)) return;

  // change itself and perpetuate to adjacent cells
  image[x][y] = new_color;

  smart_fill(x-1, y, color, new_color);
  smart_fill(x+1, y, color, new_color);
  smart_fill(x, y-1, color, new_color);
  smart_fill(x, y+1, color, new_color);

  return;
}

void init_image(){

  cin >> M >> N; // take in size
  clear_matrix(); // fill matrix with starting values

  return;
}

void paint_pixel(){

  int x, y; // pixel coordinates
  char color;

  cin >> y >> x >> color; // read command inputs
  image[x][y] = color; // color pixel

  return;
}

void draw_vertical(){

  int x0, x1; // lowest and highest lines
  int y; // column
  int temp; // for swapping
  char color;

  cin >> y >> x0 >> x1 >> color; // read command inputs
  if(x0 > x1) { temp = x1; x1 = x0; x0 = temp; } // check if x0 > x1
  for(int i = x0; i <= x1; ++i) image[i][y] = color; // draw vertical line

  return;
}

void draw_horizontal(){

  int y0, y1; // lowest and highest columns
  int x; // line
  int temp; // for swapping
  char color;

  cin >> y0 >> y1 >> x >> color; // read command inputs
  if(y0 > y1) { temp = y1; y1 = y0; y0 = temp; } // check if x0 > x1
  for(int i = y0; i <= y1; ++i) image[x][i] = color; // draw vertical line

  return;
}

void fill_rectangle(){

  int x0, y0; // first point coordinates
  int x1, y1; // second point coordinates
  char color;

  cin >> y0 >> x0 >> y1 >> x1 >> color; // read command inputs
  for(int i = x0; i <= x1; ++i)
    for(int j = y0; j <= y1; ++j)
      image[i][j] = color; // draw vertical line

  return;
}

void save(){

  string name;

  cin >> name; // read file name

  cout << name << endl; // print name
  // print matrix
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= M; ++j) cout << image[i][j];
    cout << endl;
  }

  return;
}

void smart_fill_wrapper(){

  int x, y; // initial coordinates
  char color;

  cin >> y >> x >> color; // read command inputs
  smart_fill(x, y, image[x][y], color);

  return;
}
