let stateContext = React.createContext(RootState.make());
let dispatchContext = React.createContext(_action => ());

module Provider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };

  let make = React.Context.provider(stateContext);
};
module Consumer = {
  [@react.component]
  let make = (~children: RootState.state => React.element) => {
    let state = React.useContext(stateContext);
    children(state);
  };
};

module DispatchProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(dispatchContext);
};

module DispatchConsumer = {
  [@react.component]
  let make = (~children) => {
    let dispatch = React.useContext(dispatchContext);
    children(dispatch);
  };
};

[@react.component]
let make = (~children) => {
  let (state, dispatch) =
    React.useReducer(RootState.reducer, RootState.make());
  <DispatchProvider value=dispatch>
    <Provider value=state> children </Provider>
  </DispatchProvider>;
};