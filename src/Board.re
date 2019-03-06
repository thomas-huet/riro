open Game;

let string = string_of_float;

let component = ReasonReact.statelessComponent("Board");

let make = (~board_state, ~selected_robot, ~send, _children) => {
  ...component,
  render: (_self) => {
    let height = Array.length(board_state.grid);
    let width = Array.length(board_state.grid[0]);
    let grid = {
      let vertical = Array.init(width + 1, (i) => <line x1={string_of_int(i)} y1 ="0" x2={string_of_int(i)} y2={string_of_int(height)} stroke="black" strokeWidth="0.02"/>);
      let horizontal = Array.init(height + 1, (i) => <line x1="0" y1 ={string_of_int(i)} x2={string_of_int(width)} y2={string_of_int(i)} stroke="black" strokeWidth="0.02"/>);
      let walls = Array.map(((y, x)) => <rect x={string_of_int(x)} y={string_of_int(y)} height="1" width="1"/>, Game.get_walls(board_state.grid));
      <g>
        <rect x="0" y="0" height={string_of_int(height)} width={string_of_int(width)} stroke="black" strokeWidth="0.05" fill="none"/>
        <g> ...vertical </g>
        <g> ...horizontal </g>
        <g> ...walls </g>
      </g>
    };
    let robots =
      Array.mapi(
        (i, (y, x)) => <Robot x=x y=y id=i num_robots={Array.length(board_state.robots)} send_parent=send/>,
        board_state.robots);
    let target = {
      let (y, x) = board_state.target;
      <rect x={string(float(x) +. 0.05)} y ={string(float(y) +. 0.05)} height="0.9" width="0.9" stroke={Color.get(0, 0)} strokeWidth="0.1" fill="none"/>
    };
    let selection = if (selected_robot >= 0) {
      let (y,x) = board_state.robots[selected_robot];
      <circle cx={string(float(x) +. 0.5)} cy={string(float(y) +. 0.5)} r="0.1" fill="white"/>
    } else {ReasonReact.null};
    <svg viewBox={"-0.1 -0.1 " ++ string(float(width) +. 0.2) ++ " " ++ string(float(height) +. 0.2)} xmlns="http://www.w3.org/2000/svg">
      target
      grid
      <g> ...robots </g>
      selection
    </svg>
  }
};