open RuntimeTypes;
open Belt;

let _updatePeriod = 200;
let _canvasId = "js-canvas";

let makeRuntimeContext = (): Result.t(runtimeContext, string) => {
    JsRuntimeContext.make(_canvasId, _updatePeriod);
};