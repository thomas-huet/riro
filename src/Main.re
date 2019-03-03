let component = ReasonReact.statelessComponent("Main");

let make = (_children) => {
  ...component,
  render: _self => <Board options=Game.default_options/>
};