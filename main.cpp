#include<iostream>
#include<fstream>
#include<string>
#include"sudoku.cpp"

using namespace std;

int main(int argc, char** argv){
   short inputDigits[NUM_DIGITS*NUM_DIGITS];
   int counter = 0;
   string filename;
   FILE* puzzleFile;
   getline(cin,filename);

   //extract the puzzle from the file
   puzzleFile = fopen(filename.c_str(),"r");
   if(!puzzleFile){
      cout<<"file not found\n";
   }else{
      char ch;
      short digit;
      for(int row = 0; row < 9; row++){
         for(int col = 0; col < 9; col++){
            ch = getc(puzzleFile);
            if(ch >= '1' && ch <= '9'){
               digit = ch - '0';
            }else{
               digit = 0;
            }
            inputDigits[counter] = digit;
            counter++;
            cout<<digit;
         }
         //read and throw out the newline
         getc(puzzleFile);
         cout<<"\n";
      }
      //don't keep the file open longer than needed.
      fclose(puzzleFile);

      SudokuPuzzle myPuzzle(inputDigits);
   }

   return 0;
}
