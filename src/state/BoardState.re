type value =
  | X
  | O
  | Empty;

type state = (value, value, value, value, value, value, value, value, value);

let checkWinner = (board: state): value =>
  switch (board) {
  | (X, X, X, _, _, _, _, _, _) => X
  | (_, _, _, X, X, X, _, _, _) => X
  | (_, _, _, _, _, _, X, X, X) => X
  | (X, _, _, X, _, _, X, _, _) => X
  | (_, X, _, _, X, _, _, X, _) => X
  | (_, _, X, _, _, X, _, _, X) => X
  | (X, _, _, _, X, _, _, _, X) => X
  | (_, _, X, _, X, _, X, _, _) => X

  | (O, O, O, _, _, _, _, _, _) => O
  | (_, _, _, O, O, O, _, _, _) => O
  | (_, _, _, _, _, _, O, O, O) => O
  | (O, _, _, O, _, _, O, _, _) => O
  | (_, O, _, _, O, _, _, O, _) => O
  | (_, _, O, _, _, O, _, _, O) => O
  | (O, _, _, _, O, _, _, _, O) => O
  | (_, _, O, _, O, _, O, _, _) => O

  | _ => Empty
  };

let make = (): state => (
  Empty,
  Empty,
  Empty,
  Empty,
  Empty,
  Empty,
  Empty,
  Empty,
  Empty,
);