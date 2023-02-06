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

    let raw_v:Result<Vec<u8>,std::io::Error> = filepath_to_numbers(question_files[0].to_string());

    if let Ok(v) = raw_v {
        let my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(v);
        println!("{}",my_puzzle.display());
    }else if let Err(_) = raw_v{
        let mut error_message:String = "Could not read file:".to_string();
        error_message.push_str(&question_files[0]);
        println!("{}",&error_message);
    }
}


fn filepath_to_numbers(filepath: String)-> Result<Vec<u8>,std::io::Error>{
    let mut wrapped_return = Ok(vec![]);
    let mut to_return:Vec<u8> = vec![];
    let wrapped_contents:Result<String,std::io::Error> = fs::read_to_string(filepath);

    if let Ok(raw_contents) = wrapped_contents{
        let byte_contents: &[u8] = raw_contents.as_bytes();
        for (_,&item) in byte_contents.iter().enumerate(){
            match item {
                b' ' => to_return.push(0),
                b'1'..=b'9' => to_return.push((item - b'0') as u8),
                _ =>(),
            }
        }
        wrapped_return = Ok(to_return);
    }else if let Err(a) = wrapped_contents{
        wrapped_return = Err(a);
    }
    wrapped_return
}

