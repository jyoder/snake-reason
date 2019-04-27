open Types;

type t;

let make: (point, direction) => t;

let locations: t => list(point);

let move: (t, direction) => t;
let moveForward: t => t;
let grow: t => t;