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
  num_walls = 4;
  min_num_moves = 3;
}

type cell =
| Empty
| Wall
| Robot of int

type position = {
  grid : cell array array;
  target : int * int;
  robots : (int * int) array;
}

type direction = Up | Down | Left | Right

let coord_of_dir = function
| Up -> -1, 0
| Down -> 1, 0
| Left -> 0, -1
| Right -> 0, 1

type move = int * direction

let move position m =
  None (* TODO *)

let find_solution position depth =
  None (* TODO *)

let exists_path position =
  true (* TODO *)

let () = Random.self_init ()

let rec generate opts =
  let grid = Array.make_matrix opts.height opts.width Empty in
  let rec find_empty () =
    let i = Random.int opts.height and j = Random.int opts.width in
    if grid.(i).(j) = Empty then i, j else find_empty ()
  in
  let rec place_walls n =
    if n > 0 then begin
      let i, j = find_empty () in
      grid.(i).(j) <- Wall;
      place_walls (n - 1)
    end
  in
  place_walls opts.num_walls;
  let target = find_empty () in
  let place_robot r =
    let i, j = find_empty () in
    grid.(i).(j) <- Robot r;
    i, j
  in
  let robots = Array.init opts.num_robots place_robot in
  let position = { grid; target; robots } in
  if exists_path position
  && find_solution position (opts.min_num_moves - 1) = None then
    position
  else
    generate opts

let get_walls grid =
  let walls = ref [] in
  for i = 0 to Array.length grid - 1 do
    for j = 0 to Array.length grid.(0) - 1 do
      if grid.(i).(j) = Wall then
        walls := (i, j) :: !walls
    done
  done;
  Array.of_list !walls