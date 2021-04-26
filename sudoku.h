
class SudokuPuzzle{
   public:
   class GroupOfNine;
   class DigitBox{
      public:
      short filled;
      bool options[9];
      GroupOfNine *row;
      GroupOfNine *col;
      GroupOfNine *box;
   };

   class GroupOfNine{
      public:
      bool contains[9];
      DigitBox *contents[9];
   };

   DigitBox individual[9][9];
   GroupOfNine rows[9];
   GroupOfNine cols[9];
   GroupOfNine boxes[3][3];

      SudokuPuzzle(){
         for (int irow = 0; irow < 9; irow++){
            for(int icol = 0; icol < 9; icol++){
               individual[irow][icol].filled = 0;
               individual[irow][icol].row = &rows[irow];
               individual[irow][icol].col = &cols[icol];
               individual[irow][icol].col = &boxes[irow/3][icol/3];
               rows[irow].contents[icol] = &individual[irow][icol];
               cols[icol].contents[irow] = &individual[irow][icol];
               boxes[irow/3][icol/3].contents[3*irow%3 + icol%3] = &individual[irow][icol];
            }
         }
      }

};
