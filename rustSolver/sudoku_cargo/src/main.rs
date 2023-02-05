use std::env;
use std::fs;

pub mod sudoku;

fn main() {
    let args: Vec<String> = env::args().collect();
    if (args.len() > 1) && (&args[1] == "test"){
            test();
    }
}

fn test() {
    println!("running tests");

    let question_files:Vec<&str> = vec![
            "../../test puzzles/easy01.txt",
            "../../test puzzles/easy02.txt",
            "../../test puzzles/tough01.txt",
            "../../test puzzles/AI Escargot.txt",
            ];
    let answer_files:Vec<&str> = vec![
            "../../test puzzles/easy01sol.txt",
            "../../test puzzles/easy02sol.txt",
            "../../test puzzles/tough01sol.txt",
            "../../test puzzles/AI Escargotsol.txt",
            ];

    let v:Vec<u8> = filepath_to_numbers(question_files[0].to_string());

    let my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(v);
    println!("{}",my_puzzle.display());
}


fn filepath_to_numbers(filepath: String)-> Vec<u8>{
    let mut to_return:Vec<u8> = vec![];
    let raw_contents:String = fs::read_to_string(filepath).expect("unable to read error");
    let byte_contents: &[u8] = raw_contents.as_bytes();
    for (_,&item) in byte_contents.iter().enumerate(){
        match item {
            b' ' => to_return.push(0),
            b'1'..=b'9' => to_return.push((item - b'0') as u8),
            _ =>(),
        }
    }
    to_return
}

