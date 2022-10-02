use std::fmt;

#[derive(Copy, Clone)]
pub enum GridItem {
    SnakeHead,
    SnakeBody,
    Apple,
    Empty,
}

impl fmt::Display for GridItem {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            GridItem::SnakeHead => write!(f, "S"),
            GridItem::SnakeBody => write!(f, "s"),
            GridItem::Apple => write!(f, "a"),
            GridItem::Empty => write!(f, " "),
            // GridItem::SnakeHead => write!(f, "🐍"),
            // GridItem::SnakeBody => write!(f, "🦴"),
            // GridItem::Apple => write!(f, "🍎"),
            // GridItem::Empty => write!(f, " "),
        }
    }
}

pub struct Grid<T> {
    data: Vec<Vec<T>>,
    pub rows: usize,
    pub columns: usize,
}

impl<T: std::clone::Clone + std::marker::Copy + fmt::Display> Grid<T> {
    pub fn new(rows: usize, columns: usize, default_value: T) -> Self {
        let data = vec![vec![default_value; columns]; rows];
        Self { data, rows, columns }
    }

    pub fn show(&self) {
        for v in self.data.iter() {
            for v2 in v {
                print!("{} ", v2);
            }
            println!();
        }
    }

    pub fn set_value(&mut self, x: usize, y: usize, value: T) {
        self.data[y][x] = value;
    }

    pub fn get_value(&self, x: usize, y: usize) -> T {
        self.data[y][x]
    }
}
