#include<iostream>
#include<fstream>
#include<string>
#include"sudoku.h"

using namespace std;

int main(int argc, char** argv){
   SudokuPuzzle myPuzzle;

   string filename;
   FILE* puzzleFile;
   getline(cin,filename);

   //extract the puzzle from the file
   puzzleFile = fopen(filename.c_str(),"r");
   if(!puzzleFile){
      cout<<"file not found\n";
   }else{
      char ch;
      int digit;
      for(int row = 0; row < 9; row++){
         for(int col = 0; col < 9; col++){
            ch = getc(puzzleFile);
            if(ch >= '1' && ch <= '9'){
               digit = ch - '0';
            }else{
               digit = 0;
            }
            cout<<digit;
         }
         //read and throw out the newline
         getc(puzzleFile);
         cout<<"\n";
      }
   }

   fclose(puzzleFile);
   return 0;
}
