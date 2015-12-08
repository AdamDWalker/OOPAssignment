//
//  main.cpp
//  MatrixWorkshop
//
//  Created by Adam Walker on 04/12/2015.
//  Copyright © 2015 Adam Walker. All rights reserved.
//

#include <iostream>
#include "Matrix.h"
#include "BinaryImage.h"

int previousMain(int argc, const char * argv[])
{
    double A[35];
   // int inputM, inputN, contentVal;
    
  //  std::cout << inputM << " " << inputN << std::endl;

    for(int i = 0; i <= 34; i++)
    {
        A[i] = (double)i;
    }
    
    double B[] = {11, 12, 13, 14, 15, 16};
    double C[] = {1, 2, 3, 4, 5, 6};
    
    Matrix matrixA(5, 7, A);
    Matrix matrixB(3, 2, B);
    Matrix matrixC(3, 2, C);
   // Matrix matrixB3 = matrixB / matrixB2;
    //Matrix matrixC = matrixB;
    
    //std::cout << matrixA.get(4, 3) << std::endl;
    //std::cout << matrixC.get(1, 1) << std::endl;
    
    Matrix matrixD = (matrixC.getBlock(0, 1, 0, 1));
    //std::cout << matrixB2.get(1, 1) << std::endl;
    //std::cout << matrixA.get(1, 1) << std::endl;
    
    //matrixA = matrixB2++;
    //std::cout << matrixA(1, 1) << std::endl;
    std::cout << "Starting matrix E" << std::endl;
    
    Matrix E;
    
    E = matrixC + matrixB;
    std::cout << E(1,1) << std::endl;
    E = matrixC - matrixB;
    std::cout << E(1,2) << std::endl;
    E = matrixC;
    std::cout << E(1,2) << std::endl;
    E = matrixC++;
    std::cout << E(1,2) << std::endl;
    
    BinaryImage biscuit(3, 2, C, 3);
    biscuit.printmatrix();
    BinaryImage G = biscuit;
	G.printmatrix();
	std::cout << "Biscuit and G have printed" << std::endl;
    
    BinaryImage H = biscuit + G;
	H.printmatrix();
   // H = biscuit * G;
    std::cout << G(1,2) << std::endl;
    //std::cout << "Hello, World!\n";
    return 0;
}
