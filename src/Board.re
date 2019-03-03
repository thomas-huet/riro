type action = 
| New(Game.options)
| Restart
| Move(Game.move);

type state = {
  start: Game.position,
  current: Game.position,
  moves: list(Game.move),
};

let start = (position) => {
  start: position,
  current: position,
  moves: [],
};

let component = ReasonReact.reducerComponent("Board");

let make = (~options, _children) => {
  ...component,
  initialState: () => start(Game.generate(options)),
  reducer: (action, state) => switch(action) {
  | New(opts) => ReasonReact.Update(start(Game.generate(opts)))
  | Restart => ReasonReact.Update(start(state.start))
  | Move(m) => {
      switch(Game.move(state.current, m)) {
        | None => ReasonReact.Update(state)
        | Some(position) =>
          ReasonReact.Update({...state,
            current: position,
            moves: [m, ...state.moves],
          })
      }
    }
  },
  render: _self => <svg> </svg>
};