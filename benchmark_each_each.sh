#!/bin/bash

join_arr() {
  local IFS="$1"
  shift
  echo "$*"
}

# other algorithms need special treatment: greedy, python ones and julia ones
algorithms=( hungarian hungarian_sp min_cost nosolve munkres )
calgorithms=$(join_arr , "${algorithms[@]}")

instances=( 10 40 160 640 10g 40g 160g 640g 10h 40h 160h 640h 10t 40t 160t 640t 10w 40w 160w 640w 10s 40s 160s 640s )

for instance in "${instances[@]}"
do
    echo "+++ testing on instance: instances/$instance.mm +++"
    hyperfine -L alg $calgorithms "{alg}/lsap_solver instances/$instance.mm test.sol" --export-json benchmarks/bundle_$instance.json
done

greedy_instances=( 10 10g 10h 10t 10w 10s )
for instance in "${greedy_instances[@]}"
do
    echo "+++ testing on instance: instances/$instance.mm +++"
    hyperfine "greedy/lsap_solver instances/$instance.mm test.sol" --export-json benchmarks/greedy_$instance.json
done

for instance in "${instances[@]}"
do
    echo "+++ testing on instance: instances/$instance.mm +++"
    hyperfine "python3 hungarian_scipy/main.py instances/$instance.mm test.sol" --export-json benchmarks/scipy_$instance.json
done