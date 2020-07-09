#include "pch.h"
#include "../CPUDirectedOrderNumberEquations/DirectedOrderNumberOperation.cpp"
#include <math.h>

TEST(Generator, GenerateReusltVector) {

	DirectedOrderNumber* resultVector;
	int rows = 5;
	resultVector = new DirectedOrderNumber[rows];

	DirectedOrderNumberGenerator* generator;

	generator = new DirectedOrderNumberGenerator(2, 5,0.00000001);

	resultVector = generator->GenerateSampleVector(rows);
	bool token;
	for (int i = 0; i < rows; i++)
	{
		token = (round(resultVector[i].infimum) >= 2.0 && round(resultVector[i].infimum) <= 5.0) && (round(resultVector[i].supremum) >= 2.0 && round(resultVector[i].supremum) <= 5.0);
		int x = 5;
	}

	delete(generator);

	delete[](resultVector);
	ASSERT_TRUE(token);
}


TEST(Generator, GenerateEquationWithoutFreeNumbers) {

	DirectedOrderNumber** equation;
	int rows = 5;

	DirectedOrderNumberGenerator* generator;

	generator = new DirectedOrderNumberGenerator(2, 5,0.00000001);

	equation = generator->GenerateEquationwithoutFreeValues(rows);
	delete(generator);
	bool token;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
			token = (equation[i][j].infimum >= 1.8 && equation[i][j].infimum <= 5.2) && (equation[i][j].supremum >= 1.8 && equation[i][j].supremum <= 5.2);
	}



	for (int i = 0; i < rows; i++)
	{
		delete[](equation[i]);
	}
	delete[](equation);
	ASSERT_TRUE(token);
}


TEST(Generator, GenerateFreeValues) {

	int rows = 5;

	DirectedOrderNumber** equationTwo;
	DirectedOrderNumber* resultVector;
	DirectedOrderNumber* freeVector;
	DirectedOrderNumberGenerator* generator;

	generator = new DirectedOrderNumberGenerator(2, 5, 0.00000001);

	resultVector = generator->GenerateSampleVector(rows);
	equationTwo = generator->GenerateEquationwithoutFreeValues(rows);
	freeVector = generator->GenereteFreeVaule(equationTwo,resultVector,rows);
	bool token;

	for (int i = 0; i < rows; i++)
	{
		token = freeVector[i].infimum != 0.0 && freeVector[i].supremum != 0.0;
	}
	
	for (int i = 0; i < rows; i++)
	{
		delete[](equationTwo[i]);
	}

	delete[](resultVector);
	delete[](freeVector);
	delete[](equationTwo);
	delete(generator);

	ASSERT_TRUE(token);
}






