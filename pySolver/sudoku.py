from constant import *

class SudokuPuzzle:

    def __init__(self,myInput:list):
        self.individual = []
        self.fixedCell  = []

        self.rowDigits = [0]*NUM_DIGITS
        self.colDigits = [0]*NUM_DIGITS
        self.boxDigits = [0]*NUM_DIGITS

        if len(myInput) != NUM_DIGITS*NUM_DIGITS :
            print("Error: malformed puzzle (",str(len(myInput)),")")
        else:
           for row in range(0,NUM_DIGITS):
                self.individual.append([])
                self.fixedCell.append([])
                for col in range(0,NUM_DIGITS):
                    toAppend:int = myInput[row*NUM_DIGITS + col]
                    digitFlag:int = 0
                    if toAppend != 0 :
                        digitFlag:int  = 1<<(toAppend -1)
                    box:int = int(col/SQRT_DIG) + SQRT_DIG * int(row/SQRT_DIG)
                    self.individual[row].append(toAppend)
                    self.fixedCell[row].append(toAppend != 0)
                    self.rowDigits[row] = self.rowDigits[row] | digitFlag
                    self.colDigits[col] = self.colDigits[col] | digitFlag
                    self.boxDigits[box] = self.boxDigits[box] | digitFlag
                
    def display(self)->str:
        toReturn:str = ""
        for row in self.individual:
            for cell in row:
                cellValue:str = " " if (cell == 0) else str(cell)
                toReturn = toReturn + cellValue
            toReturn = toReturn + "\n"
        return toReturn

    def quickValidate(self, row:int, col:int, toCheck:int)->bool:
        #check that the number is different to the other numbers in the
        #row, column, and square
        toReturn:bool = True
        if row >= NUM_DIGITS or row < 0 or col >= NUM_DIGITS or col < 0 :
            print("Internal error: validating cell out of bounds")
            toReturn = False
        elif toCheck > NUM_DIGITS or toCheck <= 0 :
            print("Internal error: validating invalid digit")
            toReturn = False
        else:
            box:int = int(col/SQRT_DIG) + SQRT_DIG * int(row/SQRT_DIG)
            digitFlag:int = 1 << (toCheck-1)
            toReturn = toReturn and ((digitFlag & self.rowDigits[row]) == 0)
            toReturn = toReturn and ((digitFlag & self.colDigits[col]) == 0)
            toReturn = toReturn and ((digitFlag & self.boxDigits[box]) == 0)

        return toReturn

    def placeDigit(self, row:int, col:int, toPlace:int):
        if row >= NUM_DIGITS or row < 0 or col >= NUM_DIGITS or col < 0 :
            print("Internal error: placing cell out of bounds")
        elif self.fixedCell[row][col] :
            print("Internal error: placing in fixed cell")
        elif toPlace <= 0 or toPlace > NUM_DIGITS :
            print("Error: placing invalid digit")
        elif self.individual[row][col] != 0 :
            print("Error: placing in occupied cell")
        else:
            box:int = int(col/SQRT_DIG) + SQRT_DIG * int(row/SQRT_DIG)
            digitFlag:int = 1 << (toPlace-1)

            self.individual[row][col] = toPlace
            self.rowDigits[row] ^= digitFlag
            self.colDigits[col] ^= digitFlag
            self.boxDigits[box] ^= digitFlag


    def removeDigit(self, row:int, col:int):
        if row >= NUM_DIGITS or row < 0 or col >= NUM_DIGITS or col < 0 :
            print("Internal error: clearing cell out of bounds")
        elif self.fixedCell[row][col] :
            print("Internal error: attempting to clear fixed cell")
        elif self.individual[row][col] < 0 or self.individual[row][col] > NUM_DIGITS :
            print("Error: cell has invalid digit")
        elif self.individual[row][col] == 0 :
            print("Error: cell is already clear")
        else:
            box:int = int(col/SQRT_DIG) + SQRT_DIG * int(row/SQRT_DIG)
            digitFlag:int = 1 << (self.individual[row][col]-1)

            self.individual[row][col] = 0
            self.rowDigits[row] ^= digitFlag
            self.colDigits[col] ^= digitFlag
            self.boxDigits[box] ^= digitFlag


    def solve(self) -> bool:
        index:int = 0 
        direction:int = 1
        #forwards is 1 backwards is -1

        while index >= 0 and index < NUM_DIGITS*NUM_DIGITS :
            row:int = int(index / NUM_DIGITS)
            col:int = index % NUM_DIGITS
            if self.fixedCell[row][col] :
                #this is a cell that was initially filled
                #so skip it
                index = index + direction
            else:
                toCheck:int = self.individual[row][col]
                foundValidDigit:bool = False

                if self.individual[row][col] != 0 :
                    self.removeDigit(row,col)

                while(toCheck < NUM_DIGITS) and (not foundValidDigit):
                    toCheck = toCheck + 1
                    foundValidDigit = self.quickValidate(row,col,toCheck)

                #if we find a valid digit, move forward and try to find more
                #if we run out of digits first, a previous cell must be incorrect
                if foundValidDigit :
                    self.placeDigit(row, col, toCheck)
                    direction = 1
                else:
                    direction = -1
                index = index + direction
        return index >= 0
