#include"test.h"
#include<cassert>

void Test::findNull(SudokuPuzzle toCheck){ 
   for(int a = 0; a < NUM_DIGITS; a++){
      for(int b = 0; b < NUM_DIGITS; b++){
         assert(toCheck.rows[a].contents[b] != NULL);
         assert(toCheck.cols[b].contents[a] != NULL);
      }
   }
   for(int a = 0; a < SQRT_DIG; a++){
      for(int b = 0; b < SQRT_DIG; b++){
         for(int c = 0; c < NUM_DIGITS; c++){
            assert(toCheck.boxes[a][b].contents[c]!= NULL);
         }
      }
   }
}
