open RuntimeTypes;

let _processCommand = (runtimeContext: runtimeContext, command: command): unit => {
  switch (command) {
  | SetColor(color) => runtimeContext.setColor(color)
  | SetTextAlign(alignment) => runtimeContext.setTextAlign(alignment)
  | SetFont(font) => runtimeContext.setFont(font)
  | FillRect(point, dimensions) => runtimeContext.fillRect(point, dimensions)
  | FillText(string, point) => runtimeContext.fillText(string, point)
  | Clear(color) => runtimeContext.clear(color)
  };
};

let _processCommands = (runtimeContext: runtimeContext, commands: commands): unit => {
  ListLabels.iter(~f=_processCommand(runtimeContext), commands);
};

let _processRunResult = (runtimeContext: runtimeContext, runResult: runResult): option(run) => {
  _processCommands(runtimeContext, runResult.commands);
  runResult.nextRun;
};

let _execute =
    (
      runtimeContext: runtimeContext,
      run: option(run),
      stop: option(stop),
      keyPress: option(keyPress),
    )
    : option(run) => {
  switch (run, stop) {
  | (Some(run), _) => _processRunResult(runtimeContext, run(keyPress))
  | (None, Some(stop)) =>
    stop();
    None;
  | _ => None
  };
};

let start = (runtimeContext: runtimeContext, run: run): unit => {
  let keyPress = ref(None);
  runtimeContext.listen(k => keyPress := Some(k));

  let run = ref(Some(run));
  let stop = ref(None);

  stop :=
    Some(
      runtimeContext.start(() => {
        run := _execute(runtimeContext, run^, stop^, keyPress^);
        keyPress := None;
      }),
    );
};