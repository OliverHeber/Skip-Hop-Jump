#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Board
{
private:
   int boardsize;
   int **grid;

public:
   Board(int size)
   {
      boardsize = size;
      grid = new int *[boardsize];
      for (int i = 0; i < boardsize; ++i)
      {
         grid[i] = new int[boardsize];
      }

      for (int i = 0; i < boardsize; i++)
      {
         for (int j = 0; j < boardsize; j++)
         {
            grid[i][j] = 0;
         }
      }
   };

   ~Board()
   {
      for (int i = 0; i < boardsize; ++i)
      {
         delete[] grid[i];
      }
      delete[] grid;
   };

   bool addMove(int cx, int cy, int bx, int by);

   bool validInput(int x, int y);
   void printBoard();
   bool isBoardFull();
   int getBoardSize();
   int **getGrid();
   bool validateBoundary(int x, int y);
};

bool Board::validateBoundary(int x, int y)
{
   if (x > boardsize - 1 || x < 0)
   {
      return false;
   }

   if (y > boardsize - 1 || y < 0)
   {
      return false;
   }
   return true;
};

int **Board::getGrid()
{
   return grid;
};

int Board::getBoardSize()
{
   return boardsize;
};

bool Board::addMove(int cx, int cy, int bx, int by)
{
   grid[cx][cy] = 1;
   grid[bx][by] = -1;
   return true;
};

bool Board::validInput(int x, int y)
{
   bool isValidBoundary = validateBoundary(x, y);

   if (isValidBoundary)
   {
      if (grid[x][y] == 0)
      {
         return true;
      }
      else
         return false;
   }
   else
      return false;
};

void Board::printBoard()
{
   for (int i = 0; i < boardsize; i++)
   {
      if (i == 0)
      {
         cout << "     " << i + 1;
      }
      else if (i < boardsize - 1)
      {
         if (i < 9)
         {
            cout << "   " << i + 1;
         }
         else if (i == 9)
         {
            cout << "   " << i + 1 << " ";
         }
         else if (i == 10)
         {
            cout << " " << i + 1;
         }
         else
            cout << "  " << i + 1;
      }
      else
      {
         if (i < 9)
         {
            cout << "   " << i + 1 << endl;
         }
         else
            cout << "  " << i + 1 << endl;
      }
   }

   // Creating dashes at top of board
   for (int i = 0; i < boardsize; i++)
   {
      if (i == 0)
      {
         cout << "   "
              << "----";
      }
      else if (i < boardsize - 1)
      {
         cout << "----";
      }
      else
      {
         cout << "----" << endl;
      }
   }
   // Creating the middle matrix of the board
   for (int i = 0; i < boardsize; i++)
   {
      if (i < 9)
      {
         cout << i + 1 << "  |";
      }
      else
      {
         cout << i + 1 << " |";
      }
      for (int j = 0; j < boardsize; j++)
      {
         char playerSymbol = ' ';
         if (grid[i][j] == 1)
            playerSymbol = 'C';
         else if (grid[i][j] == -1)
            playerSymbol = 'B';
         cout << setw(2) << playerSymbol << " |";
      }
      if (i != boardsize - 1)
      {
         cout << endl
              << endl;
      }
      else
         cout << endl;
   }

   // Creating dashes at bottom of board
   for (int i = 0; i < boardsize; i++)
   {
      if (i == 0)
      {
         cout << "   "
              << "----";
      }
      else if (i < boardsize - 1)
      {
         cout << "----";
      }
      else
      {
         cout << "----" << endl;
      }
   }
};