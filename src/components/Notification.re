type notification = {
  message: React.element,
  timeout: int,
};

type eventEmitter = {
  .
  register: (notification => unit) => unit,
  unregister: unit => unit,
  call: notification => unit,
};

let eventEmitter: eventEmitter = {
  val callback = ref(_ => ());
  pub register = callback => {
    this#setCallback(callback);
  };
  pub unregister = () => this#setCallback(_ => ());
  pub call = (args: notification) => callback^(args);
  pri setCallback = x => callback := x
};

module View = {
  [@react.component]
  let make = (~message) => {
    <div> message </div>;
  };
};

module Provider = {
  [@react.component]
  let make = () => {
    let (state, setState) = React.useState(() => []);
    React.useEffect1(
      () => {
        eventEmitter#register(notification => {
          setState(state => state @ [notification]);
          ();
        });
        Some(eventEmitter#unregister);
      },
      [||],
    );

    <>
      {state
       |> List.mapi((index, notification) =>
            <View key={string_of_int(index)} message={notification.message} />
          )
       |> Array.of_list
       |> React.array}
    </>;
  };
};

let addMessage = (~message, ~timeout=2000, ()) => {
  eventEmitter#call({message, timeout});
};