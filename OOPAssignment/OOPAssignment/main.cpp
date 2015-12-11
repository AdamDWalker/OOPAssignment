#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>

#include "BinaryImage.h"
#include "Matrix.h"

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

double sumSquaredDiffs(Matrix unshuffled, Matrix shuffled, int M, int N);

BinaryImage NNS(BinaryImage unshuffled_image, BinaryImage shuffled_image);

int main()
{
	// This part will show you how to use the two functions.
	
	//M and N represent the number of rows and columns in the image,
	//e.g. for task 1: logo_with_noise and logo_shuffled, M = 512, N = 512


	int M = 512; int N = 512;
	// input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed 
	// inside readTXT. readTXT will read an image (in .pgm format) of size MxN and will  store the result in input_data.
	// once you're done with data DO NOT forget to delete the memory as in the end of this main() function
	double* input_data = 0;
	double* noisy_image = 0;
	
	cout << endl;
	cout << "Data from text file -------------------------------------------" << endl;
	
	// .pgm image is stored in inputFileName, change the path in your program appropriately
	char* inputFileName = "shuffled_logo.txt"; 
	input_data = readTXT(inputFileName, M, N);
	noisy_image = readTXT("unshuffled_logo_noisy.txt", M, N);

	BinaryImage shuffledImage(M, N, input_data, 100);
	BinaryImage noisyImage(M, N, noisy_image, 100);


	/*int startCol = 0;
	int startRow = 0;

	int count1 = 0;
	int count2 = 0;
	for (int i = startRow; i < startRow + 32; i++)
	{
		count1++;

		for (int j = startCol ; j < startCol + 32; j++)
		{
			std::cout << i << " " << j << std::endl;
			//std::cout << "Outer: " << count2 << std::endl;
			count2++;
		}
	}*/


	BinaryImage tempImage(512, 512);
	tempImage = NNS(noisyImage, shuffledImage);
	double* output_data = tempImage.getData();

	//double B[] = { 12, 11, 14, 13, 17, 10 };
	//double C[] = { 1, 2, 3, 4, 5, 6 };

	//Matrix matrixA(3, 2, B);
	//Matrix matrixB(3, 2, C);

	//BinaryImage newImage(6, 4);
	//newImage.printmatrix();
	//newImage.placeBlock(matrixA, 1, 2);
	//newImage.printmatrix();
	//std::cout << sumSquaredDiffs(matrixA, matrixB, 3, 2) << std::endl;

	// writes data back to .pgm file stored in outputFileName
	char* outputFileName = "logo_restored.pgm";
	// Use Q = 255 for greyscale images and 1 for binary images.

	
	int Q = 1; 
	WritePGM(outputFileName, output_data, M, N, Q);
	WritePGM("Test1.pgm", shuffledImage.getData() , M, N, Q);
	WritePGM("Test2.pgm", noisyImage.getData(), M, N, Q);

	delete[] input_data;
	delete[] noisy_image;

	return 0;
}


// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
        // cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file"; 
  //cout << i;

  return data;
}

BinaryImage NNS(BinaryImage unshuffled_image, BinaryImage shuffled_image)
{
	// Giant fuckoff empty image to overwrite and return
	BinaryImage returnImage(512, 512);

	int M = 512;
	int N = 512;

	// This set of start/end values will be used for the block from the unshuffled noisy image
	int startCol1 = 0;
	int startRow1 = 0;
	int count1 = 0;

	// This set of values will be used for the blocks from the shuffled image
	int startCol2 = 0;
	int startRow2 = 0;
	int count2 = 0;

	//Matrix currentUnshuffled = unshuffled_image.getBlock(startIndex, endIndex, startIndex, endIndex);

	for (int i = 0; i < 256; i++)
	{
		//std::cout << "Unshuffled block: " << count1 << " Loop: " << i << std::endl;

		// PutBlock goes here

		startCol2 = 0;
		startRow2 = 0;

		// These are for the best matching block based on the SSD
		Matrix bestBlock;
		Matrix currentBlock;
		double SSD, bestSSD = 5000;
		int colPos, rowPos;

		if (count1 < 16)
		{
			for (int j = 0; j < 256; j++)
			{
				if (count2 < 16)
				{					
					/*
					//unshuffled_image.getBlock(startCol1, startCol1 + 31, startRow1, startRow1 + 31);
					//shuffled_image.getBlock(startCol2, startCol2 + 31, startRow2, startRow2 + 31);
					NNSResults[startColIndex] = startCol2;
					NNSResults[startRowIndex] = startRow2;
					startColIndex += 3;
					startRowIndex = startColIndex + 1;
					ssdResult = startColIndex + 2;
					*/
					currentBlock = shuffled_image.getBlock(startCol2, startCol2 + 31, startRow2, startRow2 + 31);
					SSD = sumSquaredDiffs(unshuffled_image.getBlock(startCol1, startCol1 + 31, startRow1, startRow1 + 31), currentBlock, 32, 32);
					if (count1 == 12)
						std::cout << " " << SSD;
					
					if (j == 0)
					{
						bestSSD = SSD;
						bestBlock = currentBlock;
						colPos = startCol2;
						rowPos = startRow2;
					}

					if (SSD <= bestSSD)
					{
						bestSSD = SSD;
						bestBlock = currentBlock;
						colPos = startCol2;
						rowPos = startRow2;
					}
					
					startCol2 += 32;
					count2++;
				}
				else
				{
					count2 = 0;
					startCol2 = 0;
					startRow2 += 32;
				}
			}
			if (count1 == 12)
			{
				std::cout << "\n\n\n SSD: " << bestSSD << std::endl;
				bestBlock.printmatrix();
				std::cout << "\n\n\n" << std::endl;
				
			}
			returnImage.placeBlock(bestBlock, startCol1, startRow1);

		}
		else
		{
			// The column resets to the beginning and the row increases by 32
			count1 = 0;
			startCol1 = 0;
			startRow1 += 32;
		}
			count1++;
			startCol1 += 32;
	}

	return returnImage;

}

double sumSquaredDiffs(Matrix unshuffled, Matrix shuffled, int M, int N)
{
	double SSD = 0;
	Matrix temp(32, 32);

	temp = shuffled - unshuffled;
	double* tempArray = temp.getData();
	for (int i = 0; i < M * N; i++)
	{
		double temp = (tempArray[i] * tempArray[i]);
		SSD += temp;
	}

	return SSD;
}


// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

 int i, j;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out|ios::binary|ios::trunc);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();

 delete [] image;

}