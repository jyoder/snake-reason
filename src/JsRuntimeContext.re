open Types;
open RuntimeTypes;

open Belt;
open Dom;

type context;
type canvas;
type event;

[@bs.val] external _jsDocument: document = "document";
[@bs.send] external _addListener: (document, string, event => unit) => unit = "addEventListener";
[@bs.get] external _jsKeyGet: event => string = "key";
[@bs.send] external _jsFindCanvas: (document, string) => Js.nullable(canvas) = "getElementById";
[@bs.get] external _jsContextCanvas: context => canvas = "canvas";
[@bs.get] external _jsCanvasWidth: canvas => int = "width";
[@bs.get] external _jsCanvasHeight: canvas => int = "height";
[@bs.send] external _jsGetContext: (canvas, string) => context = "getContext";
[@bs.send] external _jsFillRect: (context, int, int, int, int) => unit = "fillRect";
[@bs.set] external _jsFillStyleSet: (context, string) => unit = "fillStyle";
[@bs.send] external _jsFillText: (context, string, int, int) => unit = "fillText";
[@bs.set] external _jsFontSet: (context, string) => unit = "font";
[@bs.set] external _jsTextAlignSet: (context, string) => unit = "textAlign";

let _findContext = (canvasId: string): Result.t(context, string) => {
  switch (Js.toOption(_jsFindCanvas(_jsDocument, canvasId))) {
  | Some(canvas) => Ok(_jsGetContext(canvas, "2d"))
  | None => Error("Could not find canvas element: " ++ canvasId)
  };
};

let _keyPressOfString = (key: string): option(keyPress) => {
  switch (key) {
  | "ArrowLeft" => Some(ArrowLeft)
  | "ArrowRight" => Some(ArrowRight)
  | "ArrowUp" => Some(ArrowUp)
  | "ArrowDown" => Some(ArrowDown)
  | _ => None
  };
};

let _jsColor = (color: color): string => {
  switch (color) {
  | White => "white"
  | Green => "green"
  | Red => "red"
  | Gray => "gray"
  | Black => "black"
  };
};

let _jsAlignment = (alignment: alignment): string => {
  switch (alignment) {
  | Center => "center"
  };
};

let _jsFont = (font: font): string => {
  switch (font) {
  | Title => "30px Comic Sans MS"
  };
};

let _start = (period: int, action: unit => unit): stop => {
  let intervalId = Js.Global.setInterval(action, period);
  () => Js.Global.clearInterval(intervalId);
};

let _listen = (handleKey: handleKey): unit => {
  _addListener(_jsDocument, "keydown", event =>
    switch (_keyPressOfString(_jsKeyGet(event))) {
    | Some(keyPress) => handleKey(keyPress)
    | None => ()
    }
  );
};

let _setColor = (context: context, color: color): unit => {
  _jsFillStyleSet(context, _jsColor(color));
};

let _setTextAlign = (context: context, alignment: alignment): unit => {
  _jsTextAlignSet(context, _jsAlignment(alignment));
};

let _setFont = (context: context, font: font): unit => {
  _jsFontSet(context, _jsFont(font));
};

let _fillRect = (context: context, location: point, dim: dimensions): unit => {
  _jsFillRect(context, location.x, location.y, dim.width, dim.height);
};

let _fillText = (context: context, text: string, location: point): unit => {
  _jsFillText(context, text, location.x, location.y);
};

let _clear = (context: context, color: color): unit => {
  _setColor(context, color);
  _fillRect(
    context,
    {x: 0, y: 0},
    {
      width: _jsCanvasWidth(_jsContextCanvas(context)),
      height: _jsCanvasHeight(_jsContextCanvas(context)),
    },
  );
};

let _make = (context: context, period: int): runtimeContext => {
  {
    start: _start(period),
    listen: _listen,
    setColor: _setColor(context),
    setTextAlign: _setTextAlign(context),
    setFont: _setFont(context),
    fillRect: _fillRect(context),
    fillText: _fillText(context),
    clear: _clear(context),
  };
};

let make = (canvasId: string, period: int): Result.t(runtimeContext, string) => {
  switch (_findContext(canvasId)) {
  | Ok(context) => Ok(_make(context, period))
  | Error(reason) => Error(reason)
  };
};