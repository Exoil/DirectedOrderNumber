#include "gtest/gtest.h"
#include "../DirectedOrderNumberEquationsCPU/DirectedEquation.cpp"



TEST(FileManager, GetPathToFileIsFalse) {

	FileHelper newFileHelper(9);
	bool token = newFileHelper.CheckDirectoryExist();
	EXPECT_FALSE(token);
	ASSERT_FALSE(token);

}

TEST(FileManager, GetPathToFileITrue) {

	FileHelper newFileHelper;
	bool token = newFileHelper.CheckDirectoryExist();
	EXPECT_TRUE(token);
	ASSERT_TRUE(token);

}

TEST(FileManager, CreateDirectory) {

	FileHelper newFileHelper;
	int token = newFileHelper.CreateSampleFolder();
	EXPECT_TRUE(token == 0);
	ASSERT_TRUE(token == 0);

}

TEST(FileManager, SaveEquation) {


	std::string fileName = "testUkladu";
	std::string folderName = "Testowa";
	FileHelper newFileHelper;
	DirectedOrderNumber** equation;
	equation = new  DirectedOrderNumber * [2];
	newFileHelper.CreateEquationFolder(folderName);
	for (int i = 0; i < 2; i++)
	{
		equation[i] = new DirectedOrderNumber[2 + 1];
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2 + 1; j++)
		{
			equation[i][j].SetValues((long double)(j + 0.1), long double(j + 0.1));
		}
	}



	newFileHelper.SaveEquation(equation, 2, fileName, folderName);
	bool token = newFileHelper.FileExist(fileName, folderName);
	for (int i = 0; i < 2; i++)
	{
		delete[](equation[i]);
	}
	delete[](equation);
	EXPECT_TRUE(token);
	ASSERT_TRUE(token);

}

TEST(FileManager, ReadEquation) {

	FileHelper newFileHelper;
	DirectedOrderNumber** equation;



	int rows = 0;
	std::string fileName = "testUkladu";
	std::string folderName = "Testowa";
	//	bool tokenFolder = newFileHelper.ChcekEquationFolderExisst(folderName);
	//	EXPECT_TRUE(tokenFolder);
	equation = newFileHelper.ReadEquation(fileName, folderName, &rows);

	bool token;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2 + 1; j++)
		{
			token = equation[i][j].infimum != NULL && equation[i][j].supremum != NULL;
		}
	}


	delete(equation);
	ASSERT_TRUE(token);


}

TEST(FileManager, SaveVector) {
	FileHelper newFileHelper(9);
	DirectedOrderNumber* vector;

	vector = new DirectedOrderNumber[2];

	for (int i = 0; i < 2; i++)
	{
		vector[i].infimum = (double)0.1 + i;
		vector[i].supremum = (double)0.2 + i;
	}

	std::string fileName = "testZapisuVektora";
	std::string folderName = "Testowa";

	newFileHelper.SaveVectorToFile(vector, fileName, folderName, 2);
	delete[] vector;
	ASSERT_TRUE(newFileHelper.FileExist(fileName, folderName));

}

TEST(FileManager, ReadVector) {
	std::string fileName = "testZapisuVektora";
	std::string folderName = "Testowa";
	FileHelper newFileHelper;
	DirectedOrderNumber* vector;

	vector = newFileHelper.ReadVectorFromFile(fileName, folderName, 2);
	bool token = vector != NULL;

	ASSERT_TRUE(token);
	delete[] vector;

}
