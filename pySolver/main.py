from constant import *
from sudoku import *

#intentionally including types, even though python doesn't require it

def main():
    print("enter puzzle filename:")
    filename:str = input()
    inputDigits:list[int] = []
    try:
        with open(filename,"r") as puzzleFile:
            puzzleFile:io.TextIOWrapper
            ch:str = "a"
            while (ch != ""):
                ch = puzzleFile.read(1)
                if((ch >= '1') and (ch <= '9')):
                    inputDigits.append(int(ch))
                elif(ch == " "):
                    inputDigits.append(0)

            #print(len(inputDigits))
            #print(inputDigits)

    except IOError:
      print("Could not read file:", filename)

    myPuzzle:SudokuPuzzle = SudokuPuzzle(inputDigits)
    print(myPuzzle.display())
    myPuzzle.solve()
    print(myPuzzle.display())


if __name__ == "__main__":
    main()
