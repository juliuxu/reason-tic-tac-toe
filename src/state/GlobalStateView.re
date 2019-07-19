let jSONStringifyDebugInfo = _object => {
  _object;
  let result: string = [%bs.raw
    {|
    // https://github.com/BuckleScript/bucklescript/blob/master/jscomp/runtime/caml_chrome_debugger.ml#L139
    JSON.stringify(_object, (key, value) => {
      const log = false ? console.log : () => {};
      if (value === undefined) {
        log("Undefined value for key", key);
        return value
      };
      if (value[Symbol.for('BsRecord')] !== undefined) {
        log("BsRecord", value);
        return value[Symbol.for('BsRecord')]
          .reduce((acc, x, index) => ({ ...acc, [x]: value[index] }), {});
      } else if (value[Symbol.for('BsVariant')] !== undefined) {
        log("BsVariant", value);

        const rec = (acc, x) => {
          if (!x) return acc;
          return rec([...acc, x[0]], x[1]);
        };
        return rec([], value);
      } else if (value[Symbol.for('BsLocalModule')] !== undefined) {
        log("BsLocalModule");
        return value; // TODO
      } else if (value[Symbol.for('BsPolyVar')] !== undefined) {
        log("BsPolyVar");
        return value; // TODO
      }
      return value;
    }, 2)
    |}
  ];
  result;
};

[@react.component]
let make = () => {
  let globalState = React.useContext(GlobalStateProvider.stateContext);
  let stringified = jSONStringifyDebugInfo(globalState);
  Js.log2("[GlobalStateView]", globalState);
  // Js.log2("[GlobalStateView]", stringified);
  <pre> {stringified |> React.string} </pre>;
};