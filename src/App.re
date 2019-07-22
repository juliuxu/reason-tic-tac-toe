let styles =
  ReactDOMRe.Style.make(
    ~font="14px \"Century Gothic\", Futura, sans-serif",
    ~display="flex",
    ~flexDirection="column",
    ~alignItems="center",
    (),
  );

type todo = {
  finished: bool,
  name: string,
};
let todos = [
  {finished: true, name: "State debug"},
  {finished: true, name: "State"},
  {finished: true, name: "Playable"},
  {finished: true, name: "Local multiplayer"},
  {finished: false, name: "Highscore"},
  {finished: false, name: "Human vs Bot"},
  {finished: false, name: "Networked multiplayer!"},
];

[@react.component]
let make = () => {
  <GlobalStateProvider>
    <div style=styles>
      <h1> {"Tic Tac Toe" |> React.string} </h1>
      // Status
      <h2>
        <GlobalStateProvider.Consumer>
          ...{state =>
            (
              switch (state.gameState.status) {
              | GameState.Unfinished(player) =>
                GameState.playerToString(player) ++ " to move"
              | GameState.Tie => "It's a tie"
              | GameState.Win(player) =>
                {j|🎉|j}
                ++ GameState.playerToString(player)
                ++ {j| Wins 👏|j}
              }
            )
            |> React.string
          }
        </GlobalStateProvider.Consumer>
      </h2>
      <Board />
      <Notification.Provider />
      // Actions
      <GlobalStateProvider.DispatchConsumer>
        ...{dispatch =>
          <div style={ReactDOMRe.Style.make(~marginTop="16px", ())}>
            <button onClick={_ => dispatch(GameState.Clear)}>
              {{j|👉New Game|j} |> React.string}
            </button>
          </div>
        }
      </GlobalStateProvider.DispatchConsumer>
      <h3> {"Debug" |> React.string} </h3>
      <GlobalStateView />
      <h3> {"Todos" |> React.string} </h3>
      <ul style={ReactDOMRe.Style.make(~margin="", ())}>
        {todos
         |> List.map(todo =>
              <li key={todo.name}>
                {{todo.finished ? {js|✅|js} : {js|☐|js}} |> React.string}
                {todo.name |> React.string}
              </li>
            )
         |> Array.of_list
         |> React.array}
      </ul>
    </div>
  </GlobalStateProvider>;
};