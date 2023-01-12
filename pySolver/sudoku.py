from constant import *

class SudokuPuzzle:

    def __init__(self,myInput:list):
        self.individual = []
        self.fixed = []
        if(len(myInput) != NUM_DIGITS*NUM_DIGITS):
            print("Error: malformed puzzle (",str(len(myInput)),")")
        else:
           for row in range(0,NUM_DIGITS):
                self.individual.append([])
                self.fixed.append([])
                for col in range(0,NUM_DIGITS):
                    toAppend:int = myInput[row*NUM_DIGITS + col]
                    self.individual[row].append(toAppend)
                    self.fixed[row].append(toAppend != 0)
                
    def display(self)->str:
        toReturn:str = ""
        for row in self.individual:
            for cell in row:
                cellValue:str = " " if (cell == 0) else str(cell)
                toReturn = toReturn + cellValue
            toReturn = toReturn + "\n"
        return toReturn

    def quickValidate(self, row:int, col:int)->bool:
        #check that the number is different to the other numbers in the
        #row, column, and square
        toReturn:bool = True
        if(row >= NUM_DIGITS or row < 0 or col >= NUM_DIGITS or col < 0):
            print("Internal error: cell out of bounds")
            toReturn = False
        else:
            toCheck:int = self.individual[row][col]
            sqRow:int = SQRT_DIG*(int(row/SQRT_DIG))
            sqCol:int = SQRT_DIG*(int(col/SQRT_DIG))
            counter:int = 0

            for a in range(NUM_DIGITS):
                        if(self.individual[row][a] == toCheck):
                            counter = counter + 1
                        if(self.individual[a][col] == toCheck):
                            counter = counter + 1
                        if(self.individual[a%SQRT_DIG + sqRow]\
                                [int(a/SQRT_DIG) + sqCol] == toCheck):
                            counter = counter + 1
            #there should be 3 instances, row, col, square
            #where the number matches with itself.
            toReturn = counter == 3
        return toReturn

    def solve(self):
        index:int = 0
        trying:int = 1
        direction:int = 1
        #forwards is 1 backwards is -1

        while (index >= 0 and index < NUM_DIGITS*NUM_DIGITS):
            row:int = int(index / NUM_DIGITS)
            col:int = int(index % NUM_DIGITS)
            if(self.fixed[row][col]):
                #this is a cell that was initially filled
                #so skip it
                index = index + direction
                #don't need this, as it should already be set to 1
                #trying = 1
            elif(self.individual[row][col] == NUM_DIGITS):
                #we've already tried all the numbers in this cell
                #so there must be a wrong number somewhere else
                #reverse back to previous cells
                self.individual[row][col] = 0
                direction = -1
                index = index + direction
            else:
                #try a new number
                self.individual[row][col] = self.individual[row][col] + 1
                #validate that it doesn't break rules
                if(self.quickValidate(row,col)):
                    direction = 1
                    index = index + direction
                #else the validation failed, and we go through the loop again
        if(index < 0):
            print("Error: could not solve Sudoku")
