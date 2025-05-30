// game.h

// contents:
//   classes:
//     Timex  計時
//     score_system 分數系統
//     Game_Operating_System  遊戲運行程式

// if modify: // ken_modified: modify what
// Ken: understand // 我看懂的地方的comment
// Ken: can't understand

#ifndef GAME_H
#define GAME_H
#include "blocks.h"

class Timex
{
  time_t start;// , now; //起始時間與目前時間 // Ken: 不需要 now
public: 
  Timex(){start = time(NULL);} //建構子 初始化起始時間
  int getduration();            //function:計算經過時間
};

class score_system
{
private:  
  int grade;
  int combo;
  int highest_combo;
  int Remaintime;
  int color;
  time_t start, now;
public:
  score_system(int a = 0, int b = 0, int c = 90, int d = 0);
  
  int getgrade() {return grade;}
  int getcombo() {return combo;}
  int gethcombo() {return highest_combo;}
  int getremaintime();
  
  void show();
  void remaintime();
  void checkpoint(int a,bool &ho);
};

class Game_Opreatoring_System 
{
private:  
  int map_type;
  int mode;
  int hardness;
  int person;
  score_system total; 
  string name;
public:
  Game_Opreatoring_System(int map = 1,int mod = 1,int hard = 3,int per = 1,string na = "Henry")
  :map_type(map), mode(mod), hardness(hard), person(per), name(na){} // Ken: add name(na) 
  
  void show_Tetris_battle();
  GameStatus menu();
  GameStatus loading();
  GameStatus playing_mode1();
  GameStatus playing_mode2();
  GameStatus playing_mode3();
  GameStatus playing_mode4();
  GameStatus gameover();
  void pause();
};

//class Timex
  int Timex::getduration()            //function:計算經過時間
  {
    // now = time(NULL);
    return time(NULL) - start; // Ken: 去掉 new
  }
//end class

//class score_system
  score_system::score_system(int a, int b, int c, int d) :grade(a), combo(b), Remaintime(c),highest_combo(d)
  {
    start = time(NULL);
  }
  void score_system::show()
  {
      getremaintime();
      if(Remaintime < 10) color = 31;
      else if (Remaintime > 10 && Remaintime < 30) color = 33;
      else if(Remaintime > 30) color = 34;
      cout << gotoxy(17, 15) << "\x1b[" << color << "m" << "RemainTime" << "\x1b[0m";
		  cout << gotoxy(18, 16) << "\x1b[" << color << "m" << getremaintime() << "\x1b[0m";
		  if(combo < 4) color = 35;
      else if (combo > 4 && combo < 8) color = 33;
      else if(combo > 8) color = 31;
		  cout << gotoxy(17, 17) << "\x1b[" << color << "m" << "COMBO" << "\x1b[0m";
		  cout << gotoxy(18, 18) << "\x1b[" << color << "m" << combo << "\x1b[0m";
		  if(grade < 10) color = 36;
      else if (grade> 10 && grade < 25) color = 33;
      else if(grade > 25) color = 31;		  
		  cout << gotoxy(17, 19) << "\x1b[" << color << "m" << "SCORE" << "\x1b[0m";
		  cout << gotoxy(18, 20) << "\x1b[" << color << "m" << grade << "\x1b[0m";
  }
  
  int score_system::getremaintime()
  {
    remaintime();
    return Remaintime;
  }
  
  void score_system::remaintime()  // Ken: 計算出剩下的時間
  {
    now = time(NULL);
    Remaintime = start - now + 120;
  }
  
  void score_system::checkpoint(int a,bool &ho){
    if(ho) ho = false;
    else if(a == 0 && !ho) {
      if(highest_combo < combo) highest_combo = combo;
      combo = 0;
    }
    else
    {
      for (int i = a; i > 0; i -= 1){
        combo++;
        grade += combo;
      }
    }
  }
//end class

// Game_Opreatoring_System
  void Game_Opreatoring_System::show_Tetris_battle()  // Ken: understand
  {
    for(int i = 0;i < 13; i++)
      for(int j = 0;j < 36; j++)
        if(!Tetris_battle[i][j])
          cout << gotoxy(3 + j, 2 + i) << "\x1b[" << 45 << "m  \x1b[0m";
        else if(Tetris_battle[i][j] && i < 6)
          cout << gotoxy(3 + j, 2 + i) << "\x1b[" << 43 << "m  \x1b[0m";
        else
          cout << gotoxy(3 + j, 2 + i) << "\x1b[" << 100 << "m  \x1b[0m";
  }
  
  GameStatus Game_Opreatoring_System::menu(){  // Ken: understand
    clearscreen();
    show_Tetris_battle();
    cout << gotoxy(3, 16) << "\x1b[" << 34 << "m" << "Welcome to Tetris Battle!" << "\x1b[0m";
    cout << gotoxy(3, 17) << "\x1b[" << 34 << "m" << "This game was developed by Henry Lai & Ken Lin!" << "\x1b[0m";
    cout << gotoxy(3, 18) << "\x1b[" << 34 << "m" << "Enjoy and have fun!" << "\x1b[0m";
    cout << gotoxy(3, 19) << "\x1b[" << 34 << "m" << "Date: 2018/05/23" << "\x1b[0m";
   // cout << gotoxy(3, 20) << "\x1b[" << 34 << "m" << "Email: h123572119@gmail.com" << "\x1b[0m";
    cout << gotoxy(3, 21) << "\x1b[" << 95 << "m" << "Type your name to start: " << "\x1b[0m";
    cin >> name;

    cout << gotoxy(3, 16) << "\x1b[" << 95 << "m" << "Hello, "<<"\x1b[33m" << name << "\x1b[95m" <<", welcome to Tetris Battle!" << "\x1b[0m";
    cout << gotoxy(3, 17) << "\x1b[" << 95 << "m" << "0)If you play this gmae first time, "<<"\x1b[31m" <<"Press 0"<<"\x1b[95m" <<" to read tuorial!" << "\x1b[0m";
    cout << gotoxy(3, 18) << "\x1b[" << 95 << "m" << "1)One player (1p), " <<"\x1b[31m" <<"Press 1"<<"\x1b[95m" <<" to get start!" << "\x1b[0m";
    cout << gotoxy(3, 19) << "\x1b[" << 95 << "m" << "2)Two player (2p), " <<"\x1b[31m" <<"Press 2"<<"\x1b[95m" <<" to get start!" << "\x1b[0m";    
	  cout << gotoxy(3, 21) << "\x1b[" << 31 << "m" << "Type your Choice :                " << "\x1b[0m";
	  
	  while (cin >> person) {
      if (person != 0 && person != 1 && person != 2)
        cout << "Please choose number 0 ~ 2";
      else break;
    }
    if (person == 0) {
      clearscreen();
      cout << gotoxy(3, 1) << "Welcome to Tetris.";
      cout << gotoxy(3, 2) << "There are two modes in this game, Normal Mode and Five Blocks Mode.";
      cout << gotoxy(3, 3) << "In Normal Mode, rules are basically the same with the origin game.";
      cout << gotoxy(3, 4) << "In Five Blocks Mode, specially, there exist seven shapes composed of five blocks.";
      cout << gotoxy(3, 5) << "You have to eliminate blocks as much as you can and prevent they hit the top of the boundary.";
      
      cout << gotoxy(3, 7) << ">>Commands in one player mode:";
      cout << gotoxy(3, 8) << "  ←: move the block to left hand side.";
      cout << gotoxy(3, 9) << "  →: move the block to right hand side.";
      cout << gotoxy(3, 10) << "  ↑: rotate the block.";
      cout << gotoxy(3, 11) << "  ↓: increase the dropping speed.";
      cout << gotoxy(3, 12) << "  c: hold.";
      cout << gotoxy(3, 13) << "  p: pause.";
      cout << gotoxy(3, 14) << "  white space: move the block to the bottom.";
      
      cout << gotoxy(3, 16) << ">>Commands in two players mode:";
      cout << gotoxy(3, 17) << "  p: pause.";
      
      cout << gotoxy(3, 19) << "player1:";
      cout << gotoxy(3, 20) << "  d: move the block to left hand side.";
      cout << gotoxy(3, 21) << "  g: move the block to right hand side.";
      cout << gotoxy(3, 22) << "  r: rotate the block.";
      cout << gotoxy(3, 23) << "  f: increase the dropping speed.";
      cout << gotoxy(3, 24) << "  a: hold.";
      cout << gotoxy(3, 25) << "  z: move the block to the bottom.";
      
      cout << gotoxy(3, 27) << "player2:";
      cout << gotoxy(3, 28) << "  ←: move the block to left hand side.";
      cout << gotoxy(3, 29) << "  →: move the block to right hand side.";
      cout << gotoxy(3, 30) << "  ↑: rotate the block.";
      cout << gotoxy(3, 31) << "  ↓: increase the dropping speed.";
      cout << gotoxy(3, 32) << "  j: hold.";
      cout << gotoxy(3, 33) << "  m: move the block to the bottom.";
      cout << "After reading, press your number of person to continue!";
      
      cin >> person;

    }

	  
	  clearscreen();
	  show_Tetris_battle();
	  cout << gotoxy(3, 16) << "\x1b[" << 34 << "m" << "Choose one mode you want to play" << "\x1b[0m";
	  cout << gotoxy(3, 17) << "\x1b[" << 32 << "m" << "1)Normal Mode" << "\x1b[0m";
	  cout << gotoxy(3, 18) << "\x1b[" << 32 << "m" << "2)Five blocks Mode" << "\x1b[0m";
//    cout << gotoxy(3, 17) << "\x1b[" << 32 << "m" << "1)General Mode  4)Probs Mode" << "\x1b[0m";
//    cout << gotoxy(3, 18) << "\x1b[" << 32 << "m" << "2)Timing Mode   5)Image Mode" << "\x1b[0m";
//    cout << gotoxy(3, 19) << "\x1b[" << 32 << "m" << "3)Extreme Mode  6)Hell Mode " << "\x1b[0m";    
	  cout << gotoxy(3, 21) << "\x1b[" << 31 << "m" << "Type your Choice :                " << "\x1b[0m";
	  while (cin >> mode) {
      if (mode != 1 && mode != 2) 
        cout << "Please choose number 1 ~ 2";
      else break;
    }
	  
	  
	  clearscreen();
	  show_Tetris_battle();
	  cout << gotoxy(3, 16) << "\x1b[" << 34 << "m" << "Choose hardness you want to play " << "\x1b[0m";
    cout << gotoxy(3, 17) << "\x1b[" << 32 << "m" << "4)Easy  " << "\x1b[0m";
    cout << gotoxy(3, 18) << "\x1b[" << 32 << "m" << "3)General " << "\x1b[0m";
    cout << gotoxy(3, 19) << "\x1b[" << 32 << "m" << "2)Hard " << "\x1b[0m";
    cout << gotoxy(3, 20) << "\x1b[" << 32 << "m" << "1)Hell " << "\x1b[0m"; 
	  cout << gotoxy(3, 21) << "\x1b[" << 31 << "m" << "Type your Choice :                " << "\x1b[0m";
	  cin  >> hardness;
	  
	  bool sure = false;
	  while(!sure){
	    clearscreen();
	    show_Tetris_battle();
	    cout << gotoxy(3, 16) << "\x1b[" << 34 << "m" << "Choose one map you want to play " << "\x1b[0m";
      cout << gotoxy(3, 17) << "\x1b[" << 32 << "m" << "1)No map            5)Monster map" << "\x1b[0m";
      cout << gotoxy(3, 18) << "\x1b[" << 32 << "m" << "2)Combo map         " << "\x1b[0m";
      cout << gotoxy(3, 19) << "\x1b[" << 32 << "m" << "3)Turtle map        " << "\x1b[0m";
      cout << gotoxy(3, 20) << "\x1b[" << 32 << "m" << "4)Fire & Water map  " << "\x1b[0m"; 
	    cout << gotoxy(3, 21) << "\x1b[" << 31 << "m" << "Type your Choice :                " << "\x1b[0m";
	    cin  >> map_type;
	    
	    clearscreen();
	    boundary pool_boundary(1, 1, 12, 22);
	    Pool pool(map_type);
	    pool_boundary.showboundary();
	    pool.show();
	    cout << gotoxy(14, 6) << "\x1b[" << 34 << "m"  << "Do you want to play this Map" << "\x1b[0m";
	    cout << gotoxy(14, 7) << "\x1b[" << 32 << "m"  << "Press 1 to Start!" << "\x1b[0m";
	    cout << gotoxy(14, 8) << "\x1b[" << 32 << "m"  << "Press 0 to go back!" << "\x1b[0m";
	    cout << gotoxy(14, 9) << "\x1b[" << 31 << "m"  << "Yes/No (1/0) : " << "\x1b[0m";
	    cin >> sure;
	    
	  }
	 clearscreen();
	 return Loading;
  }
  
  GameStatus Game_Opreatoring_System::loading()  // Ken: understand
  {
    clearscreen();
    show_Tetris_battle();
    Timex temp;
    cout << gotoxy(3, 15) << "\x1b[" << 100 << "m" << "                                                                        " << "\x1b[0m";
    while(1){
      cout << gotoxy(50, 30) << temp.getduration() << endl;
      if(temp.getduration()>=0)
      {
        cout << gotoxy(3, 16) << "\x1b[" << 34 << "m" << "Loading." << "\x1b[0m";
        cout << gotoxy(3, 15) << "\x1b[" << 46 << "m" << "                  " << "\x1b[0m";
      }
      if(temp.getduration()*2>=1)
      {
        cout << gotoxy(3, 17) << "\x1b[" << 34 << "m" << "Loading.." << "\x1b[0m";
        cout << gotoxy(3, 15) << "\x1b[" << 46 << "m" << "                                  " << "\x1b[0m";
      }
      if(temp.getduration()*2>=2)
      {
        cout << gotoxy(3, 18) << "\x1b[" << 34 << "m" << "Loading..." << "\x1b[0m";
        cout << gotoxy(3, 15) << "\x1b[" << 46 << "m" << "                                               " << "\x1b[0m";
      }
      if(temp.getduration()*2>=3)
      {
        cout << gotoxy(3, 19) << "\x1b[" << 34 << "m" << "Successed" << "\x1b[0m";
        cout << gotoxy(3, 15) << "\x1b[" << 46 << "m" << "                                                                        " << "\x1b[0m";
        cout << gotoxy(3, 21);
        break;
      }
    }
    
    if(mode == 1 && person == 1)
      return Playing1;
    else if(mode == 2 && person == 1)
      return Playing2;
    else if(mode == 1 && person == 2)
      return Playing3;
    else if(mode == 2 && person == 2)
      return Playing4;
     return Playing1;  // Ken: default
  }
  
  
  GameStatus Game_Opreatoring_System::playing_mode1 ()  // Ken: the core of the game.
  {
    // mode 1: normal mode

    
    srand(time(NULL));
	  unsigned int holdtype = 0;
	  bool hold_true = false;
	  bool haveHold = false;
	  
	  boundary pool_boundary(1, 1, 12, 22);
	  boundary next_boundary(15, 1, 6, 5);
	  boundary hold_boundary(15, 7, 6, 5);
	  
	  Pool pool(map_type);
	  
	  
	  Shape in_pool;  // Ken: in_pool_shape
	  Shape hold((rand() % 7) + 1, 4, 17, 9);  // Ken: 先產生一個長的方塊？
	  score_system score;
	 
	  while (!pool.isfull() && score.getremaintime() > 0) {  // Ken: loop each frame.
	    Shape next; // declare next shape
	    clearscreen(); // clean window
      in_pool.movetoxy(6,1); // move to center
    
	    for (int i = 0; i < 400 && score.getremaintime() > 0; i++) {
		    clearscreen();
		    score.show();
		    pool_boundary.showboundary();
		    next_boundary.showboundary();
		    hold_boundary.showboundary();
		    cout << gotoxy(17, 6) << "NEXT";
		    cout << gotoxy(17, 12) << "HOLD";
		    
		    Shape shadow = in_pool;
		    shadow.setcolor(100);
        shadow.movetobottom2(pool);
      
        next.show();
        if (haveHold == true)  // Ken: modified
          hold.show();
        shadow.show();
	  	  pool.show();
	  	
	  	  if (kbhit()) {
		    
		      char command[3];
		  	  command[0] = getchar();
			    if(command[0] == ' ')
			    {
			  	  in_pool.movetobottom(pool);
			  	  pool.pushin(in_pool);
			  	  break;
			    }
			    else if (command[0] == 'p')
			    {
			      pause();
			    }
			    else if(command[0] == 'c')
			    {
			  	  holdtype = in_pool.gettype();
			  	  next = hold;
			  	  hold = Shape(holdtype, 4, 17, 9);
			  	  hold_true = true;
			  	  haveHold = true;
					  break;
			    }
			    else if(command[0] == 27)
			    {
			      getchar(); command[2] = getchar();
		  	    switch (command[2]) 
		  	    {
			  	    case 'D':
				  	    in_pool.left();
				  	    break;
				      case 'C':
				        in_pool.right();
					      break;
				      case 'A':
				        in_pool.RotateR();
					      break;
					    case 'B':
				        if (!in_pool.isbottom(pool)) in_pool.down(); 
				        i += 20;
					      break;
		  	    }
	  		  }
	  	  }

		    in_pool.show();
		    cout << gotoxy(50, 30) << i << endl;
		    if ((i % 20 == 0 && in_pool.isbottom(pool)) || i > 379)
		    {
		      pool.pushin(in_pool);
		      break;
		    } 
		    else if (i % 20 == 0 && !in_pool.isbottom(pool)) in_pool.down();
		  
		    sleep001(hardness);
	    }
	    score.checkpoint(pool.isrow(), hold_true);
	    in_pool = next;
	    
	  }
	  total = score;
	  return GameOver;
  }
  
  GameStatus Game_Opreatoring_System::playing_mode2()
  {

    
    srand(time(NULL));
	  unsigned int holdtype = 0;
	  bool hold_true = false;
	  bool haveHold = false;
	  
	  boundary pool_boundary(1, 1, 12, 22);
	  boundary next_boundary(15, 1, 6, 5);
	  boundary hold_boundary(15, 7, 6, 5);
	  
	  Pool pool(map_type);
	  
    Shape5 in_pool;  // Ken: in_pool_shape
//	  Shape5(holdtype, 5, 17, 9);
	  Shape5 hold((rand() % 7) + 1, 5, 17, 9);  // Ken: 先產生一個長的方塊？ // rand() % 2
	  score_system score;
//	boundary pool2_boundary(30, 1, 12, 22);
//	boundary next2_boundary(22, 1, 6, 5); 
//	boundary hold2_boundary(22, 7, 6, 5);
//	Pool pool2; 	

	  while (!pool.isfull() && score.getremaintime() > 0) {  // Ken: loop each frame.
	    Shape5 next; // declare next shape
	    clearscreen(); // clean window
      in_pool.movetoxy(6,1); // move to center
    
	    for (int i = 0; i < 400 && score.getremaintime() > 0; i++) {
		    clearscreen();
		    score.show();
		    pool_boundary.showboundary();
		    next_boundary.showboundary();
		    hold_boundary.showboundary();
		    cout << gotoxy(17, 6) << "NEXT";
		    cout << gotoxy(17, 12) << "HOLD";
//			pool2_boundary.showboundary();
//		  next2_boundary.showboundary();
//		  hold2_boundary.showboundary();			
		  
		    Shape5 shadow = in_pool;
		    shadow.setcolor(100);
        shadow.movetobottom2(pool);
      
        next.show();
        if (haveHold == true)  // Ken: modified
          hold.show();
        shadow.show();
	  	  pool.show();
	  	
	  	  if (kbhit()) {
		    
		      char command[3];
		  	  command[0] = getchar();
			    if(command[0] == ' ')
			    {
			  	  in_pool.movetobottom(pool);
			  	  pool.pushin(in_pool);
			  	  break;
			    }
			    else if (command[0] == 'p')
			    {
			      pause();
			    }
			    else if(command[0] == 'c')
			    {
			  	  holdtype = in_pool.gettype();
			  	  next = hold;
			  	  hold = Shape5(holdtype, 5, 17, 9);
			  	  hold_true = true;
			  	  haveHold = true;
					  break;
			    }
			    else if(command[0] == 27)
			    {
			      getchar(); command[2] = getchar();
		  	    switch (command[2]) 
		  	    {
			  	    case 'D':
				  	    in_pool.left();
				  	    break;
				      case 'C':
				        in_pool.right();
					      break;
				      case 'A':
				        in_pool.RotateR();
					      break;
					    case 'B':
				        if (!in_pool.isbottom(pool)) in_pool.down(); 
				        i += 20;
					      break;
		  	    }
	  		  }
	  	  }

		    in_pool.show();
		    cout << gotoxy(50, 30) << i << endl;
		    if ((i % 20 == 0 && in_pool.isbottom(pool)) || i > 379)
		    {
		      cout << gotoxy(30, 20) << "are you ok?" << endl; // delete
		      pool.pushin(in_pool);
		      cout << gotoxy(35, 20) << "yes, I'm." << endl;
		      break;
		    } 
		    else if (i % 20 == 0 && !in_pool.isbottom(pool)) in_pool.down();
		  
		    sleep001(hardness);
	    }
	    score.checkpoint(pool.isrow(), hold_true);
	    in_pool = next;
	    
	  }
	  total = score;
	  return GameOver;
  }
  
  GameStatus Game_Opreatoring_System::playing_mode3()
  {
    // mode 3: normal mode

    
    srand(time(NULL));
	  unsigned int holdtype = 0, holdtype2 = 0;
	  bool hold_true = false, hold_true2 = false;
	  bool haveHold = false, haveHold2 = false;
	  
	  boundary pool_boundary(1, 1, 12, 22);
	  boundary next_boundary(15, 1, 6, 5);
	  boundary hold_boundary(15, 7, 6, 5);
	  boundary pool2_boundary(30, 1, 12, 22);
    boundary next2_boundary(22, 1, 6, 5); 
  	boundary hold2_boundary(22, 7, 6, 5);
  	 	
	  Pool pool(map_type);
	  Pool pool2(map_type);
	  
	  
	  Shape in_pool, in_pool2;  // Ken: in_pool_shape
	  Shape hold((rand() % 7) + 1, 4, 17, 9);
	  Shape hold2((rand() % 7) + 1, 4, 17, 9);// Ken: 先產生一個長的方塊？
	  score_system score, score2;
	  

  	  


	  while (!pool.isfull() && score.getremaintime() > 0) {  // Ken: loop each frame.
	    Shape next, next2; // declare next shape
	    next2.movetoxy(24,3);
	    
	    clearscreen(); // clean window
      in_pool.movetoxy(6,1); // move to center
      in_pool2.movetoxy(35,1);
      
	    for (int i = 0; i < 400 && score.getremaintime() > 0; i++) {
		    clearscreen();
		    score.show(), score2.show();
		    pool_boundary.showboundary(); pool2_boundary.showboundary();
		    next_boundary.showboundary(); next2_boundary.showboundary();
		    hold_boundary.showboundary(); hold2_boundary.showboundary();
		    cout << gotoxy(17, 6) << "NEXT";
		    cout << gotoxy(17, 12) << "HOLD";
		  
		    Shape shadow = in_pool, shadow2 = in_pool2;
		    shadow.setcolor(100); shadow2.setcolor(100);
        shadow.movetobottom2(pool); shadow2.movetobottom2(pool2);
      
        next.show(); next2.show();
        
        if (haveHold == true)  // Ken: modified
          hold.show();
        if (haveHold2 == true)  // Ken: modified
          hold2.show();
          
        shadow.show(); shadow2.show();
	  	  pool.show(); pool2.show();
	  	
	  	  if (kbhit()) {
		    
		      char command[3];
		  	  command[0] = getchar();
			    if(command[0] == 'm')
			    {
			  	  in_pool.movetobottom(pool);
			  	  pool.pushin(in_pool);
			  	  break;
			    }
			    
			    else if(command[0] == 'j')
			    {
			  	  holdtype2 = in_pool2.gettype();
			  	  next2 = hold2;
			  	  hold2 = Shape(holdtype2, 4, 17, 9);
			  	  hold_true2 = true;
			  	  haveHold2 = true;
					  break;
			    }
			    else if(command[0] == 27)
			    {
			      getchar(); command[2] = getchar();
		  	    switch (command[2]) 
		  	    {
			  	    case 'D':
				  	    in_pool2.left();
				  	    break;
				      case 'C':
				        in_pool2.right();
					      break;
				      case 'A':
				        in_pool2.RotateR();
					      break;
					    case 'B':
				        if (!in_pool2.isbottom(pool)) in_pool2.down(); 
				        i += 20;
					      break;
		  	    }
	  		  }
	  		  else if (command[0] == 'p')
			    {
			      pause();
			    }
	  	  }

		    in_pool.show();
		    cout << gotoxy(50, 30) << i << endl;
		    if ((i % 20 == 0 && in_pool.isbottom(pool)) || i > 379)
		    {
		      pool.pushin(in_pool);
		      break;
		    } 
		    else if (i % 20 == 0 && !in_pool.isbottom(pool)) in_pool.down();
		  
		    sleep001(hardness);
	    }
	    score.checkpoint(pool.isrow(), hold_true);
	    in_pool = next;
	    
	  }
	  total = score;
	  return GameOver;
  }
  
  GameStatus Game_Opreatoring_System::playing_mode4()
  {

    
    srand(time(NULL));
	  unsigned int holdtype = 0;
	  bool hold_true = false;
	  bool haveHold = false;
	  
	  boundary pool_boundary(1, 1, 12, 22);
	  boundary next_boundary(15, 1, 6, 5);
	  boundary hold_boundary(15, 7, 6, 5);
	  
	  Pool pool(map_type);
	  
    Shape5 in_pool;  // Ken: in_pool_shape
//	  Shape5(holdtype, 5, 17, 9);
	  Shape5 hold((rand() % 7) + 1, 5, 17, 9);  // Ken: 先產生一個長的方塊？ // rand() % 2
	  score_system score;
//	boundary pool2_boundary(30, 1, 12, 22);
//	boundary next2_boundary(22, 1, 6, 5); 
//	boundary hold2_boundary(22, 7, 6, 5);
//	Pool pool2; 	

	  while (!pool.isfull() && score.getremaintime() > 0) {  // Ken: loop each frame.
	    Shape5 next; // declare next shape
	    clearscreen(); // clean window
      in_pool.movetoxy(6,1); // move to center
    
	    for (int i = 0; i < 400 && score.getremaintime() > 0; i++) {
		    clearscreen();
		    score.show();
		    pool_boundary.showboundary();
		    next_boundary.showboundary();
		    hold_boundary.showboundary();
		    cout << gotoxy(17, 6) << "NEXT";
		    cout << gotoxy(17, 12) << "HOLD";
//			pool2_boundary.showboundary();
//		  next2_boundary.showboundary();
//		  hold2_boundary.showboundary();			
		  
		    Shape5 shadow = in_pool;
		    shadow.setcolor(100);
        shadow.movetobottom2(pool);
      
        next.show();
        if (haveHold == true)  // Ken: modified
          hold.show();
        shadow.show();
	  	  pool.show();
	  	
	  	  if (kbhit()) {
		    
		      char command[3];
		  	  command[0] = getchar();
			    if(command[0] == ' ')
			    {
			  	  in_pool.movetobottom(pool);
			  	  pool.pushin(in_pool);
			  	  break;
			    }
			    else if (command[0] == 'p')
			    {
			      pause();
			    }
			    else if(command[0] == 'c')
			    {
			  	  holdtype = in_pool.gettype();
			  	  next = hold;
			  	  hold = Shape5(holdtype, 5, 17, 9);
			  	  hold_true = true;
			  	  haveHold = true;
					  break;
			    }
			    else if(command[0] == 27)
			    {
			      getchar(); command[2] = getchar();
		  	    switch (command[2]) 
		  	    {
			  	    case 'D':
				  	    in_pool.left();
				  	    break;
				      case 'C':
				        in_pool.right();
					      break;
				      case 'A':
				        in_pool.RotateR();
					      break;
					    case 'B':
				        if (!in_pool.isbottom(pool)) in_pool.down(); 
				        i += 20;
					      break;
		  	    }
	  		  }
	  	  }

		    in_pool.show();
		    cout << gotoxy(50, 30) << i << endl;
		    if ((i % 20 == 0 && in_pool.isbottom(pool)) || i > 379)
		    {
		      cout << gotoxy(30, 20) << "are you ok?" << endl; // delete
		      pool.pushin(in_pool);
		      cout << gotoxy(35, 20) << "yes, I'm." << endl;
		      break;
		    } 
		    else if (i % 20 == 0 && !in_pool.isbottom(pool)) in_pool.down();
		  
		    sleep001(hardness);
	    }
	    score.checkpoint(pool.isrow(), hold_true);
	    in_pool = next;
	    
	  }
	  total = score;
	  return GameOver;
  }
  GameStatus Game_Opreatoring_System::gameover()  // Ken: understand
  {
    clearscreen(); // clean window
    Rank a("rank.in");
	  a.getrank(data(name,mode,total.getgrade(),total.gethcombo()));
    cout << gotoxy(21, 5) << "\x1b[" << 34 << "m" << "Your Score is : "<< total.getgrade() << "\x1b[0m";
    cout << gotoxy(21, 6) << "\x1b[" << 34 << "m" << "Your Highest Combo is : "<< total.gethcombo() << "\x1b[0m";
//    cout << gotoxy(21, 7) << "\x1b[" << 34 << "m" << "Your Combo is : "<< total.getcombo() << "\x1b[0m";
    cout << gotoxy(21, 9) << "\x1b[" << 34 << "m" << "Do You Want To Try Again? " << "\x1b[0m";
    cout << gotoxy(21, 10) << "\x1b[" << 32 << "m" << "1)Try Again!" << "\x1b[0m";
    cout << gotoxy(21, 11) << "\x1b[" << 32 << "m" << "2)Back to Menu" << "\x1b[0m";
    cout << gotoxy(21, 12) << "\x1b[" << 32 << "m" << "3)End of Game " << "\x1b[0m";
	  cout << gotoxy(21, 15) << "\x1b[" << 31 << "m" << "Type your Choice :   " << "\x1b[0m";
	  int choice;
	//  cin  >> choice;
    while (cin  >> choice){
	  
	  if (choice == 1) {
      if(mode == 1 && person == 1)
        return Playing1;
      else if(mode == 2 && person == 1)
        return Playing2;
      else if(mode == 1 && person == 2)
        return Playing3;
      else if(mode == 2 && person == 2)
        return Playing4;
	  }
	  if (choice == 2) return Menu;
	  if (choice == 3) exit (1);
    }
		// control reach non void function
		// assume true
		// please fix it if you see it
  }

  void Game_Opreatoring_System::pause()
  {
    clearscreen();
    char a;
    show_Tetris_battle();
    cout << gotoxy(3, 16) << "If you want to continue playing, please press 'p': ";
    while (cin >> a)
      if (a == 'p')
        return;
  }


//end class



#endif
