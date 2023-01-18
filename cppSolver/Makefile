.PHONY: all
all: sudoku.out test.out

sudoku.out: main.cpp sudoku.cpp sudoku.h
	g++ -Wall -Werror main.cpp sudoku.cpp -o sudoku.out

test.out: test.cpp sudoku.cpp sudoku.h
	g++ -Wall -Werror test.cpp sudoku.cpp -o test.out

