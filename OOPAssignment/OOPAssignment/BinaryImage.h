#pragma once

#include "Matrix.h"

class BinaryImage : public Matrix
{
public:
    BinaryImage();
	BinaryImage(int M, int N);
    BinaryImage( int M, int N, double* input_data, double threshold);
    ~BinaryImage();
    
    BinaryImage(const BinaryImage& other);
    BinaryImage operator+(const BinaryImage& other);
    BinaryImage operator-(const BinaryImage& other);
    BinaryImage operator*(const BinaryImage& other);
private:
    double threshold;
};
