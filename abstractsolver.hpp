#ifndef HEADER_ABSTRACT_SOLVER
#define HEADER_ABSTRACT_SOLVER

#include "problem.hpp"
#include "solution.hpp"

class AbstractSolver
{
public:
    virtual Solution solve(Problem const &p) = 0;
};

#endif