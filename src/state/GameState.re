type player =
  | X
  | O;

let playerToString = player =>
  switch (player) {
  // | X => {j|╳|j}
  // | O => {j|◯|j}
  | X => {j|X|j}
  | O => {j|O|j}
  };

type status =
  | Unfinished
  | Win(player)
  | Tie;

type square = option(player);

type state = {
  currentPlayer: player,
  board: list(square),
  status,
};

type action =
  | Move(int)
  | Clear;

let makeBoard = () => [None, None, None, None, None, None, None, None, None];

let checkStatus = (board: list(square)): status =>
  switch (board) {
  | [Some(X), Some(X), Some(X), _, _, _, _, _, _] => Win(X)
  | [_, _, _, Some(X), Some(X), Some(X), _, _, _] => Win(X)
  | [_, _, _, _, _, _, Some(X), Some(X), Some(X)] => Win(X)
  | [Some(X), _, _, Some(X), _, _, Some(X), _, _] => Win(X)
  | [_, Some(X), _, _, Some(X), _, _, Some(X), _] => Win(X)
  | [_, _, Some(X), _, _, Some(X), _, _, Some(X)] => Win(X)
  | [Some(X), _, _, _, Some(X), _, _, _, Some(X)] => Win(X)
  | [_, _, Some(X), _, Some(X), _, Some(X), _, _] => Win(X)

  | [Some(O), Some(O), Some(O), _, _, _, _, _, _] => Win(O)
  | [_, _, _, Some(O), Some(O), Some(O), _, _, _] => Win(O)
  | [_, _, _, _, _, _, Some(O), Some(O), Some(O)] => Win(O)
  | [Some(O), _, _, Some(O), _, _, Some(O), _, _] => Win(O)
  | [_, Some(O), _, _, Some(O), _, _, Some(O), _] => Win(O)
  | [_, _, Some(O), _, _, Some(O), _, _, Some(O)] => Win(O)
  | [Some(O), _, _, _, Some(O), _, _, _, Some(O)] => Win(O)
  | [_, _, Some(O), _, Some(O), _, Some(O), _, _] => Win(O)

  | [
      Some(_),
      Some(_),
      Some(_),
      Some(_),
      Some(_),
      Some(_),
      Some(_),
      Some(_),
      Some(_),
    ] =>
    Tie

  | _ => Unfinished
  };

let make = (): state => {
  currentPlayer: X,
  status: Unfinished,
  board: makeBoard(),
};

let reducer = (state, action) =>
  switch (action) {
  | Move(position) when state.status === Unfinished =>
    let board =
      state.board
      |> List.mapi((index, x) =>
           index === position ? Some(state.currentPlayer) : x
         );
    let status = checkStatus(board);
    let currentPlayer = state.currentPlayer === X ? O : X;
    {currentPlayer, status, board};
  | Move(_) => state

  | Clear => make()
  };