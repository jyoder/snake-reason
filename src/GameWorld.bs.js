// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Apple$Snake = require("./Apple.bs.js");
var Snake$Snake = require("./Snake.bs.js");

function _cmpLocations(l1, l2) {
  if (l1[/* x */0] < l2[/* x */0]) {
    return -1;
  } else if (l1[/* x */0] > l2[/* x */0]) {
    return 1;
  } else if (l1[/* y */1] < l2[/* y */1]) {
    return -1;
  } else if (l1[/* y */1] > l2[/* y */1]) {
    return 1;
  } else {
    return 0;
  }
}

function _eatingApple(snake, apple) {
  return Caml_obj.caml_equal(Apple$Snake.$$location(apple), List.hd(Snake$Snake.locations(snake)));
}

function _eatingSelf(snake) {
  var locs = Snake$Snake.locations(snake);
  return List.length(locs) !== List.length(List.sort_uniq(_cmpLocations, locs));
}

function _outsideBoundaries(snake, dimensions) {
  var $$location = List.hd(Snake$Snake.locations(snake));
  if ($$location[/* x */0] < 0 || $$location[/* y */1] < 0 || $$location[/* x */0] >= dimensions[/* width */0]) {
    return true;
  } else {
    return $$location[/* y */1] >= dimensions[/* height */1];
  }
}

function _move(snake, direction) {
  if (direction !== undefined) {
    return Snake$Snake.move(snake, direction);
  } else {
    return Snake$Snake.moveForward(snake);
  }
}

function _grow(snake, apple) {
  var match = _eatingApple(snake, apple);
  if (match) {
    return Snake$Snake.grow(snake);
  } else {
    return snake;
  }
}

function _newState(snake, dimensions) {
  var match = _outsideBoundaries(snake, dimensions) || _eatingSelf(snake);
  if (match) {
    return /* Dead */1;
  } else {
    return /* Alive */0;
  }
}

function _newApple(snake, apple, nextApple) {
  var match = _eatingApple(snake, apple);
  if (match) {
    return Curry._1(nextApple, /* () */0);
  } else {
    return apple;
  }
}

function make(dimensions, state, snake, apple, nextApple) {
  return /* record */[
          /* dimensions */dimensions,
          /* state */state,
          /* snake */snake,
          /* apple */apple,
          /* nextApple */nextApple
        ];
}

function dimensions(gameWorld) {
  return gameWorld[/* dimensions */0];
}

function state(gameWorld) {
  return gameWorld[/* state */1];
}

function snake(gameWorld) {
  return gameWorld[/* snake */2];
}

function apple(gameWorld) {
  return gameWorld[/* apple */3];
}

function tick(gameWorld, movement) {
  var snake = _move(gameWorld[/* snake */2], movement);
  return /* record */[
          /* dimensions */gameWorld[/* dimensions */0],
          /* state */_newState(snake, gameWorld[/* dimensions */0]),
          /* snake */_grow(snake, gameWorld[/* apple */3]),
          /* apple */_newApple(snake, gameWorld[/* apple */3], gameWorld[/* nextApple */4]),
          /* nextApple */gameWorld[/* nextApple */4]
        ];
}

exports.make = make;
exports.dimensions = dimensions;
exports.state = state;
exports.snake = snake;
exports.apple = apple;
exports.tick = tick;
/* No side effect */
