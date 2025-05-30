
#include <iostream>
#include "map.h"
#include "blocks.h"
#include "rank.h"
#include "game.h"
using namespace std;


int main()
{
  GameStatus status = Menu;
  Game_Opreatoring_System OS;
  
  while(1){
    if ( status == Menu )
      status = OS.menu(); 
      
    if ( status == Loading )
      status = OS.loading();
      
    if ( status == Playing1 )
      status = OS.playing_mode1();
      
    if ( status == Playing2 )
      status = OS.playing_mode2();
      
    if ( status == Playing3 )
      status = OS.playing_mode3();
    
    if ( status == Playing4 )
      status = OS.playing_mode4();

    if ( status == GameOver)
      status = OS.gameover();
  }
  
  return 0;
}
