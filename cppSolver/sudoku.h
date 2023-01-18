#pragma once
#include<string>
#include<array>

using namespace std;

constexpr int NUM_DIGITS = 9;
constexpr int SQRT_DIG = 3;

class SudokuPuzzle{
   protected:
      array<array<int,NUM_DIGITS>,NUM_DIGITS> individual;
      array<array<bool,NUM_DIGITS>,NUM_DIGITS> fixedCell;
   public:
      SudokuPuzzle(array<int,NUM_DIGITS*NUM_DIGITS> input);
      string display();
      bool quickValidate(int row, int col);
      void solve();
};
