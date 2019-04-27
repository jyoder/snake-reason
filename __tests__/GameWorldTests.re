open Jest;
open Expect;
open Types;

let _nextApple = () => Apple.make({x: 1, y: 1});

let _gameWorld =
  GameWorld.make(
    {width: 10, height: 10},
    Alive,
    Snake.make({x: 5, y: 5}, Left),
    Apple.make({x: 3, y: 5}),
    _nextApple
  );

let _smallGameWorld = (direction: direction): GameWorld.t => {
  GameWorld.make(
    {width: 1, height: 1},
    Alive,
    Snake.make({x: 0, y: 0}, direction),
    Apple.make({x: 5, y: 5}),
    _nextApple
  );
};


describe("dimensions", () =>
  test("returns the dimensions of the game world", () =>
    expect(GameWorld.dimensions(_gameWorld))
    |> toEqual({width: 10, height: 10})
  )
);

describe("state", () =>
  test("returns the state of the game world", () =>
    expect(GameWorld.state(_gameWorld)) |> toEqual(GameWorld.Alive)
  )
);

describe("snake", () =>
  test(
    "returns the snake in the game world, initially located in the center", () =>
    expect(Snake.locations(GameWorld.snake(_gameWorld)))
    |> toEqual([{x: 5, y: 5}])
  )
);

describe("apple", () =>
  test("returns the apple in the game world", () =>
    expect(Apple.location(GameWorld.apple(_gameWorld)))
    |> toEqual({x: 3, y: 5})
  )
);

describe("tick", () => {
  test("moves the snake based on the given input direction", () => {
    expect(
      Snake.locations(GameWorld.snake(GameWorld.tick(_gameWorld, Some(Up)))),
    )
    |> toEqual([{x: 5, y: 4}]);
  });

  test("moves the snake forward if no input direction is given", () => {
    expect(
      Snake.locations(GameWorld.snake(GameWorld.tick(_gameWorld, None))),
    )
    |> toEqual([{x: 4, y: 5}]);
  });

  test("generates a new apple if the snake eats the existing one", () => {
    expect(
      Apple.location(
        GameWorld.apple(
          GameWorld.tick(GameWorld.tick(_gameWorld, Some(Left)), Some(Left)),
        ),
      ),
    )
    |> toEqual({x: 1, y: 1});
  });

  test("grows the snake when it eats the apple", () => {
    expect(
      List.length(
        Snake.locations(
          GameWorld.snake(
            GameWorld.tick(GameWorld.tick(_gameWorld, Some(Left)), Some(Left)),
          ),
        ),
      ),
    )
    |> toEqual(2);
  });

  test("kills the snake when it hits the left boundary", () => {
    expect(GameWorld.state(GameWorld.tick(_smallGameWorld(Left), Some(Left))))
    |> toEqual(GameWorld.Dead);
  });

  test("kills the snake when it hits the top boundary", () => {
    expect(GameWorld.state(GameWorld.tick(_smallGameWorld(Up), Some(Up))))
    |> toEqual(GameWorld.Dead);
  });

  test("kills the snake when it hits the right boundary", () => {
    expect(GameWorld.state(GameWorld.tick(_smallGameWorld(Right), Some(Right))))
    |> toEqual(GameWorld.Dead);
  });

  test("kills the snake when it hits the bottom boundary", () => {
    expect(GameWorld.state(GameWorld.tick(_smallGameWorld(Down), Some(Down))))
    |> toEqual(GameWorld.Dead);
  });

  test("kills the snake when it eats itself", () => {
    let longSnake =
      Snake.grow(
        Snake.grow(
          Snake.grow(Snake.grow(Snake.make({x: 5, y: 5}, Left))),
        ),
      );

    let gameWorld =
      GameWorld.make(
        {width: 10, height: 10},
        GameWorld.Alive,
        longSnake,
        Apple.make({x: 0, y: 0}),
        _nextApple
      );

    expect(
      GameWorld.state(
        GameWorld.tick(
          GameWorld.tick(GameWorld.tick(gameWorld, Some(Up)), Some(Right)),
          Some(Down),
        ),
      ),
    )
    |> toEqual(GameWorld.Dead);
  });
});