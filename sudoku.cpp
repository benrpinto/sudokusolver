#include"sudoku.h"
#define NUM_GROUPS 3
//3 different groups, cols, rows, and boxes
#include<iostream>
//included for debugging purposes

DigitBox::DigitBox(int input){
   set(input);
}

DigitBox::DigitBox(){
   DigitBox(0);
}

void DigitBox::set(int input){
   if(input > 0 && input <= NUM_DIGITS){
      options.fill(false);
      filled = input;
      options[filled] = true;
   }else{
      options.fill(true);
      filled = 0;
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

void DigitBox::reset(){
   set(filled);
}

GroupOfNine::GroupOfNine(){
   completed = false;
   contents.fill(NULL);
   filled.fill(false);
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
   bool toReturn = true;
   int loc = 0;
   if(!completed){
      while(loc < NUM_DIGITS && toReturn){
         toReturn = contents[loc]->get() != 0;
         loc++;
      }
      completed = toReturn;
   }
   return toReturn;
}

void GroupOfNine::check(){
   int focus;
   for (int loc = 0; loc < NUM_DIGITS; loc++){
      focus = contents[loc]->get();
      filled[focus] = true;
   }
}
void GroupOfNine::consolidate(){
   check();
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

bool GroupOfNine::validate(){
   bool toReturn = true;
   int focus;
   int loc = 0;
   bool found[NUM_DIGITS+1] = {0};
   while(loc < NUM_DIGITS && toReturn){
      focus = contents[loc]->get();
      if(focus != 0){
         toReturn = !found[focus];
         found[focus] = true;
      }
      loc++;
   }
   return toReturn;
}

void GroupOfNine::reset(){
   filled.fill(false);
   check();
   isComplete();
}

//std::ostream & operator<<(std::ostream & Str, SudokuPuzzle const & v){
//   Str << v.display();
//   return Str;
//}

std::string SudokuPuzzle::display(){
   std::string toReturn = "";
   for(int irow = 0; irow < NUM_DIGITS;irow++){
      for(int icol = 0; icol < NUM_DIGITS;icol++){
         int temp = individual[irow][icol].get();
         toReturn = toReturn + std::to_string(temp);
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

SudokuPuzzle::SudokuPuzzle(std::array<int,NUM_DIGITS*NUM_DIGITS> input){
   int counter = 0;
   int temp = 0;
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

//SudokuPuzzle::SudokuPuzzle(SudokuPuzzle &input){
//   SudokuPuzzle(input.arrayOut());
//}

std::array<int,NUM_DIGITS*NUM_DIGITS> SudokuPuzzle::arrayOut(){
   std::array<int,NUM_DIGITS*NUM_DIGITS> toReturn;
   int counter = 0;
   for(int irow = 0; irow < NUM_DIGITS; irow++){
      for(int icol = 0; icol < NUM_DIGITS; icol++){
         toReturn[counter] = individual[irow][icol].get();
      }
   }
   return toReturn;
}

void SudokuPuzzle::solve(){
   validate();
   std::array<GroupOfNine *, NUM_DIGITS*NUM_GROUPS> solveOrder;
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
   validate();
}

bool SudokuPuzzle::validate(){
   bool toReturn = true;
   int counter = 0;
   while(counter < NUM_DIGITS && toReturn){
      toReturn = rows[counter].validate();
      counter++;
   }
   counter = 0;
   while(counter < NUM_DIGITS && toReturn){
      toReturn = cols[counter].validate();
      counter++;
   }
   counter = 0;
   while(counter < NUM_DIGITS && toReturn){
      toReturn = boxes[counter/SQRT_DIG][counter%SQRT_DIG].validate();
      counter++;
   }
//   if(toReturn){
//      std::cout<<"valid puzzle\n";
//   }else{
//      std::cout<<"invalid puzzle\n";
//   }

   return toReturn;
}

void SudokuPuzzle::reset(){
   int temp = 0;
   for (int irow = 0; irow < NUM_DIGITS; irow++){
      for(int icol = 0; icol < NUM_DIGITS; icol++){
         individual[irow][icol].reset();
      }
   }
   for(int a = 0; a <NUM_DIGITS; a++){
      rows[a].reset();
      cols[a].reset();
      boxes[a/SQRT_DIG][a%SQRT_DIG].reset();
   }
   
}
