#include <iostream>
#include <iomanip>
#include <string>
#include "Player.h" // this will come with "Board.h"

using namespace std;

//########################################### HumanPlayer
class HumanPlayer : public Player
{
private:
   string playerName;

public:
   HumanPlayer(int pType, string pName) : Player(pType)
   {
      playerName = pName;
   };
   void getMove(Board &b, int &x, int &y);
   int getType();
};

void HumanPlayer::getMove(Board &b, int &x, int &y)
{
   while (true)
   {
      // Getting x coordinate
      cout << "Please enter " << playerName << " x-coordinate: ";
      cin >> x;
      if (!cin)
      {
         reset_cin("Move was invalid, please try again!");
         continue;
      }

      // Getting y coordinate
      cout << "Please enter " << playerName << " y-coordinate: ";
      cin >> y;
      if (!cin)
      {
         reset_cin("Move was invalid, please try again!");
         continue;
      }
      x -= 1;
      y -= 1;

      // Validate move
      if (b.validInput(x, y))
      {
         break;
      }
      cout << "Move was invalid - please try again!" << endl;
   }
};

int HumanPlayer::getType()
{
   return playerType;
};

//########################################### RandomPlayer
class RandomPlayer : public Player
{
private:
   string playerName;

public:
   RandomPlayer(int pType, string pName) : Player(pType)
   {
      playerName = pName;
   };
   void getMove(Board &b, int &x, int &y);
   int getType();
};

void RandomPlayer::getMove(Board &b, int &x, int &y)
{
   srand(time(0));
   int row = 0;
   int col = 0;

   do
   {
      row = rand() % b.getBoardSize();
      col = rand() % b.getBoardSize();
   } while (!b.validInput(row, col));

   x = row;
   y = col;
};

int RandomPlayer::getType()
{
   return playerType;
};

//########################################### StraightLinePlayer
class StraightLinePlayer : public Player
{
private:
   string playerName;
   bool isFirstMove = true;
   int targetedRow;
   int targetedCol;

public:
   StraightLinePlayer(int pType, string pName) : Player(pType)
   {
      playerName = pName;
   };
   void getMove(Board &b, int &x, int &y);
   int getType();
};

void StraightLinePlayer::getMove(Board &b, int &x, int &y)
{
   if (playerType == 1)
   {
      if (isFirstMove)
      {
         targetedRow = 0;
         x = targetedRow;
         targetedCol = 0;
         y = targetedCol;
         isFirstMove = false;
      }
      else
      {
         targetedCol += 1;
         x = targetedRow;
         y = targetedCol;
         if (y > b.getBoardSize() - 1)
         {
            targetedRow += 1;
            x = targetedRow;
            targetedCol = 0;
            y = targetedCol;
         }
         while (b.getGrid()[x][y] != 0)
         {
            targetedCol += 1;
            x = targetedRow;
            y = targetedCol;
            if (y > b.getBoardSize() - 1)
            {
               targetedRow += 1;
               x = targetedRow;
               targetedCol = 0;
               y = targetedCol;
            }
            if (targetedRow >= b.getBoardSize())
            {
               x = -1;
               y = -1;
               break;
            }
         }
      }
   }
   else if (playerType == -1)
   {
      if (isFirstMove)
      {
         targetedRow = 0;
         x = targetedRow;
         targetedCol = b.getBoardSize() - 1;
         y = targetedCol;
         isFirstMove = false;
      }
      else
      {
         targetedRow += 1;
         x = targetedRow;
         y = targetedCol;
         if (x > b.getBoardSize() - 1)
         {
            targetedCol -= 1;
            y = targetedCol;
            targetedRow = 0;
            x = targetedRow;
         }
         while (b.getGrid()[x][y] != 0)
         {
            targetedRow += 1;
            x = targetedRow;
            y = targetedCol;
            if (x > b.getBoardSize() - 1)
            {
               targetedCol -= 1;
               y = targetedCol;
               targetedRow = 0;
               x = targetedRow;
            }
            if (targetedCol < 0)
            {
               x = -1;
               y = -1;
               break;
            }
         }
      }
   }
};

int StraightLinePlayer::getType()
{
   return playerType;
};

//########################################### SmartCrosserPlayer
class SmartCrosserPlayer : public Player
{
private:
   string playerName;
   vector<int> previousState;
   vector<int> nextState;
   bool startStateFound = false;
   bool goalStateFound = false;
   vector<int> startState;
   vector<int> goalState;

public:
   SmartCrosserPlayer(int pType, string pName) : Player(pType)
   {
      playerName = pName;
   };
   void getMove(Board &b, int &x, int &y);
   int getType();
};

void SmartCrosserPlayer::getMove(Board &b, int &x, int &y)
{
   bool playRandomlyStart = true;
   bool playRandomlyGoal = true;
   //1. Select randomly a start state from the first column - play that move
   // Verify move was actually played
   if (nextState.size() > 0)
   {
      if (b.getGrid()[nextState[0]][nextState[1]] == 1)
      {
         // Crosser move was accepted
         if (nextState[1] == 0)
         {
            startStateFound = true;
            startState.push_back(nextState[0]);
            startState.push_back(nextState[1]);
            nextState.clear();
         }
         else if (nextState[1] == b.getBoardSize() - 1)
         {
            goalStateFound = true;
            goalState.push_back(nextState[0]);
            goalState.push_back(nextState[1]);
            nextState.clear();
         }
         else
         {
            startState[0] = nextState[0];
            startState[1] = nextState[1];
            nextState.clear();
         }
      }
      else
      {
         nextState.clear();
      }
   }
   // Verify all start states are blocked <- Play randomly
   for (int i = 0; i < b.getBoardSize(); i++)
   {
      // Check for crosser move/empty move, don't play randomly
      if (b.getGrid()[i][0] == 1 || b.getGrid()[i][0] == 0)
      {
         playRandomlyStart = false;
      }
   }

   // Verfiy all goal states are blocked <- Play randomly
   for (int i = 0; i < b.getBoardSize(); i++)
   {
      // Check for crosser move/empty move, don't play randomly
      if (b.getGrid()[i][b.getBoardSize() - 1] == 1 || b.getGrid()[i][b.getBoardSize() - 1] == 0)
      {
         playRandomlyGoal = false;
      }
   }

   if (!startStateFound && !playRandomlyStart && !playRandomlyGoal)
   {
      srand(time(NULL));
      int row = 0;

      do
      {
         row = rand() % b.getBoardSize();
      } while (!b.validInput(row, 0));

      x = row;
      y = 0;

      nextState.push_back(x);
      nextState.push_back(y);
   }
   else if (!goalStateFound && !playRandomlyStart && !playRandomlyGoal)
   {
      srand(time(NULL));
      int row = 0;
      int col = b.getBoardSize() - 1;

      do
      {
         row = rand() % b.getBoardSize();
      } while (!b.validInput(row, col));

      x = row;
      y = col;

      nextState.push_back(x);
      nextState.push_back(y);
   }
   else if (!playRandomlyStart && !playRandomlyGoal)
   {
      // Connecting start and goal state
      SearchNode *parent;
      SearchNode *startNode = new SearchNode(startState[0], startState[1], 0, parent);
      vector<vector<int>> goalStates = getAllPossibleGoalStates(b);
      vector<int> playerTypes = {0, 1};

      // pass board size, start node (where to begin search), crosser/blocker, goal states
      vector<actions> solution = depth_first_search(b, startNode, playerTypes, goalStates);
      if (solution.size() > 0)
      {
         actions nextAction = solution[0];
         vector<int> coords = get_coordinates_for_action(startState[0], startState[1], nextAction);
         nextState.push_back(coords[0]);
         nextState.push_back(coords[1]);
         x = coords[0];
         y = coords[1];
      }
      else
      {
         srand(time(NULL));
         int row = 0;
         int col = 0;

         do
         {
            row = rand() % b.getBoardSize();
            col = rand() % b.getBoardSize();
         } while (!b.validInput(row, col));

         x = row;
         y = col;
      }
   }
   else if (playRandomlyStart || playRandomlyGoal)
   {
      srand(time(NULL));
      int row = 0;
      int col = 0;

      do
      {
         row = rand() % b.getBoardSize();
         col = rand() % b.getBoardSize();
      } while (!b.validInput(row, col));

      x = row;
      y = col;
   }
}

int SmartCrosserPlayer::getType()
{
   return playerType;
};