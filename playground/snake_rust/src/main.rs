mod grid;
mod snake;
mod game;
mod point;
mod Point;

use crate::game::Game;
use crate::grid::Grid;
use crate::grid::GridItem;
use crate::snake::Snake;

use std::{thread, time};

fn main() {
    let grid = Grid::new(5, 14, GridItem::Empty);
    let snake = Snake::new();
    let mut game = Game::new(snake, grid, |x| {
        print!("{}[2J", 27 as char);
        print!("{}", x);
    });

    loop {
        thread::sleep(time::Duration::from_millis(300));
        game.run_once();
    }
}
