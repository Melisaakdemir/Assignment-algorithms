#ifndef HEADER_SOLUTION
#define HEADER_SOLUTION

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.hpp"

class Solution
{
    int minimal_cost_;
    std::vector<unsigned int> assigned_;

public:
    Solution(Matrix<int> const &cost_matrix, std::vector<unsigned int> phi) : assigned_{phi}
    {
        minimal_cost_ = 0;
        for (size_t i = 0; i < cost_matrix.nrows(); i++)
            minimal_cost_ += cost_matrix.at(i, phi.at(i));
    };
    void save_to_file(std::string const &filename)
    {
        std::ofstream output_file(filename);
        output_file << "# minimal cost: " << minimal_cost_ << std::endl;
        for (size_t i = 0; i < assigned_.size(); i++)
            output_file << i + 1 << " " << assigned_.at(i) + 1 << std::endl;
    }
    void display()
    {
        std::cout << "Minimal cost: " << minimal_cost_ << std::endl;
        for (size_t i = 0; i < assigned_.size(); i++)
            std::cout << i + 1 << " " << assigned_.at(i) + 1 << std::endl;
    }
};

#endif