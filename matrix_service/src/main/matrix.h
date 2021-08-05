#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <string>
#include <type_traits>

#include "main/schema.grpc.pb.h"
using routeguide::MatrixArr;

template <typename T>
class Matrix {
    public:
        int rows;
        int columns;
        int size;
        std::vector<std::vector<T>> data;

        Matrix();
        Matrix(const std::vector<std::vector<T>>& new_matrix);
        Matrix(const std::vector<std::vector<T>>& new_matrix, T r, T c);
        Matrix(routeguide::MatrixArr m_arr);
        Matrix(int r, int c);

        //Matrix operator*(Matrix& m2);
        Matrix operator+(const Matrix& m2);
        void add(const Matrix& m2);
        //Matrix operator-(Matrix& m2);

        std::vector<T> ravel();
        void print_matrix();
};

template<typename T>
Matrix<T>::Matrix(int r, int c) {
    rows = r; 
    columns = c;
    size = rows * columns;
    std::vector<std::vector<T>> new_data(rows, std::vector<T>(columns, 0));
    data = new_data;
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& new_matrix, T r, T c) {
    if (new_matrix.size() != r * c)
        throw std::invalid_argument("Invalid Matrix");

    rows = r;
    columns = c;
    size = r * c;
    std::vector<std::vector<T>> new_data(rows, std::vector<T>(columns, 0));

    int row_count = 0;
    int old_index = 0;
    while (row_count < rows) 
    {
        for (int i = 0; i < columns; i++)
        {
            new_data[row_count][i] = new_matrix[old_index];
            ++old_index;
        }
        ++row_count;
    }
    data = new_data;
}

template<typename T>
Matrix<T>::Matrix(routeguide::MatrixArr m_arr)
{
    rows = m_arr.rows();
    columns = m_arr.cols();

    std::vector<std::vector<T>> new_data(rows, std::vector<T>(columns, 0));

    // Need separate step to properly iterate over array
    int step = 0;
    int row_count = 0;
    while (row_count < rows && step < m_arr.array_size()) 
    {
        for (int i = 0; i < columns; i++)
        {
            new_data[row_count][i] = m_arr.array(step);
            ++step;
        }
        ++row_count;
    }
    data = new_data;
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
void Matrix<T>::add(const Matrix& m2) 
{
    if (m2.size != size || m2.rows != rows || m2.columns != columns)
        throw std::invalid_argument("Matrixes are not of the same size");

    for (int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++) 
        {
            data[i][j] = data[i][j] + m2.data[i][j];
        }
    }
}

template<typename T>
std::vector<T> Matrix<T>::ravel() 
{
    std::vector<T> v;
    v.reserve(rows * columns);
    for (const auto &row : data) {
        for (const auto &cell : row) {
            v.push_back(cell);
        }
    }

    return v;
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