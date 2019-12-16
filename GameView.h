#pragma once 
#include "GameBoard.h"
#include <iostream>

class GameView {
private:
   /*
   Prints the View's member GameBoard to the ostream parameter.
   */
   virtual void PrintBoard(std::ostream &s) const = 0;


public:
   /*
   Helper method for doing operator<< on derived GameView types. This method
   will be called any time you use << to output a GameView object; the 
   operator will in turn call the virtual PrintBoard method to support derived-class
   output.
   */
   friend std::ostream& operator<< (std::ostream &os, const GameView &v) {
      v.PrintBoard(os);
      return os;
   }

   /*
   Converts a string representation of a move into a GameMove object appropriate
   to the derived game type. 
   */
   virtual std::unique_ptr<GameMove> ParseMove(const std::string &move) const = 0;

   /*
   Returns a string used to describe the given player number (1 or 2) for the derived
   game type.
   */
   virtual std::string GetPlayerString(int player) const = 0;
};
