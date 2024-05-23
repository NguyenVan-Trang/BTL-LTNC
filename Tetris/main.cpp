#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
  Game game;
  game.showMenu();
  while (game.tick());

  return 0;
}
