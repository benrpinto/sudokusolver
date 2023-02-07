#include<iostream>
#include<fstream>
#include<string>
#include"sudoku.h"

using namespace std;

int main(int argc, char **argv){
   string filename;
   char ch = 'a';
   int counter = 0;
   array<int, NUM_DIGITS*NUM_DIGITS> inputDigits;

   cout<<"enter puzzle filename:\n";
   getline(cin,filename);
   ifstream puzzleFile (filename);

   if(puzzleFile.is_open()){
      while(puzzleFile.get(ch) && (counter < NUM_DIGITS*NUM_DIGITS)){
         if((ch >= '1') && (ch <= '9')){
            inputDigits[counter] = int(ch - '0');
            counter++;
         }else if(ch == ' '){
            inputDigits[counter] = 0;
            counter++;
         }
      }
      puzzleFile.close();

      SudokuPuzzle myPuzzle = SudokuPuzzle(inputDigits);
      cout << myPuzzle.display()<<"\n";
      if(myPuzzle.solve()){
         cout<< myPuzzle.display()<<"\n";
      }else{
         cout<<"Error: could not solve Sudoku\n";
      }
   }else{
      cout<<"Could not read file:"<<filename<<"\n";
   }
}
