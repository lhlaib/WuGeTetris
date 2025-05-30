#include <iostream>
#include "map.h"
#include "blocks.h"

#include "rank.h"
#include "game.h"
using namespace std;


int main()
{
  clearscreen();
  Rank a("rank.in");

  a.getrank(data("IV5",1,500));

  return 0;
}