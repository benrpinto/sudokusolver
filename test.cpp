#include"test.h"
#include<cassert>
#include<iostream>

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
   std::cout<<"Null check passed\n";
}

void Test::testAssign(int input[NUM_DIGITS*NUM_DIGITS]){
   int testCopy[NUM_DIGITS*NUM_DIGITS];
   int counter = 0;
   int temp = 0;
   DigitBox *focus;
   for(int a = 0; a < NUM_DIGITS*NUM_DIGITS;a++){
      assert(input[a] >= 0);
      assert(input[a] <= NUM_DIGITS);
      testCopy[a] = input[a];
   }
   SudokuPuzzle toCheck(input);

   //check that the pointers in the groups point to the same digitbox.
   for(int irow = 0; irow<NUM_DIGITS; irow++){
      for(int icol = 0; icol<NUM_DIGITS; icol++){
         focus = &toCheck.individual[irow][icol];
         assert(testCopy[counter] == focus->get());
         assert(toCheck.rows[irow].contents[icol] == focus);
         assert(toCheck.cols[icol].contents[irow] == focus);
         temp =(irow%SQRT_DIG)*SQRT_DIG + (icol%SQRT_DIG);
         assert(toCheck.boxes[irow/SQRT_DIG][icol/SQRT_DIG].contents[temp] == focus);
         counter++;
      }
   }
   std::cout<<"Assignment test passed\n";
}

