use std::env;

pub mod sudoku;

fn main() {
    let args: Vec<String> = env::args().collect();
    if (args.len() > 1) && (&args[1] == "test"){
            test();
    }
}

fn test() {
    println!("running tests");

    let my_var : sudoku::Cell = sudoku::Cell::Filled(5);
    println!("{}",my_var.display());
    let v:Vec<u8> = vec![
    1,2,3,4,5,6,7,8,9,
    7,8,9,1,2,3,4,5,6,
    4,5,6,7,8,9,1,2,3,
    2,3,4,5,6,7,8,9,1,
    8,9,1,2,3,4,5,6,7,
    5,6,7,8,9,1,2,3,4,
    3,4,5,6,7,8,9,1,2,
    9,1,2,3,4,5,6,7,8,
    6,7,8,9,1,2,3,4,5,
    ];
    let my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(v);
    println!("{}",my_puzzle.display());

    

    
}
