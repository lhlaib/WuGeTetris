#ifndef RANK_H
#define RANK_H
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>

class data
{
public:
  data(string a, int b, int c, int d):name(a), mode(b), score(c), highest_combo(d) {}
  data() {}
  friend bool CompareFunction(const data& a,const data& b);
  friend class Rank;
private:
  string name;
  int mode;
  int score;
  int highest_combo;
};

bool CompareFunction(const data& a,const data& b) {
    if(a.mode < b.mode) return true;
    else if (a.mode > b.mode) return false;
    else if (a.score > b.score) return true;
    else if (a.score < b.score) return false;
    else if (a.highest_combo > b.highest_combo) return true;
    else if (a.highest_combo < b.highest_combo) return false;
    else if (a.name < b.name) return true;
    else if (a.name > b.name) return false;
    return true; // Ken: control reach non-void function
}

class Rank
{
public:
  Rank(string file,int a = 0,data b = data("N",0,0,0)) : rank_file_name(file), count(a), user(b) {}
  void readfile();
  void writefile();
  bool push_back_data(data a);
  void sorting_data();
  void show_rank(int mode);
  void getrank(data temp);
private:
  string rank_file_name;
  vector<data> Point_vec;
  data user;
  int count;
};

//Rank member function
  void Rank::writefile() {
    fstream rank_file;
    rank_file.open(rank_file_name.c_str(), ios::out | ios::app);
    if(!rank_file) cout << "failed";
    rank_file << user.name << " " << user.mode << " " << user.score << " " << user.highest_combo << endl;
    rank_file.close();
  }
  
  void Rank::readfile()
  {
    fstream rank_file;
    rank_file.open(rank_file_name.c_str(), ios::in);
    if(!rank_file) cout<<"failed";
    
    string name; int m,s,h;
    while(rank_file >> name)
    {
      rank_file >> m >> s >> h;
      Point_vec.push_back(data(name, m, s, h));
      count++;
    }
  }
  
  bool Rank::push_back_data(data a){
    user = a;
    Point_vec.push_back(user);
    count++;
    return true;
  }

  void Rank::sorting_data()
  {
    sort(Point_vec.begin(), Point_vec.end(),CompareFunction);
  }

  void Rank::show_rank(int mode)
  {
    int i = 0,c = 1;
    clearscreen();
    cout << gotoxy(1, 2) << "+====================================+";
    cout << gotoxy(1, 3) << "|        R     A     N     K         |";
    cout << gotoxy(1, 4) << "+====================================+";
    cout << gotoxy(1, 5) << "|  ";
    cout << std::setw(8) <<std::left<< "Rank";  
    cout << std::setw(10)<<std::left << "Name";
    cout << std::setw(8)<<std::left << "Score";
    cout << std::setw(8) <<std::left<< "H_combo"; 
    cout << "|";
    for(i = 0; i < count && c<=10; i++)
    {
      if(Point_vec[i].mode == mode)
      {
        cout <<  gotoxy(1,5 + c) << "|  ";
        if(user.name!="N"&&Point_vec[i].name == user.name && Point_vec[i].score == user.score)
          cout << "\x1b[" << 100 << "m"<< "\x1b[" << 91 << "m"  ;
        cout << std::setw(8) << c;  
        cout << std::setw(10) << Point_vec[i].name;
        cout << std::setw(8) << Point_vec[i].score;
        cout << std::setw(8) << Point_vec[i].highest_combo;
        if(user.name!="N"&&Point_vec[i].name == user.name && Point_vec[i].score == user.score)
          cout << "\x1b[0m";
        cout << "|";
        c++;
      }
    }
    cout << gotoxy(1, 5 + c) << "+====================================+"<<endl;
  }
  void Rank::getrank(data temp)
  {
    readfile();
    push_back_data(temp);
    sorting_data();
    show_rank(temp.mode);
    writefile();
  }
//end class

#endif