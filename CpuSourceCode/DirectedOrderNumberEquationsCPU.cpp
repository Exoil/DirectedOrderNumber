#include <iostream>
#include "../DirectedOrderNumberEquationsCPU/DirectedEquation.cpp"
#include <chrono>  // for high_resolution_clock
using namespace std;
string OptionList() 
{

	string result = "1. Generate Equations Sample.\n";
	result += "2. Gauss Elimination.\n";
	result += "3. Gauss Jordan Elemination.\n";
	result += "4. Zaladuj uklad rownan z folderu Sample\n";
	return result;
}



int main()
{

	chrono::steady_clock::time_point start, end;
	chrono::duration<double> elapsed;
	int rows = 0;
	DirectedOrderNumber** equation;
	equation = NULL;
	DirectedOrderNumber* vector;
	vector = NULL;
	FileHelper* fileHelper;
	DirectedOrderNumberGenerator* generator;
	DirectedEquationMethod* operations;
	generator = new DirectedOrderNumberGenerator(2, 4, 0.01);
	fileHelper = new FileHelper(9);
	int chose = 100;
	string fileName, folderName;
	operations = new DirectedEquationMethod(0.01);
	cout << "Rozmiar liczby skierowanej: " << sizeof(DirectedOrderNumber) << endl;
	cout << "Domyslne ustawienia:\nGenerator przedzial podloga 2 sufit 10, precyzja 10^-8\nPrecyzja zapisu wartosci zmiennoprzecinkowej 10^-9\n";
	cout << "Wybierz opcje\n";
	while (chose != 0)
	{
		cout << OptionList();
		cin >> chose;
		switch (chose)
		{
		case 1:

			cout << "Podaj ilosc rzedu macierzy\n";
			cin >> rows;

			equation = generator->GenerateEquationwithoutFreeValues(rows);
			vector = generator->GenerateSampleVector(rows);
			generator->FillEquationWithFreeValues(equation, vector, rows);
			/*for (int i = 0; i < rows ; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					cout << equation[i][j].infimum << endl;
				}
			}
			*/
		
			cout << "Wpisz nazwe folderu z przykladem\n";
			cin >> folderName;
			fileHelper->CreateEquationFolder(folderName);

			cout << "Wpisz nazwe pliku dla ukladu\n";
			cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);

			cout << "Wpisz nazwe pliku dla wektora rozwiazan\n";
			cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
		
			break;

		case 2:
			cout << "Eliminacja Gaussa trwa...\n";
			start = chrono::high_resolution_clock::now();
			vector = operations->GaussElemination(equation, rows);
			end = chrono::high_resolution_clock::now();
		
			cout << "Wpisz nazwe pliku dla ukladu po eliminacji\n";
			cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);
			cout << "Wpisz nazwe pliku dla wektora rozwiazania ukladu rownan\n";
			cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			
			chrono::duration<double> elapsed = end - start;
			cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
			break;

		case 3:
			cout << "Eliminac Gaussa-Jordana\n";
			start = chrono::steady_clock::now();
			vector = operations->GaussJordanElemination(equation, rows);
			end = chrono::steady_clock::now();		
			/*
			cout << "Wpisz nazwe pliku dla ukladu po eliminacji\n";
			cin >> fileName;			
			elapsed = end - start;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);
			cout << "Wpisz nazwe pliku dla wektora rozwiazania ukladu rownan\n";
			cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			*/
			cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
			break;
		case 4:
			cout << "Wpisz nazwe folderu z przykladem\n";
			cin >> folderName;
			cout << "Wpisz nazwe plik z uk³adem\n";
			cin >> fileName;
			equation = fileHelper->ReadEquation(fileName, folderName, &rows);
			break;
		//Wywo³anie testowego przyk³adu
		case 6:
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					cout << std::setprecision(13) << equation[i][j].infimum;
				}
			}
			break;
		case 100:
			equation = generator->SimpleSampleEquationFourRowsTest();
			vector = operations->GaussElemination(equation, 4);
	/*
			for (int i = 0; i < 4; i++)
			{
				for(int j = 0; j<=4;j++)
					std::cout << "(" << equation[i][j].infimum << "," << equation[i][j].supremum << ") ";
				std::cout << "\n";
			}

			for (int i = 0; i < 4; i++)
			{
				std::cout << "X" << i << ": (" << vector[i].infimum << "," << vector[i].supremum << ")\n";
			}
			*/
			break;

		default:
			chose = 0;
			break;
		}

	}
	if (equation != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			delete[](equation[i]);
		}

		delete[] equation;
	}

	if (vector != NULL)
		delete[] vector;

	delete fileHelper;
	delete generator;
	
	std::cout << "End\n";
	return 0;

}

