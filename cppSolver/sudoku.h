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

      array<unsigned short int, NUM_DIGITS> rowDigits;
      array<unsigned short int, NUM_DIGITS> colDigits;
      array<unsigned short int, NUM_DIGITS> boxDigits;

      bool quickValidate(int row, int col, int toCheck);
      void placeDigit(int row, int col, int toPlace);
      void removeDigit(int row, int col);

   public:
      SudokuPuzzle(array<int,NUM_DIGITS*NUM_DIGITS> input);
      string display();
      bool solve();
};
