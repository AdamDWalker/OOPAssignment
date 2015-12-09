#pragma once

#include <iostream>

class Matrix
{
public:
    Matrix();
    Matrix(int sizeR, int sizeC, double* input_data);
    Matrix(const Matrix& objectName);
    ~Matrix();
    
    
    Matrix operator=(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator/(const Matrix& other);
    Matrix operator++();
    Matrix operator++(int dummyInt);
    double operator()(int i, int j);
    
    double get(int i, int j); // This is now replaced by the overloaded () operator, but I'll keep it here for a while anyway. Why not? It's my code not yours.
	double* getData();
	void set(int i, int j, double val);
    Matrix getBlock(int start_column, int end_column, int start_row, int end_row);
    void printmatrix();

protected:
    int _M, _N;
    double *_data;
};
