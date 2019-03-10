open Game

type t = {
  start: position;
  current: position;
  selected_robot: int;
  moves: (int * direction) list;
  options: options;
  settings_open: bool;
}

let init position options = {
  start = position;
  current = position;
  selected_robot = -1;
  moves = [];
  options;
  settings_open = false;
}

type action =
| Open_settings
| Close_settings
| Change_settings of options
| New
| Restart
| Select_robot of int
| Move of (int * direction)
