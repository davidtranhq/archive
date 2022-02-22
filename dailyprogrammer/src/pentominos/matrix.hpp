#ifndef MATRIX_H
#define MATRIX_H

class matrix
{
    public:
        // class member for representation of matrix
        class matrix_row;
        // constructor from initializer_list of initializer_lists
        matrix(std::initializer_list<matrix_row> vals);
    
    private:
        std::vector<matrix_row> m;
        size_t rows, cols;
};

class matrix_row
{
    public:
    
    private:
        std::vector<double> v;
};

#endif