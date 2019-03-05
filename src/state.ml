open Game

type t = {
  start: position;
  current: position;
  moves: move list;
  options: options;
  settings_open: bool;
}

let init position options = {
  start = position;
  current = position;
  moves = [];
  options;
  settings_open = false;
}

type action =
| Open_settings
| Change_settings of options
| New
| Restart
| Move of move