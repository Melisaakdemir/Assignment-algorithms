#ifndef HEADER_PROBLEM
#define HEADER_PROBLEM

#include <string>

#include "matrix.hpp"
#include "solution.hpp"

/// @brief A class to represent an instance of the LSAP with various solving methods
class Problem
{
public:
    Matrix<int> cost_matrix_;
    Problem(std::string const &filename);
    void display();
};

#endif