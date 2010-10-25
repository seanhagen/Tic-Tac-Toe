#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

int main( int argc, char** argv ){

  GameEngine *engine = new GameEngine();

  engine->gameLoop();

  return 0;
}
