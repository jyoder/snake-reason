open Types;
open RuntimeTypes;

let _cellSize = 15;
let _cellDimensions = {width: _cellSize, height: _cellSize};

let _aliveBackgroundColor = White;
let _deadBackgroundColor = Gray;

let _snakeColor = Green;
let _appleColor = Red;

let _font = Title;
let _textColor = Black;
let _textAlign = Center;

let _backgroundColor = (gameWorld: GameWorld.t): color => {
  switch (GameWorld.state(gameWorld)) {
  | GameWorld.Alive => _aliveBackgroundColor
  | GameWorld.Dead => _deadBackgroundColor
  };
};

let _pixelOfLocation = (location: point): point => {
  {x: location.x * _cellSize, y: location.y * _cellSize};
};

let _middleOfScreen = (gameWorld: GameWorld.t): point => {
  let d = GameWorld.dimensions(gameWorld);
  _pixelOfLocation({x: d.width / 2, y: d.height / 2});
};

let _background = (gameWorld: GameWorld.t): commands => {
  [Clear(_backgroundColor(gameWorld))];
};

let _cell = (pixel: point): command => {
  FillRect(pixel, _cellDimensions);
};

let _snake = (snake: Snake.t): commands => {
  [
    SetColor(_snakeColor),
    ...List.map(location => _cell(_pixelOfLocation(location)), Snake.locations(snake)),
  ];
};

let _apple = (apple: Apple.t): commands => {
  [SetColor(_appleColor), _cell(_pixelOfLocation(Apple.location(apple)))];
};

let _deadMessage = (gameWorld: GameWorld.t): commands => {
  [
    SetFont(_font),
    SetColor(_textColor),
    SetTextAlign(_textAlign),
    FillText("You have died.", _middleOfScreen(gameWorld)),
  ];
};

let _message = (gameWorld: GameWorld.t): commands => {
  switch (GameWorld.state(gameWorld)) {
  | GameWorld.Dead => _deadMessage(gameWorld)
  | GameWorld.Alive => []
  };
};

let render = (gameWorld: GameWorld.t): commands => {
  List.concat([
    _background(gameWorld),
    _snake(GameWorld.snake(gameWorld)),
    _apple(GameWorld.apple(gameWorld)),
    _message(gameWorld),
  ]);
};