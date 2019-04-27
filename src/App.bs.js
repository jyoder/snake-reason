// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Random = require("bs-platform/lib/js/random.js");
var Runtime$Snake = require("./Runtime.bs.js");
var GameRunFactory$Snake = require("./GameRunFactory.bs.js");
var RuntimeContextFactory$Snake = require("./RuntimeContextFactory.bs.js");

Random.init(Date.now() | 0);

var match = RuntimeContextFactory$Snake.makeRuntimeContext(/* () */0);

if (match.tag) {
  console.log(match[0]);
} else {
  Runtime$Snake.start(match[0], GameRunFactory$Snake.makeGameRun(/* () */0));
}

/*  Not a pure module */
