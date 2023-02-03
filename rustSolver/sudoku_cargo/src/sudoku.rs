
const NUM_DIGITS: u8 = 9;
//const SQRT_DIG: u8 = 3;

const SIZE_DIGITS: usize = 9;

#[derive(Copy, Clone)]
pub enum Cell {
    Empty,
    Filled(u8),
    Fixed(u8),
}

pub struct SudokuPuzzle{
    individual:[[Cell;SIZE_DIGITS];SIZE_DIGITS],
    row_digits:[u16;SIZE_DIGITS],
    col_digits:[u16;SIZE_DIGITS],
    box_digits:[u16;SIZE_DIGITS],
}

impl Cell {
    pub fn display(&self)->String{
        match &self {
            Cell::Empty => String::from(" "),
            Cell::Filled(x) => x.to_string(),
            Cell::Fixed(x) => x.to_string(),
        }
    }

    pub fn new(input:u8) ->Self{
        if input == 0 {
            Cell::Empty
        }else if input <= NUM_DIGITS{
            Cell::Fixed(input)
        }else{
            Cell::Empty
        }
    }
}

impl SudokuPuzzle {

    pub fn new(input:Vec<u8>) -> Self {
        if input.len() > SIZE_DIGITS*SIZE_DIGITS{
            panic!("Too many digits");
        }else if input.len() < SIZE_DIGITS*SIZE_DIGITS{
            panic!("Too few digits");
        }
        let mut temp_individual = [[Cell::Empty as Cell;SIZE_DIGITS];SIZE_DIGITS];
        for row in 0..SIZE_DIGITS{
            for col in 0..SIZE_DIGITS{
                temp_individual[row][col] = Cell::new(input[row*SIZE_DIGITS + col]);
            }
        }




        Self{
            individual:temp_individual,
            row_digits:[9,9,9,9,9,9,9,9,9],
            col_digits:[9,9,9,9,9,9,9,9,9],
            box_digits:[9,9,9,9,9,9,9,9,9]

        }
    }


    //fn quickValidate() -> bool{
    //    false
    //}

    //fn placeDigit(){
    //
    //}

    //fn removeDigit(){
    //
    //}

    //fn solve(){
    //
    //}

    pub fn display(&self) -> String {
        let mut to_return:String = "".to_string();
        for row in self.individual{
            for dig in row{
                to_return.push_str(&dig.display());
            }
            to_return.push_str("\n");
        }
        to_return
    }
}

