#ifndef HEADER_MATRIX
#define HEADER_MATRIX

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::vector;

template <typename ElType>
class Matrix
{
    /// @brief number of rows
    unsigned int m_;
    /// @brief number of columns
    unsigned int n_;
    vector<vector<ElType>> rows_;

public:
    Matrix<ElType>() {}
    Matrix<ElType>(unsigned int const m, unsigned int const n) : m_{m}, n_{n}, rows_{vector(m, vector(n, ElType(0)))} {}

    /// @brief reads a matrix from a file
    /// @param filename mm file defining a matrix
    void from_file(std::string const &filename)
    {
        std::ifstream input_file(filename);

        input_file >> m_ >> n_;

        rows_.reserve(m_);
        ElType c;
        vector<ElType> temp_row(n_, ElType(0));

        for (size_t i = 0; i < m_; i++)
        {
            for (size_t j = 0; j < n_; j++)
            {
                input_file >> c;
                temp_row.at(j) = c;
            }
            rows_.push_back(temp_row);
        }
    }

    ElType at(unsigned int const i, unsigned int const j) const
    {
        return rows_.at(i).at(j);
    }

    void set_at(size_t const i, size_t const j, ElType v)
    {
        rows_.at(i).at(j) = v;
    }

    void add_at(size_t const i, size_t const j, ElType v)
    {
        rows_.at(i).at(j) += v;
    }

    void display() const
    {
        for (size_t i = 0; i < m_; i++)
        {
            for (size_t j = 0; j < n_; j++)
                std::cout << std::setw(2) << (int) at(i, j) << " ";
            std::cout << std::endl;
        }
    }

    unsigned int nrows() const
    {
        return m_;
    }
};

#endif