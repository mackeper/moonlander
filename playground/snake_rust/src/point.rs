use std::ops::Sub;

#[derive(PartialEq, Copy, Clone, Debug)]
pub struct Point<T> {
    pub x: T,
    pub y: T,
}

impl<T> Point<T> {
    pub fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

impl<T: Sub<Output = T>> Sub for Point<T> {
    type Output = Self;

    fn sub(self, rhs: Self) -> Self::Output {
        Point::new(self.x - rhs.x, self.y - rhs.y)
    }
}

// impl<T: PartialEq> PartialEq for Point<T> {
//     fn eq(&self, &other: &Point<T>) -> bool {
//         self.x == other.x && self.y == other.y
//     }
// }
