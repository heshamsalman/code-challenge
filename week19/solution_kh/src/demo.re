let (--) i j => {
  let rec aux n acc => n < i ? acc : aux (n - 1) [n, ...acc];
  aux (j - 1) []
};

let (---) i j => {
  let rec aux n acc => n < i ? acc : aux (n - 1) [n, ...acc];
  aux j []
};

type moveDirection =
  | NNW
  | NNE
  | ENE
  | ESE
  | SSE
  | SSW
  | WSW
  | WNW;

let directions = [NNW, NNE, ENE, ESE, SSE, SSW, WSW, WNW];

type coordinate = (int, int);

let getValidMoves n ((x, y): coordinate) => {
  let aux direction =>
    switch direction {
    | NNW => x - 1 >= 0 && y - 2 >= 0 ? (x - 1, y - 2) : ((-1), (-1))
    | NNE => x + 1 < n && y - 2 >= 0 ? (x + 1, y - 2) : ((-1), (-1))
    | ENE => x + 2 < n && y - 1 >= 0 ? (x + 2, y - 1) : ((-1), (-1))
    | ESE => x + 2 < n && y + 1 < n ? (x + 2, y + 1) : ((-1), (-1))
    | SSE => x + 1 < n && y + 2 < n ? (x + 1, y + 2) : ((-1), (-1))
    | SSW => x - 1 >= 0 && y + 2 < n ? (x - 1, y + 2) : ((-1), (-1))
    | WSW => x - 2 >= 0 && y + 1 < n ? (x - 2, y + 1) : ((-1), (-1))
    | WNW => x - 2 >= 0 && y - 1 >= 0 ? (x - 2, y - 1) : ((-1), (-1))
    };
  let validMapPositions: list coordinate = List.map aux directions;
  List.fold_left
    (fun (agg: list coordinate) (x: coordinate) => fst x == (-1) ? agg : [x, ...agg])
    ([]: list coordinate)
    validMapPositions
};

let willHeDie n k x y => {
  let rec expandMoves (k: int) (position: coordinate) (movesToExpand: list coordinate) =>
    switch k {
    | 0 => movesToExpand
    | _ =>
      let validMoves = getValidMoves n position;
      expandMoves (k - 1) position (List.concat [validMoves, movesToExpand])
    };
  let initialPosition = (x, y);
  let allPositions: list coordinate = expandMoves k initialPosition [];
  float_of_int (List.length allPositions)
  /. float_of_int (List.length directions)
  *\* float_of_int k
};

print_endline (string_of_float (willHeDie 3 2 0 0));
