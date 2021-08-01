#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
class Matrix {
    public:
        int rows;
        int columns;
        int size;

        Matrix();
        Matrix(const std::vector<std::vector<T>>& new_matrix);

        //Matrix operator*(Matrix& m2);
        Matrix operator+(const Matrix& m2);
        //Matrix operator-(Matrix& m2);

        void print_matrix();

    private:
        std::vector<std::vector<T>> data;
};

template<typename T>
Matrix<T>::Matrix() {
    rows = 2; 
    columns = 2;
    size = rows * columns;
    data = {
        {1, 2},
        {3, 4}
    };
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& new_matrix)
{
    int height, width;

    height = new_matrix.size();
    if (height == 0)
        throw std::invalid_argument("Matrix: Column length must be greater than 0");

    width = new_matrix.at(0).size();
    if (width == 0)
        throw std::invalid_argument("Matrix: Row length must be greater than 0");

    for (auto row : new_matrix)
    {
        if (row.size() != width)
            throw std::invalid_argument("Matrix: Row or column lengths do not match");
    }

    rows = height;
    columns = width;
    size = rows * columns;
    data = new_matrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& m2) 
{
    if (m2.size != size || m2.rows != rows || m2.columns != columns)
        throw std::invalid_argument("Matrixes are not of the same size");

    // Init vector
    std::vector<std::vector<T>> new_data(rows, std::vector<T>(columns, 0));

    for (int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++) 
        {
            new_data[i][j] = data[i][j] + m2.data[i][j];
        }
    }

    return Matrix<T>(new_data);
}

template<typename T>
void Matrix<T>::print_matrix() 
{
    for (auto const &row : data)
    {
        std::cout << "[ ";
        for(int cell = 0; cell < row.size(); cell++)
        {
            std::cout << row[cell];
            if (cell != row.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << " ]\n";
    }
}
#endif