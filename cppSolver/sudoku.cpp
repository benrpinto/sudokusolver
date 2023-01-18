#include<array>
#include<string>
#include<cstring>
#include<iostream>
#include"sudoku.h"

using namespace std;

SudokuPuzzle::SudokuPuzzle(array<int,NUM_DIGITS*NUM_DIGITS> input){
   for(int a = 0; a < NUM_DIGITS;a++){
         memcpy(&individual[a][0],&input[a*NUM_DIGITS],sizeof(individual[a]));
   }

   for(int row = 0; row < NUM_DIGITS; row++){
      for(int col = 0; col < NUM_DIGITS; col++){
         fixedCell[row][col] = individual[row][col] != 0;
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

bool SudokuPuzzle::quickValidate(int row, int col){
   bool toReturn = true;
   int toCheck;
   int sqRow;
   int sqCol;
   int counter = 0;
   if(row >= NUM_DIGITS || row < 0 || col >= NUM_DIGITS || col < 0){
      cout<<"Internal error: cell out of bounds\n";
      toReturn = false;
   }else{
      toCheck = individual[row][col];
      sqRow = SQRT_DIG*(int(row/SQRT_DIG));
      sqCol = SQRT_DIG*(int(col/SQRT_DIG));

      for (int a = 0; a < NUM_DIGITS; a++){
         if(individual[row][a] == toCheck){
            counter++;
         }
         if(individual[a][col] == toCheck){
            counter++;
         }
         if(individual[a%SQRT_DIG +sqRow][int(a/SQRT_DIG) + sqCol] == toCheck){
            counter++;
         }
      }
      toReturn = counter == 3;
   }
   return toReturn;
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
      }else if(individual[row][col] == NUM_DIGITS){
         //we've already tried all the numbers in this cell
         //so there must be a wrong number somewhere else
         //reverse back to previous cells
         individual[row][col] = 0;
         direction = -1;
         index += direction;
      }else{
         individual[row][col] = individual[row][col] + 1;
         if(quickValidate(row,col)){
            direction = 1;
            index += direction;
         }
      }
   }
   if(index < 0){
      cout<<"Error: could not solve Sudoku\n";
   }
}
