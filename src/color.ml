let show (r, g, b) = Printf.sprintf "#%02x%02x%02x" r g b

let colors =[|
224, 0, 0;
0, 224, 0;
0, 0, 224;
224, 224, 0;
0, 224, 224;
224, 0, 224;
|]

let get n i =
  if i < 6 then
    show colors.(i)
  else
    let i = i - 6 in
    let m = (n - 1) / 6 in
    let a, b, c = 224, 224 * (i / 6 + 1) / (m + 1), 0 in
    let r, g, b = match i mod 6 with
      | 0 -> a, b, c
      | 1 -> b, c, a
      | 2 -> c, a, b
      | 3 -> c, b, a
      | 4 -> b, a, c
      | 5 -> a, c, b
    in
    show (r, g, b)
