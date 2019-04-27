open RuntimeTypes;

let _gameWorldSize = 40;

let _nextApple = (): Apple.t => {
  Apple.make({x: Random.int(_gameWorldSize), y: Random.int(_gameWorldSize)});
};

let _makeSnake = (): Snake.t => {
  Snake.make({x: _gameWorldSize / 2, y: _gameWorldSize / 2}, Left);
};

let _makeGameWorld = (): GameWorld.t => {
  GameWorld.make(
    {width: _gameWorldSize, height: _gameWorldSize},
    GameWorld.Alive,
    _makeSnake(),
    _nextApple(),
    _nextApple,
  );
};

let makeGameRun = (): run => {
    GameRun.run(_makeGameWorld());
};
