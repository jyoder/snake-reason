open Types;
open RuntimeTypes;

let _directionOfKeyPress = (keyPress: RuntimeTypes.keyPress): direction => {
  switch (keyPress) {
  | ArrowLeft => Left
  | ArrowUp => Up
  | ArrowRight => Right
  | ArrowDown => Down
  };
};

let rec run = (gameWorld: GameWorld.t, keyPress: option(keyPress)): runResult => {
    let direction = switch(keyPress) {
        | Some(keyPress) => Some(_directionOfKeyPress(keyPress))
        | None => None
    };

    let nextGameWorld = GameWorld.tick(gameWorld, direction);
    let commands = GameRenderer.render(gameWorld);

    switch(GameWorld.state(gameWorld)) {
      | Alive => {nextRun: Some(run(nextGameWorld)), commands: commands}
      | Dead => {nextRun: None, commands: commands}
    };
};