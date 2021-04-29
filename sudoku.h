#define NUM_DIGITS 9
//number of digits in a sudoku, so 0 doesn't count
#define SQRT_DIG 3
#define MULTIPLE_FOUND NUM_DIGITS + 5
#define NONE_FOUND NUM_DIGITS + 6

class GroupOfNine;

class DigitBox{
   public:
   short filled;
   bool options[NUM_DIGITS+1];
   //setting array size to + 1
   //so we don't have to adjust indexes when working.

   DigitBox(short input);
   DigitBox();
   void set(short input);
   short get();
   //removes an option, and checks if this digit can be solved
   short removeOption(short input);
};

class GroupOfNine{
   public:
   bool completed;
   DigitBox *contents[NUM_DIGITS];
   short filled[NUM_DIGITS+1];

   GroupOfNine();
   void set(DigitBox *input,short location);
   void consolidate();
};

class SudokuPuzzle{
   public:

   DigitBox individual[NUM_DIGITS][NUM_DIGITS];
   GroupOfNine rows[NUM_DIGITS];
   GroupOfNine cols[NUM_DIGITS];
   GroupOfNine boxes[SQRT_DIG][SQRT_DIG];

   SudokuPuzzle();
   SudokuPuzzle(short input[NUM_DIGITS*NUM_DIGITS]);
};
