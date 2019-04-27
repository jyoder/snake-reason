open Jest;
open Expect;
open Types;

describe("location", () =>
  test("returns the location of the apple", () => {
    let apple = Apple.make({x: 5, y: 4});
    expect(Apple.location(apple)) |> toEqual({x: 5, y: 4});
  })
);