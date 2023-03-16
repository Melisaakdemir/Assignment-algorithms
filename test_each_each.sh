#!/bin/bash

algorithms=( hungarian hungarian_sp min_cost nosolve munkres)
instances=( 10 40 160 640 10g 40g 160g 640g 10h 40h 160h 640h 10t 40t 160t 640t 10w 40w 160w 640w 10s 40s 160s 640s )

for instance in "${instances[@]}"
do
    echo "+++ testing on instance: instances/$instance.mm +++"
    for algorithm in "${algorithms[@]}"
    do
        echo "  +++ running $algorithm on instances/$instance.mm +++"
        $algorithm/lsap_solver instances/$instance.mm test.sol
        python3 instances/check_sol.py compare instances/$instance test.sol
    done
done