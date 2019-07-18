let borderStyle = "2px solid black";
let itemDimension = "96px";

let styles =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flexWrap="wrap",
    ~border=borderStyle,
    ~width="calc(96px * 3 + 4px)",
    (),
  );

let stylesItem =
  ReactDOMRe.Style.make(
    ~height=itemDimension,
    ~width=itemDimension,
    ~display="flex",
    ~alignItems="center",
    ~justifyContent="center",
    ~cursor="pointer",
    (),
  );
let stylesItemRight = ReactDOMRe.Style.make(~borderRight=borderStyle, ());
let stylesItemTop = ReactDOMRe.Style.make(~borderTop=borderStyle, ());

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
  | [Right] => stylesItemRight
  | [Top] => stylesItemTop
  | [first, second] =>
    ReactDOMRe.Style.combine(
      bordersToStyle([first]),
      bordersToStyle([second]),
    )
  | _ => ReactDOMRe.Style.make()
  };

let getItemStyle = id => id->calculateBorder->bordersToStyle;

[@react.component]
let make = () => {
  <div style=styles>
    {[1, 2, 3, 4, 5, 6, 7, 8, 9]
     |> List.map(x =>
          <div
            key={string_of_int(x)}
            style={ReactDOMRe.Style.combine(stylesItem, getItemStyle(x))}>
            {string_of_int(x) |> React.string}
          </div>
        )
     |> Array.of_list
     |> React.array}
  </div>;
};