#include"sudoku.h"
#include<cassert>
#define NUM_GROUPS 3
//3 different groups, cols, rows, and boxes
#include<iostream>
//included for debugging purposes

DigitBox::DigitBox(int input){
   bool empty = (input==0);
   filled = input;
   options[0] = false;
   for(int a = 1 ; a <= NUM_DIGITS; a++){
      options[a] = (empty)||(a == filled);
   }
}

DigitBox::DigitBox(){
   DigitBox(0);
}

void DigitBox::set(int input){
   bool empty = (input==0);
   filled = input;
   options[0] = false;
   for(int a = 1 ; a <= NUM_DIGITS; a++){
      options[a] = (empty)||(a == filled);
   }
}

int DigitBox::get(){
   return filled;
}

int DigitBox::removeOption(int toRemove){
   int toReturn = 0;
   int tempReturn = NONE_FOUND;
   if(filled != 0){
      toReturn = filled;
   }else if(options[toRemove]){
      options[toRemove] = false;
      toReturn = NONE_FOUND;
      for(int a = 1; a <= NUM_DIGITS; a++){
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
         std::cout<<"error:all possibilities removed\n";
         toReturn = 0;
      }else if(tempReturn > 0 && tempReturn <= NUM_DIGITS){
         filled = tempReturn;
         toReturn = filled;
      }
   }
   return toReturn;
}

GroupOfNine::GroupOfNine(){
   completed = false;
   for(int a = 0; a < NUM_DIGITS; a++){
      contents[a] = NULL;
      filled[a+1] = false;
   }
}
void GroupOfNine::set(DigitBox *input,int location){
   int focus;
   if(input != NULL && 0 <= location && location < NUM_DIGITS){
      contents[location] = input;
      focus = input->get();
      filled[focus] = true;
   }
}

bool GroupOfNine::isComplete(){
   bool tempComplete = true;
   if(!completed){
      check();
      for(int loc = 0; loc <NUM_DIGITS;loc++){
         if(contents[loc]->get() == 0){
            tempComplete = false;
         }
      }
      completed = tempComplete;
   }
   return completed;
}

void GroupOfNine::check(){
   int focus;
   for (int loc = 0; loc < NUM_DIGITS; loc++){
      focus = contents[loc]->get();
      filled[focus] = true;
   }
}
void GroupOfNine::consolidate(){
   int focus = 0;
   if(!completed){
      for(int dig = 1; dig <= NUM_DIGITS; dig++){
         if(filled[dig]){
            for(int loc = 0; loc < NUM_DIGITS; loc++){
               focus = contents[loc]->removeOption(dig);
               if(focus > 0 && focus <= NUM_DIGITS){
                  filled[focus] = true;
               }
            }
         }
      }
   }
}

//std::ostream & operator<<(std::ostream & Str, SudokuPuzzle const & v){
//   Str << v.display();
//   return Str;
//}

std::string SudokuPuzzle::display(){
   std::string toReturn = "";
   for(int irow = 0; irow < NUM_DIGITS;irow++){
      for(int icol = 0; icol < NUM_DIGITS;icol++){
         if(individual[irow*NUM_DIGITS+icol] != NULL){
            int temp = individual[irow][icol].get();
            toReturn = toReturn + std::to_string(temp);
         }else{
            toReturn = toReturn + "0";
         }
      }
      toReturn = toReturn + "\n";
   }
   return toReturn;
}

SudokuPuzzle::SudokuPuzzle(){
   int temp = 0;
   for (int irow = 0; irow < NUM_DIGITS; irow++){
      for(int icol = 0; icol < NUM_DIGITS; icol++){
         //individual[irow][icol] is already set to 0
         rows[irow].set(&individual[irow][icol],icol);
         cols[icol].set(&individual[irow][icol],irow);
         temp = (irow%SQRT_DIG)*SQRT_DIG + icol%SQRT_DIG;
         boxes[irow/SQRT_DIG][icol/SQRT_DIG].set(&individual[irow][icol],temp);
      }
   }
}

SudokuPuzzle::SudokuPuzzle(int input[NUM_DIGITS*NUM_DIGITS]){
   int counter = 0;
   int temp = 0;
   if(input == NULL){
      SudokuPuzzle();
   }else{
      for (int irow = 0; irow < NUM_DIGITS; irow++){
         for(int icol = 0; icol < NUM_DIGITS; icol++){
            individual[irow][icol].set(input[counter]);
            rows[irow].set(&individual[irow][icol],icol);
            cols[icol].set(&individual[irow][icol],irow);
            temp = (irow%SQRT_DIG)*SQRT_DIG + icol%SQRT_DIG;
            boxes[irow/SQRT_DIG][icol/SQRT_DIG].set(&individual[irow][icol],temp);
            counter++;
         }
      }
   }
}

void SudokuPuzzle::solve(){
   findNull();
   GroupOfNine *solveOrder[NUM_DIGITS*NUM_GROUPS];
   int focus = 0;
   int counter = 0;
   for(int a = 0; a < NUM_DIGITS;a++){
      solveOrder[focus] = &boxes[a/SQRT_DIG][a%SQRT_DIG];
      focus++;
      solveOrder[focus] = &cols[a];
      focus++;
      solveOrder[focus] = &rows[a];
      focus++;
   }
   focus = 0;
   while(counter < NUM_DIGITS*NUM_GROUPS*1000){
      if(!solveOrder[focus]->isComplete()){
         solveOrder[focus]->consolidate();
      }
      counter++;
      focus = (focus + 1)%(NUM_DIGITS*NUM_GROUPS);
   }
}


void SudokuPuzzle::findNull(){
   for(int a = 0; a < NUM_DIGITS; a++){
      for(int b = 0; b < NUM_DIGITS; b++){
         assert(rows[a].contents[b] != NULL);
         assert(cols[b].contents[a] != NULL);
      }
   }
   for(int a = 0; a < SQRT_DIG; a++){
      for(int b = 0; b < SQRT_DIG; b++){
         for(int c = 0; c < NUM_DIGITS; c++){
            assert(boxes[a][b].contents[c]!= NULL);
         }
      }
   }
}
