/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code 
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include "BlockerGame.h" // Comes with EVERYTHING

using namespace std;

enum choices
{
   HUMAN_VS_HUMAN = 1,
   HUMAN_VS_RANDOM = 2,
   RANDOM_VS_HUMAN = 3,
   HUMAN_VS_STRAIGHTLINE = 4,
   STRAIGHTLINE_VS_HUMAN = 5,
   RANDOM_VS_STRAIGHTLINE = 6,
   STRAIGHTLINE_VS_RANDOM = 7,
   SMARTCROSSERPLAYER_VS_HUMAN = 8,
   SMARTCROSSERPLAYER_VS_RANDOM = 9,
   SMARTCROSSERPLAYER_VS_STRAIGHTLINE = 10
};

int main()
{
   int boardsize;
   int option;
   Player *player1, *player2;
   cout << "--- BLOCKER GAME ---" << endl;
   cout << "1. Human vs. Human" << endl;
   cout << "2. Human vs. Random" << endl;
   cout << "3. Random vs. Human" << endl;
   cout << "4. Human vs. StraightLine" << endl;
   cout << "5. StraightLine vs. Human" << endl;
   cout << "6. Random vs. StraightLine" << endl;
   cout << "7. StraightLine vs. Random" << endl;
   cout << "8. SmartCrosserPlayer vs. Human" << endl;
   cout << "9. SmartCrosserPlayer vs. Random" << endl;
   cout << "10. SmartCrosserPlayer vs. StraightLine" << endl;
   cout << "Choose a level to run: ";
   cin >> option;

   //Cast chosen option as enum for switch
   choices choice = static_cast<choices>(option);
   switch (choice)
   {
   case HUMAN_VS_HUMAN:
      player1 = new HumanPlayer(1, "Human - Crosser");
      player2 = new HumanPlayer(-1, "Human - Blocker");
      break;
   case HUMAN_VS_RANDOM:
      player1 = new HumanPlayer(1, "Human - Crosser");
      player2 = new RandomPlayer(-1, "Random - Blocker");
      break;
   case RANDOM_VS_HUMAN:
      player1 = new RandomPlayer(1, "Random - Crosser");
      player2 = new HumanPlayer(-1, "Human - Blocker");
      break;
   case HUMAN_VS_STRAIGHTLINE:
      player1 = new HumanPlayer(1, "Human - Crosser");
      player2 = new StraightLinePlayer(-1, "StraightLine - Blocker");
      break;
   case STRAIGHTLINE_VS_HUMAN:
      player1 = new StraightLinePlayer(1, "StraightLine - Crosser");
      player2 = new HumanPlayer(-1, "Human - Blocker");
      break;
   case RANDOM_VS_STRAIGHTLINE:
      player1 = new RandomPlayer(1, "Random - Crosser");
      player2 = new StraightLinePlayer(-1, "Straightline - Blocker");
      break;
   case STRAIGHTLINE_VS_RANDOM:
      player1 = new StraightLinePlayer(1, "Straightline - Crosser");
      player2 = new RandomPlayer(-1, "Random - Blocker");
      break;
   case SMARTCROSSERPLAYER_VS_HUMAN:
      player1 = new SmartCrosserPlayer(1, "SmartCrosser - Crosser");
      player2 = new HumanPlayer(-1, "Human - Blocker");
      break;
   case SMARTCROSSERPLAYER_VS_RANDOM:
      player1 = new SmartCrosserPlayer(1, "SmartCrosser - Crosser");
      player2 = new RandomPlayer(-1, "Random - Blocker");
      break;
   case SMARTCROSSERPLAYER_VS_STRAIGHTLINE:
      player1 = new SmartCrosserPlayer(1, "SmartCrosser - Crosser");
      player2 = new StraightLinePlayer(-1, "StraightLine - Blocker");
      break;
   default:
      cout << "Invalid choice" << endl;
      break;
   };

   while (true)
   {
      cout << "Enter the size of the board (max 15x15 | min 3x3): ";
      cin >> boardsize;
      if (!cin)
      {
         reset_cin("Please enter a valid board size data type!");
         continue;
      }
      if (boardsize > 15 || boardsize < 3)
      {
         cout << "Please enter a valid board size" << endl;
      }
      else
         break;
   }
   BlockerGame game(boardsize, player1, player2);
   game.play();

   return 0;
};