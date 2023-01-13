from constant import *
from sudoku import *

def main():

    questionFiles:list[str] = [\
            "../test puzzles/easy01.txt",\
            "../test puzzles/easy02.txt",\
            "../test puzzles/tough01.txt",\
            "../test puzzles/AI Escargot.txt"\
            ]
    answerFiles:list[str] = [\
            "../test puzzles/easy01sol.txt",\
            "../test puzzles/easy02sol.txt",\
            "../test puzzles/tough01sol.txt",\
            "../test puzzles/AI Escargotsol.txt"\
            ]
    for q, a in zip (questionFiles,answerFiles):
        try:
            inputDigits:list[int] = []
            with open(q,"r") as qFile:
                puzzleFile:io.TextIOWrapper
                ch:str = "a"
                while (ch != ""):
                    ch = qFile.read(1)
                    if((ch >= '1') and (ch <= '9')):
                        inputDigits.append(int(ch))
                    elif(ch == " "):
                        inputDigits.append(0)
            try:
                answerText:str
                with open(a,"r") as aFile:
                    answerText = aFile.read()
                if(compare(inputDigits,answerText)):
                    print("Pass: ",q)
                else:
                    print("Fail: ",q)
            except IOError:
                print("Could not read file:", a)
        except IOError:
            print("Could not read file:", q)

def compare(question:list, answer:str)->bool:
    testA:SudokuPuzzle = SudokuPuzzle(question)
    testA.solve()
    return testA.display() == answer


if __name__ == "__main__":
    main()
