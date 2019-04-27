// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var GameWorld$Snake = require("./GameWorld.bs.js");
var GameRenderer$Snake = require("./GameRenderer.bs.js");

function run(gameWorld, keyPress) {
  var direction = keyPress !== undefined ? keyPress : undefined;
  var nextGameWorld = GameWorld$Snake.tick(gameWorld, direction);
  var commands = GameRenderer$Snake.render(gameWorld);
  var match = GameWorld$Snake.state(gameWorld);
  if (match) {
    return /* record */[
            /* nextRun */undefined,
            /* commands */commands
          ];
  } else {
    return /* record */[
            /* nextRun */(function (param) {
                return run(nextGameWorld, param);
              }),
            /* commands */commands
          ];
  }
}

exports.run = run;
/* No side effect */
