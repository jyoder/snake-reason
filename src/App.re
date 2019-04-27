Random.init(int_of_float(Js.Date.now()));

switch(RuntimeContextFactory.makeRuntimeContext()) {
    | Ok(runtimeContext) => Runtime.start(runtimeContext, GameRunFactory.makeGameRun())
    | Error(reason) => Js.log(reason)
};