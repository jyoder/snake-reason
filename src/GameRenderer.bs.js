// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Apple$Snake = require("./Apple.bs.js");
var Snake$Snake = require("./Snake.bs.js");
var GameWorld$Snake = require("./GameWorld.bs.js");

var _cellDimensions = /* record */[
  /* width */15,
  /* height */15
];

function _backgroundColor(gameWorld) {
  var match = GameWorld$Snake.state(gameWorld);
  if (match) {
    return /* Gray */3;
  } else {
    return /* White */0;
  }
}

function _pixelOfLocation($$location) {
  return /* record */[
          /* x */Caml_int32.imul($$location[/* x */0], 15),
          /* y */Caml_int32.imul($$location[/* y */1], 15)
        ];
}

function _middleOfScreen(gameWorld) {
  var d = GameWorld$Snake.dimensions(gameWorld);
  return _pixelOfLocation(/* record */[
              /* x */d[/* width */0] / 2 | 0,
              /* y */d[/* height */1] / 2 | 0
            ]);
}

function _background(gameWorld) {
  return /* :: */[
          /* Clear */Block.__(5, [_backgroundColor(gameWorld)]),
          /* [] */0
        ];
}

function _snake(snake) {
  return /* :: */[
          /* SetColor */Block.__(0, [/* Green */1]),
          List.map((function ($$location) {
                  return /* FillRect */Block.__(3, [
                            _pixelOfLocation($$location),
                            _cellDimensions
                          ]);
                }), Snake$Snake.locations(snake))
        ];
}

function _apple(apple) {
  return /* :: */[
          /* SetColor */Block.__(0, [/* Red */2]),
          /* :: */[
            /* FillRect */Block.__(3, [
                _pixelOfLocation(Apple$Snake.$$location(apple)),
                _cellDimensions
              ]),
            /* [] */0
          ]
        ];
}

function _message(gameWorld) {
  var match = GameWorld$Snake.state(gameWorld);
  if (match) {
    var gameWorld$1 = gameWorld;
    return /* :: */[
            /* SetFont */Block.__(2, [/* Title */0]),
            /* :: */[
              /* SetColor */Block.__(0, [/* Black */4]),
              /* :: */[
                /* SetTextAlign */Block.__(1, [/* Center */0]),
                /* :: */[
                  /* FillText */Block.__(4, [
                      "You have died.",
                      _middleOfScreen(gameWorld$1)
                    ]),
                  /* [] */0
                ]
              ]
            ]
          ];
  } else {
    return /* [] */0;
  }
}

function render(gameWorld) {
  return List.concat(/* :: */[
              _background(gameWorld),
              /* :: */[
                _snake(GameWorld$Snake.snake(gameWorld)),
                /* :: */[
                  _apple(GameWorld$Snake.apple(gameWorld)),
                  /* :: */[
                    _message(gameWorld),
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

exports.render = render;
/* No side effect */
