#include "Matrix.h"
#include <iostream>

Matrix::Matrix()
{
    _M = 1;
    _N = 1;
    
    _data = new double[_M*_N];
    
    for (int x = 0; x < _M*_N; x++)
    {
        _data[x] = 0;
    }
}

Matrix::Matrix(int M, int N)
{
	_M = M;
	_N = N;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = 0;
	}
}

Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
    //std::cout << "Matrix::Matrix(int sizeR, int sizeC, double val[]) is invoked" << std::endl;
    _M = sizeR;
    _N = sizeC;
    
    _data = new double[_M * _N];
    
    for(int i = 0; i < (_M * _N); i++)
        _data[i] = input_data[i];
}

Matrix::Matrix(const Matrix& objectName)
{
   // std::cout << "Matrix::Matrix(const Matrix&) is invoked" << std::endl;
    _M = objectName._M;
    _N = objectName._N;
    
    _data = new double [_M * _N];
    
    for(int i = 0; i < (_M * _N); i++)
        _data[i] = objectName._data[i];

}

Matrix::~Matrix()
{
    //std::cout << "Matrix::~Matrix() is invoked" << std::endl;
    delete[] _data;
}

Matrix Matrix::operator=(const Matrix& other)
{
    //std::cout << "Operator '=' overload" << std::endl;
    //delete existing _data information - as we are going to replace it with 'other._data'
    delete[] _data;
    _M = other._M;
    _N = other._N;
    
    //reserve memory for new array
    _data = new double[_M*_N];
    
    //'this' pointer refers to the current object
    for (int x = 0; x < (_M*_N); x++)
    {
        this->_data[x] = other._data[x];
    }
    
    return *this;
}

//
// Overloaded operator + takes the data from the additional matrix and adds each value
// to the corresponding value in the first matrix
//
Matrix Matrix::operator+(const Matrix& other)
{
    //std::cout << "Operator '+' overload" << std::endl;
    Matrix temp;
    temp._M = other._M;
    temp._N = other._N;
    
    temp._data = new double[temp._M * temp._N];
    
    for(int i = 0; i < (temp._M * temp._N); i++)
    {
        temp._data[i] = this->_data[i] + other._data[i];
        std::cout << "Temp: " << temp._data[i] << " This: " << this->_data[i] << " Other: " << other._data[i] << std::endl;
    }
    
    return temp;
}

Matrix Matrix::operator-(const Matrix& other)
{
    //std::cout << "Operator '-' overload" << std::endl;
    Matrix temp;
    temp._M = other._M;
    temp._N = other._N;
    
    temp._data = new double[temp._M * temp._N];
    
    for(int i = 0; i < (temp._M * temp._N); i++)
    {
        temp._data[i] = this->_data[i] - other._data[i];
    }
    
    return temp;
}

Matrix Matrix::operator*(const Matrix& other)
{
    //std::cout << "Operator '*' overload" << std::endl;
    Matrix temp;
    temp._M = other._M;
    temp._N = other._N;
    
    temp._data = new double[temp._M * temp._N];
    
    for(int i = 0; i < (temp._M * temp._N); i++)
    {
        temp._data[i] = this->_data[i] * other._data[i];
    }
    
    return temp;
}

Matrix Matrix::operator/(const Matrix& other)
{
    //std::cout << "Operator '/' overload" << std::endl;
    Matrix temp;
    temp._M = other._M;
    temp._N = other._N;
    
    temp._data = new double[temp._M * temp._N];
    
    for(int i = 0; i < (temp._M * temp._N); i++)
    {
        temp._data[i] = this->_data[i] / other._data[i];
    }
    
    return temp;
}

Matrix Matrix::operator++(int dummyInt)
{
    Matrix oldMatrix = *this;
    
    for(int i = 0; i < (this->_M * this->_N); i++)
    {
        this->_data[i]++;
        //std::cout << "Increment implemented, value now: " << _data[i] << std::endl;
    }
    
    return oldMatrix;
}

double Matrix::operator()(int i, int j)
{
    //std::cout << " Matrix::operator() is invoked" << std::endl;
    int k;
    
    k = i * _N + j;
    
    return _data[k];
}

double Matrix::get(int i, int j)
{
    //k = i × N + j
    
    int k;
    
    k = i * _N + j;
    
    return _data[k];
}

double* Matrix::getData()
{
	return _data;
}

void Matrix::set(int i, int j, double val)
{
    int k;
    
    k = i * _N + j;
    
    _data[k] = val;
}

Matrix Matrix::getBlock(int start_column, int end_column, int start_row, int end_row)
{
    int k;
    
    int rows = (end_row - start_row);
    int columns = (end_column - start_column);
    
    double* tempData = new double[rows * columns];
    
    for(int i = start_column; i <= end_column; i++)
    {
        
        for(int j = start_row; j <= end_row; j++)
        {
            //int k = i * N + j;
            k = (i * _N) + j;
            //std::cout << i << " " << j << " " << _N << " " << _data[k] << std::endl;
            tempData[j] = _data[k];
            //std::cout << localArray[j];
			//
        }
    }
    
    Matrix returnMatrix(rows, columns, tempData);
    return returnMatrix;
}

void Matrix::placeBlock(Matrix block, int startCol, int startRow)
{
	int i = startRow;
	int j = startCol;
	int k;
	int N = 4;

	int count = 0;
	for (int i = startRow; i < startRow + 3; i++)
	{
		for (int j = startCol; j < startCol + 2; j++)
		{
			//std::cout << i << " " << j << std::endl;
			k = i * N + j;
			//this->_data[k] = block._data[k];
			std::cout << "This: " << this->_data[k] << " Block: " << block._data[count] << std::endl;
			count++;
		}
	}
}

void Matrix::printmatrix()
{
	std::cout << "Print mtrix invoked" << std::endl;
    for (int i = 0; i < _M; i++)
    {
        for ( int j = 0; j < _N; j++)
        {
            int k = i * _N + j;
            std::cout << _data[k] << " ";
        }
        std::cout << std::endl;
    }
}

