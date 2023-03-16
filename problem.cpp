#include <iostream>
#include <string>

#include "problem.hpp"
#include "matrix.hpp"

Problem::Problem(std::string const &filename)
{
    cost_matrix_.from_file(filename);
}

void Problem::display()
{
    std::cout << "Linear Sum Assignment Problem with costs matrix\n"
              << std::endl;
    cost_matrix_.display();
}