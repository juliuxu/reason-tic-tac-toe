type state = {gameState: GameState.state};
let reducer = (state, action) => {
  gameState: GameState.reducer(state.gameState, action),
};
let make = () => {gameState: GameState.make()};

// Side-effects
let middlewareReducer = (enhancer, reducer, state, action) => {
  enhancer(state, reducer(state), action);
};

let loggerSideEffects = (_state, next, action) => {
  // Js.log("Logging side effect");
  next(action);
};

let endgameSideEffects = (state, next, action) => {
  let nextState = next(action);
  switch (state.gameState.status, nextState.gameState.status) {
  | (GameState.Unfinished(_), GameState.Win(player)) =>
    Notification.addMessage(
      ~message={
        GameState.playerToString(player) ++ "wins" |> React.string;
      },
      (),
    )
  | (GameState.Unfinished(_), GameState.Tie) =>
    Notification.addMessage(
      ~message={
        "It's a tie" |> React.string;
      },
      (),
    )
  | _ => ()
  };

  nextState;
};

let sideEffects = (state, next) =>
  endgameSideEffects(state) @@ loggerSideEffects(state) @@ next;
let reducer = middlewareReducer(sideEffects, reducer);