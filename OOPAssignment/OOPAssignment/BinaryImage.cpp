#include "BinaryImage.h"
#include "Matrix.h"

BinaryImage::BinaryImage() : Matrix()
{
 
}

BinaryImage::BinaryImage( int M, int N, double* input_data, double threshold ) : Matrix( M, N, input_data )
{
    
    for(int i = 0; i < M * N; i++)
    {
        if (_data[i] > threshold)
        {
            _data[i] = 1;
        }
        else
        {
            _data[i] = 0;
        }
    }
}

BinaryImage::BinaryImage(const BinaryImage& other) : Matrix(other)
{
    std::cout << "BinaryImage(const BinaryImage& other) is invoked" << std::endl;
    
    threshold = other.threshold;
}

BinaryImage::~BinaryImage()
{
    std::cout << "~BinaryImage() is invoked" << std::endl;
}

BinaryImage BinaryImage::operator+(const BinaryImage& other)
{
	BinaryImage temp(other._M, other._N, other._data, threshold);
    std::cout << "BinaryImage::operator+(const BinaryImage& other) invoked, M and N are: " << temp._M << " " << temp._N << std::endl;


    for(int i = 0; i < temp._M * temp._N; i++)
    {
        if(temp._data[i] == 0 && other._data[i] == 0)
        {
            temp._data[i] = 0;
        }
        else
        {
            temp._data[i] = 1;
        }
    }
    return temp;
    
}

BinaryImage BinaryImage::operator-(const BinaryImage& other)
{
    std::cout << "BinaryImage::operator-(const BinaryImage& other) invoked" << std::endl;
    
    BinaryImage temp(other._M, other._N, other._data, threshold);

    for(int i = 0; i < temp._M * temp._N; i++)
    {
        if(temp._data[i] == other._data[i])
        {
            temp._data[i] = 0;
        }
        else
        {
            temp._data[i] = 1;
        }
    }
    return temp;
    
}

BinaryImage BinaryImage::operator*(const BinaryImage& other)
{
    std::cout << "BinaryImage::operator*(const BinaryImage& other) invoked" << std::endl;
    
	BinaryImage temp(other._M, other._N, other._data, threshold); 
    
    for(int i = 0; i < temp._M * temp._N; i++)
    {
        if(temp._data[i] ==  1 && other._data[i] == 1)
        {
            temp._data[i] = 1;
        }
        else
        {
            temp._data[i] = 1;
        }
    }
    return temp;
}
