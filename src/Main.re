open Game;
open State;

let component = ReasonReact.reducerComponent("Main");

let make = (_children) => {
  ...component,
  initialState: () => init(generate(default_options), default_options),
  reducer: (action, state) => switch(action) {
  | Open_settings => ReasonReact.Update({...state, settings_open: true})
  | Change_settings(opts) => ReasonReact.Update({...state, options: opts})
  | New => ReasonReact.Update(init(generate(state.options), state.options))
  | Restart => ReasonReact.Update(init(state.start, state.options))
  | Move(m) => {
      switch(move(state.current, m)) {
        | None => ReasonReact.NoUpdate
        | Some(position) =>
          ReasonReact.Update({...state,
            current: position,
            moves: [m, ...state.moves],
          })
      }
    }
  },
  render: ({state, send}) =>
    if (state.settings_open) {
      <Settings send=send opts=state.options/>
    } else {
      <>
        <Menu send=send/>
        <Board board_state=state.current/>
      </>
    }
};