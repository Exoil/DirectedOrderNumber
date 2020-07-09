#include <fstream>
#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include "DirectedOrderNumber.cpp"
#include <vector>
#include <sstream>
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



class FileHelper
{

public:
	int precsiosn;
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
	//		printf("%s \nLength: %zu\n", buffer, strlen(buffer));

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
		std::string path = GetPathToSampleFolder()+"\\"+folderName;
		std::ifstream file(path.c_str());
		bool isTrue = file.good();
		return isTrue;
	}

	int CreateEquationFolder(std::string folderName)
	{
		if (ChcekEquationFolderExisst(folderName))
			return 0;
		std::string pathToFolder = "md " + GetPathToSampleFolder()+"\\"+folderName;
		int x = system(pathToFolder.c_str());
		return x;
	}

	

	void SaveEquation(DirectedOrderNumber** equation, int rows,std::string fileName, std::string folderName)
	{
		
		std::string pathToFile = GetPathToSampleFolder();
		std::ofstream myfile;
		try {

		myfile.open(pathToFile + "\\" + folderName+ "\\"+ fileName + ".txt");
		myfile << rows << "\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows+1; j++)
			{
				myfile << "(" << std::fixed << std::setprecision(precsiosn) <<(double)equation[i][j].infimum << "," <<  std::fixed << std::setprecision(precsiosn) <<(double)equation[i][j].supremum << ")";
		
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
		std::string pathToFile = GetPathToSampleFolder()+"\\"+folderName+"\\"+fileName+".txt";
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

	DirectedOrderNumber* ReadVectorFromFile(std::string fileName, std::string folderName,int rows)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" + folderName+"\\" +fileName +".txt";
		std::ifstream file;

		DirectedOrderNumber* vector;

		
		file.open(pathToFile.c_str());
		if (!file) {
			printf("Cannot read file");
			return NULL;
		}
		else
		{
			int counter=0;
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

	bool FileExist(std::string filename,std::string folderName)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\"+folderName+"\\"+filename+".txt";
		std::ifstream file(pathToFile.c_str());
		bool isTrue = file.good();
		return isTrue;
	}


	DirectedOrderNumber** ReadEquation(std::string filename,std::string folderName, int *rowstoSave)
	{
		std::string pathToFile = GetPathToSampleFolder() + "\\" +folderName+ "\\" +filename + ".txt";
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
			std::vector<std::string> *splittedStrings;
			while (std::getline(file, line,'\n'))
			{
				splittedStrings = StringRowToVector(line);

				SetNumberRowFromText(splittedStrings,equation,*rowstoSave,count);
				delete(splittedStrings);
				count++;
			}
			int x = 5;
		}
		file.close();
		return equation;
	}

	std::vector<std::string> *StringRowToVector(std::string row)
	{
		std::stringstream ss(row);
		std::string item;
		std::vector<std::string> *splittedStrings;
		splittedStrings = new std::vector<std::string>();

		while (std::getline(ss, item, ';'))
		{
			splittedStrings->push_back(item);
		}

		return splittedStrings;
	}

	void SetNumberRowFromText(std::vector<std::string> *row , DirectedOrderNumber** equation, int rows, int counter)
	{
		
		DirectedOrderNumber *number;
		number = NULL;
		std::string numberString;

		for (int i = 0; i < rows+1; i++)
		{	
			number = GetDirectedOrderNumberFromString(row->at(i));
			equation[counter][i].infimum = number->infimum;
			equation[counter][i].supremum = number->supremum;
		}
		delete(number);
	
	}

	DirectedOrderNumber* GetDirectedOrderNumberFromString(std::string numberInString)
	{
		DirectedOrderNumber *number;

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



	DirectedOrderNumber** CreatMatrix(int rows)
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
