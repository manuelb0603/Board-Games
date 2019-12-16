#pragma once
#include <string>

/*
Every game represents "moves" in a different way, so we don't define any member
variables for a GameMove. Instead we declare several pure virtual functions
that all Move-derived types need to implement in order to support input, output,
and comparisons.
*/
class GameMove {
public:
   /*
   Converts the GameMove to a string for output.
   */
   virtual operator std::string() const = 0;

   /*
   Compares one GameMove to another, assuming they are of the same derived type.
   */
   virtual bool operator==(const GameMove &rhs) const = 0;
};
