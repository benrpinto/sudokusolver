# run this file using one of the below commands
# streamlit run streamlitSolver.py
# python -m streamlit run streamlitSolver.py
import streamlit as st
from sudoku import *

def main():
    #create a list containing 81 zeroes
    sudokuArray:list[int] = [0]*81
    with st.form("Sudoku Form"):
        st.write("Sudoku")
        #create 9 columns, then fill each column with text_input elements
        myCols = st.columns(9,gap=None)
        for col in range(9):
            with myCols[col]:
                for row in range(9):
                    temp = st.text_input(f"c{col}r{row}",None,1,f"c{col}r{row}",label_visibility="hidden")
                    # input accepts any text, convert to 0 if it is not a digit
                    if (temp == None) or (not temp.isdigit()):
                        temp = 0
                    else:
                        temp = int(temp)
                    sudokuArray[row*9 + col] = temp
        submitted = st.form_submit_button()

        if submitted:
            myPuzzle:SudokuPuzzle = SudokuPuzzle(sudokuArray)
            #print(myPuzzle.display())
            if(myPuzzle.solve()):
                st.text(myPuzzle.display())
                #print(myPuzzle.display())
            #print("Done")

if __name__ == "__main__":
    main()
