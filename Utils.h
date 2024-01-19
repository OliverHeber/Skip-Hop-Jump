#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include "Board.h"

using namespace std;

enum actor
{
   NO_ONE = 0,
   CROSSER = 1,
   BLOCKER = 2
};

// Possible actions
enum actions
{
   NONE = 0,
   UP = 1,
   DOWN = 2,
   RIGHT = 3,
   UP_RIGHT = 4,
   DOWN_RIGHT = 5
};

void reset_cin(string message)
{
   cout << message << endl;
   cin.clear();
   cin.ignore();
};

bool isBoardFull(Board &b)
{
   bool isFull = true;

   for (int i = 0; i < b.getBoardSize(); i++)
   {
      for (int j = 0; j < b.getBoardSize(); j++)
      {
         if (b.getGrid()[i][j] == 0)
         {
            isFull = false;
            break;
         }
      }
      if (!isFull)
         break;
   }
   return isFull;
}

// Defines state (coordinate), action, and previous node
class SearchNode
{
public:
   vector<int> state;
   actions action;
   SearchNode *parent;

   SearchNode(int x, int y, int act, SearchNode *prt)
   {
      action = static_cast<actions>(act);
      parent = prt;
      vector<int> newState = {x, y};
      state = newState;
   };

   // When goal state is reached, path is reversed and passed back
   vector<actions> extract_solution()
   {
      vector<actions> solution_path;
      SearchNode *node = this;
      while (node->action != NONE)
      {
         solution_path.push_back(node->action);
         node = node->parent;
      };
      reverse(solution_path.begin(), solution_path.end());
      return solution_path;
   };
};

// Return coordinates after undertaking an action
vector<int> get_coordinates_for_action(int x, int y, actions action)
{
   vector<int> coords;
   switch (action)
   {
   case UP:
      coords.push_back(x - 1);
      coords.push_back(y);
      break;
   case DOWN:
      coords.push_back(x + 1);
      coords.push_back(y);
      break;
   case RIGHT:
      coords.push_back(x);
      coords.push_back(y + 1);
      break;
   case UP_RIGHT:
      coords.push_back(x - 1);
      coords.push_back(y + 1);
      break;
   case DOWN_RIGHT:
      coords.push_back(x + 1);
      coords.push_back(y + 1);
      break;
   };
   return coords;
};

// Given a position, identifies child nodes
vector<SearchNode> get_successors(Board &b, SearchNode *source, vector<int> playerTypes)
{
   // source is the node to be explored (we are checking for successors)
   int startx = source->state[0];
   int starty = source->state[1];
   vector<SearchNode> nextNodes;

   for (int act = UP; act <= DOWN_RIGHT; act++)
   {
      actions action = static_cast<actions>(act);
      vector<int> coords = get_coordinates_for_action(source->state[0], source->state[1], action);

      if (b.validateBoundary(coords[0], coords[1]))
      {
         for (auto playerType : playerTypes)
         {
            if (b.getGrid()[coords[0]][coords[1]] == playerType)
            {
               SearchNode nextNode(coords[0], coords[1], act, source);
               nextNodes.push_back(nextNode);
            };
         }
      };
   };
   return nextNodes;
};

// Check if goal state reached
bool is_state_in_goal_states(vector<int> state, vector<vector<int>> goalStates)
{
   for (auto goalState : goalStates)
   {
      if ((goalState[0] == state[0]) && (goalState[1] == state[1]))
      {
         return true;
      }
   }
   return false;
}

// DFS
vector<actions> depth_first_search(Board &b, SearchNode *startNode, vector<int> playerTypes, vector<vector<int>> goalStates)
{
   // Getting start node onto stack to then explore all nodes until stack is empty or goal state is reached (win or lose for crosser)
   // Stack of search node pointers to be explored
   stack<SearchNode *> frontier;
   // Set will contain unique explored nodes to ensure seen nodes are not re-seen
   set<vector<int>> explored;
   // List of actions (enums)
   vector<actions> solution_path;
   frontier.push(startNode);
   // Runs until stack is empty
   while (!frontier.empty())
   {
      // Return top most element in stack then pop it out and explore the topped element
      SearchNode *node = frontier.top();
      frontier.pop();
      // State (coordinate) is seen and will not be explored again
      explored.insert(node->state);

      // Check if state is a goal state, if so fire extract_solution
      if (is_state_in_goal_states(node->state, goalStates))
      {
         return node->extract_solution();
      };

      // Expand node
      vector<SearchNode> successors = get_successors(b, node, playerTypes);

      // Run a loop to check if nodes to be explored have already been explored,
      //if so, do not add them to the stack(avoid loops / never ending stack).
      for (auto item : successors)
      {
         // Check if node is already explored
         if (explored.find(item.state) == explored.end())
         {
            // Pass current node as the parent node in order to build the graph
            SearchNode *child_node = new SearchNode(item.state[0], item.state[1], item.action, item.parent);
            frontier.push(child_node);
         };
      };
   };
   return solution_path;
};

vector<vector<int>> getStartStates(Board &b)
{
   vector<vector<int>> startStates;

   for (int i = 0; i < b.getBoardSize(); i++)
   {
      if (b.getGrid()[i][0] == 1)
      {
         vector<int> startState = {i, 0};
         startStates.push_back(startState);
      }
   }
   return startStates;
};

vector<vector<int>> getGoalStates(Board &b)
{
   vector<vector<int>> goalStates;

   for (int i = 0; i < b.getBoardSize(); i++)
   {
      if (b.getGrid()[i][b.getBoardSize() - 1] == 1)
      {
         vector<int> goalState = {i, b.getBoardSize() - 1};
         goalStates.push_back(goalState);
      }
   }
   return goalStates;
};

vector<vector<int>> getAllPossibleGoalStates(Board &b)
{
   vector<vector<int>> goalStates;

   for (int i = 0; i < b.getBoardSize(); i++)
   {
      if (b.getGrid()[i][b.getBoardSize() - 1] == 1 || b.getGrid()[i][b.getBoardSize() - 1] == 0)
      {
         vector<int> goalState = {i, b.getBoardSize() - 1};
         goalStates.push_back(goalState);
      }
   }
   return goalStates;
};

vector<actions> checkIfPathExists(Board &b)
{
   // startStates defines where to begin dfs -> from current point is there a path to the end
   vector<vector<int>> startStates = getStartStates(b);
   vector<vector<int>> goalStates = getGoalStates(b);
   vector<int> playerTypes = {1};
   vector<actions> solution;
   if (goalStates.size() > 0)
   {
      for (auto startState : startStates)
      {
         SearchNode *parent;
         SearchNode *startNode = new SearchNode(startState[0], startState[1], 0, parent);

         // pass board size, start node (where to begin search), crosser/blocker, goal states
         solution = depth_first_search(b, startNode, playerTypes, goalStates);
      }
   }
   return solution;
}

actor checkWin(Board &b)
{
   bool isFull = isBoardFull(b);
   if (!isFull)
   {
      vector<actions> solution = checkIfPathExists(b);
      if (solution.size() > 0)
      {
         return CROSSER;
      }
   }
   else
   {
      vector<actions> solution = checkIfPathExists(b);
      if (solution.size() > 0)
      {
         return CROSSER;
      }
      else
      {
         return BLOCKER;
      }
   }
   return NO_ONE;
};
