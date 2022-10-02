use crate::snake::Snake;
use crate::grid::Grid;
use crate::grid::GridItem;
use crate::point::Point;

use rand::Rng;
use rand::thread_rng;
use rand::seq::SliceRandom;

pub struct Game {
    snake: Snake,
    grid: Grid<GridItem>,
    output: fn(String),
    score: i32,
}

impl Game {
    pub fn new(snake: Snake, grid: Grid<GridItem>, output: fn(String)) -> Self {
        let mut game = Self { snake, grid, output, score: 0 };
        game.add_random_apple();
        game
    }

    pub fn run_once(&mut self) {
        self.clear_snake();
        self.move_snake();
        self.fit_snake_to_grid();
        self.check_for_score();
        self.add_snake();
        self.draw();
    }

    fn try_move(&self, value: u32) -> Option<Snake> {
        let bound = Point::new(self.grid.columns as i32, self.grid.rows as i32);
        match value {
            0 => self.snake.move_east(bound),
            1 => self.snake.move_north(bound),
            2 => self.snake.move_west(bound),
            3 => self.snake.move_south(bound),
            _ => None
        }
    }

    fn check_for_score(&mut self) {
        match self.grid.get_value(self.snake.head().x as usize, self.snake.head().y as usize) {
            GridItem::Apple => {
                self.score += 1;
                self.add_random_apple();
            },
            _ => ()
        }
    }

    fn move_snake(&mut self) {
        let mut vec: Vec<u32> = (0..4).collect();
        vec.shuffle(&mut thread_rng());
        for i in vec {
            match self.try_move(i) {
                Some(s) => {
                    self.snake = s;
                    return;
                },
                None => {}
            }
        }
        panic!("No movement found! {}", self.snake);
    }

    fn fit_snake_to_grid(&mut self) {
        let mod_grid = |a:i32, m: usize| (a + m as i32) % (m as i32);
        self.snake = Snake::from_vector(self.snake.data.iter().map(|p| Point::new(mod_grid(p.x, self.grid.columns), mod_grid(p.y, self.grid.rows))).collect());
    }

    fn add_snake(&mut self) {
        self.snake.data.iter().take(1).for_each(|s| self.grid.set_value(s.x as usize, s.y as usize, GridItem::SnakeHead));
        self.snake.data.iter().skip(1).for_each(|s| self.grid.set_value(s.x as usize, s.y as usize, GridItem::SnakeBody));
    }

    fn clear_snake(&mut self) {
        for row in 0..self.grid.rows {
            for column in 0..self.grid.columns {
                let item = self.grid.get_value(column, row);
                match item {
                    GridItem::SnakeBody => self.grid.set_value(column, row, GridItem::Empty),
                    GridItem::SnakeHead => self.grid.set_value(column, row, GridItem::Empty),
                    GridItem::Apple => {},
                    GridItem::Empty => {},
                }
            }
        }
    }

    fn add_apple(&mut self, x: usize, y: usize) {
        self.grid.set_value(x, y, GridItem::Apple);
    }

    fn add_random_apple(&mut self) {
        loop  {
            let p = Point::<i32>::new(thread_rng().gen_range(0..self.grid.columns-1) as i32, thread_rng().gen_range(0..self.grid.rows-1) as i32);
            if self.snake.data.iter().all(|&x| p != x) {
                self.add_apple(p.x as usize, p.y as usize);
                break;
            }
        }
    }

    fn draw(&self) {
        let mut string_builder: Vec<String> = vec![];
        string_builder.push(String::from(format!("Score: {}\n", self.score)));
        string_builder.push(std::iter::repeat("-").take(self.grid.columns + 2).collect());
        string_builder.push(String::from("\n"));
        for row in 0..self.grid.rows {
            string_builder.push(String::from("|"));
            for column in 0..self.grid.columns {
                let item = self.grid.get_value(column, row);
                string_builder.push(format!("{}", item));
            }
            string_builder.push(String::from("|\n"));
        }
        string_builder.push(std::iter::repeat("-").take(self.grid.columns + 2).collect());
        string_builder.push(String::from("\n"));
        (self.output)(string_builder.join(""));
    }
}
