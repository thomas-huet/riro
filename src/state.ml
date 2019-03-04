open Game

type t = {
  start: position;
  current: position;
  moves: move list;
  options: options;
}

let init position options = {
  start = position;
  current = position;
  moves = [];
  options;
}

type action =
| Set_options of options
| New
| Restart
| Move of move