from constant import *
from sudoku import *

def main():

    questionFiles:list[str] = [\
            "../test puzzles/easy01.txt",\
            "../test puzzles/easy02.txt",\
            "../test puzzles/tough01.txt",\
            "../test puzzles/AI Escargot.txt",\
            "../test puzzles/malformed01.txt"\
            ]
    answerFiles:list[str] = [\
            "../test puzzles/easy01sol.txt",\
            "../test puzzles/easy02sol.txt",\
            "../test puzzles/tough01sol.txt",\
            "../test puzzles/AI Escargotsol.txt",\
            "../test puzzles/unsol.txt"\
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
    qText:str
    testA:SudokuPuzzle = SudokuPuzzle(question)
    if(testA.solve()):
        qText = testA.display()
    else:
        qText = "Error: could not solve Sudoku\n"

    return qText == answer


if __name__ == "__main__":
    main()
