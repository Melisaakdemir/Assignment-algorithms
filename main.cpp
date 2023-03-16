///  Group g14: Melisa Akdemir, Ludwig Austermann, Tabea Both, Matthias Jean Théo Personnaz

#include <assert.h>
#include <chrono>
#include <complex>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "problem.hpp"

#ifdef COMPILE_hungarian
#include "hungarian/algorithm.hpp"
#elif defined(COMPILE_hungarian_sp)
#else
#include "nosolve/algorithm.hpp"
#endif

constexpr char FILEEXT[] = ".mm";
constexpr unsigned int FILEEXTLENGTH = sizeof(FILEEXT) - 1; // char arrays are \0 terminated, so there is an extra char
constexpr char SOLEXT[] = ".sol";
constexpr unsigned int SOLEXTLENGTH = sizeof(SOLEXT) - 1; // char arrays are \0 terminated, so there is an extra char

using std::endl, std::cout, std::vector;

int main(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument("Too few arguments given! The syntax is " + std::string(argv[0]) + " <instance filename> <solution filename>?.");

    std::string filename = argv[1];

    if ((filename.length() <= FILEEXTLENGTH) or (filename.substr(filename.length() - FILEEXTLENGTH, filename.length()) != FILEEXT))
        throw std::invalid_argument("Non valid instance filename. Filename has to have '{}" + std::string(FILEEXT) + "' file-extension.");

    std::string solfilename;
    if (argc < 3)
        solfilename = filename.substr(0, filename.length() - FILEEXTLENGTH) + SOLEXT;
    else
    {
        solfilename = argv[2];
        if (solfilename.length() <= SOLEXTLENGTH or solfilename.substr(solfilename.length() - SOLEXTLENGTH, solfilename.length()) != SOLEXT)
            throw std::invalid_argument("Non valid solution filename. Filename has to have '{}" + std::string(SOLEXT) + "' file-extension.");
    }

    // time at beginning
    auto start_time = std::chrono::high_resolution_clock::now();

    auto instance = Problem(filename);

    // instance.display();

    auto solution = Solver().solve(instance);

    // solution.display();

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;

    solution.save_to_file(solfilename);

    cout << "Computed in " << std::setprecision(2) << std::fixed << 1'000 * duration.count() << " ms. Solution saved to " << solfilename << "." << endl;

    return 0;
};