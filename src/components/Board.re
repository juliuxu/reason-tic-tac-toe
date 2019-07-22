let borderStyle = "2px solid black";
let squareDimension = "96px";

type styles = {
  root: ReactDOMRe.Style.t,
  square: ReactDOMRe.Style.t,
  squareX: ReactDOMRe.Style.t,
  squareO: ReactDOMRe.Style.t,
  squareRight: ReactDOMRe.Style.t,
  squareTop: ReactDOMRe.Style.t,
};

let styles = {
  root:
    ReactDOMRe.Style.make(
      ~display="flex",
      ~flexWrap="wrap",
      ~border=borderStyle,
      ~width={j|calc($squareDimension * 3 + 4px)|j},
      (),
    ),
  square:
    ReactDOMRe.Style.make(
      ~height=squareDimension,
      ~width=squareDimension,
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="center",
      ~cursor="pointer",
      (),
    ),

  squareX: ReactDOMRe.Style.make(~color="#791E94", ~fontSize="40px", ()),
  squareO: ReactDOMRe.Style.make(~color="#DE6449", ~fontSize="40px", ()),
  squareRight: ReactDOMRe.Style.make(~borderRight=borderStyle, ()),
  squareTop: ReactDOMRe.Style.make(~borderTop=borderStyle, ()),
};
type border =
  | Top
  | Right;

let calculateBorder = id =>
  switch (id) {
  | 1 => [Right]
  | 2 => [Right]
  | 3 => []
  | 4 => [Top, Right]
  | 5 => [Top, Right]
  | 6 => [Top]
  | 7 => [Top, Right]
  | 8 => [Top, Right]
  | 9 => [Top]
  | _ => []
  };

let rec bordersToStyle = borders =>
  switch (borders) {
  | [Right] => styles.squareRight
  | [Top] => styles.squareTop
  | [first, second] =>
    ReactDOMRe.Style.combine(
      bordersToStyle([first]),
      bordersToStyle([second]),
    )
  | _ => ReactDOMRe.Style.make()
  };

let getSquareStyle = id => id->calculateBorder->bordersToStyle;
let getPlayerStyle = player => {
  switch (player) {
  | Some(GameState.X) => styles.squareX
  | Some(GameState.O) => styles.squareO
  | None => ReactDOMRe.Style.make()
  };
};

[@react.component]
let make = () => {
  let globalState = React.useContext(GlobalStateProvider.stateContext);
  let dispatch = React.useContext(GlobalStateProvider.dispatchContext);
  let board = globalState.gameState.board;

  let onSquareClick = (index, _e) => {
    switch (List.nth(board, index), globalState.gameState.status) {
    | (None, Unfinished(_)) => dispatch(GameState.Move(index))
    | (_, _) => ()
    };
  };

  <div style={styles.root}>
    {board
     |> List.mapi((index, x) =>
          <div
            onClick={onSquareClick(index)}
            key={string_of_int(index)}
            style={ReactDOMRe.Style.combine(
              styles.square,
              getSquareStyle(index + 1),
            )}>
            // {string_of_int(index) |> React.string}

              <span style={getPlayerStyle(x)}>
                {(
                   switch (x) {
                   | Some(player) => GameState.playerToString(player)
                   | None => ""
                   }
                 )
                 |> React.string}
              </span>
            </div>
        )
     |> Array.of_list
     |> React.array}
  </div>;
};