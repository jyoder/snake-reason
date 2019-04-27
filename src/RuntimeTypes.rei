open Types;

type color =
  | White
  | Green
  | Red
  | Gray
  | Black;

type alignment =
  | Center;

type font =
  | Title;

type command =
  | SetColor(color)
  | SetTextAlign(alignment)
  | SetFont(font)
  | FillRect(point, dimensions)
  | FillText(string, point)
  | Clear(color);

type commands = list(command);

type keyPress =
  | ArrowLeft
  | ArrowRight
  | ArrowUp
  | ArrowDown;

type run = (option(keyPress)) => runResult
and runResult = {
  nextRun: option(run),
  commands
};

type stop = (unit) => unit;
type start = ((unit) => unit) => stop;

type handleKey = (keyPress) => unit;
type listen = (handleKey) => unit;

type runtimeContext = {
  start: start,
  listen: listen,
  setColor: (color) => unit,
  setTextAlign: (alignment) => unit,
  setFont: (font) => unit,
  fillRect: (point, dimensions) => unit,
  fillText: (string, point) => unit,
  clear: (color) => unit
};
