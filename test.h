#include"sudoku.h"
#include<array>

class Test{
   public:
   void findNull(SudokuPuzzle toCheck);
   void testAssign(std::array<int, NUM_DIGITS*NUM_DIGITS> input);
};

