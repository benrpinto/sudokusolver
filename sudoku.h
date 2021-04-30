#include<string>
#define NUM_DIGITS 9
//number of digits in a sudoku, so 0 doesn't count
#define SQRT_DIG 3
#define MULTIPLE_FOUND NUM_DIGITS + 5
#define NONE_FOUND NUM_DIGITS + 6

class GroupOfNine;

class DigitBox{
   public:
   int filled;
   bool options[NUM_DIGITS+1];
   //setting array size to + 1
   //so we don't have to adjust indexes when working.

   DigitBox(int input);
   DigitBox();
   void set(int input);
   int get();
   //removes an option, and checks if this digit can be solved
   int removeOption(int input);
};

class GroupOfNine{
   public:
   bool completed;
   DigitBox *contents[NUM_DIGITS];
   int filled[NUM_DIGITS+1];

   GroupOfNine();
   void set(DigitBox *input,int location);
   void consolidate();
   void check();
   bool isComplete();
};

class SudokuPuzzle{
   public:

   DigitBox individual[NUM_DIGITS][NUM_DIGITS];
   GroupOfNine rows[NUM_DIGITS];
   GroupOfNine cols[NUM_DIGITS];
   GroupOfNine boxes[SQRT_DIG][SQRT_DIG];

   SudokuPuzzle();
   SudokuPuzzle(int input[NUM_DIGITS*NUM_DIGITS]);
   void solve();
   void findNull();
   std::string display();
};
