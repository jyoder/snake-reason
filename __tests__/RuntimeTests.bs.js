// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/src/jest.js");
var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Runtime$Snake = require("../src/Runtime.bs.js");

function _stop(calls, param) {
  calls[0] = /* :: */[
    /* Control */Block.__(0, [/* Stop */0]),
    calls[0]
  ];
  return /* () */0;
}

function _runtimeContext(calls) {
  return /* record */[
          /* start */(function (run) {
              calls[0] = /* :: */[
                /* Control */Block.__(0, [/* Start */Block.__(0, [run])]),
                calls[0]
              ];
              return (function (param) {
                  return _stop(calls, param);
                });
            }),
          /* listen */(function (handleKey) {
              calls[0] = /* :: */[
                /* Control */Block.__(0, [/* Listen */Block.__(1, [handleKey])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* setColor */(function (color) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* SetColor */Block.__(0, [color])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* setTextAlign */(function (alignment) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* SetTextAlign */Block.__(1, [alignment])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* setFont */(function (font) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* SetFont */Block.__(2, [font])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* fillRect */(function (point, dimensions) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* FillRect */Block.__(3, [
                        point,
                        dimensions
                      ])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* fillText */(function (string, point) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* FillText */Block.__(4, [
                        string,
                        point
                      ])]),
                calls[0]
              ];
              return /* () */0;
            }),
          /* clear */(function (color) {
              calls[0] = /* :: */[
                /* Command */Block.__(1, [/* Clear */Block.__(5, [color])]),
                calls[0]
              ];
              return /* () */0;
            })
        ];
}

function _run(commands, keyPresses, keyPress) {
  if (keyPress !== undefined) {
    keyPresses[0] = /* :: */[
      keyPress,
      keyPresses[0]
    ];
  }
  return /* record */[
          /* nextRun */undefined,
          /* commands */commands
        ];
}

Jest.describe("start", (function (param) {
        Jest.test("listens for and uses key presses in each run of the game loop", (function (param) {
                var calls = /* record */[/* contents : [] */0];
                var keyPresses = /* record */[/* contents : [] */0];
                Runtime$Snake.start(_runtimeContext(calls), (function (param) {
                        return _run(/* [] */0, keyPresses, param);
                      }));
                var match = List.rev(calls[0]);
                if (match) {
                  var match$1 = match[0];
                  if (!match$1.tag) {
                    var match$2 = match$1[0];
                    if (typeof match$2 !== "number") {
                      if (match$2.tag) {
                        var match$3 = match[1];
                        if (match$3) {
                          var match$4 = match$3[0];
                          if (!match$4.tag) {
                            var match$5 = match$4[0];
                            if (typeof match$5 !== "number") {
                              if (!match$5.tag) {
                                if (!match$3[1]) {
                                  Curry._1(match$2[0], /* ArrowUp */2);
                                  Curry._1(match$5[0], /* () */0);
                                }
                                
                              }
                              
                            }
                            
                          }
                          
                        }
                        
                      }
                      
                    }
                    
                  }
                  
                }
                return Jest.Expect[/* toEqual */12](/* :: */[
                            /* ArrowUp */2,
                            /* [] */0
                          ], Jest.Expect[/* expect */0](keyPresses[0]));
              }));
        Jest.test("stops when there is no next run", (function (param) {
                var calls = /* record */[/* contents : [] */0];
                var keyPresses = /* record */[/* contents : [] */0];
                Runtime$Snake.start(_runtimeContext(calls), (function (param) {
                        return _run(/* [] */0, keyPresses, param);
                      }));
                var match = List.rev(calls[0]);
                if (match) {
                  var match$1 = match[0];
                  if (!match$1.tag) {
                    var match$2 = match$1[0];
                    if (typeof match$2 !== "number") {
                      if (match$2.tag) {
                        var match$3 = match[1];
                        if (match$3) {
                          var match$4 = match$3[0];
                          if (!match$4.tag) {
                            var match$5 = match$4[0];
                            if (typeof match$5 !== "number") {
                              if (!match$5.tag) {
                                if (!match$3[1]) {
                                  var run = match$5[0];
                                  Curry._1(match$2[0], /* ArrowUp */2);
                                  Curry._1(run, /* () */0);
                                  Curry._1(run, /* () */0);
                                }
                                
                              }
                              
                            }
                            
                          }
                          
                        }
                        
                      }
                      
                    }
                    
                  }
                  
                }
                var match$6 = List.hd(calls[0]);
                var stopped;
                stopped = match$6.tag || typeof match$6[0] !== "number" ? false : true;
                return Jest.Expect[/* toEqual */12](true, Jest.Expect[/* expect */0](stopped));
              }));
        return Jest.test("executes all render commands", (function (param) {
                      var calls = /* record */[/* contents : [] */0];
                      var keyPresses = /* record */[/* contents : [] */0];
                      Runtime$Snake.start(_runtimeContext(calls), (function (param) {
                              return _run(/* :: */[
                                          /* SetColor */Block.__(0, [/* Green */1]),
                                          /* :: */[
                                            /* SetTextAlign */Block.__(1, [/* Center */0]),
                                            /* :: */[
                                              /* SetFont */Block.__(2, [/* Title */0]),
                                              /* :: */[
                                                /* FillRect */Block.__(3, [
                                                    /* record */[
                                                      /* x */3,
                                                      /* y */4
                                                    ],
                                                    /* record */[
                                                      /* width */5,
                                                      /* height */6
                                                    ]
                                                  ]),
                                                /* :: */[
                                                  /* FillText */Block.__(4, [
                                                      "hello",
                                                      /* record */[
                                                        /* x */1,
                                                        /* y */2
                                                      ]
                                                    ]),
                                                  /* :: */[
                                                    /* Clear */Block.__(5, [/* White */0]),
                                                    /* [] */0
                                                  ]
                                                ]
                                              ]
                                            ]
                                          ]
                                        ], keyPresses, param);
                            }));
                      var match = List.rev(calls[0]);
                      if (match) {
                        var match$1 = match[1];
                        if (match$1) {
                          var match$2 = match$1[0];
                          if (!match$2.tag) {
                            var match$3 = match$2[0];
                            if (typeof match$3 !== "number") {
                              if (!match$3.tag) {
                                if (!match$1[1]) {
                                  Curry._1(match$3[0], /* () */0);
                                }
                                
                              }
                              
                            }
                            
                          }
                          
                        }
                        
                      }
                      return Jest.Expect[/* toEqual */12](/* :: */[
                                  /* Command */Block.__(1, [/* SetColor */Block.__(0, [/* Green */1])]),
                                  /* :: */[
                                    /* Command */Block.__(1, [/* SetTextAlign */Block.__(1, [/* Center */0])]),
                                    /* :: */[
                                      /* Command */Block.__(1, [/* SetFont */Block.__(2, [/* Title */0])]),
                                      /* :: */[
                                        /* Command */Block.__(1, [/* FillRect */Block.__(3, [
                                                /* record */[
                                                  /* x */3,
                                                  /* y */4
                                                ],
                                                /* record */[
                                                  /* width */5,
                                                  /* height */6
                                                ]
                                              ])]),
                                        /* :: */[
                                          /* Command */Block.__(1, [/* FillText */Block.__(4, [
                                                  "hello",
                                                  /* record */[
                                                    /* x */1,
                                                    /* y */2
                                                  ]
                                                ])]),
                                          /* :: */[
                                            /* Command */Block.__(1, [/* Clear */Block.__(5, [/* White */0])]),
                                            /* [] */0
                                          ]
                                        ]
                                      ]
                                    ]
                                  ]
                                ], Jest.Expect[/* expect */0](List.tl(List.tl(List.rev(calls[0])))));
                    }));
      }));

exports._stop = _stop;
exports._runtimeContext = _runtimeContext;
exports._run = _run;
/*  Not a pure module */
