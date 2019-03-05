open State;

let component = ReasonReact.statelessComponent("Menu");

let make = (~send, _children) => {
  ...component,
  render: (_self) =>
    <div id="menu">
      <button onClick={_event => send(Restart)}> {ReasonReact.string("Restart")} </button>
      <button onClick={_event => send(New)}> {ReasonReact.string("New")} </button>
      <button onClick={_event => send(Open_settings)}> {ReasonReact.string("Settings")} </button>
    </div>
};
