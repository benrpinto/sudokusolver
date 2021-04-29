#define NUM_DIGITS 9
//number of digits in a sudoku, so 0 doesn't count
#define SQRT_DIG 3
#define MULTIPLE_FOUND NUM_DIGITS + 5
#define NONE_FOUND NUM_DIGITS + 6

class SudokuPuzzle{
   public:
   class GroupOfNine;

   class DigitBox{
      public:
      short filled;
      bool options[NUM_DIGITS+1];
      //setting array size to + 1
      //so we don't have to adjust indexes when working.

      DigitBox(short input){
         bool empty = (input==0);
         filled = input;
         options[0] = false;
         for(short a = 1 ; a <= NUM_DIGITS; a++){
            options[a] = (empty)||(a == filled);
         }
      }
      DigitBox(){
         DigitBox(0);
      }

      void set(short input){
         bool empty = (input==0);
         filled = input;
         options[0] = false;
         for(short a = 1 ; a <= NUM_DIGITS; a++){
            options[a] = (empty)||(a == filled);
         }
      }

      short get(){
         return filled;
      }

      //removes an option, and checks if this digit can be solved
      short removeOption(short toRemove){
         short toReturn = 0;
         short tempReturn = NONE_FOUND;
         if(filled != 0){
            toReturn = filled;
         }else if(options[toRemove]){
            options[toRemove] = false;
            toReturn = NONE_FOUND;
            for(short a = 1; a <= NUM_DIGITS; a++){
               if(options[a]){
                  if(tempReturn == NONE_FOUND){
                     tempReturn = a;
                  }else{
                     tempReturn = MULTIPLE_FOUND;
                  }
               }
            }
            if(tempReturn == NONE_FOUND){
               //error, all possibilities have been eliminated
               toReturn = 0;
            }else if(0 < tempReturn && tempReturn <= NUM_DIGITS){
               filled = tempReturn;
               toReturn = filled;
            }
         }
         return toReturn;
      }
   };

   class GroupOfNine{
      public:
      bool completed;
      DigitBox *contents[NUM_DIGITS];
      short filled[NUM_DIGITS+1];

      GroupOfNine(){
         completed = false;
         for(int a = 0; a < NUM_DIGITS; a++){
            contents[a] = NULL;
            filled[a+1] = false;
         }
      }
      void set(DigitBox *input,short location){
         short focus;
         if(input != NULL && 0 <= location && location < NUM_DIGITS){
            contents[location] = input;
            focus = input->get();
            filled[focus] = true;
         }
      }
      void consolidate(){
         short focus;
         for(short dig = 1; dig <= NUM_DIGITS; dig++){
            if(filled[dig]){
               for(short loc = 0; loc < NUM_DIGITS; loc++){
                  focus = contents[loc]->removeOption(dig);
                  if(focus != 0){
                     filled[focus] = true;
                  }
               }
            }
         }
      }

   };

   DigitBox individual[NUM_DIGITS][NUM_DIGITS];
   GroupOfNine rows[NUM_DIGITS];
   GroupOfNine cols[NUM_DIGITS];
   GroupOfNine boxes[SQRT_DIG][SQRT_DIG];

      SudokuPuzzle(){
         for (int irow = 0; irow < NUM_DIGITS; irow++){
            for(int icol = 0; icol < NUM_DIGITS; icol++){
               //individual[irow][icol] is already set to 0
               rows[irow].contents[icol] = &individual[irow][icol];
               cols[icol].contents[irow] = &individual[irow][icol];
               boxes[irow/SQRT_DIG][icol/SQRT_DIG].contents[SQRT_DIG*irow%SQRT_DIG + icol%SQRT_DIG] =\
               &individual[irow][icol];
            }
         }
      }

      SudokuPuzzle(short input[NUM_DIGITS*NUM_DIGITS]){
         short counter = 0;
         if(input == NULL){
            SudokuPuzzle();
         }else{
            for (int irow = 0; irow < 9; irow++){
               for(int icol = 0; icol < 9; icol++){
                  individual[irow][icol].set(input[counter]);
                  rows[irow].contents[icol] = &individual[irow][icol];
                  cols[icol].contents[irow] = &individual[irow][icol];
                  boxes[irow/SQRT_DIG][icol/SQRT_DIG].contents[SQRT_DIG*irow%SQRT_DIG + icol%SQRT_DIG] =\
                  &individual[irow][icol];
                  counter++;
               }
            }
         }
      }
};
