open Game;
open State;

let component = ReasonReact.statelessComponent("Settings");

let make = (~send, ~opts, _children) => {
  ...component,
  render: (_self) => {
    let onHeightChange = (event) => send(Change_settings({...opts, height: ReactEvent.Form.target(event)##value}));
    let onWidthChange = (event) => send(Change_settings({...opts, width: ReactEvent.Form.target(event)##value}));
    let onNumRobotsChange = (event) => send(Change_settings({...opts, num_robots: ReactEvent.Form.target(event)##value}));
    let onNumWallsChange = (event) => send(Change_settings({...opts, num_walls: ReactEvent.Form.target(event)##value}));
    let onMinNumMovesChange = (event) => send(Change_settings({...opts, min_num_moves: ReactEvent.Form.target(event)##value}));
    <div id="settings">
      <div className="line">
        <label>{ReasonReact.string("Height:")}</label>
        <input type_="number" min=2 value={string_of_int(opts.height)} onChange=onHeightChange/>
      </div>
      <div className="line">
	<label>{ReasonReact.string("Width:")}</label>
	<input type_="number" min=2 value={string_of_int(opts.width)} onChange=onWidthChange/>
      </div>
      <div className="line">
	<label>{ReasonReact.string("Number of robots:")}</label>
	<input type_="number" min=1 max={string_of_int(opts.height * opts.width - opts.num_walls - 1)} value={string_of_int(opts.num_robots)} onChange=onNumRobotsChange/>
      </div>
      <div className="line">
	<label>{ReasonReact.string("Number of walls:")}</label>
	<input type_="number" min=0 max={string_of_int(opts.height * opts.width - opts.num_robots - 1)} value={string_of_int(opts.num_walls)} onChange=onNumWallsChange/>
      </div>
      <div className="line">
	<label>{ReasonReact.string("Minimum number of moves:")}</label>
	<input type_="number" min=1 value={string_of_int(opts.min_num_moves)} onChange=onMinNumMovesChange/>
      </div>
      <button onClick={_event => send(New)}> {ReasonReact.string("Apply")} </button>
    </div>
  }
};
