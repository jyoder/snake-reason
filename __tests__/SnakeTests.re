open Jest;
open Expect;
open Types;

describe("locations", () =>
  test("returns the locations a snall snake inhabits", () => {
    let snake = Snake.make({x: 3, y: 4}, Left);
    expect(Snake.locations(snake)) |> toEqual([{x: 3, y: 4}]);
  })
);

describe("grow", () => {
  test("grows the snake's tail right if the tail is pointed right", () => {
    let snake = Snake.make({x: 3, y: 4}, Left);
    expect(Snake.locations(Snake.grow(snake)))
    |> toEqual([{x: 3, y: 4}, {x: 4, y: 4}]);
  });

  test("grows the snake's tail left if the tail is pointed left", () => {
    let snake = Snake.make({x: 3, y: 4}, Right);
    expect(Snake.locations(Snake.grow(snake)))
    |> toEqual([{x: 3, y: 4}, {x: 2, y: 4}]);
  });

  test("grows the snake's tail up if the tail is pointed up", () => {
    let snake = Snake.make({x: 3, y: 4}, Down);
    expect(Snake.locations(Snake.grow(snake)))
    |> toEqual([{x: 3, y: 4}, {x: 3, y: 3}]);
  });

  test("grows the snake's tail down if the tail is pointed down", () => {
    let snake = Snake.make({x: 3, y: 4}, Up);
    expect(Snake.locations(Snake.grow(snake)))
    |> toEqual([{x: 3, y: 4}, {x: 3, y: 5}]);
  });

  test("grows from the end of a long snake's tail", () => {
    let snake = Snake.make({x: 3, y: 4}, Up);
    expect(Snake.locations(Snake.grow(Snake.grow(snake))))
    |> toEqual([{x: 3, y: 4}, {x: 3, y: 5}, {x: 3, y: 6}]);
  });
});

describe("move", () => {
  test("advances the tail left if it is pointed right", () => {
    let snake = Snake.grow(Snake.make({x: 3, y: 4}, Left));
    expect(Snake.locations(Snake.move(snake, Left)))
    |> toEqual([{x: 2, y: 4}, {x: 3, y: 4}]);
  });

  test("advances the tail right if it is pointed left", () => {
    let snake = Snake.grow(Snake.make({x: 3, y: 4}, Right));
    expect(Snake.locations(Snake.move(snake, Right)))
    |> toEqual([{x: 4, y: 4}, {x: 3, y: 4}]);
  });

  test("advances the tail up if it is pointed down", () => {
    let snake = Snake.grow(Snake.make({x: 3, y: 4}, Right));
    expect(Snake.locations(Snake.move(snake, Up)))
    |> toEqual([{x: 3, y: 3}, {x: 3, y: 4}]);
  });

  test("advances the tail down if it is pointed up", () => {
    let snake = Snake.grow(Snake.make({x: 3, y: 4}, Down));
    expect(Snake.locations(Snake.move(snake, Down)))
    |> toEqual([{x: 3, y: 5}, {x: 3, y: 4}]);
  });

  test("prevents the snake from moving back on itself", () => {
    let snake = Snake.grow(Snake.make({x: 3, y: 4}, Down));
    expect(Snake.locations(Snake.move(snake, Up)))
    |> toEqual([{x: 3, y: 5}, {x: 3, y: 4}]);
  });
});

describe("moveForward", () =>
  test("advances the snake in the opposite direction as the head", () => {
    let snake = Snake.make({x: 3, y: 4}, Left);
    expect(Snake.locations(Snake.moveForward(snake)))
    |> toEqual([{x: 2, y: 4}]);
  })
);