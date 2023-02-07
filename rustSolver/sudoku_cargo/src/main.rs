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
    let mut filename:String = "".to_string();
    io::stdin().read_line(&mut filename).expect("Failed to read line");
    filename.truncate(filename.len() - 1);

    let raw_q_in:Result<Vec<u8>,std::io::Error> = filepath_to_numbers(filename.to_string());

    if let Ok(input_digits) = raw_q_in {
        let mut my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(input_digits);
        println!("{}",my_puzzle.display());
        my_puzzle = my_puzzle.solve();
        println!("{}",my_puzzle.display());

    }else if let Err(_) = raw_q_in{
        let mut error_message:String = "Could not read file:".to_string();
        error_message.push_str(&filename);
        println!("{}",&error_message);
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

    let num_tests:usize = question_files.len();
    for a in 0..=(num_tests - 1){
        let raw_q_in:Result<Vec<u8>,std::io::Error> = filepath_to_numbers(question_files[a].to_string());

        if let Ok(input_digits) = raw_q_in {
            let mut my_puzzle:sudoku::SudokuPuzzle = sudoku::SudokuPuzzle::new(input_digits);
            my_puzzle = my_puzzle.solve();
            let q_text:String = my_puzzle.display();

            let wrapped_answer:Result<String,std::io::Error> = fs::read_to_string(answer_files[a].to_string());
            if let Ok(a_text) = wrapped_answer{
                if q_text == a_text{
                    println!("Pass: {}",&question_files[a]);
                }else{
                    println!("Fail: {}",&question_files[a]);
                }
            }else if let Err(_) = wrapped_answer{
                let mut error_message:String = "Could not read file:".to_string();
                error_message.push_str(&answer_files[a]);
                println!("{}",&error_message);
            }
        }else if let Err(_) = raw_q_in{
            let mut error_message:String = "Could not read file:".to_string();
            error_message.push_str(&question_files[a]);
            println!("{}",&error_message);
        }
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
