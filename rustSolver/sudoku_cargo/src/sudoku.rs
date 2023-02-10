
const NUM_DIGITS: u8 = 9;

const SIZE_DIGITS: usize = 9;
const SIZE_SQRT_DIG: usize = 3;

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
            panic!("Error: invalid digit");
        }
    }
    pub fn alter(self, input:u8) ->Self{
        if input == 0 {
            Cell::Empty
        }else if input <= NUM_DIGITS{
            Cell::Filled(input)
        }else{
            panic!("Error: invalid digit");
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
        let mut temp_row_digits = [0 as u16;SIZE_DIGITS];
        let mut temp_col_digits = [0 as u16;SIZE_DIGITS];
        let mut temp_box_digits = [0 as u16;SIZE_DIGITS];

        for row in 0..SIZE_DIGITS{
            for col in 0..SIZE_DIGITS{
                temp_individual[row][col] = Cell::new(input[row*SIZE_DIGITS + col]);
                if let Cell::Fixed(digit) = temp_individual[row][col]{

                    let my_box:usize = (col/SIZE_SQRT_DIG) as usize 
                        + SIZE_SQRT_DIG*((row/SIZE_SQRT_DIG)as usize);
                    let digit_flag:u16 = 1 << (digit -1);

                    temp_row_digits[row] |= digit_flag;
                    temp_col_digits[col] |= digit_flag;
                    temp_box_digits[my_box] |= digit_flag;

                }
            }
        }

        Self{
            individual:temp_individual,
            row_digits:temp_row_digits,
            col_digits:temp_col_digits,
            box_digits:temp_box_digits

        }
    }


    fn quick_validate(&self, row:usize,col:usize,to_check:u8) -> bool {
        let mut to_return:bool = true;
        if row > SIZE_DIGITS||col > SIZE_DIGITS {
            panic!("Internal error: validating cell out of bounds");
        }else if to_check > NUM_DIGITS || to_check == 0{
            panic!("Internal error: validating invalid digit");
        }

        let my_box:usize = (col/SIZE_SQRT_DIG) as usize 
            + SIZE_SQRT_DIG*((row/SIZE_SQRT_DIG)as usize);
        let digit_flag:u16 = 1 << (to_check -1);

        to_return = to_return && ((self.row_digits[row] & digit_flag) == 0);
        to_return = to_return && ((self.col_digits[col] & digit_flag) == 0);
        to_return = to_return && ((self.box_digits[my_box] & digit_flag) == 0);


        to_return
    }


    fn place_digit(mut self, row:usize, col:usize, to_place:u8)->Self {
        if row > SIZE_DIGITS || col > SIZE_DIGITS{
            panic!("Internal error: placing cell out of bounds\n");
        }
        match self.individual[row][col] {
            Cell::Empty => {
                if to_place > NUM_DIGITS || to_place == 0 {
                    panic!("Error: placing invalid digit");
                }
            
                let my_box:usize = (col/SIZE_SQRT_DIG) as usize 
                    + SIZE_SQRT_DIG*((row/SIZE_SQRT_DIG)as usize);
                let digit_flag:u16 = 1 << (to_place -1);

                self.individual[row][col] = self.individual[row][col].alter(to_place);
                self.row_digits[row] ^= digit_flag;
                self.col_digits[col] ^= digit_flag;
                self.box_digits[my_box] ^= digit_flag
            }
            Cell::Filled(_) => println!("Error: placing in occupied cell"),
            Cell::Fixed(_) => panic!("Internal Error: placing in fixed cell"),
        }
        self
    }

    fn remove_digit(mut self, row:usize, col:usize)->Self {
        if row > SIZE_DIGITS || col > SIZE_DIGITS{
            panic!("Internal error: clearing cell out of bounds\n");
        }
        match self.individual[row][col] {
            Cell::Filled(digit) => {
                if digit > NUM_DIGITS || digit == 0 {
                    panic!("Error: cell has invalid digit");
                }
            
                let my_box:usize = (col/SIZE_SQRT_DIG) as usize 
                    + SIZE_SQRT_DIG*((row/SIZE_SQRT_DIG)as usize);
                let digit_flag:u16 = 1 << (digit -1);

                self.individual[row][col] = self.individual[row][col].alter(0);
                self.row_digits[row] ^= digit_flag;
                self.col_digits[col] ^= digit_flag;
                self.box_digits[my_box] ^= digit_flag
            }
            Cell::Empty => println!("Error: cell is already clear"),
            Cell::Fixed(_) => panic!("Internal Error: attempting to clear fixed cell"),
        }
        self
    }

    pub fn solve(mut self) -> Option<Self> {
        let mut index:isize = 0;
        let mut direction:isize = 1;
        let max_size:isize = (SIZE_DIGITS*SIZE_DIGITS).try_into().unwrap();

        while index >= 0 && index < max_size {
            let row:usize = index.unsigned_abs()/SIZE_DIGITS;
            let col:usize = index.unsigned_abs()%SIZE_DIGITS;
            if let Cell::Fixed(_) = self.individual[row][col]{
                index += direction;
            }else{
                let mut to_check:u8 = 0;
                let mut found_valid_digit:bool = false;
                if let Cell::Filled(digit) = self.individual[row][col]{
                    to_check = digit;
                    self = self.remove_digit(row,col);
                }
                while(to_check < NUM_DIGITS) && (!found_valid_digit){
                    to_check += 1;
                    found_valid_digit = self.quick_validate(row,col,to_check);
                }
                if found_valid_digit {
                    self = self.place_digit(row,col,to_check);
                    direction = 1;
                }else{
                    direction = -1;
                }
                index += direction;
            }
        }
        if index < 0 {
            None
        }else{
            Some(self)
        }
    }

    pub fn _imperative_display(&self) -> String {
        let mut to_return:String = "".to_string();
        for row in self.individual{
            for dig in row{
                to_return.push_str(&dig.display());
            }
            to_return.push_str("\n");
        }
        to_return
    }

    //fold the function that prints a cell and adds it to the result
    //we get a function that prints a row
    //fold the function that prints a row (and a newline) and adds it to the result
    //we get a function that prints a sudoku
    pub fn display(&self) -> String {
        self.individual.into_iter().fold(
            String::new(),|mut to_return: String, row|{
                //function that prints a row
                to_return = row.into_iter().fold(
                    to_return,|mut a: String, dig|{
                        //function that prints a cell
                        a.push_str(&dig.display());
                        a
                    });
                to_return.push_str("\n");
                to_return
        })
    }
}

