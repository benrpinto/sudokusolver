#pragma once

#include"sudoku.h"
#include<array>

class DFSSolve : public SudokuPuzzle{
   private:
   int index;
   std::array<int,NUM_DIGITS*NUM_DIGITS> trying;
   std::array<std::array<bool,NUM_DIGITS>,NUM_DIGITS> fixed;

   public:
   DFSSolve();
   DFSSolve(std::array<int,NUM_DIGITS*NUM_DIGITS> input);
   //DFSSolve(SudokuPuzzle input);
   bool overlay();
   void solve();
   void reset();
};

