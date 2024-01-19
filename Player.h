#include <iostream>
#include <iomanip>
#include <string>
#include "Utils.h"

using namespace std;

class Player
{
protected:
   int playerType;

public:
   Player(int pType)
   {
      playerType = pType;
   };
   virtual void getMove(Board &b, int &x, int &y) = 0;
   virtual int getType() = 0;
};