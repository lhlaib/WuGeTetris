#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <curses.h>
#include <ctime>

class gotoxy
{
  int xx;
  int yy;
	friend ostream &operator<<(ostream &output, const gotoxy &a);
public:
	gotoxy(int x = 1, int y = 1):xx(x), yy(y){};
};

ostream &operator<<(ostream &output, const gotoxy &a){
	cout << "\x1b[" << a.yy << ";" <<  2*a.xx << "H";
	return output;
}


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