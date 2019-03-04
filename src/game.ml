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
  min_num_moves = 4;
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

let move position (r, d) =
  let height = Array.length position.grid in
  let width = Array.length position.grid.(0) in
  let y, x = position.robots.(r) in
  let i, j = coord_of_dir d in
  let is_empty a b =
    a >= 0 && a < height && b >= 0 && b < width
    && position.grid.(a).(b) = Empty
  in
  if not (is_empty (y + i) (x + j)) then
    None
  else begin
    let grid = Array.map Array.copy position.grid in
    grid.(y).(x) <- Empty;
    let robots = Array.copy position.robots in
    let rec find_stop m =
      if is_empty (y + m * i) (x + m * j) then
        find_stop (m + 1)
      else
        y + (m - 1) * i, x + (m - 1) * j
    in
    let y, x = find_stop 2 in
    robots.(r) <- y, x;
    grid.(y).(x) <- Robot r;
    Some { position with grid; robots }
  end

let winning position =
  position.robots.(0) = position.target

let find_solution position depth =
  let q = Queue.create () in
  let h = Hashtbl.create 5 in
  Queue.push (depth, position) q;
  Hashtbl.add h position ();
  let rec explore () =
    if Queue.is_empty q then None else
    let depth, position = Queue.pop q in
    if winning position then
      Some ()
    else begin
      if depth > 0 then begin
        let try_move m = match move position m with
        | None -> ()
        | Some position ->
          try Hashtbl.find h position with
          Not_found -> begin
            Queue.push (depth - 1, position) q;
            Hashtbl.add h position ();
          end
        in
        for i = 0 to Array.length position.robots - 1 do
          List.iter (fun d -> try_move (i, d)) [Up; Down; Left; Right]
        done
      end;
      explore ()
    end
  in
  explore ()

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
