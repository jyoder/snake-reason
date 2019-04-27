open Jest;
open Expect;
open Types;
open RuntimeTypes;

let _nextApple = () => Apple.make({x: 1, y: 1});

let _gameWorld =
  GameWorld.make(
    {width: 10, height: 10},
    Alive,
    Snake.make({x: 5, y: 5}, Left),
    Apple.make({x: 3, y: 5}),
    _nextApple,
  );

let _deadGameWorld =
  GameWorld.make(
    {width: 10, height: 10},
    Dead,
    Snake.make({x: 5, y: 5}, Left),
    Apple.make({x: 3, y: 5}),
    _nextApple,
  );

describe("render", () => {
  test("renders a white background", () =>
    expect(List.nth(GameRenderer.render(_gameWorld), 0)) |> toEqual(Clear(White))
  );

  test("renders the snake as a green square", () => {
    let commands = GameRenderer.render(_gameWorld);
    expect((List.nth(commands, 1), List.nth(commands, 2)))
    |> toEqual((SetColor(Green), FillRect({x: 75, y: 75}, {width: 15, height: 15})));
  });

  test("renders the apple as a red square", () => {
    let commands = GameRenderer.render(_gameWorld);
    expect((List.nth(commands, 3), List.nth(commands, 4)))
    |> toEqual((SetColor(Red), FillRect({x: 45, y: 75}, {width: 15, height: 15})));
  });

  test("renders nothing extra when the snake is alive", () => {
    let commands = GameRenderer.render(_gameWorld);
    expect(List.length(commands)) |> toEqual(5);
  });

  test("renders a gray background when the snake is dead", () =>
    expect(List.nth(GameRenderer.render(_deadGameWorld), 0)) |> toEqual(Clear(Gray))
  );

  test("renders an informative message when the snake is dead", () => {
    let commands = GameRenderer.render(_deadGameWorld);
    expect((
      List.nth(commands, 5),
      List.nth(commands, 6),
      List.nth(commands, 7),
      List.nth(commands, 8),
    ))
    |> toEqual((
         SetFont(Title),
         SetColor(Black),
         SetTextAlign(Center),
         FillText("You have died.", {x: 75, y: 75}),
       ));
  });
});