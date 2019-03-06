open State;

let string = string_of_float;

let component = ReasonReact.reducerComponent("Robot");

let make = (~x, ~y, ~id, ~num_robots, ~send_parent, _children) => {
  ...component,
  initialState: () => (0, 0, 0, 0),
  reducer: (action, _state : (int, int, int, int)) => switch(action) {
  | (x_start, y_start, x_end, y_end) => ReasonReact.Update((x_start, y_start, x_end, y_end))
  },
  render: ({state: (x_start, y_start, x_end, y_end), send}) => {
    let onTouchEnd = (_event) => {
      let horizontal = x_end - x_start;
      let vertical = y_end - y_start;
      if (abs(horizontal) > 2 * abs(vertical) && abs(horizontal) > 10) {
        if (horizontal > 0) {
          send_parent(Move((id, Right)))
        } else {
          send_parent(Move((id, Left)))
        }
      } else if (abs(vertical) > 2 * abs(horizontal) && abs(vertical) > 10) {
        if (vertical > 0) {
          send_parent(Move((id, Down)))
        } else {
          send_parent(Move((id, Up)))
        }
      }
    };
    <rect x={string(float(x) +. 0.1)} y={string(float(y) +. 0.1)} height="0.8" width="0.8" fill={Color.get(num_robots, id)}
      onClick={(_event) => if ((x_start, y_start) == (0, 0)) {send_parent(Select_robot(id))} else {send((0, 0, 0, 0))}}
      onTouchStart={(event) => {
        let touch = ReactEvent.Touch.targetTouches(event)##item(0);
        let x_start = touch##clientX;
        let y_start = touch##clientY;
        send((x_start, y_start, x_start, y_start));
      }}
      onTouchMove={(event) => {
        let touch = ReactEvent.Touch.targetTouches(event)##item(0);
        let x_end = touch##clientX;
        let y_end = touch##clientY;
        send((x_start, y_start, x_end, y_end));
      }}
      onTouchEnd=onTouchEnd
      onTouchCancel=onTouchEnd
    />
  }
}