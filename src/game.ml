type options = {  
  num_robots : int;
  height : int;
  width : int;
  num_walls : int;
  min_num_moves : int;
}

let default_options = {
  num_robots = 4;
  height = 6;
  width = 6;
  num_walls = 6;
  min_num_moves = 4;
}

type position = {
  grid : bool array array;
  target : int * int;
  robots : (int * int) array;
}

let generate opts =
  let grid = Array.make_matrix opts.height opts.width true in
  let target = 0, 0 in
  let robots = [||] in
  { grid; target; robots }

type direction = Up | Down | Left | Right

type move = int * direction

let move position m =
  None