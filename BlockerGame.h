#include <iostream>
#include <iomanip>
#include <string>
#include "CustomPlayers.h" // this will come with Board.h, Player.h and Utils.h

using namespace std;

class BlockerGame
{
   Board board;
   Player *player1;
   Player *player2;

public:
   BlockerGame(int boardsize, Player *p1, Player *p2) : board(boardsize)
   {
      player1 = p1;
      player2 = p2;
   };
   void play();
};

void BlockerGame::play()
{
   actor whoWon = checkWin(board);
   while (whoWon == NO_ONE)
   {
      int cx = 0;
      int cy = 0;
      int bx = 0;
      int by = 0;
      player1->getMove(board, cx, cy);
       player2->getMove(board, bx, by);
      if (bx >= 0 && by >= 0 && cx >= 0 && cy >= 0)
      {
         board.addMove(cx, cy, bx, by);
         board.printBoard();
         whoWon = checkWin(board);
      }
      else
      {
         whoWon = BLOCKER;
      }
   }
   switch (whoWon)
   {
   case CROSSER:
      cout << "The game is won by: CROSSER!!" << endl;
      break;

   case BLOCKER:
      cout << "The game is won by: BLOCKER!!" << endl;
      break;
   }
}