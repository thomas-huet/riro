open Game;
open State;

let component = ReasonReact.reducerComponent("Settings");

let make = (~send_parent, ~opts, _children) => {
  ...component,
  initialState: () => opts,
  reducer: (new_state, _old) => ReasonReact.Update(new_state),
  render: ({state, send}) => {
    let onHeightChange = (event) => send({...state, height: ReactEvent.Form.target(event)##value});
    let onWidthChange = (event) => send({...state, width: ReactEvent.Form.target(event)##value});
    let onNumRobotsChange = (event) => send({...state, num_robots: ReactEvent.Form.target(event)##value});
    let onNumWallsChange = (event) => send({...state, num_walls: ReactEvent.Form.target(event)##value});
    /*let onMinNumMovesChange = (event) => send({...state, min_num_moves: ReactEvent.Form.target(event)##value});*/
    <div id="settings">
      <div className="line">
        <label>{ReasonReact.string("Height:")}</label>
        <input type_="number" min=3 max="99" value={string_of_int(state.height)} onChange=onHeightChange/>
      </div>
      <div className="line">
        <label>{ReasonReact.string("Width:")}</label>
        <input type_="number" min=3 max="99" value={string_of_int(state.width)} onChange=onWidthChange/>
      </div>
      <div className="line">
        <label>{ReasonReact.string("Number of robots:")}</label>
        <input type_="number" min=1 max={string_of_int(min(99, state.height * state.width - state.num_walls - 1))} value={string_of_int(state.num_robots)} onChange=onNumRobotsChange/>
      </div>
      <div className="line">
        <label>{ReasonReact.string("Number of walls:")}</label>
        <input type_="number" min=0 max={string_of_int(min(99, state.height * state.width - state.num_robots - 1))} value={string_of_int(state.num_walls)} onChange=onNumWallsChange/>
      </div>
      /*<div className="line">
        <label>{ReasonReact.string("Minimum number of moves:")}</label>
        <input type_="number" min=1 max="99" value={string_of_int(state.min_num_moves)} onChange=onMinNumMovesChange/>
      </div>*/
      <button onClick={_event => send_parent(Change_settings(state))}> {ReasonReact.string("Apply")} </button>
      <button onClick={_event => send_parent(Close_settings)}> {ReasonReact.string("Cancel")} </button>
    </div>
  }
};
