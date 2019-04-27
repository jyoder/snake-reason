open Types;

type t = {
  location: point,
  head: direction,
  body: list(direction),
};

let _fullBody = (snake: t): list(direction) => {
  [snake.head, ...snake.body];
};

let _adjacentTo = (location: point, direction: direction): point => {
  switch (direction) {
  | Left => {...location, x: location.x - 1}
  | Right => {...location, x: location.x + 1}
  | Up => {...location, y: location.y - 1}
  | Down => {...location, y: location.y + 1}
  };
};

let _reverse = (direction: direction): direction => {
  switch (direction) {
  | Left => Right
  | Right => Left
  | Up => Down
  | Down => Up
  };
};

let _currentDirection = (snake: t): direction => {
  _reverse(snake.head);
};

let _opposites = (d1: direction, d2: direction): bool => {
  switch (d1, d2) {
  | (Left, Right)
  | (Right, Left)
  | (Up, Down)
  | (Down, Up) => true
  | _ => false
  };
};

let _chooseDirection = (old: direction, next: direction): direction => {
  _opposites(old, next) ? old : next;
};

let rec _locationsOfDirections = (start: point, directions: list(direction)): list(point) => {
  switch (directions) {
  | [head, ...tail] => [start, ..._locationsOfDirections(_adjacentTo(start, head), tail)]
  | [] => []
  };
};

let _dropLast = (list: list('a)): list('a) => {
  List.rev(List.tl(List.rev(list)));
};

let make = (location: point, initialDirection: direction): t => {
  {location, head: _reverse(initialDirection), body: []};
};

let locations = (snake: t): list(point) => {
  _locationsOfDirections(snake.location, _fullBody(snake));
};

let move = (snake: t, direction: direction): t => {
  let direction = _chooseDirection(_currentDirection(snake), direction);
  {
    location: _adjacentTo(snake.location, direction),
    head: _reverse(direction),
    body: _dropLast(_fullBody(snake)),
  };
};

let moveForward = (snake: t): t => {
  move(snake, _reverse(snake.head));
};

let grow = (snake: t): t => {
  switch (snake.body) {
  | [] => {...snake, body: [snake.head]}
  | body => {...snake, body: List.append(body, [List.nth(body, List.length(body) - 1)])}
  };
};