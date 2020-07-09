#include "./DirectedOrderNumber.cpp"
#include <vector>
#include <string>
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
#include <stdlib.h>
#include <iostream>

class DirectedOrderNumberArithmetic
{
public:
	void AddDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
	{
		result->SetValues(firstValue->infimum+ secondValue->infimum, firstValue->supremum + secondValue->supremum);
	}
	void SubstractDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
	{
		result->SetValues(firstValue->infimum - secondValue->infimum, firstValue->supremum - secondValue->supremum);
	}
	void MultipleDirectedOrderNumber(DirectedOrderNumber* firstNumber, DirectedOrderNumber* secondNumber, DirectedOrderNumber* result) {

		double* multipleResult;
		multipleResult = new double[4];

		multipleResult[0] = (firstNumber->infimum * secondNumber->infimum);
		multipleResult[1] = (firstNumber->infimum * secondNumber->supremum);
		multipleResult[2] = (firstNumber->supremum * secondNumber->supremum);
		multipleResult[3] = (firstNumber->supremum * secondNumber->infimum);
		std::sort(multipleResult, multipleResult + 4);
		result->infimum = multipleResult[0];
		result->supremum = multipleResult[3];
		delete[](multipleResult);
	}

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
			secondNumber->infimum = (1.0);
			secondNumber->supremum = (1.0);
			DivideDirectedOrderNumber(firstNumber, secondNumber, result);
		}	
	
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
			equation[i][rows].SetValues(0.0, 0.0);

		}

		return equation;
	}

	DirectedOrderNumber* GenereteFreeVaule(DirectedOrderNumber** equation, DirectedOrderNumber* resultVector, int rows)
	{
		DirectedOrderNumberArithmetic operations;
		DirectedOrderNumber* freeVector;
		freeVector = new DirectedOrderNumber[rows];
		DirectedOrderNumber tmp(0.0, 0.0);


		for (int i = 0; i < rows; i++)
		{
			tmp = GenerateDirectedOrderNumber();
			freeVector[i].SetValues(tmp.infimum, tmp.supremum);
		}

		return freeVector;
	}


	void FillEquationWithFreeValues(DirectedOrderNumber** equation, DirectedOrderNumber* resultVector, int rows)
	{
		DirectedOrderNumber tmp(0.0, 0.0);

		DirectedOrderNumberArithmetic operations;

		for (int i = 0; i < rows; i++)
		{
			tmp = GenerateDirectedOrderNumber();
			equation[i][rows].SetValues(tmp.infimum, tmp.supremum);
		}
	}



	DirectedOrderNumber** SimpleSampleEquationTest()
	{

		DirectedOrderNumber** sample;
		sample = new DirectedOrderNumber * [2];

		for (int i = 0; i < 2; i++)
			sample[i] = new DirectedOrderNumber[3];

		sample[0][0].SetValues(1.99999999, 2.00000001);
		sample[0][1].SetValues(2.99999999, 3.00000001);
		sample[0][2].SetValues(6.99999999, 7.00000001);
		sample[1][0].SetValues(-1.00000001, -0.99999999);
		sample[1][1].SetValues(3.99999999, 4.00000001);
		sample[1][2].SetValues(1.99999999, 2.00000001);

		return sample;
	}

	DirectedOrderNumber** SimpleSampleEquationFourRowsTest()
	{

		DirectedOrderNumber** sample;
		sample = new DirectedOrderNumber * [4];

		for (int i = 0; i < 4; i++)
			sample[i] = new DirectedOrderNumber[5];

		sample[0][0].SetValues(2.01,5.99);
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
	DirectedOrderNumber** SimpleSampleForPivotEquationTest()
	{

		DirectedOrderNumber** sample;
		sample = new DirectedOrderNumber * [2];

		for (int i = 0; i < 2; i++)
			sample[i] = new DirectedOrderNumber[3];

		sample[1][0].SetValues(1.99999999, 2.00000001);
		sample[1][1].SetValues(2.99999999, 3.00000001);
		sample[1][2].SetValues(6.99999999, 7.00000001);
		sample[0][0].SetValues(-1.00000001, -0.99999999);
		sample[0][1].SetValues(3.99999999, 4.00000001);
		sample[0][2].SetValues(1.99999999, 2.00000001);

		return sample;
	}

	DirectedOrderNumber** PivotSimpleSampleEquationTest()
	{

		DirectedOrderNumber** sample;
		sample = new DirectedOrderNumber * [2];

		for (int i = 0; i < 2; i++)
			sample[i] = new DirectedOrderNumber[3];

		sample[0][0].SetValues(1.99999999, 2.00000001);
		sample[0][1].SetValues(2.99999999, 3.00000001);
		sample[0][2].SetValues(6.99999999, 7.00000001);
		sample[1][0].SetValues(1.00000001, 6.99999999);
		sample[1][1].SetValues(3.99999999, 4.00000001);
		sample[1][2].SetValues(1.99999999, 2.00000001);

		return sample;
	}

	DirectedOrderNumber** SimpleSampleEquationTestSecond()
	{

		DirectedOrderNumber** sample;
		sample = new DirectedOrderNumber * [3];

		for (int i = 0; i < 3; i++)
			sample[i] = new DirectedOrderNumber[3 + 1];

		sample[0][0].SetValues(4.99999999, 5.00000001);
		sample[0][1].SetValues(-4.00000001, -2.99999999);
		sample[0][2].SetValues(1.99999999, 3.00000001);
		sample[0][3].SetValues(4.00000001, 4.99999999);

		sample[1][0].SetValues(0.99999999, 2.00000001);
		sample[1][1].SetValues(2.99999999, 3.00000000001);
		sample[1][2].SetValues(2.99999999, 2.00000001);
		sample[1][3].SetValues(-6.00000001, -2.99999999);

		sample[2][0].SetValues(2.99999999, 6.00000001);
		sample[2][1].SetValues(1.99999999, 1.00000001);
		sample[2][2].SetValues(-1.00000001, -0.99999999);
		sample[2][3].SetValues(-4.99999999, 2.99999999);

		return sample;
	}


};


class DirectedEquationMethod {


public:
	DirectedOrderNumberArithmetic* operation;
	double precison;
	DirectedEquationMethod(double precison)
	{
		operation = new  DirectedOrderNumberArithmetic();
		this->precison = precison;
	}

	~DirectedEquationMethod()
	{
		delete operation;
	}

	void SetElimantedZeroToken(DirectedOrderNumber** equation, int rows, int i)
	{
		for (int l = 0; l < rows; l++)
		{
			if (l != i)
				equation[l][i].zeroFlag = true;
		}
	}

	void EleminatePart(DirectedOrderNumber** equation, int rows)
	{   
		int i, j;
		DirectedOrderNumber *mnoznik;
		DirectedOrderNumber *minus;
		DirectedOrderNumber* tmp;
		mnoznik = new DirectedOrderNumber();
		minus = new DirectedOrderNumber(-1.0, -1.0);
		tmp = new DirectedOrderNumber(0.0, 0.0);


		for (i = 0; i < rows - 1; i++)
		{
			for (j = i + 1; j < rows; j++)
			{
				operation->MultipleDirectedOrderNumber(minus, &equation[j][i],minus);
				operation->DivideDirectedOrderNumber(minus, &equation[i][i], mnoznik);
				
				for (int k = i; k <= rows; k++)
				{
					operation->MultipleDirectedOrderNumber(mnoznik, &equation[i][k], tmp);
					operation->AddDirectedOrderNumber(&equation[j][k], tmp, &equation[j][k]);
				
				}
	//			std::cout << std::setprecision(8) << "inf " << equation[i][j].infimum << " sup " << equation[i][j].supremum;
			}

			std::cout <<"Krok: " <<i<< std::endl;
	//		
		
			SetElimantedZeroToken(equation, rows, i);
			tmp->SetValues(0.0, 0.0);
			minus->SetValues(-1.0, -1.0);
			mnoznik->SetValues(0.0, 0.0);
		}
		delete tmp;
		delete minus;
		delete mnoznik;
	}

	DirectedOrderNumber* VectorResult(DirectedOrderNumber** equation, int rows)
	{
		int i, j;
		DirectedOrderNumber *sum,*tmp;
		DirectedOrderNumber* vectorResult;
		vectorResult = new DirectedOrderNumber[rows];
		sum = new DirectedOrderNumber(0.0, 0.0);
		tmp = new DirectedOrderNumber(0.0, 0.0);
		for (int k = 0; k < rows; k++)
		{
			vectorResult[k].SetValues(1.0, 1.0);
		}

		for (i = rows - 1; i >= 0; i--)
		{
			sum->SetValues(equation[i][rows].infimum, equation[i][rows].supremum);
			for (j = rows - 1; j >= i + 1; j--)
			{
				operation->MultipleDirectedOrderNumber(&equation[i][j], &vectorResult[j], tmp);
				operation->SubstractDirectedOrderNumber(sum, tmp, sum);				
			}
			operation->DivideDirectedOrderNumber(sum, &equation[i][i],&vectorResult[i]);
		}

		return vectorResult;
	}

	DirectedOrderNumber* GaussElemination(DirectedOrderNumber** equation, int rows)
	{

		DirectedOrderNumber* resultVector;
		EleminatePart(equation, rows);
		resultVector = VectorResult(equation, rows);
		return resultVector;
	}


	int FindMaxInColumn(DirectedOrderNumber** equation, int column, int row, int rows)
	{
		int indexWithMaxValue = row;

		for (int i = row + 1; i < rows; i++)
		{

			if (equation[indexWithMaxValue][column].GetAbsoulteRealNumber() < equation[i][column].GetAbsoulteRealNumber()) {
				indexWithMaxValue = i;
			}
		}

		return indexWithMaxValue;
	}

	void PartialPivot(DirectedOrderNumber** equation, int rows, int firstIndexToSwap, int secondIndexToSwap)
	{

		DirectedOrderNumber *rowTmp;

		rowTmp = NULL;

		for (int i = 0; i < rows + 1; i++)
		{
			rowTmp = new DirectedOrderNumber(equation[firstIndexToSwap][i].infimum, equation[firstIndexToSwap][i].supremum);

			equation[firstIndexToSwap][i].SetValues(equation[secondIndexToSwap][i].infimum, equation[secondIndexToSwap][i].supremum);
			equation[secondIndexToSwap][i].SetValues(rowTmp->infimum, rowTmp->supremum);

			int x = 5;
		}
		delete rowTmp;

	}


	void EleminatePartWithPivot(DirectedOrderNumber** equation, int rows)
	{   //iteratory
		int i, j;
		int indexPivot = -1;
		int indexToswap = -1;
		DirectedOrderNumber* mnoznik;
		DirectedOrderNumber* minus;
		DirectedOrderNumber* tmp;
		mnoznik = new DirectedOrderNumber();
		minus = new DirectedOrderNumber(-1.0, -1.0);
		tmp = new DirectedOrderNumber(0.0, 0.0);

		for (i = 0; i < rows - 1; i++)
		{
			indexPivot = i;
			indexToswap = FindMaxInColumn(equation, i, i, rows);

			if (indexPivot != indexToswap)
				PartialPivot(equation, rows, indexPivot, indexToswap);

			for (j = i + 1; j < rows; j++)
			{


				operation->MultipleDirectedOrderNumber(minus, &equation[j][i], minus);
				operation->DivideDirectedOrderNumber(minus, &equation[i][i], mnoznik);
				for (int k = i; k <= rows; k++)
				{
					operation->MultipleDirectedOrderNumber(mnoznik, &equation[i][k], tmp);
					operation->AddDirectedOrderNumber(&equation[j][k], tmp, &equation[j][k]);

				}
			}
			SetElimantedZeroToken(equation, rows, i);
		
		}

	}

	DirectedOrderNumber* GaussEleminationWithPivot(DirectedOrderNumber** equation, int rows)
	{
		DirectedOrderNumber* resultVector;
		resultVector = new DirectedOrderNumber[rows];

		EleminatePartWithPivot(equation, rows);

		resultVector = VectorResult(equation, rows);

		return resultVector;
	}
	
	void ElemintPartJordan(DirectedOrderNumber** equation, int rows)
	{
		DirectedOrderNumber *tmp;
		DirectedOrderNumber *tmp2;
		DirectedOrderNumber *minus;
		DirectedOrderNumberArithmetic* operations;
		tmp = new DirectedOrderNumber(0.0, 0.0);
		tmp2 = new DirectedOrderNumber(0.0, 0.0);
		minus = new DirectedOrderNumber(-1.0, -1.0);
		operations = new  DirectedOrderNumberArithmetic();
		for (int i = 0; i < rows; i++)
		{	for (int j = 0; j < rows; j++)
			{	if (j != i)
				{	operations->DivideDirectedOrderNumber(&equation[j][i], &equation[j][j], tmp);
					operations->MultipleDirectedOrderNumber(minus,tmp,minus);
					for (int k = 0; k < rows + 1; k++)
					{
						if (equation[i][k].zeroFlag != true)
						{
							operations->MultipleDirectedOrderNumber(tmp, &equation[i][k],tmp2);
							operations->AddDirectedOrderNumber(&equation[j][k], tmp2, &equation[j][k]);
						}
					}
				}
				minus->SetValues(-1.0, -1.0);
			}
			std::cout << "Krok: " << i << std::endl;
			SetElimantedZeroToken(equation, rows, i);
		}
		delete tmp;
		delete tmp2;
		delete minus;
		delete(operations);
	}

	DirectedOrderNumber* JordanVector(DirectedOrderNumber** equation, int rows)
	{
		DirectedOrderNumber* resultVector;
		DirectedOrderNumberArithmetic operation;
		DirectedOrderNumber *tmp;
		tmp = new DirectedOrderNumber(0.0, 0.0);
		resultVector = new DirectedOrderNumber[rows];

		for (int i = 0; i < rows; i++)
		{
			operation.DivideDirectedOrderNumber(&equation[i][rows], &equation[i][i], tmp);
			resultVector[i].SetValues(tmp->infimum, tmp->supremum);

		}

		return resultVector;

	}

	DirectedOrderNumber* GaussJordanElemination(DirectedOrderNumber** equation, int rows)
	{
		DirectedOrderNumber* resultVector;
		ElemintPartJordan(equation, rows);
		resultVector = JordanVector(equation, rows);
		return resultVector;
	}
};


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
