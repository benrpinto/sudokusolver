#include<array>
#include<string>
#include<cstring>
#include<iostream>
#include"sudoku.h"

using namespace std;

SudokuPuzzle::SudokuPuzzle(array<int,NUM_DIGITS*NUM_DIGITS> input){
   for(int a = 0; a < NUM_DIGITS;a++){
         memcpy(&individual[a][0],&input[a*NUM_DIGITS],sizeof(individual[a]));
         rowDigits[a] = 0;
         colDigits[a] = 0;
         boxDigits[a] = 0;
   }

   unsigned short int digitFlag = 0;
   for(int row = 0; row < NUM_DIGITS; row++){
      for(int col = 0; col < NUM_DIGITS; col++){
         if( individual[row][col] != 0){
            fixedCell[row][col] = true;
            digitFlag = 1 << (individual[row][col]-1);
            rowDigits[row] |= digitFlag;
            colDigits[col] |= digitFlag;
            boxDigits[(int(col/SQRT_DIG)) + SQRT_DIG*(int(row/SQRT_DIG))] |= digitFlag;
         }else{
            fixedCell[row][col] = false;       
         }
      }
   }
}

string SudokuPuzzle::display(){
   string toReturn = "";
   for(auto&& row : individual){
      for(auto&& cell : row){
         toReturn += cell == 0? " ": to_string(cell);
      }
      toReturn += "\n";
   }
   return toReturn;
}

bool SudokuPuzzle::quickValidate(int row, int col, int toCheck){
   bool toReturn = true;
   if(   row >= NUM_DIGITS || row < 0 ||
         col >= NUM_DIGITS || col < 0 ||
         toCheck > NUM_DIGITS || toCheck <= 0){
      if(toCheck > NUM_DIGITS || toCheck <= 0){
         cout << "Internal error: validating invalid digit\n";
      }else{
         cout<<"Internal error: validating cell out of bounds\n";
      }
      toReturn = false;
   }else{
      int box = (int(col/SQRT_DIG)) + SQRT_DIG*(int(row/SQRT_DIG));
      unsigned short int digitFlag = 1 << (individual[row][col]-1);
      toReturn = toReturn && not(digitFlag & rowDigits[row]);
      toReturn = toReturn && not(digitFlag & colDigits[col]);
      toReturn = toReturn && not(digitFlag & boxDigits[box]);
   }
   return toReturn;
}

void SudokuPuzzle::placeDigit(int row, int col, int toPlace){
   if(   row >= NUM_DIGITS || row < 0 ||
         col >= NUM_DIGITS || col < 0 ){
      cout<<"Internal error: placing cell out of bounds\n";
   }else if(fixedCell[row][col]){
      cout<<"Internal error: placing in fixed cell\n";
   }else if(toPlace < 0 || toPlace > NUM_DIGITS){
      cout<<"Error: placing invalid digit\n";
   }else if(individual[row][col] != 0){
      cout<<"Error: placing in occupied cell\n";
   }else{
      int box = (int(col/SQRT_DIG)) + SQRT_DIG*(int(row/SQRT_DIG));
      unsigned short int digitFlag = 1 << (individual[row][col]-1);
      individual[row][col] = toPlace;
      rowDigits[row] ^= digitFlag;
      colDigits[col] ^= digitFlag;
      boxDigits[box] ^= digitFlag;
   }
}

void SudokuPuzzle::removeDigit(int row, int col){
   if(   row >= NUM_DIGITS || row < 0 ||
         col >= NUM_DIGITS || col < 0 ){
      cout<<"Internal error: clearing cell out of bounds\n";
   }else if(fixedCell[row][col]){
      cout<<"Internal error: attempting to clear fixed cell\n";
   }else if(individual[row][col] < 0 || individual[row][col] > NUM_DIGITS){
      cout<<"Error: cell has invalid digit\n";
   }else{
      int box = (int(col/SQRT_DIG)) + SQRT_DIG*(int(row/SQRT_DIG));
      unsigned short int digitFlag = 1 << (individual[row][col]-1);
      individual[row][col] = 0;
      rowDigits[row] ^= digitFlag;
      colDigits[col] ^= digitFlag;
      boxDigits[box] ^= digitFlag;
   }
}

void SudokuPuzzle::solve(){
   int index = 0;
   int direction = 1;
   //forwards is 1 backwards is -1
   
   while(index >= 0 && index < NUM_DIGITS*NUM_DIGITS){
      int row = int(index/NUM_DIGITS);
      int col = int(index % NUM_DIGITS);
      if(fixedCell[row][col]){
         //cell that was initially filled, so not editable
         //skip it.
         index += direction;
      }else{
         int toCheck = individual[row][col];
         bool foundValidDigit = false;

         if(individual[row][col] != 0){
            removeDigit(row,col);
         }

         while ((toCheck < NUM_DIGITS) && ( not foundValidDigit)){
            toCheck += 1;
            foundValidDigit = quickValidate(row,col,toCheck);
         }

         //if we find a valid digit, move forward and try to find more
         //if we run out of digits first, a previous cell must be incorrect
         if(foundValidDigit){
            placeDigit(row,col,toCheck);
            direction = 1;
            index += direction;
         }else{
            direction = -1;
            index -= direction;
         }
      }
   }
   if(index < 0){
      cout<<"Error: could not solve Sudoku\n";
   }
}
