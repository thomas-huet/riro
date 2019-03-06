open Game;
open State;

[@bs.val]
external add_keyboard_event_listener :
  (string, ReactEvent.Keyboard.t => unit) => unit =
  "addEventListener";

let component = ReasonReact.reducerComponent("Main");

let make = (_children) => {
  ...component,
  initialState: () => init(generate(default_options), default_options),
  reducer: (action, state) => switch(action) {
  | Open_settings => ReasonReact.Update({...state, settings_open: true})
  | Change_settings(opts) => ReasonReact.Update({...state, options: opts})
  | New => ReasonReact.Update(init(generate(state.options), state.options))
  | Restart => ReasonReact.Update(init(state.start, state.options))
  | Select_robot(r) => ReasonReact.Update({...state, selected_robot: r})
  | Move((r, dir)) => if (r < 0 && state.selected_robot < 0) {
      ReasonReact.NoUpdate
    } else {
      let m = (r >= 0 ? r : state.selected_robot, dir);
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
  didMount: ({send}) =>
    add_keyboard_event_listener("keydown", (event) => {
      open ReactEvent.Keyboard;
      if (!altKey(event) && !ctrlKey(event) && !metaKey(event) && !shiftKey(event)) {
        switch(key(event)) {
        | "ArrowDown" => send(Move((-1, Down)))
        | "ArrowLeft" => send(Move((-1, Left)))
        | "ArrowRight" => send(Move((-1, Right)))
        | "ArrowUp" => send(Move((-1, Up)))
        | _ => ()
        }
      }
    }),
  render: ({state, send}) =>
    if (state.settings_open) {
      <Settings send=send opts=state.options/>
    } else if (winning(state.current)) {
      <EndMenu send=send num_moves={List.length(state.moves)}/>
    } else {
      <div id="main">
        <Menu send=send/>
        <Board send=send board_state=state.current selected_robot=state.selected_robot/>
      </div>
    }
};
