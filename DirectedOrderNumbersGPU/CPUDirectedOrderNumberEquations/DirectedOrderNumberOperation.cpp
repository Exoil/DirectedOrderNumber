#include "FileHelper.cpp"

class DirectedOrderNumberOperation
{
public:

	DirectedOrderNumberOperation()
	{
	}
	

	~DirectedOrderNumberOperation()
	{
	
	}

	void AddDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
	{
		result->infimum = firstValue->infimum + secondValue->infimum;
		result->supremum = firstValue->supremum + secondValue->supremum;
	}


	DirectedOrderNumber AddDirectedOrderNumber(DirectedOrderNumber firstValue, DirectedOrderNumber secondValue)
	{
		DirectedOrderNumber result(firstValue.infimum + secondValue.infimum, firstValue.supremum + secondValue.supremum);

		return result;
	}

	void SubstractDirectedOrderNumber(DirectedOrderNumber* firstValue, DirectedOrderNumber* secondValue, DirectedOrderNumber* result)
	{
		result->infimum = firstValue->infimum - secondValue->infimum;
		result->supremum = firstValue->supremum - secondValue->supremum;
	}

	DirectedOrderNumber SubstractDirectedOrderNumber(DirectedOrderNumber firstValue, DirectedOrderNumber secondValue)
	{
		DirectedOrderNumber result(firstValue.infimum - secondValue.infimum, firstValue.supremum - secondValue.supremum);
		return result;
	}

	void MultipleDirectedOrderNumber(DirectedOrderNumber* firstNumber, DirectedOrderNumber* secondNumber, DirectedOrderNumber* result)
	{
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

	DirectedOrderNumber MultipleDirectedOrderNumber(DirectedOrderNumber firstNumber, DirectedOrderNumber secondNumber)
	{
		

		double* multipleResult;
		multipleResult = new double[4];

		multipleResult[0] = (firstNumber.infimum * secondNumber.infimum);
		multipleResult[1] = (firstNumber.infimum * secondNumber.supremum);
		multipleResult[2] = (firstNumber.supremum * secondNumber.supremum);
		multipleResult[3] = (firstNumber.supremum * secondNumber.infimum);


		std::sort(multipleResult, multipleResult + 4);

		
		DirectedOrderNumber result(multipleResult[0], multipleResult[3]);
		delete[](multipleResult);

		return result;
	}


	DirectedOrderNumber DivideDirectedOrderNumber(DirectedOrderNumber firstNumber, DirectedOrderNumber secondNumber)
	{
		DirectedOrderNumber result;

		if (firstNumber.GetDivideType() == GreaterThanZero && secondNumber.GetDivideType() == GreaterThanZero)
		{
			result.infimum = firstNumber.infimum / secondNumber.infimum;
			result.supremum = firstNumber.supremum / secondNumber.supremum;
		}

		else if (firstNumber.GetDivideType()  == LesserThanZero && secondNumber.GetDivideType() == LesserThanZero)
		{
			result.supremum = firstNumber.infimum / secondNumber.infimum;
			result.infimum = firstNumber.supremum / secondNumber.supremum;
		}
		else if (firstNumber.GetDivideType() == GreaterThanZero && secondNumber.GetDivideType() == LesserThanZero)
		{
			result.infimum = firstNumber.supremum / secondNumber.infimum;
			result.supremum = firstNumber.infimum / secondNumber.supremum;
		}
		else if (firstNumber.GetDivideType() == LesserThanZero && secondNumber.GetDivideType() == GreaterThanZero)
		{
			result.infimum = firstNumber.infimum / secondNumber.supremum;
			result.supremum = firstNumber.supremum / secondNumber.infimum;
		}

		else if (firstNumber.GetDivideType() == HaveZero  && secondNumber.GetDivideType() == GreaterThanZero)
		{
			result.infimum = firstNumber.infimum / secondNumber.supremum;
			result.supremum = firstNumber.supremum / secondNumber.supremum;
		}
		else if (firstNumber.GetDivideType() == HaveZero && secondNumber.GetDivideType() == LesserThanZero)
		{
			result.infimum = firstNumber.supremum / secondNumber.infimum;
			result.supremum = firstNumber.infimum / secondNumber.infimum;
		}
		
		else if (firstNumber.GetDivideType() == GreaterThanZero && secondNumber.GetDivideType() == HaveZero)
		{
			double RealNumber = firstNumber.GetRealNumber() / secondNumber.GetRealNumber();

			double newSupremum = (RealNumber * 2) + (-1 * firstNumber.infimum);

			result.SetValues(firstNumber.infimum, newSupremum);


		}
		
 		return result;
	}

	void DivideDirectedOrderNumber(DirectedOrderNumber* firstNumber, DirectedOrderNumber* secondNumber, DirectedOrderNumber* result)
	{
		if (firstNumber->GetDivideType() == GreaterThanZero && secondNumber->GetDivideType() == GreaterThanZero)
		{
			result->infimum = firstNumber->infimum / secondNumber->infimum;
			result->supremum = firstNumber->supremum / secondNumber->supremum;
		}

		else if (firstNumber->GetDivideType() == LesserThanZero &&  secondNumber->GetDivideType() == LesserThanZero)
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
		else if (firstNumber->GetDivideType() == GreaterThanZero && secondNumber->GetDivideType() == HaveZero)
		{
			double RealNumber = firstNumber->GetRealNumber() / secondNumber->GetRealNumber();

			double newSupremum = (RealNumber * 2) + (-1 * firstNumber->infimum);

			result->SetValues(firstNumber->infimum, newSupremum);

		}
	
	}



	void GaussEleimationDirectedArth(DirectedOrderNumber **equation, int rows, double precision)
	{
		std::vector<double> result;

		int i = 0;
		int j = 0;
		int k = 0;
		DirectedOrderNumber mnoznik(0.0, 0.0);
		DirectedOrderNumber sumaIloczynow(0.0, 0.0);
		DirectedOrderNumber tmp(0.0, 0.0);
		DirectedOrderNumber ujemna(-1.0, -1.0);
		DirectedOrderNumber tmp2;

		for (int i = 0; i < rows; i++)
		{
			for (j = i + 1; j < rows; j++)
			{
				tmp.infimum = equation[j][i].infimum;
				tmp.supremum = equation[j][i].supremum;
				tmp = MultipleDirectedOrderNumber(tmp, ujemna);
				mnoznik = DivideDirectedOrderNumber(tmp, equation[i][i]);
				for (k = 0; k <= rows; k++)
				{
					tmp2 = MultipleDirectedOrderNumber(mnoznik, equation[i][k]);

					equation[j][k] = AddDirectedOrderNumber(equation[j][k], tmp2);

					if (abs(equation[j][k].GetRealNumber()) < precision)
					{
						equation[j][k].infimum = 0.0;
						equation[j][k].supremum = 0.0;
					}

					if (abs(equation[j][k].infimum) < precision)
						equation[j][k].infimum = 0.0;

					if (abs(equation[j][k].supremum) < precision)
						equation[j][k].supremum = 0.0;

				}
			}
		}

	}

};

class DirectedOrderNumberGenerator
{
private:
	/*double Generatelongdouble()
	{
		return ((double)rand() * (upperRange - lowerRange)) / (double)RAND_MAX + lowerRange;
	}*/

	double GenerateNumber()
	{
		
		int floor = (int)lowerRange;
		int roof = (int)upperRange;

		double result = (double)(rand() % roof+1.0);
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

		if(rand()%100+1%2 == 0)
			result.SetValues(halfNumber - precision, halfNumber + precision);
		else
			result.SetValues(halfNumber + precision,halfNumber - precision);
		return result;
	}


public:

	void FillEquationWithFreeValues(DirectedOrderNumber** equation, DirectedOrderNumber* resultVector, int rows)
	{
		DirectedOrderNumber tmp(0.0, 0.0);
		//DirectedOrderNumber tmp2(0.0, 0.0);
		DirectedOrderNumberOperation operations;

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


class DirectedEquationMethod {


public:
	DirectedOrderNumberOperation *operation;
	double precison;
	DirectedEquationMethod(double precison)
	{
		operation = new DirectedOrderNumberOperation();
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
	{   //iteratory
		int i, j;
		DirectedOrderNumber mnoznik(0.0, 0.0);

		for (i = 0; i < rows - 1; i++)
		{
			for (j = i + 1; j < rows; j++)
			{

				mnoznik = operation->DivideDirectedOrderNumber(operation->MultipleDirectedOrderNumber(DirectedOrderNumber(-1.00000000, -1.00000000), equation[j][i]), equation[i][i]);
				for (int k = i; k <= rows; k++)
				{
					DirectedOrderNumber tmp0 = equation[i][k];
					DirectedOrderNumber tmp2 = equation[j][k];
					DirectedOrderNumber tmp1 = operation->MultipleDirectedOrderNumber(mnoznik, tmp0);
					equation[j][k] = operation->AddDirectedOrderNumber(equation[j][k], tmp1);

				}
			}
			SetElimantedZeroToken(equation, rows, i);
		}

	}

	DirectedOrderNumber* VectorResult(DirectedOrderNumber** equation, int rows)
	{
		int i, j;

		DirectedOrderNumber suma(0.0, 0.0);
		DirectedOrderNumber* vectorResult;
		vectorResult = new DirectedOrderNumber[rows];

		for (int k = 0; k < rows; k++)
		{
			vectorResult[k].SetValues(1.0, 1.0);
		}


		for (i = rows - 1; i >= 0; i--)
		{
			//współczynnik wyrazu wolnego
			suma = equation[i][rows];
			for (j = rows - 1; j >= i+1; j--)
			{
				suma = operation->SubstractDirectedOrderNumber(suma, operation->MultipleDirectedOrderNumber(equation[i][j], vectorResult[j]));
			}
			vectorResult[i] = operation->DivideDirectedOrderNumber(suma, equation[i][i]);
		}

		return vectorResult;
	}

	DirectedOrderNumber* GaussElemination(DirectedOrderNumber** equation, int rows)
	{	

		
		DirectedOrderNumber* resultVector;
		EleminatePart(equation, rows);
		resultVector = VectorResult(equation,rows);

		return resultVector;
	}


	int FindMaxInColumn(DirectedOrderNumber** equation, int column, int row, int rows)
	{
		int indexWithMaxValue = row;

		for (int i = row+1; i < rows; i++)
		{
		
			if (equation[indexWithMaxValue][column].GetAbsoulteRealNumber() < equation[i][column].GetAbsoulteRealNumber()){
				indexWithMaxValue = i;
			}
		}

		return indexWithMaxValue;
	}

	void PartialPivot(DirectedOrderNumber** equation, int rows, int firstIndexToSwap, int secondIndexToSwap)
	{

		DirectedOrderNumber rowTmp;


		for (int i = 0; i < rows + 1; i++)
		{
			rowTmp = new DirectedOrderNumber(equation[firstIndexToSwap][i].infimum, equation[firstIndexToSwap][i].supremum);
		
			equation[firstIndexToSwap][i].SetValues(equation[secondIndexToSwap][i].infimum, equation[secondIndexToSwap][i].supremum);
			equation[secondIndexToSwap][i].SetValues(rowTmp.infimum, rowTmp.supremum);

			int x = 5;
		}

	
	}



	void EleminatePartWithPivot(DirectedOrderNumber** equation, int rows)
	{   //iteratory
		int i, j;
		int indexPivot = -1;
		int indexToswap = -1;
		DirectedOrderNumber mnoznik(0.0, 0.0);
		
		for (i = 0; i < rows - 1; i++)
		{
			indexPivot = i;
			indexToswap = FindMaxInColumn(equation, i, i, rows);

			if(indexPivot != indexToswap)
				PartialPivot(equation, rows, indexPivot, indexToswap);

			for (j = i + 1; j < rows; j++)
			{

				mnoznik = operation->DivideDirectedOrderNumber(operation->MultipleDirectedOrderNumber(DirectedOrderNumber(-1.00000000, -1.00000000), equation[j][i]), equation[i][i]);
				for (int k = i; k <= rows; k++)
				{
					DirectedOrderNumber tmp0 = equation[i][k];
					DirectedOrderNumber tmp2 = equation[j][k];
					DirectedOrderNumber tmp1 = operation->MultipleDirectedOrderNumber(mnoznik, tmp0);
					equation[j][k] = operation->AddDirectedOrderNumber(equation[j][k], tmp1);

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
		DirectedOrderNumber tmp(0.0, 0.0);
		DirectedOrderNumber tmp2(0.0, 0.0);
		DirectedOrderNumber Minus(-1.0, -1.0);
		DirectedOrderNumberOperation* operations;

		operations = new DirectedOrderNumberOperation();

		//iteratory
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (j != i)
				{
					tmp = operations->MultipleDirectedOrderNumber(Minus,operations->DivideDirectedOrderNumber(equation[j][i], equation[j][j]));
					for (int k = 0; k < rows + 1; k++)
					{
						if (equation[i][k].zeroFlag != true)
						{
							tmp2 = operations->MultipleDirectedOrderNumber(tmp, equation[i][k]);
							equation[j][k] = operations->AddDirectedOrderNumber(equation[j][k], tmp2);
						}
					}

				}
				
			}
			SetElimantedZeroToken(equation, rows, i);
	
		}

		delete(operations);
	}

	DirectedOrderNumber* JordanVector(DirectedOrderNumber** equation, int rows)
	{
		DirectedOrderNumber* resultVector;
		DirectedOrderNumberOperation operation;
		DirectedOrderNumber tmp(0.0,0.0);
		resultVector = new DirectedOrderNumber[rows];

		for (int i = 0; i < rows; i++) 
		{
		tmp = operation.DivideDirectedOrderNumber(equation[i][rows], equation[i][i]);
		resultVector[i].SetValues(tmp.infimum, tmp.supremum);

		}

			return resultVector;
		
	}
	
	DirectedOrderNumber* GaussJordanElemination(DirectedOrderNumber** equation, int rows)
	{

	
		DirectedOrderNumber* resultVector;
		ElemintPartJordan(equation, rows);

		/*
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{

				printf("(%10.8f,%10.8f) ", equation[i][j].infimum, equation[i][j].supremum);
			}

			printf("\n");
		}
		*/

		resultVector = JordanVector(equation,rows);
		return resultVector;
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
			sample[i] = new DirectedOrderNumber[3+1];

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