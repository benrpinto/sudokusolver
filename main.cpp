#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include"sudoku.h"
#include"test.h"

#define RUNTESTS true

using namespace std;



int main(int argc, char** argv){
   std::array<int, NUM_DIGITS*NUM_DIGITS> inputDigits;
   int counter = 0;
   string filename;
   FILE* puzzleFile;

   std::cout<<"enter puzzle filename:\n";
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
            inputDigits[counter] = digit;
            counter++;
            //cout<<digit;
         }
         //read and throw out the newline
         getc(puzzleFile);
         //cout<<"\n";
      }
      //don't keep the file open longer than needed.
      fclose(puzzleFile);

      if(RUNTESTS){
         cout<<"running tests\n";
         Test myTest;
         SudokuPuzzle testPuzzle(inputDigits);
         myTest.findNull(testPuzzle);
         myTest.testAssign(inputDigits);
         cout<<"All tests passed! :D\n";
      }

      SudokuPuzzle myPuzzle(inputDigits);
      cout<<"initialised\n";
      cout<<myPuzzle.display();
      cout<<"solving\n";
      myPuzzle.solve();
      cout<<"solved\n";
      cout<<myPuzzle.display();
   }
   return 0;
}
