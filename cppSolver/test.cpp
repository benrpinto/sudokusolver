#include"sudoku.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

int main(int argc, char **argv){
   vector<string> questionFiles = {
            "../test puzzles/easy01.txt",
            "../test puzzles/easy02.txt",
            "../test puzzles/tough01.txt",
            "../test puzzles/AI Escargot.txt"
   };
   vector<string> answerFiles = {
            "../test puzzles/easy01sol.txt",
            "../test puzzles/easy02sol.txt",
            "../test puzzles/tough01sol.txt",
            "../test puzzles/AI Escargotsol.txt"
   };

   int numTests = questionFiles.size();
   for(int a = 0; a < numTests;a++){
      ifstream qFile (questionFiles[a]);
      array<int, NUM_DIGITS*NUM_DIGITS> inputDigits;
      char ch = 'a';
      int counter = 0;
      if(qFile.is_open()){
         while(qFile.get(ch) && (counter < NUM_DIGITS*NUM_DIGITS)){
            if((ch >= '1') && (ch <= '9')){
               inputDigits[counter] = int(ch - '0');
              counter++;
            }else if(ch == ' '){
               inputDigits[counter] = 0;
               counter++;

            }
         }
         qFile.close();
         
         SudokuPuzzle myPuzzle = SudokuPuzzle(inputDigits);
         myPuzzle.solve();

         ifstream aFile (answerFiles[a]);
         if(aFile.is_open()){
            stringstream aText;
            aText << aFile.rdbuf();
            if(myPuzzle.display() == aText.str()){
               cout<<"Pass: "<<questionFiles[a]<<"\n";
            }else{
               cout<<"Pass: "<<questionFiles[a]<<"\n";
            }
            aFile.close();

         }else{
            cout<<"Could not read file:"<<answerFiles[a]<<"\n";

         }
      }else{
         cout<<"Could not read file:"<<questionFiles[a]<<"\n";
      }
   }
   return 0;
}
