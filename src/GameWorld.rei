open Types;

type t;

type state =
  | Alive
  | Dead;

type nextApple = unit => Apple.t;

let make: (dimensions, state, Snake.t, Apple.t, nextApple) => t;

let dimensions: t => dimensions;
let state: t => state;
let snake: t => Snake.t;
let apple: t => Apple.t;

let tick: (t, option(direction)) => t;