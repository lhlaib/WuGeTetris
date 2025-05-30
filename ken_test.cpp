#include <iostream>
#include "map.h"
#include "game.h"
#include "blocks.h"
using namespace std;

enum GameStatus{
  Menu,      // 開頭選單 
  Loading,   // 載入畫面
  Playing,   // 遊戲進行中
  Pause,     // 遊戲暫停
  GameOver   // 遊戲結束
};

int main()
{
  GameStatus status = Menu;
  Game_Opreatoring_System OS;

	Shape5 hold;
	cout << gotoxy(30,20) << "hi";
	hold.show();
  return 0;
}
