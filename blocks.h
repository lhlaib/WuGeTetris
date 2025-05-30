// blocks.h

// contents:
//   classes:
//     Cube
//     Shape : Cube
//     Pool
//     gotoxy
//     Blocks
//     score_system

#ifndef BLOCKS_H
#define BLOCKS_H
//enum Type{I = 1, J = 2, L = 3, O = 4, S = 5, T = 6, Z = 7};
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include <fcntl.h>
#include <curses.h>
#include <ctime>

using namespace std;

class gotoxy
{
  int xx;
  int yy;
	friend ostream &operator<<(ostream &output, const gotoxy &a);
public:
	gotoxy(int x = 1, int y = 1):xx(x), yy(y){};
};

ostream &operator<<(ostream &output, const gotoxy &a) {
	cout << "\x1b[" << a.yy << ";" <<  2*a.xx << "H";
	return output;
	
	
	
}



class Shape;

class Pool
{
private:  
  int x,y;
  bool map[10][21];
  int color[10][21];
public:
  Pool();
  Pool(int a, int b, int c);
  
  void show();
  int isrow();
  bool isfull();
  bool pushin(Shape &in);
  
  friend class Shape;
};

class Move
{
public:
  virtual void up(int) = 0;
  virtual void down(int) = 0;
  virtual void left(int) = 0;
  virtual void right(int) = 0;
};
 // Pool(int l = 10, int w = 20):length(l),width(w)
 // int length,width;
 
/*
string gotoxy(int x, int y)
{
	char strx[4], stry[4];
	sprintf(strx, "%d", 2 * x);
	sprintf(stry, "%d", y);
	string tx(strx), ty(stry);
	return "\x1b[" + ty + ";" + tx + "H";
}*/


class Blocks : public Move
{
	int x, y;   // left one
	int color;  // 40 ~ 47
public:
	Blocks(int xpos = 1, int ypos = 1, int col = 40): x(xpos), y(ypos), color(col) {}
	
	int getx() {return x;}
	int gety() {return y;}
	int getcolor() {return color;}
	void setxy(int xpos, int ypos);
	void setcolor(int a) { color = a; }
	void show() { cout << gotoxy(x, y) << "\x1b[" << color << "m  \x1b[0m";	}  // Ken: show出一個整方形block

	void up(int a = 1) {y -= a;}
	void down(int a = 1) {y += a;}
	void left(int a = 1) {x -= a;}
	void right(int a = 1) {x += a;}
	
	void RotateR(int cx, int cy) {int lx = x,ly = y; x = cx - ly + cy; y = cy + lx - cx;}
  void RotateL(int cx, int cy) {}  // Ken: can't understand ^
	
	friend class Shape;
};

class Cube
{
protected:  
  int centerx, centery;
public:
  Cube(int a = 6, int b = 1) :centerx(a), centery(b){}
};

class Shape : public Cube, public Move
{
protected:
  unsigned int type;
  int NumberOfBlocks;
  Blocks *ptr;
public:
  Shape();
  Shape(unsigned int a, int b, int c, int d);
  Shape(const Shape &old);
  
  bool isbottom(Pool &in); //  bool isLobstacle(Pool &in);
  bool isbottom2(Pool &in); //  bool isRobstacle(Pool &in);
  bool isLboundary();  // Ken: haven't finished
  bool isRboundary();  // Ken: haven't finished
  
  void show();
  void setcolor(int a);
  unsigned int gettype() {return type;}
  
  void up(int a = 1){};
  void down(int a = 1);
	void left(int a = 1);
	void right(int a = 1);
  
  void RotateR(int a = 1);
	void movetoxy(int a, int b);
  void movetobottom(Pool &in);
  void movetobottom2(Pool &in);

  friend class Pool;
};


class Shape5 : public Shape  // flag
{
  friend class Pool;
public:
  Shape5();
  Shape5(unsigned int t, int NOB, int x_pos, int y_pos);
  Shape5(const Shape5 &);
  static int fiveBlocksTimes;
};

int Shape5::fiveBlocksTimes = 0;

Shape5::Shape5()
{
  srand(time(NULL));
  int fourOrFive = rand() % 2;
  if (fourOrFive == 0) {
    Shape();
  } else {
    if (fiveBlocksTimes == 2) {
      fiveBlocksTimes = 0;
      Shape();
       } else {
    fiveBlocksTimes++;
  type = (rand() % 7) + 1;
  NumberOfBlocks = 5;
  centerx = 17;
  centery = 3;
  ptr = new Blocks[5];
  switch(type)
  {
    case 1:
      ptr[0] = Blocks(centerx, centery, 46);
      ptr[1] = Blocks(centerx - 1, centery, 46);
      ptr[2] = Blocks(centerx + 1, centery, 46);
      ptr[3] = Blocks(centerx + 1, centery - 1, 46);
      ptr[4] = Blocks(centerx - 1, centery - 1, 46);
  
      break;
    case 2:
      ptr[0] = Blocks(centerx, centery, 43);
      ptr[1] = Blocks(centerx - 1, centery, 43);
      ptr[2] = Blocks(centerx + 1, centery, 43);
      ptr[3] = Blocks(centerx, centery + 1, 43);
      ptr[4] = Blocks(centerx, centery - 1, 43);
      
      break;    
    case 3:
      ptr[0] = Blocks(centerx, centery, 44);
      ptr[1] = Blocks(centerx, centery + 1, 44);
      ptr[2] = Blocks(centerx, centery + 2, 44);
      ptr[3] = Blocks(centerx, centery - 1, 44);
      ptr[4] = Blocks(centerx, centery - 2, 44);
      
      break;    
    case 4:
      ptr[0] = Blocks(centerx, centery, 105);
      ptr[1] = Blocks(centerx, centery + 1, 105);
      ptr[2] = Blocks(centerx, centery - 1, 105);
      ptr[3] = Blocks(centerx - 1, centery, 105);
      ptr[4] = Blocks(centerx + 1, centery - 1, 105);
      
      break;    
    case 5:
      ptr[0] = Blocks(centerx, centery, 42);
      ptr[1] = Blocks(centerx - 1, centery - 1, 42);
      ptr[2] = Blocks(centerx - 1, centery, 42);
      ptr[3] = Blocks(centerx, centery + 1, 42);
      ptr[4] = Blocks(centerx + 1, centery + 1, 42);
      
      break;    
    case 6:
      ptr[0] = Blocks(centerx, centery, 45);
      ptr[1] = Blocks(centerx - 1, centery - 1, 45);
      ptr[2] = Blocks(centerx, centery - 1, 45);
      ptr[3] = Blocks(centerx, centery + 1, 45);
      ptr[4] = Blocks(centerx + 1, centery + 1, 45);
      
      break;  
    case 7:
      ptr[0] = Blocks(centerx, centery, 41);
      ptr[1] = Blocks(centerx, centery - 1, 41);
      ptr[2] = Blocks(centerx - 1, centery, 41);
      ptr[3] = Blocks(centerx, centery + 1, 41);
      ptr[4] = Blocks(centerx, centery + 2, 41);
      
      break;
  }
  }
  }
}

Shape5::Shape5(unsigned int t, int NOB, int x_pos, int y_pos)
{
  if (NOB == 4)
    Shape(t, NOB, x_pos, y_pos);
  else {
  type = t;
  NumberOfBlocks = NOB;
  centerx = x_pos;
  centery = y_pos;
  ptr = new Blocks[5];
  switch(type)
  {
    case 1:
      ptr[0] = Blocks(centerx, centery, 46);
      ptr[1] = Blocks(centerx - 1, centery, 46);
      ptr[2] = Blocks(centerx + 1, centery, 46);
      ptr[3] = Blocks(centerx + 1, centery - 1, 46);
      ptr[4] = Blocks(centerx - 1, centery - 1, 46);
  
      break;
    case 2:
      ptr[0] = Blocks(centerx, centery, 43);
      ptr[1] = Blocks(centerx - 1, centery, 43);
      ptr[2] = Blocks(centerx + 1, centery, 43);
      ptr[3] = Blocks(centerx, centery + 1, 43);
      ptr[4] = Blocks(centerx, centery - 1, 43);
      
      break;    
    case 3:
      ptr[0] = Blocks(centerx, centery, 44);
      ptr[1] = Blocks(centerx, centery + 1, 44);
      ptr[2] = Blocks(centerx, centery + 2, 44);
      ptr[3] = Blocks(centerx, centery - 1, 44);
      ptr[4] = Blocks(centerx, centery - 2, 44);
      
      break;    
    case 4:
      ptr[0] = Blocks(centerx, centery, 105);
      ptr[1] = Blocks(centerx, centery + 1, 105);
      ptr[2] = Blocks(centerx, centery - 1, 105);
      ptr[3] = Blocks(centerx - 1, centery, 105);
      ptr[4] = Blocks(centerx + 1, centery - 1, 105);
      
      break;    
    case 5:
      ptr[0] = Blocks(centerx, centery, 42);
      ptr[1] = Blocks(centerx - 1, centery - 1, 42);
      ptr[2] = Blocks(centerx - 1, centery, 42);
      ptr[3] = Blocks(centerx, centery + 1, 42);
      ptr[4] = Blocks(centerx + 1, centery + 1, 42);
      
      break;    
    case 6:
      ptr[0] = Blocks(centerx, centery, 45);
      ptr[1] = Blocks(centerx - 1, centery - 1, 45);
      ptr[2] = Blocks(centerx, centery - 1, 45);
      ptr[3] = Blocks(centerx, centery + 1, 45);
      ptr[4] = Blocks(centerx + 1, centery + 1, 45);
      
      break;  
    case 7:
      ptr[0] = Blocks(centerx, centery, 41);
      ptr[1] = Blocks(centerx, centery - 1, 41);
      ptr[2] = Blocks(centerx - 1, centery, 41);
      ptr[3] = Blocks(centerx, centery + 1, 41);
      ptr[4] = Blocks(centerx, centery + 2, 41);
      
      break;   
  }
  }
}

Shape5::Shape5(const Shape5 &old)
  {
    centerx = old.centerx;
    centery = old.centery;
    type = old.type;
    NumberOfBlocks = old.NumberOfBlocks;
    ptr = new Blocks[old.NumberOfBlocks];
    for (int i = 0; i < NumberOfBlocks; i++)
      ptr[i] = old.ptr[i];
 }



class boundary  // Ken: understand
{
  int x, y;
  int length, width;
public:
  boundary(int xx = 1, int yy = 1, int ww = 0, int ll = 0):x(xx), y(yy), length(ll), width(ww) {}
  void showboundary()
  {
	  cout << "\x1b[47m";
	  for (int i = 0; i < width; i++)
	    cout << gotoxy(x + i, y) << "  ";
    for (int i = 0; i < length; i++)
		  cout << gotoxy(x, i + y ) << "  " << gotoxy(x + width - 1, i + y ) << "  "; 
	  for (int i = 0; i < width; i++)
	    cout << gotoxy(x + i, y + length - 1) << "  ";
	  cout << "\x1b[0m";
  }
};

//class Shape 
  void Shape::movetobottom(Pool &in)
  {
    while(!isbottom(in)) {
      down();
    }
  }
  void Shape::movetobottom2(Pool &in)
  {
    while(!isbottom2(in)){
      down();
    }
  }
  void Shape::setcolor(int a)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      ptr[i].Blocks::setcolor(a);
  }
  bool Shape::isLboundary()
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(ptr[i].x - 1 <= 1) return true;
    return false;
  }
  bool Shape::isRboundary()
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(ptr[i].x + 1 >= 12) return true;
    return false;
  }
 /* bool Shape::isLobstacle(Pool &in)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(in.map[ptr[i].x - 1][ptr[i].y + 1] == true) return true;
    return false;
  }
  bool Shape::isRobstacle(Pool &in)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(in.map[ptr[i].x + 1][ptr[i].y + 1] == true) return true;
    return false;
  }*/
  bool Shape::isbottom(Pool &in)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(in.map[ptr[i].x - 2][ptr[i].y  + 1] == true || ptr[i].y + 1 >= 21) return true;
    return false;
  }
  
  bool Shape::isbottom2(Pool &in)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      if(in.map[ptr[i].x - 2][ptr[i].y] == true || ptr[i].y + 1 >= 22) return true;
    return false;
  }
  
  void Shape::show()
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      ptr[i].Blocks::show();
    cout << gotoxy(30,30) ;//<< centerx <<','<<centery;
  }
  
  void Shape::down(int a)
  {
    for (int i = 0; i < NumberOfBlocks; i++)
      ptr[i].Blocks::down(a);
    centery += 1;
  }
  
	void Shape::left(int a)
	{
    if(!isLboundary())
    {
      for (int i = 0; i < NumberOfBlocks; i++)
        ptr[i].Blocks::left(a);
      centerx -= 1;
    }  
	}
	
	void Shape::right(int a){
    if(!isRboundary())
    {
	    for (int i = 0; i < NumberOfBlocks; i++)
        ptr[i].Blocks::right(a);
      centerx += 1;
    }
	}
	
	void Shape::movetoxy(int a, int b)
  {
    int xcomponent, ycomponent;
    xcomponent = a - centerx; 
    ycomponent = b - centery;
    for (int i = 0; i < NumberOfBlocks; i++)
    {
      ptr[i].Blocks::down(ycomponent);
      ptr[i].Blocks::right(xcomponent);
    }
    centerx = a; centery = b;
  }
  
  void Shape::RotateR(int a)
  {
     //condition add
    //int k = 0;
    for (int i = 1; i < NumberOfBlocks; i++)
      ptr[i].Blocks::RotateR(centerx, centery);
/*    for (int i = 0; i < NumberOfBlocks; i++)
      if(ptr[i].x  <= 1) k += 1;
    for (int i = 0; i < NumberOfBlocks; i++)
      if(ptr[i].x  >= 12) k -= 1;
*/  while(isLboundary()) Shape::right(a);
    while(isRboundary()) Shape::left(a);
  }
  
  // Ken: Shape constructors
  Shape::Shape(unsigned int a, int b, int c, int d) : Cube(c, d), type(a), NumberOfBlocks(b)  // Ken: understand
  {
    switch(type)
    {
      case 1:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 46);
        ptr[1] = Blocks(centerx - 1, centery, 46);
        ptr[2] = Blocks(centerx + 2, centery, 46);
        ptr[3] = Blocks(centerx + 1, centery, 46);

        break;
      case 2:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 43);
        ptr[1] = Blocks(centerx + 1, centery - 1, 43);
        ptr[2] = Blocks(centerx - 1, centery, 43);
        ptr[3] = Blocks(centerx + 1, centery, 43);
        
        break;
      case 3:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 44);
        ptr[1] = Blocks(centerx, centery - 1, 44);
        ptr[2] = Blocks(centerx + 1, centery, 44);
        ptr[3] = Blocks(centerx + 2, centery, 44);
        
        break;
      case 4:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 105);
        ptr[1] = Blocks(centerx, centery - 1, 105);
        ptr[2] = Blocks(centerx + 1, centery, 105);
        ptr[3] = Blocks(centerx + 1, centery - 1, 105);
        
        break;
      case 5:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 42);
        ptr[1] = Blocks(centerx + 1, centery, 42);
        ptr[2] = Blocks(centerx - 1, centery + 1, 42);
        ptr[3] = Blocks(centerx, centery + 1, 42);
        
        break;
      case 6:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 45);
        ptr[1] = Blocks(centerx, centery - 1, 45);
        ptr[2] = Blocks(centerx + 1, centery, 45);
        ptr[3] = Blocks(centerx - 1, centery, 45);
        
        break;
      case 7:
        NumberOfBlocks = 4;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 41);
        ptr[1] = Blocks(centerx + 1, centery, 41);
        ptr[2] = Blocks(centerx + 1, centery + 1, 41);
        ptr[3] = Blocks(centerx + 2, centery + 1, 41);
        
        break;
    }
  }
  
  Shape::Shape() : Cube()  // Ken: understand // flag
  {
    type = (rand()%7)+1;
    switch(type)
    {
      case 1:
        NumberOfBlocks = 4;
        centerx = 17;  
        centery = 3;        
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 46);
        ptr[1] = Blocks(centerx - 1, centery, 46);
        ptr[2] = Blocks(centerx + 2, centery, 46);
        ptr[3] = Blocks(centerx + 1, centery, 46);

        break;
      case 2:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 43);
        ptr[1] = Blocks(centerx + 1, centery - 1, 43);
        ptr[2] = Blocks(centerx - 1, centery, 43);
        ptr[3] = Blocks(centerx + 1, centery, 43);
        
        break;
      case 3:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 44);
        ptr[1] = Blocks(centerx, centery - 1, 44);
        ptr[2] = Blocks(centerx + 1, centery, 44);
        ptr[3] = Blocks(centerx + 2, centery, 44);
        
        break;
      case 4:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 105);
        ptr[1] = Blocks(centerx, centery - 1, 105);
        ptr[2] = Blocks(centerx + 1, centery, 105);
        ptr[3] = Blocks(centerx + 1, centery - 1, 105);
        
        break;
      case 5:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 42);
        ptr[1] = Blocks(centerx + 1, centery, 42);
        ptr[2] = Blocks(centerx - 1, centery + 1, 42);
        ptr[3] = Blocks(centerx, centery + 1, 42);
        
        break;
      case 6:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 45);
        ptr[1] = Blocks(centerx, centery - 1, 45);
        ptr[2] = Blocks(centerx + 1, centery, 45);
        ptr[3] = Blocks(centerx - 1, centery, 45);
        
        break;
      case 7:
        NumberOfBlocks = 4;
        centerx = 17;
        centery = 3;
        ptr = new Blocks[4];
        ptr[0] = Blocks(centerx, centery, 41);
        ptr[1] = Blocks(centerx + 1, centery, 41);
        ptr[2] = Blocks(centerx + 1, centery + 1, 41);
        ptr[3] = Blocks(centerx + 2, centery + 1, 41);
        
        break;
    }
  }
  
  Shape::Shape(const Shape &old)  // Ken: understand
  {
    centerx = old.centerx;
    centery = old.centery;
    type = old.type;
    NumberOfBlocks = old.NumberOfBlocks;
    ptr = new Blocks[4];
    for (int i = 0; i < NumberOfBlocks; i++)
      ptr[i] = old.ptr[i];
  }
//end class

//class Pool
  Pool::Pool()
  {
    for(int i = 0;i < 10; i++)
      for(int j = 0;j < 21; j++)
      {
        map[i][j] = false;
        color[i][j] = 47;
      }
    x = 2; y = 1;
  }
  
  Pool::Pool(int a, int b = 2, int c = 1):x(b), y(c){
    for(int i = 0;i < 10; i++)
      for(int j = 0;j < 21; j++)
      {
        map[i][j] = Map[a-1][j][i];
        color[i][j] = Color[a-1][j][i];
      }
  }
  
  int Pool::isrow(){
    int row = 0, count = 0, win = 0, temp[10];
    for(int j = 1;j < 21; j++)
    {
      for(int i = 0;i < 10; i++)
        if(map[i][j]) count++;
      if(count == 10)
      {
        for(int i = 0;i < 10; i++)
          map[i][j] = false;
        for(int k = j;k > 0; k--)
          for(int i = 0;i < 10; i++)
          {
            map[i][k] = map[i][k-1];
            color[i][k] = color[i][k-1];
          }
        win++;
      }
      count = 0;
    }
    return win;
  }
  bool Pool::isfull()
  {
    for(int i = 0;i < 10; i++)
      if(map[i][0]) return true;
    return false;
  }
  void Pool::show(){
    for(int i = 0;i < 10; i++)
      for(int j = 1;j < 21; j++)
        if(map[i][j])
          cout << gotoxy(x + i, y + j) << "\x1b[" << color[i][j] << "m  \x1b[0m";;  // Ken: ;;?
  }
  
  bool Pool::pushin(Shape &in){
   for (int i = 0; i < in.NumberOfBlocks; i++)
    {
      map[in.ptr[i].getx() - 2][in.ptr[i].gety()] = true;
      color[in.ptr[i].getx() - 2][in.ptr[i].gety()] = in.ptr[i].getcolor();
    }
	// control reaches end of non-void function
	// assume true
	// please fix it if you see it
		return true;
  }
//end class





void clearscreen()
{
	cout << "\x1B[2J\x1B[H";
}

void hidecursor()
{
	cout << "\x1b[?25l";
}

void sleep001(int i)
{
	usleep(10000 * i);
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

#endif

