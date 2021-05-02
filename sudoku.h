#pragma once
#include<string>
#include<array>
#define NUM_DIGITS 9
//number of digits in a sudoku, so 0 doesn't count
#define SQRT_DIG 3
#define MULTIPLE_FOUND NUM_DIGITS + 5
#define NONE_FOUND NUM_DIGITS + 6

class DigitBox;
class GroupOfNine;
class SudokuPuzzle;

class DigitBox{
   private:
   int filled;
   std::array<bool, NUM_DIGITS+1> options;
   //setting array size to + 1
   //so we don't have to adjust indexes when working.
   public:
   friend class Test;
   DigitBox(int input);
   DigitBox();
   void set(int input);
   int get();
   //removes an option, and checks if this digit can be solved
   int removeOption(int input);
};

class GroupOfNine{
   private:
   bool completed;
   std::array<DigitBox *, NUM_DIGITS> contents;
   std::array<int, NUM_DIGITS+1> filled;
   void check();
   public:
   friend class Test;
   GroupOfNine();
   void set(DigitBox *input,int location);
   void consolidate();
   bool isComplete();
   bool validate();
};

class SudokuPuzzle{
   private:
   std::array<std::array<DigitBox, NUM_DIGITS>, NUM_DIGITS> individual;
   std::array<GroupOfNine, NUM_DIGITS> rows;
   std::array<GroupOfNine, NUM_DIGITS> cols;
   std::array<std::array<GroupOfNine, SQRT_DIG>, SQRT_DIG> boxes;

   public:
   friend class Test;
   SudokuPuzzle();
   SudokuPuzzle(std::array<int,NUM_DIGITS*NUM_DIGITS> input);
   void solve();
   std::string display();
   bool validate();
};

