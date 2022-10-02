use std::fmt;

use crate::point::Point;

type SnakeType = i32;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Direction {
    West,
    North,
    East,
    South,
}

impl Direction {
    fn vector(self) -> Point<SnakeType> {
        match self {
            Direction::East => Point::new(1, 0),
            Direction::West => Point::new(-1, 0),
            Direction::North => Point::new(0, -1),
            Direction::South => Point::new(0, 1),
        }
    }
}
pub struct Snake {
    pub data: Vec<Point<SnakeType>>,
    pub length: usize,
}

impl fmt::Display for Snake {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.debug_struct("Snake").field("data", &self.data).field("length", &self.length).field("facing", &self.facing()).finish()
    }
}

impl Snake {
    pub fn new() -> Self {
        const LENGTH: usize = 5;
        let x: Vec<SnakeType>= (0..LENGTH).rev().map(|x| x as SnakeType).collect();
        let y = [0 as SnakeType; LENGTH].map(|x| x as SnakeType).to_vec();
        let data = x.into_iter().zip(y.into_iter()).map(|p| Point::new(p.0, p.1)).collect();
        Self { data, length: LENGTH }
    }

    pub fn from_vector(data: Vec<Point<SnakeType>>) -> Self {
        let length = data.len();

        Self { data, length }
    }

    fn facing(&self) -> Direction{
        match self.data[0] - self.data[1] {
            Point { x: 0, y: 1 } => Direction::South,
            Point { x: 0, y: -1 } => Direction::North,
            Point { x: 1, y: 0 } => Direction::East,
            Point { x: -1, y: 0 } => Direction::West,
            _ => panic!("Incorrect facing snake!")
        }
    }

    pub fn head(&self) -> Point<SnakeType> {
        self.data[0]
    }

    fn body(&self) -> Vec<Point<SnakeType>> {
        self.data[0..].to_vec()
    }

    fn can_move(&self, new_head: Point<SnakeType>, bound: Point<SnakeType>) -> bool {
        let does_not_go_into_body = self.data.iter().skip(1).all(|body_point| body_point != &new_head);
        let does_go_outside_bound = 0 <= new_head.x && new_head.x < bound.x && 0 <= new_head.y && new_head.y < bound.y;
        return does_not_go_into_body && does_go_outside_bound;
    }

    fn move_snake(&self, direction: Direction, bound: Point<SnakeType>) ->  Option<Snake>{
        let move_vector = direction.vector();

        let new_head: Point<SnakeType> = Point { x: self.head().x + move_vector.x, y: self.head().y + move_vector.y };
        let mut new_body = self.data[..self.length-1].to_vec();
        let mut new_data = vec![new_head];
        new_data.append(&mut new_body);
        let new_snake = Snake::from_vector(new_data);

        return match self.can_move(new_head, bound) {
            true => Some(new_snake),
            false => None,
        }
    }

    pub fn move_west(&self, bound: Point<SnakeType>) -> Option<Snake> {
        return self.move_snake(Direction::West, bound)
    }

    pub fn move_east(&self, bound: Point<SnakeType>) -> Option<Snake> {
        return self.move_snake(Direction::East, bound)
    }

    pub fn move_north(&self, bound: Point<SnakeType>) -> Option<Snake> {
        return self.move_snake(Direction::North, bound)
    }

    pub fn move_south(&self, bound: Point<SnakeType>) -> Option<Snake> {
        return self.move_snake(Direction::South, bound)
    }

}
