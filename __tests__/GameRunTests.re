open Jest;
open Expect;
open Types;
open RuntimeTypes;

let _nextApple = () => Apple.make({x: 1, y: 1});

let _gameWorld = (~direction=Left, ()) => {
  GameWorld.make(
    {width: 3, height: 3},
    Alive,
    Snake.make({x: 1, y: 1}, direction),
    Apple.make({x: 0, y: 0}),
    _nextApple,
  );
};

describe("run", () => {
  test("returns successive game states until the snake is dead", () => {
    let died =
      switch (GameRun.run(_gameWorld(), None).nextRun) {
      | Some(nextRun) =>
        switch (nextRun(None).nextRun) {
        | Some(nextRun) =>
          switch (nextRun(None).nextRun) {
          | Some(_) => false
          | None => true
          }
        | None => false
        }
      | None => false
      };
    expect(died) |> toEqual(true);
  });

  test("returns commands to render the game world", () => {
    let commands = GameRun.run(_gameWorld(), None).commands;
    expect(List.hd(commands)) |> toEqual(Clear(White));
  });

  test("moves the snake up when the up arrow is pressed", () => {
    let commands =
      switch (GameRun.run(_gameWorld(), Some(ArrowUp)).nextRun) {
      | Some(nextRun) => nextRun(None).commands
      | None => []
      };
    expect((List.nth(commands, 1), List.nth(commands, 2)))
    |> toEqual((SetColor(Green), FillRect({x: 15, y: 0}, {width: 15, height: 15})));
  });

  test("moves the snake down when the down arrow is pressed", () => {
    let commands =
      switch (GameRun.run(_gameWorld(), Some(ArrowDown)).nextRun) {
      | Some(nextRun) => nextRun(None).commands
      | None => []
      };
    expect((List.nth(commands, 1), List.nth(commands, 2)))
    |> toEqual((SetColor(Green), FillRect({x: 15, y: 30}, {width: 15, height: 15})));
  });

  test("moves the snake left when the left arrow is pressed", () => {
    let commands =
      switch (GameRun.run(_gameWorld(), Some(ArrowLeft)).nextRun) {
      | Some(nextRun) => nextRun(None).commands
      | None => []
      };
    expect((List.nth(commands, 1), List.nth(commands, 2)))
    |> toEqual((SetColor(Green), FillRect({x: 0, y: 15}, {width: 15, height: 15})));
  });

  test("moves the snake right when the right arrow is pressed", () => {
    let commands =
      switch (GameRun.run(_gameWorld(~direction=Right)(), Some(ArrowRight)).nextRun) {
      | Some(nextRun) => nextRun(None).commands
      | None => []
      };
    expect((List.nth(commands, 1), List.nth(commands, 2)))
    |> toEqual((SetColor(Green), FillRect({x: 30, y: 15}, {width: 15, height: 15})));
  });
});