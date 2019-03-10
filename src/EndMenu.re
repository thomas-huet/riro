open State;

let component = ReasonReact.statelessComponent("EndMenu");

let make = (~send, ~num_moves, _children) => {
  ...component,
  render: (_self) =>
    <div>
      {ReasonReact.string(Printf.sprintf("Congratulations, you won in %d moves.", num_moves))}
      <br/>
      <button onClick={_event => send(Restart)}> {ReasonReact.string("Try to do better")} </button>
      <button onClick={_event => send(New)}> {ReasonReact.string("New game")} </button>
      <button onClick={_event => send(Open_settings)}> {ReasonReact.string("Change settings")} </button>
    </div>
};