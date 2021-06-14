let randomDay = () => Random.int(365);

let createSample = n => {
  let rec createSampleFn = (n, list) => {
    switch(n) {
    | 0 => list
    | _ => createSampleFn(n - 1, [randomDay(), ...list])
    }
  }
  createSampleFn(n, []);
}

let createSamples = (size, num) => {
  let rec createSamplesFn = (num, list) => {
    switch(num) {
    | 0 => list
    | _ => createSamplesFn(num - 1, [createSample(size), ...list])
    }
  }
  createSamplesFn(num, []);
}

let rec hasDuplicates = list => {
  switch(list) {
  | [] => false
  | [x, ...xs] => List.mem(x, xs) ? true : hasDuplicates(xs)
  }
}

let numDuplicates = list => {
  let rec numDuplicatesFn = (list, count) => {
    switch(list) {
    | [] => count
    | [x, ...xs] => numDuplicatesFn(xs, count + (hasDuplicates(x) ? 1 : 0))
    }
  }
  numDuplicatesFn(list, 0);
}

let simulate = iterations => {
  /* initialization */
  let start = Unix.gettimeofday();
  let sampleSize = 23;
  Random.self_init();

  /* generate data */
  let percent = iterations
    |> createSamples(sampleSize)
    |> numDuplicates
    |> float_of_int
    |> x => x /. float_of_int(iterations)
    |> x => x *. float_of_int(100);

  /* output */
  Printf.printf("iterations: %d\n", iterations);
  Printf.printf("sample-size: %d\n", sampleSize);
  Printf.printf("percent: %.2f\n", percent);
  let fin = Unix.gettimeofday();
  let seconds = fin -. start;
  Printf.printf("seconds: %.3f\n", seconds);
}
