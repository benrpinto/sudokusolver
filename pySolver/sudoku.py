from constant import *

class DigitBox:

    def __init__(self, myInput:int):
        self.filled = myInput

    def display(self)->str:
        return " " if (self.filled == 0) else str(self.filled)


class SudokuPuzzle:

    def __init__(self,myInput:list):
        self.individual = []
        if(len(myInput) != NUM_DIGITS*NUM_DIGITS):
            print("Error: malformed puzzle (",str(len(myInput)),")")
        else:
           for row in range(0,NUM_DIGITS):
                self.individual.append([])
                for col in range(0,NUM_DIGITS):
                    toAppend:DigitBox = DigitBox(myInput[row*NUM_DIGITS + col])
                    self.individual[row].append(toAppend)
                
    def display(self)->str:
        toReturn:str = ""
        for row in self.individual:
            for cell in row:
                toReturn = toReturn + cell.display()
            toReturn = toReturn + "\n"
        return toReturn

