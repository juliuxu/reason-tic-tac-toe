let stateContext = React.createContext(RootState.make());

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(stateContext);