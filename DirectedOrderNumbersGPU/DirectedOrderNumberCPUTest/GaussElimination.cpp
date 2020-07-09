#include "pch.h"
#include "../CPUDirectedOrderNumberEquations/DirectedOrderNumberOperation.cpp"
#include <math.h>

TEST(GaussElemination, EliminacjaGaussa)
{
	DirectedOrderNumber** sampleEquation;
	DirectedEquationMethod* operations;
	DirectedOrderNumber* resultVector;
	DirectedOrderNumber test;
	operations = new DirectedEquationMethod(0.000000001);

	sampleEquation = operations->SimpleSampleEquationTest();

	resultVector =  operations->GaussElemination(sampleEquation, 2);
	
	std::cerr << "Pierwszy X Infimum: " << round(resultVector[0].infimum) << std::endl;
	std::cerr << " Pierwszy X Supremum: " << round(resultVector[0].supremum) << std::endl;

	std::cerr << "Drugi X Infimum: " << round(resultVector[1].infimum) << std::endl;
	std::cerr << " Drugi X Supremum: " << round(resultVector[2].supremum) << std::endl;

	bool tokenFirst = round(resultVector[0].infimum) == 2.00000000 && round(resultVector[0].supremum) == 2;
	bool tokenSecond = round(resultVector[1].infimum) == 1.00000000 && round(resultVector[1].supremum) == 1.000000000;

	

	for (int i = 0; i < 2; i++)
	{
		delete[](sampleEquation[i]);
	}

	delete operations;
	delete[] sampleEquation;
	delete[] resultVector;


	ASSERT_TRUE(tokenFirst && tokenSecond);
}


TEST(GaussElemination, EtapEliminacji)
{
	DirectedOrderNumber** sampleEquation;
	
	DirectedEquationMethod* operations;
	DirectedOrderNumber test;
	operations = new DirectedEquationMethod(0.000000001);

	sampleEquation = operations->SimpleSampleEquationTest();
	
	operations->EleminatePart(sampleEquation, 2);


	std::cerr << "Infimum: "<< round(sampleEquation[1][0].infimum) << std::endl;
	std::cerr << "Supremum: " << round(sampleEquation[1][0].supremum) << std::endl;
	bool tokenFirst = round(sampleEquation[1][0].infimum) == 0.0 && round(sampleEquation[1][0].supremum) == 0.0;

	for (int i = 0; i < 2; i++)
	{
		delete[](sampleEquation[i]);
	}

	delete operations;
	delete[] sampleEquation;

	ASSERT_TRUE(tokenFirst);
}



TEST(GaussElemination, FindMaxInColumnFirstRow)
{
	DirectedOrderNumber** sampleEquation;
	DirectedEquationMethod* operations;
	operations = new DirectedEquationMethod(0.000001);
	sampleEquation = operations->SimpleSampleEquationTest();

	int index = operations->FindMaxInColumn(sampleEquation, 0, 0, 2);

	for (int i = 0; i < 2; i++)
	{
		delete[](sampleEquation[i]);
	}

	delete operations;
	delete[] sampleEquation;

	ASSERT_TRUE(index == 0);
}

TEST(GaussElemination, Pivot)
{
	DirectedOrderNumber** sampleEquation;
	DirectedEquationMethod* operations;
	DirectedOrderNumber* testExample;

	testExample = new DirectedOrderNumber(1.00000001, 6.99999999);

	operations = new DirectedEquationMethod(0.000001);
	sampleEquation = operations->PivotSimpleSampleEquationTest();

	int indexToPivot = 0;
	int indexToSwap = operations->FindMaxInColumn(sampleEquation, 0, 0, 2);

	operations->PartialPivot(sampleEquation, 2, indexToPivot, indexToSwap);

	bool token = sampleEquation[0][0].GetAbsoulteRealNumber() == testExample->GetAbsoulteRealNumber();


	ASSERT_TRUE(token);
}


