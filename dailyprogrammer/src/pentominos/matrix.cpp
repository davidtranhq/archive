#include "matrix.hpp"

// constructor from init_list of init_lists
matrix(std::initializer_list<std::initializer_list<double>> mat)
    : rows{mat.size()},
      cols{mat.begin().size()}
{
    for (std::initializer_list<double> r : mat)
        m.insert(m.end(), r);
}