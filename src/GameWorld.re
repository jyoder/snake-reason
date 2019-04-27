open Types;

type state =
  | Alive
  | Dead;

type nextApple = unit => Apple.t;

type t = {
  dimensions,
  state,
  snake: Snake.t,
  apple: Apple.t,
  nextApple,
};

let _cmpLocations = (l1: point, l2: point): int =>
  if (l1.x < l2.x) {
    (-1);
  } else if (l1.x > l2.x) {
    1;
  } else if (l1.y < l2.y) {
    (-1);
  } else if (l1.y > l2.y) {
    1;
  } else {
    0;
  };

let _eatingApple = (snake: Snake.t, apple: Apple.t): bool => {
  Apple.location(apple) == List.hd(Snake.locations(snake));
};

let _eatingSelf = (snake: Snake.t): bool => {
  let locs = Snake.locations(snake);
  List.length(locs) != List.length(List.sort_uniq(_cmpLocations, locs));
};

let _outsideBoundaries = (snake: Snake.t, dimensions: dimensions): bool => {
  let location = List.hd(Snake.locations(snake));
  location.x < 0
  || location.y < 0
  || location.x >= dimensions.width
  || location.y >= dimensions.height;
};

let _move = (snake: Snake.t, direction: option(direction)): Snake.t => {
  switch (direction) {
  | Some(d) => Snake.move(snake, d)
  | None => Snake.moveForward(snake)
  };
};

let _grow = (snake: Snake.t, apple: Apple.t): Snake.t => {
  _eatingApple(snake, apple) ? Snake.grow(snake) : snake;
};

let _newState = (snake: Snake.t, dimensions: dimensions): state => {
  _outsideBoundaries(snake, dimensions) || _eatingSelf(snake) ? Dead : Alive;
};

let _newSnake = (snake: Snake.t, apple: Apple.t): Snake.t => {
  _grow(snake, apple);
};

let _newApple = (snake: Snake.t, apple: Apple.t, nextApple: nextApple): Apple.t => {
  _eatingApple(snake, apple) ? nextApple() : apple;
};

let make =
    (dimensions: dimensions, state: state, snake: Snake.t, apple: Apple.t, nextApple: nextApple)
    : t => {
  {dimensions, state, snake, apple, nextApple};
};

let dimensions = (gameWorld: t): dimensions => {
  gameWorld.dimensions;
};

let state = (gameWorld: t): state => {
  gameWorld.state;
};

let snake = (gameWorld: t): Snake.t => {
  gameWorld.snake;
};

let apple = (gameWorld: t): Apple.t => {
  gameWorld.apple;
};

let tick = (gameWorld: t, movement: option(direction)): t => {
  let snake = _move(gameWorld.snake, movement);
  {
    ...gameWorld,
    state: _newState(snake, gameWorld.dimensions),
    snake: _newSnake(snake, gameWorld.apple),
    apple: _newApple(snake, gameWorld.apple, gameWorld.nextApple),
  };
};