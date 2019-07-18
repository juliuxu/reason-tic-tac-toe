let jSONStringifyDebugInfo = _object => {
  _object;
  let result: string = [%bs.raw
    {|
    // https://github.com/BuckleScript/bucklescript/blob/master/jscomp/runtime/caml_chrome_debugger.ml#L139
    JSON.stringify(_object, (key, value) => {
      if (value[Symbol.for('BsRecord')] !== undefined) {
        return value[Symbol.for('BsRecord')]
          .reduce((acc, x, index) => ({ ...acc, [x]: value[index] }), {});
      } else if (value[Symbol.for('BsVariant')] !== undefined) {
        return value; // TODO
      } else if (value[Symbol.for('BsLocalModule')] !== undefined) {
        return value; // TODO
      } else if (value[Symbol.for('BsPolyVar')] !== undefined) {
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