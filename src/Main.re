open Game;
open State;

let component = ReasonReact.reducerComponent("Main");

let make = (_children) => {
  ...component,
  initialState: () => init(generate(default_options), default_options),
  reducer: (action, state) => switch(action) {
  | Set_options(opts) => ReasonReact.Update(init(generate(opts), opts))
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
  render: self => {
    <>
      {Menu.render(self)}
      {Board.render(self.state.current)}
    </>
  }
};