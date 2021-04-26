class GroupOfNine;

class DigitBox{
      short Filled = 0;
      bool options[9];
      GroupOfNine *row;
      GroupOfNine *col;
      GroupOfNine *box;
};

class GroupOfNine{
   bool contains[9];
   DigitBox contents;
};
