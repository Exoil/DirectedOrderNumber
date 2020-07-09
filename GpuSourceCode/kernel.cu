#include <chrono>  // for high_resolution_clock
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream> 
#include <thrust/sort.h>
#include <stdio.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>
#include <algorithm>
#include <time.h>
#include <filesystem>
#if defined(_MSC_VER)
#include <direct.h>
#define getcwd _getcwd
#elif defined(__GNUC__)
#include <unistd.h>
#endif
#include <iomanip>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <string>

/*
rozmiary siatek
100x100
4    4
25	 25

1000x1000
25   25
40	 40

10000x10000
40   40
250	 250
*/

enum DivideType {
	LesserThanZero,
	HaveZero,
	GreaterThanZero
};

class DirectedOrderNumber {

public:
	double infimum, supremum;
	bool zeroFlag;
	__device__  __host__
	DirectedOrderNumber()
	{
		infimum = 0.0;
		supremum = 0.0;
		zeroFlag = false;
	}
	__device__  __host__
	DirectedOrderNumber(const DirectedOrderNumber& that)
	{
		infimum = that.infimum;
		supremum = that.supremum;
		zeroFlag = false;
	}
	__device__ __host__
	DirectedOrderNumber(double newInfimum, double newSupremum)
	{
		infimum = double(newInfimum);
		supremum = double(newSupremum);
		zeroFlag = false;
	}
	__device__ __host__
	DirectedOrderNumber(DirectedOrderNumber* orderNumber)
	{
		infimum = orderNumber->infimum;
		supremum = orderNumber->supremum;
		zeroFlag = orderNumber->zeroFlag;
	}
	__device__ __host__
	void SetValues(double newInf, double newSup)
	{
		infimum = newInf;
		supremum = newSup;
		zeroFlag = false;
	}
	__device__
		double GetRealNumber()
	{
		return (infimum + supremum) / 2.0;
	}
	__device__
		double GetAbsoulteRealNumber()
	{
		double result = (infimum + supremum) / 2.0;

		if (result < 0)
			return -1 * result;

		else
			return result;
	}
	__device__
		DivideType GetDivideType()
	{
		if (infimum > 0.0 && supremum > 0.0)
		{
			return GreaterThanZero;
		}

		else if (infimum < 0.0 && supremum < 0.0)
		{
			return LesserThanZero;
		}
		else
		{
			return HaveZero;
		}
	}
};

__device__
void AddDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
{
	result->SetValues(firstValue->infimum + secondValue->infimum, firstValue->supremum + secondValue->supremum);
}
__device__
void SubstractDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
{
	result->SetValues(firstValue->infimum - secondValue->infimum, firstValue->supremum - secondValue->supremum);
}

__device__
void SortMultipleArray(double* array)
{
	double tmp = 0.0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 4 - i; j++) {
			if (array[j - 1] > array[j])
			{
				tmp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = tmp;
			}
		}
	}
}

__device__
void MultipleDirectedOrderNumber(DirectedOrderNumber* firstNumber, DirectedOrderNumber* secondNumber, DirectedOrderNumber* result) {

	double* multipleResult;
	multipleResult = new double[4];
	multipleResult[0] = (firstNumber->infimum * secondNumber->infimum);
	multipleResult[1] = (firstNumber->infimum * secondNumber->supremum);
	multipleResult[2] = (firstNumber->supremum * secondNumber->supremum);
	multipleResult[3] = (firstNumber->supremum * secondNumber->infimum);

	SortMultipleArray(multipleResult);
	result->infimum = multipleResult[0];
	result->supremum = multipleResult[3];
	delete[](multipleResult);
}

__device__
void DivideDirectedOrderNumber(DirectedOrderNumber* firstNumber, DirectedOrderNumber* secondNumber, DirectedOrderNumber* result) {

	if (firstNumber->GetDivideType() == GreaterThanZero && secondNumber->GetDivideType() == GreaterThanZero)
	{
		result->infimum = firstNumber->infimum / secondNumber->infimum;
		result->supremum = firstNumber->supremum / secondNumber->supremum;
	}

	else if (firstNumber->GetDivideType() == LesserThanZero && secondNumber->GetDivideType() == LesserThanZero)
	{
		result->supremum = firstNumber->infimum / secondNumber->infimum;
		result->infimum = firstNumber->supremum / secondNumber->supremum;
	}
	else if (firstNumber->GetDivideType() == GreaterThanZero && secondNumber->GetDivideType() == LesserThanZero)
	{
		result->infimum = firstNumber->supremum / secondNumber->infimum;
		result->supremum = firstNumber->infimum / secondNumber->supremum;
	}
	else if (firstNumber->GetDivideType() == LesserThanZero && secondNumber->GetDivideType() == GreaterThanZero)
	{
		result->infimum = firstNumber->infimum / secondNumber->supremum;
		result->supremum = firstNumber->supremum / secondNumber->infimum;
	}

	else if (firstNumber->GetDivideType() == HaveZero && secondNumber->GetDivideType() == GreaterThanZero)
	{
		result->infimum = firstNumber->infimum / secondNumber->supremum;
		result->supremum = firstNumber->supremum / secondNumber->supremum;
	}
	else if (firstNumber->GetDivideType() == HaveZero && secondNumber->GetDivideType() == LesserThanZero)
	{
		result->infimum = firstNumber->supremum / secondNumber->infimum;
		result->supremum = firstNumber->infimum / secondNumber->infimum;
	}
	else if (secondNumber->GetDivideType() == HaveZero)
	{
		secondNumber->infimum = (secondNumber->GetRealNumber() / 2.0) - 0.00000001;
		secondNumber->supremum = (secondNumber->GetRealNumber() / 2.0) + 0.00000001;
		DivideDirectedOrderNumber(firstNumber, secondNumber, result);
	}

}

__global__
void SetMnoznikMatrix(DirectedOrderNumber* matrix, DirectedOrderNumber* mnoznik, int size, int actuall_Collumn)
{	
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * size + column;
	DirectedOrderNumber minus(-1.0, -1.0);
	if (index < size * size)
	{
		mnoznik[index].infimum = 1.0;
		mnoznik[index].supremum = 1.0;
	}

	if (index == row * size + actuall_Collumn && index != row * (size + 1))
	{
		MultipleDirectedOrderNumber(&mnoznik[index], &minus, &mnoznik[index]);	
		DivideDirectedOrderNumber(&mnoznik[index], &matrix[(actuall_Collumn * size) + actuall_Collumn], &mnoznik[index]);
	}
	__syncthreads();
	if (index != row * size + actuall_Collumn)
	{
		mnoznik[index] = mnoznik[row * size + actuall_Collumn];
	}
}

__global__
void EleminatePart(DirectedOrderNumber* matrix, DirectedOrderNumber* cmatrix, DirectedOrderNumber* devBVector, int size, int actuall_Collumn)
{
	int column = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
	int index = row * size + column;
	DirectedOrderNumber tmp(0.0, 0.0);
	DirectedOrderNumber tmpTwo(0.0, 0.0);
	if (row > actuall_Collumn)
	{	
		MultipleDirectedOrderNumber(&cmatrix[row * size + actuall_Collumn], &matrix[(actuall_Collumn * size) + column], &tmp);
		if (matrix[index].zeroFlag == false)
		{
			AddDirectedOrderNumber(&matrix[index], &tmp, &matrix[index]);
		}
	}
	__syncthreads();
	if (row == actuall_Collumn)
	{
		matrix[actuall_Collumn * size + row].zeroFlag = true;
	}
	if (index < size && index > actuall_Collumn)
	{
		MultipleDirectedOrderNumber(&cmatrix[column * size + actuall_Collumn], &devBVector[actuall_Collumn], &tmpTwo);
		AddDirectedOrderNumber(&devBVector[index], &tmpTwo, &devBVector[index]);
	}
	__syncthreads();

}



__global__
void SetReductionTable(DirectedOrderNumber* reductionVector, DirectedOrderNumber* matrix, DirectedOrderNumber* resultVector, int size, int actual_column)
{


	int column = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
	int index = row * size + column;

	if (index > actual_column * size + row && index < size * size && row == actual_column && index != row * (size + 1))
	{
		MultipleDirectedOrderNumber(&matrix[actual_column * size + column], &resultVector[column], &reductionVector[column]);
	}

	else
	{
		reductionVector[index].infimum = 0.0;
		reductionVector[index].supremum = 0.0;
	}

}

__global__
void Reduction(DirectedOrderNumber* reductionVector, int size, DirectedOrderNumber* result)
{
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	int cacheIndex = threadIdx.x;
	auto step_size = 1;
	int number_of_threads = blockDim.x;
	while (number_of_threads > 0)
	{
		if (index < number_of_threads)
		{
			const auto fst = index * step_size * 2;
			const auto snd = fst + step_size;
			AddDirectedOrderNumber(&reductionVector[fst], &reductionVector[snd], &reductionVector[fst]);
		}
		step_size <<= 1;
		number_of_threads >>= 1;
	}
	if (index == 0)
	{
		result->infimum = reductionVector[0].infimum;
		result->supremum = reductionVector[0].supremum;
	}
}

__global__
void GainResolveVector(DirectedOrderNumber* matrix, DirectedOrderNumber* resultVector, DirectedOrderNumber* bVector, DirectedOrderNumber* reductedValue, int size, int acutalColumn)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	DirectedOrderNumber sum = bVector[acutalColumn];
	SubstractDirectedOrderNumber(&sum, reductedValue, &sum);
	DivideDirectedOrderNumber(&sum, &matrix[acutalColumn * (size + 1)], &resultVector[acutalColumn]);
}

__global__
void SetResultVector(DirectedOrderNumber* resultVector, int size)
{
	int column = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
	int index = row * size + column;
	if (index < size)
	{
		resultVector[index].infimum = 1.0;
		resultVector[index].supremum = 1.0;
	}
}




DirectedOrderNumber *GaussElemination(DirectedOrderNumber* equation, DirectedOrderNumber* bvector, int size, int blocksize, int threadGridsize)
{
	DirectedOrderNumber* devVector, * devBValues, * mnoznikMatrix, * VectorResult;

	size_t matrixSize = size * size * sizeof(DirectedOrderNumber);
	size_t resultVectorSize = size * sizeof(DirectedOrderNumber);

	cudaMalloc((void**)&devVector, matrixSize);
	cudaMalloc((void**)&mnoznikMatrix, matrixSize);
	cudaMalloc((void**)&VectorResult, resultVectorSize);
	cudaMalloc((void**)&devBValues, resultVectorSize);
	cudaEvent_t start, stop;
	cudaEvent_t start2;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventCreate(&start2);
	cudaEventRecord(start);
	cudaMemcpy(devVector, equation, matrixSize, cudaMemcpyHostToDevice);
	cudaMemcpy(devBValues, bvector, resultVectorSize, cudaMemcpyHostToDevice);

	dim3 blockGrid(blocksize, blocksize);
	dim3 thredGrid(threadGridsize, threadGridsize);
	dim3 RdimBlock(1, 1, 1);
	dim3 RdimGrid(size, 1, 1);
	SetResultVector << < blockGrid, thredGrid >> > (VectorResult, size);
	cudaEventRecord(start2);
	for (int i = 0; i < size; i++)
	{
		SetMnoznikMatrix << <blockGrid, thredGrid >> > (devVector, mnoznikMatrix, size, i);
		EleminatePart << < blockGrid, thredGrid >> > (devVector, mnoznikMatrix, devBValues, size, i);
		std::cout << "Aktualny krok eliminacji: " << i << std::endl;
	}


	DirectedOrderNumber* minusVector;
	cudaMalloc((void**)&minusVector, resultVectorSize);
	DirectedOrderNumber* reductionResult;
	cudaMalloc((void**)&reductionResult, sizeof(DirectedOrderNumber));
	for (int i = size-1; i >= 0; i--)
	{
		SetReductionTable <<<blockGrid, thredGrid >>> (minusVector, devVector, VectorResult, size, i);
		Reduction << <RdimBlock, RdimGrid >> > (minusVector, size, reductionResult);
		GainResolveVector << <1, 1 >> > (devVector, VectorResult, devBValues, reductionResult, size, i);
		std::cout << "Aktualny krok uzyskania wektoru: " << i << std::endl;
	}
	cudaDeviceSynchronize();
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	float milliseconds = 0, milisecondstwo = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	cudaEventElapsedTime(&milisecondstwo, start2, stop);
	std::cout << "Czas w milisekundach po stronie GPU:" << milliseconds << std::endl;
	std::cout << "Czas w milisekundach po stronie GPU bez alkoacji pamieci:" << milisecondstwo << std::endl;
	DirectedOrderNumber* hostResult;
	hostResult = new DirectedOrderNumber[size];
	cudaMemcpy(hostResult, VectorResult, resultVectorSize, cudaMemcpyDeviceToHost);

	cudaFree(reductionResult);
	cudaFree(minusVector);
	cudaFree(devVector);
	cudaFree(devBValues);
	cudaFree(mnoznikMatrix);
	cudaFree(VectorResult);

	return hostResult;
}



/*Koniec elimiancji Gaussa Funkcji*/
/*#####################################################################*/
/*Eliminiacja Gaussa-Jordana*/


__global__
void SetCMatirxJordan(DirectedOrderNumber* devMatrix, DirectedOrderNumber* cmatrix, int rowSize, int acutall_Column)
{
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * rowSize + column;

	if (index == row * rowSize + acutall_Column)
	{
		DivideDirectedOrderNumber(&devMatrix[index], &devMatrix[(acutall_Column * rowSize) + acutall_Column], &cmatrix[index]);

	}

	if (index < rowSize * rowSize)
	{
		if (index != row * rowSize + acutall_Column)
		{
			cmatrix[index].infimum = cmatrix[row * rowSize + acutall_Column].infimum;
			cmatrix[index].supremum = cmatrix[row * rowSize + acutall_Column].supremum;
		}
	}
}


__global__
void EleminatePartGPUJordan(DirectedOrderNumber* devMatrix, DirectedOrderNumber* cmatrix, DirectedOrderNumber* bvector, int rowSize, int acutall_Column)
{
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * rowSize + column;
	DirectedOrderNumber tmp2(-1.0, -1.0);
	DirectedOrderNumber tmp(0.0, 0.0);
	if (index < rowSize * rowSize)
	{
		if (row != acutall_Column)
		{
			if (devMatrix[index].zeroFlag == false)
			{
				MultipleDirectedOrderNumber(&cmatrix[row * rowSize + acutall_Column], &devMatrix[(acutall_Column * rowSize) + column], &tmp);
				SubstractDirectedOrderNumber(&devMatrix[index], &tmp, &devMatrix[index]);
			}	
		}
		if (index < rowSize && index != acutall_Column)
		{
			MultipleDirectedOrderNumber(&cmatrix[column * rowSize + acutall_Column], &bvector[acutall_Column], &tmp2);
			SubstractDirectedOrderNumber(&bvector[index], &tmp2, &bvector[index]);
		}
		__syncthreads();
		if (column*rowSize*row == acutall_Column)
		{
			devMatrix[index].zeroFlag = true;
		}

		}
		
		
		__syncthreads();
}

__global__
void SetResolveVectorJordan(DirectedOrderNumber* matrix, DirectedOrderNumber* vector, int size)
{
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * size + column;

	if (index < size)
	{
		vector[index] = matrix[index * (size + 1)];
	}

}

__global__
void GetResovleVectorJordan(DirectedOrderNumber* diagonal, DirectedOrderNumber* bvector, DirectedOrderNumber* result, int size)
{
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * size + column;

	if (index < size)
	{
		DivideDirectedOrderNumber(&bvector[index], &diagonal[index], &result[index]);
	}

}


__global__
void printMatrix(DirectedOrderNumber* x, int size)
{
	int row = (blockIdx.y * blockDim.y) + threadIdx.y;
	int column = (blockIdx.x * blockDim.x) + threadIdx.x;
	int index = row * size + column;

	if (index < size)
	{
		printf(" watke: %d", index);
		printf(" kontrola: %f",x[index].infimum);
	}

}

DirectedOrderNumber *GaussJordanElemination(DirectedOrderNumber * hmatrix, DirectedOrderNumber* hvectorb, int size, int blockGridSize, int ThreadSize)
{
	DirectedOrderNumber* dMatrix, * dBVector, *cMatrix, *dResultVector;
	size_t matrixSize = size * size * sizeof(DirectedOrderNumber);
	size_t resultVectorSize = size * sizeof(DirectedOrderNumber);
	cudaEvent_t start, stop;
	cudaEvent_t start2;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventCreate(&start2);

	cudaMalloc((void**)&dMatrix, matrixSize);
	cudaMalloc((void**)&cMatrix, matrixSize);
	cudaMalloc((void**)&dBVector, resultVectorSize);
	cudaMalloc((void**)&dResultVector, resultVectorSize);
	cudaEventRecord(start);
	cudaMemcpy(dMatrix, hmatrix, matrixSize, cudaMemcpyHostToDevice);
	cudaMemcpy(dBVector, hvectorb, resultVectorSize, cudaMemcpyHostToDevice);

	dim3 blockGrid(blockGridSize, blockGridSize);
	dim3 threadGrid(ThreadSize, ThreadSize);
	cudaEventRecord(start2);
	for (int i = 0; i < size; i++)
	{
		SetCMatirxJordan << <blockGrid, threadGrid >> > (dMatrix, cMatrix, size, i);
		EleminatePartGPUJordan << <blockGrid, threadGrid >> > (dMatrix, cMatrix, dBVector, size, i);
		std::cout << "Aktualny krok: " << i << std::endl;
	}
	//printMatrix << <blockGrid, threadGrid >> > (dMatrix, size);
	DirectedOrderNumber *hostReulst;
	GetResovleVectorJordan << <blockGrid, threadGrid >> > (dMatrix, dBVector, dResultVector, size);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	float milliseconds = 0;
	float milisecondstwo = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);
	cudaEventElapsedTime(&milisecondstwo, start2, stop);

	std::cout << "Czas w milisekundach po stronie GPU:" << milliseconds << std::endl;
	std::cout << "Czas w milisekundach po stronie GPU bez alkoacji pamieci:" << milisecondstwo << std::endl;
	hostReulst = new DirectedOrderNumber[size];
	cudaMemcpy(hostReulst, dResultVector, resultVectorSize, cudaMemcpyDeviceToHost);

	cudaFree(dMatrix);
	cudaFree(dResultVector);
	cudaFree(cMatrix);
	cudaFree(dBVector);

	return hostReulst;
}


DirectedOrderNumber** SimpleSampleEquationFourRowsTest()
{

	DirectedOrderNumber** sample;
	sample = new DirectedOrderNumber * [4];

	for (int i = 0; i < 4; i++)
		sample[i] = new DirectedOrderNumber[5];

	sample[0][0].SetValues(2.01, 5.99);
	sample[0][1].SetValues(-3.01, -0.99);
	sample[0][2].SetValues(1.99, 4.01);
	sample[0][3].SetValues(-0.99, -3.01);
	sample[0][4].SetValues(4.01, 7.99);

	sample[1][0].SetValues(1.99, 4.01);
	sample[1][1].SetValues(0.99, 1.01);
	sample[1][2].SetValues(2.99, 3.01);
	sample[1][3].SetValues(0.99, 3.01);
	sample[1][4].SetValues(4.01, 9.99);

	sample[2][0].SetValues(1.01, 2.99);
	sample[2][1].SetValues(2.01, 3.99);
	sample[2][2].SetValues(1.99, 2.01);
	sample[2][3].SetValues(0.99, 1.01);
	sample[2][4].SetValues(7.99, 12.01);

	sample[3][0].SetValues(1.99, 2.01);
	sample[3][1].SetValues(-2.01, -1.99);
	sample[3][2].SetValues(2.99, 3.01);
	sample[3][3].SetValues(1.99, 2.01);
	sample[3][4].SetValues(2.01, 1.99);

	return sample;
}




class FileHelper
{

public:
	double precsiosn;
	FileHelper()
	{
		precsiosn = 0.00000001;
	}
	FileHelper(int prec)
	{
		precsiosn = prec;
	}
	std::string GetPathToSampleFolder()
	{
		char* buffer;

		if ((buffer = getcwd(NULL, 0)) == NULL) {
			perror("failed to get current directory\n");
		}
		else {

			std::string pathToCurrentDirectory(buffer);
			pathToCurrentDirectory += "\\Sample";
			free(buffer);
			return pathToCurrentDirectory;
		}
		return "";


	}
	bool CheckDirectoryExist()
	{
		std::string path = GetPathToSampleFolder();
		std::ifstream file(path.c_str());
		bool isTrue = file.good();
		return isTrue;

	}

	int  CreateSampleFolder()
	{
		std::string pathToFolder = "md " + GetPathToSampleFolder();
		int x = system(pathToFolder.c_str());
		return x;
	}

	bool ChcekEquationFolderExisst(std::string folderName)
	{
		std::string path = GetPathToSampleFolder() + "\\" + folderName;
		std::ifstream file(path.c_str());
		bool isTrue = file.good();
		return isTrue;
	}

	int CreateEquationFolder(std::string folderName)
	{
		if (ChcekEquationFolderExisst(folderName))
			return 0;
		std::string pathToFolder = "md " + GetPathToSampleFolder() + "\\" + folderName;
		int x = system(pathToFolder.c_str());
		return x;
	}



	void SaveEquation(DirectedOrderNumber** equation, int rows, std::string fileName, std::string folderName)
	{

		std::string pathToFile = GetPathToSampleFolder();
		std::ofstream myfile;
		try {

			myfile.open(pathToFile + "\\" + folderName + "\\" + fileName + ".txt");
			myfile << rows << "\n";
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < rows + 1; j++)
				{
					myfile << "(" << std::fixed << std::setprecision(precsiosn) << (double)equation[i][j].infimum << "," << std::fixed << std::setprecision(precsiosn) << (double)equation[i][j].supremum << ")";

					myfile << ";";
				}
				myfile << "\n";

			}

			myfile.close();
		}
		catch (std::ifstream::failure e)
		{
			printf("Exception");
		}
	}

	void SaveVectorToFile(DirectedOrderNumber* frevaluesVector, std::string fileName, std::string folderName, int rows)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" + folderName + "\\" + fileName + ".txt";
		std::ofstream myfile;

		try {

			myfile.open(pathToFile);

			for (int i = 0; i < rows; i++)
			{

				myfile << "(" << std::fixed << std::setprecision(precsiosn) << frevaluesVector[i].infimum << "," << std::fixed << std::setprecision(precsiosn) << frevaluesVector[i].supremum << ")";
				myfile << "\n";

			}

			myfile.close();
		}
		catch (std::ifstream::failure e)
		{
			printf("Exception");
		}
	}

	DirectedOrderNumber* ReadVectorFromFile(std::string fileName, std::string folderName, int rows)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" + folderName + "\\" + fileName + ".txt";
		std::ifstream file;

		DirectedOrderNumber* vector;


		file.open(pathToFile.c_str());
		if (!file) {
			printf("Cannot read file");
			return NULL;
		}
		else
		{
			int counter = 0;
			std::string line;
			vector = new DirectedOrderNumber[rows];
			while (std::getline(file, line, '\n'))
			{
				vector[counter] = GetDirectedOrderNumberFromString(line);
				counter++;
			}
			return vector;
		}
		return NULL;
	}

	bool FileExist(std::string filename, std::string folderName)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" + folderName + "\\" + filename + ".txt";
		std::ifstream file(pathToFile.c_str());
		bool isTrue = file.good();
		return isTrue;
	}


	DirectedOrderNumber** ReadEquation(std::string filename, std::string folderName, int* rowstoSave)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" + folderName + "\\" + filename + ".txt";
		std::ifstream file;

		DirectedOrderNumber** equation;

		file.open(pathToFile.c_str());
		if (!file) {
			printf("Cannot read file");
			equation = CreateMatrix(1);
		}
		else
		{
			std::string line;
			std::getline(file, line);
			*rowstoSave = std::atoi(line.c_str());
			//	rowstoSave = &rows;
			equation = CreateMatrix(*rowstoSave);


			line = "";
			int count = 0;
			std::vector<std::string>* splittedStrings;
			while (std::getline(file, line, '\n'))
			{
				splittedStrings = StringRowToVector(line);

				SetNumberRowFromText(splittedStrings, equation, *rowstoSave, count);
				delete(splittedStrings);
				count++;
			}
			int x = 5;
		}
		file.close();
		return equation;
	}

	std::vector<std::string>* StringRowToVector(std::string row)
	{
		std::stringstream ss(row);
		std::string item;
		std::vector<std::string>* splittedStrings;
		splittedStrings = new std::vector<std::string>();

		while (std::getline(ss, item, ';'))
		{
			splittedStrings->push_back(item);
		}

		return splittedStrings;
	}

	void SetNumberRowFromText(std::vector<std::string>* row, DirectedOrderNumber** equation, int rows, int counter)
	{

		DirectedOrderNumber* number;
		number = NULL;
		std::string numberString;

		for (int i = 0; i < rows + 1; i++)
		{
			number = GetDirectedOrderNumberFromString(row->at(i));
			equation[counter][i].infimum = number->infimum;
			equation[counter][i].supremum = number->supremum;
		}
		delete(number);

	}

	DirectedOrderNumber* GetDirectedOrderNumberFromString(std::string numberInString)
	{
		DirectedOrderNumber* number;

		number = new DirectedOrderNumber(0.0, 0.0);

		numberInString.erase(std::remove(numberInString.begin(), numberInString.end(), '('), numberInString.end());
		numberInString.erase(std::remove(numberInString.begin(), numberInString.end(), ')'), numberInString.end());

		std::stringstream ss(numberInString);
		std::string line;
		std::vector<std::string>* splittedStrings;
		splittedStrings = new std::vector<std::string>();

		while (std::getline(ss, line, ','))
		{
			splittedStrings->push_back(line);
		}

		number->SetValues(std::stod(splittedStrings->at(0), NULL), std::stod(splittedStrings->at(1), NULL));
		return number;
	}

	DirectedOrderNumber** CreateMatrix(int rows)
	{
		DirectedOrderNumber** equation;
		equation = new  DirectedOrderNumber * [rows];

		for (int i = 0; i < rows; i++)
		{
			equation[i] = new DirectedOrderNumber[rows + 1];
		}

		return equation;
	}

};

class DirectedOrderNumberGenerator
{
private:

	double GenerateNumber()
	{

		int floor = (int)lowerRange;
		int roof = (int)upperRange;

		double result = (double)(rand() % roof + 1.0);
		return result;
	}

	double CreateSampleInfimum()
	{
		return (GenerateNumber() - precision);
	}

	double CreateSampleSupremum()
	{
		return (GenerateNumber() + precision);
	}

	DirectedOrderNumber GenerateDirectedOrderNumber()
	{
		double generatedNumber = GenerateNumber();

		if (rand() % 100 + 1 % 2 != 0) {
			generatedNumber *= -1.0;
		}

		double halfNumber = generatedNumber / 2.0;
		DirectedOrderNumber result;

		if (rand() % 100 + 1 % 2 == 0)
			result.SetValues(halfNumber - precision, halfNumber + precision);
		else
			result.SetValues(halfNumber + precision, halfNumber - precision);
		return result;
	}


public:
	double precision;
	int lowerRange;
	int upperRange;
	DirectedOrderNumberGenerator(int low, int up, double prec)
	{
		srand((unsigned)time(0));
		lowerRange = low;
		upperRange = up;
		precision = prec;

	}

	DirectedOrderNumber* GenerateSampleVector(int rows)
	{
		DirectedOrderNumber* resultVector;
		resultVector = new DirectedOrderNumber[rows];
		for (int i = 0; i < rows; i++)
		{
			resultVector[i] = GenerateDirectedOrderNumber();
		}

		return resultVector;
	}

	DirectedOrderNumber** GenerateEquationwithoutFreeValues(int rows)
	{
		DirectedOrderNumber** equation;
		equation = new DirectedOrderNumber * [rows];

		for (int i = 0; i < rows; i++)
			equation[i] = new DirectedOrderNumber[rows + 1];

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows + 1; j++)
				equation[i][j] = GenerateDirectedOrderNumber();
			equation[i][rows] = GenerateDirectedOrderNumber();

		}

		return equation;
	}

	void GenereteFreeVaule(DirectedOrderNumber* equation, DirectedOrderNumber* resultVector, int rows)
	{

		DirectedOrderNumber tmp(0.0, 0.0);
		DirectedOrderNumber tmp2(0.0, 0.0);
		

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				tmp = GenerateDirectedOrderNumber();
				equation[i*rows+j].SetValues(tmp.infimum, tmp.supremum);
			}
			
			tmp2 = GenerateDirectedOrderNumber();
			resultVector[i].SetValues(tmp2.infimum, tmp2.supremum);
		
		}

	}


	void FillEquationWithFreeValues(DirectedOrderNumber** equation, DirectedOrderNumber* resultVector, int rows)
	{
		DirectedOrderNumber tmp(0.0, 0.0);
		//DirectedOrderNumber tmp2(0.0, 0.0);


		for (int i = 0; i < rows; i++)
		{	/*
			for (int j = 0; j < rows; j++)
			{
				tmp2 = operations.MultipleDirectedOrderNumber(equation[i][j], resultVector[i]);
				tmp = operations.AddDirectedOrderNumber(tmp, tmp2);
			}
			*/
			tmp = GenerateDirectedOrderNumber();
			equation[i][rows].SetValues(tmp.infimum, tmp.supremum);
		}
	}
};


std::string OptionList()
{

	std::string list = "1. Generete Equations Sample.\n";
	list += "2. Gauss Elimination.\n";
	list += "3. Gauss Jordan Elemination.\n";
	list += "4. Zaladuj uklad rownan z folderu Sample\n";
	return list;
}

int main()
{
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<double> elapsed;

	int rows = 0;
	int chose = 100;
	int blocks = 0;
	int threads = 0;
	DirectedOrderNumberGenerator generator(1, 10, 0.00000001);


	DirectedOrderNumber* matrixToVector;
	DirectedOrderNumber* bVector;

	std::string fileName, folderName; 

	std::cout << "Wybierz opcje\n";

	while (chose != 0)
	{
		std::cout << OptionList();
		std::cin >> chose;
		
		switch (chose)
		{
		case 1:
			std::cout << "podaj wielkosc ukladu rownan\n";
			std::cin >> rows;

	

			matrixToVector = new DirectedOrderNumber[rows * rows];
			bVector = new DirectedOrderNumber[rows];
			generator.GenereteFreeVaule(matrixToVector, bVector, rows);
			/*for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					std::cout << "liczba" << matrixToVector[i * rows + j].infimum << " ";
				}
				std::cout << std::endl;
			}
			*/
			break;

		case 2:
			std::cout << "wielkosc ukladu: " << rows << std::endl;
			std::cout << "Podaj ilosc blokow" << std::endl;
			std::cin >> blocks;
			std::cout << "Podaj ilosc w¹ktków w bloku" << std::endl;
			std::cin >> threads;

			std::cout << "Uruchiomienie algorytmu eliminacji Gaussa\n";
			start = std::chrono::high_resolution_clock::now();
			GaussElemination(matrixToVector, bVector, rows, blocks, threads);
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Czas trwania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
			break;

		case 3:
			std::cout << "wielkosc ukladu: " << rows << std::endl;
			std::cout << "Podaj ilosc blokow" << std::endl;
			std::cin >> blocks;
			std::cout << "Podaj ilosc w¹ktków w bloku" << std::endl;
			std::cin >> threads;

			std::cout << "Uruchiomienie algorytmu eliminacji Gaussa-Jordana\n";
			start = std::chrono::high_resolution_clock::now();
			//GaussEleminationGpu(matrixToVector, bVector, rows, blocks, threads);
			GaussJordanElemination(matrixToVector, bVector, rows, blocks, threads);
			end = std::chrono::high_resolution_clock::now();

			std::cout << "Czas trwania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";
			break;

		case 4:
			break;
		}
	}
	delete[] bVector;
	return 0;
}

