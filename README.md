# Final Project - Linear Sum Assignment Problem

Different Implementations of Solution Algirithms for the Linear Sum Assignment Problem

## Orginisation
The repository consists of the following:
- Files:
  - `main.cpp`: The main code for cpp solutions
  - `matrix.hpp`: Underlying matrix sturcture
  - `problem.{h/c}pp`: Definition of a problem instance
  - `solution.hpp`: Definition of a solution
  - `abstractsolver.hpp`: Definition of a solver
- Directories:
  - `algorithm for algorithm in {greedy, hungarian, hungarian_sp, min_cost, munkres, nosolve}`: Location for specific cpp algorithms with
    - `greedy`: Greedy / Combinatorial method
    - `hungarian`: Hungarian method
    - `hungarian_sp`: Hungarian method using shortest augmenting path
    - `min_cost`: Successive shortest paths algorithm over a flow network
    - `munkres`: Hungarian method
    - `nosolve`: Actually not a solving method. This folder is only used for benchmarking
  - `greedy_cuda`:
  - `lp`: files for [SCIP](https://www.scipopt.org/) solver, to solve the lsap. This method is also our reference implementation.
  - `munkres_julia`: implementation using julia library: [Hungrarian.jl](https://github.com/Gnimuc/Hungarian.jl/blob/master/src/Munkres.jl)
  - `hungarian_scipy`: implementation using python library: [scipy](https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.linear_sum_assignment.html)
  - `hungarian_python`: implementation using python library: [hungarian-algorithm](https://pypi.org/project/hungarian-algorithm/) *(Note that this library gives wrong results.)*
  - `instances`: Folder with example/test instances and their solutions

## Build / Prequisites
The build all cpp algorithms, run `make lsaps`.
To build the cuda codes, run `make lsaps_cuda`.
To run the julia code, install `Hungrarian.jl` by running inside of julia `using Pkg; Pkg.add("Hungarian")`.
To run the pure python code, install `hungarian-algorithm` by running `pip3 install hungarian-algorithm`.
To run the scipy code, install `scipy` by running `pip3 install scipy`.
To run the lp code, install the [scip optimization suit](https://scipopt.org/#scipoptsuite) and put the scip path inside the `SCIP` environment variable. (`declare -x SCIP=.../scip`)

## Execution
To run a specific algorithm, run `{algorithm}/lsap_solver {instance filename}` or `{algorithm}/lsap_solver {instance filename} {solution filename}`.

## Tests
To run the test suit, run `make test`. Solutions can also controlled individually by using `instances/check_sol.py`

## Benchmarks
The benchmarks will be run with [hyperfine](https://github.com/sharkdp/hyperfine). The julia benchmark is run with [BenchmarkTools](https://github.com/JuliaCI/BenchmarkTools.jl).

To run the benchmarks, run `make benchmark`. To run the lp benchmarks, go to the lp folder and the run `bash benchmark_each.sh`. To run the julia benchmarks, open the julia file in interactive mode and run `run_benchmark(benchmark_instances)`.

### Graphics
The benchmark graphics in the directory `benchmark` saved as pdf files.

## Slides and Report
Both are saved toplevel.