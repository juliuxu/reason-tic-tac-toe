let styles =
  ReactDOMRe.Style.make(
    ~font="14px \"Century Gothic\", Futura, sans-serif",
    ~backgroundColor="#EEEEEE",
    ~height="100vh",
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
  {finished: false, name: "State"},
  {finished: false, name: "Playable"},
  {finished: false, name: "Local multiplayer"},
  {finished: false, name: "Highscore"},
  {finished: false, name: "Human vs Bot"},
  {finished: false, name: "Networked multiplayer!"},
];

[@react.component]
let make = () => {
  <GlobalStateProvider value={RootState.make()}>
    <div style=styles>
      <h1> {"Tic Tac Toe" |> React.string} </h1>
      <Board />
      <h3> {"Todos" |> React.string} </h3>
      <ul style={ReactDOMRe.Style.make(~margin="", ())}>
        {todos
         |> List.map(todo =>
              <li key={todo.name}>
                {{todo.finished ? {js|✅|js} : {js|⟥|js}} |> React.string}
                {todo.name |> React.string}
              </li>
            )
         |> Array.of_list
         |> React.array}
      </ul>
      <h3> {"Debug" |> React.string} </h3>
      <GlobalStateView />
    </div>
  </GlobalStateProvider>;
};