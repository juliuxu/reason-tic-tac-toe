[@react.component]
let make = () => {
  let globalState = React.useContext(GlobalStateProvider.stateContext);
  Js.log2("[GlobalStateView]", globalState);
  <pre>
    {(
       switch (Js.Json.stringifyAny(globalState)) {
       | Some(s) => s
       | None => ""
       }
     )
     |> React.string}
  </pre>;
};