open Jest;
open Expect;
open Types;
open RuntimeTypes;

type control =
  | Start(unit => unit)
  | Stop
  | Listen(handleKey);

type call =
  | Control(control)
  | Command(command);

type calls = list(call);
type keyPresses = list(keyPress);

let _stop = (calls: ref(calls), ()): unit => {
  calls := [Control(Stop), ...calls^];
};

let _runtimeContext = (calls: ref(calls)): runtimeContext => {
  start: run => {
    calls := [Control(Start(run)), ...calls^];
    _stop(calls);
  },
  listen: handleKey => calls := [Control(Listen(handleKey)), ...calls^],
  setColor: color => calls := [Command(SetColor(color)), ...calls^],
  setTextAlign: alignment => calls := [Command(SetTextAlign(alignment)), ...calls^],
  setFont: font => calls := [Command(SetFont(font)), ...calls^],
  fillRect: (point, dimensions) => calls := [Command(FillRect(point, dimensions)), ...calls^],
  fillText: (string, point) => calls := [Command(FillText(string, point)), ...calls^],
  clear: color => calls := [Command(Clear(color)), ...calls^],
};

let _run =
    (commands: commands, keyPresses: ref(keyPresses), keyPress: option(keyPress)): runResult => {
  switch (keyPress) {
  | Some(keyPress) => keyPresses := [keyPress, ...keyPresses^]
  | None => ()
  };
  {nextRun: None, commands};
};

describe("start", () => {
  test("listens for and uses key presses in each run of the game loop", () => {
    let calls = ref([]);
    let keyPresses = ref([]);
    Runtime.start(_runtimeContext(calls), _run([], keyPresses));

    switch (List.rev(calls^)) {
    | [Control(Listen(handleKey)), Control(Start(run))] =>
      handleKey(ArrowUp);
      run();
    | _ => ()
    };

    expect(keyPresses^) |> toEqual([ArrowUp]);
  });

  test("stops when there is no next run", () => {
    let calls = ref([]);
    let keyPresses = ref([]);
    Runtime.start(_runtimeContext(calls), _run([], keyPresses));

    switch (List.rev(calls^)) {
    | [Control(Listen(handleKey)), Control(Start(run))] =>
      handleKey(ArrowUp);
      run();
      run();
    | _ => ()
    };

    let stopped =
      switch (List.hd(calls^)) {
      | Control(Stop) => true
      | _ => false
      };

    expect(stopped) |> toEqual(true);
  });

  test("executes all render commands", () => {
    let calls = ref([]);
    let keyPresses = ref([]);

    let commands = [
      SetColor(Green),
      SetTextAlign(Center),
      SetFont(Title),
      FillRect({x: 3, y: 4}, {width: 5, height: 6}),
      FillText("hello", {x: 1, y: 2}),
      Clear(White),
    ];
    Runtime.start(_runtimeContext(calls), _run(commands, keyPresses));

    switch (List.rev(calls^)) {
    | [_, Control(Start(run))] => run()
    | _ => ()
    };

    expect(List.tl(List.tl(List.rev(calls^))))
    |> toEqual([
         Command(SetColor(Green)),
         Command(SetTextAlign(Center)),
         Command(SetFont(Title)),
         Command(FillRect({x: 3, y: 4}, {width: 5, height: 6})),
         Command(FillText("hello", {x: 1, y: 2})),
         Command(Clear(White)),
       ]);
  });
});