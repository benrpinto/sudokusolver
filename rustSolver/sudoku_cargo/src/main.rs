use std::env;
use std::fs;
use std::io;

pub mod sudoku;

fn main() {
    let args: Vec<String> = env::args().collect();
    if (args.len() > 1) && (&args[1] == "test"){
        test();
    }else{
        user();
    }
}

fn user(){
    println!("enter puzzle filename:");
    let mut filename:String = String::new();
    io::stdin().read_line(&mut filename).expect("Failed to read line");
    filename.truncate(filename.len() - 1);


    if let Ok(input_digits) = filepath_to_numbers(filename.to_string()){
        let my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(input_digits);
        println!("{}",my_puzzle.display());
        if let Some(result) = my_puzzle.solve(){
            println!("{}",result.display());
        }else{
            println!("Error: could not solve Sudoku");
        }
    }else{
        println!("Could not read file:{}",&filename);
    }
}

fn test() {
    println!("running tests");

    let question_files:Vec<&str> = vec![
            "../../test puzzles/easy01.txt",
            "../../test puzzles/easy02.txt",
            "../../test puzzles/tough01.txt",
            "../../test puzzles/AI Escargot.txt",
            "../../test puzzles/malformed01.txt",
            ];
    let answer_files:Vec<&str> = vec![
            "../../test puzzles/easy01sol.txt",
            "../../test puzzles/easy02sol.txt",
            "../../test puzzles/tough01sol.txt",
            "../../test puzzles/AI Escargotsol.txt",
            "../../test puzzles/unsol.txt",
            ];

    let num_tests:usize = question_files.len();
    for a in 0..=(num_tests - 1){
        if let Ok(input_digits) = filepath_to_numbers(question_files[a].to_string()) {
            let my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(input_digits);
            let q_text:String;
            if let Some(result) = my_puzzle.solve(){
                q_text = result.display();
            }else{
                q_text = "Error: could not solve Sudoku\n".to_string();
            }

            match fs::read_to_string(answer_files[a].to_string()) {
                Ok(a_text) =>{
                    if q_text == a_text{
                        println!("Pass: {}",&question_files[a]);
                    }else{
                        println!("Fail: {}",&question_files[a]);
                        println!("Expected:\n{}",&a_text);
                        println!("Received:\n{}",&q_text);
                    }
                },
                Err(_) => println!("Could not read file:{}",&answer_files[a]),
            }
        }else{
            println!("Could not read file:{}",&question_files[a]);
        }
    }
}


fn filepath_to_numbers(filepath: String)-> Result<Vec<u8>,std::io::Error>{
    let wrapped_contents:Result<String,std::io::Error> = fs::read_to_string(filepath);

    match wrapped_contents {
        Ok(raw_contents) =>{
            let byte_contents: &[u8] = raw_contents.as_bytes();
            Ok(byte_contents.iter().fold(vec![],| mut my_output: Vec<u8>, &item|{
                match item {
                    b' ' => my_output.push(0),
                    b'1'..=b'9' => my_output.push((item - b'0') as u8),
                    _ =>(),
                };
                my_output
            }))
        },
        Err(a) => Err(a),
    }
}
