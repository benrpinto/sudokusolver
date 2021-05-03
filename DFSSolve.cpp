#include"DFSSolve.h"
#include<iostream>


DFSSolve::DFSSolve(){
   index = 0;
   trying.fill(0);
   for(int a = 0; a < NUM_DIGITS; a++){
      fixed[a].fill(false);
   }
}

DFSSolve::DFSSolve(std::array<int,NUM_DIGITS*NUM_DIGITS> input):SudokuPuzzle(input){
   index = 0;
   trying.fill(0);

   for(int irow = 0; irow < NUM_DIGITS; irow++){
      for(int icol = 0; icol < NUM_DIGITS; icol++){
         fixed[irow][icol] = individual[irow][icol].get()!= 0;
      }
   }

}

//DFSSolve::DFSSolve(SudokuPuzzle input):SudokuPuzzle(input){
//   index = 0;
//   trying.fill(0);
//
//   for(int irow = 0; irow < NUM_DIGITS; irow++){
//      for(int icol = 0; icol < NUM_DIGITS; icol++){
//         fixed[irow][icol] = individual[irow][icol].get()!= 0;
//      }
//   }
//}

bool DFSSolve::overlay(){
   reset();
   int counter = 0;
   bool toReturn = true;
   bool flag = true;
   for(int irow = 0; irow < NUM_DIGITS && flag; irow++){
      for(int icol = 0; icol < NUM_DIGITS && flag; icol++){
         if(trying[counter] == 0){
            //if we don't have a number to stick in a box
            //then there won't be any digits further along the array
            flag = false;
         }else if(!fixed[irow][icol]){
            //box isn't fixed, put the number in.
            individual[irow][icol].set(trying[counter]);
         }else if(individual[irow][icol].get() > trying[counter]){
            //if we're trying to stick a number into a fixed box
            //don't go through all the smaller numbers, just skip to the right one
            trying[counter] = individual[irow][icol].get();
         //}else if(individual[irow][icol].get() == trying[counter]){
         //already set, don't need to do anything
         }else if(individual[irow][icol].get() < trying[counter]){
            //if we've incremented a number we're trying to stick in a fixed box
            //don't go through all the larger numbers, just skip to the largest digit
            trying[counter] = NUM_DIGITS;
            toReturn = false;
            flag = false;
         }
         counter++;
      }
   }
   toReturn &= validate();
   return toReturn;
}

void DFSSolve::solve(){
   bool zeroFlag = true;
   if(NUM_DIGITS > 0){
   //you never know, someone might change NUM_DIGITS
      trying[0] = 1;
   }
   while(index >=0 && index < NUM_DIGITS*NUM_DIGITS){
      
      if(overlay()){
         index++;
         if(index < NUM_DIGITS*NUM_DIGITS){
            trying[index] = 1;
         }
      }else{
         trying[index] = trying[index] + 1;
         while(index > 0 && trying[index] > NUM_DIGITS){
            trying[index] = 0;
            index--;
            trying[index] = trying[index] + 1;
         }
         if(trying[0] > NUM_DIGITS){
            //if the first element has been incremented
            //beyond NUM_DIGITS, the puzzle is unsolvable
            index--;
         }
      }
   }
   if(index == NUM_DIGITS*NUM_DIGITS){
      std::cout<<"Puzzle solved\n";
   }else if(index < 0){
      std::cout<<"Puzzle not solved\n";
   }
}

void DFSSolve::reset(){
   for(int irow = 0; irow < NUM_DIGITS; irow++){
      for(int icol = 0; icol < NUM_DIGITS; icol++){
         if(!fixed[irow][icol]){
            individual[irow][icol].set(0);
         }
         individual[irow][icol].reset();
      }
   }
   for(int a = 0; a < NUM_DIGITS; a++){
      rows[a].reset();
      cols[a].reset();
      boxes[a/SQRT_DIG][a%SQRT_DIG].reset();
   }
}
