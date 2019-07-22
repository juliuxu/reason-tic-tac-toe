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
  | Unfinished(player)
  | Win(player)
  | Tie;

type square = option(player);

type state = {
  board: list(square),
  status,
};

type action =
  | Move(int)
  | Clear;

let makeBoard = () => [None, None, None, None, None, None, None, None, None];

let updateStatus = (state): status =>
  switch (state.board) {
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

  | _ when state.status == Unfinished(X) => Unfinished(O)
  | _ when state.status == Unfinished(O) => Unfinished(X)
  | _ => Unfinished(X)
  };

let make = (): state => {status: Unfinished(X), board: makeBoard()};

let reducer = (state, action) =>
  switch (action, state.status) {
  | (Move(position), Unfinished(player)) =>
    let board =
      state.board
      |> List.mapi((index, x) => index === position ? Some(player) : x);
    let status = updateStatus({...state, board});
    {status, board};

  | (Move(_), _) => state
  | (Clear, _) => make()
  };