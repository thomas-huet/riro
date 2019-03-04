open State;

let render = (self) =>
  <div>
    <button onClick={_event => self.ReasonReact.send(Restart)}> {ReasonReact.string("Restart")} </button>
    <button onClick={_event => self.ReasonReact.send(New)}> {ReasonReact.string("New")} </button>
  </div>;