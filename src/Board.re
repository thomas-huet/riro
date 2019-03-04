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

let string = string_of_float;

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
  render: self => {
    let height = Array.length(self.state.current.grid);
    let width = Array.length(self.state.current.grid[0]);
    let grid = {
      let vertical = Array.init(width + 1, (i) => <line x1={string_of_int(i)} y1 ="-0.025" x2={string_of_int(i)} y2={string(float(height) +. 0.025)} stroke="black" strokeWidth="0.05"/>);
      let horizontal = Array.init(height + 1, (i) => <line x1="-0.025" y1 ={string_of_int(i)} x2={string(float(width) +. 0.025)} y2={string_of_int(i)} stroke="black" strokeWidth="0.05"/>);
      let walls = Array.map(((y, x)) => <rect x={string_of_int(x)} y={string_of_int(y)} height="1" width="1"/>, Game.get_walls(self.state.current.grid));
      <g>
        <g> ...vertical </g>
        <g> ...horizontal </g>
        <g> ...walls </g>
      </g>
    };
    let robots = Array.mapi((i, (y, x)) => <rect x={string(float(x) +. 0.1)} y={string(float(y) +. 0.1)} height="0.8" width="0.8" fill={i == 0 ? "red" : "blue"}/>, self.state.current.robots);
    let target = {
      let (y, x) = self.state.current.target;
      <rect x={string(float(x) +. 0.05)} y ={string(float(y) +. 0.05)} height="0.9" width="0.9" stroke="red" strokeWidth="0.1" fill="none"/>
    };
    <svg viewBox={"-0.1 -0.1 " ++ string(float(width) +. 0.2) ++ " " ++ string(float(height) +. 0.2)} xmlns="http://www.w3.org/2000/svg">
      target
      grid
      <g> ...robots </g>
    </svg>
  }
};